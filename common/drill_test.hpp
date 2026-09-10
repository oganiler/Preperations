#ifndef DRILL_TEST_HPP
#define DRILL_TEST_HPP

// Minimal dependency-free test harness.
// Rationale: an interview drill must build with one g++ invocation on any machine.
// Swap for GoogleTest later if you want fixtures/parameterised tests.

#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace drill {

struct Stats {
  std::uint32_t checks_run{0U};
  std::uint32_t checks_failed{0U};
};

inline Stats& stats() {
  static Stats s{};
  return s;
}

inline void report(const std::string& case_name, bool ok, const std::string& detail) {
  stats().checks_run++;
  if (ok) {
    std::cout << "  [ ok ] " << case_name << '\n';
  } else {
    stats().checks_failed++;
    std::cout << "  [FAIL] " << case_name << "\n         " << detail << '\n';
  }
}

template <typename T>
std::string to_string(const std::vector<T>& v) {
  std::string out{"["};
  for (std::size_t i = 0U; i < v.size(); ++i) {
    out += std::to_string(v[i]);
    if (i + 1U < v.size()) {
      out += ", ";
    }
  }
  return out + "]";
}

template <typename T>
void expect_eq_vec(const std::string& case_name,
                   const std::vector<T>& actual,
                   const std::vector<T>& expected,
                   T tolerance = static_cast<T>(0)) {
  bool ok = actual.size() == expected.size();
  if (ok) {
    for (std::size_t i = 0U; i < actual.size(); ++i) {
      if (std::fabs(static_cast<double>(actual[i] - expected[i])) >
          static_cast<double>(tolerance)) {
        ok = false;
        break;
      }
    }
  }
  report(case_name, ok, "got " + to_string(actual) + " expected " + to_string(expected));
}

inline void expect_true(const std::string& case_name, bool condition,
                        const std::string& detail = "condition was false") {
  report(case_name, condition, detail);
}

/// Wall-clock a callable, in milliseconds. Not a benchmark - a budget smoke test.
template <typename Fn>
double time_ms(Fn&& fn) {
  const auto t0 = std::chrono::steady_clock::now();
  fn();
  const auto t1 = std::chrono::steady_clock::now();
  return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

inline int summary() {
  std::cout << "\n" << stats().checks_run - stats().checks_failed << "/" << stats().checks_run
            << " checks passed\n";
  return (stats().checks_failed == 0U) ? 0 : 1;
}

}  // namespace drill

#endif  // DRILL_TEST_HPP
