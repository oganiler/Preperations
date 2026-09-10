#ifndef ROLLING_MAX_RCS_H
#define ROLLING_MAX_RCS_H

#include <cstddef>
#include <span>
#include <vector>

/// \brief Rolling maximum of a radar RCS stream over a window of size k.
///
/// Returns r where r[i] = max(rcs_dbsm[i .. i + k - 1]), i in [0, n - k].
/// Output size is n - k + 1.
///
/// Preconditions: 1 <= k <= rcs_dbsm.size().
/// Target: O(n) time, O(k) auxiliary space, no heap allocation in the steady-state loop.
std::vector<float> RollingMaxRcs(std::span<const float> rcs_dbsm, std::size_t k);

#endif  // ROLLING_MAX_RCS_H
