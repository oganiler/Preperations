#ifndef LABEL_COMPONENTS_H
#define LABEL_COMPONENTS_H

#include <cstddef>
#include <cstdint>
#include <span>

/// \brief Label the 4-connected components of a binary segmentation mask.
///
/// \param mask        Row-major, width*height bytes. Non-zero = foreground.
/// \param width       Image width in pixels.
/// \param height      Image height in pixels.
/// \param labels_out  Caller-owned output buffer, width*height elements. Background
///                    pixels are written as 0; foreground pixels receive the id of
///                    their component.
/// \return Number of components found.
///
/// Components are numbered 1..N in raster-scan order of first appearance.
///
/// Preconditions: mask.size() == width * height == labels_out.size().
/// Target: O(width*height) time, one allocation before the pixel loop, no heap
/// allocation in the steady-state loop, stack depth independent of image content.
std::uint32_t LabelComponents(std::span<const std::uint8_t> mask,
                              std::size_t width,
                              std::size_t height,
                              std::span<std::uint32_t> labels_out);

#endif  // LABEL_COMPONENTS_H
