#include "problem.h"

// -----------------------------------------------------------------------------
// Your attempt goes here.
//
// Targets:
//   * O(n) time, O(k) auxiliary space
//   * no heap allocation in the steady-state loop (the output vector is allowed)
//   * const-correct, no owning raw pointers, no UB on the boundaries
//
// Build + check:  ./scripts/run_drill.sh days/2026-09-10_sliding-window
// -----------------------------------------------------------------------------

std::vector<float> RollingMaxRcs(std::span<const float> rcs_dbsm, std::size_t k)
{
    std::vector<float> rolling_max;
    rolling_max.reserve(rcs_dbsm.size() - k + 1U);

    // TODO: implement.

    return rolling_max;
}
