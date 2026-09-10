# Daily Technical Fact — 5–10 min

**Concept:** why scaled dot-product attention divides by `sqrt(d_k)`.

## The math, with numbers

Attention scores come from `q · k` for query/key vectors in `R^{d_k}`. Assume the components
are independent, zero-mean, unit-variance (roughly what LayerNorm + sane init gives you):

```
E[q·k] = sum_i E[q_i] E[k_i]          = 0
Var(q·k) = sum_i Var(q_i k_i)
         = sum_i (E[q_i^2] E[k_i^2] - 0)
         = sum_i 1 * 1                = d_k
```

So the logits entering softmax are approximately `N(0, d_k)`.

Put real numbers in. `d_k = 64` → std = 8. Over a row of `N` keys, the spread between the
largest and smallest logit is on the order of tens. Concretely, two logits 20 apart give

```
softmax weight ratio = exp(20) ≈ 4.85e8
```

i.e. one key takes essentially all the mass. The softmax Jacobian is
`J = diag(p) - p p^T`; when `p → e_j` (one-hot), every entry of `J` → 0. The gradient into
`Q` and `K` dies. That is the failure mode: not wrong outputs, but **no learning signal**.

Divide by `sqrt(d_k) = 8` and the logits are back to `N(0, 1)`, which is the regime where
softmax has usable curvature.

## The same thing in code (Eigen)

```cpp
#include <Eigen/Dense>

// scores: [N] logits for one query against N keys
Eigen::VectorXf Softmax(const Eigen::VectorXf& scores)
{
    const float m = scores.maxCoeff();          // stability shift, always do this
    Eigen::VectorXf e = (scores.array() - m).exp();
    return e / e.sum();
}

// d_k = 64, N = 8 keys
Eigen::VectorXf q = Eigen::VectorXf::Random(64);
Eigen::MatrixXf K = Eigen::MatrixXf::Random(8, 64);

Eigen::VectorXf raw    = K * q;                                  // Var ~ d_k
Eigen::VectorXf scaled = (K * q) / std::sqrt(64.0F);             // Var ~ 1

// raw    -> softmax ~ [0, 0, 1, 0, ...]           entropy ~ 0, grad ~ 0
// scaled -> softmax ~ [0.09, 0.16, 0.21, ...]     entropy high, grad alive
```

Note `maxCoeff()` subtraction: that is a *numerical* stability trick (avoids `exp` overflow)
and is orthogonal to the `sqrt(d_k)` scaling, which is a *statistical* one. Interviewers
routinely conflate them — you should not.

## Where this bites you in ADAS work

Any BEV/occupancy transformer with per-head `d_k = 64..128` and deformable or cross-attention
into image features. If someone hand-rolls attention in a custom CUDA kernel and forgets the
scale, the network still trains — just very badly, and the symptom looks like a learning-rate
problem, not a bug.

## Interview question

> A colleague replaces `softmax(QKᵀ / sqrt(d_k))` with `softmax(QKᵀ / d_k)` and reports that
> training is *more* stable early on but plateaus at worse accuracy. Explain both halves of
> that observation, and say what you would measure to confirm your explanation.

Answer sealed. Attempt it out loud, in under 2 minutes, before revealing.

## Source

Vaswani et al., *Attention Is All You Need*, §3.2.1 — the scaling by `1/sqrt(d_k)` is
motivated exactly by large-magnitude dot products pushing softmax into a
small-gradient region: https://arxiv.org/abs/1706.03762
