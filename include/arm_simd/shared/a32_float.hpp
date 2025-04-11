#pragma once
#include "vfpv4_float.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd mve
#else
#define simd neon
#endif

#ifdef __cplusplus

#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

namespace simd {
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
template <> [[gnu::always_inline]] nce float16x8_t convert(uint16x8_t a) { return vcvtq_f16_u16(a); }
template <int n>[[gnu::always_inline]] nce float16x8_t convert_n(uint16x8_t a) { return vcvtq_n_f16_u16(a, n); }
template <> [[gnu::always_inline]] nce float16x8_t convert(int16x8_t a) { return vcvtq_f16_s16(a); }
template <int n>[[gnu::always_inline]] nce float16x8_t convert_n(int16x8_t a) { return vcvtq_n_f16_s16(a, n); }
[[gnu::always_inline]] nce float16x8_t subtract_absolute(float16x8_t a, float16x8_t b) { return vabdq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t add(float16x8_t a, float16x8_t b) { return vaddq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t a, float16x8_t b) { return vmulq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t subtract(float16x8_t a, float16x8_t b) { return vsubq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t negate(float16x8_t a) { return vnegq_f16(a); }
[[gnu::always_inline]] nce float16x8_t complex_add_rotate_90(float16x8_t a, float16x8_t b) { return vcaddq_rot90_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t complex_add_rotate_270(float16x8_t a, float16x8_t b) { return vcaddq_rot270_f16(a, b); }
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
template <int n>[[gnu::always_inline]] nce int16x8_t convert_n_signed(float16x8_t a) { return vcvtq_n_s16_f16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t convert_n_unsigned(float16x8_t a) { return vcvtq_n_u16_f16(a, n); }
[[gnu::always_inline]] nce float32x4_t min_strict(float32x4_t a, float32x4_t b) { return vminnmq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t max_strict(float32x4_t a, float32x4_t b) { return vmaxnmq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t round(float32x4_t a) { return vrndq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_to_nearest_with_ties_to_even(float32x4_t a) { return vrndnq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_toward_negative_infinity(float32x4_t a) { return vrndmq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_toward_positive_infinity(float32x4_t a) { return vrndpq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_to_nearest_with_ties_away_from_zero(float32x4_t a) { return vrndaq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_inexact(float32x4_t a) { return vrndxq_f32(a); }
[[gnu::always_inline]] nce float32x4_t complex_add_rotate_90(float32x4_t a, float32x4_t b) { return vcaddq_rot90_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t complex_add_rotate_270(float32x4_t a, float32x4_t b) { return vcaddq_rot270_f32(a, b); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_to_nearest_with_ties_away_from_zero(float32x4_t a) { return vcvtaq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_to_nearest_with_ties_away_from_zero(float32x4_t a) { return vcvtaq_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_to_nearest_with_ties_to_even(float32x4_t a) { return vcvtnq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_to_nearest_with_ties_to_even(float32x4_t a) { return vcvtnq_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_toward_positive_infinity(float32x4_t a) { return vcvtpq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_toward_positive_infinity(float32x4_t a) { return vcvtpq_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_toward_negative_infinity(float32x4_t a) { return vcvtmq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_toward_negative_infinity(float32x4_t a) { return vcvtmq_u32_f32(a); }
// clang-format on
}  // namespace simd
#endif
#undef nce
#undef simd
