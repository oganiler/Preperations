# C++ Challenge — 25–40 min · Difficulty: Medium

## Rolling maximum of a radar RCS stream

A radar front-end delivers a stream of per-detection RCS values in dBsm. A downstream
tracker needs, for every position, the maximum RCS over a fixed window of the last `k`
samples — a cheap peak-hold used to suppress dropout in the detection confidence.

Implement:

```cpp
std::vector<float> RollingMaxRcs(std::span<const float> rcs_dbsm, std::size_t k);
```

`result[i] = max(rcs_dbsm[i .. i + k - 1])` for `i` in `[0, n - k]`, so the output has
`n - k + 1` elements.

### Examples

```
rcs_dbsm = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
result   = [3, 3, 5, 5, 6, 7]

rcs_dbsm = [5, 4, 3, 2, 1], k = 2
result   = [5, 4, 3, 2]

rcs_dbsm = [3, 1, 4, 1, 5], k = 5
result   = [5]
```

### Constraints

- `1 <= k <= n <= 2e5`
- values are finite `float`, may be negative (dBsm routinely is)
- `rcs_dbsm` is a non-owning view; the callee must not take ownership or copy the input

### Required complexity

- **Time:** O(n). An O(n·k) solution does not count as solved.
- **Auxiliary space:** O(k), excluding the output.
- **Allocation:** no heap allocation in the steady-state loop. The test harness counts
  global `operator new` calls during your function and prints the number. Anything beyond
  a small constant at setup means you are allocating per iteration.

### What the review will grade

Correctness and edge cases; the complexity you actually achieved (not the one you intended);
memory safety under ASan/UBSan; const-correctness and ownership; whether the code would pass
an automotive static-analysis gate; and how clearly you narrate the approach.

### Run it

```bash
./scripts/run_drill.sh days/2026-09-10_sliding-window            # ASan + UBSan + tests
./scripts/run_drill.sh days/2026-09-10_sliding-window --release  # -O2, for the timing number
```

Write your attempt in `solution.cpp`. Do not open `.sealed/`.
