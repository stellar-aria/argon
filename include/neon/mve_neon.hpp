#pragma once
#ifdef __ARM_NEON
#include <arm_neon.h>
#elifdef __ARM_MVE
#include <arm_mve.h>
#endif


#ifdef __cplusplus
#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

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
template <typename T> nce T convert(int32x4_t a);
template <typename T> nce T convert(uint32x4_t a);
template <typename T> nce T convert(float16x8_t a);
template <typename T> nce T convert(float32x4_t a);
template <typename T> nce T reinterpret(int8x16_t a);
template <typename T> nce T reinterpret(int16x8_t a);
template <typename T> nce T reinterpret(int32x4_t a);
template <typename T> nce T reinterpret(float32x4_t a);
template <typename T> nce T reinterpret(uint8x16_t a);
template <typename T> nce T reinterpret(uint16x8_t a);
template <typename T> nce T reinterpret(uint32x4_t a);
template <typename T> nce T reinterpret(uint64x2_t a);
template <typename T> nce T reinterpret(int64x2_t a);
template <typename T> nce T reinterpret(float16x8_t a);
[[gnu::always_inline]] nce uint8x16_t reverse_16bit(uint8x16_t a) { return vrev16q_u8(a); }
[[gnu::always_inline]] nce uint8x16_t reverse_32bit(uint8x16_t a) { return vrev32q_u8(a); }
[[gnu::always_inline]] nce uint8x16_t reverse_64bit(uint8x16_t a) { return vrev64q_u8(a); }
template <int idx>[[gnu::always_inline]] nce uint8_t get(uint8x16_t a) { return vgetq_lane_u8(a, idx); }
[[gnu::always_inline]] nce uint8x16_t min(uint8x16_t a, uint8x16_t b) { return vminq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t max(uint8x16_t a, uint8x16_t b) { return vmaxq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_abs(uint8x16_t a, uint8x16_t b) { return vabdq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add(uint8x16_t a, uint8x16_t b) { return vaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_halve(uint8x16_t a, uint8x16_t b) { return vhaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_halve_round(uint8x16_t a, uint8x16_t b) { return vrhaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_saturate(uint8x16_t a, uint8x16_t b) { return vqaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t multiply(uint8x16_t a, uint8x16_t b) { return vmulq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract(uint8x16_t a, uint8x16_t b) { return vsubq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_high(uint8x16_t a, uint8x16_t b) { return vhsubq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_saturate(uint8x16_t a, uint8x16_t b) { return vqsubq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t multiply(uint8x16_t a, uint8_t b) { return vmulq_n_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t count_leading_zero_bits(uint8x16_t a) { return vclzq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t bitwise_clear(uint8x16_t a, uint8x16_t b) { return vbicq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t bitwise_and(uint8x16_t a, uint8x16_t b) { return vandq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t bitwise_xor(uint8x16_t a, uint8x16_t b) { return veorq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t bitwise_not(uint8x16_t a) { return vmvnq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t bitwise_or_not(uint8x16_t a, uint8x16_t b) { return vornq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t bitwise_or(uint8x16_t a, uint8x16_t b) { return vorrq_u8(a, b); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint8x16_t a) { return vreinterpretq_s8_u8(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_s16_u8(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint8x16_t a) { return vreinterpretq_s32_u8(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint8x16_t a) { return vreinterpretq_f32_u8(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_u16_u8(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(uint8x16_t a) { return vreinterpretq_u32_u8(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(uint8x16_t a) { return vreinterpretq_u64_u8(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint8x16_t a) { return vreinterpretq_s64_u8(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_f16_u8(a); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_round(uint8x16_t a) { return vrshrq_n_u8(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right(uint8x16_t a) { return vshrq_n_u8(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_insert(uint8x16_t a, uint8x16_t b) { return vsriq_n_u8(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_left_insert(uint8x16_t a, uint8x16_t b) { return vsliq_n_u8(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round_saturate(uint8x16_t a, int8x16_t b) { return vqrshlq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left_saturate(uint8x16_t a, int8x16_t b) { return vqshlq_u8(a, b); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_left_saturate(uint8x16_t a) { return vqshlq_n_u8(a, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round(uint8x16_t a, int8x16_t b) { return vrshlq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t a, int8x16_t b) { return vshlq_u8(a, b); }
[[gnu::always_inline]] nce int8x16_t reverse_16bit(int8x16_t a) { return vrev16q_s8(a); }
[[gnu::always_inline]] nce int8x16_t reverse_32bit(int8x16_t a) { return vrev32q_s8(a); }
[[gnu::always_inline]] nce int8x16_t reverse_64bit(int8x16_t a) { return vrev64q_s8(a); }
template <int idx>[[gnu::always_inline]] nce int8_t get(int8x16_t a) { return vgetq_lane_s8(a, idx); }
[[gnu::always_inline]] nce int8x16_t min(int8x16_t a, int8x16_t b) { return vminq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t max(int8x16_t a, int8x16_t b) { return vmaxq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_abs(int8x16_t a, int8x16_t b) { return vabdq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t abs(int8x16_t a) { return vabsq_s8(a); }
[[gnu::always_inline]] nce int8x16_t abs_saturate(int8x16_t a) { return vqabsq_s8(a); }
[[gnu::always_inline]] nce int8x16_t add(int8x16_t a, int8x16_t b) { return vaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_halve(int8x16_t a, int8x16_t b) { return vhaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_halve_round(int8x16_t a, int8x16_t b) { return vrhaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_saturate(int8x16_t a, int8x16_t b) { return vqaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply(int8x16_t a, int8x16_t b) { return vmulq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract(int8x16_t a, int8x16_t b) { return vsubq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_high(int8x16_t a, int8x16_t b) { return vhsubq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_saturate(int8x16_t a, int8x16_t b) { return vqsubq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply(int8x16_t a, int8_t b) { return vmulq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t count_leading_sign_bits(int8x16_t a) { return vclsq_s8(a); }
[[gnu::always_inline]] nce int8x16_t count_leading_zero_bits(int8x16_t a) { return vclzq_s8(a); }
[[gnu::always_inline]] nce int8x16_t bitwise_clear(int8x16_t a, int8x16_t b) { return vbicq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t negate(int8x16_t a) { return vnegq_s8(a); }
[[gnu::always_inline]] nce int8x16_t negate_saturate(int8x16_t a) { return vqnegq_s8(a); }
[[gnu::always_inline]] nce int8x16_t bitwise_and(int8x16_t a, int8x16_t b) { return vandq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t bitwise_xor(int8x16_t a, int8x16_t b) { return veorq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t bitwise_not(int8x16_t a) { return vmvnq_s8(a); }
[[gnu::always_inline]] nce int8x16_t bitwise_or_not(int8x16_t a, int8x16_t b) { return vornq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t bitwise_or(int8x16_t a, int8x16_t b) { return vorrq_s8(a, b); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(int8x16_t a) { return vreinterpretq_s16_s8(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(int8x16_t a) { return vreinterpretq_s32_s8(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int8x16_t a) { return vreinterpretq_f32_s8(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int8x16_t a) { return vreinterpretq_u8_s8(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int8x16_t a) { return vreinterpretq_u16_s8(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int8x16_t a) { return vreinterpretq_u32_s8(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int8x16_t a) { return vreinterpretq_u64_s8(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(int8x16_t a) { return vreinterpretq_s64_s8(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int8x16_t a) { return vreinterpretq_f16_s8(a); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_right_round(int8x16_t a) { return vrshrq_n_s8(a, imm); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_right(int8x16_t a) { return vshrq_n_s8(a, imm); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_right_insert(int8x16_t a, int8x16_t b) { return vsriq_n_s8(a, b, imm); }
[[gnu::always_inline]] nce int8x16_t shift_left_round_saturate(int8x16_t a, int8x16_t b) { return vqrshlq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left_saturate(int8x16_t a, int8x16_t b) { return vqshlq_s8(a, b); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_left_saturate(int8x16_t a) { return vqshlq_n_s8(a, imm); }
[[gnu::always_inline]] nce int8x16_t shift_left_round(int8x16_t a, int8x16_t b) { return vrshlq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t a, int8x16_t b) { return vshlq_s8(a, b); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_left_insert(int8x16_t a, int8x16_t b) { return vsliq_n_s8(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t reverse_32bit(uint16x8_t a) { return vrev32q_u16(a); }
[[gnu::always_inline]] nce uint16x8_t reverse_64bit(uint16x8_t a) { return vrev64q_u16(a); }
template <int idx>[[gnu::always_inline]] nce uint16_t get(uint16x8_t a) { return vgetq_lane_u16(a, idx); }
[[gnu::always_inline]] nce uint16x8_t min(uint16x8_t a, uint16x8_t b) { return vminq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t max(uint16x8_t a, uint16x8_t b) { return vmaxq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_abs(uint16x8_t a, uint16x8_t b) { return vabdq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add(uint16x8_t a, uint16x8_t b) { return vaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_halve(uint16x8_t a, uint16x8_t b) { return vhaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_halve_round(uint16x8_t a, uint16x8_t b) { return vrhaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_saturate(uint16x8_t a, uint16x8_t b) { return vqaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t a, uint16x8_t b) { return vmulq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract(uint16x8_t a, uint16x8_t b) { return vsubq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_high(uint16x8_t a, uint16x8_t b) { return vhsubq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_saturate(uint16x8_t a, uint16x8_t b) { return vqsubq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t a, uint16_t b) { return vmulq_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t count_leading_zero_bits(uint16x8_t a) { return vclzq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t bitwise_clear(uint16x8_t a, uint16x8_t b) { return vbicq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t bitwise_and(uint16x8_t a, uint16x8_t b) { return vandq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t bitwise_xor(uint16x8_t a, uint16x8_t b) { return veorq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t bitwise_not(uint16x8_t a) { return vmvnq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t bitwise_or_not(uint16x8_t a, uint16x8_t b) { return vornq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t bitwise_or(uint16x8_t a, uint16x8_t b) { return vorrq_u16(a, b); }
template <> [[gnu::always_inline]] nce float16x8_t convert(uint16x8_t a) { return vcvtq_f16_u16(a); }
template <int imm6>[[gnu::always_inline]] nce float16x8_t convert(uint16x8_t a) { return vcvtq_n_f16_u16(a, imm6); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint16x8_t a) { return vreinterpretq_s8_u16(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint16x8_t a) { return vreinterpretq_s16_u16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint16x8_t a) { return vreinterpretq_s32_u16(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint16x8_t a) { return vreinterpretq_f32_u16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(uint16x8_t a) { return vreinterpretq_u8_u16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(uint16x8_t a) { return vreinterpretq_u32_u16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(uint16x8_t a) { return vreinterpretq_u64_u16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint16x8_t a) { return vreinterpretq_s64_u16(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint16x8_t a) { return vreinterpretq_f16_u16(a); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_round(uint16x8_t a) { return vrshrq_n_u16(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right(uint16x8_t a) { return vshrq_n_u16(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_insert(uint16x8_t a, uint16x8_t b) { return vsriq_n_u16(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round_saturate(uint16x8_t a, int16x8_t b) { return vqrshlq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t shift_left_saturate(uint16x8_t a, int16x8_t b) { return vqshlq_u16(a, b); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_left_saturate(uint16x8_t a) { return vqshlq_n_u16(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_left_insert(uint16x8_t a, uint16x8_t b) { return vsliq_n_u16(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round(uint16x8_t a, int16x8_t b) { return vrshlq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t a, int16x8_t b) { return vshlq_u16(a, b); }
[[gnu::always_inline]] nce int16x8_t reverse_32bit(int16x8_t a) { return vrev32q_s16(a); }
[[gnu::always_inline]] nce int16x8_t reverse_64bit(int16x8_t a) { return vrev64q_s16(a); }
template <int idx>[[gnu::always_inline]] nce int16_t get(int16x8_t a) { return vgetq_lane_s16(a, idx); }
[[gnu::always_inline]] nce int16x8_t min(int16x8_t a, int16x8_t b) { return vminq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t max(int16x8_t a, int16x8_t b) { return vmaxq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_abs(int16x8_t a, int16x8_t b) { return vabdq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t abs(int16x8_t a) { return vabsq_s16(a); }
[[gnu::always_inline]] nce int16x8_t abs_saturate(int16x8_t a) { return vqabsq_s16(a); }
[[gnu::always_inline]] nce int16x8_t add(int16x8_t a, int16x8_t b) { return vaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add_halve(int16x8_t a, int16x8_t b) { return vhaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add_halve_round(int16x8_t a, int16x8_t b) { return vrhaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add_saturate(int16x8_t a, int16x8_t b) { return vqaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t a, int16x8_t b) { return vmulq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high(int16x8_t a, int16x8_t b) { return vqdmulhq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high(int16x8_t a, int16x8_t b) { return vqrdmulhq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract(int16x8_t a, int16x8_t b) { return vsubq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_high(int16x8_t a, int16x8_t b) { return vhsubq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_saturate(int16x8_t a, int16x8_t b) { return vqsubq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t a, int16_t b) { return vmulq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high(int16x8_t a, int16_t b) { return vqdmulhq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high(int16x8_t a, int16_t b) { return vqrdmulhq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t count_leading_sign_bits(int16x8_t a) { return vclsq_s16(a); }
[[gnu::always_inline]] nce int16x8_t count_leading_zero_bits(int16x8_t a) { return vclzq_s16(a); }
[[gnu::always_inline]] nce int16x8_t bitwise_clear(int16x8_t a, int16x8_t b) { return vbicq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t negate(int16x8_t a) { return vnegq_s16(a); }
[[gnu::always_inline]] nce int16x8_t negate_saturate(int16x8_t a) { return vqnegq_s16(a); }
[[gnu::always_inline]] nce int16x8_t bitwise_and(int16x8_t a, int16x8_t b) { return vandq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t bitwise_xor(int16x8_t a, int16x8_t b) { return veorq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t bitwise_not(int16x8_t a) { return vmvnq_s16(a); }
[[gnu::always_inline]] nce int16x8_t bitwise_or_not(int16x8_t a, int16x8_t b) { return vornq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t bitwise_or(int16x8_t a, int16x8_t b) { return vorrq_s16(a, b); }
template <> [[gnu::always_inline]] nce float16x8_t convert(int16x8_t a) { return vcvtq_f16_s16(a); }
template <int imm6>[[gnu::always_inline]] nce float16x8_t convert(int16x8_t a) { return vcvtq_n_f16_s16(a, imm6); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(int16x8_t a) { return vreinterpretq_s8_s16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(int16x8_t a) { return vreinterpretq_s32_s16(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int16x8_t a) { return vreinterpretq_f32_s16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int16x8_t a) { return vreinterpretq_u8_s16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int16x8_t a) { return vreinterpretq_u16_s16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int16x8_t a) { return vreinterpretq_u32_s16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int16x8_t a) { return vreinterpretq_u64_s16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(int16x8_t a) { return vreinterpretq_s64_s16(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int16x8_t a) { return vreinterpretq_f16_s16(a); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_right_round(int16x8_t a) { return vrshrq_n_s16(a, imm); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_right(int16x8_t a) { return vshrq_n_s16(a, imm); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_right_insert(int16x8_t a, int16x8_t b) { return vsriq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce int16x8_t shift_left_round_saturate(int16x8_t a, int16x8_t b) { return vqrshlq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left_saturate(int16x8_t a, int16x8_t b) { return vqshlq_s16(a, b); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_left_saturate(int16x8_t a) { return vqshlq_n_s16(a, imm); }
[[gnu::always_inline]] nce int16x8_t shift_left_round(int16x8_t a, int16x8_t b) { return vrshlq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t a, int16x8_t b) { return vshlq_s16(a, b); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_left_insert(int16x8_t a, int16x8_t b) { return vsliq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce int32x4_t reverse_64bit(int32x4_t a) { return vrev64q_s32(a); }
template <int idx>[[gnu::always_inline]] nce int32_t get(int32x4_t a) { return vgetq_lane_s32(a, idx); }
[[gnu::always_inline]] nce int32x4_t min(int32x4_t a, int32x4_t b) { return vminq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t max(int32x4_t a, int32x4_t b) { return vmaxq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_abs(int32x4_t a, int32x4_t b) { return vabdq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t abs(int32x4_t a) { return vabsq_s32(a); }
[[gnu::always_inline]] nce int32x4_t abs_saturate(int32x4_t a) { return vqabsq_s32(a); }
[[gnu::always_inline]] nce int32x4_t add(int32x4_t a, int32x4_t b) { return vaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_halve(int32x4_t a, int32x4_t b) { return vhaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_halve_round(int32x4_t a, int32x4_t b) { return vrhaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_saturate(int32x4_t a, int32x4_t b) { return vqaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t a, int32x4_t b) { return vmulq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high(int32x4_t a, int32x4_t b) { return vqdmulhq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high(int32x4_t a, int32x4_t b) { return vqrdmulhq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract(int32x4_t a, int32x4_t b) { return vsubq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_high(int32x4_t a, int32x4_t b) { return vhsubq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_saturate(int32x4_t a, int32x4_t b) { return vqsubq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t a, int32_t b) { return vmulq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high(int32x4_t a, int32_t b) { return vqdmulhq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high(int32x4_t a, int32_t b) { return vqrdmulhq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t count_leading_sign_bits(int32x4_t a) { return vclsq_s32(a); }
[[gnu::always_inline]] nce int32x4_t count_leading_zero_bits(int32x4_t a) { return vclzq_s32(a); }
[[gnu::always_inline]] nce int32x4_t bitwise_clear(int32x4_t a, int32x4_t b) { return vbicq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t negate(int32x4_t a) { return vnegq_s32(a); }
[[gnu::always_inline]] nce int32x4_t negate_saturate(int32x4_t a) { return vqnegq_s32(a); }
[[gnu::always_inline]] nce int32x4_t bitwise_and(int32x4_t a, int32x4_t b) { return vandq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t bitwise_xor(int32x4_t a, int32x4_t b) { return veorq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t bitwise_not(int32x4_t a) { return vmvnq_s32(a); }
[[gnu::always_inline]] nce int32x4_t bitwise_or_not(int32x4_t a, int32x4_t b) { return vornq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t bitwise_or(int32x4_t a, int32x4_t b) { return vorrq_s32(a, b); }
template <> [[gnu::always_inline]] nce float32x4_t convert(int32x4_t a) { return vcvtq_f32_s32(a); }
template <int imm6>[[gnu::always_inline]] nce float32x4_t convert(int32x4_t a) { return vcvtq_n_f32_s32(a, imm6); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(int32x4_t a) { return vreinterpretq_s8_s32(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(int32x4_t a) { return vreinterpretq_s16_s32(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int32x4_t a) { return vreinterpretq_f32_s32(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int32x4_t a) { return vreinterpretq_u8_s32(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int32x4_t a) { return vreinterpretq_u16_s32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int32x4_t a) { return vreinterpretq_u32_s32(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int32x4_t a) { return vreinterpretq_u64_s32(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(int32x4_t a) { return vreinterpretq_s64_s32(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int32x4_t a) { return vreinterpretq_f16_s32(a); }
template <int imm>[[gnu::always_inline]] nce int32x4_t shift_right_round(int32x4_t a) { return vrshrq_n_s32(a, imm); }
template <int imm>[[gnu::always_inline]] nce int32x4_t shift_right(int32x4_t a) { return vshrq_n_s32(a, imm); }
template <int imm>[[gnu::always_inline]] nce int32x4_t shift_right_insert(int32x4_t a, int32x4_t b) { return vsriq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce int32x4_t shift_left_round_saturate(int32x4_t a, int32x4_t b) { return vqrshlq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left_saturate(int32x4_t a, int32x4_t b) { return vqshlq_s32(a, b); }
template <int imm>[[gnu::always_inline]] nce int32x4_t shift_left_saturate(int32x4_t a) { return vqshlq_n_s32(a, imm); }
[[gnu::always_inline]] nce int32x4_t shift_left_round(int32x4_t a, int32x4_t b) { return vrshlq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t a, int32x4_t b) { return vshlq_s32(a, b); }
template <int imm>[[gnu::always_inline]] nce int32x4_t shift_left_insert(int32x4_t a, int32x4_t b) { return vsliq_n_s32(a, b, imm); }
template <int idx>[[gnu::always_inline]] nce uint64_t get(uint64x2_t a) { return vgetq_lane_u64(a, idx); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint64x2_t a) { return vreinterpretq_s8_u64(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_s16_u64(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint64x2_t a) { return vreinterpretq_s32_u64(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint64x2_t a) { return vreinterpretq_f32_u64(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(uint64x2_t a) { return vreinterpretq_u8_u64(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_u16_u64(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(uint64x2_t a) { return vreinterpretq_u32_u64(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint64x2_t a) { return vreinterpretq_s64_u64(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_f16_u64(a); }
[[gnu::always_inline]] nce uint32x4_t reverse_64bit(uint32x4_t a) { return vrev64q_u32(a); }
template <int idx>[[gnu::always_inline]] nce uint32_t get(uint32x4_t a) { return vgetq_lane_u32(a, idx); }
[[gnu::always_inline]] nce uint32x4_t min(uint32x4_t a, uint32x4_t b) { return vminq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t max(uint32x4_t a, uint32x4_t b) { return vmaxq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_abs(uint32x4_t a, uint32x4_t b) { return vabdq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add(uint32x4_t a, uint32x4_t b) { return vaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_halve(uint32x4_t a, uint32x4_t b) { return vhaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_halve_round(uint32x4_t a, uint32x4_t b) { return vrhaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_saturate(uint32x4_t a, uint32x4_t b) { return vqaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t a, uint32x4_t b) { return vmulq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract(uint32x4_t a, uint32x4_t b) { return vsubq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_high(uint32x4_t a, uint32x4_t b) { return vhsubq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_saturate(uint32x4_t a, uint32x4_t b) { return vqsubq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t a, uint32_t b) { return vmulq_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t count_leading_zero_bits(uint32x4_t a) { return vclzq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t bitwise_clear(uint32x4_t a, uint32x4_t b) { return vbicq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t bitwise_and(uint32x4_t a, uint32x4_t b) { return vandq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t bitwise_xor(uint32x4_t a, uint32x4_t b) { return veorq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t bitwise_not(uint32x4_t a) { return vmvnq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t bitwise_or(uint32x4_t a, uint32x4_t b) { return vorrq_u32(a, b); }
template <> [[gnu::always_inline]] nce float32x4_t convert(uint32x4_t a) { return vcvtq_f32_u32(a); }
template <int imm6>[[gnu::always_inline]] nce float32x4_t convert(uint32x4_t a) { return vcvtq_n_f32_u32(a, imm6); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint32x4_t a) { return vreinterpretq_s8_u32(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_s16_u32(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint32x4_t a) { return vreinterpretq_s32_u32(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint32x4_t a) { return vreinterpretq_f32_u32(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(uint32x4_t a) { return vreinterpretq_u8_u32(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_u16_u32(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(uint32x4_t a) { return vreinterpretq_u64_u32(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint32x4_t a) { return vreinterpretq_s64_u32(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_f16_u32(a); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t shift_right_round(uint32x4_t a) { return vrshrq_n_u32(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t shift_right(uint32x4_t a) { return vshrq_n_u32(a, imm); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round_saturate(uint32x4_t a, int32x4_t b) { return vqrshlq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left_saturate(uint32x4_t a, int32x4_t b) { return vqshlq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round(uint32x4_t a, int32x4_t b) { return vrshlq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t a, int32x4_t b) { return vshlq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t bitwise_or_not(uint32x4_t a, uint32x4_t b) { return vornq_u32(a, b); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t shift_right_insert(uint32x4_t a, uint32x4_t b) { return vsriq_n_u32(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t shift_left_saturate(uint32x4_t a) { return vqshlq_n_u32(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t shift_left_insert(uint32x4_t a, uint32x4_t b) { return vsliq_n_u32(a, b, imm); }
[[gnu::always_inline]] nce float16x8_t reverse_32bit(float16x8_t a) { return vrev32q_f16(a); }
[[gnu::always_inline]] nce float16x8_t reverse_64bit(float16x8_t a) { return vrev64q_f16(a); }
template <int idx>[[gnu::always_inline]] nce float16_t get(float16x8_t a) { return vgetq_lane_f16(a, idx); }
[[gnu::always_inline]] nce float16x8_t min(float16x8_t a, float16x8_t b) { return vminnmq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t max(float16x8_t a, float16x8_t b) { return vmaxnmq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t subtract_abs(float16x8_t a, float16x8_t b) { return vabdq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t abs(float16x8_t a) { return vabsq_f16(a); }
[[gnu::always_inline]] nce float16x8_t add(float16x8_t a, float16x8_t b) { return vaddq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t a, float16x8_t b) { return vmulq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t subtract(float16x8_t a, float16x8_t b) { return vsubq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t bitwise_clear(float16x8_t a, float16x8_t b) { return vbicq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t negate(float16x8_t a) { return vnegq_f16(a); }
[[gnu::always_inline]] nce float16x8_t bitwise_and(float16x8_t a, float16x8_t b) { return vandq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t bitwise_xor(float16x8_t a, float16x8_t b) { return veorq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t complex_add_rotate_90(float16x8_t a, float16x8_t b) { return vcaddq_rot90_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t complex_add_rotate_270(float16x8_t a, float16x8_t b) { return vcaddq_rot270_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_90(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_rot90_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_180(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_rot180_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_270(float16x8_t a, float16x8_t b, float16x8_t c) { return vcmlaq_rot270_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t a, float16_t b) { return vmulq_n_f16(a, b); }
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
template <int imm6>[[gnu::always_inline]] nce int16x8_t convert(float16x8_t a) { return vcvtq_n_s16_f16(a, imm6); }
template <int imm6>[[gnu::always_inline]] nce uint16x8_t convert(float16x8_t a) { return vcvtq_n_u16_f16(a, imm6); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(float16x8_t a) { return vreinterpretq_s8_f16(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(float16x8_t a) { return vreinterpretq_s16_f16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(float16x8_t a) { return vreinterpretq_s32_f16(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(float16x8_t a) { return vreinterpretq_f32_f16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(float16x8_t a) { return vreinterpretq_u8_f16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(float16x8_t a) { return vreinterpretq_u16_f16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(float16x8_t a) { return vreinterpretq_u32_f16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(float16x8_t a) { return vreinterpretq_u64_f16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(float16x8_t a) { return vreinterpretq_s64_f16(a); }
[[gnu::always_inline]] nce float32x4_t reverse_64bit(float32x4_t a) { return vrev64q_f32(a); }
template <int idx>[[gnu::always_inline]] nce float32_t get(float32x4_t a) { return vgetq_lane_f32(a, idx); }
[[gnu::always_inline]] nce float32x4_t min(float32x4_t a, float32x4_t b) { return vminnmq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t max(float32x4_t a, float32x4_t b) { return vmaxnmq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t subtract_abs(float32x4_t a, float32x4_t b) { return vabdq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t abs(float32x4_t a) { return vabsq_f32(a); }
[[gnu::always_inline]] nce float32x4_t add(float32x4_t a, float32x4_t b) { return vaddq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t a, float32x4_t b) { return vmulq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t subtract(float32x4_t a, float32x4_t b) { return vsubq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t a, float32_t b) { return vmulq_n_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t round(float32x4_t a) { return vrndq_f32(a); }
[[gnu::always_inline]] nce float32x4_t Round_to_nearest_with_ties_to_even.(float32x4_t a) { return vrndnq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_toward_negative_infinity(float32x4_t a) { return vrndmq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_toward_positive_infinity(float32x4_t a) { return vrndpq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_to_nearest_with_ties_away_from_zero(float32x4_t a) { return vrndaq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_inexact(float32x4_t a) { return vrndxq_f32(a); }
[[gnu::always_inline]] nce float32x4_t bitwise_clear(float32x4_t a, float32x4_t b) { return vbicq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t negate(float32x4_t a) { return vnegq_f32(a); }
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
template <> [[gnu::always_inline]] nce int32x4_t convert(float32x4_t a) { return vcvtq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert(float32x4_t a) { return vcvtq_u32_f32(a); }
template <int imm6>[[gnu::always_inline]] nce int32x4_t convert(float32x4_t a) { return vcvtq_n_s32_f32(a, imm6); }
template <int imm6>[[gnu::always_inline]] nce uint32x4_t convert(float32x4_t a) { return vcvtq_n_u32_f32(a, imm6); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(float32x4_t a) { return vreinterpretq_s8_f32(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(float32x4_t a) { return vreinterpretq_s16_f32(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(float32x4_t a) { return vreinterpretq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(float32x4_t a) { return vreinterpretq_u8_f32(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(float32x4_t a) { return vreinterpretq_u16_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(float32x4_t a) { return vreinterpretq_u32_f32(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(float32x4_t a) { return vreinterpretq_u64_f32(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(float32x4_t a) { return vreinterpretq_s64_f32(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(float32x4_t a) { return vreinterpretq_f16_f32(a); }
[[gnu::always_inline]] nce int8x16_t duplicate(int8_t a) { return vdupq_n_s8(a); }
[[gnu::always_inline]] nce int16x8_t duplicate(int16_t a) { return vdupq_n_s16(a); }
[[gnu::always_inline]] nce int32x4_t duplicate(int32_t a) { return vdupq_n_s32(a); }
[[gnu::always_inline]] nce uint8x16_t duplicate(uint8_t a) { return vdupq_n_u8(a); }
[[gnu::always_inline]] nce uint16x8_t duplicate(uint16_t a) { return vdupq_n_u16(a); }
[[gnu::always_inline]] nce uint32x4_t duplicate(uint32_t a) { return vdupq_n_u32(a); }
[[gnu::always_inline]] nce float16x8_t duplicate(float16_t a) { return vdupq_n_f16(a); }
[[gnu::always_inline]] nce float32x4_t duplicate(float32_t a) { return vdupq_n_f32(a); }
template <int idx>[[gnu::always_inline]] nce int64_t get(int64x2_t a) { return vgetq_lane_s64(a, idx); }
template <int idx>[[gnu::always_inline]] nce float16x8_t set(float16_t a, float16x8_t b) { return vsetq_lane_f16(a, b, idx); }
template <int idx>[[gnu::always_inline]] nce float32x4_t set(float32_t a, float32x4_t b) { return vsetq_lane_f32(a, b, idx); }
template <int idx>[[gnu::always_inline]] nce int8x16_t set(int8_t a, int8x16_t b) { return vsetq_lane_s8(a, b, idx); }
template <int idx>[[gnu::always_inline]] nce int16x8_t set(int16_t a, int16x8_t b) { return vsetq_lane_s16(a, b, idx); }
template <int idx>[[gnu::always_inline]] nce int32x4_t set(int32_t a, int32x4_t b) { return vsetq_lane_s32(a, b, idx); }
template <int idx>[[gnu::always_inline]] nce int64x2_t set(int64_t a, int64x2_t b) { return vsetq_lane_s64(a, b, idx); }
template <int idx>[[gnu::always_inline]] nce uint8x16_t set(uint8_t a, uint8x16_t b) { return vsetq_lane_u8(a, b, idx); }
template <int idx>[[gnu::always_inline]] nce uint16x8_t set(uint16_t a, uint16x8_t b) { return vsetq_lane_u16(a, b, idx); }
template <int idx>[[gnu::always_inline]] nce uint32x4_t set(uint32_t a, uint32x4_t b) { return vsetq_lane_u32(a, b, idx); }
template <int idx>[[gnu::always_inline]] nce uint64x2_t set(uint64_t a, uint64x2_t b) { return vsetq_lane_u64(a, b, idx); }
[[gnu::always_inline]] inline int8x16_t load1(int8_t const *base) { return vld1q_s8(base); }
[[gnu::always_inline]] inline int16x8_t load1(int16_t const *base) { return vld1q_s16(base); }
[[gnu::always_inline]] inline int32x4_t load1(int32_t const *base) { return vld1q_s32(base); }
[[gnu::always_inline]] inline uint8x16_t load1(uint8_t const *base) { return vld1q_u8(base); }
[[gnu::always_inline]] inline uint16x8_t load1(uint16_t const *base) { return vld1q_u16(base); }
[[gnu::always_inline]] inline uint32x4_t load1(uint32_t const *base) { return vld1q_u32(base); }
[[gnu::always_inline]] inline float16x8_t load1(float16_t const *base) { return vld1q_f16(base); }
[[gnu::always_inline]] inline float32x4_t load1(float32_t const *base) { return vld1q_f32(base); }
[[gnu::always_inline]] inline void store1(int8_t *base, int8x16_t value) { return vst1q_s8(base, value); }
[[gnu::always_inline]] inline void store1(int16_t *base, int16x8_t value) { return vst1q_s16(base, value); }
[[gnu::always_inline]] inline void store1(int32_t *base, int32x4_t value) { return vst1q_s32(base, value); }
[[gnu::always_inline]] inline void store1(uint8_t *base, uint8x16_t value) { return vst1q_u8(base, value); }
[[gnu::always_inline]] inline void store1(uint16_t *base, uint16x8_t value) { return vst1q_u16(base, value); }
[[gnu::always_inline]] inline void store1(uint32_t *base, uint32x4_t value) { return vst1q_u32(base, value); }
[[gnu::always_inline]] inline void store1(float16_t *base, float16x8_t value) { return vst1q_f16(base, value); }
[[gnu::always_inline]] inline void store1(float32_t *base, float32x4_t value) { return vst1q_f32(base, value); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(int64x2_t a) { return vreinterpretq_s8_s64(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(int64x2_t a) { return vreinterpretq_s16_s64(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(int64x2_t a) { return vreinterpretq_s32_s64(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int64x2_t a) { return vreinterpretq_f32_s64(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int64x2_t a) { return vreinterpretq_u8_s64(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int64x2_t a) { return vreinterpretq_u16_s64(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int64x2_t a) { return vreinterpretq_u32_s64(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int64x2_t a) { return vreinterpretq_u64_s64(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int64x2_t a) { return vreinterpretq_f16_s64(a); }
// clang-format on
}  // namespace helium
#endif
