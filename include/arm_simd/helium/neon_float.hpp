#pragma once
#include "arm_simd/shared/vfpv4_float.hpp"

#ifdef __cplusplus

#define nce [[gnu::always_inline]] inline

namespace helium {
// clang-format off
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float16x8_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float32x4_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float16x8_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float32x4_t a);
template <typename T> nce T convert_round_toward_positive_infinity(float16x8_t a);
template <typename T> nce T convert_round_toward_positive_infinity(float32x4_t a);
template <typename T> nce T convert_round_toward_negative_infinity(float16x8_t a);
template <typename T> nce T convert_round_toward_negative_infinity(float32x4_t a);
template <typename T> nce T convert(int16x8_t a);
template <typename T> nce T convert(uint16x8_t a);
template <typename T> nce T convert(float16x8_t a);
template <typename T> nce T reinterpret(int8x16_t a);
template <typename T> nce T reinterpret(int16x8_t a);
template <typename T> nce T reinterpret(int32x4_t a);
template <typename T> nce T reinterpret(uint8x16_t a);
template <typename T> nce T reinterpret(uint16x8_t a);
template <typename T> nce T reinterpret(uint32x4_t a);
template <typename T> nce T reinterpret(int64x2_t a);
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_f16_u8(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int8x16_t a) { return vreinterpretq_f16_s8(a); }
template <> [[gnu::always_inline]] nce float16x8_t convert(uint16x8_t a) { return vcvtq_f16_u16(a); }
template <int n>[[gnu::always_inline]] nce float16x8_t convert(uint16x8_t a) { return vcvtq_n_f16_u16(a, n); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint16x8_t a) { return vreinterpretq_f16_u16(a); }
template <> [[gnu::always_inline]] nce float16x8_t convert(int16x8_t a) { return vcvtq_f16_s16(a); }
template <int n>[[gnu::always_inline]] nce float16x8_t convert(int16x8_t a) { return vcvtq_n_f16_s16(a, n); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int16x8_t a) { return vreinterpretq_f16_s16(a); }
template <int n>[[gnu::always_inline]] nce float32x4_t convert(int32x4_t a) { return vcvtq_n_f32_s32(a, n); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int32x4_t a) { return vreinterpretq_f16_s32(a); }
template <int n>[[gnu::always_inline]] nce float32x4_t convert(uint32x4_t a) { return vcvtq_n_f32_u32(a, n); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_f16_u32(a); }
[[gnu::always_inline]] nce float16x8_t reverse_32bit(float16x8_t a) { return vrev32q_f16(a); }
[[gnu::always_inline]] nce float16x8_t reverse_64bit(float16x8_t a) { return vrev64q_f16(a); }
[[gnu::always_inline]] nce float16x8_t min(float16x8_t a, float16x8_t b) { return vminnmq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t max(float16x8_t a, float16x8_t b) { return vmaxnmq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t subtract_abs(float16x8_t a, float16x8_t b) { return vabdq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t abs(float16x8_t a) { return vabsq_f16(a); }
[[gnu::always_inline]] nce float16x8_t add(float16x8_t a, float16x8_t b) { return vaddq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t a, float16x8_t b) { return vmulq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t subtract(float16x8_t a, float16x8_t b) { return vsubq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t bitwise_clear(float16x8_t a, float16x8_t b) { return vbicq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t a, float16_t b) { return vmulq_n_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t negate(float16x8_t a) { return vnegq_f16(a); }
[[gnu::always_inline]] nce float16x8_t bitwise_and(float16x8_t a, float16x8_t b) { return vandq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t bitwise_xor(float16x8_t a, float16x8_t b) { return veorq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t complex_add_rotate_90(float16x8_t a, float16x8_t b) { return vcaddq_rot90_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t complex_add_rotate_270(float16x8_t a, float16x8_t b) { return vcaddq_rot270_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_90(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_rot90_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_180(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_rot180_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_270(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_rot270_f16(a, b, c); }
template <> [[gnu::always_inline]] nce int16x8_t convert_round_to_nearest_with_ties_away_from_zero(float16x8_t a) { return vcvtaq_s16_f16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t convert_round_to_nearest_with_ties_away_from_zero(float16x8_t a) { return vcvtaq_u16_f16(a); }
template <> [[gnu::always_inline]] nce int16x8_t convert_round_to_nearest_with_ties_to_even(float16x8_t a) { return vcvtnq_s16_f16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t convert_round_to_nearest_with_ties_to_even(float16x8_t a) { return vcvtnq_u16_f16(a); }
template <> [[gnu::always_inline]] nce int16x8_t convert_round_toward_positive_infinity(float16x8_t a) { return vcvtpq_s16_f16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t convert_round_toward_positive_infinity(float16x8_t a) { return vcvtpq_u16_f16(a); }
template <> [[gnu::always_inline]] nce int16x8_t convert_round_toward_negative_infinity(float16x8_t a) { return vcvtmq_s16_f16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t convert_round_toward_negative_infinity(float16x8_t a) { return vcvtmq_u16_f16(a); }
template <> [[gnu::always_inline]] nce int16x8_t convert(float16x8_t a) { return vcvtq_s16_f16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t convert(float16x8_t a) { return vcvtq_u16_f16(a); }
template <int n>[[gnu::always_inline]] nce int16x8_t convert(float16x8_t a) { return vcvtq_n_s16_f16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t convert(float16x8_t a) { return vcvtq_n_u16_f16(a, n); }
[[gnu::always_inline]] nce float32x4_t min(float32x4_t a, float32x4_t b) { return vminnmq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t max(float32x4_t a, float32x4_t b) { return vmaxnmq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t round(float32x4_t a) { return vrndq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_to_nearest_with_ties_to_even(float32x4_t a) { return vrndnq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_toward_negative_infinity(float32x4_t a) { return vrndmq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_toward_positive_infinity(float32x4_t a) { return vrndpq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_to_nearest_with_ties_away_from_zero(float32x4_t a) { return vrndaq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_inexact(float32x4_t a) { return vrndxq_f32(a); }
[[gnu::always_inline]] nce float32x4_t bitwise_clear(float32x4_t a, float32x4_t b) { return vbicq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t bitwise_and(float32x4_t a, float32x4_t b) { return vandq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t bitwise_xor(float32x4_t a, float32x4_t b) { return veorq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t complex_add_rotate_90(float32x4_t a, float32x4_t b) { return vcaddq_rot90_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t complex_add_rotate_270(float32x4_t a, float32x4_t b) { return vcaddq_rot270_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add(float32x4_t a, float32x4_t b, float32x4_t c) { return vcmlaq_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_90(float32x4_t a, float32x4_t b, float32x4_t c) { return vcmlaq_rot90_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_180(float32x4_t a, float32x4_t b, float32x4_t c) { return vcmlaq_rot180_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_270(float32x4_t a, float32x4_t b, float32x4_t c) { return vcmlaq_rot270_f32(a, b, c); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_to_nearest_with_ties_away_from_zero(float32x4_t a) { return vcvtaq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_to_nearest_with_ties_away_from_zero(float32x4_t a) { return vcvtaq_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_to_nearest_with_ties_to_even(float32x4_t a) { return vcvtnq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_to_nearest_with_ties_to_even(float32x4_t a) { return vcvtnq_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_toward_positive_infinity(float32x4_t a) { return vcvtpq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_toward_positive_infinity(float32x4_t a) { return vcvtpq_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_toward_negative_infinity(float32x4_t a) { return vcvtmq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_toward_negative_infinity(float32x4_t a) { return vcvtmq_u32_f32(a); }
template <int n>[[gnu::always_inline]] nce int32x4_t convert(float32x4_t a) { return vcvtq_n_s32_f32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t convert(float32x4_t a) { return vcvtq_n_u32_f32(a, n); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(float32x4_t a) { return vreinterpretq_f16_f32(a); }
[[gnu::always_inline]] nce float16x8_t duplicate(float16_t a) { return vdupq_n_f16(a); }
[[gnu::always_inline]] nce float32x4_t duplicate(float32_t a) { return vdupq_n_f32(a); }
[[gnu::always_inline]] inline float16x8_t load1(float16_t const *ptr) { return vld1q_f16(ptr); }
[[gnu::always_inline]] inline float32x4_t load1(float32_t const *ptr) { return vld1q_f32(ptr); }
[[gnu::always_inline]] inline void store1(float16_t *ptr, float16x8_t val) { return vst1q_f16(ptr, val); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int64x2_t a) { return vreinterpretq_f16_s64(a); }
// clang-format on
}
#endif
#undef nce
