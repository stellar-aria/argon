#pragma once
#include "features.h"
#include "../arm_simd.hpp"

#include <type_traits>
namespace argon::impl {
// clang-format off

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
#endif
    ;

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
    || std::is_same_v<T, float16_t>
#endif
    ;

template <typename T>
concept has_smaller = has_smaller_v<T>;

template <typename T>
concept has_larger = has_larger_v<T>;

template <typename T> struct NextLarger;
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

template <typename T>
using NextLarger_t = NextLarger<T>::type;

template <typename T> struct NextSmaller;
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

template <typename T>
using NextSmaller_t = NextSmaller<T>::type;

template <auto Start, auto End, auto Inc, class F>
constexpr void constexpr_for(F&& f) {
	if constexpr (Start < End) {
		f.template operator()<Start>();
		constexpr_for<Start + Inc, End, Inc>(f);
	}
}

// clang-format on
}  // namespace argon::impl
