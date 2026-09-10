# C++ Challenge — 25–40 min · Difficulty: Medium · Category: CV

## Connected-component labelling of a segmentation mask

The semantic-segmentation head of your perception network emits a binary mask: one byte per
pixel, non-zero meaning "drivable surface". Before the mask is useful to the planner it has
to be turned into *instances* — each maximally connected blob gets its own integer id, so
downstream code can measure areas, reject specks, and track blobs across frames.

Implement:

```cpp
std::uint32_t LabelComponents(std::span<const std::uint8_t> mask,
                              std::size_t width,
                              std::size_t height,
                              std::span<std::uint32_t> labels_out);
```

- `mask` is row-major, `mask[y * width + x]`. Non-zero is foreground, zero is background.
- Two foreground pixels belong to the same component when they are **4-connected**
  (up / down / left / right). Diagonal contact does **not** connect.
- Write into `labels_out`: `0` for every background pixel, and for foreground pixels the id
  of its component.
- Return the number of components found.

### Label numbering is part of the specification

Components are numbered `1, 2, 3, ...` **in raster-scan order of first appearance** — the
component containing the first foreground pixel in row-major order is `1`, the component
containing the first foreground pixel not belonging to `1` is `2`, and so on. Two runs on
the same input must produce byte-identical output.

### Examples

```
width = 5, height = 3          mask            labels_out          returns
                            1 1 0 0 1        1 1 0 0 2
                            0 1 0 0 1        0 1 0 0 2               3
                            1 0 0 1 1        3 0 0 2 2

width = 3, height = 3          mask            labels_out          returns
                            1 0 1            1 0 1
                            1 0 1            1 0 1                   1
                            1 1 1            1 1 1

width = 3, height = 3          mask            labels_out          returns
                            1 0 1            1 0 2
                            0 1 0            0 3 0                   5
                            1 0 1            4 0 5
```

### Constraints

- `1 <= width, height`, and `width * height <= 4'000'000`
- `mask.size() == width * height == labels_out.size()` is a precondition
- the number of components can be as large as `(width * height + 1) / 2`
- `mask` is a read-only view; `labels_out` is a caller-owned buffer. The callee owns neither
  and must not retain either beyond the call.

### Required complexity

- **Time:** O(width · height). A solution that rescans the image once per component does not
  count as solved.
- **Auxiliary space:** O(width · height) worst case, but allocated **once**, before the pixel
  loop.
- **Allocation:** no heap allocation in the steady-state loop. The harness counts global
  `operator new` calls during your function and prints the number.
- **Stack:** bounded and independent of image content. Recursion whose depth scales with
  component size is a defect here, not a style preference — a 4 MP mask must not be able to
  blow the stack.

### What the review will grade

Correctness on merges and on the numbering rule; the complexity you actually achieved;
memory safety under ASan/UBSan; const-correctness, ownership and explicit conversions;
whether it would pass an automotive static-analysis gate; and how clearly you narrate the
approach before you write it.

### Run it

```bash
./scripts/run_drill.sh days/cv/2026-09-11_connected-components
./scripts/run_drill.sh days/cv/2026-09-11_connected-components --release
```

Write your attempt in `solution.cpp`. Fill `notes.md` §2 **before** you start coding.
Do not open `.sealed/`.
