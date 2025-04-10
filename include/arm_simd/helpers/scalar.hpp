#pragma once
#include <type_traits>
#include "argon/features.h"

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

namespace simd {
// clang-format off

/// @brief Helper template to get the scalar type of a SIMD vector type.
/// @tparam T The SIMD vector type (e.g., int8x16_t, float32x4_t).
template <typename T> struct Scalar;

/// @cond EXCLUDE
template <> struct Scalar<int8x16_t>   { using type = int8_t; };
template <> struct Scalar<uint8x16_t>  { using type = uint8_t; };
template <> struct Scalar<int16x8_t>   { using type = int16_t; };
template <> struct Scalar<uint16x8_t>  { using type = uint16_t; };
template <> struct Scalar<int32x4_t>   { using type = int32_t; };
template <> struct Scalar<uint32x4_t>  { using type = uint32_t; };
template <> struct Scalar<int64x2_t>   { using type = int64_t; };
template <> struct Scalar<uint64x2_t>  { using type = uint64_t; };

#if ARGON_HAS_SINGLE_FLOAT
template <> struct Scalar<float32x4_t> { using type = float; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct Scalar<float16x8_t> { using type = float16_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct Scalar<float64x2_t> { using type = double; };
#endif

#ifndef ARGON_PLATFORM_MVE
template <> struct Scalar<int8x8_t> { using type = int8_t; };
template <> struct Scalar<uint8x8_t> { using type = uint8_t; };
template <> struct Scalar<int16x4_t> { using type = int16_t; };
template <> struct Scalar<uint16x4_t> { using type = uint16_t; };
template <> struct Scalar<int32x2_t> { using type = int32_t; };
template <> struct Scalar<uint32x2_t> { using type = uint32_t; };
template <> struct Scalar<int64x1_t> { using type = int64_t; };
template <> struct Scalar<uint64x1_t> { using type = uint64_t; };
#if ARGON_HAS_SINGLE_FLOAT
template <> struct Scalar<float32x2_t> { using type = float; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct Scalar<float16x4_t> { using type = float16_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct Scalar<float64x1_t> { using type = double; };
#endif
#endif
/// @endcond

/// @brief Helper alias to get the scalar type of a SIMD vector type.
/// @tparam T The SIMD vector type (e.g., int8x16_t, float32x4_t).
template <typename T>
using Scalar_t = typename Scalar<std::remove_cv_t<T>>::type;

// clang-format on
}  // namespace simd
#undef simd
