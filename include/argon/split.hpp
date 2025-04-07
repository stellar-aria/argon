#pragma once
#include <span>
#include <tuple>
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

namespace argon {

/// @brief Split a span into two spans, with the first span aligned to the vector size
/// @param span The span to split
/// @return A pair of spans, the first divisible by the vector size and the second containing any remaining elements
template <typename scalar_type>
std::pair<std::span<scalar_type>, std::span<scalar_type>> split_head_aligned(std::span<scalar_type> span) {
  constexpr size_t lanes = sizeof(simd::Vec128_t<scalar_type>) / sizeof(scalar_type);
  return {span.first(span.size() & ~(lanes - 1)), span.last(span.size() & (lanes - 1))};
}

/// @brief Split a span into two spans, with the second span aligned to the vector size
/// @param span The span to split
/// @return A pair of spans, the first containing any remaining elements and the second divisible by the vector size
template <typename scalar_type>
std::pair<std::span<scalar_type>, std::span<scalar_type>> split_tail_aligned(std::span<scalar_type> span) {
  constexpr size_t lanes = sizeof(simd::Vec128_t<scalar_type>) / sizeof(scalar_type);
  return {span.first(span.size() & (lanes - 1)), span.last(span.size() & ~(lanes - 1))};
}
}  // namespace argon
#undef simd
