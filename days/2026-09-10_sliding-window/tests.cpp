#include "problem.h"

#include <cstdlib>
#include <new>
#include <random>

#include "drill_test.hpp"

// ---------------------------------------------------------------------------
// Allocation counter.
// Automotive angle: after init, a real-time perception node must not touch the
// heap. This counts every global operator new so the drill can tell you whether
// your solution allocates inside the loop.
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

int main() {
  using drill::expect_eq_vec;
  using drill::expect_true;

  std::cout << "== rolling max RCS ==\n";

  {
    const std::vector<float> in{1.0F, 3.0F, -1.0F, -3.0F, 5.0F, 3.0F, 6.0F, 7.0F};
    expect_eq_vec<float>("basic k=3", RollingMaxRcs(in, 3U),
                         {3.0F, 3.0F, 5.0F, 5.0F, 6.0F, 7.0F});
  }
  {
    const std::vector<float> in{1.0F, 3.0F, -1.0F, -3.0F, 5.0F};
    expect_eq_vec<float>("k=1 is identity", RollingMaxRcs(in, 1U), in);
  }
  {
    const std::vector<float> in{3.0F, 1.0F, 4.0F, 1.0F, 5.0F};
    expect_eq_vec<float>("k == n", RollingMaxRcs(in, 5U), {5.0F});
  }
  {
    const std::vector<float> in{2.0F, 2.0F, 2.0F, 2.0F};
    expect_eq_vec<float>("all equal", RollingMaxRcs(in, 2U), {2.0F, 2.0F, 2.0F});
  }
  {
    const std::vector<float> in{5.0F, 4.0F, 3.0F, 2.0F, 1.0F};
    expect_eq_vec<float>("strictly decreasing", RollingMaxRcs(in, 2U),
                         {5.0F, 4.0F, 3.0F, 2.0F});
  }
  {
    const std::vector<float> in{1.0F, 2.0F, 3.0F, 4.0F, 5.0F};
    expect_eq_vec<float>("strictly increasing", RollingMaxRcs(in, 3U), {3.0F, 4.0F, 5.0F});
  }
  {
    const std::vector<float> in{2.0F, 1.0F, 2.0F, 1.0F, 2.0F};
    expect_eq_vec<float>("duplicate maxima across windows", RollingMaxRcs(in, 3U),
                         {2.0F, 2.0F, 2.0F});
  }
  {
    const std::vector<float> in{-9.0F, -2.0F, -7.0F, -1.0F};
    expect_eq_vec<float>("all negative dBsm", RollingMaxRcs(in, 2U), {-2.0F, -2.0F, -1.0F});
  }
  {
    const std::vector<float> in{42.0F};
    expect_eq_vec<float>("single element", RollingMaxRcs(in, 1U), {42.0F});
  }

  // --- scale + latency budget + allocation behaviour ---------------------
  {
    constexpr std::size_t kN = 200000U;
    constexpr std::size_t kK = 1000U;
    std::vector<float> in(kN);
    std::mt19937 rng(42U);
    std::uniform_real_distribution<float> dist(-40.0F, 30.0F);
    for (float& v : in) {
      v = dist(rng);
    }

    std::vector<float> out;
    const std::size_t alloc_before = g_alloc_count;
    const double ms = drill::time_ms([&]() { out = RollingMaxRcs(in, kK); });
    const std::size_t allocs = g_alloc_count - alloc_before;

    expect_true("n=200000 output size", out.size() == kN - kK + 1U,
                "got " + std::to_string(out.size()));

    // Brute force reference on a sparse subset of windows.
    bool matches = true;
    for (std::size_t i = 0U; i + kK <= kN; i += 4999U) {
      float m = in[i];
      for (std::size_t j = i; j < i + kK; ++j) {
        m = (in[j] > m) ? in[j] : m;
      }
      if (out[i] != m) {
        matches = false;
        break;
      }
    }
    expect_true("n=200000 matches brute force (sampled)", matches, "mismatch found");

    std::cout << "         elapsed: " << std::fixed << std::setprecision(2) << ms << " ms"
              << "   heap allocations during call: " << allocs << '\n';
    std::cout << "         (<=3 = output + scratch, allocated once at setup. "
                 "Dozens or more = you are allocating inside the loop.)\n";
  }

  return drill::summary();
}
