#pragma once
#include <type_traits>
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

/// @brief Templated constant to determine if a type is a quad-word SIMD vector type.
/// @tparam T The type to check.
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
#if ARGON_HAS_DOUBLE_FLOAT
    || std::is_same_v<T, float64x2_t>
#endif
#if ARGON_HAS_HALF_FLOAT
    || std::is_same_v<T, float16x8_t>
#endif
#if ARGON_HAS_BRAIN_FLOAT
    || std::is_same_v<T, bfloat16x8_t>
#endif
#if ARGON_HAS_POLY
    || std::is_same_v<T, poly8x16_t>
    || std::is_same_v<T, poly16x8_t>
    || std::is_same_v<T, poly32x4_t>
    || std::is_same_v<T, poly64x2_t>
#endif
    ;
// clang-format on


/// @brief Concept to check if a type is a quad-word SIMD vector type.
/// @tparam T The type to check.
/// @note This concept is used to constrain template parameters to only accept quad-word SIMD vector types.
template <typename T>
concept is_quadword = is_quadword_v<T>;

#if ARGON_HAS_DWORD
// clang-format off

/// @brief Templated constant to determine if a type is a double-word SIMD vector type.
/// @tparam T The type to check.
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
#if ARGON_HAS_SINGLE_FLOAT
|| std::is_same_v<T, float32x2_t>
#endif
#if ARGON_HAS_DOUBLE_FLOAT
|| std::is_same_v<T, float64x1_t>
#endif
#if ARGON_HAS_HALF_FLOAT
|| std::is_same_v<T, float16x4_t>
#endif
#if ARGON_HAS_BRAIN_FLOAT
|| std::is_same_v<T, bfloat16x4_t>
#endif
#if ARGON_HAS_POLY
|| std::is_same_v<T, poly8x8_t>
|| std::is_same_v<T, poly16x4_t>
|| std::is_same_v<T, poly32x2_t>
|| std::is_same_v<T, poly64x1_t>
#endif
;
// clang-format on


/// @brief Concept to check if a type is a double-word SIMD vector type.
/// @tparam T The type to check.
template <typename T>
concept is_doubleword = is_doubleword_v<T>;
#endif

/// @concept is_vector_type
/// @brief Concept to check if a type is a vector type (either double-word or quad-word).
/// @tparam T The type to check.
#if ARGON_HAS_DWORD
template <typename T>
concept is_vector_type = is_doubleword<T> || is_quadword<T>;
#else
template <typename T>
concept is_vector_type = is_quadword<T>;
#endif

}  // namespace simd
#undef simd
