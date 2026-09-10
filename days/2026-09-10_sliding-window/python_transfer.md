# Python Transfer — 5–10 min

Do this **after** the C++ attempt.

## Task

Write the same rolling maximum in Python, O(n), then answer three questions about the
differences.

```python
from typing import Sequence

def rolling_max_rcs(rcs_dbsm: Sequence[float], k: int) -> list[float]:
    ...
```

## Questions

1. `collections.deque` gives you O(1) `append`/`popleft`. What is it actually implemented as
   in CPython, and why does that make the constant factor behave differently from the
   contiguous ring buffer you would write in C++?

2. `numpy.lib.stride_tricks.sliding_window_view(a, k).max(axis=-1)` produces the same answer
   in one line. What is its time complexity, what does it do to memory, and in what regime
   would you still prefer it in a real pipeline?

3. In C++ you pass `std::span<const float>` — a non-owning view with no lifetime guarantees.
   What is the closest Python equivalent, and where does the analogy break down with respect
   to object lifetime?

Answers sealed with the rest of the session.
