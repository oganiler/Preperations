#include "problem.h"

#include <cstdlib>
#include <new>
#include <random>

#include "common/drill_test.hpp"

namespace {
std::size_t g_alloc_count = 0U;
}

void* operator new(std::size_t size) {
  g_alloc_count++;
  void* const p = std::malloc(size);
  if (p == nullptr) { throw std::bad_alloc(); }
  return p;
}
void* operator new[](std::size_t size) { return ::operator new(size); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete[](void* p) noexcept { std::free(p); }
void operator delete(void* p, std::size_t) noexcept { std::free(p); }
void operator delete[](void* p, std::size_t) noexcept { std::free(p); }

int main() {
  std::cout << "== <title> ==\n";

  // TODO: cases - typical, boundary, degenerate, adversarial, scale.

  return drill::summary();
}
