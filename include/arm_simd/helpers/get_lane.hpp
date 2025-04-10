#pragma once
#include <utility>
#include "argon/features.h"
#include "arm_simd.hpp"
#include "scalar.hpp"

#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#elifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd mve
#else
#define SIMDE_ENABLE_NATIVE_ALIASES
#include <arm/neon.h>
#define simd neon
#endif

#ifdef ARGON_PLATFORM_SIMDE
#define nce
#elifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace simd {

/// @brief Get the lane of a SIMD vector at a specified index.
/// @tparam T The SIMD vector type (e.g., int8x16_t, float32x4_t).
/// @param vec The SIMD vector to get the lane from.
/// @param i The index of the lane to get (0-based).
/// @return The value of the specified lane in the SIMD vector.
template <typename T>
nce Scalar_t<T> get_lane(T vec, const int i) {
  constexpr size_t lanes = sizeof(T) / sizeof(Scalar_t<T>);
  if constexpr (lanes == 1) {
    return simd::get_lane<0>(vec);
  } else if constexpr (lanes == 2) {
    switch (i) {
      case 0:
        return simd::get_lane<0>(vec);
      case 1:
        return simd::get_lane<1>(vec);
      default:
        std::unreachable();
    }
  } else if constexpr (lanes == 4) {
    switch (i) {
      case 0:
        return simd::get_lane<0>(vec);
      case 1:
        return simd::get_lane<1>(vec);
      case 2:
        return simd::get_lane<2>(vec);
      case 3:
        return simd::get_lane<3>(vec);
      default:
        std::unreachable();
    }
  } else if constexpr (lanes == 8) {
    switch (i) {
      case 0:
        return simd::get_lane<0>(vec);
      case 1:
        return simd::get_lane<1>(vec);
      case 2:
        return simd::get_lane<2>(vec);
      case 3:
        return simd::get_lane<3>(vec);
      case 4:
        return simd::get_lane<4>(vec);
      case 5:
        return simd::get_lane<5>(vec);
      case 6:
        return simd::get_lane<6>(vec);
      case 7:
        return simd::get_lane<7>(vec);
      default:
        std::unreachable();
    }
  } else if constexpr (lanes == 16) {
    switch (i) {
      case 0:
        return simd::get_lane<0>(vec);
      case 1:
        return simd::get_lane<1>(vec);
      case 2:
        return simd::get_lane<2>(vec);
      case 3:
        return simd::get_lane<3>(vec);
      case 4:
        return simd::get_lane<4>(vec);
      case 5:
        return simd::get_lane<5>(vec);
      case 6:
        return simd::get_lane<6>(vec);
      case 7:
        return simd::get_lane<7>(vec);
      case 8:
        return simd::get_lane<8>(vec);
      case 9:
        return simd::get_lane<9>(vec);
      case 10:
        return simd::get_lane<10>(vec);
      case 11:
        return simd::get_lane<11>(vec);
      case 12:
        return simd::get_lane<12>(vec);
      case 13:
        return simd::get_lane<13>(vec);
      case 14:
        return simd::get_lane<14>(vec);
      case 15:
        return simd::get_lane<15>(vec);
      default:
        std::unreachable();
    }
  } else {
    std::unreachable();
  }
}
}  // namespace simd
#undef simd
