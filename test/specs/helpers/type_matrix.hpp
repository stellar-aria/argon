#pragma once
#include <array>
#include <cstdint>
#include <numeric>
#include <tuple>
#include "argon/features.h"

// clang-format off

namespace argon::test {

/// All integer scalar types supported by NEON/MVE vectors.
using AllIntTypes = std::tuple<
  int8_t, uint8_t,
  int16_t, uint16_t,
  int32_t, uint32_t,
  int64_t, uint64_t
>;

/// Signed integer types only.
using SignedIntTypes = std::tuple<int8_t, int16_t, int32_t, int64_t>;

/// Unsigned integer types only.
using UnsignedIntTypes = std::tuple<uint8_t, uint16_t, uint32_t, uint64_t>;

/// Float types guarded by platform capability macros.
#if ARGON_HAS_SINGLE_FLOAT
using Float32Types = std::tuple<float>;
#else
using Float32Types = std::tuple<>;
#endif

#if ARGON_HAS_DOUBLE_FLOAT
using Float64Types = std::tuple<double>;
#else
using Float64Types = std::tuple<>;
#endif

/// All floating-point types available on the current platform.
/// On A32/VFPv3 this is just float; on A64 it also includes double.
using AllFloatTypes = decltype(std::tuple_cat(Float32Types{}, Float64Types{}));

/// Union of integer and floating-point types.
using AllTypes = decltype(std::tuple_cat(AllIntTypes{}, AllFloatTypes{}));

/// Integer types that can be narrowed (have a smaller counterpart).
using NarrowableIntTypes = std::tuple<int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>;

/// Subword integer types (8-bit and 16-bit) — useful for widening tests.
using WidenableIntTypes = std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t>;

/// @brief Fill an array with sequentially increasing values starting at `start`.
/// @tparam T  Scalar element type.
/// @tparam N  Number of elements.
template <typename T, size_t N>
std::array<T, N> iota_array(T start = T{0}) {
  std::array<T, N> arr;
  std::iota(arr.begin(), arr.end(), start);
  return arr;
}

/// @brief Fill an array by repeating a single value across all elements.
template <typename T, size_t N>
std::array<T, N> fill_array(T value) {
  std::array<T, N> arr;
  arr.fill(value);
  return arr;
}

}  // namespace argon::test
