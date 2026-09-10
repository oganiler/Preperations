#include "problem.h"

#include <cstdlib>
#include <new>
#include <string>
#include <vector>

#include "drill_test.hpp"

// ---------------------------------------------------------------------------
// Allocation counter.
// Automotive angle: after init, a real-time perception node must not touch the
// heap. This counts every global operator new so the drill can tell you whether
// your solution allocates inside the pixel loop.
// ---------------------------------------------------------------------------
namespace {
std::size_t g_alloc_count = 0U;
}

void* operator new(std::size_t size) {
  g_alloc_count++;
  void* const p = std::malloc(size);
  if (p == nullptr) {
    throw std::bad_alloc();
  }
  return p;
}
void* operator new[](std::size_t size) { return ::operator new(size); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete[](void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }
void operator delete[](void* p, std::size_t) noexcept { std::free(p); }

namespace {

struct Image {
  std::vector<std::uint8_t> mask;
  std::size_t width{0U};
  std::size_t height{0U};
};

/// '#' = foreground, '.' = background.
Image FromRows(const std::vector<std::string>& rows) {
  Image img;
  img.height = rows.size();
  img.width = rows.empty() ? 0U : rows.front().size();
  img.mask.assign(img.width * img.height, static_cast<std::uint8_t>(0));
  for (std::size_t y = 0U; y < img.height; ++y) {
    for (std::size_t x = 0U; x < img.width; ++x) {
      img.mask[(y * img.width) + x] =
          (rows[y][x] == '#') ? static_cast<std::uint8_t>(1) : static_cast<std::uint8_t>(0);
    }
  }
  return img;
}

/// Exact check: component count and the full label buffer.
void ExpectLabels(const std::string& case_name,
                  const std::vector<std::string>& rows,
                  std::uint32_t expected_count,
                  const std::vector<std::uint32_t>& expected_labels) {
  const Image img = FromRows(rows);
  std::vector<std::uint32_t> out(img.mask.size(), 0xFFFFFFFFU);
  const std::uint32_t n = LabelComponents(img.mask, img.width, img.height, out);
  drill::expect_true(case_name + " [count]", n == expected_count,
                     "got " + std::to_string(n) + " expected " +
                         std::to_string(expected_count));
  drill::expect_eq_vec<std::uint32_t>(case_name + " [labels]", out, expected_labels);
}

/// Structural check for masks too large to write out by hand.
///  - background is 0, foreground is non-zero
///  - 4-adjacent foreground pixels carry the same label  (catches a missed merge)
///  - the labels seen in raster order are exactly 1, 2, 3, ... N  (catches numbering bugs
///    and over-merging)
bool CheckInvariants(const Image& img,
                     const std::vector<std::uint32_t>& labels,
                     std::uint32_t count,
                     std::string& why) {
  const std::size_t w = img.width;
  const std::size_t h = img.height;
  if (labels.size() != img.mask.size()) {
    why = "labels_out was not written over its whole length";
    return false;
  }

  std::uint32_t next_expected = 1U;
  std::vector<bool> seen(static_cast<std::size_t>(count) + 1U, false);

  for (std::size_t y = 0U; y < h; ++y) {
    for (std::size_t x = 0U; x < w; ++x) {
      const std::size_t i = (y * w) + x;
      const bool fg = img.mask[i] != 0U;
      const std::uint32_t lab = labels[i];

      if (!fg) {
        if (lab != 0U) {
          why = "background pixel at (" + std::to_string(x) + "," + std::to_string(y) +
                ") got label " + std::to_string(lab);
          return false;
        }
        continue;
      }
      if (lab == 0U || lab > count) {
        why = "foreground pixel at (" + std::to_string(x) + "," + std::to_string(y) +
              ") got label " + std::to_string(lab) + ", count was " + std::to_string(count);
        return false;
      }
      if (!seen[lab]) {
        if (lab != next_expected) {
          why = "first appearance of label " + std::to_string(lab) + " at (" +
                std::to_string(x) + "," + std::to_string(y) + ") but expected " +
                std::to_string(next_expected) + " - raster-order numbering violated";
          return false;
        }
        seen[lab] = true;
        next_expected++;
      }
      if ((x + 1U) < w) {
        const std::size_t r = i + 1U;
        if ((img.mask[r] != 0U) && (labels[r] != lab)) {
          why = "horizontally adjacent foreground pixels at (" + std::to_string(x) + "," +
                std::to_string(y) + ") have labels " + std::to_string(lab) + " and " +
                std::to_string(labels[r]);
          return false;
        }
      }
      if ((y + 1U) < h) {
        const std::size_t d = i + w;
        if ((img.mask[d] != 0U) && (labels[d] != lab)) {
          why = "vertically adjacent foreground pixels at (" + std::to_string(x) + "," +
                std::to_string(y) + ") have labels " + std::to_string(lab) + " and " +
                std::to_string(labels[d]);
          return false;
        }
      }
    }
  }

  if ((next_expected - 1U) != count) {
    why = "returned " + std::to_string(count) + " components but " +
          std::to_string(next_expected - 1U) + " distinct labels were used";
    return false;
  }
  return true;
}

}  // namespace

int main() {
  std::cout << "== connected-component labelling ==\n";

  // ---- exact, hand-checked cases -----------------------------------------
  ExpectLabels("three blobs", {"##..#",
                               ".#..#",
                               "#..##"},
               3U, {1U, 1U, 0U, 0U, 2U,
                    0U, 1U, 0U, 0U, 2U,
                    3U, 0U, 0U, 2U, 2U});

  ExpectLabels("horseshoe joins at the bottom", {"#.#",
                                                 "#.#",
                                                 "###"},
               1U, {1U, 0U, 1U,
                    1U, 0U, 1U,
                    1U, 1U, 1U});

  ExpectLabels("diagonal contact does not connect", {"#.",
                                                     ".#"},
               2U, {1U, 0U,
                    0U, 2U});

  ExpectLabels("checkerboard", {"#.#",
                                ".#.",
                                "#.#"},
               5U, {1U, 0U, 2U,
                    0U, 3U, 0U,
                    4U, 0U, 5U});

  // The one that separates a correct implementation from a plausible one: two
  // provisional labels in row 0 turn out to be the same component, so the blob in
  // the corner must come out as 2, not 3.
  ExpectLabels("merge then renumber", {"#.#..",
                                       "###..",
                                       "....#"},
               2U, {1U, 0U, 1U, 0U, 0U,
                    1U, 1U, 1U, 0U, 0U,
                    0U, 0U, 0U, 0U, 2U});

  ExpectLabels("all background", {"....",
                                  "...."},
               0U, {0U, 0U, 0U, 0U,
                    0U, 0U, 0U, 0U});

  ExpectLabels("single pixel", {"#"}, 1U, {1U});

  ExpectLabels("single row", {"#####"}, 1U, {1U, 1U, 1U, 1U, 1U});

  ExpectLabels("single column", {"#", "#", ".", "#"}, 2U, {1U, 1U, 0U, 2U});

  ExpectLabels("full mask is one component", {"###",
                                              "###"},
               1U, {1U, 1U, 1U,
                    1U, 1U, 1U});

  // ---- large structured cases --------------------------------------------
  {
    // 333 x 333 grid of separated 2x2 blocks: the component count is known exactly.
    Image img;
    img.width = 999U;
    img.height = 999U;
    img.mask.assign(img.width * img.height, static_cast<std::uint8_t>(0));
    for (std::size_t y = 0U; y < img.height; ++y) {
      for (std::size_t x = 0U; x < img.width; ++x) {
        const bool fg = ((y % 3U) != 2U) && ((x % 3U) != 2U);
        img.mask[(y * img.width) + x] = fg ? static_cast<std::uint8_t>(1)
                                           : static_cast<std::uint8_t>(0);
      }
    }
    std::vector<std::uint32_t> out(img.mask.size(), 0xFFFFFFFFU);

    const std::size_t before = g_alloc_count;
    std::uint32_t n = 0U;
    const double ms = drill::time_ms(
        [&] { n = LabelComponents(img.mask, img.width, img.height, out); });
    const std::size_t allocs = g_alloc_count - before;

    drill::expect_true("999x999 grid of blocks: exact count", n == 110889U,
                       "got " + std::to_string(n) + " expected 110889");
    std::string why;
    drill::expect_true("999x999 grid of blocks: invariants",
                       CheckInvariants(img, out, n, why), why);

    std::cout << "         elapsed: " << std::fixed << std::setprecision(2) << ms << " ms"
              << "   heap allocations during call: " << allocs << '\n';
    std::cout << "         (a small constant = scratch allocated once at setup. Dozens or\n"
                 "          more = you are allocating inside the pixel loop.)\n";
  }
  {
    // Comb: 501 vertical teeth joined by the bottom row. Everything is one component,
    // and a naive merge strategy degrades badly here.
    Image img;
    img.width = 1001U;
    img.height = 501U;
    img.mask.assign(img.width * img.height, static_cast<std::uint8_t>(0));
    for (std::size_t y = 0U; y < img.height; ++y) {
      for (std::size_t x = 0U; x < img.width; ++x) {
        const bool fg = ((x % 2U) == 0U) || (y == (img.height - 1U));
        img.mask[(y * img.width) + x] = fg ? static_cast<std::uint8_t>(1)
                                           : static_cast<std::uint8_t>(0);
      }
    }
    std::vector<std::uint32_t> out(img.mask.size(), 0xFFFFFFFFU);
    std::uint32_t n = 0U;
    const double ms = drill::time_ms(
        [&] { n = LabelComponents(img.mask, img.width, img.height, out); });

    drill::expect_true("comb: 501 teeth merge into one component", n == 1U,
                       "got " + std::to_string(n) + " expected 1");
    std::string why;
    drill::expect_true("comb: invariants", CheckInvariants(img, out, n, why), why);
    std::cout << "         elapsed: " << std::fixed << std::setprecision(2) << ms << " ms\n";
  }

  return drill::summary();
}
