#pragma once
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
/// @brief Helper template to get the SIMD double-word vector type for a given scalar type.
/// @tparam T The scalar type to get the SIMD vector type for.
template <typename T, size_t Lanes> struct Vector;


/// @cond EXCLUDE
template <> struct Vector<int8_t, 16> { using type = int8x16_t; };
template <> struct Vector<uint8_t, 16> { using type = uint8x16_t; };
template <> struct Vector<int16_t, 8> { using type = int16x8_t; };
template <> struct Vector<uint16_t, 8> { using type = uint16x8_t; };
template <> struct Vector<int32_t, 4> { using type = int32x4_t; };
template <> struct Vector<uint32_t, 4> { using type = uint32x4_t; };
template <> struct Vector<int64_t, 2> { using type = int64x2_t; };
template <> struct Vector<uint64_t, 2> { using type = uint64x2_t; };

#if ARGON_HAS_SINGLE_FLOAT
template <> struct Vector<float, 4> {using type = float32x4_t; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct Vector<float16_t, 8> {using type = float16x8_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct Vector<float64_t, 2> {using type = float64x2_t; };
#endif

#ifndef ARGON_PLATFORM_MVE
template <> struct Vector<int8_t, 8> { using type = int8x8_t; };
template <> struct Vector<uint8_t, 8> { using type = uint8x8_t; };
template <> struct Vector<int16_t, 4> { using type = int16x4_t; };
template <> struct Vector<uint16_t, 4> { using type = uint16x4_t; };
template <> struct Vector<int32_t, 2> { using type = int32x2_t; };
template <> struct Vector<uint32_t, 2> { using type = uint32x2_t; };
template <> struct Vector<int64_t, 1> { using type = int64x1_t; };
template <> struct Vector<uint64_t, 1> { using type = uint64x1_t; };

#if ARGON_HAS_SINGLE_FLOAT
template <> struct Vector<float, 2> {using type = float32x2_t; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct Vector<float16_t, 4> {using type = float16x4_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct Vector<float64_t, 1> {using type = float64x1_t; };
#endif
#endif
/// @endcond

/// @brief Helper alias to get the SIMD vector type for a given scalar type.
/// @tparam T The scalar type to get the SIMD vector type for.
template <typename T, size_t Lanes>
using Vector_t = typename Vector<T, Lanes>::type;

// clang-format on
}  // namespace simd
#undef simd
