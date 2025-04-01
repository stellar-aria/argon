#pragma once
#include "argon/features.h"

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


namespace simd {
// clang-format off
#if ARGON_HAS_DWORD
template <typename type> struct Vec64;
template <> struct Vec64<int8_t> { using type = int8x8_t; };
template <> struct Vec64<uint8_t> { using type = uint8x8_t; };
template <> struct Vec64<int16_t> { using type = int16x4_t; };
template <> struct Vec64<uint16_t> { using type = uint16x4_t; };
template <> struct Vec64<int32_t> { using type = int32x2_t; };
template <> struct Vec64<uint32_t> { using type = uint32x2_t; };
template <> struct Vec64<int64_t> { using type = int64x1_t; };
template <> struct Vec64<uint64_t> { using type = uint64x1_t; };

#if ARGON_HAS_SINGLE_FLOAT
template <> struct Vec64<float> {using type = float32x2_t; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct Vec64<float16_t> {using type = float16x4_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct Vec64<float64_t> {using type = float64x1_t; };
#endif

template <typename T>
using Vec64_t = typename Vec64<T>::type;

#endif
// clang-format on
}  // namespace simd
#undef simd
