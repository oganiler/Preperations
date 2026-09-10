#include "problem.h"

// -----------------------------------------------------------------------------
// Your attempt goes here.
//
// Targets:
//   * O(width * height) time
//   * scratch allocated once, before the pixel loop; nothing on the heap inside it
//   * stack depth independent of image content (a 4 MP blob must not overflow it)
//   * labels numbered 1..N in raster-scan order of first appearance
//   * const-correct, explicit conversions, no owning raw pointers, no UB at the borders
//
// Build + check:  ./scripts/run_drill.sh days/cv/2026-09-11_connected-components
// -----------------------------------------------------------------------------

std::uint32_t LabelComponents(std::span<const std::uint8_t> mask,
                              std::size_t width,
                              std::size_t height,
                              std::span<std::uint32_t> labels_out)
{
    static_cast<void>(mask);
    static_cast<void>(width);
    static_cast<void>(height);
    static_cast<void>(labels_out);

    // TODO: implement.

    return 0U;
}
