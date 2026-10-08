#pragma once
#include <utility>
#include "argon/features.h"
#include "arm_simd.hpp"
#include "concepts.hpp"
#include "scalar.hpp"
#include "vec64.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd mve
#else
#define simd neon
#endif

#ifdef ARGON_PLATFORM_SIMDE
#define nce [[gnu::always_inline]] inline
#elifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace simd {
#ifndef ARGON_PLATFORM_MVE
namespace detail {
/// @brief Broadcast lane `Lane` of the 64-bit vector `vec` across a VectorType.
template <typename VectorType, int Lane>
nce VectorType duplicate_half_lane(Vec64_t<Scalar_t<VectorType>> vec) {
  if constexpr (is_quadword_v<VectorType>) {
    return simd::duplicate_lane_quad<Lane>(vec);
  } else if constexpr (sizeof(VectorType) == sizeof(Scalar_t<VectorType>)) {
    return vec;  // a one-lane vector is its own broadcast
  } else {
    return simd::duplicate_lane<Lane>(vec);
  }
}
}  // namespace detail

/// @brief Broadcast lane `i` of the 64-bit vector `vec` across a VectorType, a 64- or 128-bit vector.
/// @details A runtime Lane of a quadword hands over the 64-bit half that holds the lane and the lane's index within
/// that half, so `i` indexes the lanes of `vec`: 8 of them for 8-bit lanes, down to 1 for 64-bit lanes.
template <typename VectorType>
nce VectorType duplicate_lane(Vec64_t<Scalar_t<VectorType>> vec, const int i) {
  constexpr int half_lanes = sizeof(Vec64_t<Scalar_t<VectorType>>) / sizeof(Scalar_t<VectorType>);
  if constexpr (half_lanes == 1) {
    return detail::duplicate_half_lane<VectorType, 0>(vec);
  } else if constexpr (half_lanes == 2) {
    switch (i) {
      case 0:
        return detail::duplicate_half_lane<VectorType, 0>(vec);
      case 1:
        return detail::duplicate_half_lane<VectorType, 1>(vec);
      default:
        std::unreachable();
    }
  } else if constexpr (half_lanes == 4) {
    switch (i) {
      case 0:
        return detail::duplicate_half_lane<VectorType, 0>(vec);
      case 1:
        return detail::duplicate_half_lane<VectorType, 1>(vec);
      case 2:
        return detail::duplicate_half_lane<VectorType, 2>(vec);
      case 3:
        return detail::duplicate_half_lane<VectorType, 3>(vec);
      default:
        std::unreachable();
    }
  } else {
    static_assert(half_lanes == 8);
    switch (i) {
      case 0:
        return detail::duplicate_half_lane<VectorType, 0>(vec);
      case 1:
        return detail::duplicate_half_lane<VectorType, 1>(vec);
      case 2:
        return detail::duplicate_half_lane<VectorType, 2>(vec);
      case 3:
        return detail::duplicate_half_lane<VectorType, 3>(vec);
      case 4:
        return detail::duplicate_half_lane<VectorType, 4>(vec);
      case 5:
        return detail::duplicate_half_lane<VectorType, 5>(vec);
      case 6:
        return detail::duplicate_half_lane<VectorType, 6>(vec);
      case 7:
        return detail::duplicate_half_lane<VectorType, 7>(vec);
      default:
        std::unreachable();
    }
  }
}
#endif
}  // namespace simd
#undef simd
#undef nce
