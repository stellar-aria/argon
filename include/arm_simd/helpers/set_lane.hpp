#pragma once
#include <utility>
#include "arm_simd.hpp"
#include "scalar.hpp"


#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#elifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
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
    return simd::set_lane<0>(vec, a);
  } else if constexpr (lanes == 2) {
    switch (i) {
      case 0:
        return simd::set_lane<0>(vec, a);
      case 1:
        return simd::set_lane<1>(vec, a);
      default:
        std::unreachable();
    }
  } else if constexpr (lanes == 4) {
    switch (i) {
      case 0:
        return simd::set_lane<0>(vec, a);
      case 1:
        return simd::set_lane<1>(vec, a);
      case 2:
        return simd::set_lane<2>(vec, a);
      case 3:
        return simd::set_lane<3>(vec, a);
      default:
        std::unreachable();
    }
  } else if constexpr (lanes == 8) {
    switch (i) {
      case 0:
        return simd::set_lane<0>(vec, a);
      case 1:
        return simd::set_lane<1>(vec, a);
      case 2:
        return simd::set_lane<2>(vec, a);
      case 3:
        return simd::set_lane<3>(vec, a);
      case 4:
        return simd::set_lane<4>(vec, a);
      case 5:
        return simd::set_lane<5>(vec, a);
      case 6:
        return simd::set_lane<6>(vec, a);
      case 7:
        return simd::set_lane<7>(vec, a);
      default:
        std::unreachable();
    }
  } else if constexpr (lanes == 16) {
    switch (i) {
      case 0:
        return simd::set_lane<0>(vec, a);
      case 1:
        return simd::set_lane<1>(vec, a);
      case 2:
        return simd::set_lane<2>(vec, a);
      case 3:
        return simd::set_lane<3>(vec, a);
      case 4:
        return simd::set_lane<4>(vec, a);
      case 5:
        return simd::set_lane<5>(vec, a);
      case 6:
        return simd::set_lane<6>(vec, a);
      case 7:
        return simd::set_lane<7>(vec, a);
      case 8:
        return simd::set_lane<8>(vec, a);
      case 9:
        return simd::set_lane<9>(vec, a);
      case 10:
        return simd::set_lane<10>(vec, a);
      case 11:
        return simd::set_lane<11>(vec, a);
      case 12:
        return simd::set_lane<12>(vec, a);
      case 13:
        return simd::set_lane<13>(vec, a);
      case 14:
        return simd::set_lane<14>(vec, a);
      case 15:
        return simd::set_lane<15>(vec, a);
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
