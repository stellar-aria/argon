#pragma once
#include <type_traits>
#include "../arm_simd.hpp"
#include "features.h"

/// @file helpers.hpp
/// @brief Provides utility templates and concepts for type traits and compile-time iteration.
/// This header defines a set of utilities for working with type traits, including determining
/// the next larger or smaller type for a given type, as well as compile-time iteration.

/// @brief Contains helper templates and concepts for type manipulation and compile-time utilities.
namespace argon::helpers {
// clang-format off

/// @brief Helper template to determine if a type has a smaller corresponding type.
/// @tparam T The type to check.
template <typename T>
constexpr bool has_smaller_v =
    std::is_same_v<T, uint16_t>
    || std::is_same_v<T, uint32_t>
    || std::is_same_v<T, uint64_t>
    || std::is_same_v<T, int16_t>
    || std::is_same_v<T, int32_t>
    || std::is_same_v<T, int64_t>
    || std::is_same_v<T, double>
#if ARGON_HAS_HALF_FLOAT
    || std::is_same_v<T, float>
    || std::is_same_v<T, float32_t>
#endif
    ;

/// @brief Helper template to determine if a type has a larger corresponding type.
/// @tparam T The type to check.
template <typename T>
constexpr bool has_larger_v =
    std::is_same_v<T, uint8_t>
    || std::is_same_v<T, uint16_t>
    || std::is_same_v<T, uint32_t>
    || std::is_same_v<T, int8_t>
    || std::is_same_v<T, int16_t>
    || std::is_same_v<T, int32_t>
    || std::is_same_v<T, float>
#if ARGON_HAS_HALF_FLOAT
    || std::is_same_v<T, std::float16_t>
#endif
    ;

/// @brief Concept to check if a type has a smaller corresponding type.
template <typename T>
concept has_smaller = has_smaller_v<T>;

//// @brief Concept to check if a type has a larger corresponding type.
template <typename T>
concept has_larger = has_larger_v<T>;

/// @brief Helper template to determine the next larger type for a given type.
/// @tparam T The type to determine the next larger type for.
template <typename T> struct NextLarger;
/// @cond EXCLUDE
template <> struct NextLarger<int8_t> { using type = int16_t; };
template <> struct NextLarger<uint8_t> { using type = uint16_t; };
template <> struct NextLarger<int16_t> { using type = int32_t; };
template <> struct NextLarger<uint16_t> { using type = uint32_t; };
template <> struct NextLarger<int32_t> { using type = int64_t; };
template <> struct NextLarger<uint32_t> { using type = uint64_t; };
template <> struct NextLarger<float> { using type = double; };
#if ARGON_HAS_HALF_FLOAT
template <> struct NextLarger<float16_t> { using type = float; };
#endif
/// @endcond

/// @brief Helper alias to get the next larger type for a given type.
/// @tparam T  The type to determine the next larger type for.
template <typename T>
using NextLarger_t = NextLarger<T>::type;

/// @brief Helper template to determine the next smaller type for a given type.
/// @tparam T The type to determine the next smaller type for.
template <typename T> struct NextSmaller;

/// @cond EXCLUDE
template <> struct NextSmaller<int16_t> { using type = int8_t; };
template <> struct NextSmaller<uint16_t> { using type = uint8_t; };
template <> struct NextSmaller<int32_t> { using type = int16_t; };
template <> struct NextSmaller<uint32_t> { using type = uint16_t; };
template <> struct NextSmaller<int64_t> { using type = int32_t; };
template <> struct NextSmaller<uint64_t> { using type = uint32_t; };
template <> struct NextSmaller<double> { using type = float; };
#if ARGON_HAS_HALF_FLOAT
template <> struct NextSmaller<float> { using type = float16_t; };
#endif
/// @endcond

/// @brief Helper alias to get the next smaller type for a given type.
/// @tparam T The type to determine the next smaller type for.
template <typename T>
using NextSmaller_t = NextSmaller<T>::type;

/// @brief A constexpr function template for compile-time iteration. Used to unroll loops at compile time.
/// @tparam Start The starting value of the iteration.
/// @tparam End The ending value of the iteration.
/// @tparam Increment The increment value for each iteration step.
/// @tparam FunctionType The callable type to be invoked during each iteration step.
/// @param f The callable object to be invoked with the current iteration value.
template <auto Start, auto End, auto Increment, class FunctionType>
constexpr void consteval_for(FunctionType&& f) {
	if constexpr (Start < End) {
		f.template operator()<Start>();
		consteval_for<Start + Increment, End, Increment>(f);
	}
}

// clang-format on
}  // namespace argon::helpers
