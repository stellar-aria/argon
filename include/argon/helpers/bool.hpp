#pragma once
#include "arm_simd/helpers/make_unsigned.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

namespace argon {
// clang-format off

/// @brief  Helper template to determine the boolean type of a SIMD operation.
/// @tparam T
template <typename T> struct Bool {
  using type = typename simd::make_unsigned<T>::type;
};

#if ARGON_HAS_SINGLE_FLOAT
template <> struct Bool<float32x4_t> { using type = uint32x4_t; };

#if ARGON_HAS_DWORD
template <> struct Bool<float32x2_t> { using type = uint32x2_t; };
#endif
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct Bool<float64x2_t> { using type = uint64x2_t; };

#if ARGON_HAS_DWORD
template <> struct Bool<float64x1_t> { using type = uint64x1_t; };
#endif
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct Bool<float16x8_t> { using type = uint16x8_t; };

#if ARGON_HAS_DWORD
template <> struct Bool<float16x4_t> { using type = uint16x4_t; };
#endif
#endif

template <typename T>
using Bool_t = Bool<T>::type;
// clang-format on
}  // namespace argon::helpers
#undef simd
