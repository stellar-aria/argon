#pragma once
#include "arm_simd/shared/a32_float.hpp"

#ifdef __cplusplus

#define nce [[gnu::always_inline]] inline

namespace helium {
// clang-format off
template <int n>[[gnu::always_inline]] nce float32x4_t convert(int32x4_t a) { return vcvtq_n_f32_s32(a, n); }
template <int n>[[gnu::always_inline]] nce float32x4_t convert(uint32x4_t a) { return vcvtq_n_f32_u32(a, n); }
[[gnu::always_inline]] nce float16x8_t reverse_32bit(float16x8_t a) { return vrev32q_f16(a); }
[[gnu::always_inline]] nce float16x8_t reverse_64bit(float16x8_t a) { return vrev64q_f16(a); }
[[gnu::always_inline]] nce float16x8_t min_strict(float16x8_t a, float16x8_t b) { return vminnmq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t max_strict(float16x8_t a, float16x8_t b) { return vmaxnmq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t abs(float16x8_t a) { return vabsq_f16(a); }
[[gnu::always_inline]] nce float16x8_t bitwise_clear(float16x8_t a, float16x8_t b) { return vbicq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t a, float16_t b) { return vmulq_n_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t bitwise_and(float16x8_t a, float16x8_t b) { return vandq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t bitwise_xor(float16x8_t a, float16x8_t b) { return veorq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_90(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_rot90_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_180(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_rot180_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_270(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_rot270_f16(a, b, c); }
[[gnu::always_inline]] nce float32x4_t bitwise_clear(float32x4_t a, float32x4_t b) { return vbicq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t bitwise_and(float32x4_t a, float32x4_t b) { return vandq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t bitwise_xor(float32x4_t a, float32x4_t b) { return veorq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add(float32x4_t a, float32x4_t b, float32x4_t c) { return vcmlaq_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_90(float32x4_t a, float32x4_t b, float32x4_t c) { return vcmlaq_rot90_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_180(float32x4_t a, float32x4_t b, float32x4_t c) { return vcmlaq_rot180_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_270(float32x4_t a, float32x4_t b, float32x4_t c) { return vcmlaq_rot270_f32(a, b, c); }
template <int n>[[gnu::always_inline]] nce int32x4_t convert(float32x4_t a) { return vcvtq_n_s32_f32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t convert(float32x4_t a) { return vcvtq_n_u32_f32(a, n); }
[[gnu::always_inline]] nce float16x8_t duplicate(float16_t a) { return vdupq_n_f16(a); }
[[gnu::always_inline]] nce float32x4_t duplicate(float32_t a) { return vdupq_n_f32(a); }
[[gnu::always_inline]] inline float16x8_t load1(float16_t const *ptr) { return vld1q_f16(ptr); }
[[gnu::always_inline]] inline float32x4_t load1(float32_t const *ptr) { return vld1q_f32(ptr); }
[[gnu::always_inline]] inline void store1(float16_t *ptr, float16x8_t val) { return vst1q_f16(ptr, val); }
// clang-format on
}  // namespace helium
#endif
#undef nce
