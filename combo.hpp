#pragma once
#include <array>
#include <cstddef>
#include <ranges>
#include <span>
#include <type_traits>
#pragma once
#include <array>
#include <type_traits>
#pragma once


#pragma once
#pragma once
#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

#ifdef __cplusplus

#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

namespace simd {
template <typename T> nce T reinterpret(int8x16_t a);
template <typename T> nce T reinterpret(int16x8_t a);
template <typename T> nce T reinterpret(int32x4_t a);
template <typename T> nce T reinterpret(uint8x16_t a);
template <typename T> nce T reinterpret(uint16x8_t a);
template <typename T> nce T reinterpret(uint32x4_t a);
template <typename T> nce T reinterpret(uint64x2_t a);
template <typename T> nce T reinterpret(int64x2_t a);
[[gnu::always_inline]] nce uint8x16_t add(uint8x16_t a, uint8x16_t b) { return vaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_halve(uint8x16_t a, uint8x16_t b) { return vhaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_halve_round(uint8x16_t a, uint8x16_t b) { return vrhaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_saturate(uint8x16_t a, uint8x16_t b) { return vqaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t multiply(uint8x16_t a, uint8x16_t b) { return vmulq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract(uint8x16_t a, uint8x16_t b) { return vsubq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_halve(uint8x16_t a, uint8x16_t b) { return vhsubq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_saturate(uint8x16_t a, uint8x16_t b) { return vqsubq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_absolute(uint8x16_t a, uint8x16_t b) { return vabdq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t max(uint8x16_t a, uint8x16_t b) { return vmaxq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t min(uint8x16_t a, uint8x16_t b) { return vminq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t a, int8x16_t b) { return vshlq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left_saturate(uint8x16_t a, int8x16_t b) { return vqshlq_u8(a, b); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_left_saturate(uint8x16_t a) { return vqshlq_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_left_insert(uint8x16_t a, uint8x16_t b) { return vsliq_n_u8(a, b, n); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round(uint8x16_t a, int8x16_t b) { return vrshlq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round_saturate(uint8x16_t a, int8x16_t b) { return vqrshlq_u8(a, b); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right(uint8x16_t a) { return vshrq_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_round(uint8x16_t a) { return vrshrq_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_insert(uint8x16_t a, uint8x16_t b) { return vsriq_n_u8(a, b, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint8x16_t a) { return vreinterpretq_s8_u8(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_s16_u8(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint8x16_t a) { return vreinterpretq_s32_u8(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_u16_u8(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(uint8x16_t a) { return vreinterpretq_u32_u8(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(uint8x16_t a) { return vreinterpretq_u64_u8(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint8x16_t a) { return vreinterpretq_s64_u8(a); }
[[gnu::always_inline]] nce uint8x16_t bitwise_not(uint8x16_t a) { return vmvnq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t bitwise_and(uint8x16_t a, uint8x16_t b) { return vandq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t bitwise_or(uint8x16_t a, uint8x16_t b) { return vorrq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t bitwise_xor(uint8x16_t a, uint8x16_t b) { return veorq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t bitwise_or_not(uint8x16_t a, uint8x16_t b) { return vornq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t count_leading_zero_bits(uint8x16_t a) { return vclzq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t bitwise_clear(uint8x16_t a, uint8x16_t b) { return vbicq_u8(a, b); }
template <int lane>[[gnu::always_inline]] nce uint8_t get_lane(uint8x16_t v) { return vgetq_lane_u8(v, lane); }
[[gnu::always_inline]] nce uint8x16_t reverse_64bit(uint8x16_t a) { return vrev64q_u8(a); }
[[gnu::always_inline]] nce uint8x16_t reverse_32bit(uint8x16_t a) { return vrev32q_u8(a); }
[[gnu::always_inline]] nce uint8x16_t reverse_16bit(uint8x16_t a) { return vrev16q_u8(a); }
[[gnu::always_inline]] nce int8x16_t add(int8x16_t a, int8x16_t b) { return vaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_halve(int8x16_t a, int8x16_t b) { return vhaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_halve_round(int8x16_t a, int8x16_t b) { return vrhaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_saturate(int8x16_t a, int8x16_t b) { return vqaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply(int8x16_t a, int8x16_t b) { return vmulq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract(int8x16_t a, int8x16_t b) { return vsubq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_halve(int8x16_t a, int8x16_t b) { return vhsubq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_saturate(int8x16_t a, int8x16_t b) { return vqsubq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_absolute(int8x16_t a, int8x16_t b) { return vabdq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t abs(int8x16_t a) { return vabsq_s8(a); }
[[gnu::always_inline]] nce int8x16_t abs_saturate(int8x16_t a) { return vqabsq_s8(a); }
[[gnu::always_inline]] nce int8x16_t max(int8x16_t a, int8x16_t b) { return vmaxq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t min(int8x16_t a, int8x16_t b) { return vminq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t a, int8x16_t b) { return vshlq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left_saturate(int8x16_t a, int8x16_t b) { return vqshlq_s8(a, b); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_left_saturate(int8x16_t a) { return vqshlq_n_s8(a, n); }
[[gnu::always_inline]] nce int8x16_t shift_left_round(int8x16_t a, int8x16_t b) { return vrshlq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left_round_saturate(int8x16_t a, int8x16_t b) { return vqrshlq_s8(a, b); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_left_insert(int8x16_t a, int8x16_t b) { return vsliq_n_s8(a, b, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right(int8x16_t a) { return vshrq_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_round(int8x16_t a) { return vrshrq_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_insert(int8x16_t a, int8x16_t b) { return vsriq_n_s8(a, b, n); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(int8x16_t a) { return vreinterpretq_s16_s8(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(int8x16_t a) { return vreinterpretq_s32_s8(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int8x16_t a) { return vreinterpretq_u8_s8(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int8x16_t a) { return vreinterpretq_u16_s8(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int8x16_t a) { return vreinterpretq_u32_s8(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int8x16_t a) { return vreinterpretq_u64_s8(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(int8x16_t a) { return vreinterpretq_s64_s8(a); }
[[gnu::always_inline]] nce int8x16_t negate(int8x16_t a) { return vnegq_s8(a); }
[[gnu::always_inline]] nce int8x16_t negate_saturate(int8x16_t a) { return vqnegq_s8(a); }
[[gnu::always_inline]] nce int8x16_t bitwise_not(int8x16_t a) { return vmvnq_s8(a); }
[[gnu::always_inline]] nce int8x16_t bitwise_and(int8x16_t a, int8x16_t b) { return vandq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t bitwise_or(int8x16_t a, int8x16_t b) { return vorrq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t bitwise_xor(int8x16_t a, int8x16_t b) { return veorq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t bitwise_or_not(int8x16_t a, int8x16_t b) { return vornq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t count_leading_sign_bits(int8x16_t a) { return vclsq_s8(a); }
[[gnu::always_inline]] nce int8x16_t count_leading_zero_bits(int8x16_t a) { return vclzq_s8(a); }
[[gnu::always_inline]] nce int8x16_t bitwise_clear(int8x16_t a, int8x16_t b) { return vbicq_s8(a, b); }
template <int lane>[[gnu::always_inline]] nce int8_t get_lane(int8x16_t v) { return vgetq_lane_s8(v, lane); }
[[gnu::always_inline]] nce int8x16_t reverse_64bit(int8x16_t a) { return vrev64q_s8(a); }
[[gnu::always_inline]] nce int8x16_t reverse_32bit(int8x16_t a) { return vrev32q_s8(a); }
[[gnu::always_inline]] nce int8x16_t reverse_16bit(int8x16_t a) { return vrev16q_s8(a); }
[[gnu::always_inline]] nce uint16x8_t add(uint16x8_t a, uint16x8_t b) { return vaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_halve(uint16x8_t a, uint16x8_t b) { return vhaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_halve_round(uint16x8_t a, uint16x8_t b) { return vrhaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_saturate(uint16x8_t a, uint16x8_t b) { return vqaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t a, uint16x8_t b) { return vmulq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract(uint16x8_t a, uint16x8_t b) { return vsubq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_halve(uint16x8_t a, uint16x8_t b) { return vhsubq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_saturate(uint16x8_t a, uint16x8_t b) { return vqsubq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_absolute(uint16x8_t a, uint16x8_t b) { return vabdq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t max(uint16x8_t a, uint16x8_t b) { return vmaxq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t min(uint16x8_t a, uint16x8_t b) { return vminq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t shift_left_saturate(uint16x8_t a, int16x8_t b) { return vqshlq_u16(a, b); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_left_saturate(uint16x8_t a) { return vqshlq_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_left_insert(uint16x8_t a, uint16x8_t b) { return vsliq_n_u16(a, b, n); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round(uint16x8_t a, int16x8_t b) { return vrshlq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round_saturate(uint16x8_t a, int16x8_t b) { return vqrshlq_u16(a, b); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right(uint16x8_t a) { return vshrq_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_round(uint16x8_t a) { return vrshrq_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_insert(uint16x8_t a, uint16x8_t b) { return vsriq_n_u16(a, b, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint16x8_t a) { return vreinterpretq_s8_u16(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint16x8_t a) { return vreinterpretq_s16_u16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint16x8_t a) { return vreinterpretq_s32_u16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(uint16x8_t a) { return vreinterpretq_u8_u16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(uint16x8_t a) { return vreinterpretq_u32_u16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(uint16x8_t a) { return vreinterpretq_u64_u16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint16x8_t a) { return vreinterpretq_s64_u16(a); }
[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t a, int16x8_t b) { return vshlq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t bitwise_not(uint16x8_t a) { return vmvnq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t bitwise_and(uint16x8_t a, uint16x8_t b) { return vandq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t bitwise_or(uint16x8_t a, uint16x8_t b) { return vorrq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t bitwise_xor(uint16x8_t a, uint16x8_t b) { return veorq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t bitwise_or_not(uint16x8_t a, uint16x8_t b) { return vornq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t count_leading_zero_bits(uint16x8_t a) { return vclzq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t bitwise_clear(uint16x8_t a, uint16x8_t b) { return vbicq_u16(a, b); }
template <int lane>[[gnu::always_inline]] nce uint16_t get_lane(uint16x8_t v) { return vgetq_lane_u16(v, lane); }
[[gnu::always_inline]] nce uint16x8_t reverse_64bit(uint16x8_t a) { return vrev64q_u16(a); }
[[gnu::always_inline]] nce uint16x8_t reverse_32bit(uint16x8_t a) { return vrev32q_u16(a); }
[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t a, uint16_t b) { return vmulq_n_u16(a, b); }
[[gnu::always_inline]] nce int16x8_t add(int16x8_t a, int16x8_t b) { return vaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add_halve(int16x8_t a, int16x8_t b) { return vhaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add_halve_round(int16x8_t a, int16x8_t b) { return vrhaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add_saturate(int16x8_t a, int16x8_t b) { return vqaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t a, int16x8_t b) { return vmulq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high(int16x8_t a, int16x8_t b) { return vqdmulhq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high(int16x8_t a, int16x8_t b) { return vqrdmulhq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract(int16x8_t a, int16x8_t b) { return vsubq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_halve(int16x8_t a, int16x8_t b) { return vhsubq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_saturate(int16x8_t a, int16x8_t b) { return vqsubq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_absolute(int16x8_t a, int16x8_t b) { return vabdq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high(int16x8_t a, int16_t b) { return vqdmulhq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high(int16x8_t a, int16_t b) { return vqrdmulhq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t abs(int16x8_t a) { return vabsq_s16(a); }
[[gnu::always_inline]] nce int16x8_t abs_saturate(int16x8_t a) { return vqabsq_s16(a); }
[[gnu::always_inline]] nce int16x8_t max(int16x8_t a, int16x8_t b) { return vmaxq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t min(int16x8_t a, int16x8_t b) { return vminq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t a, int16x8_t b) { return vshlq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left_saturate(int16x8_t a, int16x8_t b) { return vqshlq_s16(a, b); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_left_saturate(int16x8_t a) { return vqshlq_n_s16(a, n); }
[[gnu::always_inline]] nce int16x8_t shift_left_round(int16x8_t a, int16x8_t b) { return vrshlq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left_round_saturate(int16x8_t a, int16x8_t b) { return vqrshlq_s16(a, b); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_left_insert(int16x8_t a, int16x8_t b) { return vsliq_n_s16(a, b, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right(int16x8_t a) { return vshrq_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_round(int16x8_t a) { return vrshrq_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_insert(int16x8_t a, int16x8_t b) { return vsriq_n_s16(a, b, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(int16x8_t a) { return vreinterpretq_s8_s16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(int16x8_t a) { return vreinterpretq_s32_s16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int16x8_t a) { return vreinterpretq_u8_s16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int16x8_t a) { return vreinterpretq_u16_s16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int16x8_t a) { return vreinterpretq_u32_s16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int16x8_t a) { return vreinterpretq_u64_s16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(int16x8_t a) { return vreinterpretq_s64_s16(a); }
[[gnu::always_inline]] nce int16x8_t negate(int16x8_t a) { return vnegq_s16(a); }
[[gnu::always_inline]] nce int16x8_t negate_saturate(int16x8_t a) { return vqnegq_s16(a); }
[[gnu::always_inline]] nce int16x8_t bitwise_not(int16x8_t a) { return vmvnq_s16(a); }
[[gnu::always_inline]] nce int16x8_t bitwise_and(int16x8_t a, int16x8_t b) { return vandq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t bitwise_or(int16x8_t a, int16x8_t b) { return vorrq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t bitwise_xor(int16x8_t a, int16x8_t b) { return veorq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t bitwise_or_not(int16x8_t a, int16x8_t b) { return vornq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t count_leading_sign_bits(int16x8_t a) { return vclsq_s16(a); }
[[gnu::always_inline]] nce int16x8_t count_leading_zero_bits(int16x8_t a) { return vclzq_s16(a); }
[[gnu::always_inline]] nce int16x8_t bitwise_clear(int16x8_t a, int16x8_t b) { return vbicq_s16(a, b); }
template <int lane>[[gnu::always_inline]] nce int16_t get_lane(int16x8_t v) { return vgetq_lane_s16(v, lane); }
[[gnu::always_inline]] nce int16x8_t reverse_64bit(int16x8_t a) { return vrev64q_s16(a); }
[[gnu::always_inline]] nce int16x8_t reverse_32bit(int16x8_t a) { return vrev32q_s16(a); }
[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t a, int16_t b) { return vmulq_n_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t add(int32x4_t a, int32x4_t b) { return vaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_halve(int32x4_t a, int32x4_t b) { return vhaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_halve_round(int32x4_t a, int32x4_t b) { return vrhaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_saturate(int32x4_t a, int32x4_t b) { return vqaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t a, int32x4_t b) { return vmulq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high(int32x4_t a, int32x4_t b) { return vqdmulhq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high(int32x4_t a, int32x4_t b) { return vqrdmulhq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract(int32x4_t a, int32x4_t b) { return vsubq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_halve(int32x4_t a, int32x4_t b) { return vhsubq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_saturate(int32x4_t a, int32x4_t b) { return vqsubq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_absolute(int32x4_t a, int32x4_t b) { return vabdq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high(int32x4_t a, int32_t b) { return vqdmulhq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high(int32x4_t a, int32_t b) { return vqrdmulhq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t abs(int32x4_t a) { return vabsq_s32(a); }
[[gnu::always_inline]] nce int32x4_t abs_saturate(int32x4_t a) { return vqabsq_s32(a); }
[[gnu::always_inline]] nce int32x4_t max(int32x4_t a, int32x4_t b) { return vmaxq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t min(int32x4_t a, int32x4_t b) { return vminq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t a, int32x4_t b) { return vshlq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left_saturate(int32x4_t a, int32x4_t b) { return vqshlq_s32(a, b); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_left_saturate(int32x4_t a) { return vqshlq_n_s32(a, n); }
[[gnu::always_inline]] nce int32x4_t shift_left_round(int32x4_t a, int32x4_t b) { return vrshlq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left_round_saturate(int32x4_t a, int32x4_t b) { return vqrshlq_s32(a, b); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_left_insert(int32x4_t a, int32x4_t b) { return vsliq_n_s32(a, b, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right(int32x4_t a) { return vshrq_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_round(int32x4_t a) { return vrshrq_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_insert(int32x4_t a, int32x4_t b) { return vsriq_n_s32(a, b, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(int32x4_t a) { return vreinterpretq_s8_s32(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(int32x4_t a) { return vreinterpretq_s16_s32(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int32x4_t a) { return vreinterpretq_u8_s32(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int32x4_t a) { return vreinterpretq_u16_s32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int32x4_t a) { return vreinterpretq_u32_s32(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int32x4_t a) { return vreinterpretq_u64_s32(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(int32x4_t a) { return vreinterpretq_s64_s32(a); }
[[gnu::always_inline]] nce int32x4_t negate(int32x4_t a) { return vnegq_s32(a); }
[[gnu::always_inline]] nce int32x4_t negate_saturate(int32x4_t a) { return vqnegq_s32(a); }
[[gnu::always_inline]] nce int32x4_t bitwise_not(int32x4_t a) { return vmvnq_s32(a); }
[[gnu::always_inline]] nce int32x4_t bitwise_and(int32x4_t a, int32x4_t b) { return vandq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t bitwise_or(int32x4_t a, int32x4_t b) { return vorrq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t bitwise_xor(int32x4_t a, int32x4_t b) { return veorq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t bitwise_or_not(int32x4_t a, int32x4_t b) { return vornq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t count_leading_sign_bits(int32x4_t a) { return vclsq_s32(a); }
[[gnu::always_inline]] nce int32x4_t count_leading_zero_bits(int32x4_t a) { return vclzq_s32(a); }
[[gnu::always_inline]] nce int32x4_t bitwise_clear(int32x4_t a, int32x4_t b) { return vbicq_s32(a, b); }
template <int lane>[[gnu::always_inline]] nce int32_t get_lane(int32x4_t v) { return vgetq_lane_s32(v, lane); }
[[gnu::always_inline]] nce int32x4_t reverse_64bit(int32x4_t a) { return vrev64q_s32(a); }
[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t a, int32_t b) { return vmulq_n_s32(a, b); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint64x2_t a) { return vreinterpretq_s8_u64(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_s16_u64(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint64x2_t a) { return vreinterpretq_s32_u64(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(uint64x2_t a) { return vreinterpretq_u8_u64(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_u16_u64(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(uint64x2_t a) { return vreinterpretq_u32_u64(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint64x2_t a) { return vreinterpretq_s64_u64(a); }
template <int lane>[[gnu::always_inline]] nce uint64_t get_lane(uint64x2_t v) { return vgetq_lane_u64(v, lane); }
[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t a, int32x4_t b) { return vshlq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add(uint32x4_t a, uint32x4_t b) { return vaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_halve(uint32x4_t a, uint32x4_t b) { return vhaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_halve_round(uint32x4_t a, uint32x4_t b) { return vrhaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_saturate(uint32x4_t a, uint32x4_t b) { return vqaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t a, uint32x4_t b) { return vmulq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract(uint32x4_t a, uint32x4_t b) { return vsubq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_halve(uint32x4_t a, uint32x4_t b) { return vhsubq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_saturate(uint32x4_t a, uint32x4_t b) { return vqsubq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_absolute(uint32x4_t a, uint32x4_t b) { return vabdq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t max(uint32x4_t a, uint32x4_t b) { return vmaxq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t min(uint32x4_t a, uint32x4_t b) { return vminq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left_saturate(uint32x4_t a, int32x4_t b) { return vqshlq_u32(a, b); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_left_saturate(uint32x4_t a) { return vqshlq_n_u32(a, n); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round(uint32x4_t a, int32x4_t b) { return vrshlq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round_saturate(uint32x4_t a, int32x4_t b) { return vqrshlq_u32(a, b); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_left_insert(uint32x4_t a, uint32x4_t b) { return vsliq_n_u32(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right(uint32x4_t a) { return vshrq_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_round(uint32x4_t a) { return vrshrq_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_insert(uint32x4_t a, uint32x4_t b) { return vsriq_n_u32(a, b, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint32x4_t a) { return vreinterpretq_s8_u32(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_s16_u32(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint32x4_t a) { return vreinterpretq_s32_u32(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(uint32x4_t a) { return vreinterpretq_u8_u32(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_u16_u32(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(uint32x4_t a) { return vreinterpretq_u64_u32(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint32x4_t a) { return vreinterpretq_s64_u32(a); }
[[gnu::always_inline]] nce uint32x4_t bitwise_not(uint32x4_t a) { return vmvnq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t bitwise_and(uint32x4_t a, uint32x4_t b) { return vandq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t bitwise_or(uint32x4_t a, uint32x4_t b) { return vorrq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t bitwise_xor(uint32x4_t a, uint32x4_t b) { return veorq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t bitwise_or_not(uint32x4_t a, uint32x4_t b) { return vornq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t count_leading_zero_bits(uint32x4_t a) { return vclzq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t bitwise_clear(uint32x4_t a, uint32x4_t b) { return vbicq_u32(a, b); }
template <int lane>[[gnu::always_inline]] nce uint32_t get_lane(uint32x4_t v) { return vgetq_lane_u32(v, lane); }
[[gnu::always_inline]] nce uint32x4_t reverse_64bit(uint32x4_t a) { return vrev64q_u32(a); }
[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t a, uint32_t b) { return vmulq_n_u32(a, b); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(int64x2_t a) { return vreinterpretq_s8_s64(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(int64x2_t a) { return vreinterpretq_s16_s64(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(int64x2_t a) { return vreinterpretq_s32_s64(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int64x2_t a) { return vreinterpretq_u8_s64(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int64x2_t a) { return vreinterpretq_u16_s64(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int64x2_t a) { return vreinterpretq_u32_s64(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int64x2_t a) { return vreinterpretq_u64_s64(a); }
template <int lane>[[gnu::always_inline]] nce int64_t get_lane(int64x2_t v) { return vgetq_lane_s64(v, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16_t set_lane(uint8_t a, uint8x16_t v) { return vsetq_lane_u8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t set_lane(uint16_t a, uint16x8_t v) { return vsetq_lane_u16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t set_lane(uint32_t a, uint32x4_t v) { return vsetq_lane_u32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t set_lane(uint64_t a, uint64x2_t v) { return vsetq_lane_u64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16_t set_lane(int8_t a, int8x16_t v) { return vsetq_lane_s8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t set_lane(int16_t a, int16x8_t v) { return vsetq_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t set_lane(int32_t a, int32x4_t v) { return vsetq_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t set_lane(int64_t a, int64x2_t v) { return vsetq_lane_s64(a, v, lane); }
[[gnu::always_inline]] inline void store1(int8_t *ptr, int8x16_t val) { return vst1q_s8(ptr, val); }
[[gnu::always_inline]] inline void store1(int16_t *ptr, int16x8_t val) { return vst1q_s16(ptr, val); }
[[gnu::always_inline]] inline void store1(int32_t *ptr, int32x4_t val) { return vst1q_s32(ptr, val); }
[[gnu::always_inline]] inline void store1(uint8_t *ptr, uint8x16_t val) { return vst1q_u8(ptr, val); }
[[gnu::always_inline]] inline void store1(uint16_t *ptr, uint16x8_t val) { return vst1q_u16(ptr, val); }
[[gnu::always_inline]] inline void store1(uint32_t *ptr, uint32x4_t val) { return vst1q_u32(ptr, val); }
}
#endif
#undef nce
#undef simd
#pragma once


#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

#ifdef __cplusplus

namespace simd {
template <typename T> nce T convert(float32x4_t a);
template <typename T> nce T convert(int32x4_t a);
template <typename T> nce T convert(uint32x4_t a);
template <typename T> nce T reinterpret(float32x4_t a);
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint8x16_t a) { return vreinterpretq_f32_u8(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int8x16_t a) { return vreinterpretq_f32_s8(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint16x8_t a) { return vreinterpretq_f32_u16(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int16x8_t a) { return vreinterpretq_f32_s16(a); }
template <> [[gnu::always_inline]] nce float32x4_t convert(int32x4_t a) { return vcvtq_f32_s32(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int32x4_t a) { return vreinterpretq_f32_s32(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint64x2_t a) { return vreinterpretq_f32_u64(a); }
template <> [[gnu::always_inline]] nce float32x4_t convert(uint32x4_t a) { return vcvtq_f32_u32(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint32x4_t a) { return vreinterpretq_f32_u32(a); }
[[gnu::always_inline]] nce float32x4_t add(float32x4_t a, float32x4_t b) { return vaddq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t a, float32x4_t b) { return vmulq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t subtract(float32x4_t a, float32x4_t b) { return vsubq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t subtract_absolute(float32x4_t a, float32x4_t b) { return vabdq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t abs(float32x4_t a) { return vabsq_f32(a); }
template <> [[gnu::always_inline]] nce int32x4_t convert(float32x4_t a) { return vcvtq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert(float32x4_t a) { return vcvtq_u32_f32(a); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(float32x4_t a) { return vreinterpretq_s8_f32(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(float32x4_t a) { return vreinterpretq_s16_f32(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(float32x4_t a) { return vreinterpretq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(float32x4_t a) { return vreinterpretq_u8_f32(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(float32x4_t a) { return vreinterpretq_u16_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(float32x4_t a) { return vreinterpretq_u32_f32(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(float32x4_t a) { return vreinterpretq_u64_f32(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(float32x4_t a) { return vreinterpretq_s64_f32(a); }
[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t a, float32_t b) { return vmulq_n_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t negate(float32x4_t a) { return vnegq_f32(a); }
[[gnu::always_inline]] nce float32x4_t reverse_64bit(float32x4_t a) { return vrev64q_f32(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int64x2_t a) { return vreinterpretq_f32_s64(a); }
template <int lane>[[gnu::always_inline]] nce float32_t get_lane(float32x4_t v) { return vgetq_lane_f32(v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t set_lane(float32_t a, float32x4_t v) { return vsetq_lane_f32(a, v, lane); }
[[gnu::always_inline]] inline void store1(float32_t *ptr, float32x4_t val) { return vst1q_f32(ptr, val); }

}
#endif
#undef nce
#undef simd

#ifdef __cplusplus
#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

namespace neon {

template <typename T> nce T convert(float32x2_t a);
template <typename T> nce T convert(int32x2_t a);
template <typename T> nce T convert(uint32x2_t a);
template <typename T> nce T reinterpret(int8x8_t a);
template <typename T> nce T reinterpret(int16x4_t a);
template <typename T> nce T reinterpret(int32x2_t a);
template <typename T> nce T reinterpret(float32x2_t a);
template <typename T> nce T reinterpret(uint8x8_t a);
template <typename T> nce T reinterpret(uint16x4_t a);
template <typename T> nce T reinterpret(uint32x2_t a);
template <typename T> nce T reinterpret(poly8x8_t a);
template <typename T> nce T reinterpret(poly16x4_t a);
template <typename T> nce T reinterpret(uint64x1_t a);
template <typename T> nce T reinterpret(int64x1_t a);
template <typename T> nce T reinterpret(poly8x16_t a);
template <typename T> nce T reinterpret(poly16x8_t a);
template <typename T> nce T create(uint64_t a);
template <typename T> nce T duplicate(int8_t value);
template <typename T> nce T duplicate(int16_t value);
template <typename T> nce T duplicate(int32_t value);
template <typename T> nce T duplicate(int64_t value);
template <typename T> nce T duplicate(uint8_t value);
template <typename T> nce T duplicate(uint16_t value);
template <typename T> nce T duplicate(uint32_t value);
template <typename T> nce T duplicate(uint64_t value);
template <typename T> nce T duplicate(float32_t value);
template <typename T> nce T duplicate(poly8_t value);
template <typename T> nce T duplicate(poly16_t value);
template <typename T> nce T load1(int8_t const *ptr);
template <typename T> nce T load1(int16_t const *ptr);
template <typename T> nce T load1(int32_t const *ptr);
template <typename T> nce T load1(int64_t const *ptr);
template <typename T> nce T load1(uint8_t const *ptr);
template <typename T> nce T load1(uint16_t const *ptr);
template <typename T> nce T load1(uint32_t const *ptr);
template <typename T> nce T load1(uint64_t const *ptr);
template <typename T> nce T load1(float32_t const *ptr);
template <typename T> nce T load1(poly8_t const *ptr);
template <typename T> nce T load1(poly16_t const *ptr);
template <typename T> nce T load1_duplicate(int8_t const *ptr);
template <typename T> nce T load1_duplicate(int16_t const *ptr);
template <typename T> nce T load1_duplicate(int32_t const *ptr);
template <typename T> nce T load1_duplicate(int64_t const *ptr);
template <typename T> nce T load1_duplicate(uint8_t const *ptr);
template <typename T> nce T load1_duplicate(uint16_t const *ptr);
template <typename T> nce T load1_duplicate(uint32_t const *ptr);
template <typename T> nce T load1_duplicate(uint64_t const *ptr);
template <typename T> nce T load1_duplicate(float32_t const *ptr);
template <typename T> nce T load1_duplicate(poly8_t const *ptr);
template <typename T> nce T load1_duplicate(poly16_t const *ptr);
template <typename T> nce T load2(int8_t const *ptr);
template <typename T> nce T load2(int16_t const *ptr);
template <typename T> nce T load2(int32_t const *ptr);
template <typename T> nce T load2(uint8_t const *ptr);
template <typename T> nce T load2(uint16_t const *ptr);
template <typename T> nce T load2(uint32_t const *ptr);
template <typename T> nce T load2(float32_t const *ptr);
template <typename T> nce T load2(poly8_t const *ptr);
template <typename T> nce T load2(poly16_t const *ptr);
template <typename T> nce T load3(int8_t const *ptr);
template <typename T> nce T load3(int16_t const *ptr);
template <typename T> nce T load3(int32_t const *ptr);
template <typename T> nce T load3(uint8_t const *ptr);
template <typename T> nce T load3(uint16_t const *ptr);
template <typename T> nce T load3(uint32_t const *ptr);
template <typename T> nce T load3(float32_t const *ptr);
template <typename T> nce T load3(poly8_t const *ptr);
template <typename T> nce T load3(poly16_t const *ptr);
template <typename T> nce T load4(int8_t const *ptr);
template <typename T> nce T load4(int16_t const *ptr);
template <typename T> nce T load4(int32_t const *ptr);
template <typename T> nce T load4(uint8_t const *ptr);
template <typename T> nce T load4(uint16_t const *ptr);
template <typename T> nce T load4(uint32_t const *ptr);
template <typename T> nce T load4(float32_t const *ptr);
template <typename T> nce T load4(poly8_t const *ptr);
template <typename T> nce T load4(poly16_t const *ptr);
template <typename T> nce T load2_duplicate(int8_t const *ptr);
template <typename T> nce T load2_duplicate(int16_t const *ptr);
template <typename T> nce T load2_duplicate(int32_t const *ptr);
template <typename T> nce T load2_duplicate(uint8_t const *ptr);
template <typename T> nce T load2_duplicate(uint16_t const *ptr);
template <typename T> nce T load2_duplicate(uint32_t const *ptr);
template <typename T> nce T load2_duplicate(float32_t const *ptr);
template <typename T> nce T load2_duplicate(poly8_t const *ptr);
template <typename T> nce T load2_duplicate(poly16_t const *ptr);
template <typename T> nce T load3_duplicate(int8_t const *ptr);
template <typename T> nce T load3_duplicate(int16_t const *ptr);
template <typename T> nce T load3_duplicate(int32_t const *ptr);
template <typename T> nce T load3_duplicate(uint8_t const *ptr);
template <typename T> nce T load3_duplicate(uint16_t const *ptr);
template <typename T> nce T load3_duplicate(uint32_t const *ptr);
template <typename T> nce T load3_duplicate(float32_t const *ptr);
template <typename T> nce T load3_duplicate(poly8_t const *ptr);
template <typename T> nce T load3_duplicate(poly16_t const *ptr);
template <typename T> nce T load4_duplicate(int8_t const *ptr);
template <typename T> nce T load4_duplicate(int16_t const *ptr);
template <typename T> nce T load4_duplicate(int32_t const *ptr);
template <typename T> nce T load4_duplicate(uint8_t const *ptr);
template <typename T> nce T load4_duplicate(uint16_t const *ptr);
template <typename T> nce T load4_duplicate(uint32_t const *ptr);
template <typename T> nce T load4_duplicate(float32_t const *ptr);
template <typename T> nce T load4_duplicate(poly8_t const *ptr);
template <typename T> nce T load4_duplicate(poly16_t const *ptr);
#if defined(__clang__) || (__GNUC__ > 13)
template <typename T> nce T load1_x2(int8_t const *ptr);
template <typename T> nce T load1_x2(int16_t const *ptr);
template <typename T> nce T load1_x2(int32_t const *ptr);
template <typename T> nce T load1_x2(uint8_t const *ptr);
template <typename T> nce T load1_x2(uint16_t const *ptr);
template <typename T> nce T load1_x2(uint32_t const *ptr);
template <typename T> nce T load1_x2(float32_t const *ptr);
template <typename T> nce T load1_x2(poly8_t const *ptr);
template <typename T> nce T load1_x2(poly16_t const *ptr);
template <typename T> nce T load1_x2(int64_t const *ptr);
template <typename T> nce T load1_x2(uint64_t const *ptr);
template <typename T> nce T load1_x3(int8_t const *ptr);
template <typename T> nce T load1_x3(int16_t const *ptr);
template <typename T> nce T load1_x3(int32_t const *ptr);
template <typename T> nce T load1_x3(uint8_t const *ptr);
template <typename T> nce T load1_x3(uint16_t const *ptr);
template <typename T> nce T load1_x3(uint32_t const *ptr);
template <typename T> nce T load1_x3(float32_t const *ptr);
template <typename T> nce T load1_x3(poly8_t const *ptr);
template <typename T> nce T load1_x3(poly16_t const *ptr);
template <typename T> nce T load1_x3(int64_t const *ptr);
template <typename T> nce T load1_x3(uint64_t const *ptr);
template <typename T> nce T load1_x4(int8_t const *ptr);
template <typename T> nce T load1_x4(int16_t const *ptr);
template <typename T> nce T load1_x4(int32_t const *ptr);
template <typename T> nce T load1_x4(uint8_t const *ptr);
template <typename T> nce T load1_x4(uint16_t const *ptr);
template <typename T> nce T load1_x4(uint32_t const *ptr);
template <typename T> nce T load1_x4(float32_t const *ptr);
template <typename T> nce T load1_x4(poly8_t const *ptr);
template <typename T> nce T load1_x4(poly16_t const *ptr);
template <typename T> nce T load1_x4(int64_t const *ptr);
template <typename T> nce T load1_x4(uint64_t const *ptr);
#endif
template <typename T> nce T load2(int64_t const *ptr);
template <typename T> nce T load2(uint64_t const *ptr);
template <typename T> nce T load3(int64_t const *ptr);
template <typename T> nce T load3(uint64_t const *ptr);
template <typename T> nce T load4(int64_t const *ptr);
template <typename T> nce T load4(uint64_t const *ptr);
template <typename T> nce T load2_duplicate(int64_t const *ptr);
template <typename T> nce T load2_duplicate(uint64_t const *ptr);
template <typename T> nce T load3_duplicate(int64_t const *ptr);
template <typename T> nce T load3_duplicate(uint64_t const *ptr);
template <typename T> nce T load4_duplicate(int64_t const *ptr);
template <typename T> nce T load4_duplicate(uint64_t const *ptr);

inline void store1(int8_t *ptr, int8x8_t val);
inline void store1(int8_t *ptr, int8x16_t val);
inline void store1(int16_t *ptr, int16x4_t val);
inline void store1(int16_t *ptr, int16x8_t val);
inline void store1(int32_t *ptr, int32x2_t val);
inline void store1(int32_t *ptr, int32x4_t val);
inline void store1(int64_t *ptr, int64x1_t val);
inline void store1(int64_t *ptr, int64x2_t val);
inline void store1(uint8_t *ptr, uint8x8_t val);
inline void store1(uint8_t *ptr, uint8x16_t val);
inline void store1(uint16_t *ptr, uint16x4_t val);
inline void store1(uint16_t *ptr, uint16x8_t val);
inline void store1(uint32_t *ptr, uint32x2_t val);
inline void store1(uint32_t *ptr, uint32x4_t val);
inline void store1(uint64_t *ptr, uint64x1_t val);
inline void store1(uint64_t *ptr, uint64x2_t val);
inline void store1(float32_t *ptr, float32x2_t val);
inline void store1(float32_t *ptr, float32x4_t val);
inline void store1(poly8_t *ptr, poly8x8_t val);
inline void store1(poly8_t *ptr, poly8x16_t val);
inline void store1(poly16_t *ptr, poly16x4_t val);
inline void store1(poly16_t *ptr, poly16x8_t val);
inline void store2(int8_t *ptr, int8x8x2_t val);
inline void store2(int16_t *ptr, int16x4x2_t val);
inline void store2(int16_t *ptr, int16x8x2_t val);
inline void store2(int32_t *ptr, int32x2x2_t val);
inline void store2(int32_t *ptr, int32x4x2_t val);
inline void store2(uint8_t *ptr, uint8x8x2_t val);
inline void store2(uint16_t *ptr, uint16x4x2_t val);
inline void store2(uint16_t *ptr, uint16x8x2_t val);
inline void store2(uint32_t *ptr, uint32x2x2_t val);
inline void store2(uint32_t *ptr, uint32x4x2_t val);
inline void store2(float32_t *ptr, float32x2x2_t val);
inline void store2(float32_t *ptr, float32x4x2_t val);
inline void store2(poly8_t *ptr, poly8x8x2_t val);
inline void store2(poly16_t *ptr, poly16x4x2_t val);
inline void store2(poly16_t *ptr, poly16x8x2_t val);
inline void store3(int8_t *ptr, int8x8x3_t val);
inline void store3(int8_t *ptr, int8x16x3_t val);
inline void store3(int16_t *ptr, int16x4x3_t val);
inline void store3(int16_t *ptr, int16x8x3_t val);
inline void store3(int32_t *ptr, int32x2x3_t val);
inline void store3(int32_t *ptr, int32x4x3_t val);
inline void store3(uint8_t *ptr, uint8x8x3_t val);
inline void store3(uint8_t *ptr, uint8x16x3_t val);
inline void store3(uint16_t *ptr, uint16x4x3_t val);
inline void store3(uint16_t *ptr, uint16x8x3_t val);
inline void store3(uint32_t *ptr, uint32x2x3_t val);
inline void store3(uint32_t *ptr, uint32x4x3_t val);
inline void store3(float32_t *ptr, float32x2x3_t val);
inline void store3(float32_t *ptr, float32x4x3_t val);
inline void store3(poly8_t *ptr, poly8x8x3_t val);
inline void store3(poly8_t *ptr, poly8x16x3_t val);
inline void store3(poly16_t *ptr, poly16x4x3_t val);
inline void store3(poly16_t *ptr, poly16x8x3_t val);
inline void store4(int8_t *ptr, int8x8x4_t val);
inline void store4(int16_t *ptr, int16x4x4_t val);
inline void store4(int16_t *ptr, int16x8x4_t val);
inline void store4(int32_t *ptr, int32x2x4_t val);
inline void store4(int32_t *ptr, int32x4x4_t val);
inline void store4(uint8_t *ptr, uint8x8x4_t val);
inline void store4(uint16_t *ptr, uint16x4x4_t val);
inline void store4(uint16_t *ptr, uint16x8x4_t val);
inline void store4(uint32_t *ptr, uint32x2x4_t val);
inline void store4(uint32_t *ptr, uint32x4x4_t val);
inline void store4(float32_t *ptr, float32x2x4_t val);
inline void store4(float32_t *ptr, float32x4x4_t val);
inline void store4(poly8_t *ptr, poly8x8x4_t val);
inline void store4(poly16_t *ptr, poly16x4x4_t val);
inline void store4(poly16_t *ptr, poly16x8x4_t val);
[[gnu::always_inline]] nce uint8x8_t add(uint8x8_t a, uint8x8_t b) { return vadd_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_long(uint8x8_t a, uint8x8_t b) { return vaddl_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t add_halve(uint8x8_t a, uint8x8_t b) { return vhadd_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t add_halve_round(uint8x8_t a, uint8x8_t b) { return vrhadd_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t add_saturate(uint8x8_t a, uint8x8_t b) { return vqadd_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t multiply(uint8x8_t a, uint8x8_t b) { return vmul_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t multiply_add(uint8x8_t a, uint8x8_t b, uint8x8_t c) { return vmla_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x8_t multiply_subtract(uint8x8_t a, uint8x8_t b, uint8x8_t c) { return vmls_u8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t multiply_long(uint8x8_t a, uint8x8_t b) { return vmull_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract(uint8x8_t a, uint8x8_t b) { return vsub_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_long(uint8x8_t a, uint8x8_t b) { return vsubl_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract_halve(uint8x8_t a, uint8x8_t b) { return vhsub_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract_saturate(uint8x8_t a, uint8x8_t b) { return vqsub_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract_absolute(uint8x8_t a, uint8x8_t b) { return vabd_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_absolute_long(uint8x8_t a, uint8x8_t b) { return vabdl_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract_absolute_add(uint8x8_t a, uint8x8_t b, uint8x8_t c) { return vaba_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x8_t max(uint8x8_t a, uint8x8_t b) { return vmax_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t min(uint8x8_t a, uint8x8_t b) { return vmin_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t pairwise_add(uint8x8_t a, uint8x8_t b) { return vpadd_u8(a, b); }
[[gnu::always_inline]] nce uint16x4_t pairwise_add_long(uint8x8_t a) { return vpaddl_u8(a); }
[[gnu::always_inline]] nce uint8x8_t pairwise_max(uint8x8_t a, uint8x8_t b) { return vpmax_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t pairwise_min(uint8x8_t a, uint8x8_t b) { return vpmin_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t equal(uint8x8_t a, uint8x8_t b) { return vceq_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t greater_than_or_equal(uint8x8_t a, uint8x8_t b) { return vcge_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t less_than_or_equal(uint8x8_t a, uint8x8_t b) { return vcle_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t greater_than(uint8x8_t a, uint8x8_t b) { return vcgt_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t less_than(uint8x8_t a, uint8x8_t b) { return vclt_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t compare_test_nonzero(uint8x8_t a, uint8x8_t b) { return vtst_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t shift_left(uint8x8_t a, int8x8_t b) { return vshl_u8(a, b); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_left(uint8x8_t a) { return vshl_n_u8(a, n); }
[[gnu::always_inline]] nce uint8x8_t shift_left_saturate(uint8x8_t a, int8x8_t b) { return vqshl_u8(a, b); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_left_saturate(uint8x8_t a) { return vqshl_n_u8(a, n); }
[[gnu::always_inline]] nce uint8x8_t shift_left_round(uint8x8_t a, int8x8_t b) { return vrshl_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t shift_left_round_saturate(uint8x8_t a, int8x8_t b) { return vqrshl_u8(a, b); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_left_long(uint8x8_t a) { return vshll_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_left_insert(uint8x8_t a, uint8x8_t b) { return vsli_n_u8(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right(uint8x8_t a) { return vshr_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_round(uint8x8_t a) { return vrshr_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_accumulate(uint8x8_t a, uint8x8_t b) { return vsra_n_u8(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_accumulate_round(uint8x8_t a, uint8x8_t b) { return vrsra_n_u8(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_insert(uint8x8_t a, uint8x8_t b) { return vsri_n_u8(a, b, n); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(uint8x8_t a) { return vreinterpret_s8_u8(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(uint8x8_t a) { return vreinterpret_s16_u8(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(uint8x8_t a) { return vreinterpret_s32_u8(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(uint8x8_t a) { return vreinterpret_f32_u8(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(uint8x8_t a) { return vreinterpret_u16_u8(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(uint8x8_t a) { return vreinterpret_u32_u8(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(uint8x8_t a) { return vreinterpret_p8_u8(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(uint8x8_t a) { return vreinterpret_p16_u8(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(uint8x8_t a) { return vreinterpret_u64_u8(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(uint8x8_t a) { return vreinterpret_s64_u8(a); }
[[gnu::always_inline]] nce uint16x8_t move_long(uint8x8_t a) { return vmovl_u8(a); }
[[gnu::always_inline]] nce uint8x8_t bitwise_not(uint8x8_t a) { return vmvn_u8(a); }
[[gnu::always_inline]] nce uint8x8_t bitwise_and(uint8x8_t a, uint8x8_t b) { return vand_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t bitwise_or(uint8x8_t a, uint8x8_t b) { return vorr_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t bitwise_xor(uint8x8_t a, uint8x8_t b) { return veor_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t bitwise_or_not(uint8x8_t a, uint8x8_t b) { return vorn_u8(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce int8x8_t count_leading_sign_bits(uint8x8_t a) { return vcls_u8(a); }
#endif
[[gnu::always_inline]] nce uint8x8_t count_leading_zero_bits(uint8x8_t a) { return vclz_u8(a); }
[[gnu::always_inline]] nce uint8x8_t count_active_bits(uint8x8_t a) { return vcnt_u8(a); }
[[gnu::always_inline]] nce uint8x8_t bitwise_clear(uint8x8_t a, uint8x8_t b) { return vbic_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t bitwise_select(uint8x8_t a, uint8x8_t b, uint8x8_t c) { return vbsl_u8(a, b, c); }
[[gnu::always_inline]] nce int8x8_t bitwise_select(uint8x8_t a, int8x8_t b, int8x8_t c) { return vbsl_s8(a, b, c); }
[[gnu::always_inline]] nce poly8x8_t bitwise_select(uint8x8_t a, poly8x8_t b, poly8x8_t c) { return vbsl_p8(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint8x8_t duplicate_lane(uint8x8_t a) { return vdup_lane_u8(a, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16_t duplicate_lane_quad(uint8x8_t a) { return vdupq_lane_u8(a, lane); }
[[gnu::always_inline]] nce uint8x16_t combine(uint8x8_t low, uint8x8_t high) { return vcombine_u8(low, high); }
template <int lane>[[gnu::always_inline]] nce uint8_t get_lane(uint8x8_t v) { return vget_lane_u8(v, lane); }
template <int n>[[gnu::always_inline]] nce uint8x8_t extract(uint8x8_t a, uint8x8_t b) { return vext_u8(a, b, n); }
[[gnu::always_inline]] nce uint8x8_t reverse_64bit(uint8x8_t a) { return vrev64_u8(a); }
[[gnu::always_inline]] nce uint8x8_t reverse_32bit(uint8x8_t a) { return vrev32_u8(a); }
[[gnu::always_inline]] nce uint8x8_t reverse_16bit(uint8x8_t a) { return vrev16_u8(a); }
[[gnu::always_inline]] nce uint8x8x2_t zip(uint8x8_t a, uint8x8_t b) { return vzip_u8(a, b); }
[[gnu::always_inline]] nce uint8x8x2_t unzip(uint8x8_t a, uint8x8_t b) { return vuzp_u8(a, b); }
[[gnu::always_inline]] nce uint8x8x2_t transpose(uint8x8_t a, uint8x8_t b) { return vtrn_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t table_lookup1(uint8x8_t a, uint8x8_t idx) { return vtbl1_u8(a, idx); }
[[gnu::always_inline]] nce uint8x8_t table_extension1(uint8x8_t a, uint8x8_t b, uint8x8_t idx) { return vtbx1_u8(a, b, idx); }
[[gnu::always_inline]] nce uint8x8_t table_extension2(uint8x8_t a, uint8x8x2_t b, uint8x8_t idx) { return vtbx2_u8(a, b, idx); }
[[gnu::always_inline]] nce uint8x8_t table_extension3(uint8x8_t a, uint8x8x3_t b, uint8x8_t idx) { return vtbx3_u8(a, b, idx); }
[[gnu::always_inline]] nce uint8x8_t table_extension4(uint8x8_t a, uint8x8x4_t b, uint8x8_t idx) { return vtbx4_u8(a, b, idx); }
[[gnu::always_inline]] nce uint8x16_t multiply_add(uint8x16_t a, uint8x16_t b, uint8x16_t c) { return vmlaq_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x16_t multiply_subtract(uint8x16_t a, uint8x16_t b, uint8x16_t c) { return vmlsq_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x16_t subtract_absolute_add(uint8x16_t a, uint8x16_t b, uint8x16_t c) { return vabaq_u8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t pairwise_add_long(uint8x16_t a) { return vpaddlq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t equal(uint8x16_t a, uint8x16_t b) { return vceqq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t greater_than_or_equal(uint8x16_t a, uint8x16_t b) { return vcgeq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t less_than_or_equal(uint8x16_t a, uint8x16_t b) { return vcleq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t greater_than(uint8x16_t a, uint8x16_t b) { return vcgtq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t less_than(uint8x16_t a, uint8x16_t b) { return vcltq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t compare_test_nonzero(uint8x16_t a, uint8x16_t b) { return vtstq_u8(a, b); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t a) { return vshlq_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_accumulate(uint8x16_t a, uint8x16_t b) { return vsraq_n_u8(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_accumulate_round(uint8x16_t a, uint8x16_t b) { return vrsraq_n_u8(a, b, n); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(uint8x16_t a) { return vreinterpretq_p8_u8(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_p16_u8(a); }
#ifdef __clang__
[[gnu::always_inline]] nce int8x16_t count_leading_sign_bits(uint8x16_t a) { return vclsq_u8(a); }
#endif
[[gnu::always_inline]] nce uint8x16_t count_active_bits(uint8x16_t a) { return vcntq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t bitwise_select(uint8x16_t a, uint8x16_t b, uint8x16_t c) { return vbslq_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x8_t get_high(uint8x16_t a) { return vget_high_u8(a); }
[[gnu::always_inline]] nce uint8x8_t get_low(uint8x16_t a) { return vget_low_u8(a); }
template <int n>[[gnu::always_inline]] nce uint8x16_t extract(uint8x16_t a, uint8x16_t b) { return vextq_u8(a, b, n); }
[[gnu::always_inline]] nce uint8x16x2_t zip(uint8x16_t a, uint8x16_t b) { return vzipq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16x2_t unzip(uint8x16_t a, uint8x16_t b) { return vuzpq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16x2_t transpose(uint8x16_t a, uint8x16_t b) { return vtrnq_u8(a, b); }
[[gnu::always_inline]] nce int8x16_t bitwise_select(uint8x16_t a, int8x16_t b, int8x16_t c) { return vbslq_s8(a, b, c); }
[[gnu::always_inline]] nce poly8x16_t bitwise_select(uint8x16_t a, poly8x16_t b, poly8x16_t c) { return vbslq_p8(a, b, c); }
[[gnu::always_inline]] nce int8x8_t add(int8x8_t a, int8x8_t b) { return vadd_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t add_long(int8x8_t a, int8x8_t b) { return vaddl_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t add_halve(int8x8_t a, int8x8_t b) { return vhadd_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t add_halve_round(int8x8_t a, int8x8_t b) { return vrhadd_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t add_saturate(int8x8_t a, int8x8_t b) { return vqadd_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t multiply(int8x8_t a, int8x8_t b) { return vmul_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t multiply_add(int8x8_t a, int8x8_t b, int8x8_t c) { return vmla_s8(a, b, c); }
[[gnu::always_inline]] nce int8x8_t multiply_subtract(int8x8_t a, int8x8_t b, int8x8_t c) { return vmls_s8(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_long(int8x8_t a, int8x8_t b) { return vmull_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract(int8x8_t a, int8x8_t b) { return vsub_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_long(int8x8_t a, int8x8_t b) { return vsubl_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract_halve(int8x8_t a, int8x8_t b) { return vhsub_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract_saturate(int8x8_t a, int8x8_t b) { return vqsub_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract_absolute(int8x8_t a, int8x8_t b) { return vabd_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_absolute_long(int8x8_t a, int8x8_t b) { return vabdl_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract_absolute_add(int8x8_t a, int8x8_t b, int8x8_t c) { return vaba_s8(a, b, c); }
[[gnu::always_inline]] nce int8x8_t absolute(int8x8_t a) { return vabs_s8(a); }
[[gnu::always_inline]] nce int8x8_t absolute_saturate(int8x8_t a) { return vqabs_s8(a); }
[[gnu::always_inline]] nce int8x8_t max(int8x8_t a, int8x8_t b) { return vmax_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t min(int8x8_t a, int8x8_t b) { return vmin_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t pairwise_add(int8x8_t a, int8x8_t b) { return vpadd_s8(a, b); }
[[gnu::always_inline]] nce int16x4_t pairwise_add_long(int8x8_t a) { return vpaddl_s8(a); }
[[gnu::always_inline]] nce int8x8_t pairwise_max(int8x8_t a, int8x8_t b) { return vpmax_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t pairwise_min(int8x8_t a, int8x8_t b) { return vpmin_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t equal(int8x8_t a, int8x8_t b) { return vceq_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t greater_than_or_equal(int8x8_t a, int8x8_t b) { return vcge_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t less_than_or_equal(int8x8_t a, int8x8_t b) { return vcle_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t greater_than(int8x8_t a, int8x8_t b) { return vcgt_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t less_than(int8x8_t a, int8x8_t b) { return vclt_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t compare_test_nonzero(int8x8_t a, int8x8_t b) { return vtst_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t shift_left(int8x8_t a, int8x8_t b) { return vshl_s8(a, b); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_left(int8x8_t a) { return vshl_n_s8(a, n); }
[[gnu::always_inline]] nce int8x8_t shift_left_saturate(int8x8_t a, int8x8_t b) { return vqshl_s8(a, b); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_left_saturate(int8x8_t a) { return vqshl_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_left_unsigned_saturate(int8x8_t a) { return vqshlu_n_s8(a, n); }
[[gnu::always_inline]] nce int8x8_t shift_left_round(int8x8_t a, int8x8_t b) { return vrshl_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t shift_left_round_saturate(int8x8_t a, int8x8_t b) { return vqrshl_s8(a, b); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_left_long(int8x8_t a) { return vshll_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_left_insert(int8x8_t a, int8x8_t b) { return vsli_n_s8(a, b, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right(int8x8_t a) { return vshr_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_round(int8x8_t a) { return vrshr_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_accumulate(int8x8_t a, int8x8_t b) { return vsra_n_s8(a, b, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_accumulate_round(int8x8_t a, int8x8_t b) { return vrsra_n_s8(a, b, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_insert(int8x8_t a, int8x8_t b) { return vsri_n_s8(a, b, n); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(int8x8_t a) { return vreinterpret_s16_s8(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(int8x8_t a) { return vreinterpret_s32_s8(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(int8x8_t a) { return vreinterpret_f32_s8(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(int8x8_t a) { return vreinterpret_u8_s8(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(int8x8_t a) { return vreinterpret_u16_s8(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(int8x8_t a) { return vreinterpret_u32_s8(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(int8x8_t a) { return vreinterpret_p8_s8(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(int8x8_t a) { return vreinterpret_p16_s8(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(int8x8_t a) { return vreinterpret_u64_s8(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(int8x8_t a) { return vreinterpret_s64_s8(a); }
[[gnu::always_inline]] nce int16x8_t move_long(int8x8_t a) { return vmovl_s8(a); }
[[gnu::always_inline]] nce int8x8_t negate(int8x8_t a) { return vneg_s8(a); }
[[gnu::always_inline]] nce int8x8_t negate_saturate(int8x8_t a) { return vqneg_s8(a); }
[[gnu::always_inline]] nce int8x8_t bitwise_not(int8x8_t a) { return vmvn_s8(a); }
[[gnu::always_inline]] nce int8x8_t bitwise_and(int8x8_t a, int8x8_t b) { return vand_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t bitwise_or(int8x8_t a, int8x8_t b) { return vorr_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t bitwise_xor(int8x8_t a, int8x8_t b) { return veor_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t bitwise_or_not(int8x8_t a, int8x8_t b) { return vorn_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t count_leading_sign_bits(int8x8_t a) { return vcls_s8(a); }
[[gnu::always_inline]] nce int8x8_t count_leading_zero_bits(int8x8_t a) { return vclz_s8(a); }
[[gnu::always_inline]] nce int8x8_t count_active_bits(int8x8_t a) { return vcnt_s8(a); }
[[gnu::always_inline]] nce int8x8_t bitwise_clear(int8x8_t a, int8x8_t b) { return vbic_s8(a, b); }
template <int lane>[[gnu::always_inline]] nce int8x8_t duplicate_lane(int8x8_t a) { return vdup_lane_s8(a, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16_t duplicate_lane_quad(int8x8_t a) { return vdupq_lane_s8(a, lane); }
[[gnu::always_inline]] nce int8x16_t combine(int8x8_t low, int8x8_t high) { return vcombine_s8(low, high); }
template <int lane>[[gnu::always_inline]] nce int8_t get_lane(int8x8_t v) { return vget_lane_s8(v, lane); }
template <int n>[[gnu::always_inline]] nce int8x8_t extract(int8x8_t a, int8x8_t b) { return vext_s8(a, b, n); }
[[gnu::always_inline]] nce int8x8_t reverse_64bit(int8x8_t a) { return vrev64_s8(a); }
[[gnu::always_inline]] nce int8x8_t reverse_32bit(int8x8_t a) { return vrev32_s8(a); }
[[gnu::always_inline]] nce int8x8_t reverse_16bit(int8x8_t a) { return vrev16_s8(a); }
[[gnu::always_inline]] nce int8x8x2_t zip(int8x8_t a, int8x8_t b) { return vzip_s8(a, b); }
[[gnu::always_inline]] nce int8x8x2_t unzip(int8x8_t a, int8x8_t b) { return vuzp_s8(a, b); }
[[gnu::always_inline]] nce int8x8x2_t transpose(int8x8_t a, int8x8_t b) { return vtrn_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t table_lookup1(int8x8_t a, int8x8_t idx) { return vtbl1_s8(a, idx); }
[[gnu::always_inline]] nce int8x8_t table_extension1(int8x8_t a, int8x8_t b, int8x8_t idx) { return vtbx1_s8(a, b, idx); }
[[gnu::always_inline]] nce int8x8_t table_extension2(int8x8_t a, int8x8x2_t b, int8x8_t idx) { return vtbx2_s8(a, b, idx); }
[[gnu::always_inline]] nce int8x8_t table_extension3(int8x8_t a, int8x8x3_t b, int8x8_t idx) { return vtbx3_s8(a, b, idx); }
[[gnu::always_inline]] nce int8x8_t table_extension4(int8x8_t a, int8x8x4_t b, int8x8_t idx) { return vtbx4_s8(a, b, idx); }
[[gnu::always_inline]] nce int8x16_t multiply_add(int8x16_t a, int8x16_t b, int8x16_t c) { return vmlaq_s8(a, b, c); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract(int8x16_t a, int8x16_t b, int8x16_t c) { return vmlsq_s8(a, b, c); }
[[gnu::always_inline]] nce int8x16_t subtract_absolute_add(int8x16_t a, int8x16_t b, int8x16_t c) { return vabaq_s8(a, b, c); }
[[gnu::always_inline]] nce int16x8_t pairwise_add_long(int8x16_t a) { return vpaddlq_s8(a); }
[[gnu::always_inline]] nce uint8x16_t equal(int8x16_t a, int8x16_t b) { return vceqq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t greater_than_or_equal(int8x16_t a, int8x16_t b) { return vcgeq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t less_than_or_equal(int8x16_t a, int8x16_t b) { return vcleq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t greater_than(int8x16_t a, int8x16_t b) { return vcgtq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t less_than(int8x16_t a, int8x16_t b) { return vcltq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t compare_test_nonzero(int8x16_t a, int8x16_t b) { return vtstq_s8(a, b); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t a) { return vshlq_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_left_unsigned_saturate(int8x16_t a) { return vqshluq_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_accumulate(int8x16_t a, int8x16_t b) { return vsraq_n_s8(a, b, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_accumulate_round(int8x16_t a, int8x16_t b) { return vrsraq_n_s8(a, b, n); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(int8x16_t a) { return vreinterpretq_p8_s8(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(int8x16_t a) { return vreinterpretq_p16_s8(a); }
[[gnu::always_inline]] nce int8x16_t count_active_bits(int8x16_t a) { return vcntq_s8(a); }
[[gnu::always_inline]] nce int8x8_t get_high(int8x16_t a) { return vget_high_s8(a); }
[[gnu::always_inline]] nce int8x8_t get_low(int8x16_t a) { return vget_low_s8(a); }
template <int n>[[gnu::always_inline]] nce int8x16_t extract(int8x16_t a, int8x16_t b) { return vextq_s8(a, b, n); }
[[gnu::always_inline]] nce int8x16x2_t zip(int8x16_t a, int8x16_t b) { return vzipq_s8(a, b); }
[[gnu::always_inline]] nce int8x16x2_t unzip(int8x16_t a, int8x16_t b) { return vuzpq_s8(a, b); }
[[gnu::always_inline]] nce int8x16x2_t transpose(int8x16_t a, int8x16_t b) { return vtrnq_s8(a, b); }
[[gnu::always_inline]] nce uint16x4_t add(uint16x4_t a, uint16x4_t b) { return vadd_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_long(uint16x4_t a, uint16x4_t b) { return vaddl_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t add_halve(uint16x4_t a, uint16x4_t b) { return vhadd_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t add_halve_round(uint16x4_t a, uint16x4_t b) { return vrhadd_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t add_saturate(uint16x4_t a, uint16x4_t b) { return vqadd_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t multiply(uint16x4_t a, uint16x4_t b) { return vmul_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t multiply_add(uint16x4_t a, uint16x4_t b, uint16x4_t c) { return vmla_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t multiply_subtract(uint16x4_t a, uint16x4_t b, uint16x4_t c) { return vmls_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_long(uint16x4_t a, uint16x4_t b) { return vmull_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract(uint16x4_t a, uint16x4_t b) { return vsub_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_long(uint16x4_t a, uint16x4_t b) { return vsubl_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract_halve(uint16x4_t a, uint16x4_t b) { return vhsub_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract_saturate(uint16x4_t a, uint16x4_t b) { return vqsub_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract_absolute(uint16x4_t a, uint16x4_t b) { return vabd_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_absolute_long(uint16x4_t a, uint16x4_t b) { return vabdl_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract_absolute_add(uint16x4_t a, uint16x4_t b, uint16x4_t c) { return vaba_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t max(uint16x4_t a, uint16x4_t b) { return vmax_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t min(uint16x4_t a, uint16x4_t b) { return vmin_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t pairwise_add(uint16x4_t a, uint16x4_t b) { return vpadd_u16(a, b); }
[[gnu::always_inline]] nce uint32x2_t pairwise_add_long(uint16x4_t a) { return vpaddl_u16(a); }
[[gnu::always_inline]] nce uint16x4_t pairwise_add_accumulate_long(uint16x4_t a, uint8x8_t b) { return vpadal_u8(a, b); }
[[gnu::always_inline]] nce uint16x4_t pairwise_max(uint16x4_t a, uint16x4_t b) { return vpmax_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t pairwise_min(uint16x4_t a, uint16x4_t b) { return vpmin_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t equal(uint16x4_t a, uint16x4_t b) { return vceq_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t greater_than_or_equal(uint16x4_t a, uint16x4_t b) { return vcge_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t less_than_or_equal(uint16x4_t a, uint16x4_t b) { return vcle_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t greater_than(uint16x4_t a, uint16x4_t b) { return vcgt_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t less_than(uint16x4_t a, uint16x4_t b) { return vclt_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t compare_test_nonzero(uint16x4_t a, uint16x4_t b) { return vtst_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t shift_left(uint16x4_t a, int16x4_t b) { return vshl_u16(a, b); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_left(uint16x4_t a) { return vshl_n_u16(a, n); }
[[gnu::always_inline]] nce uint16x4_t shift_left_saturate(uint16x4_t a, int16x4_t b) { return vqshl_u16(a, b); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_left_saturate(uint16x4_t a) { return vqshl_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_left_long(uint16x4_t a) { return vshll_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_left_insert(uint16x4_t a, uint16x4_t b) { return vsli_n_u16(a, b, n); }
[[gnu::always_inline]] nce uint16x4_t shift_left_round(uint16x4_t a, int16x4_t b) { return vrshl_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t shift_left_round_saturate(uint16x4_t a, int16x4_t b) { return vqrshl_u16(a, b); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right(uint16x4_t a) { return vshr_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_round(uint16x4_t a) { return vrshr_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_accumulate(uint16x4_t a, uint16x4_t b) { return vsra_n_u16(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_accumulate_round(uint16x4_t a, uint16x4_t b) { return vrsra_n_u16(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_insert(uint16x4_t a, uint16x4_t b) { return vsri_n_u16(a, b, n); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(uint16x4_t a) { return vreinterpret_s8_u16(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(uint16x4_t a) { return vreinterpret_s16_u16(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(uint16x4_t a) { return vreinterpret_s32_u16(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(uint16x4_t a) { return vreinterpret_f32_u16(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(uint16x4_t a) { return vreinterpret_u8_u16(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(uint16x4_t a) { return vreinterpret_u32_u16(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(uint16x4_t a) { return vreinterpret_p8_u16(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(uint16x4_t a) { return vreinterpret_p16_u16(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(uint16x4_t a) { return vreinterpret_u64_u16(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(uint16x4_t a) { return vreinterpret_s64_u16(a); }
[[gnu::always_inline]] nce uint32x4_t move_long(uint16x4_t a) { return vmovl_u16(a); }
template <int lane> [[gnu::always_inline]] nce uint16x4_t multiply_add_lane(uint16x4_t a, uint16x4_t b, uint16x4_t v) { return vmla_lane_u16(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce uint16x4_t multiply_subtract_lane(uint16x4_t a, uint16x4_t b, uint16x4_t v) { return vmls_lane_u16(a, b, v, lane); }
[[gnu::always_inline]] nce uint16x4_t multiply_add(uint16x4_t a, uint16x4_t b, uint16_t c) { return vmla_n_u16(a, b, c); }
template <int lane> [[gnu::always_inline]] nce uint16x4_t multiply_lane(uint16x4_t a, uint16x4_t v) { return vmul_lane_u16(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce uint32x4_t multiply_long_lane(uint16x4_t a, uint16x4_t v) { return vmull_lane_u16(a, v, lane); }
[[gnu::always_inline]] nce uint16x4_t multiply_subtract(uint16x4_t a, uint16x4_t b, uint16_t c) { return vmls_n_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t bitwise_not(uint16x4_t a) { return vmvn_u16(a); }
[[gnu::always_inline]] nce uint16x4_t bitwise_and(uint16x4_t a, uint16x4_t b) { return vand_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t bitwise_or(uint16x4_t a, uint16x4_t b) { return vorr_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t bitwise_xor(uint16x4_t a, uint16x4_t b) { return veor_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t bitwise_or_not(uint16x4_t a, uint16x4_t b) { return vorn_u16(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce int16x4_t count_leading_sign_bits(uint16x4_t a) { return vcls_u16(a); }
#endif
[[gnu::always_inline]] nce uint16x4_t count_leading_zero_bits(uint16x4_t a) { return vclz_u16(a); }
[[gnu::always_inline]] nce uint16x4_t bitwise_clear(uint16x4_t a, uint16x4_t b) { return vbic_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t bitwise_select(uint16x4_t a, uint16x4_t b, uint16x4_t c) { return vbsl_u16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t duplicate_lane(uint16x4_t a) { return vdup_lane_u16(a, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t duplicate_lane_quad(uint16x4_t a) { return vdupq_lane_u16(a, lane); }
[[gnu::always_inline]] nce uint16x8_t combine(uint16x4_t low, uint16x4_t high) { return vcombine_u16(low, high); }
template <int lane>[[gnu::always_inline]] nce uint16_t get_lane(uint16x4_t v) { return vget_lane_u16(v, lane); }
template <int n>[[gnu::always_inline]] nce uint16x4_t extract(uint16x4_t a, uint16x4_t b) { return vext_u16(a, b, n); }
[[gnu::always_inline]] nce uint16x4_t reverse_64bit(uint16x4_t a) { return vrev64_u16(a); }
[[gnu::always_inline]] nce uint16x4_t reverse_32bit(uint16x4_t a) { return vrev32_u16(a); }
[[gnu::always_inline]] nce uint16x4x2_t zip(uint16x4_t a, uint16x4_t b) { return vzip_u16(a, b); }
[[gnu::always_inline]] nce uint16x4x2_t unzip(uint16x4_t a, uint16x4_t b) { return vuzp_u16(a, b); }
[[gnu::always_inline]] nce uint16x4x2_t transpose(uint16x4_t a, uint16x4_t b) { return vtrn_u16(a, b); }
[[gnu::always_inline]] nce int16x4_t bitwise_select(uint16x4_t a, int16x4_t b, int16x4_t c) { return vbsl_s16(a, b, c); }
[[gnu::always_inline]] nce poly16x4_t bitwise_select(uint16x4_t a, poly16x4_t b, poly16x4_t c) { return vbsl_p16(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t multiply(uint16x4_t a, uint16_t b) { return vmul_n_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_long(uint16x4_t a, uint16_t b) { return vmull_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add(uint16x8_t a, uint8x8_t b) { return vaddw_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply_add_long(uint16x8_t a, uint8x8_t b, uint8x8_t c) { return vmlal_u8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t multiply_subtract_long(uint16x8_t a, uint8x8_t b, uint8x8_t c) { return vmlsl_u8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t subtract(uint16x8_t a, uint8x8_t b) { return vsubw_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_absolute_add(uint16x8_t a, uint8x8_t b, uint8x8_t c) { return vabal_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x8_t add_narrow(uint16x8_t a, uint16x8_t b) { return vaddhn_u16(a, b); }
[[gnu::always_inline]] nce uint8x8_t add_round_narrow(uint16x8_t a, uint16x8_t b) { return vraddhn_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply_add(uint16x8_t a, uint16x8_t b, uint16x8_t c) { return vmlaq_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t multiply_subtract(uint16x8_t a, uint16x8_t b, uint16x8_t c) { return vmlsq_u16(a, b, c); }
[[gnu::always_inline]] nce uint8x8_t subtract_narrow(uint16x8_t a, uint16x8_t b) { return vsubhn_u16(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract_round_narrow(uint16x8_t a, uint16x8_t b) { return vrsubhn_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_absolute_add(uint16x8_t a, uint16x8_t b, uint16x8_t c) { return vabaq_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t pairwise_add_long(uint16x8_t a) { return vpaddlq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t pairwise_add_accumulate_long(uint16x8_t a, uint8x16_t b) { return vpadalq_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t equal(uint16x8_t a, uint16x8_t b) { return vceqq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t greater_than_or_equal(uint16x8_t a, uint16x8_t b) { return vcgeq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t less_than_or_equal(uint16x8_t a, uint16x8_t b) { return vcleq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t greater_than(uint16x8_t a, uint16x8_t b) { return vcgtq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t less_than(uint16x8_t a, uint16x8_t b) { return vcltq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t compare_test_nonzero(uint16x8_t a, uint16x8_t b) { return vtstq_u16(a, b); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_accumulate(uint16x8_t a, uint16x8_t b) { return vsraq_n_u16(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_accumulate_round(uint16x8_t a, uint16x8_t b) { return vrsraq_n_u16(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_narrow(uint16x8_t a) { return vshrn_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_saturate_narrow(uint16x8_t a) { return vqshrn_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_round_saturate_narrow(uint16x8_t a) { return vqrshrn_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_round_narrow(uint16x8_t a) { return vrshrn_n_u16(a, n); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(uint16x8_t a) { return vreinterpretq_p8_u16(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(uint16x8_t a) { return vreinterpretq_p16_u16(a); }
[[gnu::always_inline]] nce uint8x8_t move_narrow(uint16x8_t a) { return vmovn_u16(a); }
[[gnu::always_inline]] nce uint8x8_t move_saturate_narrow(uint16x8_t a) { return vqmovn_u16(a); }
template <int lane> [[gnu::always_inline]] nce uint16x8_t multiply_add_lane(uint16x8_t a, uint16x8_t b, uint16x4_t v) { return vmlaq_lane_u16(a, b, v, lane); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t a) { return vshlq_n_u16(a, n); }
template <int lane> [[gnu::always_inline]] nce uint16x8_t multiply_lane(uint16x8_t a, uint16x4_t v) { return vmulq_lane_u16(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce uint16x8_t multiply_subtract_lane(uint16x8_t a, uint16x8_t b, uint16x4_t v) { return vmlsq_lane_u16(a, b, v, lane); }
[[gnu::always_inline]] nce uint16x8_t multiply_add(uint16x8_t a, uint16x8_t b, uint16_t c) { return vmlaq_n_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t multiply_subtract(uint16x8_t a, uint16x8_t b, uint16_t c) { return vmlsq_n_u16(a, b, c); }
#ifdef __clang__
[[gnu::always_inline]] nce int16x8_t count_leading_sign_bits(uint16x8_t a) { return vclsq_u16(a); }
#endif
[[gnu::always_inline]] nce uint16x8_t bitwise_select(uint16x8_t a, uint16x8_t b, uint16x8_t c) { return vbslq_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t get_high(uint16x8_t a) { return vget_high_u16(a); }
[[gnu::always_inline]] nce uint16x4_t get_low(uint16x8_t a) { return vget_low_u16(a); }
template <int n>[[gnu::always_inline]] nce uint16x8_t extract(uint16x8_t a, uint16x8_t b) { return vextq_u16(a, b, n); }
[[gnu::always_inline]] nce uint16x8x2_t zip(uint16x8_t a, uint16x8_t b) { return vzipq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8x2_t unzip(uint16x8_t a, uint16x8_t b) { return vuzpq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8x2_t transpose(uint16x8_t a, uint16x8_t b) { return vtrnq_u16(a, b); }
[[gnu::always_inline]] nce int16x8_t bitwise_select(uint16x8_t a, int16x8_t b, int16x8_t c) { return vbslq_s16(a, b, c); }
[[gnu::always_inline]] nce poly16x8_t bitwise_select(uint16x8_t a, poly16x8_t b, poly16x8_t c) { return vbslq_p16(a, b, c); }
[[gnu::always_inline]] nce int16x4_t pairwise_add_accumulate_long(int16x4_t a, int8x8_t b) { return vpadal_s8(a, b); }
[[gnu::always_inline]] nce int16x4_t add(int16x4_t a, int16x4_t b) { return vadd_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t add_long(int16x4_t a, int16x4_t b) { return vaddl_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t add_halve(int16x4_t a, int16x4_t b) { return vhadd_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t add_halve_round(int16x4_t a, int16x4_t b) { return vrhadd_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t add_saturate(int16x4_t a, int16x4_t b) { return vqadd_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t multiply(int16x4_t a, int16x4_t b) { return vmul_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t multiply_add(int16x4_t a, int16x4_t b, int16x4_t c) { return vmla_s16(a, b, c); }
[[gnu::always_inline]] nce int16x4_t multiply_subtract(int16x4_t a, int16x4_t b, int16x4_t c) { return vmls_s16(a, b, c); }
[[gnu::always_inline]] nce int16x4_t multiply_double_saturate_high(int16x4_t a, int16x4_t b) { return vqdmulh_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t multiply_double_round_saturate_high(int16x4_t a, int16x4_t b) { return vqrdmulh_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long(int16x4_t a, int16x4_t b) { return vqdmull_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_long(int16x4_t a, int16x4_t b) { return vmull_s16(a, b); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_lane(int16x4_t a, int16x4_t v) { return vqdmull_lane_s16(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce int16x4_t multiply_double_saturate_high_lane(int16x4_t a, int16x4_t v) { return vqdmulh_lane_s16(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce int16x4_t multiply_double_round_saturate_high_lane(int16x4_t a, int16x4_t v) { return vqrdmulh_lane_s16(a, v, lane); }
[[gnu::always_inline]] nce int16x4_t subtract(int16x4_t a, int16x4_t b) { return vsub_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_long(int16x4_t a, int16x4_t b) { return vsubl_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_halve(int16x4_t a, int16x4_t b) { return vhsub_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_saturate(int16x4_t a, int16x4_t b) { return vqsub_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_absolute(int16x4_t a, int16x4_t b) { return vabd_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_absolute_long(int16x4_t a, int16x4_t b) { return vabdl_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_absolute_add(int16x4_t a, int16x4_t b, int16x4_t c) { return vaba_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long(int16x4_t a, int16_t b) { return vqdmull_n_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t multiply_double_saturate_high(int16x4_t a, int16_t b) { return vqdmulh_n_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t multiply_double_round_saturate_high(int16x4_t a, int16_t b) { return vqrdmulh_n_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t absolute(int16x4_t a) { return vabs_s16(a); }
[[gnu::always_inline]] nce int16x4_t absolute_saturate(int16x4_t a) { return vqabs_s16(a); }
[[gnu::always_inline]] nce int16x4_t max(int16x4_t a, int16x4_t b) { return vmax_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t min(int16x4_t a, int16x4_t b) { return vmin_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t pairwise_add(int16x4_t a, int16x4_t b) { return vpadd_s16(a, b); }
[[gnu::always_inline]] nce int32x2_t pairwise_add_long(int16x4_t a) { return vpaddl_s16(a); }
[[gnu::always_inline]] nce int16x4_t pairwise_max(int16x4_t a, int16x4_t b) { return vpmax_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t pairwise_min(int16x4_t a, int16x4_t b) { return vpmin_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t equal(int16x4_t a, int16x4_t b) { return vceq_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t greater_than_or_equal(int16x4_t a, int16x4_t b) { return vcge_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t less_than_or_equal(int16x4_t a, int16x4_t b) { return vcle_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t greater_than(int16x4_t a, int16x4_t b) { return vcgt_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t less_than(int16x4_t a, int16x4_t b) { return vclt_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t compare_test_nonzero(int16x4_t a, int16x4_t b) { return vtst_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t shift_left(int16x4_t a, int16x4_t b) { return vshl_s16(a, b); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_left(int16x4_t a) { return vshl_n_s16(a, n); }
[[gnu::always_inline]] nce int16x4_t shift_left_saturate(int16x4_t a, int16x4_t b) { return vqshl_s16(a, b); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_left_saturate(int16x4_t a) { return vqshl_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_left_unsigned_saturate(int16x4_t a) { return vqshlu_n_s16(a, n); }
[[gnu::always_inline]] nce int16x4_t shift_left_round(int16x4_t a, int16x4_t b) { return vrshl_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t shift_left_round_saturate(int16x4_t a, int16x4_t b) { return vqrshl_s16(a, b); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_left_long(int16x4_t a) { return vshll_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_left_insert(int16x4_t a, int16x4_t b) { return vsli_n_s16(a, b, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right(int16x4_t a) { return vshr_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_round(int16x4_t a) { return vrshr_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_accumulate(int16x4_t a, int16x4_t b) { return vsra_n_s16(a, b, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_accumulate_round(int16x4_t a, int16x4_t b) { return vrsra_n_s16(a, b, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_insert(int16x4_t a, int16x4_t b) { return vsri_n_s16(a, b, n); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(int16x4_t a) { return vreinterpret_s8_s16(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(int16x4_t a) { return vreinterpret_s32_s16(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(int16x4_t a) { return vreinterpret_f32_s16(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(int16x4_t a) { return vreinterpret_u8_s16(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(int16x4_t a) { return vreinterpret_u16_s16(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(int16x4_t a) { return vreinterpret_u32_s16(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(int16x4_t a) { return vreinterpret_p8_s16(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(int16x4_t a) { return vreinterpret_p16_s16(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(int16x4_t a) { return vreinterpret_u64_s16(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(int16x4_t a) { return vreinterpret_s64_s16(a); }
[[gnu::always_inline]] nce int32x4_t move_long(int16x4_t a) { return vmovl_s16(a); }
template <int lane> [[gnu::always_inline]] nce int16x4_t multiply_add_lane(int16x4_t a, int16x4_t b, int16x4_t v) { return vmla_lane_s16(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce int16x4_t multiply_subtract_lane(int16x4_t a, int16x4_t b, int16x4_t v) { return vmls_lane_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int16x4_t multiply_add(int16x4_t a, int16x4_t b, int16_t c) { return vmla_n_s16(a, b, c); }
template <int lane> [[gnu::always_inline]] nce int16x4_t multiply_lane(int16x4_t a, int16x4_t v) { return vmul_lane_s16(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_long_lane(int16x4_t a, int16x4_t v) { return vmull_lane_s16(a, v, lane); }
[[gnu::always_inline]] nce int16x4_t multiply_subtract(int16x4_t a, int16x4_t b, int16_t c) { return vmls_n_s16(a, b, c); }
[[gnu::always_inline]] nce int16x4_t negate(int16x4_t a) { return vneg_s16(a); }
[[gnu::always_inline]] nce int16x4_t negate_saturate(int16x4_t a) { return vqneg_s16(a); }
[[gnu::always_inline]] nce int16x4_t bitwise_not(int16x4_t a) { return vmvn_s16(a); }
[[gnu::always_inline]] nce int16x4_t bitwise_and(int16x4_t a, int16x4_t b) { return vand_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t bitwise_or(int16x4_t a, int16x4_t b) { return vorr_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t bitwise_xor(int16x4_t a, int16x4_t b) { return veor_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t bitwise_or_not(int16x4_t a, int16x4_t b) { return vorn_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t count_leading_sign_bits(int16x4_t a) { return vcls_s16(a); }
[[gnu::always_inline]] nce int16x4_t count_leading_zero_bits(int16x4_t a) { return vclz_s16(a); }
[[gnu::always_inline]] nce int16x4_t bitwise_clear(int16x4_t a, int16x4_t b) { return vbic_s16(a, b); }
template <int lane>[[gnu::always_inline]] nce int16x4_t duplicate_lane(int16x4_t a) { return vdup_lane_s16(a, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t duplicate_lane_quad(int16x4_t a) { return vdupq_lane_s16(a, lane); }
[[gnu::always_inline]] nce int16x8_t combine(int16x4_t low, int16x4_t high) { return vcombine_s16(low, high); }
template <int lane>[[gnu::always_inline]] nce int16_t get_lane(int16x4_t v) { return vget_lane_s16(v, lane); }
template <int n>[[gnu::always_inline]] nce int16x4_t extract(int16x4_t a, int16x4_t b) { return vext_s16(a, b, n); }
[[gnu::always_inline]] nce int16x4_t reverse_64bit(int16x4_t a) { return vrev64_s16(a); }
[[gnu::always_inline]] nce int16x4_t reverse_32bit(int16x4_t a) { return vrev32_s16(a); }
[[gnu::always_inline]] nce int16x4x2_t zip(int16x4_t a, int16x4_t b) { return vzip_s16(a, b); }
[[gnu::always_inline]] nce int16x4x2_t unzip(int16x4_t a, int16x4_t b) { return vuzp_s16(a, b); }
[[gnu::always_inline]] nce int16x4x2_t transpose(int16x4_t a, int16x4_t b) { return vtrn_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t multiply(int16x4_t a, int16_t b) { return vmul_n_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_long(int16x4_t a, int16_t b) { return vmull_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add(int16x8_t a, int8x8_t b) { return vaddw_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_add_long(int16x8_t a, int8x8_t b, int8x8_t c) { return vmlal_s8(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_long(int16x8_t a, int8x8_t b, int8x8_t c) { return vmlsl_s8(a, b, c); }
[[gnu::always_inline]] nce int16x8_t subtract(int16x8_t a, int8x8_t b) { return vsubw_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_absolute_add(int16x8_t a, int8x8_t b, int8x8_t c) { return vabal_s8(a, b, c); }
template <int lane> [[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high_lane(int16x8_t a, int16x4_t v) { return vqdmulhq_lane_s16(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high_lane(int16x8_t a, int16x4_t v) { return vqrdmulhq_lane_s16(a, v, lane); }
[[gnu::always_inline]] nce int8x8_t add_narrow(int16x8_t a, int16x8_t b) { return vaddhn_s16(a, b); }
[[gnu::always_inline]] nce int8x8_t add_round_narrow(int16x8_t a, int16x8_t b) { return vraddhn_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_add(int16x8_t a, int16x8_t b, int16x8_t c) { return vmlaq_s16(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract(int16x8_t a, int16x8_t b, int16x8_t c) { return vmlsq_s16(a, b, c); }
[[gnu::always_inline]] nce int8x8_t subtract_narrow(int16x8_t a, int16x8_t b) { return vsubhn_s16(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract_round_narrow(int16x8_t a, int16x8_t b) { return vrsubhn_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_absolute_add(int16x8_t a, int16x8_t b, int16x8_t c) { return vabaq_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t pairwise_add_long(int16x8_t a) { return vpaddlq_s16(a); }
[[gnu::always_inline]] nce int16x8_t pairwise_add_accumulate_long(int16x8_t a, int8x16_t b) { return vpadalq_s8(a, b); }
[[gnu::always_inline]] nce uint16x8_t equal(int16x8_t a, int16x8_t b) { return vceqq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t greater_than_or_equal(int16x8_t a, int16x8_t b) { return vcgeq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t less_than_or_equal(int16x8_t a, int16x8_t b) { return vcleq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t greater_than(int16x8_t a, int16x8_t b) { return vcgtq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t less_than(int16x8_t a, int16x8_t b) { return vcltq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t compare_test_nonzero(int16x8_t a, int16x8_t b) { return vtstq_s16(a, b); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t a) { return vshlq_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_left_unsigned_saturate(int16x8_t a) { return vqshluq_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_accumulate(int16x8_t a, int16x8_t b) { return vsraq_n_s16(a, b, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_accumulate_round(int16x8_t a, int16x8_t b) { return vrsraq_n_s16(a, b, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_narrow(int16x8_t a) { return vshrn_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_saturate_narrow_unsigned(int16x8_t a) { return vqshrun_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_saturate_narrow(int16x8_t a) { return vqshrn_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_round_saturate_narrow_unsigned(int16x8_t a) { return vqrshrun_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_round_saturate_narrow(int16x8_t a) { return vqrshrn_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_round_narrow(int16x8_t a) { return vrshrn_n_s16(a, n); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(int16x8_t a) { return vreinterpretq_p8_s16(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(int16x8_t a) { return vreinterpretq_p16_s16(a); }
[[gnu::always_inline]] nce int8x8_t move_narrow(int16x8_t a) { return vmovn_s16(a); }
[[gnu::always_inline]] nce int8x8_t move_saturate_narrow(int16x8_t a) { return vqmovn_s16(a); }
[[gnu::always_inline]] nce uint8x8_t move_unsigned_saturate_narrow(int16x8_t a) { return vqmovun_s16(a); }
template <int lane> [[gnu::always_inline]] nce int16x8_t multiply_lane(int16x8_t a, int16x4_t v) { return vmulq_lane_s16(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce int16x8_t multiply_add_lane(int16x8_t a, int16x8_t b, int16x4_t v) { return vmlaq_lane_s16(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce int16x8_t multiply_subtract_lane(int16x8_t a, int16x8_t b, int16x4_t v) { return vmlsq_lane_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int16x8_t multiply_add(int16x8_t a, int16x8_t b, int16_t c) { return vmlaq_n_s16(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract(int16x8_t a, int16x8_t b, int16_t c) { return vmlsq_n_s16(a, b, c); }
[[gnu::always_inline]] nce int16x4_t get_high(int16x8_t a) { return vget_high_s16(a); }
[[gnu::always_inline]] nce int16x4_t get_low(int16x8_t a) { return vget_low_s16(a); }
template <int n>[[gnu::always_inline]] nce int16x8_t extract(int16x8_t a, int16x8_t b) { return vextq_s16(a, b, n); }
[[gnu::always_inline]] nce int16x8x2_t zip(int16x8_t a, int16x8_t b) { return vzipq_s16(a, b); }
[[gnu::always_inline]] nce int16x8x2_t unzip(int16x8_t a, int16x8_t b) { return vuzpq_s16(a, b); }
[[gnu::always_inline]] nce int16x8x2_t transpose(int16x8_t a, int16x8_t b) { return vtrnq_s16(a, b); }
[[gnu::always_inline]] nce int32x2_t add(int32x2_t a, int32x2_t b) { return vadd_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t add_long(int32x2_t a, int32x2_t b) { return vaddl_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t add_halve(int32x2_t a, int32x2_t b) { return vhadd_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t add_halve_round(int32x2_t a, int32x2_t b) { return vrhadd_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t add_saturate(int32x2_t a, int32x2_t b) { return vqadd_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t multiply(int32x2_t a, int32x2_t b) { return vmul_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t multiply_add(int32x2_t a, int32x2_t b, int32x2_t c) { return vmla_s32(a, b, c); }
[[gnu::always_inline]] nce int32x2_t multiply_subtract(int32x2_t a, int32x2_t b, int32x2_t c) { return vmls_s32(a, b, c); }
[[gnu::always_inline]] nce int32x2_t multiply_double_saturate_high(int32x2_t a, int32x2_t b) { return vqdmulh_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t multiply_double_round_saturate_high(int32x2_t a, int32x2_t b) { return vqrdmulh_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long(int32x2_t a, int32x2_t b) { return vqdmull_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_long(int32x2_t a, int32x2_t b) { return vmull_s32(a, b); }
template <int lane> [[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_lane(int32x2_t a, int32x2_t v) { return vqdmull_lane_s32(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce int32x2_t multiply_double_saturate_high_lane(int32x2_t a, int32x2_t v) { return vqdmulh_lane_s32(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce int32x2_t multiply_double_round_saturate_high_lane(int32x2_t a, int32x2_t v) { return vqrdmulh_lane_s32(a, v, lane); }
[[gnu::always_inline]] nce int32x2_t subtract(int32x2_t a, int32x2_t b) { return vsub_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_long(int32x2_t a, int32x2_t b) { return vsubl_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_halve(int32x2_t a, int32x2_t b) { return vhsub_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_saturate(int32x2_t a, int32x2_t b) { return vqsub_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_absolute(int32x2_t a, int32x2_t b) { return vabd_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_absolute_long(int32x2_t a, int32x2_t b) { return vabdl_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_absolute_add(int32x2_t a, int32x2_t b, int32x2_t c) { return vaba_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long(int32x2_t a, int32_t b) { return vqdmull_n_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t multiply_double_saturate_high(int32x2_t a, int32_t b) { return vqdmulh_n_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t multiply_double_round_saturate_high(int32x2_t a, int32_t b) { return vqrdmulh_n_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t absolute(int32x2_t a) { return vabs_s32(a); }
[[gnu::always_inline]] nce int32x2_t absolute_saturate(int32x2_t a) { return vqabs_s32(a); }
[[gnu::always_inline]] nce int32x2_t max(int32x2_t a, int32x2_t b) { return vmax_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t min(int32x2_t a, int32x2_t b) { return vmin_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t pairwise_add(int32x2_t a, int32x2_t b) { return vpadd_s32(a, b); }
[[gnu::always_inline]] nce int64x1_t pairwise_add_long(int32x2_t a) { return vpaddl_s32(a); }
[[gnu::always_inline]] nce int32x2_t pairwise_add_accumulate_long(int32x2_t a, int16x4_t b) { return vpadal_s16(a, b); }
[[gnu::always_inline]] nce int32x2_t pairwise_max(int32x2_t a, int32x2_t b) { return vpmax_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t pairwise_min(int32x2_t a, int32x2_t b) { return vpmin_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t equal(int32x2_t a, int32x2_t b) { return vceq_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t greater_than_or_equal(int32x2_t a, int32x2_t b) { return vcge_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t less_than_or_equal(int32x2_t a, int32x2_t b) { return vcle_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t greater_than(int32x2_t a, int32x2_t b) { return vcgt_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t less_than(int32x2_t a, int32x2_t b) { return vclt_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t compare_test_nonzero(int32x2_t a, int32x2_t b) { return vtst_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t shift_left(int32x2_t a, int32x2_t b) { return vshl_s32(a, b); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_left(int32x2_t a) { return vshl_n_s32(a, n); }
[[gnu::always_inline]] nce int32x2_t shift_left_saturate(int32x2_t a, int32x2_t b) { return vqshl_s32(a, b); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_left_saturate(int32x2_t a) { return vqshl_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_left_unsigned_saturate(int32x2_t a) { return vqshlu_n_s32(a, n); }
[[gnu::always_inline]] nce int32x2_t shift_left_round(int32x2_t a, int32x2_t b) { return vrshl_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t shift_left_round_saturate(int32x2_t a, int32x2_t b) { return vqrshl_s32(a, b); }
template <int n>[[gnu::always_inline]] nce int64x2_t shift_left_long(int32x2_t a) { return vshll_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_left_insert(int32x2_t a, int32x2_t b) { return vsli_n_s32(a, b, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right(int32x2_t a) { return vshr_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right_round(int32x2_t a) { return vrshr_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right_accumulate(int32x2_t a, int32x2_t b) { return vsra_n_s32(a, b, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right_accumulate_round(int32x2_t a, int32x2_t b) { return vrsra_n_s32(a, b, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right_insert(int32x2_t a, int32x2_t b) { return vsri_n_s32(a, b, n); }
template <> [[gnu::always_inline]] nce float32x2_t convert(int32x2_t a) { return vcvt_f32_s32(a); }
template <int fracbits> [[gnu::always_inline]] nce float32x2_t convert_n(int32x2_t a) { return vcvt_n_f32_s32(a, fracbits); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(int32x2_t a) { return vreinterpret_s8_s32(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(int32x2_t a) { return vreinterpret_s16_s32(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(int32x2_t a) { return vreinterpret_f32_s32(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(int32x2_t a) { return vreinterpret_u8_s32(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(int32x2_t a) { return vreinterpret_u16_s32(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(int32x2_t a) { return vreinterpret_u32_s32(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(int32x2_t a) { return vreinterpret_p8_s32(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(int32x2_t a) { return vreinterpret_p16_s32(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(int32x2_t a) { return vreinterpret_u64_s32(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(int32x2_t a) { return vreinterpret_s64_s32(a); }
[[gnu::always_inline]] nce int64x2_t move_long(int32x2_t a) { return vmovl_s32(a); }
template <int lane> [[gnu::always_inline]] nce int32x2_t multiply_add_lane(int32x2_t a, int32x2_t b, int32x2_t v) { return vmla_lane_s32(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce int32x2_t multiply_subtract_lane(int32x2_t a, int32x2_t b, int32x2_t v) { return vmls_lane_s32(a, b, v, lane); }
[[gnu::always_inline]] nce int32x2_t multiply_add(int32x2_t a, int32x2_t b, int32_t c) { return vmla_n_s32(a, b, c); }
template <int lane> [[gnu::always_inline]] nce int32x2_t multiply_lane(int32x2_t a, int32x2_t v) { return vmul_lane_s32(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce int64x2_t multiply_long_lane(int32x2_t a, int32x2_t v) { return vmull_lane_s32(a, v, lane); }
[[gnu::always_inline]] nce int32x2_t multiply_subtract(int32x2_t a, int32x2_t b, int32_t c) { return vmls_n_s32(a, b, c); }
[[gnu::always_inline]] nce int32x2_t negate(int32x2_t a) { return vneg_s32(a); }
[[gnu::always_inline]] nce int32x2_t negate_saturate(int32x2_t a) { return vqneg_s32(a); }
[[gnu::always_inline]] nce int32x2_t bitwise_not(int32x2_t a) { return vmvn_s32(a); }
[[gnu::always_inline]] nce int32x2_t bitwise_and(int32x2_t a, int32x2_t b) { return vand_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t bitwise_or(int32x2_t a, int32x2_t b) { return vorr_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t bitwise_xor(int32x2_t a, int32x2_t b) { return veor_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t bitwise_or_not(int32x2_t a, int32x2_t b) { return vorn_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t count_leading_sign_bits(int32x2_t a) { return vcls_s32(a); }
[[gnu::always_inline]] nce int32x2_t count_leading_zero_bits(int32x2_t a) { return vclz_s32(a); }
[[gnu::always_inline]] nce int32x2_t bitwise_clear(int32x2_t a, int32x2_t b) { return vbic_s32(a, b); }
template <int lane>[[gnu::always_inline]] nce int32x2_t duplicate_lane(int32x2_t a) { return vdup_lane_s32(a, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t duplicate_lane_quad(int32x2_t a) { return vdupq_lane_s32(a, lane); }
[[gnu::always_inline]] nce int32x4_t combine(int32x2_t low, int32x2_t high) { return vcombine_s32(low, high); }
template <int lane>[[gnu::always_inline]] nce int32_t get_lane(int32x2_t v) { return vget_lane_s32(v, lane); }
template <int n>[[gnu::always_inline]] nce int32x2_t extract(int32x2_t a, int32x2_t b) { return vext_s32(a, b, n); }
[[gnu::always_inline]] nce int32x2_t reverse_64bit(int32x2_t a) { return vrev64_s32(a); }
[[gnu::always_inline]] nce int32x2x2_t zip(int32x2_t a, int32x2_t b) { return vzip_s32(a, b); }
[[gnu::always_inline]] nce int32x2x2_t unzip(int32x2_t a, int32x2_t b) { return vuzp_s32(a, b); }
[[gnu::always_inline]] nce int32x2x2_t transpose(int32x2_t a, int32x2_t b) { return vtrn_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t multiply(int32x2_t a, int32_t b) { return vmul_n_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_long(int32x2_t a, int32_t b) { return vmull_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add(int32x4_t a, int16x4_t b) { return vaddw_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_add_long(int32x4_t a, int16x4_t b, int16x4_t c) { return vmlal_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_long(int32x4_t a, int16x4_t b, int16x4_t c) { return vmlsl_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_add_saturate_long(int32x4_t a, int16x4_t b, int16x4_t c) { return vqdmlal_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_saturate_long(int32x4_t a, int16x4_t b, int16x4_t c) { return vqdmlsl_s16(a, b, c); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_double_add_saturate_long_lane(int32x4_t a, int16x4_t b, int16x4_t v) { return vqdmlal_lane_s16(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_double_subtract_saturate_long_lane(int32x4_t a, int16x4_t b, int16x4_t v) { return vqdmlsl_lane_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t subtract_absolute_add(int32x4_t a, int16x4_t b, int16x4_t c) { return vabal_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_add_saturate_long(int32x4_t a, int16x4_t b, int16_t c) { return vqdmlal_n_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_saturate_long(int32x4_t a, int16x4_t b, int16_t c) { return vqdmlsl_n_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t subtract(int32x4_t a, int16x4_t b) { return vsubw_s16(a, b); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high_lane(int32x4_t a, int32x2_t v) { return vqdmulhq_lane_s32(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high_lane(int32x4_t a, int32x2_t v) { return vqrdmulhq_lane_s32(a, v, lane); }
[[gnu::always_inline]] nce int16x4_t add_narrow(int32x4_t a, int32x4_t b) { return vaddhn_s32(a, b); }
[[gnu::always_inline]] nce int16x4_t add_round_narrow(int32x4_t a, int32x4_t b) { return vraddhn_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_add(int32x4_t a, int32x4_t b, int32x4_t c) { return vmlaq_s32(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract(int32x4_t a, int32x4_t b, int32x4_t c) { return vmlsq_s32(a, b, c); }
[[gnu::always_inline]] nce int16x4_t subtract_narrow(int32x4_t a, int32x4_t b) { return vsubhn_s32(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_round_narrow(int32x4_t a, int32x4_t b) { return vrsubhn_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_absolute_add(int32x4_t a, int32x4_t b, int32x4_t c) { return vabaq_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t pairwise_add_long(int32x4_t a) { return vpaddlq_s32(a); }
[[gnu::always_inline]] nce int32x4_t pairwise_add_accumulate_long(int32x4_t a, int16x8_t b) { return vpadalq_s16(a, b); }
[[gnu::always_inline]] nce uint32x4_t equal(int32x4_t a, int32x4_t b) { return vceqq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t greater_than_or_equal(int32x4_t a, int32x4_t b) { return vcgeq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t less_than_or_equal(int32x4_t a, int32x4_t b) { return vcleq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t greater_than(int32x4_t a, int32x4_t b) { return vcgtq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t less_than(int32x4_t a, int32x4_t b) { return vcltq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t compare_test_nonzero(int32x4_t a, int32x4_t b) { return vtstq_s32(a, b); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t a) { return vshlq_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_left_unsigned_saturate(int32x4_t a) { return vqshluq_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_accumulate(int32x4_t a, int32x4_t b) { return vsraq_n_s32(a, b, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_accumulate_round(int32x4_t a, int32x4_t b) { return vrsraq_n_s32(a, b, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_narrow(int32x4_t a) { return vshrn_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_saturate_narrow_unsigned(int32x4_t a) { return vqshrun_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_saturate_narrow(int32x4_t a) { return vqshrn_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_round_saturate_narrow_unsigned(int32x4_t a) { return vqrshrun_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_round_saturate_narrow(int32x4_t a) { return vqrshrn_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_round_narrow(int32x4_t a) { return vrshrn_n_s32(a, n); }
template <int fracbits> [[gnu::always_inline]] nce float32x4_t convert_n(int32x4_t a) { return vcvtq_n_f32_s32(a, fracbits); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(int32x4_t a) { return vreinterpretq_p8_s32(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(int32x4_t a) { return vreinterpretq_p16_s32(a); }
[[gnu::always_inline]] nce int16x4_t move_narrow(int32x4_t a) { return vmovn_s32(a); }
[[gnu::always_inline]] nce int16x4_t move_saturate_narrow(int32x4_t a) { return vqmovn_s32(a); }
[[gnu::always_inline]] nce uint16x4_t move_unsigned_saturate_narrow(int32x4_t a) { return vqmovun_s32(a); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_add_long_lane(int32x4_t a, int16x4_t b, int16x4_t v) { return vmlal_lane_s16(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_subtract_long_lane(int32x4_t a, int16x4_t b, int16x4_t v) { return vmlsl_lane_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t multiply_add_long(int32x4_t a, int16x4_t b, int16_t c) { return vmlal_n_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_long(int32x4_t a, int16x4_t b, int16_t c) { return vmlsl_n_s16(a, b, c); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_lane(int32x4_t a, int32x2_t v) { return vmulq_lane_s32(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_add_lane(int32x4_t a, int32x4_t b, int32x2_t v) { return vmlaq_lane_s32(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce int32x4_t multiply_subtract_lane(int32x4_t a, int32x4_t b, int32x2_t v) { return vmlsq_lane_s32(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t multiply_add(int32x4_t a, int32x4_t b, int32_t c) { return vmlaq_n_s32(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract(int32x4_t a, int32x4_t b, int32_t c) { return vmlsq_n_s32(a, b, c); }
[[gnu::always_inline]] nce int32x2_t get_high(int32x4_t a) { return vget_high_s32(a); }
[[gnu::always_inline]] nce int32x2_t get_low(int32x4_t a) { return vget_low_s32(a); }
template <int n>[[gnu::always_inline]] nce int32x4_t extract(int32x4_t a, int32x4_t b) { return vextq_s32(a, b, n); }
[[gnu::always_inline]] nce int32x4x2_t zip(int32x4_t a, int32x4_t b) { return vzipq_s32(a, b); }
[[gnu::always_inline]] nce int32x4x2_t unzip(int32x4_t a, int32x4_t b) { return vuzpq_s32(a, b); }
[[gnu::always_inline]] nce int32x4x2_t transpose(int32x4_t a, int32x4_t b) { return vtrnq_s32(a, b); }
[[gnu::always_inline]] nce uint64x1_t add(uint64x1_t a, uint64x1_t b) { return vadd_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t add_saturate(uint64x1_t a, uint64x1_t b) { return vqadd_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t subtract(uint64x1_t a, uint64x1_t b) { return vsub_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t subtract_saturate(uint64x1_t a, uint64x1_t b) { return vqsub_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t pairwise_add_accumulate_long(uint64x1_t a, uint32x2_t b) { return vpadal_u32(a, b); }
[[gnu::always_inline]] nce uint64x1_t shift_left(uint64x1_t a, int64x1_t b) { return vshl_u64(a, b); }
template <int n>[[gnu::always_inline]] nce uint64x1_t shift_left(uint64x1_t a) { return vshl_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x1_t shift_right(uint64x1_t a) { return vshr_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x1_t shift_right_round(uint64x1_t a) { return vrshr_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x1_t shift_right_accumulate(uint64x1_t a, uint64x1_t b) { return vsra_n_u64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint64x1_t shift_right_accumulate_round(uint64x1_t a, uint64x1_t b) { return vrsra_n_u64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint64x1_t shift_right_insert(uint64x1_t a, uint64x1_t b) { return vsri_n_u64(a, b, n); }
[[gnu::always_inline]] nce uint64x1_t shift_left_saturate(uint64x1_t a, int64x1_t b) { return vqshl_u64(a, b); }
template <int n>[[gnu::always_inline]] nce uint64x1_t shift_left_saturate(uint64x1_t a) { return vqshl_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x1_t shift_left_insert(uint64x1_t a, uint64x1_t b) { return vsli_n_u64(a, b, n); }
[[gnu::always_inline]] nce uint64x1_t shift_left_round(uint64x1_t a, int64x1_t b) { return vrshl_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t shift_left_round_saturate(uint64x1_t a, int64x1_t b) { return vqrshl_u64(a, b); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(uint64x1_t a) { return vreinterpret_s8_u64(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(uint64x1_t a) { return vreinterpret_s16_u64(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(uint64x1_t a) { return vreinterpret_s32_u64(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(uint64x1_t a) { return vreinterpret_f32_u64(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(uint64x1_t a) { return vreinterpret_u8_u64(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(uint64x1_t a) { return vreinterpret_u16_u64(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(uint64x1_t a) { return vreinterpret_u32_u64(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(uint64x1_t a) { return vreinterpret_p8_u64(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(uint64x1_t a) { return vreinterpret_p16_u64(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(uint64x1_t a) { return vreinterpret_s64_u64(a); }
[[gnu::always_inline]] nce uint64x1_t bitwise_and(uint64x1_t a, uint64x1_t b) { return vand_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t bitwise_or(uint64x1_t a, uint64x1_t b) { return vorr_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t bitwise_xor(uint64x1_t a, uint64x1_t b) { return veor_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t bitwise_or_not(uint64x1_t a, uint64x1_t b) { return vorn_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t bitwise_clear(uint64x1_t a, uint64x1_t b) { return vbic_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t bitwise_select(uint64x1_t a, uint64x1_t b, uint64x1_t c) { return vbsl_u64(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint64x1_t duplicate_lane(uint64x1_t a) { return vdup_lane_u64(a, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t duplicate_lane_quad(uint64x1_t a) { return vdupq_lane_u64(a, lane); }
[[gnu::always_inline]] nce uint64x2_t combine(uint64x1_t low, uint64x1_t high) { return vcombine_u64(low, high); }
template <int lane>[[gnu::always_inline]] nce uint64_t get_lane(uint64x1_t v) { return vget_lane_u64(v, lane); }
template <int n>[[gnu::always_inline]] nce uint64x1_t extract(uint64x1_t a, uint64x1_t b) { return vext_u64(a, b, n); }
[[gnu::always_inline]] nce int64x1_t bitwise_select(uint64x1_t a, int64x1_t b, int64x1_t c) { return vbsl_s64(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t add(uint64x2_t a, uint64x2_t b) { return vaddq_u64(a, b); }
[[gnu::always_inline]] nce uint32x2_t add_narrow(uint64x2_t a, uint64x2_t b) { return vaddhn_u64(a, b); }
[[gnu::always_inline]] nce uint32x2_t add_round_narrow(uint64x2_t a, uint64x2_t b) { return vraddhn_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t add_saturate(uint64x2_t a, uint64x2_t b) { return vqaddq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract(uint64x2_t a, uint64x2_t b) { return vsubq_u64(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_narrow(uint64x2_t a, uint64x2_t b) { return vsubhn_u64(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_round_narrow(uint64x2_t a, uint64x2_t b) { return vrsubhn_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract_saturate(uint64x2_t a, uint64x2_t b) { return vqsubq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t shift_left_saturate(uint64x2_t a, int64x2_t b) { return vqshlq_u64(a, b); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_left_saturate(uint64x2_t a) { return vqshlq_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_left_insert(uint64x2_t a, uint64x2_t b) { return vsliq_n_u64(a, b, n); }
[[gnu::always_inline]] nce uint64x2_t add(uint64x2_t a, uint32x2_t b) { return vaddw_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t multiply_add_long(uint64x2_t a, uint32x2_t b, uint32x2_t c) { return vmlal_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long(uint64x2_t a, uint32x2_t b, uint32x2_t c) { return vmlsl_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t subtract(uint64x2_t a, uint32x2_t b) { return vsubw_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract_absolute_add(uint64x2_t a, uint32x2_t b, uint32x2_t c) { return vabal_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t shift_left_round(uint64x2_t a, int64x2_t b) { return vrshlq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t shift_left_round_saturate(uint64x2_t a, int64x2_t b) { return vqrshlq_u64(a, b); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_right(uint64x2_t a) { return vshrq_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_right_round(uint64x2_t a) { return vrshrq_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_right_accumulate(uint64x2_t a, uint64x2_t b) { return vsraq_n_u64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_right_accumulate_round(uint64x2_t a, uint64x2_t b) { return vrsraq_n_u64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_narrow(uint64x2_t a) { return vshrn_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_saturate_narrow(uint64x2_t a) { return vqshrn_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_round_saturate_narrow(uint64x2_t a) { return vqrshrn_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_round_narrow(uint64x2_t a) { return vrshrn_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_right_insert(uint64x2_t a, uint64x2_t b) { return vsriq_n_u64(a, b, n); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(uint64x2_t a) { return vreinterpretq_p8_u64(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_p16_u64(a); }
[[gnu::always_inline]] nce uint32x2_t move_narrow(uint64x2_t a) { return vmovn_u64(a); }
[[gnu::always_inline]] nce uint32x2_t move_saturate_narrow(uint64x2_t a) { return vqmovn_u64(a); }
template <int lane> [[gnu::always_inline]] nce uint64x2_t multiply_add_long_lane(uint64x2_t a, uint32x2_t b, uint32x2_t v) { return vmlal_lane_u32(a, b, v, lane); }
[[gnu::always_inline]] nce uint64x2_t pairwise_add_accumulate_long(uint64x2_t a, uint32x4_t b) { return vpadalq_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t shift_left(uint64x2_t a, int64x2_t b) { return vshlq_u64(a, b); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_left(uint64x2_t a) { return vshlq_n_u64(a, n); }
[[gnu::always_inline]] nce uint64x2_t bitwise_and(uint64x2_t a, uint64x2_t b) { return vandq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t bitwise_or(uint64x2_t a, uint64x2_t b) { return vorrq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t bitwise_xor(uint64x2_t a, uint64x2_t b) { return veorq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t bitwise_or_not(uint64x2_t a, uint64x2_t b) { return vornq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t bitwise_clear(uint64x2_t a, uint64x2_t b) { return vbicq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t bitwise_select(uint64x2_t a, uint64x2_t b, uint64x2_t c) { return vbslq_u64(a, b, c); }
[[gnu::always_inline]] nce uint64x1_t get_high(uint64x2_t a) { return vget_high_u64(a); }
[[gnu::always_inline]] nce uint64x1_t get_low(uint64x2_t a) { return vget_low_u64(a); }
template <int n>[[gnu::always_inline]] nce uint64x2_t extract(uint64x2_t a, uint64x2_t b) { return vextq_u64(a, b, n); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long_lane(uint64x2_t a, uint32x2_t b, uint32x2_t v) { return vmlsl_lane_u32(a, b, v, lane); }
[[gnu::always_inline]] nce uint64x2_t multiply_add_long(uint64x2_t a, uint32x2_t b, uint32_t c) { return vmlal_n_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long(uint64x2_t a, uint32x2_t b, uint32_t c) { return vmlsl_n_u32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t bitwise_select(uint64x2_t a, int64x2_t b, int64x2_t c) { return vbslq_s64(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t shift_left(uint32x2_t a, int32x2_t b) { return vshl_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t add(uint32x2_t a, uint32x2_t b) { return vadd_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t add_long(uint32x2_t a, uint32x2_t b) { return vaddl_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t add_halve(uint32x2_t a, uint32x2_t b) { return vhadd_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t add_halve_round(uint32x2_t a, uint32x2_t b) { return vrhadd_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t add_saturate(uint32x2_t a, uint32x2_t b) { return vqadd_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t multiply(uint32x2_t a, uint32x2_t b) { return vmul_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t multiply_add(uint32x2_t a, uint32x2_t b, uint32x2_t c) { return vmla_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t multiply_subtract(uint32x2_t a, uint32x2_t b, uint32x2_t c) { return vmls_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t multiply_long(uint32x2_t a, uint32x2_t b) { return vmull_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract(uint32x2_t a, uint32x2_t b) { return vsub_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract_long(uint32x2_t a, uint32x2_t b) { return vsubl_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_halve(uint32x2_t a, uint32x2_t b) { return vhsub_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_saturate(uint32x2_t a, uint32x2_t b) { return vqsub_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_absolute(uint32x2_t a, uint32x2_t b) { return vabd_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract_absolute_long(uint32x2_t a, uint32x2_t b) { return vabdl_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_absolute_add(uint32x2_t a, uint32x2_t b, uint32x2_t c) { return vaba_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t max(uint32x2_t a, uint32x2_t b) { return vmax_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t min(uint32x2_t a, uint32x2_t b) { return vmin_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t reciprocal_estimate(uint32x2_t a) { return vrecpe_u32(a); }
[[gnu::always_inline]] nce uint32x2_t reciprocal_sqrt_estimate(uint32x2_t a) { return vrsqrte_u32(a); }
[[gnu::always_inline]] nce uint32x2_t pairwise_add(uint32x2_t a, uint32x2_t b) { return vpadd_u32(a, b); }
[[gnu::always_inline]] nce uint64x1_t pairwise_add_long(uint32x2_t a) { return vpaddl_u32(a); }
[[gnu::always_inline]] nce uint32x2_t pairwise_add_accumulate_long(uint32x2_t a, uint16x4_t b) { return vpadal_u16(a, b); }
[[gnu::always_inline]] nce uint32x2_t pairwise_max(uint32x2_t a, uint32x2_t b) { return vpmax_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t pairwise_min(uint32x2_t a, uint32x2_t b) { return vpmin_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t equal(uint32x2_t a, uint32x2_t b) { return vceq_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t greater_than_or_equal(uint32x2_t a, uint32x2_t b) { return vcge_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t less_than_or_equal(uint32x2_t a, uint32x2_t b) { return vcle_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t greater_than(uint32x2_t a, uint32x2_t b) { return vcgt_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t less_than(uint32x2_t a, uint32x2_t b) { return vclt_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t compare_test_nonzero(uint32x2_t a, uint32x2_t b) { return vtst_u32(a, b); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_left(uint32x2_t a) { return vshl_n_u32(a, n); }
[[gnu::always_inline]] nce uint32x2_t shift_left_saturate(uint32x2_t a, int32x2_t b) { return vqshl_u32(a, b); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_left_saturate(uint32x2_t a) { return vqshl_n_u32(a, n); }
[[gnu::always_inline]] nce uint32x2_t shift_left_round(uint32x2_t a, int32x2_t b) { return vrshl_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t shift_left_round_saturate(uint32x2_t a, int32x2_t b) { return vqrshl_u32(a, b); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_left_long(uint32x2_t a) { return vshll_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_left_insert(uint32x2_t a, uint32x2_t b) { return vsli_n_u32(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right(uint32x2_t a) { return vshr_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_round(uint32x2_t a) { return vrshr_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_accumulate(uint32x2_t a, uint32x2_t b) { return vsra_n_u32(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_accumulate_round(uint32x2_t a, uint32x2_t b) { return vrsra_n_u32(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_insert(uint32x2_t a, uint32x2_t b) { return vsri_n_u32(a, b, n); }
template <> [[gnu::always_inline]] nce float32x2_t convert(uint32x2_t a) { return vcvt_f32_u32(a); }
template <int fracbits> [[gnu::always_inline]] nce float32x2_t convert_n(uint32x2_t a) { return vcvt_n_f32_u32(a, fracbits); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(uint32x2_t a) { return vreinterpret_s8_u32(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(uint32x2_t a) { return vreinterpret_s16_u32(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(uint32x2_t a) { return vreinterpret_s32_u32(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(uint32x2_t a) { return vreinterpret_f32_u32(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(uint32x2_t a) { return vreinterpret_u8_u32(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(uint32x2_t a) { return vreinterpret_u16_u32(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(uint32x2_t a) { return vreinterpret_p8_u32(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(uint32x2_t a) { return vreinterpret_p16_u32(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(uint32x2_t a) { return vreinterpret_u64_u32(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(uint32x2_t a) { return vreinterpret_s64_u32(a); }
[[gnu::always_inline]] nce uint64x2_t move_long(uint32x2_t a) { return vmovl_u32(a); }
template <int lane> [[gnu::always_inline]] nce uint32x2_t multiply_add_lane(uint32x2_t a, uint32x2_t b, uint32x2_t v) { return vmla_lane_u32(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce uint32x2_t multiply_subtract_lane(uint32x2_t a, uint32x2_t b, uint32x2_t v) { return vmls_lane_u32(a, b, v, lane); }
[[gnu::always_inline]] nce uint32x2_t multiply_add(uint32x2_t a, uint32x2_t b, uint32_t c) { return vmla_n_u32(a, b, c); }
template <int lane> [[gnu::always_inline]] nce uint32x2_t multiply_lane(uint32x2_t a, uint32x2_t v) { return vmul_lane_u32(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce uint64x2_t multiply_long_lane(uint32x2_t a, uint32x2_t v) { return vmull_lane_u32(a, v, lane); }
[[gnu::always_inline]] nce uint32x2_t multiply_subtract(uint32x2_t a, uint32x2_t b, uint32_t c) { return vmls_n_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t bitwise_not(uint32x2_t a) { return vmvn_u32(a); }
[[gnu::always_inline]] nce uint32x2_t bitwise_and(uint32x2_t a, uint32x2_t b) { return vand_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t bitwise_or(uint32x2_t a, uint32x2_t b) { return vorr_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t bitwise_xor(uint32x2_t a, uint32x2_t b) { return veor_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t bitwise_or_not(uint32x2_t a, uint32x2_t b) { return vorn_u32(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce int32x2_t count_leading_sign_bits(uint32x2_t a) { return vcls_u32(a); }
#endif
[[gnu::always_inline]] nce uint32x2_t count_leading_zero_bits(uint32x2_t a) { return vclz_u32(a); }
[[gnu::always_inline]] nce int32x2_t bitwise_select(uint32x2_t a, int32x2_t b, int32x2_t c) { return vbsl_s32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t bitwise_clear(uint32x2_t a, uint32x2_t b) { return vbic_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t bitwise_select(uint32x2_t a, uint32x2_t b, uint32x2_t c) { return vbsl_u32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t duplicate_lane(uint32x2_t a) { return vdup_lane_u32(a, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t duplicate_lane_quad(uint32x2_t a) { return vdupq_lane_u32(a, lane); }
[[gnu::always_inline]] nce uint32x4_t combine(uint32x2_t low, uint32x2_t high) { return vcombine_u32(low, high); }
template <int lane>[[gnu::always_inline]] nce uint32_t get_lane(uint32x2_t v) { return vget_lane_u32(v, lane); }
template <int n>[[gnu::always_inline]] nce uint32x2_t extract(uint32x2_t a, uint32x2_t b) { return vext_u32(a, b, n); }
[[gnu::always_inline]] nce uint32x2_t reverse_64bit(uint32x2_t a) { return vrev64_u32(a); }
[[gnu::always_inline]] nce uint32x2x2_t zip(uint32x2_t a, uint32x2_t b) { return vzip_u32(a, b); }
[[gnu::always_inline]] nce uint32x2x2_t unzip(uint32x2_t a, uint32x2_t b) { return vuzp_u32(a, b); }
[[gnu::always_inline]] nce uint32x2x2_t transpose(uint32x2_t a, uint32x2_t b) { return vtrn_u32(a, b); }
[[gnu::always_inline]] nce float32x2_t bitwise_select(uint32x2_t a, float32x2_t b, float32x2_t c) { return vbsl_f32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t multiply(uint32x2_t a, uint32_t b) { return vmul_n_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t multiply_long(uint32x2_t a, uint32_t b) { return vmull_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add(uint32x4_t a, uint16x4_t b) { return vaddw_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_add_long(uint32x4_t a, uint16x4_t b, uint16x4_t c) { return vmlal_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_subtract_long(uint32x4_t a, uint16x4_t b, uint16x4_t c) { return vmlsl_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t subtract(uint32x4_t a, uint16x4_t b) { return vsubw_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_absolute_add(uint32x4_t a, uint16x4_t b, uint16x4_t c) { return vabal_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t add_narrow(uint32x4_t a, uint32x4_t b) { return vaddhn_u32(a, b); }
[[gnu::always_inline]] nce uint16x4_t add_round_narrow(uint32x4_t a, uint32x4_t b) { return vraddhn_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_add(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vmlaq_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_subtract(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vmlsq_u32(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t subtract_narrow(uint32x4_t a, uint32x4_t b) { return vsubhn_u32(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract_round_narrow(uint32x4_t a, uint32x4_t b) { return vrsubhn_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_absolute_add(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vabaq_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t reciprocal_estimate(uint32x4_t a) { return vrecpeq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t reciprocal_sqrt_estimate(uint32x4_t a) { return vrsqrteq_u32(a); }
[[gnu::always_inline]] nce uint64x2_t pairwise_add_long(uint32x4_t a) { return vpaddlq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t pairwise_add_accumulate_long(uint32x4_t a, uint16x8_t b) { return vpadalq_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t equal(uint32x4_t a, uint32x4_t b) { return vceqq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t greater_than_or_equal(uint32x4_t a, uint32x4_t b) { return vcgeq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t less_than_or_equal(uint32x4_t a, uint32x4_t b) { return vcleq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t greater_than(uint32x4_t a, uint32x4_t b) { return vcgtq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t less_than(uint32x4_t a, uint32x4_t b) { return vcltq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t compare_test_nonzero(uint32x4_t a, uint32x4_t b) { return vtstq_u32(a, b); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t a) { return vshlq_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_accumulate(uint32x4_t a, uint32x4_t b) { return vsraq_n_u32(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_accumulate_round(uint32x4_t a, uint32x4_t b) { return vrsraq_n_u32(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_narrow(uint32x4_t a) { return vshrn_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_saturate_narrow(uint32x4_t a) { return vqshrn_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_round_saturate_narrow(uint32x4_t a) { return vqrshrn_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_round_narrow(uint32x4_t a) { return vrshrn_n_u32(a, n); }
template <int fracbits> [[gnu::always_inline]] nce float32x4_t convert_n(uint32x4_t a) { return vcvtq_n_f32_u32(a, fracbits); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(uint32x4_t a) { return vreinterpretq_p8_u32(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_p16_u32(a); }
[[gnu::always_inline]] nce uint16x4_t move_narrow(uint32x4_t a) { return vmovn_u32(a); }
[[gnu::always_inline]] nce uint16x4_t move_saturate_narrow(uint32x4_t a) { return vqmovn_u32(a); }
template <int lane> [[gnu::always_inline]] nce uint32x4_t multiply_add_long_lane(uint32x4_t a, uint16x4_t b, uint16x4_t v) { return vmlal_lane_u16(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce uint32x4_t multiply_subtract_long_lane(uint32x4_t a, uint16x4_t b, uint16x4_t v) { return vmlsl_lane_u16(a, b, v, lane); }
[[gnu::always_inline]] nce uint32x4_t multiply_add_long(uint32x4_t a, uint16x4_t b, uint16_t c) { return vmlal_n_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_subtract_long(uint32x4_t a, uint16x4_t b, uint16_t c) { return vmlsl_n_u16(a, b, c); }
template <int lane> [[gnu::always_inline]] nce uint32x4_t multiply_lane(uint32x4_t a, uint32x2_t v) { return vmulq_lane_u32(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce uint32x4_t multiply_add_lane(uint32x4_t a, uint32x4_t b, uint32x2_t v) { return vmlaq_lane_u32(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce uint32x4_t multiply_subtract_lane(uint32x4_t a, uint32x4_t b, uint32x2_t v) { return vmlsq_lane_u32(a, b, v, lane); }
[[gnu::always_inline]] nce uint32x4_t multiply_add(uint32x4_t a, uint32x4_t b, uint32_t c) { return vmlaq_n_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_subtract(uint32x4_t a, uint32x4_t b, uint32_t c) { return vmlsq_n_u32(a, b, c); }
#ifdef __clang__
[[gnu::always_inline]] nce int32x4_t count_leading_sign_bits(uint32x4_t a) { return vclsq_u32(a); }
#endif
[[gnu::always_inline]] nce int32x4_t bitwise_select(uint32x4_t a, int32x4_t b, int32x4_t c) { return vbslq_s32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t bitwise_select(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vbslq_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t get_high(uint32x4_t a) { return vget_high_u32(a); }
[[gnu::always_inline]] nce uint32x2_t get_low(uint32x4_t a) { return vget_low_u32(a); }
template <int n>[[gnu::always_inline]] nce uint32x4_t extract(uint32x4_t a, uint32x4_t b) { return vextq_u32(a, b, n); }
[[gnu::always_inline]] nce uint32x4x2_t zip(uint32x4_t a, uint32x4_t b) { return vzipq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4x2_t unzip(uint32x4_t a, uint32x4_t b) { return vuzpq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4x2_t transpose(uint32x4_t a, uint32x4_t b) { return vtrnq_u32(a, b); }
[[gnu::always_inline]] nce float32x4_t bitwise_select(uint32x4_t a, float32x4_t b, float32x4_t c) { return vbslq_f32(a, b, c); }
[[gnu::always_inline]] nce float32x2_t add(float32x2_t a, float32x2_t b) { return vadd_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t multiply(float32x2_t a, float32x2_t b) { return vmul_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t multiply_add(float32x2_t a, float32x2_t b, float32x2_t c) { return vmla_f32(a, b, c); }
[[gnu::always_inline]] nce float32x2_t multiply_subtract(float32x2_t a, float32x2_t b, float32x2_t c) { return vmls_f32(a, b, c); }
[[gnu::always_inline]] nce float32x2_t subtract(float32x2_t a, float32x2_t b) { return vsub_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t subtract_absolute(float32x2_t a, float32x2_t b) { return vabd_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t absolute(float32x2_t a) { return vabs_f32(a); }
[[gnu::always_inline]] nce float32x2_t max(float32x2_t a, float32x2_t b) { return vmax_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t min(float32x2_t a, float32x2_t b) { return vmin_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t reciprocal_estimate(float32x2_t a) { return vrecpe_f32(a); }
[[gnu::always_inline]] nce float32x2_t reciprocal_step(float32x2_t a, float32x2_t b) { return vrecps_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t reciprocal_sqrt_estimate(float32x2_t a) { return vrsqrte_f32(a); }
[[gnu::always_inline]] nce float32x2_t reciprocal_sqrt_step(float32x2_t a, float32x2_t b) { return vrsqrts_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t pairwise_add(float32x2_t a, float32x2_t b) { return vpadd_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t pairwise_max(float32x2_t a, float32x2_t b) { return vpmax_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t pairwise_min(float32x2_t a, float32x2_t b) { return vpmin_f32(a, b); }
[[gnu::always_inline]] nce uint32x2_t equal(float32x2_t a, float32x2_t b) { return vceq_f32(a, b); }
[[gnu::always_inline]] nce uint32x2_t greater_than_or_equal(float32x2_t a, float32x2_t b) { return vcge_f32(a, b); }
[[gnu::always_inline]] nce uint32x2_t less_than_or_equal(float32x2_t a, float32x2_t b) { return vcle_f32(a, b); }
[[gnu::always_inline]] nce uint32x2_t greater_than(float32x2_t a, float32x2_t b) { return vcgt_f32(a, b); }
[[gnu::always_inline]] nce uint32x2_t less_than(float32x2_t a, float32x2_t b) { return vclt_f32(a, b); }
[[gnu::always_inline]] nce uint32x2_t absolute_greater_than_or_equal(float32x2_t a, float32x2_t b) { return vcage_f32(a, b); }
[[gnu::always_inline]] nce uint32x2_t absolute_less_than_or_equal(float32x2_t a, float32x2_t b) { return vcale_f32(a, b); }
[[gnu::always_inline]] nce uint32x2_t absolute_greater_than(float32x2_t a, float32x2_t b) { return vcagt_f32(a, b); }
[[gnu::always_inline]] nce uint32x2_t absolute_less_than(float32x2_t a, float32x2_t b) { return vcalt_f32(a, b); }
template <> [[gnu::always_inline]] nce int32x2_t convert(float32x2_t a) { return vcvt_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x2_t convert(float32x2_t a) { return vcvt_u32_f32(a); }
template <int fracbits> [[gnu::always_inline]] nce int32x2_t convert_n_signed(float32x2_t a) { return vcvt_n_s32_f32(a, fracbits); }
template <int fracbits> [[gnu::always_inline]] nce uint32x2_t convert_n_unsigned(float32x2_t a) { return vcvt_n_u32_f32(a, fracbits); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(float32x2_t a) { return vreinterpret_s8_f32(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(float32x2_t a) { return vreinterpret_s16_f32(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(float32x2_t a) { return vreinterpret_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(float32x2_t a) { return vreinterpret_u8_f32(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(float32x2_t a) { return vreinterpret_u16_f32(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(float32x2_t a) { return vreinterpret_u32_f32(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(float32x2_t a) { return vreinterpret_p8_f32(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(float32x2_t a) { return vreinterpret_p16_f32(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(float32x2_t a) { return vreinterpret_u64_f32(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(float32x2_t a) { return vreinterpret_s64_f32(a); }
template <int lane> [[gnu::always_inline]] nce float32x2_t multiply_add_lane(float32x2_t a, float32x2_t b, float32x2_t v) { return vmla_lane_f32(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce float32x2_t multiply_subtract_lane(float32x2_t a, float32x2_t b, float32x2_t v) { return vmls_lane_f32(a, b, v, lane); }
[[gnu::always_inline]] nce float32x2_t multiply_add(float32x2_t a, float32x2_t b, float32_t c) { return vmla_n_f32(a, b, c); }
template <int lane> [[gnu::always_inline]] nce float32x2_t multiply_lane(float32x2_t a, float32x2_t v) { return vmul_lane_f32(a, v, lane); }
[[gnu::always_inline]] nce float32x2_t multiply_subtract(float32x2_t a, float32x2_t b, float32_t c) { return vmls_n_f32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce float32x2_t duplicate_lane(float32x2_t a) { return vdup_lane_f32(a, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t duplicate_lane_quad(float32x2_t a) { return vdupq_lane_f32(a, lane); }
[[gnu::always_inline]] nce float32x4_t combine(float32x2_t low, float32x2_t high) { return vcombine_f32(low, high); }
template <int lane>[[gnu::always_inline]] nce float32_t get_lane(float32x2_t v) { return vget_lane_f32(v, lane); }
template <int n>[[gnu::always_inline]] nce float32x2_t extract(float32x2_t a, float32x2_t b) { return vext_f32(a, b, n); }
[[gnu::always_inline]] nce float32x2_t reverse_64bit(float32x2_t a) { return vrev64_f32(a); }
[[gnu::always_inline]] nce float32x2x2_t zip(float32x2_t a, float32x2_t b) { return vzip_f32(a, b); }
[[gnu::always_inline]] nce float32x2x2_t unzip(float32x2_t a, float32x2_t b) { return vuzp_f32(a, b); }
[[gnu::always_inline]] nce float32x2x2_t transpose(float32x2_t a, float32x2_t b) { return vtrn_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t multiply(float32x2_t a, float32_t b) { return vmul_n_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t negate(float32x2_t a) { return vneg_f32(a); }
[[gnu::always_inline]] nce float32x4_t multiply_add(float32x4_t a, float32x4_t b, float32x4_t c) { return vmlaq_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t multiply_subtract(float32x4_t a, float32x4_t b, float32x4_t c) { return vmlsq_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t max(float32x4_t a, float32x4_t b) { return vmaxq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t min(float32x4_t a, float32x4_t b) { return vminq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t reciprocal_estimate(float32x4_t a) { return vrecpeq_f32(a); }
[[gnu::always_inline]] nce float32x4_t reciprocal_step(float32x4_t a, float32x4_t b) { return vrecpsq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t reciprocal_sqrt_estimate(float32x4_t a) { return vrsqrteq_f32(a); }
[[gnu::always_inline]] nce float32x4_t reciprocal_sqrt_step(float32x4_t a, float32x4_t b) { return vrsqrtsq_f32(a, b); }
[[gnu::always_inline]] nce uint32x4_t equal(float32x4_t a, float32x4_t b) { return vceqq_f32(a, b); }
[[gnu::always_inline]] nce uint32x4_t greater_than_or_equal(float32x4_t a, float32x4_t b) { return vcgeq_f32(a, b); }
[[gnu::always_inline]] nce uint32x4_t less_than_or_equal(float32x4_t a, float32x4_t b) { return vcleq_f32(a, b); }
[[gnu::always_inline]] nce uint32x4_t greater_than(float32x4_t a, float32x4_t b) { return vcgtq_f32(a, b); }
[[gnu::always_inline]] nce uint32x4_t less_than(float32x4_t a, float32x4_t b) { return vcltq_f32(a, b); }
[[gnu::always_inline]] nce uint32x4_t absolute_greater_than_or_equal(float32x4_t a, float32x4_t b) { return vcageq_f32(a, b); }
[[gnu::always_inline]] nce uint32x4_t absolute_less_than_or_equal(float32x4_t a, float32x4_t b) { return vcaleq_f32(a, b); }
[[gnu::always_inline]] nce uint32x4_t absolute_greater_than(float32x4_t a, float32x4_t b) { return vcagtq_f32(a, b); }
[[gnu::always_inline]] nce uint32x4_t absolute_less_than(float32x4_t a, float32x4_t b) { return vcaltq_f32(a, b); }
template <int fracbits> [[gnu::always_inline]] nce int32x4_t convert_n_signed(float32x4_t a) { return vcvtq_n_s32_f32(a, fracbits); }
template <int fracbits> [[gnu::always_inline]] nce uint32x4_t convert_n_unsigned(float32x4_t a) { return vcvtq_n_u32_f32(a, fracbits); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(float32x4_t a) { return vreinterpretq_p8_f32(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(float32x4_t a) { return vreinterpretq_p16_f32(a); }
template <int lane> [[gnu::always_inline]] nce float32x4_t multiply_lane(float32x4_t a, float32x2_t v) { return vmulq_lane_f32(a, v, lane); }
template <int lane> [[gnu::always_inline]] nce float32x4_t multiply_add_lane(float32x4_t a, float32x4_t b, float32x2_t v) { return vmlaq_lane_f32(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce float32x4_t multiply_subtract_lane(float32x4_t a, float32x4_t b, float32x2_t v) { return vmlsq_lane_f32(a, b, v, lane); }
[[gnu::always_inline]] nce float32x4_t multiply_add(float32x4_t a, float32x4_t b, float32_t c) { return vmlaq_n_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t multiply_subtract(float32x4_t a, float32x4_t b, float32_t c) { return vmlsq_n_f32(a, b, c); }
[[gnu::always_inline]] nce float32x2_t get_high(float32x4_t a) { return vget_high_f32(a); }
[[gnu::always_inline]] nce float32x2_t get_low(float32x4_t a) { return vget_low_f32(a); }
template <int n>[[gnu::always_inline]] nce float32x4_t extract(float32x4_t a, float32x4_t b) { return vextq_f32(a, b, n); }
[[gnu::always_inline]] nce float32x4x2_t zip(float32x4_t a, float32x4_t b) { return vzipq_f32(a, b); }
[[gnu::always_inline]] nce float32x4x2_t unzip(float32x4_t a, float32x4_t b) { return vuzpq_f32(a, b); }
[[gnu::always_inline]] nce float32x4x2_t transpose(float32x4_t a, float32x4_t b) { return vtrnq_f32(a, b); }
[[gnu::always_inline]] nce poly8x8_t multiply(poly8x8_t a, poly8x8_t b) { return vmul_p8(a, b); }
[[gnu::always_inline]] nce poly16x8_t multiply_long(poly8x8_t a, poly8x8_t b) { return vmull_p8(a, b); }
[[gnu::always_inline]] nce uint8x8_t equal(poly8x8_t a, poly8x8_t b) { return vceq_p8(a, b); }
[[gnu::always_inline]] nce uint8x8_t compare_test_nonzero(poly8x8_t a, poly8x8_t b) { return vtst_p8(a, b); }
template <int n>[[gnu::always_inline]] nce poly8x8_t shift_left_insert(poly8x8_t a, poly8x8_t b) { return vsli_n_p8(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly8x8_t shift_right_insert(poly8x8_t a, poly8x8_t b) { return vsri_n_p8(a, b, n); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(poly8x8_t a) { return vreinterpret_s8_p8(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(poly8x8_t a) { return vreinterpret_s16_p8(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(poly8x8_t a) { return vreinterpret_s32_p8(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(poly8x8_t a) { return vreinterpret_f32_p8(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(poly8x8_t a) { return vreinterpret_u8_p8(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(poly8x8_t a) { return vreinterpret_u16_p8(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(poly8x8_t a) { return vreinterpret_u32_p8(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(poly8x8_t a) { return vreinterpret_p16_p8(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(poly8x8_t a) { return vreinterpret_u64_p8(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(poly8x8_t a) { return vreinterpret_s64_p8(a); }
[[gnu::always_inline]] nce poly8x8_t bitwise_not(poly8x8_t a) { return vmvn_p8(a); }
[[gnu::always_inline]] nce poly8x8_t count_active_bits(poly8x8_t a) { return vcnt_p8(a); }
template <int lane>[[gnu::always_inline]] nce poly8x8_t duplicate_lane(poly8x8_t a) { return vdup_lane_p8(a, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x16_t duplicate_lane_quad(poly8x8_t a) { return vdupq_lane_p8(a, lane); }
[[gnu::always_inline]] nce poly8x16_t combine(poly8x8_t low, poly8x8_t high) { return vcombine_p8(low, high); }
template <int lane>[[gnu::always_inline]] nce poly8_t get_lane(poly8x8_t v) { return vget_lane_p8(v, lane); }
template <int n>[[gnu::always_inline]] nce poly8x8_t extract(poly8x8_t a, poly8x8_t b) { return vext_p8(a, b, n); }
[[gnu::always_inline]] nce poly8x8_t reverse_64bit(poly8x8_t a) { return vrev64_p8(a); }
[[gnu::always_inline]] nce poly8x8_t reverse_32bit(poly8x8_t a) { return vrev32_p8(a); }
[[gnu::always_inline]] nce poly8x8_t reverse_16bit(poly8x8_t a) { return vrev16_p8(a); }
[[gnu::always_inline]] nce poly8x8_t table_lookup1(poly8x8_t a, uint8x8_t idx) { return vtbl1_p8(a, idx); }
[[gnu::always_inline]] nce poly8x8x2_t zip(poly8x8_t a, poly8x8_t b) { return vzip_p8(a, b); }
[[gnu::always_inline]] nce poly8x8x2_t unzip(poly8x8_t a, poly8x8_t b) { return vuzp_p8(a, b); }
[[gnu::always_inline]] nce poly8x8x2_t transpose(poly8x8_t a, poly8x8_t b) { return vtrn_p8(a, b); }
[[gnu::always_inline]] nce poly8x8_t table_extension1(poly8x8_t a, poly8x8_t b, uint8x8_t idx) { return vtbx1_p8(a, b, idx); }
#ifdef __clang__
[[gnu::always_inline]] nce poly8x8_t add(poly8x8_t a, poly8x8_t b) { return vadd_p8(a, b); }
#endif
[[gnu::always_inline]] nce poly8x8_t table_extension2(poly8x8_t a, poly8x8x2_t b, uint8x8_t idx) { return vtbx2_p8(a, b, idx); }
[[gnu::always_inline]] nce poly8x8_t table_extension3(poly8x8_t a, poly8x8x3_t b, uint8x8_t idx) { return vtbx3_p8(a, b, idx); }
[[gnu::always_inline]] nce poly8x8_t table_extension4(poly8x8_t a, poly8x8x4_t b, uint8x8_t idx) { return vtbx4_p8(a, b, idx); }
template <int n>[[gnu::always_inline]] nce poly16x4_t shift_left_insert(poly16x4_t a, poly16x4_t b) { return vsli_n_p16(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly16x4_t shift_right_insert(poly16x4_t a, poly16x4_t b) { return vsri_n_p16(a, b, n); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(poly16x4_t a) { return vreinterpret_s8_p16(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(poly16x4_t a) { return vreinterpret_s16_p16(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(poly16x4_t a) { return vreinterpret_s32_p16(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(poly16x4_t a) { return vreinterpret_f32_p16(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(poly16x4_t a) { return vreinterpret_u8_p16(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(poly16x4_t a) { return vreinterpret_u16_p16(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(poly16x4_t a) { return vreinterpret_u32_p16(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(poly16x4_t a) { return vreinterpret_p8_p16(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(poly16x4_t a) { return vreinterpret_u64_p16(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(poly16x4_t a) { return vreinterpret_s64_p16(a); }
template <int lane>[[gnu::always_inline]] nce poly16x4_t duplicate_lane(poly16x4_t a) { return vdup_lane_p16(a, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8_t duplicate_lane_quad(poly16x4_t a) { return vdupq_lane_p16(a, lane); }
[[gnu::always_inline]] nce poly16x8_t combine(poly16x4_t low, poly16x4_t high) { return vcombine_p16(low, high); }
template <int lane>[[gnu::always_inline]] nce poly16_t get_lane(poly16x4_t v) { return vget_lane_p16(v, lane); }
template <int n>[[gnu::always_inline]] nce poly16x4_t extract(poly16x4_t a, poly16x4_t b) { return vext_p16(a, b, n); }
[[gnu::always_inline]] nce poly16x4_t reverse_64bit(poly16x4_t a) { return vrev64_p16(a); }
[[gnu::always_inline]] nce poly16x4_t reverse_32bit(poly16x4_t a) { return vrev32_p16(a); }
[[gnu::always_inline]] nce poly16x4x2_t zip(poly16x4_t a, poly16x4_t b) { return vzip_p16(a, b); }
[[gnu::always_inline]] nce poly16x4x2_t unzip(poly16x4_t a, poly16x4_t b) { return vuzp_p16(a, b); }
[[gnu::always_inline]] nce poly16x4x2_t transpose(poly16x4_t a, poly16x4_t b) { return vtrn_p16(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce poly16x4_t add(poly16x4_t a, poly16x4_t b) { return vadd_p16(a, b); }
#endif
[[gnu::always_inline]] nce int64x1_t add(int64x1_t a, int64x1_t b) { return vadd_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t add(int64x2_t a, int64x2_t b) { return vaddq_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t add(int64x2_t a, int32x2_t b) { return vaddw_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t add_narrow(int64x2_t a, int64x2_t b) { return vaddhn_s64(a, b); }
[[gnu::always_inline]] nce int32x2_t add_round_narrow(int64x2_t a, int64x2_t b) { return vraddhn_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t add_saturate(int64x1_t a, int64x1_t b) { return vqadd_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t add_saturate(int64x2_t a, int64x2_t b) { return vqaddq_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_add_long(int64x2_t a, int32x2_t b, int32x2_t c) { return vmlal_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_subtract_long(int64x2_t a, int32x2_t b, int32x2_t c) { return vmlsl_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long(int64x2_t a, int32x2_t b, int32x2_t c) { return vqdmlal_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long(int64x2_t a, int32x2_t b, int32x2_t c) { return vqdmlsl_s32(a, b, c); }
template <int lane> [[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long_lane(int64x2_t a, int32x2_t b, int32x2_t v) { return vqdmlal_lane_s32(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long_lane(int64x2_t a, int32x2_t b, int32x2_t v) { return vqdmlsl_lane_s32(a, b, v, lane); }
[[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long(int64x2_t a, int32x2_t b, int32_t c) { return vqdmlal_n_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long(int64x2_t a, int32x2_t b, int32_t c) { return vqdmlsl_n_s32(a, b, c); }
[[gnu::always_inline]] nce poly8x16_t multiply(poly8x16_t a, poly8x16_t b) { return vmulq_p8(a, b); }
[[gnu::always_inline]] nce int64x1_t subtract(int64x1_t a, int64x1_t b) { return vsub_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract(int64x2_t a, int64x2_t b) { return vsubq_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract(int64x2_t a, int32x2_t b) { return vsubw_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_narrow(int64x2_t a, int64x2_t b) { return vsubhn_s64(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_round_narrow(int64x2_t a, int64x2_t b) { return vrsubhn_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t subtract_saturate(int64x1_t a, int64x1_t b) { return vqsub_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_saturate(int64x2_t a, int64x2_t b) { return vqsubq_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_absolute_add(int64x2_t a, int32x2_t b, int32x2_t c) { return vabal_s32(a, b, c); }
[[gnu::always_inline]] nce int64x1_t pairwise_add_accumulate_long(int64x1_t a, int32x2_t b) { return vpadal_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t pairwise_add_accumulate_long(int64x2_t a, int32x4_t b) { return vpadalq_s32(a, b); }
[[gnu::always_inline]] nce uint8x16_t equal(poly8x16_t a, poly8x16_t b) { return vceqq_p8(a, b); }
[[gnu::always_inline]] nce uint8x16_t compare_test_nonzero(poly8x16_t a, poly8x16_t b) { return vtstq_p8(a, b); }
[[gnu::always_inline]] nce int64x1_t shift_left(int64x1_t a, int64x1_t b) { return vshl_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t shift_left(int64x2_t a, int64x2_t b) { return vshlq_s64(a, b); }
template <int n>[[gnu::always_inline]] nce int64x1_t shift_left(int64x1_t a) { return vshl_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int64x2_t shift_left(int64x2_t a) { return vshlq_n_s64(a, n); }
[[gnu::always_inline]] nce int64x1_t shift_left_saturate(int64x1_t a, int64x1_t b) { return vqshl_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t shift_left_saturate(int64x2_t a, int64x2_t b) { return vqshlq_s64(a, b); }
template <int n>[[gnu::always_inline]] nce int64x1_t shift_left_saturate(int64x1_t a) { return vqshl_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int64x2_t shift_left_saturate(int64x2_t a) { return vqshlq_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x1_t shift_left_unsigned_saturate(int64x1_t a) { return vqshlu_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_left_unsigned_saturate(int64x2_t a) { return vqshluq_n_s64(a, n); }
[[gnu::always_inline]] nce int64x1_t shift_left_round(int64x1_t a, int64x1_t b) { return vrshl_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t shift_left_round(int64x2_t a, int64x2_t b) { return vrshlq_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t shift_left_round_saturate(int64x1_t a, int64x1_t b) { return vqrshl_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t shift_left_round_saturate(int64x2_t a, int64x2_t b) { return vqrshlq_s64(a, b); }
template <int n>[[gnu::always_inline]] nce int64x1_t shift_left_insert(int64x1_t a, int64x1_t b) { return vsli_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce int64x2_t shift_left_insert(int64x2_t a, int64x2_t b) { return vsliq_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly8x16_t shift_left_insert(poly8x16_t a, poly8x16_t b) { return vsliq_n_p8(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly16x8_t shift_left_insert(poly16x8_t a, poly16x8_t b) { return vsliq_n_p16(a, b, n); }
template <int n>[[gnu::always_inline]] nce int64x1_t shift_right(int64x1_t a) { return vshr_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int64x2_t shift_right(int64x2_t a) { return vshrq_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int64x1_t shift_right_round(int64x1_t a) { return vrshr_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int64x2_t shift_right_round(int64x2_t a) { return vrshrq_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int64x1_t shift_right_accumulate(int64x1_t a, int64x1_t b) { return vsra_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce int64x2_t shift_right_accumulate(int64x2_t a, int64x2_t b) { return vsraq_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce int64x1_t shift_right_accumulate_round(int64x1_t a, int64x1_t b) { return vrsra_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce int64x2_t shift_right_accumulate_round(int64x2_t a, int64x2_t b) { return vrsraq_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right_narrow(int64x2_t a) { return vshrn_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_saturate_narrow_unsigned(int64x2_t a) { return vqshrun_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right_saturate_narrow(int64x2_t a) { return vqshrn_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_round_saturate_narrow_unsigned(int64x2_t a) { return vqrshrun_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right_round_saturate_narrow(int64x2_t a) { return vqrshrn_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right_round_narrow(int64x2_t a) { return vrshrn_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int64x1_t shift_right_insert(int64x1_t a, int64x1_t b) { return vsri_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce int64x2_t shift_right_insert(int64x2_t a, int64x2_t b) { return vsriq_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly8x16_t shift_right_insert(poly8x16_t a, poly8x16_t b) { return vsriq_n_p8(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly16x8_t shift_right_insert(poly16x8_t a, poly16x8_t b) { return vsriq_n_p16(a, b, n); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(int64x1_t a) { return vreinterpret_s8_s64(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(int64x1_t a) { return vreinterpret_s16_s64(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(int64x1_t a) { return vreinterpret_s32_s64(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(int64x1_t a) { return vreinterpret_f32_s64(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(int64x1_t a) { return vreinterpret_u8_s64(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(int64x1_t a) { return vreinterpret_u16_s64(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(int64x1_t a) { return vreinterpret_u32_s64(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(int64x1_t a) { return vreinterpret_p8_s64(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(int64x1_t a) { return vreinterpret_p16_s64(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(int64x1_t a) { return vreinterpret_u64_s64(a); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(poly8x16_t a) { return vreinterpretq_s8_p8(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(poly8x16_t a) { return vreinterpretq_s16_p8(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(poly8x16_t a) { return vreinterpretq_s32_p8(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(poly8x16_t a) { return vreinterpretq_f32_p8(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(poly8x16_t a) { return vreinterpretq_u8_p8(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(poly8x16_t a) { return vreinterpretq_u16_p8(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(poly8x16_t a) { return vreinterpretq_u32_p8(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(poly8x16_t a) { return vreinterpretq_p16_p8(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(poly8x16_t a) { return vreinterpretq_u64_p8(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(poly8x16_t a) { return vreinterpretq_s64_p8(a); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(poly16x8_t a) { return vreinterpretq_s8_p16(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(poly16x8_t a) { return vreinterpretq_s16_p16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(poly16x8_t a) { return vreinterpretq_s32_p16(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(poly16x8_t a) { return vreinterpretq_f32_p16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(poly16x8_t a) { return vreinterpretq_u8_p16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(poly16x8_t a) { return vreinterpretq_u16_p16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(poly16x8_t a) { return vreinterpretq_u32_p16(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(poly16x8_t a) { return vreinterpretq_p8_p16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(poly16x8_t a) { return vreinterpretq_u64_p16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(poly16x8_t a) { return vreinterpretq_s64_p16(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(int64x2_t a) { return vreinterpretq_p8_s64(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(int64x2_t a) { return vreinterpretq_p16_s64(a); }
[[gnu::always_inline]] nce int32x2_t move_narrow(int64x2_t a) { return vmovn_s64(a); }
[[gnu::always_inline]] nce int32x2_t move_saturate_narrow(int64x2_t a) { return vqmovn_s64(a); }
[[gnu::always_inline]] nce uint32x2_t move_unsigned_saturate_narrow(int64x2_t a) { return vqmovun_s64(a); }
template <int lane> [[gnu::always_inline]] nce int64x2_t multiply_add_long_lane(int64x2_t a, int32x2_t b, int32x2_t v) { return vmlal_lane_s32(a, b, v, lane); }
template <int lane> [[gnu::always_inline]] nce int64x2_t multiply_subtract_long_lane(int64x2_t a, int32x2_t b, int32x2_t v) { return vmlsl_lane_s32(a, b, v, lane); }
[[gnu::always_inline]] nce int64x2_t multiply_add_long(int64x2_t a, int32x2_t b, int32_t c) { return vmlal_n_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_subtract_long(int64x2_t a, int32x2_t b, int32_t c) { return vmlsl_n_s32(a, b, c); }
[[gnu::always_inline]] nce poly8x16_t bitwise_not(poly8x16_t a) { return vmvnq_p8(a); }
[[gnu::always_inline]] nce int64x1_t bitwise_and(int64x1_t a, int64x1_t b) { return vand_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t bitwise_and(int64x2_t a, int64x2_t b) { return vandq_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t bitwise_or(int64x1_t a, int64x1_t b) { return vorr_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t bitwise_or(int64x2_t a, int64x2_t b) { return vorrq_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t bitwise_xor(int64x1_t a, int64x1_t b) { return veor_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t bitwise_xor(int64x2_t a, int64x2_t b) { return veorq_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t bitwise_or_not(int64x1_t a, int64x1_t b) { return vorn_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t bitwise_or_not(int64x2_t a, int64x2_t b) { return vornq_s64(a, b); }
[[gnu::always_inline]] nce poly8x16_t count_active_bits(poly8x16_t a) { return vcntq_p8(a); }
[[gnu::always_inline]] nce int64x1_t bitwise_clear(int64x1_t a, int64x1_t b) { return vbic_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t bitwise_clear(int64x2_t a, int64x2_t b) { return vbicq_s64(a, b); }
template <> [[gnu::always_inline]] nce int8x8_t create(uint64_t a) { return vcreate_s8(a); }
template <> [[gnu::always_inline]] nce int16x4_t create(uint64_t a) { return vcreate_s16(a); }
template <> [[gnu::always_inline]] nce int32x2_t create(uint64_t a) { return vcreate_s32(a); }
template <> [[gnu::always_inline]] nce int64x1_t create(uint64_t a) { return vcreate_s64(a); }
template <> [[gnu::always_inline]] nce uint8x8_t create(uint64_t a) { return vcreate_u8(a); }
template <> [[gnu::always_inline]] nce uint16x4_t create(uint64_t a) { return vcreate_u16(a); }
template <> [[gnu::always_inline]] nce uint32x2_t create(uint64_t a) { return vcreate_u32(a); }
template <> [[gnu::always_inline]] nce uint64x1_t create(uint64_t a) { return vcreate_u64(a); }
template <> [[gnu::always_inline]] nce float32x2_t create(uint64_t a) { return vcreate_f32(a); }
template <> [[gnu::always_inline]] nce poly8x8_t create(uint64_t a) { return vcreate_p8(a); }
template <> [[gnu::always_inline]] nce poly16x4_t create(uint64_t a) { return vcreate_p16(a); }
template <> [[gnu::always_inline]] nce int8x8_t duplicate(int8_t value) { return vdup_n_s8(value); }
template <> [[gnu::always_inline]] nce int8x16_t duplicate(int8_t value) { return vdupq_n_s8(value); }
template <> [[gnu::always_inline]] nce int16x4_t duplicate(int16_t value) { return vdup_n_s16(value); }
template <> [[gnu::always_inline]] nce int16x8_t duplicate(int16_t value) { return vdupq_n_s16(value); }
template <> [[gnu::always_inline]] nce int32x2_t duplicate(int32_t value) { return vdup_n_s32(value); }
template <> [[gnu::always_inline]] nce int32x4_t duplicate(int32_t value) { return vdupq_n_s32(value); }
template <> [[gnu::always_inline]] nce int64x1_t duplicate(int64_t value) { return vdup_n_s64(value); }
template <> [[gnu::always_inline]] nce int64x2_t duplicate(int64_t value) { return vdupq_n_s64(value); }
template <> [[gnu::always_inline]] nce uint8x8_t duplicate(uint8_t value) { return vdup_n_u8(value); }
template <> [[gnu::always_inline]] nce uint8x16_t duplicate(uint8_t value) { return vdupq_n_u8(value); }
template <> [[gnu::always_inline]] nce uint16x4_t duplicate(uint16_t value) { return vdup_n_u16(value); }
template <> [[gnu::always_inline]] nce uint16x8_t duplicate(uint16_t value) { return vdupq_n_u16(value); }
template <> [[gnu::always_inline]] nce uint32x2_t duplicate(uint32_t value) { return vdup_n_u32(value); }
template <> [[gnu::always_inline]] nce uint32x4_t duplicate(uint32_t value) { return vdupq_n_u32(value); }
template <> [[gnu::always_inline]] nce uint64x1_t duplicate(uint64_t value) { return vdup_n_u64(value); }
template <> [[gnu::always_inline]] nce uint64x2_t duplicate(uint64_t value) { return vdupq_n_u64(value); }
template <> [[gnu::always_inline]] nce float32x2_t duplicate(float32_t value) { return vdup_n_f32(value); }
template <> [[gnu::always_inline]] nce float32x4_t duplicate(float32_t value) { return vdupq_n_f32(value); }
template <> [[gnu::always_inline]] nce poly8x8_t duplicate(poly8_t value) { return vdup_n_p8(value); }
template <> [[gnu::always_inline]] nce poly8x16_t duplicate(poly8_t value) { return vdupq_n_p8(value); }
template <> [[gnu::always_inline]] nce poly16x4_t duplicate(poly16_t value) { return vdup_n_p16(value); }
template <> [[gnu::always_inline]] nce poly16x8_t duplicate(poly16_t value) { return vdupq_n_p16(value); }
template <int lane>[[gnu::always_inline]] nce int64x1_t duplicate_lane(int64x1_t a) { return vdup_lane_s64(a, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t duplicate_lane_quad(int64x1_t a) { return vdupq_lane_s64(a, lane); }
[[gnu::always_inline]] nce int64x2_t combine(int64x1_t low, int64x1_t high) { return vcombine_s64(low, high); }
[[gnu::always_inline]] nce int64x1_t get_high(int64x2_t a) { return vget_high_s64(a); }
[[gnu::always_inline]] nce poly8x8_t get_high(poly8x16_t a) { return vget_high_p8(a); }
[[gnu::always_inline]] nce poly16x4_t get_high(poly16x8_t a) { return vget_high_p16(a); }
[[gnu::always_inline]] nce int64x1_t get_low(int64x2_t a) { return vget_low_s64(a); }
[[gnu::always_inline]] nce poly8x8_t get_low(poly8x16_t a) { return vget_low_p8(a); }
[[gnu::always_inline]] nce poly16x4_t get_low(poly16x8_t a) { return vget_low_p16(a); }
template <int lane>[[gnu::always_inline]] nce int64_t get_lane(int64x1_t v) { return vget_lane_s64(v, lane); }
template <int lane>[[gnu::always_inline]] nce poly8_t get_lane(poly8x16_t v) { return vgetq_lane_p8(v, lane); }
template <int lane>[[gnu::always_inline]] nce poly16_t get_lane(poly16x8_t v) { return vgetq_lane_p16(v, lane); }
template <int n>[[gnu::always_inline]] nce int64x1_t extract(int64x1_t a, int64x1_t b) { return vext_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce int64x2_t extract(int64x2_t a, int64x2_t b) { return vextq_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly8x16_t extract(poly8x16_t a, poly8x16_t b) { return vextq_p8(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly16x8_t extract(poly16x8_t a, poly16x8_t b) { return vextq_p16(a, b, n); }
[[gnu::always_inline]] nce poly8x16_t reverse_64bit(poly8x16_t a) { return vrev64q_p8(a); }
[[gnu::always_inline]] nce poly16x8_t reverse_64bit(poly16x8_t a) { return vrev64q_p16(a); }
[[gnu::always_inline]] nce poly8x16_t reverse_32bit(poly8x16_t a) { return vrev32q_p8(a); }
[[gnu::always_inline]] nce poly16x8_t reverse_32bit(poly16x8_t a) { return vrev32q_p16(a); }
[[gnu::always_inline]] nce poly8x16_t reverse_16bit(poly8x16_t a) { return vrev16q_p8(a); }
[[gnu::always_inline]] nce poly8x16x2_t zip(poly8x16_t a, poly8x16_t b) { return vzipq_p8(a, b); }
[[gnu::always_inline]] nce poly16x8x2_t zip(poly16x8_t a, poly16x8_t b) { return vzipq_p16(a, b); }
[[gnu::always_inline]] nce poly8x16x2_t unzip(poly8x16_t a, poly8x16_t b) { return vuzpq_p8(a, b); }
[[gnu::always_inline]] nce poly16x8x2_t unzip(poly16x8_t a, poly16x8_t b) { return vuzpq_p16(a, b); }
[[gnu::always_inline]] nce poly8x16x2_t transpose(poly8x16_t a, poly8x16_t b) { return vtrnq_p8(a, b); }
[[gnu::always_inline]] nce poly16x8x2_t transpose(poly16x8_t a, poly16x8_t b) { return vtrnq_p16(a, b); }
template <int lane>[[gnu::always_inline]] nce uint8x8_t set_lane(uint8_t a, uint8x8_t v) { return vset_lane_u8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t set_lane(uint16_t a, uint16x4_t v) { return vset_lane_u16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t set_lane(uint32_t a, uint32x2_t v) { return vset_lane_u32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x1_t set_lane(uint64_t a, uint64x1_t v) { return vset_lane_u64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int8x8_t set_lane(int8_t a, int8x8_t v) { return vset_lane_s8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t set_lane(int16_t a, int16x4_t v) { return vset_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t set_lane(int32_t a, int32x2_t v) { return vset_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x1_t set_lane(int64_t a, int64x1_t v) { return vset_lane_s64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8_t set_lane(poly8_t a, poly8x8_t v) { return vset_lane_p8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4_t set_lane(poly16_t a, poly16x4_t v) { return vset_lane_p16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t set_lane(float32_t a, float32x2_t v) { return vset_lane_f32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x16_t set_lane(poly8_t a, poly8x16_t v) { return vsetq_lane_p8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8_t set_lane(poly16_t a, poly16x8_t v) { return vsetq_lane_p16(a, v, lane); }
template <> [[gnu::always_inline]] inline int8x8_t load1(int8_t const *ptr) { return vld1_s8(ptr); }
template <> [[gnu::always_inline]] inline int8x16_t load1(int8_t const *ptr) { return vld1q_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x4_t load1(int16_t const *ptr) { return vld1_s16(ptr); }
template <> [[gnu::always_inline]] inline int16x8_t load1(int16_t const *ptr) { return vld1q_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x2_t load1(int32_t const *ptr) { return vld1_s32(ptr); }
template <> [[gnu::always_inline]] inline int32x4_t load1(int32_t const *ptr) { return vld1q_s32(ptr); }
template <> [[gnu::always_inline]] inline int64x1_t load1(int64_t const *ptr) { return vld1_s64(ptr); }
template <> [[gnu::always_inline]] inline int64x2_t load1(int64_t const *ptr) { return vld1q_s64(ptr); }
template <> [[gnu::always_inline]] inline uint8x8_t load1(uint8_t const *ptr) { return vld1_u8(ptr); }
template <> [[gnu::always_inline]] inline uint8x16_t load1(uint8_t const *ptr) { return vld1q_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x4_t load1(uint16_t const *ptr) { return vld1_u16(ptr); }
template <> [[gnu::always_inline]] inline uint16x8_t load1(uint16_t const *ptr) { return vld1q_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x2_t load1(uint32_t const *ptr) { return vld1_u32(ptr); }
template <> [[gnu::always_inline]] inline uint32x4_t load1(uint32_t const *ptr) { return vld1q_u32(ptr); }
template <> [[gnu::always_inline]] inline uint64x1_t load1(uint64_t const *ptr) { return vld1_u64(ptr); }
template <> [[gnu::always_inline]] inline uint64x2_t load1(uint64_t const *ptr) { return vld1q_u64(ptr); }
template <> [[gnu::always_inline]] inline float32x2_t load1(float32_t const *ptr) { return vld1_f32(ptr); }
template <> [[gnu::always_inline]] inline float32x4_t load1(float32_t const *ptr) { return vld1q_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x8_t load1(poly8_t const *ptr) { return vld1_p8(ptr); }
template <> [[gnu::always_inline]] inline poly8x16_t load1(poly8_t const *ptr) { return vld1q_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x4_t load1(poly16_t const *ptr) { return vld1_p16(ptr); }
template <> [[gnu::always_inline]] inline poly16x8_t load1(poly16_t const *ptr) { return vld1q_p16(ptr); }
template <int lane>[[gnu::always_inline]] nce int8x8_t load1_lane(int8_t const *ptr, int8x8_t src) { return vld1_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16_t load1_lane_quad(int8_t const *ptr, int8x16_t src) { return vld1q_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t load1_lane(int16_t const *ptr, int16x4_t src) { return vld1_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t load1_lane_quad(int16_t const *ptr, int16x8_t src) { return vld1q_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t load1_lane(int32_t const *ptr, int32x2_t src) { return vld1_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t load1_lane_quad(int32_t const *ptr, int32x4_t src) { return vld1q_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x1_t load1_lane(int64_t const *ptr, int64x1_t src) { return vld1_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t load1_lane_quad(int64_t const *ptr, int64x2_t src) { return vld1q_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x8_t load1_lane(uint8_t const *ptr, uint8x8_t src) { return vld1_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16_t load1_lane_quad(uint8_t const *ptr, uint8x16_t src) { return vld1q_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t load1_lane(uint16_t const *ptr, uint16x4_t src) { return vld1_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t load1_lane_quad(uint16_t const *ptr, uint16x8_t src) { return vld1q_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t load1_lane(uint32_t const *ptr, uint32x2_t src) { return vld1_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t load1_lane_quad(uint32_t const *ptr, uint32x4_t src) { return vld1q_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x1_t load1_lane(uint64_t const *ptr, uint64x1_t src) { return vld1_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t load1_lane_quad(uint64_t const *ptr, uint64x2_t src) { return vld1q_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t load1_lane(float32_t const *ptr, float32x2_t src) { return vld1_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t load1_lane_quad(float32_t const *ptr, float32x4_t src) { return vld1q_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8_t load1_lane(poly8_t const *ptr, poly8x8_t src) { return vld1_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x16_t load1_lane_quad(poly8_t const *ptr, poly8x16_t src) { return vld1q_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4_t load1_lane(poly16_t const *ptr, poly16x4_t src) { return vld1_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8_t load1_lane_quad(poly16_t const *ptr, poly16x8_t src) { return vld1q_lane_p16(ptr, src, lane); }
template <> [[gnu::always_inline]] inline int8x8_t load1_duplicate(int8_t const *ptr) { return vld1_dup_s8(ptr); }
template <> [[gnu::always_inline]] inline int8x16_t load1_duplicate(int8_t const *ptr) { return vld1q_dup_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x4_t load1_duplicate(int16_t const *ptr) { return vld1_dup_s16(ptr); }
template <> [[gnu::always_inline]] inline int16x8_t load1_duplicate(int16_t const *ptr) { return vld1q_dup_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x2_t load1_duplicate(int32_t const *ptr) { return vld1_dup_s32(ptr); }
template <> [[gnu::always_inline]] inline int32x4_t load1_duplicate(int32_t const *ptr) { return vld1q_dup_s32(ptr); }
template <> [[gnu::always_inline]] inline int64x1_t load1_duplicate(int64_t const *ptr) { return vld1_dup_s64(ptr); }
template <> [[gnu::always_inline]] inline int64x2_t load1_duplicate(int64_t const *ptr) { return vld1q_dup_s64(ptr); }
template <> [[gnu::always_inline]] inline uint8x8_t load1_duplicate(uint8_t const *ptr) { return vld1_dup_u8(ptr); }
template <> [[gnu::always_inline]] inline uint8x16_t load1_duplicate(uint8_t const *ptr) { return vld1q_dup_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x4_t load1_duplicate(uint16_t const *ptr) { return vld1_dup_u16(ptr); }
template <> [[gnu::always_inline]] inline uint16x8_t load1_duplicate(uint16_t const *ptr) { return vld1q_dup_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x2_t load1_duplicate(uint32_t const *ptr) { return vld1_dup_u32(ptr); }
template <> [[gnu::always_inline]] inline uint32x4_t load1_duplicate(uint32_t const *ptr) { return vld1q_dup_u32(ptr); }
template <> [[gnu::always_inline]] inline uint64x1_t load1_duplicate(uint64_t const *ptr) { return vld1_dup_u64(ptr); }
template <> [[gnu::always_inline]] inline uint64x2_t load1_duplicate(uint64_t const *ptr) { return vld1q_dup_u64(ptr); }
template <> [[gnu::always_inline]] inline float32x2_t load1_duplicate(float32_t const *ptr) { return vld1_dup_f32(ptr); }
template <> [[gnu::always_inline]] inline float32x4_t load1_duplicate(float32_t const *ptr) { return vld1q_dup_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x8_t load1_duplicate(poly8_t const *ptr) { return vld1_dup_p8(ptr); }
template <> [[gnu::always_inline]] inline poly8x16_t load1_duplicate(poly8_t const *ptr) { return vld1q_dup_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x4_t load1_duplicate(poly16_t const *ptr) { return vld1_dup_p16(ptr); }
template <> [[gnu::always_inline]] inline poly16x8_t load1_duplicate(poly16_t const *ptr) { return vld1q_dup_p16(ptr); }
template <> [[gnu::always_inline]] inline int8x8x2_t load2(int8_t const *ptr) { return vld2_s8(ptr); }
template <> [[gnu::always_inline]] inline int8x16x2_t load2(int8_t const *ptr) { return vld2q_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x4x2_t load2(int16_t const *ptr) { return vld2_s16(ptr); }
template <> [[gnu::always_inline]] inline int16x8x2_t load2(int16_t const *ptr) { return vld2q_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x2x2_t load2(int32_t const *ptr) { return vld2_s32(ptr); }
template <> [[gnu::always_inline]] inline int32x4x2_t load2(int32_t const *ptr) { return vld2q_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x2_t load2(uint8_t const *ptr) { return vld2_u8(ptr); }
template <> [[gnu::always_inline]] inline uint8x16x2_t load2(uint8_t const *ptr) { return vld2q_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x2_t load2(uint16_t const *ptr) { return vld2_u16(ptr); }
template <> [[gnu::always_inline]] inline uint16x8x2_t load2(uint16_t const *ptr) { return vld2q_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x2_t load2(uint32_t const *ptr) { return vld2_u32(ptr); }
template <> [[gnu::always_inline]] inline uint32x4x2_t load2(uint32_t const *ptr) { return vld2q_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x2x2_t load2(float32_t const *ptr) { return vld2_f32(ptr); }
template <> [[gnu::always_inline]] inline float32x4x2_t load2(float32_t const *ptr) { return vld2q_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x2_t load2(poly8_t const *ptr) { return vld2_p8(ptr); }
template <> [[gnu::always_inline]] inline poly8x16x2_t load2(poly8_t const *ptr) { return vld2q_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x2_t load2(poly16_t const *ptr) { return vld2_p16(ptr); }
template <> [[gnu::always_inline]] inline poly16x8x2_t load2(poly16_t const *ptr) { return vld2q_p16(ptr); }
template <> [[gnu::always_inline]] inline int64x1x2_t load2(int64_t const *ptr) { return vld2_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x1x2_t load2(uint64_t const *ptr) { return vld2_u64(ptr); }
template <> [[gnu::always_inline]] inline int8x8x3_t load3(int8_t const *ptr) { return vld3_s8(ptr); }
template <> [[gnu::always_inline]] inline int8x16x3_t load3(int8_t const *ptr) { return vld3q_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x4x3_t load3(int16_t const *ptr) { return vld3_s16(ptr); }
template <> [[gnu::always_inline]] inline int16x8x3_t load3(int16_t const *ptr) { return vld3q_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x2x3_t load3(int32_t const *ptr) { return vld3_s32(ptr); }
template <> [[gnu::always_inline]] inline int32x4x3_t load3(int32_t const *ptr) { return vld3q_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x3_t load3(uint8_t const *ptr) { return vld3_u8(ptr); }
template <> [[gnu::always_inline]] inline uint8x16x3_t load3(uint8_t const *ptr) { return vld3q_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x3_t load3(uint16_t const *ptr) { return vld3_u16(ptr); }
template <> [[gnu::always_inline]] inline uint16x8x3_t load3(uint16_t const *ptr) { return vld3q_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x3_t load3(uint32_t const *ptr) { return vld3_u32(ptr); }
template <> [[gnu::always_inline]] inline uint32x4x3_t load3(uint32_t const *ptr) { return vld3q_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x2x3_t load3(float32_t const *ptr) { return vld3_f32(ptr); }
template <> [[gnu::always_inline]] inline float32x4x3_t load3(float32_t const *ptr) { return vld3q_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x3_t load3(poly8_t const *ptr) { return vld3_p8(ptr); }
template <> [[gnu::always_inline]] inline poly8x16x3_t load3(poly8_t const *ptr) { return vld3q_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x3_t load3(poly16_t const *ptr) { return vld3_p16(ptr); }
template <> [[gnu::always_inline]] inline poly16x8x3_t load3(poly16_t const *ptr) { return vld3q_p16(ptr); }
template <> [[gnu::always_inline]] inline int64x1x3_t load3(int64_t const *ptr) { return vld3_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x1x3_t load3(uint64_t const *ptr) { return vld3_u64(ptr); }
template <> [[gnu::always_inline]] inline int8x8x4_t load4(int8_t const *ptr) { return vld4_s8(ptr); }
template <> [[gnu::always_inline]] inline int8x16x4_t load4(int8_t const *ptr) { return vld4q_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x4x4_t load4(int16_t const *ptr) { return vld4_s16(ptr); }
template <> [[gnu::always_inline]] inline int16x8x4_t load4(int16_t const *ptr) { return vld4q_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x2x4_t load4(int32_t const *ptr) { return vld4_s32(ptr); }
template <> [[gnu::always_inline]] inline int32x4x4_t load4(int32_t const *ptr) { return vld4q_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x4_t load4(uint8_t const *ptr) { return vld4_u8(ptr); }
template <> [[gnu::always_inline]] inline uint8x16x4_t load4(uint8_t const *ptr) { return vld4q_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x4_t load4(uint16_t const *ptr) { return vld4_u16(ptr); }
template <> [[gnu::always_inline]] inline uint16x8x4_t load4(uint16_t const *ptr) { return vld4q_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x4_t load4(uint32_t const *ptr) { return vld4_u32(ptr); }
template <> [[gnu::always_inline]] inline uint32x4x4_t load4(uint32_t const *ptr) { return vld4q_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x2x4_t load4(float32_t const *ptr) { return vld4_f32(ptr); }
template <> [[gnu::always_inline]] inline float32x4x4_t load4(float32_t const *ptr) { return vld4q_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x4_t load4(poly8_t const *ptr) { return vld4_p8(ptr); }
template <> [[gnu::always_inline]] inline poly8x16x4_t load4(poly8_t const *ptr) { return vld4q_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x4_t load4(poly16_t const *ptr) { return vld4_p16(ptr); }
template <> [[gnu::always_inline]] inline poly16x8x4_t load4(poly16_t const *ptr) { return vld4q_p16(ptr); }
template <> [[gnu::always_inline]] inline int64x1x4_t load4(int64_t const *ptr) { return vld4_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x1x4_t load4(uint64_t const *ptr) { return vld4_u64(ptr); }
template <> [[gnu::always_inline]] inline int8x8x2_t load2_duplicate(int8_t const *ptr) { return vld2_dup_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x4x2_t load2_duplicate(int16_t const *ptr) { return vld2_dup_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x2x2_t load2_duplicate(int32_t const *ptr) { return vld2_dup_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x2_t load2_duplicate(uint8_t const *ptr) { return vld2_dup_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x2_t load2_duplicate(uint16_t const *ptr) { return vld2_dup_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x2_t load2_duplicate(uint32_t const *ptr) { return vld2_dup_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x2x2_t load2_duplicate(float32_t const *ptr) { return vld2_dup_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x2_t load2_duplicate(poly8_t const *ptr) { return vld2_dup_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x2_t load2_duplicate(poly16_t const *ptr) { return vld2_dup_p16(ptr); }
template <> [[gnu::always_inline]] inline int64x1x2_t load2_duplicate(int64_t const *ptr) { return vld2_dup_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x1x2_t load2_duplicate(uint64_t const *ptr) { return vld2_dup_u64(ptr); }
template <> [[gnu::always_inline]] inline int8x8x3_t load3_duplicate(int8_t const *ptr) { return vld3_dup_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x4x3_t load3_duplicate(int16_t const *ptr) { return vld3_dup_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x2x3_t load3_duplicate(int32_t const *ptr) { return vld3_dup_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x3_t load3_duplicate(uint8_t const *ptr) { return vld3_dup_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x3_t load3_duplicate(uint16_t const *ptr) { return vld3_dup_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x3_t load3_duplicate(uint32_t const *ptr) { return vld3_dup_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x2x3_t load3_duplicate(float32_t const *ptr) { return vld3_dup_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x3_t load3_duplicate(poly8_t const *ptr) { return vld3_dup_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x3_t load3_duplicate(poly16_t const *ptr) { return vld3_dup_p16(ptr); }
template <> [[gnu::always_inline]] inline int64x1x3_t load3_duplicate(int64_t const *ptr) { return vld3_dup_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x1x3_t load3_duplicate(uint64_t const *ptr) { return vld3_dup_u64(ptr); }
template <> [[gnu::always_inline]] inline int8x8x4_t load4_duplicate(int8_t const *ptr) { return vld4_dup_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x4x4_t load4_duplicate(int16_t const *ptr) { return vld4_dup_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x2x4_t load4_duplicate(int32_t const *ptr) { return vld4_dup_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x4_t load4_duplicate(uint8_t const *ptr) { return vld4_dup_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x4_t load4_duplicate(uint16_t const *ptr) { return vld4_dup_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x4_t load4_duplicate(uint32_t const *ptr) { return vld4_dup_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x2x4_t load4_duplicate(float32_t const *ptr) { return vld4_dup_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x4_t load4_duplicate(poly8_t const *ptr) { return vld4_dup_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x4_t load4_duplicate(poly16_t const *ptr) { return vld4_dup_p16(ptr); }
#ifdef __clang__
template <> [[gnu::always_inline]] inline int8x16x2_t load2_duplicate(int8_t const *ptr) { return vld2q_dup_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x8x2_t load2_duplicate(int16_t const *ptr) { return vld2q_dup_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x4x2_t load2_duplicate(int32_t const *ptr) { return vld2q_dup_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x16x2_t load2_duplicate(uint8_t const *ptr) { return vld2q_dup_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x8x2_t load2_duplicate(uint16_t const *ptr) { return vld2q_dup_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x4x2_t load2_duplicate(uint32_t const *ptr) { return vld2q_dup_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x4x2_t load2_duplicate(float32_t const *ptr) { return vld2q_dup_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x16x2_t load2_duplicate(poly8_t const *ptr) { return vld2q_dup_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x8x2_t load2_duplicate(poly16_t const *ptr) { return vld2q_dup_p16(ptr); }
template <> [[gnu::always_inline]] inline int8x16x3_t load3_duplicate(int8_t const *ptr) { return vld3q_dup_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x8x3_t load3_duplicate(int16_t const *ptr) { return vld3q_dup_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x4x3_t load3_duplicate(int32_t const *ptr) { return vld3q_dup_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x16x3_t load3_duplicate(uint8_t const *ptr) { return vld3q_dup_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x8x3_t load3_duplicate(uint16_t const *ptr) { return vld3q_dup_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x4x3_t load3_duplicate(uint32_t const *ptr) { return vld3q_dup_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x4x3_t load3_duplicate(float32_t const *ptr) { return vld3q_dup_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x16x3_t load3_duplicate(poly8_t const *ptr) { return vld3q_dup_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x8x3_t load3_duplicate(poly16_t const *ptr) { return vld3q_dup_p16(ptr); }
template <> [[gnu::always_inline]] inline int8x16x4_t load4_duplicate(int8_t const *ptr) { return vld4q_dup_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x8x4_t load4_duplicate(int16_t const *ptr) { return vld4q_dup_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x4x4_t load4_duplicate(int32_t const *ptr) { return vld4q_dup_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x16x4_t load4_duplicate(uint8_t const *ptr) { return vld4q_dup_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x8x4_t load4_duplicate(uint16_t const *ptr) { return vld4q_dup_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x4x4_t load4_duplicate(uint32_t const *ptr) { return vld4q_dup_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x4x4_t load4_duplicate(float32_t const *ptr) { return vld4q_dup_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x16x4_t load4_duplicate(poly8_t const *ptr) { return vld4q_dup_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x8x4_t load4_duplicate(poly16_t const *ptr) { return vld4q_dup_p16(ptr); }
#endif
[[gnu::always_inline]] inline int64x1x4_t load4_duplicate(int64_t const *ptr) { return vld4_dup_s64(ptr); }
[[gnu::always_inline]] inline uint64x1x4_t load4_duplicate(uint64_t const *ptr) { return vld4_dup_u64(ptr); }
template <int lane>[[gnu::always_inline]] nce int16x4x2_t load2_lane(int16_t const *ptr, int16x4x2_t src) { return vld2_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8x2_t load2_lane_quad(int16_t const *ptr, int16x8x2_t src) { return vld2q_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2x2_t load2_lane(int32_t const *ptr, int32x2x2_t src) { return vld2_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4x2_t load2_lane_quad(int32_t const *ptr, int32x4x2_t src) { return vld2q_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4x2_t load2_lane(uint16_t const *ptr, uint16x4x2_t src) { return vld2_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8x2_t load2_lane_quad(uint16_t const *ptr, uint16x8x2_t src) { return vld2q_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2x2_t load2_lane(uint32_t const *ptr, uint32x2x2_t src) { return vld2_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4x2_t load2_lane_quad(uint32_t const *ptr, uint32x4x2_t src) { return vld2q_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2x2_t load2_lane(float32_t const *ptr, float32x2x2_t src) { return vld2_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4x2_t load2_lane_quad(float32_t const *ptr, float32x4x2_t src) { return vld2q_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4x2_t load2_lane(poly16_t const *ptr, poly16x4x2_t src) { return vld2_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8x2_t load2_lane_quad(poly16_t const *ptr, poly16x8x2_t src) { return vld2q_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x8x2_t load2_lane(int8_t const *ptr, int8x8x2_t src) { return vld2_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x8x2_t load2_lane(uint8_t const *ptr, uint8x8x2_t src) { return vld2_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8x2_t load2_lane(poly8_t const *ptr, poly8x8x2_t src) { return vld2_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4x3_t load3_lane(int16_t const *ptr, int16x4x3_t src) { return vld3_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8x3_t load3_lane_quad(int16_t const *ptr, int16x8x3_t src) { return vld3q_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2x3_t load3_lane(int32_t const *ptr, int32x2x3_t src) { return vld3_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4x3_t load3_lane_quad(int32_t const *ptr, int32x4x3_t src) { return vld3q_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4x3_t load3_lane(uint16_t const *ptr, uint16x4x3_t src) { return vld3_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8x3_t load3_lane_quad(uint16_t const *ptr, uint16x8x3_t src) { return vld3q_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2x3_t load3_lane(uint32_t const *ptr, uint32x2x3_t src) { return vld3_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4x3_t load3_lane_quad(uint32_t const *ptr, uint32x4x3_t src) { return vld3q_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2x3_t load3_lane(float32_t const *ptr, float32x2x3_t src) { return vld3_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4x3_t load3_lane_quad(float32_t const *ptr, float32x4x3_t src) { return vld3q_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4x3_t load3_lane(poly16_t const *ptr, poly16x4x3_t src) { return vld3_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8x3_t load3_lane_quad(poly16_t const *ptr, poly16x8x3_t src) { return vld3q_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x8x3_t load3_lane(int8_t const *ptr, int8x8x3_t src) { return vld3_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x8x3_t load3_lane(uint8_t const *ptr, uint8x8x3_t src) { return vld3_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8x3_t load3_lane(poly8_t const *ptr, poly8x8x3_t src) { return vld3_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4x4_t load4_lane(int16_t const *ptr, int16x4x4_t src) { return vld4_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8x4_t load4_lane_quad(int16_t const *ptr, int16x8x4_t src) { return vld4q_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2x4_t load4_lane(int32_t const *ptr, int32x2x4_t src) { return vld4_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4x4_t load4_lane_quad(int32_t const *ptr, int32x4x4_t src) { return vld4q_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4x4_t load4_lane(uint16_t const *ptr, uint16x4x4_t src) { return vld4_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8x4_t load4_lane_quad(uint16_t const *ptr, uint16x8x4_t src) { return vld4q_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2x4_t load4_lane(uint32_t const *ptr, uint32x2x4_t src) { return vld4_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4x4_t load4_lane_quad(uint32_t const *ptr, uint32x4x4_t src) { return vld4q_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2x4_t load4_lane(float32_t const *ptr, float32x2x4_t src) { return vld4_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4x4_t load4_lane_quad(float32_t const *ptr, float32x4x4_t src) { return vld4q_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4x4_t load4_lane(poly16_t const *ptr, poly16x4x4_t src) { return vld4_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8x4_t load4_lane_quad(poly16_t const *ptr, poly16x8x4_t src) { return vld4q_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x8x4_t load4_lane(int8_t const *ptr, int8x8x4_t src) { return vld4_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x8x4_t load4_lane(uint8_t const *ptr, uint8x8x4_t src) { return vld4_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8x4_t load4_lane(poly8_t const *ptr, poly8x8x4_t src) { return vld4_lane_p8(ptr, src, lane); }
#ifdef __clang__
template <int lane>[[gnu::always_inline]] nce int8x16x2_t load2_lane_quad(int8_t const *ptr, int8x16x2_t src) { return vld2q_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16x2_t load2_lane_quad(uint8_t const *ptr, uint8x16x2_t src) { return vld2q_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16x3_t load3_lane_quad(int8_t const *ptr, int8x16x3_t src) { return vld3q_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16x3_t load3_lane_quad(uint8_t const *ptr, uint8x16x3_t src) { return vld3q_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16x4_t load4_lane_quad(int8_t const *ptr, int8x16x4_t src) { return vld4q_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16x4_t load4_lane_quad(uint8_t const *ptr, uint8x16x4_t src) { return vld4q_lane_u8(ptr, src, lane); }
#endif
template <> [[gnu::always_inline]] inline int8x8x2_t load1_x2(int8_t const *ptr) { return vld1_s8_x2(ptr); }
template <> [[gnu::always_inline]] inline int8x16x2_t load1_x2(int8_t const *ptr) { return vld1q_s8_x2(ptr); }
template <> [[gnu::always_inline]] inline int16x4x2_t load1_x2(int16_t const *ptr) { return vld1_s16_x2(ptr); }
template <> [[gnu::always_inline]] inline int16x8x2_t load1_x2(int16_t const *ptr) { return vld1q_s16_x2(ptr); }
template <> [[gnu::always_inline]] inline int32x2x2_t load1_x2(int32_t const *ptr) { return vld1_s32_x2(ptr); }
template <> [[gnu::always_inline]] inline int32x4x2_t load1_x2(int32_t const *ptr) { return vld1q_s32_x2(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x2_t load1_x2(uint8_t const *ptr) { return vld1_u8_x2(ptr); }
template <> [[gnu::always_inline]] inline uint8x16x2_t load1_x2(uint8_t const *ptr) { return vld1q_u8_x2(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x2_t load1_x2(uint16_t const *ptr) { return vld1_u16_x2(ptr); }
template <> [[gnu::always_inline]] inline uint16x8x2_t load1_x2(uint16_t const *ptr) { return vld1q_u16_x2(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x2_t load1_x2(uint32_t const *ptr) { return vld1_u32_x2(ptr); }
template <> [[gnu::always_inline]] inline uint32x4x2_t load1_x2(uint32_t const *ptr) { return vld1q_u32_x2(ptr); }
template <> [[gnu::always_inline]] inline float32x2x2_t load1_x2(float32_t const *ptr) { return vld1_f32_x2(ptr); }
template <> [[gnu::always_inline]] inline float32x4x2_t load1_x2(float32_t const *ptr) { return vld1q_f32_x2(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x2_t load1_x2(poly8_t const *ptr) { return vld1_p8_x2(ptr); }
template <> [[gnu::always_inline]] inline poly8x16x2_t load1_x2(poly8_t const *ptr) { return vld1q_p8_x2(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x2_t load1_x2(poly16_t const *ptr) { return vld1_p16_x2(ptr); }
template <> [[gnu::always_inline]] inline poly16x8x2_t load1_x2(poly16_t const *ptr) { return vld1q_p16_x2(ptr); }
template <> [[gnu::always_inline]] inline int64x1x2_t load1_x2(int64_t const *ptr) { return vld1_s64_x2(ptr); }
template <> [[gnu::always_inline]] inline uint64x1x2_t load1_x2(uint64_t const *ptr) { return vld1_u64_x2(ptr); }
template <> [[gnu::always_inline]] inline int64x2x2_t load1_x2(int64_t const *ptr) { return vld1q_s64_x2(ptr); }
template <> [[gnu::always_inline]] inline uint64x2x2_t load1_x2(uint64_t const *ptr) { return vld1q_u64_x2(ptr); }
template <> [[gnu::always_inline]] inline int8x8x3_t load1_x3(int8_t const *ptr) { return vld1_s8_x3(ptr); }
template <> [[gnu::always_inline]] inline int16x4x3_t load1_x3(int16_t const *ptr) { return vld1_s16_x3(ptr); }

#if defined(__GNUC__) && __GNUC__ == 14 && (__ARM_ARCH < 8)
template <> [[gnu::always_inline]] inline int8x16x3_t load1_x3(int8_t const *ptr) { return vld1q_s8_x3((const uint8_t*)ptr); }
template <> [[gnu::always_inline]] inline int16x8x3_t load1_x3(int16_t const *ptr) { return vld1q_s16_x3((const uint16_t*)ptr); }
#else
template <> [[gnu::always_inline]] inline int8x16x3_t load1_x3(int8_t const *ptr) { return vld1q_s8_x3(ptr); }
template <> [[gnu::always_inline]] inline int16x8x3_t load1_x3(int16_t const *ptr) { return vld1q_s16_x3(ptr); }
#endif

template <> [[gnu::always_inline]] inline int32x2x3_t load1_x3(int32_t const *ptr) { return vld1_s32_x3(ptr); }
template <> [[gnu::always_inline]] inline int32x4x3_t load1_x3(int32_t const *ptr) { return vld1q_s32_x3(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x3_t load1_x3(uint8_t const *ptr) { return vld1_u8_x3(ptr); }
template <> [[gnu::always_inline]] inline uint8x16x3_t load1_x3(uint8_t const *ptr) { return vld1q_u8_x3(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x3_t load1_x3(uint16_t const *ptr) { return vld1_u16_x3(ptr); }
template <> [[gnu::always_inline]] inline uint16x8x3_t load1_x3(uint16_t const *ptr) { return vld1q_u16_x3(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x3_t load1_x3(uint32_t const *ptr) { return vld1_u32_x3(ptr); }
template <> [[gnu::always_inline]] inline uint32x4x3_t load1_x3(uint32_t const *ptr) { return vld1q_u32_x3(ptr); }
template <> [[gnu::always_inline]] inline float32x2x3_t load1_x3(float32_t const *ptr) { return vld1_f32_x3(ptr); }
template <> [[gnu::always_inline]] inline float32x4x3_t load1_x3(float32_t const *ptr) { return vld1q_f32_x3(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x3_t load1_x3(poly8_t const *ptr) { return vld1_p8_x3(ptr); }
template <> [[gnu::always_inline]] inline poly8x16x3_t load1_x3(poly8_t const *ptr) { return vld1q_p8_x3(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x3_t load1_x3(poly16_t const *ptr) { return vld1_p16_x3(ptr); }
template <> [[gnu::always_inline]] inline poly16x8x3_t load1_x3(poly16_t const *ptr) { return vld1q_p16_x3(ptr); }
template <> [[gnu::always_inline]] inline int64x1x3_t load1_x3(int64_t const *ptr) { return vld1_s64_x3(ptr); }
template <> [[gnu::always_inline]] inline uint64x1x3_t load1_x3(uint64_t const *ptr) { return vld1_u64_x3(ptr); }
template <> [[gnu::always_inline]] inline int64x2x3_t load1_x3(int64_t const *ptr) { return vld1q_s64_x3(ptr); }
template <> [[gnu::always_inline]] inline uint64x2x3_t load1_x3(uint64_t const *ptr) { return vld1q_u64_x3(ptr); }
template <> [[gnu::always_inline]] inline int8x8x4_t load1_x4(int8_t const *ptr) { return vld1_s8_x4(ptr); }

#if defined(__GNUC__) && __GNUC__ == 14 && (__ARM_ARCH < 8)
template <> [[gnu::always_inline]] inline int8x16x4_t load1_x4(int8_t const *ptr) { return vld1q_s8_x4((const uint8_t*)ptr); }
template <> [[gnu::always_inline]] inline int16x8x4_t load1_x4(int16_t const *ptr) { return vld1q_s16_x4((const uint16_t*)ptr); }
#else
template <> [[gnu::always_inline]] inline int8x16x4_t load1_x4(int8_t const *ptr) { return vld1q_s8_x4(ptr); }
template <> [[gnu::always_inline]] inline int16x8x4_t load1_x4(int16_t const *ptr) { return vld1q_s16_x4(ptr); }
#endif

template <> [[gnu::always_inline]] inline int16x4x4_t load1_x4(int16_t const *ptr) { return vld1_s16_x4(ptr); }
template <> [[gnu::always_inline]] inline int32x2x4_t load1_x4(int32_t const *ptr) { return vld1_s32_x4(ptr); }
template <> [[gnu::always_inline]] inline int32x4x4_t load1_x4(int32_t const *ptr) { return vld1q_s32_x4(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x4_t load1_x4(uint8_t const *ptr) { return vld1_u8_x4(ptr); }
template <> [[gnu::always_inline]] inline uint8x16x4_t load1_x4(uint8_t const *ptr) { return vld1q_u8_x4(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x4_t load1_x4(uint16_t const *ptr) { return vld1_u16_x4(ptr); }
template <> [[gnu::always_inline]] inline uint16x8x4_t load1_x4(uint16_t const *ptr) { return vld1q_u16_x4(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x4_t load1_x4(uint32_t const *ptr) { return vld1_u32_x4(ptr); }
template <> [[gnu::always_inline]] inline uint32x4x4_t load1_x4(uint32_t const *ptr) { return vld1q_u32_x4(ptr); }
template <> [[gnu::always_inline]] inline float32x2x4_t load1_x4(float32_t const *ptr) { return vld1_f32_x4(ptr); }
template <> [[gnu::always_inline]] inline float32x4x4_t load1_x4(float32_t const *ptr) { return vld1q_f32_x4(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x4_t load1_x4(poly8_t const *ptr) { return vld1_p8_x4(ptr); }
template <> [[gnu::always_inline]] inline poly8x16x4_t load1_x4(poly8_t const *ptr) { return vld1q_p8_x4(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x4_t load1_x4(poly16_t const *ptr) { return vld1_p16_x4(ptr); }
template <> [[gnu::always_inline]] inline poly16x8x4_t load1_x4(poly16_t const *ptr) { return vld1q_p16_x4(ptr); }
template <> [[gnu::always_inline]] inline int64x1x4_t load1_x4(int64_t const *ptr) { return vld1_s64_x4(ptr); }
template <> [[gnu::always_inline]] inline uint64x1x4_t load1_x4(uint64_t const *ptr) { return vld1_u64_x4(ptr); }
template <> [[gnu::always_inline]] inline int64x2x4_t load1_x4(int64_t const *ptr) { return vld1q_s64_x4(ptr); }
template <> [[gnu::always_inline]] inline uint64x2x4_t load1_x4(uint64_t const *ptr) { return vld1q_u64_x4(ptr); }
[[gnu::always_inline]] inline void store1(int8_t *ptr, int8x8_t val) { return vst1_s8(ptr, val); }
[[gnu::always_inline]] inline void store1(int16_t *ptr, int16x4_t val) { return vst1_s16(ptr, val); }
[[gnu::always_inline]] inline void store1(int32_t *ptr, int32x2_t val) { return vst1_s32(ptr, val); }
[[gnu::always_inline]] inline void store1(int64_t *ptr, int64x1_t val) { return vst1_s64(ptr, val); }
[[gnu::always_inline]] inline void store1(int64_t *ptr, int64x2_t val) { return vst1q_s64(ptr, val); }
[[gnu::always_inline]] inline void store1(uint8_t *ptr, uint8x8_t val) { return vst1_u8(ptr, val); }
[[gnu::always_inline]] inline void store1(uint16_t *ptr, uint16x4_t val) { return vst1_u16(ptr, val); }
[[gnu::always_inline]] inline void store1(uint32_t *ptr, uint32x2_t val) { return vst1_u32(ptr, val); }
[[gnu::always_inline]] inline void store1(uint64_t *ptr, uint64x1_t val) { return vst1_u64(ptr, val); }
[[gnu::always_inline]] inline void store1(uint64_t *ptr, uint64x2_t val) { return vst1q_u64(ptr, val); }
[[gnu::always_inline]] inline void store1(float32_t *ptr, float32x2_t val) { return vst1_f32(ptr, val); }
[[gnu::always_inline]] inline void store1(poly8_t *ptr, poly8x8_t val) { return vst1_p8(ptr, val); }
[[gnu::always_inline]] inline void store1(poly8_t *ptr, poly8x16_t val) { return vst1q_p8(ptr, val); }
[[gnu::always_inline]] inline void store1(poly16_t *ptr, poly16x4_t val) { return vst1_p16(ptr, val); }
[[gnu::always_inline]] inline void store1(poly16_t *ptr, poly16x8_t val) { return vst1q_p16(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(int8_t *ptr, int8x8_t val) { return vst1_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(int8_t *ptr, int8x16_t val) { return vst1q_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(int16_t *ptr, int16x4_t val) { return vst1_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(int16_t *ptr, int16x8_t val) { return vst1q_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(int32_t *ptr, int32x2_t val) { return vst1_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(int32_t *ptr, int32x4_t val) { return vst1q_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(int64_t *ptr, int64x1_t val) { return vst1_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(int64_t *ptr, int64x2_t val) { return vst1q_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(uint8_t *ptr, uint8x8_t val) { return vst1_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(uint8_t *ptr, uint8x16_t val) { return vst1q_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(uint16_t *ptr, uint16x4_t val) { return vst1_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(uint16_t *ptr, uint16x8_t val) { return vst1q_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(uint32_t *ptr, uint32x2_t val) { return vst1_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(uint32_t *ptr, uint32x4_t val) { return vst1q_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(uint64_t *ptr, uint64x1_t val) { return vst1_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(uint64_t *ptr, uint64x2_t val) { return vst1q_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(float32_t *ptr, float32x2_t val) { return vst1_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(float32_t *ptr, float32x4_t val) { return vst1q_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(poly8_t *ptr, poly8x8_t val) { return vst1_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(poly8_t *ptr, poly8x16_t val) { return vst1q_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(poly16_t *ptr, poly16x4_t val) { return vst1_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(poly16_t *ptr, poly16x8_t val) { return vst1q_lane_p16(ptr, val, lane); }
[[gnu::always_inline]] inline void store2(int8_t *ptr, int8x8x2_t val) { return vst2_s8(ptr, val); }
[[gnu::always_inline]] inline void store2(int8_t *ptr, int8x16x2_t val) { return vst2q_s8(ptr, val); }
[[gnu::always_inline]] inline void store2(int16_t *ptr, int16x4x2_t val) { return vst2_s16(ptr, val); }
[[gnu::always_inline]] inline void store2(int16_t *ptr, int16x8x2_t val) { return vst2q_s16(ptr, val); }
[[gnu::always_inline]] inline void store2(int32_t *ptr, int32x2x2_t val) { return vst2_s32(ptr, val); }
[[gnu::always_inline]] inline void store2(int32_t *ptr, int32x4x2_t val) { return vst2q_s32(ptr, val); }
[[gnu::always_inline]] inline void store2(uint8_t *ptr, uint8x8x2_t val) { return vst2_u8(ptr, val); }
[[gnu::always_inline]] inline void store2(uint8_t *ptr, uint8x16x2_t val) { return vst2q_u8(ptr, val); }
[[gnu::always_inline]] inline void store2(uint16_t *ptr, uint16x4x2_t val) { return vst2_u16(ptr, val); }
[[gnu::always_inline]] inline void store2(uint16_t *ptr, uint16x8x2_t val) { return vst2q_u16(ptr, val); }
[[gnu::always_inline]] inline void store2(uint32_t *ptr, uint32x2x2_t val) { return vst2_u32(ptr, val); }
[[gnu::always_inline]] inline void store2(uint32_t *ptr, uint32x4x2_t val) { return vst2q_u32(ptr, val); }
[[gnu::always_inline]] inline void store2(float32_t *ptr, float32x2x2_t val) { return vst2_f32(ptr, val); }
[[gnu::always_inline]] inline void store2(float32_t *ptr, float32x4x2_t val) { return vst2q_f32(ptr, val); }
[[gnu::always_inline]] inline void store2(poly8_t *ptr, poly8x8x2_t val) { return vst2_p8(ptr, val); }
[[gnu::always_inline]] inline void store2(poly8_t *ptr, poly8x16x2_t val) { return vst2q_p8(ptr, val); }
[[gnu::always_inline]] inline void store2(poly16_t *ptr, poly16x4x2_t val) { return vst2_p16(ptr, val); }
[[gnu::always_inline]] inline void store2(poly16_t *ptr, poly16x8x2_t val) { return vst2q_p16(ptr, val); }
[[gnu::always_inline]] inline void store2(int64_t *ptr, int64x1x2_t val) { return vst2_s64(ptr, val); }
[[gnu::always_inline]] inline void store2(uint64_t *ptr, uint64x1x2_t val) { return vst2_u64(ptr, val); }
[[gnu::always_inline]] inline void store3(int8_t *ptr, int8x8x3_t val) { return vst3_s8(ptr, val); }
[[gnu::always_inline]] inline void store3(int8_t *ptr, int8x16x3_t val) { return vst3q_s8(ptr, val); }
[[gnu::always_inline]] inline void store3(int16_t *ptr, int16x4x3_t val) { return vst3_s16(ptr, val); }
[[gnu::always_inline]] inline void store3(int16_t *ptr, int16x8x3_t val) { return vst3q_s16(ptr, val); }
[[gnu::always_inline]] inline void store3(int32_t *ptr, int32x2x3_t val) { return vst3_s32(ptr, val); }
[[gnu::always_inline]] inline void store3(int32_t *ptr, int32x4x3_t val) { return vst3q_s32(ptr, val); }
[[gnu::always_inline]] inline void store3(uint8_t *ptr, uint8x8x3_t val) { return vst3_u8(ptr, val); }
[[gnu::always_inline]] inline void store3(uint8_t *ptr, uint8x16x3_t val) { return vst3q_u8(ptr, val); }
[[gnu::always_inline]] inline void store3(uint16_t *ptr, uint16x4x3_t val) { return vst3_u16(ptr, val); }
[[gnu::always_inline]] inline void store3(uint16_t *ptr, uint16x8x3_t val) { return vst3q_u16(ptr, val); }
[[gnu::always_inline]] inline void store3(uint32_t *ptr, uint32x2x3_t val) { return vst3_u32(ptr, val); }
[[gnu::always_inline]] inline void store3(uint32_t *ptr, uint32x4x3_t val) { return vst3q_u32(ptr, val); }
[[gnu::always_inline]] inline void store3(float32_t *ptr, float32x2x3_t val) { return vst3_f32(ptr, val); }
[[gnu::always_inline]] inline void store3(float32_t *ptr, float32x4x3_t val) { return vst3q_f32(ptr, val); }
[[gnu::always_inline]] inline void store3(poly8_t *ptr, poly8x8x3_t val) { return vst3_p8(ptr, val); }
[[gnu::always_inline]] inline void store3(poly8_t *ptr, poly8x16x3_t val) { return vst3q_p8(ptr, val); }
[[gnu::always_inline]] inline void store3(poly16_t *ptr, poly16x4x3_t val) { return vst3_p16(ptr, val); }
[[gnu::always_inline]] inline void store3(poly16_t *ptr, poly16x8x3_t val) { return vst3q_p16(ptr, val); }
[[gnu::always_inline]] inline void store3(int64_t *ptr, int64x1x3_t val) { return vst3_s64(ptr, val); }
[[gnu::always_inline]] inline void store3(uint64_t *ptr, uint64x1x3_t val) { return vst3_u64(ptr, val); }
[[gnu::always_inline]] inline void store4(int8_t *ptr, int8x8x4_t val) { return vst4_s8(ptr, val); }
[[gnu::always_inline]] inline void store4(int8_t *ptr, int8x16x4_t val) { return vst4q_s8(ptr, val); }
[[gnu::always_inline]] inline void store4(int16_t *ptr, int16x4x4_t val) { return vst4_s16(ptr, val); }
[[gnu::always_inline]] inline void store4(int16_t *ptr, int16x8x4_t val) { return vst4q_s16(ptr, val); }
[[gnu::always_inline]] inline void store4(int32_t *ptr, int32x2x4_t val) { return vst4_s32(ptr, val); }
[[gnu::always_inline]] inline void store4(int32_t *ptr, int32x4x4_t val) { return vst4q_s32(ptr, val); }
[[gnu::always_inline]] inline void store4(uint8_t *ptr, uint8x8x4_t val) { return vst4_u8(ptr, val); }
[[gnu::always_inline]] inline void store4(uint8_t *ptr, uint8x16x4_t val) { return vst4q_u8(ptr, val); }
[[gnu::always_inline]] inline void store4(uint16_t *ptr, uint16x4x4_t val) { return vst4_u16(ptr, val); }
[[gnu::always_inline]] inline void store4(uint16_t *ptr, uint16x8x4_t val) { return vst4q_u16(ptr, val); }
[[gnu::always_inline]] inline void store4(uint32_t *ptr, uint32x2x4_t val) { return vst4_u32(ptr, val); }
[[gnu::always_inline]] inline void store4(uint32_t *ptr, uint32x4x4_t val) { return vst4q_u32(ptr, val); }
[[gnu::always_inline]] inline void store4(float32_t *ptr, float32x2x4_t val) { return vst4_f32(ptr, val); }
[[gnu::always_inline]] inline void store4(float32_t *ptr, float32x4x4_t val) { return vst4q_f32(ptr, val); }
[[gnu::always_inline]] inline void store4(poly8_t *ptr, poly8x8x4_t val) { return vst4_p8(ptr, val); }
[[gnu::always_inline]] inline void store4(poly8_t *ptr, poly8x16x4_t val) { return vst4q_p8(ptr, val); }
[[gnu::always_inline]] inline void store4(poly16_t *ptr, poly16x4x4_t val) { return vst4_p16(ptr, val); }
[[gnu::always_inline]] inline void store4(poly16_t *ptr, poly16x8x4_t val) { return vst4q_p16(ptr, val); }
[[gnu::always_inline]] inline void store4(int64_t *ptr, int64x1x4_t val) { return vst4_s64(ptr, val); }
[[gnu::always_inline]] inline void store4(uint64_t *ptr, uint64x1x4_t val) { return vst4_u64(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(int8_t *ptr, int8x8x2_t val) { return vst2_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(uint8_t *ptr, uint8x8x2_t val) { return vst2_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(poly8_t *ptr, poly8x8x2_t val) { return vst2_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(int8_t *ptr, int8x8x3_t val) { return vst3_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(uint8_t *ptr, uint8x8x3_t val) { return vst3_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(poly8_t *ptr, poly8x8x3_t val) { return vst3_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(int8_t *ptr, int8x8x4_t val) { return vst4_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(uint8_t *ptr, uint8x8x4_t val) { return vst4_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(poly8_t *ptr, poly8x8x4_t val) { return vst4_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(int16_t *ptr, int16x4x2_t val) { return vst2_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(int16_t *ptr, int16x8x2_t val) { return vst2q_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(int32_t *ptr, int32x2x2_t val) { return vst2_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(int32_t *ptr, int32x4x2_t val) { return vst2q_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(uint16_t *ptr, uint16x4x2_t val) { return vst2_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(uint16_t *ptr, uint16x8x2_t val) { return vst2q_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(uint32_t *ptr, uint32x2x2_t val) { return vst2_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(uint32_t *ptr, uint32x4x2_t val) { return vst2q_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(float32_t *ptr, float32x2x2_t val) { return vst2_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(float32_t *ptr, float32x4x2_t val) { return vst2q_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(poly16_t *ptr, poly16x4x2_t val) { return vst2_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(poly16_t *ptr, poly16x8x2_t val) { return vst2q_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(int16_t *ptr, int16x4x3_t val) { return vst3_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(int16_t *ptr, int16x8x3_t val) { return vst3q_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(int32_t *ptr, int32x2x3_t val) { return vst3_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(int32_t *ptr, int32x4x3_t val) { return vst3q_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(uint16_t *ptr, uint16x4x3_t val) { return vst3_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(uint16_t *ptr, uint16x8x3_t val) { return vst3q_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(uint32_t *ptr, uint32x2x3_t val) { return vst3_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(uint32_t *ptr, uint32x4x3_t val) { return vst3q_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(float32_t *ptr, float32x2x3_t val) { return vst3_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(float32_t *ptr, float32x4x3_t val) { return vst3q_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(poly16_t *ptr, poly16x4x3_t val) { return vst3_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(poly16_t *ptr, poly16x8x3_t val) { return vst3q_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(int16_t *ptr, int16x4x4_t val) { return vst4_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(int16_t *ptr, int16x8x4_t val) { return vst4q_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(int32_t *ptr, int32x2x4_t val) { return vst4_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(int32_t *ptr, int32x4x4_t val) { return vst4q_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(uint16_t *ptr, uint16x4x4_t val) { return vst4_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(uint16_t *ptr, uint16x8x4_t val) { return vst4q_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(uint32_t *ptr, uint32x2x4_t val) { return vst4_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(uint32_t *ptr, uint32x4x4_t val) { return vst4q_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(float32_t *ptr, float32x2x4_t val) { return vst4_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(float32_t *ptr, float32x4x4_t val) { return vst4q_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(poly16_t *ptr, poly16x4x4_t val) { return vst4_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(poly16_t *ptr, poly16x8x4_t val) { return vst4q_lane_p16(ptr, val, lane); }
#if defined(__clang__) || (__GNUC__ > 13)
[[gnu::always_inline]] inline void store1_x2(int8_t *ptr, int8x8x2_t val) { return vst1_s8_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(int8_t *ptr, int8x16x2_t val) { return vst1q_s8_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(int16_t *ptr, int16x4x2_t val) { return vst1_s16_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(int16_t *ptr, int16x8x2_t val) { return vst1q_s16_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(int32_t *ptr, int32x2x2_t val) { return vst1_s32_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(int32_t *ptr, int32x4x2_t val) { return vst1q_s32_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(uint8_t *ptr, uint8x8x2_t val) { return vst1_u8_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(uint8_t *ptr, uint8x16x2_t val) { return vst1q_u8_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(uint16_t *ptr, uint16x4x2_t val) { return vst1_u16_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(uint16_t *ptr, uint16x8x2_t val) { return vst1q_u16_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(uint32_t *ptr, uint32x2x2_t val) { return vst1_u32_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(uint32_t *ptr, uint32x4x2_t val) { return vst1q_u32_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(float32_t *ptr, float32x2x2_t val) { return vst1_f32_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(float32_t *ptr, float32x4x2_t val) { return vst1q_f32_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(poly8_t *ptr, poly8x8x2_t val) { return vst1_p8_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(poly8_t *ptr, poly8x16x2_t val) { return vst1q_p8_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(poly16_t *ptr, poly16x4x2_t val) { return vst1_p16_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(poly16_t *ptr, poly16x8x2_t val) { return vst1q_p16_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(int64_t *ptr, int64x1x2_t val) { return vst1_s64_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(uint64_t *ptr, uint64x1x2_t val) { return vst1_u64_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(int64_t *ptr, int64x2x2_t val) { return vst1q_s64_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(uint64_t *ptr, uint64x2x2_t val) { return vst1q_u64_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(int8_t *ptr, int8x8x3_t val) { return vst1_s8_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(int8_t *ptr, int8x16x3_t val) { return vst1q_s8_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(int16_t *ptr, int16x4x3_t val) { return vst1_s16_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(int16_t *ptr, int16x8x3_t val) { return vst1q_s16_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(int32_t *ptr, int32x2x3_t val) { return vst1_s32_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(int32_t *ptr, int32x4x3_t val) { return vst1q_s32_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(uint8_t *ptr, uint8x8x3_t val) { return vst1_u8_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(uint8_t *ptr, uint8x16x3_t val) { return vst1q_u8_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(uint16_t *ptr, uint16x4x3_t val) { return vst1_u16_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(uint16_t *ptr, uint16x8x3_t val) { return vst1q_u16_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(uint32_t *ptr, uint32x2x3_t val) { return vst1_u32_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(uint32_t *ptr, uint32x4x3_t val) { return vst1q_u32_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(float32_t *ptr, float32x2x3_t val) { return vst1_f32_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(float32_t *ptr, float32x4x3_t val) { return vst1q_f32_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(poly8_t *ptr, poly8x8x3_t val) { return vst1_p8_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(poly8_t *ptr, poly8x16x3_t val) { return vst1q_p8_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(poly16_t *ptr, poly16x4x3_t val) { return vst1_p16_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(poly16_t *ptr, poly16x8x3_t val) { return vst1q_p16_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(int64_t *ptr, int64x1x3_t val) { return vst1_s64_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(uint64_t *ptr, uint64x1x3_t val) { return vst1_u64_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(int64_t *ptr, int64x2x3_t val) { return vst1q_s64_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(uint64_t *ptr, uint64x2x3_t val) { return vst1q_u64_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(int8_t *ptr, int8x8x4_t val) { return vst1_s8_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(int8_t *ptr, int8x16x4_t val) { return vst1q_s8_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(int16_t *ptr, int16x4x4_t val) { return vst1_s16_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(int16_t *ptr, int16x8x4_t val) { return vst1q_s16_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(int32_t *ptr, int32x2x4_t val) { return vst1_s32_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(int32_t *ptr, int32x4x4_t val) { return vst1q_s32_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(uint8_t *ptr, uint8x8x4_t val) { return vst1_u8_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(uint8_t *ptr, uint8x16x4_t val) { return vst1q_u8_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(uint16_t *ptr, uint16x4x4_t val) { return vst1_u16_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(uint16_t *ptr, uint16x8x4_t val) { return vst1q_u16_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(uint32_t *ptr, uint32x2x4_t val) { return vst1_u32_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(uint32_t *ptr, uint32x4x4_t val) { return vst1q_u32_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(float32_t *ptr, float32x2x4_t val) { return vst1_f32_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(float32_t *ptr, float32x4x4_t val) { return vst1q_f32_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(poly8_t *ptr, poly8x8x4_t val) { return vst1_p8_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(poly8_t *ptr, poly8x16x4_t val) { return vst1q_p8_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(poly16_t *ptr, poly16x4x4_t val) { return vst1_p16_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(poly16_t *ptr, poly16x8x4_t val) { return vst1q_p16_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(int64_t *ptr, int64x1x4_t val) { return vst1_s64_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(uint64_t *ptr, uint64x1x4_t val) { return vst1_u64_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(int64_t *ptr, int64x2x4_t val) { return vst1q_s64_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(uint64_t *ptr, uint64x2x4_t val) { return vst1q_u64_x4(ptr, val); }
#endif
[[gnu::always_inline]] nce int8x8_t table_lookup2(int8x8x2_t a, int8x8_t idx) { return vtbl2_s8(a, idx); }
[[gnu::always_inline]] nce uint8x8_t table_lookup2(uint8x8x2_t a, uint8x8_t idx) { return vtbl2_u8(a, idx); }
[[gnu::always_inline]] nce poly8x8_t table_lookup2(poly8x8x2_t a, uint8x8_t idx) { return vtbl2_p8(a, idx); }
[[gnu::always_inline]] nce int8x8_t table_lookup3(int8x8x3_t a, int8x8_t idx) { return vtbl3_s8(a, idx); }
[[gnu::always_inline]] nce uint8x8_t table_lookup3(uint8x8x3_t a, uint8x8_t idx) { return vtbl3_u8(a, idx); }
[[gnu::always_inline]] nce poly8x8_t table_lookup3(poly8x8x3_t a, uint8x8_t idx) { return vtbl3_p8(a, idx); }
[[gnu::always_inline]] nce int8x8_t table_lookup4(int8x8x4_t a, int8x8_t idx) { return vtbl4_s8(a, idx); }
[[gnu::always_inline]] nce uint8x8_t table_lookup4(uint8x8x4_t a, uint8x8_t idx) { return vtbl4_u8(a, idx); }
[[gnu::always_inline]] nce poly8x8_t table_lookup4(poly8x8x4_t a, uint8x8_t idx) { return vtbl4_p8(a, idx); }
#ifdef __clang__
[[gnu::always_inline]] nce poly64x1_t add(poly64x1_t a, poly64x1_t b) { return vadd_p64(a, b); }
[[gnu::always_inline]] nce poly8x16_t add(poly8x16_t a, poly8x16_t b) { return vaddq_p8(a, b); }
[[gnu::always_inline]] nce poly16x8_t add(poly16x8_t a, poly16x8_t b) { return vaddq_p16(a, b); }
[[gnu::always_inline]] nce poly64x2_t add(poly64x2_t a, poly64x2_t b) { return vaddq_p64(a, b); }
#endif

}  // namespace neon
#undef nce

#endif // __cplusplus
#pragma once
#include <array>
#include <functional>
#include <span>
#include <tuple>
#include <type_traits>
#include <utility>
#pragma once
#pragma once
#include <type_traits>
#pragma once
#include <stdbool.h>

namespace argon {
enum class platform {
  NEON,
  MVE,
  MOCK,
};
}

#ifdef __ARM_NEON
namespace argon {
constexpr platform target = platform::NEON;
}
#define ARGON_HAS_DWORD true
#define ARGON_HAS_FLOAT true

#if (__ARM_ARCH >= 8)

#if (__arm__)  // A32

#define ARGON_HAS_HALF_FLOAT true
#define ARGON_HAS_SINGLE_FLOAT true
#define ARGON_HAS_DOUBLE_FLOAT false

#elif (__aarch64__)  // A64

#define ARGON_HAS_HALF_FLOAT true
#define ARGON_HAS_SINGLE_FLOAT true
#define ARGON_HAS_DOUBLE_FLOAT true

#endif

#else

#if (__ARM_NEON_FP & 2)
#define ARGON_HAS_HALF_FLOAT true
#else
#define ARGON_HAS_HALF_FLOAT false
#endif

#if (__ARM_NEON_FP & 4)
#define ARGON_HAS_SINGLE_FLOAT true
#else
#define ARGON_HAS_SINGLE_FLOAT false
#endif

#if (__ARM_NEON_FP & 8)
#define ARGON_HAS_DOUBLE_FLOAT true
#else
#define ARGON_HAS_DOUBLE_FLOAT false
#endif

#endif

#elifdef __ARM_FEATURE_MVE
namespace argon {
constexpr platform target = platform::MVE;
}
#define ARGON_HAS_DWORD false

#if (__ARM_FEATURE_MVE & 2)
#define ARGON_HAS_FLOAT true
#define ARGON_HAS_HALF_FLOAT true
#define ARGON_HAS_SINGLE_FLOAT true
#else
#define ARGON_HAS_FLOAT false
#define ARGON_HAS_HALF_FLOAT false
#define ARGON_HAS_SINGLE_FLOAT false
#endif

#else
namespace argon {
constexpr platform target = platform::MOCK;
}
#define ARGON_HAS_DWORD true
#define ARGON_HAS_FLOAT true
#define ARGON_HAS_HALF_FLOAT true
#define ARGON_HAS_SINGLE_FLOAT true
#endif

/*
#define XSTR(x) STR(x)
#define STR(x) #x
#pragma message "DWORD: " XSTR(ARGON_HAS_DWORD)
#pragma message "SINGLE_FLOAT: " XSTR(ARGON_HAS_SINGLE_FLOAT)
#pragma message "HALF_FLOAT: " XSTR(ARGON_HAS_HALF_FLOAT)
#pragma message "DOUBLE_FLOAT: " XSTR(ARGON_HAS_DOUBLE_FLOAT)
#pragma message "__ARM_NEON: " XSTR(__ARM_NEON)
#pragma message "__ARM_NEON_FP: " XSTR(__ARM_NEON_FP)
#pragma message "__ARM_FP: " XSTR(__ARM_FP)
*/

#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

namespace simd {
template <typename T>
constexpr bool is_quadword_v =
       std::is_same_v<T, uint8x16_t>
    || std::is_same_v<T, uint16x8_t>
    || std::is_same_v<T, uint32x4_t>
    || std::is_same_v<T, uint64x2_t>
    || std::is_same_v<T, int8x16_t>
    || std::is_same_v<T, int16x8_t>
    || std::is_same_v<T, int32x4_t>
    || std::is_same_v<T, int64x2_t>
#if ARGON_HAS_SINGLE_FLOAT
    || std::is_same_v<T, float32x4_t>
#endif
    ;
template <typename T>
concept is_quadword = is_quadword_v<T>;

#if ARGON_HAS_DWORD
template <typename T>
constexpr bool is_doubleword_v =
       std::is_same_v<T, uint8x8_t>
    || std::is_same_v<T, uint16x4_t>
    || std::is_same_v<T, uint32x2_t>
    || std::is_same_v<T, uint64x1_t>
    || std::is_same_v<T, int8x8_t>
    || std::is_same_v<T, int16x4_t>
    || std::is_same_v<T, int32x2_t>
    || std::is_same_v<T, int64x1_t>
    || std::is_same_v<T, float32x2_t>
    ;

template <typename T>
concept is_doubleword = is_doubleword_v<T>;

template <typename T>
concept is_vector_type = is_doubleword<T> || is_quadword<T>;
#else
template <typename T>
concept is_vector_type = is_quadword<T>;
#endif

}  // namespace simd
#undef simd
#pragma once

#pragma once


#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

namespace simd {
template <typename T> struct NonVec;
template <> struct NonVec<int8x16_t>   { using type = int8_t; };
template <> struct NonVec<uint8x16_t>  { using type = uint8_t; };
template <> struct NonVec<int16x8_t>   { using type = int16_t; };
template <> struct NonVec<uint16x8_t>  { using type = uint16_t; };
template <> struct NonVec<int32x4_t>   { using type = int32_t; };
template <> struct NonVec<uint32x4_t>  { using type = uint32_t; };
template <> struct NonVec<int64x2_t>   { using type = int64_t; };
template <> struct NonVec<uint64x2_t>  { using type = uint64_t; };

#if ARGON_HAS_SINGLE_FLOAT
template <> struct NonVec<float32x4_t> { using type = float; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct NonVec<float16x8_t> { using type = float16_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct NonVec<float64x2_t> { using type = double; };
#endif

#if ARGON_HAS_DWORD
template <> struct NonVec<int8x8_t> { using type = int8_t; };
template <> struct NonVec<uint8x8_t> { using type = uint8_t; };
template <> struct NonVec<int16x4_t> { using type = int16_t; };
template <> struct NonVec<uint16x4_t> { using type = uint16_t; };
template <> struct NonVec<int32x2_t> { using type = int32_t; };
template <> struct NonVec<uint32x2_t> { using type = uint32_t; };
template <> struct NonVec<int64x1_t> { using type = int64_t; };
template <> struct NonVec<uint64x1_t> { using type = uint64_t; };
#if ARGON_HAS_SINGLE_FLOAT
template <> struct NonVec<float32x2_t> { using type = float; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct NonVec<float16x4_t> { using type = float16_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct NonVec<float64x1_t> { using type = double; };
#endif
#endif

template <typename T>
using NonVec_t = typename NonVec<T>::type;

}  // namespace simd
#undef simd
#pragma once


#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

namespace simd {
#if ARGON_HAS_DWORD
template <typename type> struct Vec64;
template <> struct Vec64<int8_t> { using type = int8x8_t; };
template <> struct Vec64<uint8_t> { using type = uint8x8_t; };
template <> struct Vec64<int16_t> { using type = int16x4_t; };
template <> struct Vec64<uint16_t> { using type = uint16x4_t; };
template <> struct Vec64<int32_t> { using type = int32x2_t; };
template <> struct Vec64<uint32_t> { using type = uint32x2_t; };
template <> struct Vec64<int64_t> { using type = int64x1_t; };
template <> struct Vec64<uint64_t> { using type = uint64x1_t; };

#if ARGON_HAS_SINGLE_FLOAT
template <> struct Vec64<float> {using type = float32x2_t; };
#endif

#if ARGON_HAS_HALF_FLOAT
template <> struct Vec64<float16_t> {using type = float16x4_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct Vec64<float64_t> {using type = float64x1_t; };
#endif

template <typename T>
using Vec64_t = typename Vec64<T>::type;

#endif
}  // namespace simd
#undef simd


#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif


#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif


namespace simd {
#if ARGON_HAS_DWORD
template <typename T>
nce T duplicate_lane(typename Vec64<NonVec_t<T>>::type vec, const int i);

template <>
nce uint8x8_t duplicate_lane(uint8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    case 2:
      return simd::duplicate_lane<2>(vec);
    case 3:
      return simd::duplicate_lane<3>(vec);
    case 4:
      return simd::duplicate_lane<4>(vec);
    case 5:
      return simd::duplicate_lane<5>(vec);
    case 6:
      return simd::duplicate_lane<6>(vec);
    case 7:
      return simd::duplicate_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint8x16_t duplicate_lane(uint8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    case 2:
      return simd::duplicate_lane_quad<2>(vec);
    case 3:
      return simd::duplicate_lane_quad<3>(vec);
    case 4:
      return simd::duplicate_lane_quad<4>(vec);
    case 5:
      return simd::duplicate_lane_quad<5>(vec);
    case 6:
      return simd::duplicate_lane_quad<6>(vec);
    case 7:
      return simd::duplicate_lane_quad<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x8_t duplicate_lane(int8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    case 2:
      return simd::duplicate_lane<2>(vec);
    case 3:
      return simd::duplicate_lane<3>(vec);
    case 4:
      return simd::duplicate_lane<4>(vec);
    case 5:
      return simd::duplicate_lane<5>(vec);
    case 6:
      return simd::duplicate_lane<6>(vec);
    case 7:
      return simd::duplicate_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x16_t duplicate_lane(int8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    case 2:
      return simd::duplicate_lane_quad<2>(vec);
    case 3:
      return simd::duplicate_lane_quad<3>(vec);
    case 4:
      return simd::duplicate_lane_quad<4>(vec);
    case 5:
      return simd::duplicate_lane_quad<5>(vec);
    case 6:
      return simd::duplicate_lane_quad<6>(vec);
    case 7:
      return simd::duplicate_lane_quad<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x4_t duplicate_lane(uint16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    case 2:
      return simd::duplicate_lane<2>(vec);
    case 3:
      return simd::duplicate_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x8_t duplicate_lane(uint16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    case 2:
      return simd::duplicate_lane_quad<2>(vec);
    case 3:
      return simd::duplicate_lane_quad<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x4_t duplicate_lane(int16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    case 2:
      return simd::duplicate_lane<2>(vec);
    case 3:
      return simd::duplicate_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x8_t duplicate_lane(int16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    case 2:
      return simd::duplicate_lane_quad<2>(vec);
    case 3:
      return simd::duplicate_lane_quad<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x2_t duplicate_lane(uint32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x4_t duplicate_lane(uint32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x2_t duplicate_lane(int32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x4_t duplicate_lane(int32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x2_t duplicate_lane(uint64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    default:
      __builtin_unreachable();
  }
}

#if ARGON_HAS_SINGLE_FLOAT
template <>
nce float32x2_t duplicate_lane(float32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane<0>(vec);
    case 1:
      return simd::duplicate_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x4_t duplicate_lane(float32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::duplicate_lane_quad<0>(vec);
    case 1:
      return simd::duplicate_lane_quad<1>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif
#endif
}
#undef simd
#undef nce
#pragma once



#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace simd {

template <typename T>
nce auto get_lane(T vec, const int i);

template <>
nce auto get_lane(uint8x16_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    case 8:
      return simd::get_lane<8>(vec);
    case 9:
      return simd::get_lane<9>(vec);
    case 10:
      return simd::get_lane<10>(vec);
    case 11:
      return simd::get_lane<11>(vec);
    case 12:
      return simd::get_lane<12>(vec);
    case 13:
      return simd::get_lane<13>(vec);
    case 14:
      return simd::get_lane<14>(vec);
    case 15:
      return simd::get_lane<15>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int8x16_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    case 8:
      return simd::get_lane<8>(vec);
    case 9:
      return simd::get_lane<9>(vec);
    case 10:
      return simd::get_lane<10>(vec);
    case 11:
      return simd::get_lane<11>(vec);
    case 12:
      return simd::get_lane<12>(vec);
    case 13:
      return simd::get_lane<13>(vec);
    case 14:
      return simd::get_lane<14>(vec);
    case 15:
      return simd::get_lane<15>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint16x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int16x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint64x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int64x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

#if ARGON_HAS_SINGLE_FLOAT
template <>
nce auto get_lane(float32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif

#if ARGON_HAS_HALF_FLOAT
template <>
nce auto get_lane(float16x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <>
nce auto get_lane(float64x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      __builtin_unreachable();
 }
}
#endif

#if ARGON_HAS_DWORD
template <>
nce auto get_lane(uint8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    case 4:
      return simd::get_lane<4>(vec);
    case 5:
      return simd::get_lane<5>(vec);
    case 6:
      return simd::get_lane<6>(vec);
    case 7:
      return simd::get_lane<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(uint64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get_lane(int64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    default:
      __builtin_unreachable();
  }
}


#if ARGON_HAS_SINGLE_FLOAT
template <>
nce auto get_lane(float32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif

#if ARGON_HAS_HALF_FLOAT
template <>
nce auto get_lane(float16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    case 1:
      return simd::get_lane<1>(vec);
    case 2:
      return simd::get_lane<2>(vec);
    case 3:
      return simd::get_lane<3>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <>
nce auto get_lane(float64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return simd::get_lane<0>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif
#endif

}  // namespace simd
#undef simd
#pragma once



#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

#define make_lane_helper_dword_1arg(lane_func)             \
  template <is_vector_type T, is_doubleword U>             \
    requires std::is_same_v<NonVec_t<T>, NonVec_t<U>>      \
  nce T lane_func(T a, U vec, const int lane) {          \
    constexpr int lanes = sizeof(U) / sizeof(NonVec_t<U>); \
    if constexpr (lanes == 2) {                            \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 4) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        case 2:                                            \
          return lane_func<2>(a, vec);                   \
        case 3:                                            \
          return lane_func<3>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 8) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        case 2:                                            \
          return lane_func<2>(a, vec);                   \
        case 3:                                            \
          return lane_func<3>(a, vec);                   \
        case 4:                                            \
          return lane_func<4>(a, vec);                   \
        case 5:                                            \
          return lane_func<5>(a, vec);                   \
        case 6:                                            \
          return lane_func<6>(a, vec);                   \
        case 7:                                            \
          return lane_func<7>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    }                                                      \
  }

#define make_lane_helper_dword_2arg(lane_func)             \
  template <is_vector_type T, is_doubleword U>             \
    requires std::is_same_v<NonVec_t<T>, NonVec_t<U>>      \
  nce T lane_func(T a, T b, U vec, const int lane) {     \
    constexpr int lanes = sizeof(U) / sizeof(NonVec_t<U>); \
    if constexpr (lanes == 2) {                            \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 4) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        case 2:                                            \
          return lane_func<2>(a, b, vec);                \
        case 3:                                            \
          return lane_func<3>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 8) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        case 2:                                            \
          return lane_func<2>(a, b, vec);                \
        case 3:                                            \
          return lane_func<3>(a, b, vec);                \
        case 4:                                            \
          return lane_func<4>(a, b, vec);                \
        case 5:                                            \
          return lane_func<5>(a, b, vec);                \
        case 6:                                            \
          return lane_func<6>(a, b, vec);                \
        case 7:                                            \
          return lane_func<7>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    }                                                      \
  }

#define make_lane_helper_qword_1arg(lane_func)             \
  template <is_vector_type T, is_vector_type U>            \
    requires std::is_same_v<NonVec_t<T>, NonVec_t<U>>      \
  nce T lane_func(T a, U vec, const int lane) {          \
    constexpr int lanes = sizeof(U) / sizeof(NonVec_t<U>); \
    if constexpr (lanes == 2) {                            \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 4) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        case 2:                                            \
          return lane_func<2>(a, vec);                   \
        case 3:                                            \
          return lane_func<3>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 8) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        case 2:                                            \
          return lane_func<2>(a, vec);                   \
        case 3:                                            \
          return lane_func<3>(a, vec);                   \
        case 4:                                            \
          return lane_func<4>(a, vec);                   \
        case 5:                                            \
          return lane_func<5>(a, vec);                   \
        case 6:                                            \
          return lane_func<6>(a, vec);                   \
        case 7:                                            \
          return lane_func<7>(a, vec);                   \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 16) {                    \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, vec);                   \
        case 1:                                            \
          return lane_func<1>(a, vec);                   \
        case 2:                                            \
          return lane_func<2>(a, vec);                   \
        case 3:                                            \
          return lane_func<3>(a, vec);                   \
        case 4:                                            \
          return lane_func<4>(a, vec);                   \
        case 5:                                            \
          return lane_func<5>(a, vec);                   \
        case 6:                                            \
          return lane_func<6>(a, vec);                   \
        case 7:                                            \
          return lane_func<7>(a, vec);                   \
        case 8:                                            \
          return lane_func<8>(a, vec);                   \
        case 9:                                            \
          return lane_func<9>(a, vec);                   \
        case 10:                                           \
          return lane_func<10>(a, vec);                  \
        case 11:                                           \
          return lane_func<11>(a, vec);                  \
        case 12:                                           \
          return lane_func<12>(a, vec);                  \
        case 13:                                           \
          return lane_func<13>(a, vec);                  \
        case 14:                                           \
          return lane_func<14>(a, vec);                  \
        case 15:                                           \
          return lane_func<15>(a, vec);                  \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    }                                                      \
  }

#define make_lane_helper_qword_2arg(lane_func)             \
  template <is_vector_type T, is_vector_type U>            \
    requires std::is_same_v<NonVec_t<T>, NonVec_t<U>>      \
  nce T lane_func(T a, T b, U vec, const int lane) {     \
    constexpr int lanes = sizeof(U) / sizeof(NonVec_t<U>); \
    if constexpr (lanes == 2) {                            \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 4) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        case 2:                                            \
          return lane_func<2>(a, b, vec);                \
        case 3:                                            \
          return lane_func<3>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 8) {                     \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        case 2:                                            \
          return lane_func<2>(a, b, vec);                \
        case 3:                                            \
          return lane_func<3>(a, b, vec);                \
        case 4:                                            \
          return lane_func<4>(a, b, vec);                \
        case 5:                                            \
          return lane_func<5>(a, b, vec);                \
        case 6:                                            \
          return lane_func<6>(a, b, vec);                \
        case 7:                                            \
          return lane_func<7>(a, b, vec);                \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    } else if constexpr (lanes == 16) {                    \
      switch (lane) {                                      \
        case 0:                                            \
          return lane_func<0>(a, b, vec);                \
        case 1:                                            \
          return lane_func<1>(a, b, vec);                \
        case 2:                                            \
          return lane_func<2>(a, b, vec);                \
        case 3:                                            \
          return lane_func<3>(a, b, vec);                \
        case 4:                                            \
          return lane_func<4>(a, b, vec);                \
        case 5:                                            \
          return lane_func<5>(a, b, vec);                \
        case 6:                                            \
          return lane_func<6>(a, b, vec);                \
        case 7:                                            \
          return lane_func<7>(a, b, vec);                \
        case 8:                                            \
          return lane_func<8>(a, b, vec);                \
        case 9:                                            \
          return lane_func<9>(a, b, vec);                \
        case 10:                                           \
          return lane_func<10>(a, b, vec);               \
        case 11:                                           \
          return lane_func<11>(a, b, vec);               \
        case 12:                                           \
          return lane_func<12>(a, b, vec);               \
        case 13:                                           \
          return lane_func<13>(a, b, vec);               \
        case 14:                                           \
          return lane_func<14>(a, b, vec);               \
        case 15:                                           \
          return lane_func<15>(a, b, vec);               \
        default:                                           \
          __builtin_unreachable();                         \
      }                                                    \
    }                                                      \
  }

namespace simd {
#if ARGON_HAS_DWORD
make_lane_helper_dword_1arg(multiply_lane);
make_lane_helper_dword_1arg(multiply_long_lane);
make_lane_helper_dword_1arg(multiply_double_saturate_long_lane);
make_lane_helper_dword_1arg(multiply_double_saturate_high_lane);
make_lane_helper_dword_1arg(multiply_double_round_saturate_high_lane);
make_lane_helper_dword_2arg(multiply_add_lane);
make_lane_helper_dword_2arg(multiply_subtract_lane);
make_lane_helper_dword_2arg(multiply_add_long_lane);
make_lane_helper_dword_2arg(multiply_subtract_long_lane);
make_lane_helper_dword_2arg(multiply_double_add_saturate_long_lane);
make_lane_helper_dword_2arg(multiply_double_subtract_saturate_long_lane);
#endif

#ifdef __aarch64__
make_lane_helper_qword_1arg(multiply_lane);
make_lane_helper_qword_1arg(multiply_long_lane);
make_lane_helper_qword_1arg(multiply_double_saturate_long_lane);
make_lane_helper_qword_1arg(multiply_double_saturate_high_lane);
make_lane_helper_qword_1arg(multiply_double_round_saturate_high_lane);
make_lane_helper_qword_2arg(multiply_add_lane);
make_lane_helper_qword_2arg(multiply_subtract_lane);
make_lane_helper_qword_2arg(multiply_add_long_lane);
make_lane_helper_qword_2arg(multiply_subtract_long_lane);
make_lane_helper_qword_2arg(multiply_double_add_saturate_long_lane);
make_lane_helper_qword_2arg(multiply_double_subtract_saturate_long_lane);

#endif
}  // namespace simd
#undef simd
#undef nce
#undef make_lane_helper_dword_1arg
#undef make_lane_helper_qword_1arg
#undef make_lane_helper_dword_2arg
#undef make_lane_helper_qword_2arg
#pragma once



#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace simd {

template <typename T>
nce T load1_lane(T vec, const int i, typename NonVec<T>::type const *ptr);

template <>
nce uint8x16_t load1_lane(uint8x16_t vec, const int i, uint8_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    case 4:
      return simd::load1_lane_quad<4>(ptr, vec);
    case 5:
      return simd::load1_lane_quad<5>(ptr, vec);
    case 6:
      return simd::load1_lane_quad<6>(ptr, vec);
    case 7:
      return simd::load1_lane_quad<7>(ptr, vec);
    case 8:
      return simd::load1_lane_quad<8>(ptr, vec);
    case 9:
      return simd::load1_lane_quad<9>(ptr, vec);
    case 10:
      return simd::load1_lane_quad<10>(ptr, vec);
    case 11:
      return simd::load1_lane_quad<11>(ptr, vec);
    case 12:
      return simd::load1_lane_quad<12>(ptr, vec);
    case 13:
      return simd::load1_lane_quad<13>(ptr, vec);
    case 14:
      return simd::load1_lane_quad<14>(ptr, vec);
    case 15:
      return simd::load1_lane_quad<15>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x16_t load1_lane(int8x16_t vec, const int i, int8_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    case 4:
      return simd::load1_lane_quad<4>(ptr, vec);
    case 5:
      return simd::load1_lane_quad<5>(ptr, vec);
    case 6:
      return simd::load1_lane_quad<6>(ptr, vec);
    case 7:
      return simd::load1_lane_quad<7>(ptr, vec);
    case 8:
      return simd::load1_lane_quad<8>(ptr, vec);
    case 9:
      return simd::load1_lane_quad<9>(ptr, vec);
    case 10:
      return simd::load1_lane_quad<10>(ptr, vec);
    case 11:
      return simd::load1_lane_quad<11>(ptr, vec);
    case 12:
      return simd::load1_lane_quad<12>(ptr, vec);
    case 13:
      return simd::load1_lane_quad<13>(ptr, vec);
    case 14:
      return simd::load1_lane_quad<14>(ptr, vec);
    case 15:
      return simd::load1_lane_quad<15>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x8_t load1_lane(uint16x8_t vec, const int i, uint16_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    case 4:
      return simd::load1_lane_quad<4>(ptr, vec);
    case 5:
      return simd::load1_lane_quad<5>(ptr, vec);
    case 6:
      return simd::load1_lane_quad<6>(ptr, vec);
    case 7:
      return simd::load1_lane_quad<7>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x8_t load1_lane(int16x8_t vec, const int i, int16_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    case 4:
      return simd::load1_lane_quad<4>(ptr, vec);
    case 5:
      return simd::load1_lane_quad<5>(ptr, vec);
    case 6:
      return simd::load1_lane_quad<6>(ptr, vec);
    case 7:
      return simd::load1_lane_quad<7>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x4_t load1_lane(uint32x4_t vec, const int i, uint32_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x4_t load1_lane(int32x4_t vec, const int i, int32_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x4_t load1_lane(float32x4_t vec, const int i, float const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    case 2:
      return simd::load1_lane_quad<2>(ptr, vec);
    case 3:
      return simd::load1_lane_quad<3>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x2_t load1_lane(uint64x2_t vec, const int i, uint64_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x2_t load1_lane(int64x2_t vec, const int i, int64_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane_quad<0>(ptr, vec);
    case 1:
      return simd::load1_lane_quad<1>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}
#if ARGON_HAS_DWORD

template <>
nce uint8x8_t load1_lane(uint8x8_t vec, const int i, uint8_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    case 2:
      return simd::load1_lane<2>(ptr, vec);
    case 3:
      return simd::load1_lane<3>(ptr, vec);
    case 4:
      return simd::load1_lane<4>(ptr, vec);
    case 5:
      return simd::load1_lane<5>(ptr, vec);
    case 6:
      return simd::load1_lane<6>(ptr, vec);
    case 7:
      return simd::load1_lane<7>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x8_t load1_lane(int8x8_t vec, const int i, int8_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    case 2:
      return simd::load1_lane<2>(ptr, vec);
    case 3:
      return simd::load1_lane<3>(ptr, vec);
    case 4:
      return simd::load1_lane<4>(ptr, vec);
    case 5:
      return simd::load1_lane<5>(ptr, vec);
    case 6:
      return simd::load1_lane<6>(ptr, vec);
    case 7:
      return simd::load1_lane<7>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x4_t load1_lane(uint16x4_t vec, const int i, uint16_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    case 2:
      return simd::load1_lane<2>(ptr, vec);
    case 3:
      return simd::load1_lane<3>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x4_t load1_lane(int16x4_t vec, const int i, int16_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    case 2:
      return simd::load1_lane<2>(ptr, vec);
    case 3:
      return simd::load1_lane<3>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x2_t load1_lane(uint32x2_t vec, const int i, uint32_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x2_t load1_lane(int32x2_t vec, const int i, int32_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x2_t load1_lane(float32x2_t vec, const int i, float32_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    case 1:
      return simd::load1_lane<1>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x1_t load1_lane(uint64x1_t vec, const int i, uint64_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x1_t load1_lane(int64x1_t vec, const int i, int64_t const *ptr) {
  switch (i) {
    case 0:
      return simd::load1_lane<0>(ptr, vec);
    default:
      __builtin_unreachable();
  }
}
#endif

}  // namespace simd
#undef simd
#undef nce
#pragma once


#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

namespace simd {
template <typename T> struct make_signed;
template <> struct make_signed<uint8x16_t> { using type = int8x16_t; };
template <> struct make_signed<int8x16_t> { using type = int8x16_t; };
template <> struct make_signed<uint16x8_t> { using type = int16x8_t; };
template <> struct make_signed<int16x8_t> { using type = int16x8_t; };
template <> struct make_signed<uint32x4_t> { using type = int32x4_t; };
template <> struct make_signed<int32x4_t> { using type = int32x4_t; };
template <> struct make_signed<uint64x2_t> { using type = int64x2_t; };
template <> struct make_signed<int64x2_t> { using type = int64x2_t; };

#if ARGON_HAS_DWORD
template <> struct make_signed<uint8x8_t> { using type = int8x8_t; };
template <> struct make_signed<int8x8_t> { using type = int8x8_t; };
template <> struct make_signed<uint16x4_t> { using type = int16x4_t; };
template <> struct make_signed<int16x4_t> { using type = int16x4_t; };
template <> struct make_signed<uint32x2_t> { using type = int32x2_t; };
template <> struct make_signed<int32x2_t> { using type = int32x2_t; };
template <> struct make_signed<uint64x1_t> { using type = int64x1_t; };
template <> struct make_signed<int64x1_t> { using type = int64x1_t; };
#endif

template <typename T> using make_signed_t = typename make_signed<T>::type;
}  // namespace simd
#undef simd
#pragma once


#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

namespace simd {
template <typename T> struct make_unsigned;
template <> struct make_unsigned<int8x16_t> { using type = uint8x16_t; };
template <> struct make_unsigned<uint8x16_t> { using type = uint8x16_t; };
template <> struct make_unsigned<int16x8_t> { using type = uint16x8_t; };
template <> struct make_unsigned<uint16x8_t> { using type = uint16x8_t; };
template <> struct make_unsigned<int32x4_t> { using type = uint32x4_t; };
template <> struct make_unsigned<uint32x4_t> { using type = uint32x4_t; };
template <> struct make_unsigned<int64x2_t> { using type = uint64x2_t; };
template <> struct make_unsigned<uint64x2_t> { using type = uint64x2_t; };

#if ARGON_HAS_DWORD
template <> struct make_unsigned<int8x8_t> { using type = uint8x8_t; };
template <> struct make_unsigned<uint8x8_t> { using type = uint8x8_t; };
template <> struct make_unsigned<int16x4_t> { using type = uint16x4_t; };
template <> struct make_unsigned<uint16x4_t> { using type = uint16x4_t; };
template <> struct make_unsigned<int32x2_t> { using type = uint32x2_t; };
template <> struct make_unsigned<uint32x2_t> { using type = uint32x2_t; };
template <> struct make_unsigned<int64x1_t> { using type = uint64x1_t; };
template <> struct make_unsigned<uint64x1_t> { using type = uint64x1_t; };
#endif

template <typename T> using make_unsigned_t = typename make_unsigned<T>::type;
}  // namespace simd
#undef simd

#pragma once



#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace simd {

template <typename T>
nce T set_lane(T vec, const int i, typename NonVec<T>::type a);

template <>
nce uint8x16_t set_lane(uint8x16_t vec, const int i, uint8_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    case 8:
      return simd::set_lane<8>(a, vec);
    case 9:
      return simd::set_lane<9>(a, vec);
    case 10:
      return simd::set_lane<10>(a, vec);
    case 11:
      return simd::set_lane<11>(a, vec);
    case 12:
      return simd::set_lane<12>(a, vec);
    case 13:
      return simd::set_lane<13>(a, vec);
    case 14:
      return simd::set_lane<14>(a, vec);
    case 15:
      return simd::set_lane<15>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x16_t set_lane(int8x16_t vec, const int i, int8_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    case 8:
      return simd::set_lane<8>(a, vec);
    case 9:
      return simd::set_lane<9>(a, vec);
    case 10:
      return simd::set_lane<10>(a, vec);
    case 11:
      return simd::set_lane<11>(a, vec);
    case 12:
      return simd::set_lane<12>(a, vec);
    case 13:
      return simd::set_lane<13>(a, vec);
    case 14:
      return simd::set_lane<14>(a, vec);
    case 15:
      return simd::set_lane<15>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x8_t set_lane(uint16x8_t vec, const int i, uint16_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x8_t set_lane(int16x8_t vec, const int i, int16_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x4_t set_lane(uint32x4_t vec, const int i, uint32_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x4_t set_lane(int32x4_t vec, const int i, int32_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x4_t set_lane(float32x4_t vec, const int i, float a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x2_t set_lane(uint64x2_t vec, const int i, uint64_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x2_t set_lane(int64x2_t vec, const int i, int64_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}
#if ARGON_HAS_DWORD

template <>
nce uint8x8_t set_lane(uint8x8_t vec, const int i, uint8_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x8_t set_lane(int8x8_t vec, const int i, int8_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    case 4:
      return simd::set_lane<4>(a, vec);
    case 5:
      return simd::set_lane<5>(a, vec);
    case 6:
      return simd::set_lane<6>(a, vec);
    case 7:
      return simd::set_lane<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x4_t set_lane(uint16x4_t vec, const int i, uint16_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x4_t set_lane(int16x4_t vec, const int i, int16_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    case 2:
      return simd::set_lane<2>(a, vec);
    case 3:
      return simd::set_lane<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x2_t set_lane(uint32x2_t vec, const int i, uint32_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x2_t set_lane(int32x2_t vec, const int i, int32_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x2_t set_lane(float32x2_t vec, const int i, float32_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    case 1:
      return simd::set_lane<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x1_t set_lane(uint64x1_t vec, const int i, uint64_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x1_t set_lane(int64x1_t vec, const int i, int64_t a) {
  switch (i) {
    case 0:
      return simd::set_lane<0>(a, vec);
    default:
      __builtin_unreachable();
  }
}
#endif

}  // namespace simd
#undef simd
#undef nce
#pragma once




#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace simd {
#ifdef __ARM_NEON
nce auto shift_left(uint64x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    case 32:
      return shift_left<32>(vec);
    case 33:
      return shift_left<33>(vec);
    case 34:
      return shift_left<34>(vec);
    case 35:
      return shift_left<35>(vec);
    case 36:
      return shift_left<36>(vec);
    case 37:
      return shift_left<37>(vec);
    case 38:
      return shift_left<38>(vec);
    case 39:
      return shift_left<39>(vec);
    case 40:
      return shift_left<40>(vec);
    case 41:
      return shift_left<41>(vec);
    case 42:
      return shift_left<42>(vec);
    case 43:
      return shift_left<43>(vec);
    case 44:
      return shift_left<44>(vec);
    case 45:
      return shift_left<45>(vec);
    case 46:
      return shift_left<46>(vec);
    case 47:
      return shift_left<47>(vec);
    case 48:
      return shift_left<48>(vec);
    case 49:
      return shift_left<49>(vec);
    case 50:
      return shift_left<50>(vec);
    case 51:
      return shift_left<51>(vec);
    case 52:
      return shift_left<52>(vec);
    case 53:
      return shift_left<53>(vec);
    case 54:
      return shift_left<54>(vec);
    case 55:
      return shift_left<55>(vec);
    case 56:
      return shift_left<56>(vec);
    case 57:
      return shift_left<57>(vec);
    case 58:
      return shift_left<58>(vec);
    case 59:
      return shift_left<59>(vec);
    case 60:
      return shift_left<60>(vec);
    case 61:
      return shift_left<61>(vec);
    case 62:
      return shift_left<62>(vec);
    case 63:
      return shift_left<63>(vec);
    default:
      __builtin_unreachable();
  }
}
nce auto shift_left(int64x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    case 32:
      return shift_left<32>(vec);
    case 33:
      return shift_left<33>(vec);
    case 34:
      return shift_left<34>(vec);
    case 35:
      return shift_left<35>(vec);
    case 36:
      return shift_left<36>(vec);
    case 37:
      return shift_left<37>(vec);
    case 38:
      return shift_left<38>(vec);
    case 39:
      return shift_left<39>(vec);
    case 40:
      return shift_left<40>(vec);
    case 41:
      return shift_left<41>(vec);
    case 42:
      return shift_left<42>(vec);
    case 43:
      return shift_left<43>(vec);
    case 44:
      return shift_left<44>(vec);
    case 45:
      return shift_left<45>(vec);
    case 46:
      return shift_left<46>(vec);
    case 47:
      return shift_left<47>(vec);
    case 48:
      return shift_left<48>(vec);
    case 49:
      return shift_left<49>(vec);
    case 50:
      return shift_left<50>(vec);
    case 51:
      return shift_left<51>(vec);
    case 52:
      return shift_left<52>(vec);
    case 53:
      return shift_left<53>(vec);
    case 54:
      return shift_left<54>(vec);
    case 55:
      return shift_left<55>(vec);
    case 56:
      return shift_left<56>(vec);
    case 57:
      return shift_left<57>(vec);
    case 58:
      return shift_left<58>(vec);
    case 59:
      return shift_left<59>(vec);
    case 60:
      return shift_left<60>(vec);
    case 61:
      return shift_left<61>(vec);
    case 62:
      return shift_left<62>(vec);
    case 63:
      return shift_left<63>(vec);
    default:
      __builtin_unreachable();
  }
}
nce auto shift_left(uint32x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    default:
      __builtin_unreachable();
  }
}
nce auto shift_left(int32x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    default:
      __builtin_unreachable();
  }
}
nce auto shift_left(uint16x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    default:
      __builtin_unreachable();
  }
}
nce auto shift_left(int16x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    default:
      __builtin_unreachable();
  }
}
nce auto shift_left(uint8x16_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    default:
      __builtin_unreachable();
  }
}
nce auto shift_left(int8x16_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif
#if ARGON_HAS_DWORD
nce auto shift_left(uint64x1_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    case 32:
      return shift_left<32>(vec);
    case 33:
      return shift_left<33>(vec);
    case 34:
      return shift_left<34>(vec);
    case 35:
      return shift_left<35>(vec);
    case 36:
      return shift_left<36>(vec);
    case 37:
      return shift_left<37>(vec);
    case 38:
      return shift_left<38>(vec);
    case 39:
      return shift_left<39>(vec);
    case 40:
      return shift_left<40>(vec);
    case 41:
      return shift_left<41>(vec);
    case 42:
      return shift_left<42>(vec);
    case 43:
      return shift_left<43>(vec);
    case 44:
      return shift_left<44>(vec);
    case 45:
      return shift_left<45>(vec);
    case 46:
      return shift_left<46>(vec);
    case 47:
      return shift_left<47>(vec);
    case 48:
      return shift_left<48>(vec);
    case 49:
      return shift_left<49>(vec);
    case 50:
      return shift_left<50>(vec);
    case 51:
      return shift_left<51>(vec);
    case 52:
      return shift_left<52>(vec);
    case 53:
      return shift_left<53>(vec);
    case 54:
      return shift_left<54>(vec);
    case 55:
      return shift_left<55>(vec);
    case 56:
      return shift_left<56>(vec);
    case 57:
      return shift_left<57>(vec);
    case 58:
      return shift_left<58>(vec);
    case 59:
      return shift_left<59>(vec);
    case 60:
      return shift_left<60>(vec);
    case 61:
      return shift_left<61>(vec);
    case 62:
      return shift_left<62>(vec);
    case 63:
      return shift_left<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint32x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint16x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(uint8x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int64x1_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    case 32:
      return shift_left<32>(vec);
    case 33:
      return shift_left<33>(vec);
    case 34:
      return shift_left<34>(vec);
    case 35:
      return shift_left<35>(vec);
    case 36:
      return shift_left<36>(vec);
    case 37:
      return shift_left<37>(vec);
    case 38:
      return shift_left<38>(vec);
    case 39:
      return shift_left<39>(vec);
    case 40:
      return shift_left<40>(vec);
    case 41:
      return shift_left<41>(vec);
    case 42:
      return shift_left<42>(vec);
    case 43:
      return shift_left<43>(vec);
    case 44:
      return shift_left<44>(vec);
    case 45:
      return shift_left<45>(vec);
    case 46:
      return shift_left<46>(vec);
    case 47:
      return shift_left<47>(vec);
    case 48:
      return shift_left<48>(vec);
    case 49:
      return shift_left<49>(vec);
    case 50:
      return shift_left<50>(vec);
    case 51:
      return shift_left<51>(vec);
    case 52:
      return shift_left<52>(vec);
    case 53:
      return shift_left<53>(vec);
    case 54:
      return shift_left<54>(vec);
    case 55:
      return shift_left<55>(vec);
    case 56:
      return shift_left<56>(vec);
    case 57:
      return shift_left<57>(vec);
    case 58:
      return shift_left<58>(vec);
    case 59:
      return shift_left<59>(vec);
    case 60:
      return shift_left<60>(vec);
    case 61:
      return shift_left<61>(vec);
    case 62:
      return shift_left<62>(vec);
    case 63:
      return shift_left<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int32x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    case 16:
      return shift_left<16>(vec);
    case 17:
      return shift_left<17>(vec);
    case 18:
      return shift_left<18>(vec);
    case 19:
      return shift_left<19>(vec);
    case 20:
      return shift_left<20>(vec);
    case 21:
      return shift_left<21>(vec);
    case 22:
      return shift_left<22>(vec);
    case 23:
      return shift_left<23>(vec);
    case 24:
      return shift_left<24>(vec);
    case 25:
      return shift_left<25>(vec);
    case 26:
      return shift_left<26>(vec);
    case 27:
      return shift_left<27>(vec);
    case 28:
      return shift_left<28>(vec);
    case 29:
      return shift_left<29>(vec);
    case 30:
      return shift_left<30>(vec);
    case 31:
      return shift_left<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int16x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    case 8:
      return shift_left<8>(vec);
    case 9:
      return shift_left<9>(vec);
    case 10:
      return shift_left<10>(vec);
    case 11:
      return shift_left<11>(vec);
    case 12:
      return shift_left<12>(vec);
    case 13:
      return shift_left<13>(vec);
    case 14:
      return shift_left<14>(vec);
    case 15:
      return shift_left<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_left(int8x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_left<1>(vec);
    case 2:
      return shift_left<2>(vec);
    case 3:
      return shift_left<3>(vec);
    case 4:
      return shift_left<4>(vec);
    case 5:
      return shift_left<5>(vec);
    case 6:
      return shift_left<6>(vec);
    case 7:
      return shift_left<7>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif
}  // namespace simd
#undef simd
#undef nce
#pragma once



#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

#ifdef __clang__
#define nce [[gnu::always_inline]] constexpr
#else
#define nce [[gnu::always_inline]] inline
#endif

namespace simd {

#ifdef __ARM_NEON
nce auto shift_right(uint64x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    case 32:
      return shift_right<32>(vec);
    case 33:
      return shift_right<33>(vec);
    case 34:
      return shift_right<34>(vec);
    case 35:
      return shift_right<35>(vec);
    case 36:
      return shift_right<36>(vec);
    case 37:
      return shift_right<37>(vec);
    case 38:
      return shift_right<38>(vec);
    case 39:
      return shift_right<39>(vec);
    case 40:
      return shift_right<40>(vec);
    case 41:
      return shift_right<41>(vec);
    case 42:
      return shift_right<42>(vec);
    case 43:
      return shift_right<43>(vec);
    case 44:
      return shift_right<44>(vec);
    case 45:
      return shift_right<45>(vec);
    case 46:
      return shift_right<46>(vec);
    case 47:
      return shift_right<47>(vec);
    case 48:
      return shift_right<48>(vec);
    case 49:
      return shift_right<49>(vec);
    case 50:
      return shift_right<50>(vec);
    case 51:
      return shift_right<51>(vec);
    case 52:
      return shift_right<52>(vec);
    case 53:
      return shift_right<53>(vec);
    case 54:
      return shift_right<54>(vec);
    case 55:
      return shift_right<55>(vec);
    case 56:
      return shift_right<56>(vec);
    case 57:
      return shift_right<57>(vec);
    case 58:
      return shift_right<58>(vec);
    case 59:
      return shift_right<59>(vec);
    case 60:
      return shift_right<60>(vec);
    case 61:
      return shift_right<61>(vec);
    case 62:
      return shift_right<62>(vec);
    case 63:
      return shift_right<63>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif

nce auto shift_right(uint32x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    default:
      __builtin_unreachable();
  }
}


nce auto shift_right(uint16x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    default:
      __builtin_unreachable();
  }
}


nce auto shift_right(uint8x16_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    default:
      __builtin_unreachable();
  }
}

#ifdef __ARM_NEON
nce auto shift_right(int64x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    case 32:
      return shift_right<32>(vec);
    case 33:
      return shift_right<33>(vec);
    case 34:
      return shift_right<34>(vec);
    case 35:
      return shift_right<35>(vec);
    case 36:
      return shift_right<36>(vec);
    case 37:
      return shift_right<37>(vec);
    case 38:
      return shift_right<38>(vec);
    case 39:
      return shift_right<39>(vec);
    case 40:
      return shift_right<40>(vec);
    case 41:
      return shift_right<41>(vec);
    case 42:
      return shift_right<42>(vec);
    case 43:
      return shift_right<43>(vec);
    case 44:
      return shift_right<44>(vec);
    case 45:
      return shift_right<45>(vec);
    case 46:
      return shift_right<46>(vec);
    case 47:
      return shift_right<47>(vec);
    case 48:
      return shift_right<48>(vec);
    case 49:
      return shift_right<49>(vec);
    case 50:
      return shift_right<50>(vec);
    case 51:
      return shift_right<51>(vec);
    case 52:
      return shift_right<52>(vec);
    case 53:
      return shift_right<53>(vec);
    case 54:
      return shift_right<54>(vec);
    case 55:
      return shift_right<55>(vec);
    case 56:
      return shift_right<56>(vec);
    case 57:
      return shift_right<57>(vec);
    case 58:
      return shift_right<58>(vec);
    case 59:
      return shift_right<59>(vec);
    case 60:
      return shift_right<60>(vec);
    case 61:
      return shift_right<61>(vec);
    case 62:
      return shift_right<62>(vec);
    case 63:
      return shift_right<63>(vec);
    default:
      __builtin_unreachable();
  }
}
#endif

nce auto shift_right(int32x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    default:
      __builtin_unreachable();
  }
}


nce auto shift_right(int16x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int8x16_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    default:
      __builtin_unreachable();
  }
}

#if ARGON_HAS_DWORD

nce auto shift_right(uint64x1_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    case 32:
      return shift_right<32>(vec);
    case 33:
      return shift_right<33>(vec);
    case 34:
      return shift_right<34>(vec);
    case 35:
      return shift_right<35>(vec);
    case 36:
      return shift_right<36>(vec);
    case 37:
      return shift_right<37>(vec);
    case 38:
      return shift_right<38>(vec);
    case 39:
      return shift_right<39>(vec);
    case 40:
      return shift_right<40>(vec);
    case 41:
      return shift_right<41>(vec);
    case 42:
      return shift_right<42>(vec);
    case 43:
      return shift_right<43>(vec);
    case 44:
      return shift_right<44>(vec);
    case 45:
      return shift_right<45>(vec);
    case 46:
      return shift_right<46>(vec);
    case 47:
      return shift_right<47>(vec);
    case 48:
      return shift_right<48>(vec);
    case 49:
      return shift_right<49>(vec);
    case 50:
      return shift_right<50>(vec);
    case 51:
      return shift_right<51>(vec);
    case 52:
      return shift_right<52>(vec);
    case 53:
      return shift_right<53>(vec);
    case 54:
      return shift_right<54>(vec);
    case 55:
      return shift_right<55>(vec);
    case 56:
      return shift_right<56>(vec);
    case 57:
      return shift_right<57>(vec);
    case 58:
      return shift_right<58>(vec);
    case 59:
      return shift_right<59>(vec);
    case 60:
      return shift_right<60>(vec);
    case 61:
      return shift_right<61>(vec);
    case 62:
      return shift_right<62>(vec);
    case 63:
      return shift_right<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(uint32x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    default:
      __builtin_unreachable();
  }
}



nce auto shift_right(uint16x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    default:
      __builtin_unreachable();
  }
}


nce auto shift_right(uint8x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int64x1_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    case 32:
      return shift_right<32>(vec);
    case 33:
      return shift_right<33>(vec);
    case 34:
      return shift_right<34>(vec);
    case 35:
      return shift_right<35>(vec);
    case 36:
      return shift_right<36>(vec);
    case 37:
      return shift_right<37>(vec);
    case 38:
      return shift_right<38>(vec);
    case 39:
      return shift_right<39>(vec);
    case 40:
      return shift_right<40>(vec);
    case 41:
      return shift_right<41>(vec);
    case 42:
      return shift_right<42>(vec);
    case 43:
      return shift_right<43>(vec);
    case 44:
      return shift_right<44>(vec);
    case 45:
      return shift_right<45>(vec);
    case 46:
      return shift_right<46>(vec);
    case 47:
      return shift_right<47>(vec);
    case 48:
      return shift_right<48>(vec);
    case 49:
      return shift_right<49>(vec);
    case 50:
      return shift_right<50>(vec);
    case 51:
      return shift_right<51>(vec);
    case 52:
      return shift_right<52>(vec);
    case 53:
      return shift_right<53>(vec);
    case 54:
      return shift_right<54>(vec);
    case 55:
      return shift_right<55>(vec);
    case 56:
      return shift_right<56>(vec);
    case 57:
      return shift_right<57>(vec);
    case 58:
      return shift_right<58>(vec);
    case 59:
      return shift_right<59>(vec);
    case 60:
      return shift_right<60>(vec);
    case 61:
      return shift_right<61>(vec);
    case 62:
      return shift_right<62>(vec);
    case 63:
      return shift_right<63>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int32x2_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    case 16:
      return shift_right<16>(vec);
    case 17:
      return shift_right<17>(vec);
    case 18:
      return shift_right<18>(vec);
    case 19:
      return shift_right<19>(vec);
    case 20:
      return shift_right<20>(vec);
    case 21:
      return shift_right<21>(vec);
    case 22:
      return shift_right<22>(vec);
    case 23:
      return shift_right<23>(vec);
    case 24:
      return shift_right<24>(vec);
    case 25:
      return shift_right<25>(vec);
    case 26:
      return shift_right<26>(vec);
    case 27:
      return shift_right<27>(vec);
    case 28:
      return shift_right<28>(vec);
    case 29:
      return shift_right<29>(vec);
    case 30:
      return shift_right<30>(vec);
    case 31:
      return shift_right<31>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int16x4_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    case 8:
      return shift_right<8>(vec);
    case 9:
      return shift_right<9>(vec);
    case 10:
      return shift_right<10>(vec);
    case 11:
      return shift_right<11>(vec);
    case 12:
      return shift_right<12>(vec);
    case 13:
      return shift_right<13>(vec);
    case 14:
      return shift_right<14>(vec);
    case 15:
      return shift_right<15>(vec);
    default:
      __builtin_unreachable();
  }
}

nce auto shift_right(int8x8_t vec, const int i) {
  switch (i) {
    case 1:
      return shift_right<1>(vec);
    case 2:
      return shift_right<2>(vec);
    case 3:
      return shift_right<3>(vec);
    case 4:
      return shift_right<4>(vec);
    case 5:
      return shift_right<5>(vec);
    case 6:
      return shift_right<6>(vec);
    case 7:
      return shift_right<7>(vec);
    default:
      __builtin_unreachable();
  }
}

#endif
}  // namespace simd
#undef simd
#undef nce

#pragma once


#ifdef __ARM_NEON
#include <arm_neon.h>
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#include <arm_mve.h>
#define simd helium
#endif
#endif

namespace simd {
template <typename type> struct Vec128;
template <> struct Vec128<int8_t>  {using type = int8x16_t; };
template <> struct Vec128<uint8_t>  {using type = uint8x16_t; };
template <> struct Vec128<int16_t>  {using type = int16x8_t; };
template <> struct Vec128<uint16_t>  {using type = uint16x8_t; };
template <> struct Vec128<int32_t>  {using type = int32x4_t; };
template <> struct Vec128<uint32_t>  {using type = uint32x4_t; };
template <> struct Vec128<int64_t>  {using type = int64x2_t; };
template <> struct Vec128<uint64_t>  {using type = uint64x2_t; };

#if ARGON_HAS_HALF_FLOAT
template <> struct Vec128<float16_t> {using type = float16x8_t; };
#endif

#if ARGON_HAS_SINGLE_FLOAT
template <> struct Vec128<float>  {using type = float32x4_t; };
#endif

#if ARGON_HAS_DOUBLE_FLOAT
template <> struct Vec128<double> {using type = float64x2_t; };
#endif

template <typename T>
using Vec128_t = typename Vec128<T>::type;

}  // namespace simd
#undef simd




#pragma once



#include <type_traits>
namespace argon::impl {

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

}  // namespace argon::impl
#pragma once
#include <cstddef>



namespace argon::impl {
template <typename T, size_t size> struct MultiVec;
template <> struct MultiVec<int8x16_t, 2> { using type = int8x16x2_t; };
template <> struct MultiVec<uint8x16_t, 2> { using type = uint8x16x2_t; };
template <> struct MultiVec<int16x8_t, 2> { using type = int16x8x2_t; };
template <> struct MultiVec<uint16x8_t, 2> { using type = uint16x8x2_t; };
template <> struct MultiVec<int32x4_t, 2> { using type = int32x4x2_t; };
template <> struct MultiVec<uint32x4_t, 2> { using type = uint32x4x2_t; };
template <> struct MultiVec<int64x2_t, 2> { using type = int64x2x2_t; };
template <> struct MultiVec<uint64x2_t, 2> { using type = uint64x2x2_t; };

template <> struct MultiVec<float32x2_t, 2> { using type = float32x2x2_t; };
template <> struct MultiVec<float32x4_t, 2> { using type = float32x4x2_t; };

template <> struct MultiVec<poly8x8_t, 2> { using type = poly8x8x2_t; };
template <> struct MultiVec<poly16x4_t, 2> { using type = poly16x4x2_t; };


template <> struct MultiVec<int8x16_t, 3> { using type = int8x16x3_t; };
template <> struct MultiVec<uint8x16_t, 3> { using type = uint8x16x3_t; };
template <> struct MultiVec<int16x8_t, 3> { using type = int16x8x3_t; };
template <> struct MultiVec<uint16x8_t, 3> { using type = uint16x8x3_t; };
template <> struct MultiVec<int32x4_t, 3> { using type = int32x4x3_t; };
template <> struct MultiVec<uint32x4_t, 3> { using type = uint32x4x3_t; };
template <> struct MultiVec<int64x2_t, 3> { using type = int64x2x3_t; };
template <> struct MultiVec<uint64x2_t, 3> { using type = uint64x2x3_t; };

template <> struct MultiVec<float32x2_t, 3> { using type = float32x2x3_t; };
template <> struct MultiVec<float32x4_t, 3> { using type = float32x4x3_t; };

template <> struct MultiVec<poly8x8_t, 3> { using type = poly8x8x3_t; };
template <> struct MultiVec<poly16x4_t, 3> { using type = poly16x4x3_t; };

template <> struct MultiVec<int8x16_t, 4> { using type = int8x16x4_t; };
template <> struct MultiVec<uint8x16_t, 4> { using type = uint8x16x4_t; };
template <> struct MultiVec<int16x8_t, 4> { using type = int16x8x4_t; };
template <> struct MultiVec<uint16x8_t, 4> { using type = uint16x8x4_t; };
template <> struct MultiVec<int32x4_t, 4> { using type = int32x4x4_t; };
template <> struct MultiVec<uint32x4_t, 4> { using type = uint32x4x4_t; };
template <> struct MultiVec<int64x2_t, 4> { using type = int64x2x4_t; };
template <> struct MultiVec<uint64x2_t, 4> { using type = uint64x2x4_t; };

template <> struct MultiVec<float32x2_t, 4> { using type = float32x2x4_t; };
template <> struct MultiVec<float32x4_t, 4> { using type = float32x4x4_t; };

template <> struct MultiVec<poly8x8_t, 4> { using type = poly8x8x4_t; };
template <> struct MultiVec<poly16x4_t, 4> { using type = poly16x4x4_t; };

#if ARGON_HAS_DWORD
template <> struct MultiVec<int8x8_t, 2> { using type = int8x8x2_t; };
template <> struct MultiVec<uint8x8_t, 2> { using type = uint8x8x2_t; };
template <> struct MultiVec<int16x4_t, 2> { using type = int16x4x2_t; };
template <> struct MultiVec<uint16x4_t, 2> { using type = uint16x4x2_t; };
template <> struct MultiVec<int32x2_t, 2> { using type = int32x2x2_t; };
template <> struct MultiVec<uint32x2_t, 2> { using type = uint32x2x2_t; };
template <> struct MultiVec<int64x1_t, 2> { using type = int64x1x2_t; };
template <> struct MultiVec<uint64x1_t, 2> { using type = uint64x1x2_t; };

template <> struct MultiVec<int8x8_t, 3> { using type = int8x8x3_t; };
template <> struct MultiVec<uint8x8_t, 3> { using type = uint8x8x3_t; };
template <> struct MultiVec<int16x4_t, 3> { using type = int16x4x3_t; };
template <> struct MultiVec<uint16x4_t, 3> { using type = uint16x4x3_t; };
template <> struct MultiVec<int32x2_t, 3> { using type = int32x2x3_t; };
template <> struct MultiVec<uint32x2_t, 3> { using type = uint32x2x3_t; };
template <> struct MultiVec<int64x1_t, 3> { using type = int64x1x3_t; };
template <> struct MultiVec<uint64x1_t, 3> { using type = uint64x1x3_t; };

template <> struct MultiVec<int8x8_t, 4> { using type = int8x8x4_t; };
template <> struct MultiVec<uint8x8_t, 4> { using type = uint8x8x4_t; };
template <> struct MultiVec<int16x4_t, 4> { using type = int16x4x4_t; };
template <> struct MultiVec<uint16x4_t, 4> { using type = uint16x4x4_t; };
template <> struct MultiVec<int32x2_t, 4> { using type = int32x2x4_t; };
template <> struct MultiVec<uint32x2_t, 4> { using type = uint32x2x4_t; };
template <> struct MultiVec<int64x1_t, 4> { using type = int64x1x4_t; };
template <> struct MultiVec<uint64x1_t, 4> { using type = uint64x1x4_t; };
#endif

template <typename T, size_t size>
using MultiVec_t = MultiVec<T, size>::type;
}
#pragma once


namespace argon::impl {
template <typename T> struct Result;
template <> struct Result<int8x16_t> { using type = uint8x16_t; };
template <> struct Result<uint8x16_t> { using type = uint8x16_t; };
template <> struct Result<int16x8_t> { using type = uint16x8_t; };
template <> struct Result<uint16x8_t> { using type = uint16x8_t; };
template <> struct Result<int32x4_t> { using type = uint32x4_t; };
template <> struct Result<uint32x4_t> { using type = uint32x4_t; };
template <> struct Result<int64x2_t> { using type = uint64x2_t; };
template <> struct Result<uint64x2_t> { using type = uint64x2_t; };
#if ARGON_HAS_SINGLE_FLOAT
template <> struct Result<float32x4_t> { using type = uint32x4_t; };
#endif

#if ARGON_HAS_DWORD
template <> struct Result<int8x8_t> { using type = uint8x8_t; };
template <> struct Result<uint8x8_t> { using type = uint8x8_t; };
template <> struct Result<int16x4_t> { using type = uint16x4_t; };
template <> struct Result<uint16x4_t> { using type = uint16x4_t; };
template <> struct Result<int32x2_t> { using type = uint32x2_t; };
template <> struct Result<uint32x2_t> { using type = uint32x2_t; };
template <> struct Result<int64x1_t> { using type = uint64x1_t; };
template <> struct Result<uint64x1_t> { using type = uint64x1_t; };

#if ARGON_HAS_SINGLE_FLOAT
template <> struct Result<float32x2_t> { using type = uint32x2_t; };
#endif
#endif

template <typename T>
using Result_t = Result<T>::type;
}
#pragma once
#include <array>
#pragma once



#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

template <typename T>
class ArgonHalf;
template <typename T>
class Argon;

namespace argon::impl {

template <typename T>
struct ArgonFor;

template <simd::is_vector_type T>
  requires simd::is_quadword<T>
struct ArgonFor<T> {
  using type = Argon<typename simd::NonVec<T>::type>;
};

#if ARGON_HAS_DWORD
template <simd::is_vector_type T>
  requires simd::is_doubleword<T>
struct ArgonFor<T> {
  using type = ArgonHalf<typename simd::NonVec<T>::type>;
};
#endif

template <typename T>
using ArgonFor_t = typename ArgonFor<T>::type;
}  // namespace argon::impl
#undef simd

namespace argon {
namespace detail {
template <class intrinsic_type, std::size_t N, std::size_t... I>
constexpr std::array<impl::ArgonFor_t<intrinsic_type>, N> to_array_impl(intrinsic_type (&a)[N],
                                                                        std::index_sequence<I...>) {
  using argon_type = impl::ArgonFor_t<intrinsic_type>;
  return {{argon_type{a[I]}...}};
}

template <class intrinsic_type, std::size_t N, std::size_t... I>
constexpr std::array<impl::ArgonFor_t<intrinsic_type>, N> to_array_impl(intrinsic_type (&&a)[N],
                                                                        std::index_sequence<I...>) {
  using argon_type = impl::ArgonFor_t<intrinsic_type>;
  return {{argon_type{std::move(a[I])}...}};
}
}  // namespace detail

template <class intrinsic_type, std::size_t N>
constexpr std::array<impl::ArgonFor_t<intrinsic_type>, N> to_array(intrinsic_type (&a)[N]) {
  return detail::to_array_impl(a, std::make_index_sequence<N>{});
}

template <class intrinsic_type, std::size_t N>
constexpr std::array<impl::ArgonFor_t<intrinsic_type>, N> to_array(intrinsic_type (&&a)[N]) {
  return detail::to_array_impl(std::move(a), std::make_index_sequence<N>{});
}

}  // namespace argon


#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

#ifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif

namespace argon::impl {
template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename T, typename... Ts>
inline constexpr bool is_one_of = std::disjunction_v<std::is_same<T, Ts>...>;

template <typename vector_type>
class Lane;

template <typename vector_type>
class Common {
 public:
  using scalar_type = simd::NonVec_t<vector_type>;
  using lane_type = Lane<vector_type>;
  using result_type = Result_t<vector_type>;
  using argon_result_type = ArgonFor_t<result_type>;
  using argon_type = ArgonFor_t<vector_type>;

  static constexpr size_t lanes = (simd::is_quadword_v<vector_type> ? 16 : 8) / sizeof(scalar_type);

  constexpr Common() : vec_{0} {};
  constexpr Common(vector_type vector) : vec_{vector} {};
  ace Common(scalar_type scalar) : vec_(FromScalar(scalar)) {};

  template <simd::is_vector_type intrinsic_type>
    requires std::is_same_v<scalar_type, simd::NonVec_t<intrinsic_type>>
  ace Common(argon::impl::Lane<intrinsic_type> lane) : vec_(FromLane(lane)) {};

  ace static argon_type FromScalar(scalar_type* ptr) { return simd::load1_duplicate(ptr); }

  ace static argon_type FromScalar(scalar_type scalar) {
#if ARGON_HAS_DWORD
    return simd::duplicate<vector_type>(scalar);
#else
    return simd::duplicate(scalar);
#endif
  }

  template <simd::is_vector_type intrinsic_type>
  ace static argon_type FromLane(argon::impl::Lane<intrinsic_type> lane)
    requires simd::is_quadword<vector_type>
  {
    return simd::duplicate_lane_quad(lane.vec(), lane.lane());
  }

#if ARGON_HAS_DWORD
  template <simd::is_vector_type intrinsic_type>
  ace static argon_type FromLane(argon::impl::Lane<intrinsic_type> lane)
    requires simd::is_doubleword<vector_type>
  {
    return simd::duplicate_lane(lane.vec(), lane.lane());
  }
#endif

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type()>>
  ace static argon_type Generate(FuncType body) {
    vector_type out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body();
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type)>>
  ace static argon_type GenerateWithIndex(FuncType body) {
    vector_type out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(i);
    }
    return out;
  }

  ace argon_type operator-() const { return Negate(); }

  ace argon_type operator+(argon_type b) const { return Add(b); }
  ace argon_type operator-(argon_type b) const { return Subtract(b); }
  ace argon_type operator*(argon_type b) const { return Multiply(b); }
  ace argon_type operator/(argon_type b) const { return Divide(b); }

  ace argon_result_type operator==(argon_type b) const { return Equal(b); }
  ace argon_result_type operator<(argon_type b) const { return LessThan(b); }
  ace argon_result_type operator>(argon_type b) const { return GreaterThan(b); }
  ace argon_result_type operator<=(argon_type b) const { return LessThanOrEqual(b); }
  ace argon_result_type operator>=(argon_type b) const { return GreaterThanOrEqual(b); }

  ace argon_type operator++() const { return Add(1); }
  ace argon_type operator--() const { return Subtract(1); }

  ace argon_type operator&(argon_type b) const { return BitwiseAnd(b); }
  ace argon_type operator|(argon_type b) const { return BitwiseOr(b); }
  ace argon_type operator^(argon_type b) const { return BitwiseXor(b); }
  ace argon_type operator~() const { return BitwiseNot(); }

  ace const lane_type operator[](const int i) const { return lane_type{vec_, i}; }
  ace lane_type operator[](const int i) { return lane_type{vec_, i}; }

  ace argon_type operator>>(const int i) const { return ShiftRight(i); }
  ace argon_type operator<<(const int i) const { return ShiftLeft(i); }

  [[gnu::always_inline]] constexpr operator vector_type() const { return vec_; }

  ace std::array<scalar_type, lanes> to_array() {
    std::array<scalar_type, lanes> out;
    StoreTo(out.data());
    return out;
  }

  ace vector_type vec() const { return vec_; }

  ace scalar_type GetLane(const int i) { return simd::get_lane(vec_, i); }
  ace lane_type LastLane() { return lane_type{vec_, lanes - 1}; }

  ace argon_type ShiftRight(const int i) const { return simd::shift_right(vec_, i); }
  ace argon_type ShiftLeft(const int i) const { return simd::shift_left(vec_, i); }

  ace argon_type Negate() const { return simd::negate(vec_); }

  ace argon_type Add(argon_type b) const { return simd::add(vec_, b); }
  ace argon_type AddHalve(argon_type b) const { return simd::add_halve(vec_, b); }
  ace argon_type AddHalveRound(argon_type b) const { return simd::add_halve_round(vec_, b); }
  ace argon_type AddSaturate(argon_type b) const { return simd::add_saturate(vec_, b); }

  ace argon_type Subtract(argon_type b) const { return simd::subtract(vec_, b); }
  ace argon_type SubtractHalve(argon_type b) const { return simd::subtract_halve(vec_, b); }
  ace argon_type SubtractSaturate(argon_type b) const { return simd::subtract_saturate(vec_, b); }
  ace argon_type SubtractAbs(argon_type b) const { return simd::subtract_absolute(vec_, b); }
  ace argon_type SubtractAbsAdd(argon_type b, argon_type c) const { return simd::subtract_absolute_add(vec_, b, c); }

  ace argon_type Multiply(argon_type b) const { return simd::multiply(vec_, b); }
  ace argon_type Multiply(scalar_type b) const { return simd::multiply(vec_, b); }
  ace argon_type Multiply(lane_type b) const { return simd::multiply_lane(vec_, b.vec(), b.lane()); }

  ace argon_type MultiplyAdd(argon_type b, argon_type c) const { return simd::multiply_add(vec_, b, c); }
  ace argon_type MultiplyAdd(argon_type b, scalar_type c) const { return simd::multiply_add(vec_, b, c); }
  ace argon_type MultiplyAdd(argon_type b, lane_type c) const {
    return simd::multiply_add_lane(vec_, b.vec(), c.vec(), c.lane());
  }

  ace argon_type MultiplySubtract(argon_type b, argon_type c) const { return simd::multiply_subtract(vec_, b, c); }
  ace argon_type MultiplySubtract(argon_type b, scalar_type c) const { return simd::multiply_subtract(vec_, b, c); }
  ace argon_type MultiplySubtract(argon_type b, lane_type c) const {
    return simd::multiply_subtract_lane(vec_, b.vec(), c.vec(), c.lane());
  }

  ace argon_type MultiplyFixedPoint(argon_type v) const { return simd::multiply_double_saturate_high(vec_, v); }
  ace argon_type MultiplyFixedPoint(scalar_type s) const { return simd::multiply_double_saturate_high(vec_, s); }
  ace argon_type MultiplyFixedPoint(lane_type l) const {
    return simd::multiply_double_saturate_high_lane(vec_, l.vec(), l.lane());
  }

  ace argon_type MultiplyRoundFixedPoint(argon_type v) const {
    return simd::multiply_double_round_saturate_high(vec_, v);
  }
  ace argon_type MultiplyRoundFixedPoint(scalar_type s) const {
    return simd::multiply_double_round_saturate_high(vec_, s);
  }
  ace argon_type MultiplyRoundFixedPoint(lane_type l) const {
    return simd::multiply_double_round_saturate_high_lane(vec_, l.vec(), l.lane());
  }

  template <typename arg_type>
    requires(is_one_of<arg_type, argon_type, scalar_type, lane_type> || std::is_convertible_v<arg_type, argon_type> ||
             std::is_convertible_v<arg_type, scalar_type>)
  ace argon_type MultiplyAddFixedPoint(argon_type b, arg_type c) const {
    return Add(b.MultiplyFixedPoint(c));
  }

  template <typename arg_type>
    requires(is_one_of<arg_type, argon_type, scalar_type, lane_type> || std::is_convertible_v<arg_type, argon_type> ||
             std::is_convertible_v<arg_type, scalar_type>)
  ace argon_type MultiplyRoundAddFixedPoint(argon_type b, arg_type c) const {
    return Add(b.MultiplyRoundFixedPoint(c));
  }

  ace argon_type Divide(argon_type b) const
    requires std::floating_point<scalar_type>
  {
#ifdef __aarch64__
    return simd::divide(vec_, b);
#else
    return this->map2(b, [](scalar_type lane1, scalar_type lane2) { return lane1 / lane2; });
#endif
  }

  ace argon_type Max(argon_type b) const { return simd::max(vec_, b); }
  ace argon_type Min(argon_type b) const { return simd::min(vec_, b); }

  ace argon_result_type Equal(argon_type b) const { return simd::equal(vec_, b); }
  ace argon_result_type GreaterThanOrEqual(argon_type b) const { return simd::greater_than_or_equal(vec_, b); }
  ace argon_result_type LessThanOrEqual(argon_type b) const { return simd::less_than_or_equal(vec_, b); }
  ace argon_result_type GreaterThan(argon_type b) const { return simd::greater_than(vec_, b); }
  ace argon_result_type LessThan(argon_type b) const { return simd::less_than(vec_, b); }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, typename ArgonFor<simd::make_signed_t<vector_type>>::type>)
  ace argon_type ShiftLeft(signed_vector b) const
    requires std::is_integral_v<scalar_type>
  {
    return simd::shift_left(vec_, b);
  }

  template <int n>
  ace argon_type ShiftLeft() const {
    return simd::shift_left<n>(vec_);
  }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, typename ArgonFor<simd::make_signed_t<vector_type>>::type>)
  ace argon_type ShiftLeftSaturate(signed_vector b) const {
    return simd::shift_left_saturate(vec_, b);
  }

  ace argon_type ShiftLeftRound(argon_type b) const { return simd::shift_left_round(vec_, b); }
  ace argon_type ShiftLeftRoundSaturate(argon_type b) const { return simd::shift_left_round_saturate(vec_, b); }

  template <int n>
  ace argon_type ShiftLeftSaturate() const {
    return simd::shift_left_saturate<n>(vec_);
  }
  template <int n>
  ace argon_type ShiftLeftInsert(argon_type b) const {
    return simd::shift_left_insert<n>(vec_, b);
  }

  template <int n>
  ace argon_type ShiftRight() const {
    return simd::shift_right<n>(vec_);
  }
  template <int n>
  ace argon_type ShiftRightRound() const {
    return simd::shift_right_round<n>(vec_);
  }
  template <int n>
  ace argon_type ShiftRightAccumulate(argon_type b) const {
    return simd::shift_right_accumulate<n>(vec_, b);
  }
  template <int n>
  ace argon_type ShiftRightAccumulateRound(argon_type b) const {
    return simd::shift_right_accumulate_round<n>(vec_, b);
  }
  template <int n>
  ace argon_type ShiftRightInsert(argon_type b) const {
    return simd::shift_right_insert<n>(vec_, b);
  }

  ace static argon_type Load(const scalar_type* ptr) { return simd::load1<vector_type>(ptr); }
  ace static argon_type LoadCopy(const scalar_type* ptr) { return simd::load1_duplicate<vector_type>(ptr); }

  template <simd::is_vector_type intrinsic_type>
  ace static argon_type LoadGather(const scalar_type* base, intrinsic_type offset_vector) {
    using offset_type = simd::NonVec_t<intrinsic_type>;
    static_assert(std::is_unsigned_v<offset_type>, "Offset elements must be unsigned values");
    static_assert((sizeof(intrinsic_type) / sizeof(offset_type)) == lanes,
                  "Number of elements in offset vector must match number of elements in destination vector");
    argon_type destination;
    constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      offset_type lane_val = simd::get_lane<i>(offset_vector);
      destination = destination.template LoadToLane<i>(base + lane_val);
    });
    return destination;
  }

  template <typename T>
  ace static argon_type LoadGather(const scalar_type* base, T offset_vector) {
    return argon_type::template LoadGather<typename T::vector_type>(base, offset_vector);
  }

  template <size_t lane>
  ace argon_type LoadToLane(const scalar_type* ptr) {
    if constexpr (simd::is_quadword_v<vector_type>) {
      return simd::load1_lane_quad<lane>(ptr, vec_);
    } else {
      return simd::load1_lane<lane>(ptr, vec_);
    }
  }

  template <size_t stride>
  ace static std::array<argon_type, stride> LoadCopyInterleaved(const scalar_type* ptr) {
    static_assert(stride > 1 && stride < 5,
                  "De-interleaving LoadCopy can only be performed with a stride of 2, 3, or 4");
    using multivec_type = MultiVec<vector_type, stride>::type;

    if constexpr (stride == 2) {
      return argon::to_array(simd::load2_duplicate<multivec_type>(ptr).val);
    } else if constexpr (stride == 3) {
      return argon::to_array(simd::load3_duplicate<multivec_type>(ptr).val);
    } else if constexpr (stride == 4) {
      return argon::to_array(simd::load4_duplicate<multivec_type>(ptr).val);
    }
  }

  template <size_t stride>
  ace static std::array<argon_type, stride> LoadInterleaved(const scalar_type* ptr) {
    static_assert(stride > 1 && stride < 5, "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
    using multivec_type = MultiVec_t<vector_type, stride>;

    if constexpr (stride == 2) {
      return argon::to_array(simd::load2<multivec_type>(ptr).val);
    } else if constexpr (stride == 3) {
      return argon::to_array(simd::load3<multivec_type>(ptr).val);
    } else if constexpr (stride == 4) {
      return argon::to_array(simd::load4<multivec_type>(ptr).val);
    }
  }

  template <size_t lane, size_t stride>
  ace static std::array<argon_type, stride> LoadToLaneInterleaved(MultiVec_t<vector_type, stride> multi,
                                                                  const scalar_type* ptr) {
    if constexpr (stride == 2) {
      if constexpr (simd::is_quadword_v<vector_type>) {
        return argon::to_array(simd::load2_lane_quad<lane>(ptr, multi).val);
      } else {
        return argon::to_array(simd::load2_lane<lane>(ptr, multi).val);
      }
    } else if constexpr (stride == 3) {
      if constexpr (simd::is_quadword_v<vector_type>) {
        return argon::to_array(simd::load3_lane_quad<lane>(ptr, multi).val);
      } else {
        return argon::to_array(simd::load3_lane<lane>(ptr, multi).val);
      }
    } else if constexpr (stride == 4) {
      if constexpr (simd::is_quadword_v<vector_type>) {
        return argon::to_array(simd::load4_lane_quad<lane>(ptr, multi).val);
      } else {
        return argon::to_array(simd::load4_lane<lane>(ptr, multi).val);
      }
    }
  }

  template <size_t lane, size_t stride>
  ace static std::array<argon_type, stride> LoadToLaneInterleaved(std::array<argon_type, stride> multi,
                                                                  const scalar_type* ptr) {
    using multivec_type = MultiVec_t<vector_type, stride>;
    return LoadToLaneInterleaved<lane, stride>(*(multivec_type*)multi.data(), ptr);
  }

  template <size_t stride, simd::is_vector_type intrinsic_type>
  ace static std::array<argon_type, stride> LoadGatherInterleaved(const scalar_type* base_ptr,
                                                                  intrinsic_type offset_vector) {
    using offset_type = simd::NonVec_t<intrinsic_type>;
    static_assert(stride > 1 && stride < 5, "De-interleaving Loads can only be performed with a stride of 2, 3, or 4");
    static_assert(std::is_unsigned_v<offset_type>, "Offset elements must be unsigned values");
    static_assert((sizeof(intrinsic_type) / sizeof(offset_type)) == lanes,
                  "Number of elements in offset vector must match number of elements in destination vector");
    std::array<argon_type, stride> multi;
    constexpr_for<0, lanes, 1>([&]<int i>() {  //<
      offset_type lane_val = simd::get_lane<i>(offset_vector);
      multi = LoadToLaneInterleaved<i, stride>(multi, base_ptr + lane_val);
    });
    return multi;
  }

  template <size_t stride, typename T>
  ace static std::array<argon_type, stride> LoadGatherInterleaved(const scalar_type* base_ptr, T offset_vector) {
    return argon_type::template LoadGatherInterleaved<stride, typename T::vector_type>(base_ptr, offset_vector);
  }

  template <size_t n>
  ace static std::array<argon_type, n> LoadMulti(const scalar_type* ptr) {
    static_assert(n > 1 && n < 5, "LoadMulti can only be performed with a size of 2, 3, or 4");
    using multivec_type = MultiVec_t<vector_type, n>;
    using array_type = std::array<argon_type, n>;

    if constexpr (n == 2) {
      return argon::to_array(simd::load1_x2(ptr).val);
    } else if constexpr (n == 3) {
      return argon::to_array(simd::load1_x3(ptr).val);
    } else if constexpr (n == 4) {
      return argon::to_array(simd::load1_x4(ptr).val);
    }
  }

  ace void StoreTo(scalar_type* ptr) const {
    simd::store1(ptr, vec_);
  }

  template <int lane>
  ace void StoreLaneTo(scalar_type* ptr) {
    simd::store1_lane<lane>(ptr, vec_);
  }


  ace argon_type PairwiseAdd(argon_type b) const { return simd::pairwise_add(vec_, b); }
  ace argon_type PairwiseMax(argon_type b) const { return simd::pairwise_max(vec_, b); }
  ace argon_type PairwiseMin(argon_type b) const { return simd::pairwise_min(vec_, b); }


  ace argon_type BitwiseNot() const { return simd::bitwise_not(vec_); }
  ace argon_type BitwiseAnd(argon_type b) const { return simd::bitwise_and(vec_, b); }
  ace argon_type BitwiseOr(argon_type b) const { return simd::bitwise_or(vec_, b); }
  ace argon_type BitwiseXor(argon_type b) const { return simd::bitwise_xor(vec_, b); }
  ace argon_type BitwiseOrNot(argon_type b) const { return simd::bitwise_or_not(vec_, b); }
  ace argon_type BitwiseClear(argon_type b) const { return simd::bitwise_clear(vec_, b); }
  ace argon_type BitwiseSelect(argon_type b, argon_type c) const { return simd::bitwise_select(vec_, b, c); }

  ace argon_type CompareTestNonzero(argon_type b) const { return simd::compare_test_nonzero(vec_, b); }
  ace argon_type TestNonzero() const { return simd::compare_test_nonzero(vec_, argon_type{1}); }

  template <typename signed_vector>
    requires(std::is_integral_v<scalar_type> &&
             std::is_same_v<signed_vector, ArgonFor_t<simd::make_signed_t<vector_type>>>)
  ace signed_vector CountLeadingSignBits() const {
    return simd::count_leading_sign_bits(vec_);
  }

  ace argon_type CountLeadingZeroBits() const { return simd::count_leading_zero_bits(vec_); }
  ace argon_type CountActiveBits() const { return simd::count_active_bits(vec_); }

  template <int n>
  ace argon_type Extract(argon_type b) const {
    return simd::extract<n>(vec_, b);
  }

  ace argon_type Reverse64bit() const { return simd::reverse_64bit(vec_); }
  ace argon_type Reverse32bit() const { return simd::reverse_32bit(vec_); }
  ace argon_type Reverse16bit() const { return simd::reverse_16bit(vec_); }

  ace std::array<argon_type, 2> ZipWith(argon_type b) const {
    return std::bit_cast<std::array<argon_type, 2>>(std::to_array(simd::transpose(vec_, b.vec()).val));
  }

  std::array<argon_type, 2> UnzipWith(argon_type b) {
    return std::bit_cast<std::array<argon_type, 2>>(std::to_array(simd::transpose(vec_, b.vec()).val));
  }

  std::tuple<argon_type, argon_type> TransposeWith(argon_type b) const {
    auto result = simd::transpose(vec_, b.vec());
    return std::tuple<argon_type, argon_type>(result.val[0], result.val[1]);
  }

  ace static int size() { return lanes; }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type)>>
  ace argon_type map(FuncType body) const {
    vector_type out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type, int)>>
  ace argon_type map_with_index(FuncType body) const {
    vector_type out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i], i);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<scalar_type(scalar_type, scalar_type)>>
  ace argon_type map2(argon_type other, FuncType body) const {
    vector_type out;
    for (size_t i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i], other.vec_[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&)>>
  ace argon_type each_lane(FuncType body) {
    vector_type out = vec_;
    for (size_t i = 0; i < lanes; ++i) {
      body(out[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(scalar_type&, int)>>
  ace argon_type each_lane_with_index(FuncType body) {
    vector_type out = vec_;
    for (size_t i = 0; i < lanes; ++i) {
      body(out[i], i);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_lane(FuncType true_branch) {
    for (size_t i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch();
      }
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_else_lane(FuncType true_branch, FuncType false_branch) {
    for (size_t i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch();
      } else {
        false_branch();
      }
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(int)>>
  ace void if_lane_with_index(FuncType true_branch) {
    for (size_t i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch(i);
      }
    }
  }

  template <typename FuncType1, typename FuncType2>
    requires std::convertible_to<FuncType1, std::function<void(int)>> &&
             std::convertible_to<FuncType2, std::function<void(int)>>
  ace void if_else_lane_with_index(FuncType1 true_branch, FuncType2 false_branch) {
    for (size_t i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch(i);
      } else {
        false_branch(i);
      }
    }
  }

  ace bool any() {
    for (size_t i = 0; i < lanes; ++i) {
      if (vec_[i]) {
        return true;
      }
    }
    return false;
  }

  ace bool all() {
    auto nonzero = TestNonzero();
    for (size_t i = 0; i < lanes; ++i) {
      if (nonzero[i] == 0) {
        return false;
      }
    }
    return true;
  }

  template <std::size_t Index>
  std::tuple_element_t<Index, argon_type> get() {
    return Lane{vec_, Index};
  }

 protected:
  vector_type vec_;
};

template <typename vector_type>
class Lane {
  using scalar_type = simd::NonVec_t<vector_type>;
  using type = Lane<vector_type>;
  using argon_type = ArgonFor_t<vector_type>;

 public:
  ace Lane(vector_type& vec, const int lane) : vec_{vec}, lane_{lane} {}
  ace operator scalar_type() { return simd::get_lane(vec_, lane_); }
  ace argon_type operator=(scalar_type b) { return Set(b); }
  ace argon_type Load(scalar_type* ptr) { return vec_ = simd::load1_lane(vec_, lane_, ptr); }
  ace argon_type Set(scalar_type b) { return vec_ = simd::set_lane(vec_, lane_, b); }

#if __ARM_ARCH >= 8
  ace vector_type& vec() { return vec_; }
  ace const int lane() { return lane_; }
#else
  ace vector_type& vec() {
    if constexpr (simd::is_doubleword_v<vector_type>) {
      return vec_;
    } else if constexpr (simd::is_quadword_v<vector_type>) {
      if (lane_ >= ArgonHalf<scalar_type>::lanes) {
        return simd::get_high(vec_);
      } else {
        return simd::get_low(vec_);
      }
    }
  }
  ace const int lane() {
    if constexpr (simd::is_doubleword_v<vector_type>) {
      return lane_;
    } else if constexpr (simd::is_quadword_v<vector_type>) {
      if (lane_ >= ArgonHalf<scalar_type>::lanes) {
        return (lane_ - ArgonHalf<scalar_type>::lanes);
      } else {
        return lane_;
      }
    }
  }
#endif

 private:
  vector_type& vec_;
  int lane_;
};

}  // namespace argon::impl

namespace std {
template <typename T>
struct tuple_size<argon::impl::Common<T>> {
  static constexpr size_t value = argon::impl::Common<T>::lanes;
};

template <size_t Index, typename T>
struct tuple_element<Index, argon::impl::Common<T>> {
  static_assert(Index < argon::impl::Common<T>::lanes);
  using type = argon::impl::Common<T>::lane_type;
};
}  // namespace std

#undef ace
#undef simd


#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

#ifdef __clang__
#define ace [[nodiscard]] [[gnu::always_inline]] constexpr
#else
#define ace [[nodiscard]] [[gnu::always_inline]] inline
#endif

template <typename scalar_type>
class Argon : public argon::impl::Common<simd::Vec128_t<scalar_type>> {
  using T = argon::impl::Common<simd::Vec128_t<scalar_type>>;

 public:
  using vector_type = simd::Vec128_t<scalar_type>;
  using lane_type = const argon::impl::Lane<vector_type>;

  static_assert(simd::is_quadword_v<vector_type>);

  static constexpr size_t bytes = 16;
  static constexpr size_t lanes = bytes / sizeof(scalar_type);

  ace Argon() : T(){};
  ace Argon(vector_type vector) : T{vector} {};
  ace Argon(scalar_type scalar) : T{scalar} {};
  ace Argon(T&& in) : T(in){};
  ace Argon(std::array<scalar_type, 4> value_list) : T{T::Load(value_list.data())} {};
  ace Argon(ArgonHalf<scalar_type> low, ArgonHalf<scalar_type> high) : T{Combine(low, high)} {};

  template <typename... arg_types>
    requires(sizeof...(arg_types) > 1)
  ace Argon(arg_types... args) : T{vector_type{args...}} {}

  template <simd::is_vector_type intrinsic_type>
  ace Argon(argon::impl::Lane<intrinsic_type> b) : T{b} {};

  template <typename new_scalar_type>
  ace Argon<new_scalar_type> As() const {
    return simd::reinterpret<simd::Vec128_t<new_scalar_type>>(this->vec_);
  }

  ace static Argon<scalar_type> Combine(ArgonHalf<scalar_type> low, ArgonHalf<scalar_type> high) {
    return simd::combine(low, high);
  }

  ace Argon<scalar_type> Reverse() {
    auto rev_half = this->Reverse64bit();
    return Combine(rev_half.GetHigh(), rev_half.GetLow());
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplyAddLong(ArgonHalf<U> b, ArgonHalf<U> c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }
  template <typename U, typename C>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<C, simd::Vec64_t<argon::impl::NextSmaller_t<scalar_type>>>
  ace Argon<scalar_type> MultiplyAddLong(ArgonHalf<U> b, C c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplyAddLong(ArgonHalf<U> b, U c) {
    return simd::multiply_add_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplyAddLong(ArgonHalf<U> b, typename ArgonHalf<U>::lane_type c) {
    return simd::multiply_add_long(this->vec_, b, c.vec(), c.lane());
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplySubtractLong(ArgonHalf<U> b, ArgonHalf<U> c) {
    return simd::multiply_subtract_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplySubtractLong(ArgonHalf<U> b, U c) {
    return simd::multiply_subtract_long(this->vec_, b, c);
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<U, typename argon::impl::NextSmaller<scalar_type>::type>
  ace Argon<scalar_type> MultiplySubtractLong(ArgonHalf<U> b, typename ArgonHalf<U>::lane_type c) {
    return simd::multiply_subtract_long(this->vec_, b, c.vec(), c.lane());
  }

  ace auto AddNarrow(Argon<scalar_type> b) const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    auto result = simd::add_narrow(this->vec_, b);
    return argon::impl::ArgonFor_t<decltype(result)>{result};
  }

  ace auto AddRoundNarrow(Argon<scalar_type> b) const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    auto result = simd::add_round_narrow(this->vec_, b);
    return argon::impl::ArgonFor_t<decltype(result)>{result};
  }

  ace auto SubtractNarrow(Argon<scalar_type> b) const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    auto result = simd::subtract_narrow(this->vec_, b);
    return argon::impl::ArgonFor_t<decltype(result)>{result};
  }

  ace auto SubtractRoundNarrow(Argon<scalar_type> b) const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    auto result = simd::subtract_round_narrow(this->vec_, b);
    return argon::impl::ArgonFor_t<decltype(result)>{result};
  }

  template <size_t n>
    requires argon::impl::has_smaller_v<scalar_type>
  ace auto ShiftRightNarrow() const {
    auto result = simd::shift_right_narrow<n>(this->vec_);
    return argon::impl::ArgonFor_t<decltype(result)>{result};
  }

  template <size_t n>
    requires argon::impl::has_smaller_v<scalar_type>
  ace auto ShiftRightSaturateNarrow() const {
    auto result = simd::shift_right_saturate_narrow<n>(this->vec_);
    return argon::impl::ArgonFor_t<decltype(result)>{result};
  }

  template <size_t n>
    requires argon::impl::has_smaller_v<scalar_type>
  ace auto ShiftRightRoundSaturateNarrow() const {
    auto result = simd::shift_right_round_saturate_narrow<n>(this->vec_);
    return argon::impl::ArgonFor_t<decltype(result)>{result};
  }

  template <size_t n>
    requires argon::impl::has_smaller_v<scalar_type>
  ace auto ShiftRightRoundNarrow() const {
    auto result = simd::shift_right_round_narrow<n>(this->vec_);
    return argon::impl::ArgonFor_t<decltype(result)>{result};
  }

  ace auto Narrow() const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    auto result = simd::move_narrow(this->vec_);
    return argon::impl::ArgonFor_t<decltype(result)>{result};
  }

  ace auto SaturateNarrow() const
    requires argon::impl::has_smaller_v<scalar_type>
  {
    auto result = simd::move_saturate_narrow(this->vec_);
    return argon::impl::ArgonFor_t<decltype(result)>{result};
  }

  template <typename NextSmallerType>
    requires argon::impl::has_smaller_v<scalar_type> &&
             std::is_same_v<NextSmallerType, argon::impl::NextSmaller_t<scalar_type>>
  ace Argon<scalar_type> MultiplyDoubleAddSaturateLong(ArgonHalf<NextSmallerType> b, ArgonHalf<NextSmallerType> c) {
    return neon::multiply_double_add_saturate_long(this->vec_, b, c);
  }

  ace ArgonHalf<scalar_type> GetHigh() const { return simd::get_high(this->vec_); }
  ace ArgonHalf<scalar_type> GetLow() const { return simd::get_low(this->vec_); }

  template <typename U>
  ace Argon<U> ConvertTo() const {
    return simd::convert<typename simd::Vec128<U>::type>(this->vec_);
  }
  template <typename U, int fracbits>
    requires(std::is_same_v<U, uint32_t> || std::is_same_v<U, int32_t> || std::is_same_v<U, float>)
  ace Argon<U> ConvertTo() const {
    if constexpr (std::is_same_v<U, float>) {
      return neon::convert_n<fracbits>(this->vec_);
    } else if constexpr (std::is_unsigned_v<U>) {
      return neon::convert_n_unsigned<fracbits>(this->vec_);
    } else if constexpr (std::is_signed_v<U>) {
      return neon::convert_n_signed<fracbits>(this->vec_);
    }
  }

  ace Argon<scalar_type> Reverse() const {
    Argon<scalar_type> rev = this->Reverse64bit();  // rev within dword
    return Argon{rev.GetHigh(), rev.GetLow()};      // swap dwords
  }

  scalar_type ReduceAdd() {
#ifdef __aarch64__
    return simd::reduce_add(this->vec_);
#else
    auto rev = this->SwapDoublewords();
    auto sum = this->Add(rev);
    if constexpr (lanes == 16) {
      rev = sum.Reverse16bit();
      sum = sum.Add(rev);
    }
    if constexpr (lanes == 8 || lanes == 16) {
      rev = sum.Reverse32bit();
      sum = sum.Add(rev);
    }
    if constexpr (lanes == 4 || lanes == 8 || lanes == 16) {
      rev = sum.Reverse64bit();
      sum = sum.Add(rev);
    }
    return sum[0];
#endif
  }

  ace Argon<scalar_type> SwapDoublewords() { return Combine(GetHigh(), GetLow()); }
};

template <typename... arg_types>
  requires(sizeof...(arg_types) > 1)
Argon(arg_types...) -> Argon<std::tuple_element_t<0, std::tuple<arg_types...>>>;

template <typename ScalarType>
requires std::is_scalar_v<ScalarType>
Argon(ScalarType) -> Argon<ScalarType>;

template <typename V>
  requires std::is_scalar_v<V>
ace Argon<V> operator+(const V a, const Argon<V> b) {
  return b.Add(a);
}

template <typename V>
  requires std::is_scalar_v<V>
ace Argon<V> operator-(const V a, const Argon<V> b) {
  return Argon<V>{a}.Subtract(b);
}

template <typename V>
  requires std::is_scalar_v<V>
ace Argon<V> operator*(const V a, const Argon<V> b) {
  return b.Multiply(a);
}

template <typename V>
  requires std::is_scalar_v<V>
ace Argon<V> operator/(const V a, const Argon<V> b) {
  return Argon<V>{a}.Divide(b);
}

namespace std {

template <typename T>
struct tuple_size<Argon<T>> {
  static constexpr size_t value = Argon<T>::lanes;
};

template <size_t Index, typename T>
struct tuple_element<Index, Argon<T>> {
  static_assert(Index < Argon<T>::lanes);
  using type = argon::impl::Lane<typename Argon<T>::vector_type>;
};
}  // namespace std

#undef ace
#undef simd
#pragma once


#ifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif

template <typename scalar_type>
class ArgonHalf : public argon::impl::Common<neon::Vec64_t<scalar_type>> {
  using T = argon::impl::Common<neon::Vec64_t<scalar_type>>;

 public:
  using vector_type = neon::Vec64_t<scalar_type>;
  using lane_type = const argon::impl::Lane<vector_type>;

  static_assert(neon::is_doubleword_v<vector_type>);

  static constexpr size_t bytes = 8;
  static constexpr size_t lanes = bytes / sizeof(scalar_type);

  ace ArgonHalf() : T(){};
  ace ArgonHalf(vector_type vector) : T{vector} {};
  ace ArgonHalf(scalar_type scalar) : T{scalar} {};
  ace ArgonHalf(T&& in) : T{in} {};
  ace ArgonHalf(std::array<scalar_type, 2> value_list) : T{T::Load(value_list.data())} {};

  template <neon::is_vector_type intrinsic_type>
  ace ArgonHalf(argon::impl::Lane<intrinsic_type> b) : T(b){};

  template <typename... arg_types>
  requires (sizeof...(arg_types) > 1)
  ace ArgonHalf(arg_types ...args) : T{vector_type{args...}} {}

  ace static ArgonHalf<scalar_type> Create(uint64_t a) { return neon::create<vector_type>(a); }

  template <typename new_scalar_type>
  ace ArgonHalf<new_scalar_type> As() const {
    return neon::reinterpret<neon::Vec64_t<new_scalar_type>>(this->vec_);
  }

  template <typename U>
    requires argon::impl::has_larger_v<scalar_type>
  ace Argon<U> AddLong(ArgonHalf<scalar_type> b) const {
    return neon::add_long(this->vec_, b);
  }

  template <typename U>
    requires argon::impl::has_larger_v<scalar_type>
  ace Argon<U> MultiplyLong(ArgonHalf<scalar_type> b) const {
    return neon::multiply_long(this->vec_, b);
  }

  template <typename U>
    requires argon::impl::has_larger_v<scalar_type>
  ace Argon<U> MultiplyLong(scalar_type b) const {
    return neon::multiply_long(this->vec_, b);
  }

  template <typename U>
    requires argon::impl::has_larger_v<scalar_type>
  ace Argon<U> MultiplyLong(lane_type b) const {
    return neon::multiply_long_lane(this->vec_, b.vec(), b.lane());
  }

  template <typename U>
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Argon<U> MultiplyFixedLong(ArgonHalf<scalar_type> b) const {
    return neon::multiply_subtract_long(this->vec_, b);
  }

  template <typename U>
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Argon<U> MultiplyFixedLong(scalar_type b) const {
    return neon::multiply_subtract_long(this->vec_, b);
  }

  template <typename U>
    requires(std::is_same_v<vector_type, int16x4_t> || std::is_same_v<vector_type, int32x2_t>)
  ace Argon<U> MultiplyFixedLong(lane_type b) const {
    return neon::multiply_subtract_long(this->vec_, b.vec(), b.lane());
  }

  template <typename U>
    requires argon::impl::has_larger_v<scalar_type>
  ace Argon<U> SubtractLong(ArgonHalf<scalar_type> b) const {
    return neon::subtract_long(this->vec_, b);
  }

  template <typename U>
    requires argon::impl::has_larger_v<scalar_type>
  ace Argon<U> SubtractAbsoluteLong(ArgonHalf<scalar_type> b) const {
    return neon::subtract_absolute_long(this->vec_, b);
  }

  template <typename U>
    requires argon::impl::has_larger_v<scalar_type>
  ace Argon<U> PairwiseAddLong() const {
    return neon::pairwise_add_long(this->vec_);
  }

  template <typename U>
    requires argon::impl::has_smaller_v<scalar_type>
  ace Argon<U> PairwiseAddLong(ArgonHalf<typename argon::impl::NextSmaller<scalar_type>> b) const {
    return neon::pairwise_add_long(this->vec_, b);
  }

  template <typename U>
    requires argon::impl::has_larger_v<scalar_type>
  ace Argon<U> Widen() const {
    return neon::move_long(this->vec_);
  }

  template <size_t n>
  ace Argon<argon::impl::NextLarger_t<scalar_type>> ShiftLeftLong()
    requires argon::impl::has_larger_v<scalar_type>
  {
    return neon::shift_left_long<n>(this->vec_);
  }

  ace Argon<argon::impl::NextLarger_t<scalar_type>> MultiplyDoubleSaturateLong(ArgonHalf<scalar_type> b)
    requires argon::impl::has_larger_v<scalar_type>
  {
    return neon::multiply_double_saturate_long(this->vec_, b);
  }

  ace ArgonHalf<scalar_type> TableLookup(ArgonHalf<scalar_type> idx) { return neon::table_lookup1(this->vec_, idx); }
  ace ArgonHalf<scalar_type> TableExtension(ArgonHalf<scalar_type> b, ArgonHalf<scalar_type> idx) {
    return neon::table_extension1(this->vec_, b, idx);
  }

  template <size_t num_tables>
  ace ArgonHalf<scalar_type> TableExtension(std::array<ArgonHalf<scalar_type>, num_tables> b,
                                            ArgonHalf<scalar_type> idx) {
    return TableExtension<num_tables>((vector_type*)b.data(), idx);
  }

  template <size_t num_tables>
  ace ArgonHalf<scalar_type> TableExtension(vector_type* b, ArgonHalf<scalar_type> idx) {
    static_assert(num_tables > 1 && num_tables < 5, "Table Extension can only be performed with 1, 2, 3, or 4 tables");

    using multivec_type = argon::impl::MultiVec<vector_type, num_tables>::type;

    multivec_type multivec = *(multivec_type*)b;

    if constexpr (num_tables == 2) {
      return neon::table_extension2(this->vec_, multivec, idx);
    } else if constexpr (num_tables == 3) {
      return neon::table_extension3(this->vec_, multivec, idx);
    } else if constexpr (num_tables == 4) {
      return neon::table_extension4(this->vec_, multivec, idx);
    }
  }

  template <typename U>
  ace ArgonHalf<U> ConvertTo() {
    return neon::convert<typename neon::Vec64<U>::type>(this->vec_);
  }
  template <typename U, int fracbits>
    requires(std::is_same_v<U, uint32_t> || std::is_same_v<U, int32_t> || std::is_same_v<U, float>)
  ace ArgonHalf<U> ConvertTo() {
    if constexpr (std::is_same_v<U, float>) {
      return neon::convert_n<fracbits>(this->vec_);
    } else if constexpr (std::is_unsigned_v<U>) {
      return neon::convert_n_unsigned<fracbits>(this->vec_);
    } else if constexpr (std::is_signed_v<U>) {
      return neon::convert_n_signed<fracbits>(this->vec_);
    }
  }

  ace Argon<scalar_type> CombineWith(ArgonHalf<scalar_type> high) const { return neon::combine(this->vec_, high); }

  ace ArgonHalf<scalar_type> Reverse() const {
    return this->Reverse64bit();
  }
};

template <class... arg_types>
  requires(sizeof...(arg_types) > 1)
ArgonHalf(arg_types...) -> ArgonHalf<std::tuple_element_t<0, std::tuple<arg_types...>>>;

template <typename V>
  requires std::is_scalar_v<V>
ace ArgonHalf<V> operator+(const V a, const ArgonHalf<V> b) {
  return b.Add(a);
}

template <typename V>
  requires std::is_scalar_v<V>
ace ArgonHalf<V> operator-(const V a, const ArgonHalf<V> b) {
  return ArgonHalf<V>{a}.Subtract(b);
}

template <typename V>
  requires std::is_scalar_v<V>
ace ArgonHalf<V> operator*(const V a, const ArgonHalf<V> b) {
  return b.Multiply(a);
}

template <typename V>
  requires std::is_scalar_v<V>
ace ArgonHalf<V> operator/(const V a, const ArgonHalf<V> b) {
  return ArgonHalf<V>{a}.Divide(b);
}

namespace std {
template <typename T>
struct tuple_size<ArgonHalf<T>> {
  static constexpr size_t value = ArgonHalf<T>::lanes;
};
template <size_t Index, typename T>
struct tuple_element<Index, ArgonHalf<T>> {
  static_assert(Index < ArgonHalf<T>::lanes);
  using type = argon::impl::Lane<typename ArgonHalf<T>::vector_type>;
};
}  // namespace std

#undef ace


#pragma once
#include <array>
#include <cstddef>
#include <type_traits>




#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

#ifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif
namespace argon {
template <size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_interleaved(scalar_type* ptr, impl::MultiVec_t<intrinsic_type, stride> multi_vec) {
  static_assert(stride > 1 && stride < 5, "Interleaving Stores can only be performed with a stride of 2, 3, or 4");
  if constexpr (stride == 2) {
    simd::store2(ptr, multi_vec);
  } else if constexpr (stride == 3) {
    simd::store3(ptr, multi_vec);
  } else if constexpr (stride == 4) {
    simd::store4(ptr, multi_vec);
  }
}

template <size_t stride, typename scalar_type, typename argon_type>
ace void store_interleaved(scalar_type* ptr, std::array<argon_type, stride> multi_vec) {
  using intrinsic_type = typename argon_type::vector_type;
  using multivec_type = impl::MultiVec_t<intrinsic_type, stride>;
  using array_type = std::array<argon_type, stride>;

  static_assert(std::is_standard_layout_v<array_type>);
  static_assert(sizeof(multivec_type) == sizeof(array_type),
                "std::array isn't layout-compatible with this NEON multi-vector.");

  store_interleaved<stride, scalar_type, intrinsic_type>(ptr, *(multivec_type*)multi_vec.data());
}

template <size_t stride, typename scalar_type, typename... argon_types>
ace void store_interleaved(scalar_type* ptr, argon_types... vecs) {
  store_interleaved<sizeof...(argon_types)>(
      ptr, std::array<std::common_type_t<argon_types...>, sizeof...(vecs)>{std::forward<argon_types>(vecs)...});
}

template <typename scalar_type, typename argon_type>
  requires std::is_same_v<scalar_type, simd::NonVec_t<typename argon_type::vector_type>>
ace void store(scalar_type* ptr, argon_type vector) {
  simd::store1(ptr, vector);
}

template <typename scalar_type, simd::is_vector_type intrinsic_type>
  requires std::is_same_v<scalar_type, typename simd::NonVec<intrinsic_type>::type>
ace void store(scalar_type* ptr, intrinsic_type vector) {
  simd::store1(ptr, vector);
}

#if defined(__clang__) || (__GNUC__ > 13)
template <size_t stride = 1, typename scalar_type, typename... intrinsic_types>
  requires(std::is_same_v<scalar_type, simd::NonVec_t<intrinsic_types>> && ...)
ace void store(scalar_type* ptr, intrinsic_types... vectors) {
  using intrinsic_type = typename std::tuple_element<0, std::tuple<intrinsic_types...>>::type;

  constexpr size_t size = sizeof...(vectors);
  const std::array<intrinsic_type, sizeof...(vectors)> vec_array = {vectors...};

  static_assert(0 < stride && stride < 5, "Stores can only be performed with a stride of 1, 2, 3, or 4");
  static_assert(size >= stride, "You cannot store less vectors than your stride!");
  static_assert(size % stride == 0, "The number of vectors being stored must be a multiple of the stride!");

  if constexpr (stride == 1) {
    constexpr size_t tail_size = size % 4;
#pragma unroll
    for (auto v : vec_array | std::views::chunk(4)) {
      if (v.size() == 4) {  // 4-element chunks
        using multi_type = impl::MultiVec<intrinsic_type, 4>::type;
        simd::store1_x4(ptr, *(multi_type*)v.begin());
        ptr += (sizeof(intrinsic_type) / sizeof(*ptr)) * 4;  // increment output pointer
      } else {
        if constexpr (tail_size == 1) {  // 1-element tail
          simd::store1(ptr, v.begin());
        } else if constexpr (tail_size == 2) {
          using tail_multi_type = impl::MultiVec<intrinsic_type, 2>::type;
          simd::store1_x2(ptr, *(tail_multi_type*)v.begin());
        } else if constexpr (tail_size == 3) {
          using tail_multi_type = impl::MultiVec<intrinsic_type, 3>::type;
          simd::store1_x3(ptr, *(tail_multi_type*)v.begin());
        }
      }
    }
  } else {
#pragma unroll
    for (auto v : vec_array | std::views::chunk(stride)) {
      if constexpr (stride == 2) {
        store_interleaved<2>(ptr, v.begin());
      } else if constexpr (stride == 3) {
        store_interleaved<3>(ptr, v.begin());
      } else if constexpr (stride == 4) {
        store_interleaved<4>(ptr, v.begin());
      }
      ptr += sizeof(intrinsic_type) / sizeof(*ptr);  // increment output pointer
    }
  }
}

template <size_t stride = 1, typename scalar_type, typename... argon_types>
  requires(std::is_same_v<scalar_type, simd::NonVec_t<typename argon_types::vector_type>> && ...)
ace void store(scalar_type* ptr, argon_types... vectors) {
  store<stride>(ptr, std::forward<typename argon_types::vector_type>(vectors)...);
}
#endif

template <int lane, size_t stride, typename scalar_type, typename argon_type>
ace void store_lane_interleaved(scalar_type* ptr, std::array<argon_type, stride> multi_vec) {
  using intrinsic_type = typename argon_type::vector_type;
  using multivec_type = impl::MultiVec_t<intrinsic_type, stride>;
  using array_type = std::array<argon_type, 2>;

  static_assert(std::is_standard_layout_v<array_type>);
  static_assert(std::is_trivial_v<array_type>);
  static_assert(sizeof(multivec_type) == sizeof(array_type),
                "std::array isn't layout-compatible with this NEON multi-vector.");

  store_lane_interleaved<lane, stride, scalar_type, intrinsic_type>(ptr, *(multivec_type*)multi_vec.data());
}

template <int lane, size_t stride, typename scalar_type, typename intrinsic_type>
ace void store_lane_interleaved(scalar_type* ptr, impl::MultiVec_t<intrinsic_type, stride> multi_vec) {
  static_assert(stride > 1 && stride < 5, "Interleaving Stores can only be performed with a stride of 2, 3, or 4");
  if constexpr (stride == 2) {
    simd::store2_lane<lane>(ptr, multi_vec);
  } else if constexpr (stride == 3) {
    simd::store3_lane<lane>(ptr, multi_vec);
  } else if constexpr (stride == 4) {
    simd::store4_lane<lane>(ptr, multi_vec);
  }
}
}  // namespace argon
#undef ace
#undef simd
#pragma once
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <ranges>
#include <span>





#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

template <typename scalar_type>
struct ArgonPtr {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

  using difference_type = std::ptrdiff_t;
  using value_type = Argon<scalar_type>;
  using pointer = Argon<scalar_type>*;

  ArgonPtr(scalar_type* ptr) : ptr_{ptr}, vec_{Argon<scalar_type>::Load(ptr_)} {}
  ArgonPtr(const ArgonPtr&) = default;
  ArgonPtr& operator=(const ArgonPtr&) = default;
  ArgonPtr(ArgonPtr&&) = default;

  ~ArgonPtr() {
    if (dirty_) {
      vec_.StoreTo(ptr_);
    }
  }

  pointer operator->() {
    dirty_ = true;
    return &vec_;
  }

  value_type& operator*() {
    dirty_ = true;
    return vec_;
  }

  const value_type& operator*() const { return vec_; }
  const pointer operator->() const { return &vec_; }

  void store() { vec_.StoreTo(ptr_); }
  void reload() { vec_ = value_type::Load(ptr_); }

  friend bool operator==(const ArgonPtr& a, const ArgonPtr& b) { return a.ptr_ == b.ptr_; }
  friend bool operator==(const ArgonPtr& a, const scalar_type* ptr) { return a.ptr_ == ptr; }
  friend bool operator!=(const ArgonPtr& a, const ArgonPtr& b) { return a.ptr_ != b.ptr_; }
  friend bool operator!=(const ArgonPtr& a, const scalar_type* ptr) { return a.ptr_ != ptr; }

 private:
  scalar_type* ptr_;
  value_type vec_;
  bool dirty_ = false;
};

namespace argon {

template <typename scalar_type>
struct vectorize_ptr : std::ranges::view_interface<vectorize_ptr<scalar_type>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  struct Iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = ArgonPtr<scalar_type>;

    Iterator(scalar_type* ptr) : ptr{ptr} {}

    value_type operator*() const { return value_type{ptr}; }

    Iterator& operator++() {
      ptr += lanes;
      return *this;
    }

    void operator++(int) { ++*this; }
    friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }
    friend bool operator==(const Iterator& a, const scalar_type* ptr) { return a.ptr == ptr; }
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; }
    friend bool operator!=(const Iterator& a, const scalar_type* ptr) { return a.ptr != ptr; }

   private:
    scalar_type* ptr = nullptr;
  };
  static_assert(std::input_iterator<Iterator>);

  using iterator = Iterator;

  iterator begin() { return start_; }
  scalar_type* end() { return start_ + size_; }
  size_t size() const { return size_ / lanes; }

  template <std::ranges::contiguous_range R>
  vectorize_ptr(R&& r) : start_{std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

 private:
  scalar_type* start_;
  size_t size_;
};
template <std::ranges::contiguous_range R>
vectorize_ptr(R&& r) -> vectorize_ptr<std::ranges::range_value_t<R>>;

static_assert(std::ranges::range<vectorize_ptr<int32_t>>);
static_assert(std::ranges::view<vectorize_ptr<int32_t>>);
static_assert(std::movable<vectorize_ptr<int32_t>>);
static_assert(std::ranges::viewable_range<vectorize_ptr<int32_t>>);

template <typename scalar_type>
struct vectorize : public std::ranges::view_interface<vectorize<scalar_type>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = Argon<scalar_type>;
    using difference_type = std::ptrdiff_t;

    Iterator() = default;
    Iterator(scalar_type* ptr) : ptr{ptr}, vec{value_type::Load(ptr)} {}

    value_type& operator*() { return vec; }
    value_type* operator->() { return &vec; }
    const value_type& operator*() const { return vec; }
    const value_type* operator->() const { return &vec; }
    Iterator& operator++() {
      vec.StoreTo(ptr);  // store before increment
      ptr += lanes;
      vec = value_type::Load(ptr);
      return *this;
    }
    void operator++(int) { ++(*this); }
    friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }
    friend bool operator==(const Iterator& a, const scalar_type* ptr) { return a.ptr == ptr; }
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; }
    friend bool operator!=(const Iterator& a, const scalar_type* ptr) { return a.ptr != ptr; }

   private:
    scalar_type* ptr = nullptr;
    value_type vec;
  };
  static_assert(std::input_or_output_iterator<Iterator>);

  struct ConstIterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = Argon<scalar_type>;
    using difference_type = std::ptrdiff_t;

    ConstIterator() = default;
    ConstIterator(const scalar_type* ptr) : ptr{ptr}, vec{value_type::Load(ptr)} {}

    const value_type operator*() const { return vec; }
    ConstIterator& operator++() {
      ptr += lanes;
      vec = value_type::Load(ptr);
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return a.ptr == b.ptr; }
    friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.ptr != b.ptr; }

   private:
    const scalar_type* ptr = nullptr;
    value_type vec;
  };
  static_assert(std::input_iterator<ConstIterator>);

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  vectorize(scalar_type* start, scalar_type* end) : start_{start}, size_{vectorizeable_size(end - start)} {};
  vectorize(scalar_type* start, const size_t size) : start_{start}, size_{vectorizeable_size(size)} {};
  vectorize(std::span<scalar_type> span) : start_{span.data()}, size_{vectorizeable_size(span.size())} {};

  template <std::ranges::contiguous_range R>
  vectorize(R&& r) : start_{std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

  vectorize(vectorize&&) = default;
  vectorize(const vectorize&) = default;
  vectorize& operator=(vectorize&&) = default;
  vectorize& operator=(const vectorize&) = default;

  iterator begin() const { return Iterator(start_); }
  scalar_type* end() const { return start_ + size_; }
  const_iterator cbegin() const { return ConstIterator(start_); }
  const scalar_type* cend() const { return start_ + size_; }
  size_t size() const { return size_; }

 private:
  scalar_type* start_;
  size_t size_;
};

template <std::ranges::contiguous_range R>
vectorize(R&& r) -> vectorize<std::ranges::range_value_t<R>>;

static_assert(std::ranges::range<vectorize<int32_t>>);
static_assert(std::ranges::view<vectorize<int32_t>>);
static_assert(std::movable<vectorize<int32_t>>);
static_assert(std::ranges::viewable_range<vectorize<int32_t>>);

template <size_t stride, typename scalar_type>
struct vectorize_interleaved : public std::ranges::view_interface<vectorize<scalar_type>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using argon_type = Argon<scalar_type>;
    using value_type = std::array<argon_type, stride>;
    using difference_type = std::ptrdiff_t;

    Iterator() = default;
    Iterator(scalar_type* ptr) : ptr{ptr}, vec{argon_type::template LoadInterleaved<stride>(ptr)} {}

    value_type& operator*() { return vec; }
    value_type* operator->() { return &vec; }
    const value_type& operator*() const { return vec; }
    const value_type* operator->() const { return &vec; }
    Iterator& operator++() {
      argon::store_interleaved(ptr, vec);  // store before increment
      ptr += lanes;
      vec = argon_type::template LoadInterleaved<stride>(ptr);
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }
    friend bool operator==(const Iterator& a, const scalar_type* ptr) { return a.ptr == ptr; }
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; }
    friend bool operator!=(const Iterator& a, const scalar_type* ptr) { return a.ptr != ptr; }

   private:
    scalar_type* ptr = nullptr;
    value_type vec;
  };
  static_assert(std::input_or_output_iterator<Iterator>);
  struct ConstIterator {
    using iterator_category = std::forward_iterator_tag;
    using argon_type = Argon<scalar_type>;
    using value_type = std::array<argon_type, stride>;
    using difference_type = std::ptrdiff_t;

    ConstIterator() = default;
    ConstIterator(const scalar_type* ptr) : ptr{ptr}, vec{argon_type::template LoadInterleaved<stride>(ptr)} {}

    const value_type operator*() const { return vec; }
    ConstIterator& operator++() {
      ptr += lanes;
      vec = argon_type::template LoadInterleaved<stride>(ptr);
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return a.ptr == b.ptr; }
    friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.ptr != b.ptr; }

   private:
    const scalar_type* ptr = nullptr;
    value_type vec;
  };
  static_assert(std::input_iterator<ConstIterator>);

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  vectorize_interleaved(scalar_type* start, scalar_type* end) : start_{start}, size_{vectorizeable_size(end - start)} {};
  vectorize_interleaved(scalar_type* start, const size_t size) : start_{start}, size_{vectorizeable_size(size)} {};
  vectorize_interleaved(const std::span<scalar_type> span)
      : start_{span.data()}, size_{vectorizeable_size(span.size())} {};

  template <size_t, std::ranges::contiguous_range R>
  vectorize_interleaved(R&& r) : start_{std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

  iterator begin() const { return Iterator(start_); }
  const scalar_type* end() const { return start_ + size_; }
  const_iterator cbegin() const { return ConstIterator(start_); }
  const scalar_type* cend() const { return start_ + size_; }
  size_t size() const { return size_; }

 private:
  scalar_type* start_;
  size_t size_;
};

template <size_t stride, std::ranges::contiguous_range R>
vectorize_interleaved(R&& r) -> vectorize_interleaved<stride, std::ranges::range_value_t<R>>;

static_assert(std::ranges::range<vectorize_interleaved<3, int32_t>>);
static_assert(std::ranges::view<vectorize_interleaved<3, int32_t>>);
static_assert(std::movable<vectorize_interleaved<3, int32_t>>);
static_assert(std::ranges::viewable_range<vectorize_interleaved<3, int32_t>>);

namespace split {

template <typename scalar_type>
std::pair<std::span<scalar_type>, std::span<scalar_type>> head_aligned(std::span<scalar_type> span) {
  constexpr size_t lanes = sizeof(simd::Vec128_t<scalar_type>) / sizeof(scalar_type);
  return {span.first(span.size() & ~(lanes - 1)), span.last(span.size() & (lanes - 1))};
}

template <typename scalar_type>
std::pair<std::span<scalar_type>, std::span<scalar_type>> tail_aligned(std::span<scalar_type> span) {
  constexpr size_t lanes = sizeof(simd::Vec128_t<scalar_type>) / sizeof(scalar_type);
  return {span.first(span.size() & (lanes - 1)), span.last(span.size() & ~(lanes - 1))};
}

}  // namespace split
}  // namespace argon
#undef simd


#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

#ifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif

namespace argon {

template <typename T, typename V>
ace auto reinterpret(impl::Common<V> in) {
  if constexpr (simd::is_quadword_v<V>) {
    return Argon<T>{simd::reinterpret<typename Argon<T>::vector_type>(in.vec())};
  } else if constexpr (simd::is_doubleword_v<V>) {
    return ArgonHalf<T>{simd::reinterpret<typename ArgonHalf<T>::vector_type>(in.vec())};
  }
}

template <typename argon_type, simd::is_vector_type V>
ace argon_type reinterpret(V in) {
  static_assert(!std::is_same_v<typename argon_type::vector_type, V>);
  return argon_type{simd::reinterpret<typename argon_type::vector_type>(in)};
}

template <size_t lane, size_t stride, typename argon_type>
ace static std::array<argon_type, stride> load_interleaved_to_lane(
    impl::MultiVec_t<typename argon_type::vector_type, stride> multi,
    typename argon_type::scalar_type const* ptr) {
  return argon_type::load_interleaved_to_lane(multi, ptr);
}

template <size_t lane, size_t stride, typename argon_type>
ace static std::array<argon_type, stride> load_interleaved_to_lane(std::array<argon_type, stride> multi,
                                                                   typename argon_type::scalar_type const* ptr) {
  return argon_type::load_interleaved_to_lane(multi, ptr);
}

template <typename argon_type>
ace std::array<argon_type, 2> zip(argon_type a, argon_type b) {
  return argon::to_array(simd::zip(a, b).val);
}

template <typename argon_type>
ace std::array<argon_type, 2> unzip(argon_type a, argon_type b) {
  return argon::to_array(simd::unzip(a, b).val);
}

template <typename argon_type>
ace std::array<argon_type, 2> transpose(argon_type a, argon_type b) {
  return argon::to_array(simd::transpose(a, b).val);
}

template <typename T>
ace Argon<T> combine(ArgonHalf<T> low, ArgonHalf<T> high) {
  return simd::combine(low, high);
}

template <typename T>
ace Argon<T> load(const T* ptr) {
  return Argon<T>::Load(ptr);
}

template <typename T>
ace Argon<T> load_half(const T* ptr) {
  return ArgonHalf<T>::Load(ptr);
}

template <typename CondType, typename ArgonType>
  requires std::is_same_v<CondType, typename ArgonType::argon_result_type>
ace ArgonType ternary(CondType condition, ArgonType true_value, ArgonType false_value) {
  return ((condition & true_value.template As<typename CondType::scalar_type>()) |
          (~condition & false_value.template As<typename CondType::scalar_type>()))
      .template As<typename ArgonType::scalar_type>();
}

}  // namespace argon

#undef ace
#undef simd
