#pragma once
#include <cstddef>
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

/// @brief  Helper template for multi-vector types of different SIMD types and sizes.
/// @tparam T The SIMD type (e.g., int8x16_t, float32x4_t).
/// @tparam size The number of vectors to be packed together (e.g., 2, 3, 4).
template <typename T, size_t size>
struct MultiVector;

// clang-format off
/// @cond EXCLUDE
template <> struct MultiVector<int8x16_t, 2> { using type = int8x16x2_t; };
template <> struct MultiVector<uint8x16_t, 2> { using type = uint8x16x2_t; };
template <> struct MultiVector<int16x8_t, 2> { using type = int16x8x2_t; };
template <> struct MultiVector<uint16x8_t, 2> { using type = uint16x8x2_t; };
template <> struct MultiVector<int32x4_t, 2> { using type = int32x4x2_t; };
template <> struct MultiVector<uint32x4_t, 2> { using type = uint32x4x2_t; };
template <> struct MultiVector<int64x2_t, 2> { using type = int64x2x2_t; };
template <> struct MultiVector<uint64x2_t, 2> { using type = uint64x2x2_t; };
template <> struct MultiVector<float32x4_t, 2> { using type = float32x4x2_t; };

#ifndef ARGON_PLATFORM_MVE
template <> struct MultiVector<int8x16_t, 3> { using type = int8x16x3_t; };
template <> struct MultiVector<uint8x16_t, 3> { using type = uint8x16x3_t; };
template <> struct MultiVector<int16x8_t, 3> { using type = int16x8x3_t; };
template <> struct MultiVector<uint16x8_t, 3> { using type = uint16x8x3_t; };
template <> struct MultiVector<int32x4_t, 3> { using type = int32x4x3_t; };
template <> struct MultiVector<uint32x4_t, 3> { using type = uint32x4x3_t; };
template <> struct MultiVector<int64x2_t, 3> { using type = int64x2x3_t; };
template <> struct MultiVector<uint64x2_t, 3> { using type = uint64x2x3_t; };
template <> struct MultiVector<float32x4_t, 3> { using type = float32x4x3_t; };
#endif

template <> struct MultiVector<int8x16_t, 4> { using type = int8x16x4_t; };
template <> struct MultiVector<uint8x16_t, 4> { using type = uint8x16x4_t; };
template <> struct MultiVector<int16x8_t, 4> { using type = int16x8x4_t; };
template <> struct MultiVector<uint16x8_t, 4> { using type = uint16x8x4_t; };
template <> struct MultiVector<int32x4_t, 4> { using type = int32x4x4_t; };
template <> struct MultiVector<uint32x4_t, 4> { using type = uint32x4x4_t; };
template <> struct MultiVector<int64x2_t, 4> { using type = int64x2x4_t; };
template <> struct MultiVector<uint64x2_t, 4> { using type = uint64x2x4_t; };
template <> struct MultiVector<float32x4_t, 4> { using type = float32x4x4_t; };

#ifndef ARGON_PLATFORM_MVE
template <> struct MultiVector<float32x2_t, 2> { using type = float32x2x2_t; };
template <> struct MultiVector<poly8x8_t, 2> { using type = poly8x8x2_t; };
template <> struct MultiVector<poly16x4_t, 2> { using type = poly16x4x2_t; };

template <> struct MultiVector<float32x2_t, 3> { using type = float32x2x3_t; };
template <> struct MultiVector<poly8x8_t, 3> { using type = poly8x8x3_t; };
template <> struct MultiVector<poly16x4_t, 3> { using type = poly16x4x3_t; };

template <> struct MultiVector<float32x2_t, 4> { using type = float32x2x4_t; };
template <> struct MultiVector<poly8x8_t, 4> { using type = poly8x8x4_t; };
template <> struct MultiVector<poly16x4_t, 4> { using type = poly16x4x4_t; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct MultiVector<float16x8_t, 2> { using type = float16x8x2_t; };

#ifndef ARGON_PLATFORM_MVE
template <> struct MultiVector<float16x8_t, 3> { using type = float16x8x3_t; };
#endif

template <> struct MultiVector<float16x8_t, 4> { using type = float16x8x4_t; };
#endif


#ifndef ARGON_PLATFORM_MVE
template <> struct MultiVector<int8x8_t, 2> { using type = int8x8x2_t; };
template <> struct MultiVector<uint8x8_t, 2> { using type = uint8x8x2_t; };
template <> struct MultiVector<int16x4_t, 2> { using type = int16x4x2_t; };
template <> struct MultiVector<uint16x4_t, 2> { using type = uint16x4x2_t; };
template <> struct MultiVector<int32x2_t, 2> { using type = int32x2x2_t; };
template <> struct MultiVector<uint32x2_t, 2> { using type = uint32x2x2_t; };
template <> struct MultiVector<int64x1_t, 2> { using type = int64x1x2_t; };
template <> struct MultiVector<uint64x1_t, 2> { using type = uint64x1x2_t; };

template <> struct MultiVector<int8x8_t, 3> { using type = int8x8x3_t; };
template <> struct MultiVector<uint8x8_t, 3> { using type = uint8x8x3_t; };
template <> struct MultiVector<int16x4_t, 3> { using type = int16x4x3_t; };
template <> struct MultiVector<uint16x4_t, 3> { using type = uint16x4x3_t; };
template <> struct MultiVector<int32x2_t, 3> { using type = int32x2x3_t; };
template <> struct MultiVector<uint32x2_t, 3> { using type = uint32x2x3_t; };
template <> struct MultiVector<int64x1_t, 3> { using type = int64x1x3_t; };
template <> struct MultiVector<uint64x1_t, 3> { using type = uint64x1x3_t; };

template <> struct MultiVector<int8x8_t, 4> { using type = int8x8x4_t; };
template <> struct MultiVector<uint8x8_t, 4> { using type = uint8x8x4_t; };
template <> struct MultiVector<int16x4_t, 4> { using type = int16x4x4_t; };
template <> struct MultiVector<uint16x4_t, 4> { using type = uint16x4x4_t; };
template <> struct MultiVector<int32x2_t, 4> { using type = int32x2x4_t; };
template <> struct MultiVector<uint32x2_t, 4> { using type = uint32x2x4_t; };
template <> struct MultiVector<int64x1_t, 4> { using type = int64x1x4_t; };
template <> struct MultiVector<uint64x1_t, 4> { using type = uint64x1x4_t; };

#if ARGON_HAS_HALF_FLOAT
template <> struct MultiVector<float16x4_t, 2> { using type = float16x4x2_t; };
template <> struct MultiVector<float16x4_t, 3> { using type = float16x4x3_t; };
template <> struct MultiVector<float16x4_t, 4> { using type = float16x4x4_t; };
#endif
#endif
/// @endcond // EXCLUDE

/// @brief  Helper alias for multi-vector types of different SIMD types and sizes.
/// @tparam T The SIMD type (e.g., int8x16_t, float32x4_t).
/// @tparam size The number of vectors to be packed together (e.g., 2, 3, 4).
template <typename T, size_t size>
using MultiVector_t = MultiVector<T, size>::type;
}
