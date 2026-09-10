# Python Transfer — 5–10 min

Do this **after** the C++ attempt.

## Task

Write the same labelling in Python, O(W·H), matching the raster-order numbering rule.

```python
import numpy as np

def label_components(mask: np.ndarray) -> tuple[np.ndarray, int]:
    """mask: 2-D uint8 array, non-zero = foreground.
    Returns (labels, count) with labels numbered 1..count in raster order
    of first appearance, 0 for background."""
    ...
```

## Questions

1. `scipy.ndimage.label(mask)` does this in one line. What connectivity does it use by
   default in 2-D, how do you change it, and what does its `structure` argument actually
   represent? If you had to guarantee the raster-order numbering rule above, could you rely
   on the library's numbering — and how would you find out?

2. Your first instinct in Python might be a recursive flood fill. State the concrete limit
   that breaks on a 4 MP mask, why CPython hits it so much earlier than a C++ recursive
   version would, and what the iterative rewrite costs you in readability.

3. In C++ the output is a caller-owned `std::span<std::uint32_t>` — a non-owning view with
   no lifetime guarantee whatsoever. What is the closest equivalent in NumPy, both for the
   *view* and for the *caller-provides-the-buffer* convention? Name the one mechanism NumPy
   has that makes its views strictly safer than `std::span`.

Answers sealed with the rest of the session.
