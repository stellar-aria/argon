
#pragma once
#include "argon/features.h"

#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

namespace simd {
// clang-format off
template <typename type> struct Vec128 {};
template <> struct Vec128<int8_t>  {using type = int8x16_t; };
template <> struct Vec128<uint8_t>  {using type = uint8x16_t; };
template <> struct Vec128<int16_t>  {using type = int16x8_t; };
template <> struct Vec128<uint16_t>  {using type = uint16x8_t; };
template <> struct Vec128<int32_t>  {using type = int32x4_t; };
template <> struct Vec128<uint32_t>  {using type = uint32x4_t; };
template <> struct Vec128<int64_t>  {using type = int64x2_t; };
template <> struct Vec128<uint64_t>  {using type = uint64x2_t; };

#if ARGON_HAS_HALF_FLOAT
template <> struct Vec128<float16_t> {using type = float16x8_t; };
#endif

#if ARGON_HAS_SINGLE_FLOAT
template <> struct Vec128<float>  {using type = float32x4_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct Vec128<double> {using type = float64x2_t; };
#endif

template <typename T>
using Vec128_t = typename Vec128<T>::type;

// clang-format on
}  // namespace simd
#undef simd
