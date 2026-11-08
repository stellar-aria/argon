#pragma once
/// @file simde_fused.hpp
/// @brief The single-precision fused multiply-add of the VFPv4 layer, for SIMDe on a host with FMA.
/// @details SIMDe's vfma/vfms on x86 are a multiply and an add, with two roundings, so the fused forms go lane by lane
/// through std::fma, which a host compiled with FMA lowers to one fused instruction. arm_simd/neon/vfpv4.hpp is
/// not used here: it declares half-precision forms SIMDe lacks.

#include "arm_simd/helpers/simde_neon.hpp"

#include <cmath>
#include <cstddef>
#include <cstring>

namespace neon {
namespace detail {
/// a + sign * (b * c) per lane, one rounding; `sign` is +1 or -1 (negating b * c is exact).
template <typename V>
[[gnu::always_inline]] inline V fused_lanes(V a, V b, V c, float sign) {
  constexpr size_t N = sizeof(V) / sizeof(float);
  float la[N], lb[N], lc[N];
  std::memcpy(la, &a, sizeof(V));
  std::memcpy(lb, &b, sizeof(V));
  std::memcpy(lc, &c, sizeof(V));
  for (size_t i = 0; i < N; ++i)
    la[i] = std::fma(sign * lb[i], lc[i], la[i]);
  V r;
  std::memcpy(&r, la, sizeof(V));
  return r;
}
}  // namespace detail

// clang-format off
/// @brief Fused a + (b * c), one rounding.
[[gnu::always_inline]] inline float32x2_t multiply_add_fused(float32x2_t a, float32x2_t b, float32x2_t c) { return detail::fused_lanes(a, b, c, 1.0f); }
/// @brief Fused a - (b * c), one rounding.
[[gnu::always_inline]] inline float32x2_t multiply_subtract_fused(float32x2_t a, float32x2_t b, float32x2_t c) { return detail::fused_lanes(a, b, c, -1.0f); }
/// @brief Fused a + (b * c), one rounding.
[[gnu::always_inline]] inline float32x4_t multiply_add_fused(float32x4_t a, float32x4_t b, float32x4_t c) { return detail::fused_lanes(a, b, c, 1.0f); }
/// @brief Fused a - (b * c), one rounding.
[[gnu::always_inline]] inline float32x4_t multiply_subtract_fused(float32x4_t a, float32x4_t b, float32x4_t c) { return detail::fused_lanes(a, b, c, -1.0f); }
/// @brief Fused a + (b * c), by a scalar one rounding.
[[gnu::always_inline]] inline float32x2_t multiply_add_fused(float32x2_t a, float32x2_t b, float32_t c) { return multiply_add_fused(a, b, vdup_n_f32(c)); }
/// @brief Fused a - (b * c), by a scalar one rounding.
[[gnu::always_inline]] inline float32x2_t multiply_subtract_fused(float32x2_t a, float32x2_t b, float32_t c) { return multiply_subtract_fused(a, b, vdup_n_f32(c)); }
/// @brief Fused a + (b * c), by a scalar one rounding.
[[gnu::always_inline]] inline float32x4_t multiply_add_fused(float32x4_t a, float32x4_t b, float32_t c) { return multiply_add_fused(a, b, vdupq_n_f32(c)); }
/// @brief Fused a - (b * c), by a scalar one rounding.
[[gnu::always_inline]] inline float32x4_t multiply_subtract_fused(float32x4_t a, float32x4_t b, float32_t c) { return multiply_subtract_fused(a, b, vdupq_n_f32(c)); }
// clang-format on
}  // namespace neon
