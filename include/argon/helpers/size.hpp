#pragma once
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

namespace argon::helpers {
/// @brief Calculates the size of a vectorized range.
/// @tparam T The type of the elements in the range.
/// @param size The size of the range.
/// @return The size of the vectorized range.
template <typename T>
constexpr size_t vectorizeable_size(size_t size) {
  constexpr size_t lanes = sizeof(simd::Vec128_t<T>) / sizeof(T);
  return size & ~(lanes - 1);
}

/// @brief Calculates the number of vectorized elements in a range.
/// @tparam T The type of the elements in the range.
/// @param size The size of the range.
/// @return The number of vectorized elements in the range.
template <typename T>
constexpr size_t vectorized_size(size_t size) {
  constexpr size_t lanes = sizeof(simd::Vec128_t<T>) / sizeof(T);
  return vectorizeable_size<T>(size) / lanes;
}
}  // namespace argon::helpers
#undef simd
