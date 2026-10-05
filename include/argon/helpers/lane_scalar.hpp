#pragma once
#include <concepts>
#include <type_traits>
#include "argon/features.h"

#if ARGON_HAS_HALF_FLOAT
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#else
#include <arm_neon.h>
#endif
#endif

/// @file lane_scalar.hpp
/// @brief Concepts for the scalar types a vector lane can hold.

namespace argon {

/// @brief Whether T is the half-precision lane type, float16_t (__fp16), on a platform with half-float vectors.
/// @details The standard type traits don't count __fp16 as arithmetic or floating point, so it needs naming.
template <typename T>
constexpr bool is_half_float_v =
#if ARGON_HAS_HALF_FLOAT
    std::is_same_v<std::remove_cv_t<T>, float16_t>;
#else
    false;
#endif

/// @brief A scalar type a vector lane can hold: an arithmetic type, or float16_t where half-float vectors exist.
template <typename T>
concept lane_scalar = std::is_arithmetic_v<T> || is_half_float_v<T>;

/// @brief A floating-point lane type: float, double, or float16_t where half-float vectors exist.
template <typename T>
concept lane_floating_point = std::floating_point<T> || is_half_float_v<T>;

}  // namespace argon
