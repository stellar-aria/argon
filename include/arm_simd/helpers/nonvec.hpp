#pragma once
#include <type_traits>
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
template <typename T> struct NonVec;
template <> struct NonVec<int8x16_t>   { using type = int8_t; };
template <> struct NonVec<uint8x16_t>  { using type = uint8_t; };
template <> struct NonVec<int16x8_t>   { using type = int16_t; };
template <> struct NonVec<uint16x8_t>  { using type = uint16_t; };
template <> struct NonVec<int32x4_t>   { using type = int32_t; };
template <> struct NonVec<uint32x4_t>  { using type = uint32_t; };
template <> struct NonVec<int64x2_t>   { using type = int64_t; };
template <> struct NonVec<uint64x2_t>  { using type = uint64_t; };

#if ARGON_HAS_SINGLE_FLOAT
template <> struct NonVec<float32x4_t> { using type = float; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct NonVec<float16x8_t> { using type = float16_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct NonVec<float64x2_t> { using type = double; };
#endif

#if ARGON_HAS_DWORD
template <> struct NonVec<int8x8_t> { using type = int8_t; };
template <> struct NonVec<uint8x8_t> { using type = uint8_t; };
template <> struct NonVec<int16x4_t> { using type = int16_t; };
template <> struct NonVec<uint16x4_t> { using type = uint16_t; };
template <> struct NonVec<int32x2_t> { using type = int32_t; };
template <> struct NonVec<uint32x2_t> { using type = uint32_t; };
template <> struct NonVec<int64x1_t> { using type = int64_t; };
template <> struct NonVec<uint64x1_t> { using type = uint64_t; };
#if ARGON_HAS_SINGLE_FLOAT
template <> struct NonVec<float32x2_t> { using type = float; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct NonVec<float16x4_t> { using type = float16_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct NonVec<float64x1_t> { using type = double; };
#endif
#endif

template <typename T>
using NonVec_t = typename NonVec<std::remove_cv_t<T>>::type;

// clang-format on
}  // namespace simd
#undef simd
