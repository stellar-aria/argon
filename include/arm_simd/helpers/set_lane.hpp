#pragma once
#include <utility>
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

/// @brief Set the lane of a SIMD vector to a specified value.
/// @tparam T  The SIMD vector type (e.g., int8x16_t, float32x4_t).
/// @param vec  The SIMD vector to modify.
/// @param i The index of the lane to set (0-based).
/// @param a  The value to set the lane to.
/// @return  The modified SIMD vector with the specified lane set to the given value.
template <typename T>
nce T set_lane(T vec, const int i, Scalar_t<T> a) {
  constexpr size_t lanes = sizeof(T) / sizeof(Scalar_t<T>);
  if constexpr (lanes == 1) {
    return simd::set_lane<0>(a, vec);
  } else if constexpr (lanes == 2) {
    switch (i) {
      case 0:
        return simd::set_lane<0>(a, vec);
      case 1:
        return simd::set_lane<1>(a, vec);
      default:
        std::unreachable();
    }
  } else if constexpr (lanes == 4) {
    switch (i) {
      case 0:
        return simd::set_lane<0>(a, vec);
      case 1:
        return simd::set_lane<1>(a, vec);
      case 2:
        return simd::set_lane<2>(a, vec);
      case 3:
        return simd::set_lane<3>(a, vec);
      default:
        std::unreachable();
    }
  } else if constexpr (lanes == 8) {
    switch (i) {
      case 0:
        return simd::set_lane<0>(a, vec);
      case 1:
        return simd::set_lane<1>(a, vec);
      case 2:
        return simd::set_lane<2>(a, vec);
      case 3:
        return simd::set_lane<3>(a, vec);
      case 4:
        return simd::set_lane<4>(a, vec);
      case 5:
        return simd::set_lane<5>(a, vec);
      case 6:
        return simd::set_lane<6>(a, vec);
      case 7:
        return simd::set_lane<7>(a, vec);
      default:
        std::unreachable();
    }
  } else if constexpr (lanes == 16) {
    switch (i) {
      case 0:
        return simd::set_lane<0>(a, vec);
      case 1:
        return simd::set_lane<1>(a, vec);
      case 2:
        return simd::set_lane<2>(a, vec);
      case 3:
        return simd::set_lane<3>(a, vec);
      case 4:
        return simd::set_lane<4>(a, vec);
      case 5:
        return simd::set_lane<5>(a, vec);
      case 6:
        return simd::set_lane<6>(a, vec);
      case 7:
        return simd::set_lane<7>(a, vec);
      case 8:
        return simd::set_lane<8>(a, vec);
      case 9:
        return simd::set_lane<9>(a, vec);
      case 10:
        return simd::set_lane<10>(a, vec);
      case 11:
        return simd::set_lane<11>(a, vec);
      case 12:
        return simd::set_lane<12>(a, vec);
      case 13:
        return simd::set_lane<13>(a, vec);
      case 14:
        return simd::set_lane<14>(a, vec);
      case 15:
        return simd::set_lane<15>(a, vec);
      default:
        std::unreachable();
    }
  } else {
    std::unreachable();
  }
}

}  // namespace simd
#undef simd
#undef nce
