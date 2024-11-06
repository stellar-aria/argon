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
template <typename T>
constexpr bool is_quadword_v =
       std::is_same_v<T, uint8x16_t>
    || std::is_same_v<T, uint16x8_t>
    || std::is_same_v<T, uint32x4_t>
    || std::is_same_v<T, uint64x2_t>
    || std::is_same_v<T, int8x16_t>
    || std::is_same_v<T, int16x8_t>
    || std::is_same_v<T, int32x4_t>
    || std::is_same_v<T, int64x2_t>
#if ARGON_HAS_SINGLE_FLOAT
    || std::is_same_v<T, float32x4_t>
#endif
    ;
// clang-format on
template <typename T>
concept is_quadword = is_quadword_v<T>;

#if ARGON_HAS_DWORD
// clang-format off
template <typename T>
constexpr bool is_doubleword_v =
       std::is_same_v<T, uint8x8_t>
    || std::is_same_v<T, uint16x4_t>
    || std::is_same_v<T, uint32x2_t>
    || std::is_same_v<T, uint64x1_t>
    || std::is_same_v<T, int8x8_t>
    || std::is_same_v<T, int16x4_t>
    || std::is_same_v<T, int32x2_t>
    || std::is_same_v<T, int64x1_t>
    || std::is_same_v<T, float32x2_t>
    ;
// clang-format on

template <typename T>
concept is_doubleword = is_doubleword_v<T>;

template <typename T>
concept is_vector_type = is_doubleword<T> || is_quadword<T>;
#else
template <typename T>
concept is_vector_type = is_quadword<T>;
#endif

}  // namespace simd
#undef simd
