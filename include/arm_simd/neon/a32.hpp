#pragma once
#include "vfpv4.hpp"
#include "arm_simd/shared/a32_float.hpp"

#ifdef __ARM_ACLE
#include <arm_acle.h>
#endif

#ifdef __cplusplus
#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

namespace neon {
// clang-format off
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float32x2_t a);
template <typename T> nce T convert_round_toward_negative_infinity(float32x2_t a);
template <typename T> nce T convert_round_toward_positive_infinity(float32x2_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float32x2_t a);
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
template <typename T> nce T reinterpret(poly64x1_t a);
template <typename T> nce T reinterpret(float32x4_t a);
template <typename T> nce T reinterpret(poly8x16_t a);
template <typename T> nce T reinterpret(poly16x8_t a);
template <typename T> nce T reinterpret(uint64x2_t a);
template <typename T> nce T reinterpret(poly64x2_t a);
template <typename T> nce T reinterpret(float16x8_t a);
template <typename T> nce T reinterpret(poly128_t a);
template <typename T> nce T create(uint64_t a);
template <typename T> nce T duplicate(poly64_t value);
template <typename T> nce T duplicate(poly64x1_t vec);
template <typename T> nce T get(poly64x2_t a);
template <typename T> nce T load1(poly64_t const *ptr);
template <typename T> nce T load1_duplicate(poly64_t const *ptr);
template <typename T> nce T load1_x2(poly64_t const *ptr);
template <typename T> nce T load1_x3(poly64_t const *ptr);
template <typename T> nce T load1_x4(poly64_t const *ptr);
template <typename T> nce T store1(poly64_t *ptr, poly64x1_t val);
template <typename T> nce T store1(poly64_t *ptr, poly64x2_t val);
template <typename T> nce T convert(int32_t a);
template <typename T> nce T convert(uint32_t a);
template <typename T> nce T convert(float16_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float16_t a);
template <typename T> nce T convert_round_toward_negative_infinity(float16_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float16_t a);
template <typename T> nce T convert_round_toward_positive_infinity(float16_t a);
template <typename T> nce T max(float16x4_t a, float16x4_t b);
template <typename T> nce T max(float16x8_t a, float16x8_t b);
template <typename T> nce T min(float16x4_t a, float16x4_t b);
template <typename T> nce T min(float16x8_t a, float16x8_t b);
template <typename T> nce T max_strict(float16x4_t a, float16x4_t b);
template <typename T> nce T max_strict(float16x8_t a, float16x8_t b);
template <typename T> nce T min_strict(float16x4_t a, float16x4_t b);
template <typename T> nce T min_strict(float16x8_t a, float16x8_t b);
template <typename T> nce T convert(int16x4_t a);
template <typename T> nce T convert(uint16x4_t a);
template <typename T> nce T convert(float16x4_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float16x4_t a);
template <typename T> nce T convert_round_toward_negative_infinity(float16x4_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float16x4_t a);
template <typename T> nce T convert_round_toward_positive_infinity(float16x4_t a);
template <typename T> nce T dot_product(uint32x2_t r, uint8x8_t a, uint8x8_t b);
template <typename T> nce T dot_product(int32x2_t r, int8x8_t a, int8x8_t b);
template <typename T> nce T dot_product(uint32x4_t r, uint8x16_t a, uint8x16_t b);
template <typename T> nce T dot_product(int32x4_t r, int8x16_t a, int8x16_t b);
template <typename T> nce T multiply_add_long_fused_high(float32x2_t r, float16x4_t a, float16x4_t b);
template <typename T> nce T multiply_add_long_fused_high(float32x4_t r, float16x8_t a, float16x8_t b) ;
template <typename T> nce T multiply_add_long_fused_low(float32x2_t r, float16x4_t a, float16x4_t b);
template <typename T> nce T multiply_add_long_fused_low(float32x4_t r, float16x8_t a, float16x8_t b) ;
template <typename T> nce T multiply_add_long_fused(float32x2_t r, float16x4_t a, float16x4_t b);
template <typename T> nce T multiply_add_long_fused(float32x2_t r, float16x4_t a, float16x8_t b);
template <typename T> nce T multiply_add_long_fused(float32x4_t r, float16x8_t a, float16x4_t b);
template <typename T> nce T multiply_add_long_fused(float32x4_t r, float16x8_t a, float16x8_t b);
template <typename T> nce T multiply_subtract_long_fused_high(float32x2_t r, float16x4_t a, float16x4_t b);
template <typename T> nce T multiply_subtract_long_fused_high(float32x4_t r, float16x8_t a, float16x8_t b) ;
template <typename T> nce T multiply_subtract_long_fused_low(float32x2_t r, float16x4_t a, float16x4_t b);
template <typename T> nce T multiply_subtract_long_fused_low(float32x4_t r, float16x8_t a, float16x8_t b) ;
template <typename T> nce T multiply_subtract_long_fused(float32x2_t r, float16x4_t a, float16x4_t b);
template <typename T> nce T multiply_subtract_long_fused(float32x2_t r, float16x4_t a, float16x8_t b);
template <typename T> nce T multiply_subtract_long_fused(float32x4_t r, float16x8_t a, float16x4_t b);
template <typename T> nce T multiply_subtract_long_fused(float32x4_t r, float16x8_t a, float16x8_t b);
template <typename T> nce T complex_multiply_add(float16x4_t r, float16x4_t a, float16x4_t b);
template <typename T> nce T complex_multiply_add(float32x2_t r, float32x2_t a, float32x2_t b);
template <typename T> nce T complex_multiply_add(float16x8_t r, float16x8_t a, float16x8_t b);
template <typename T> nce T complex_multiply_add(float32x4_t r, float32x4_t a, float32x4_t b);
template <typename T> nce T complex_multiply_add_rotate_90(float16x4_t r, float16x4_t a, float16x4_t b);
template <typename T> nce T complex_multiply_add_rotate_90(float32x2_t r, float32x2_t a, float32x2_t b);
template <typename T> nce T complex_multiply_add_rotate_90(float16x8_t r, float16x8_t a, float16x8_t b);
template <typename T> nce T complex_multiply_add_rotate_90(float32x4_t r, float32x4_t a, float32x4_t b);
template <typename T> nce T complex_multiply_add_rotate_180(float16x4_t r, float16x4_t a, float16x4_t b);
template <typename T> nce T complex_multiply_add_rotate_180(float32x2_t r, float32x2_t a, float32x2_t b);
template <typename T> nce T complex_multiply_add_rotate_180(float16x8_t r, float16x8_t a, float16x8_t b);
template <typename T> nce T complex_multiply_add_rotate_180(float32x4_t r, float32x4_t a, float32x4_t b);
template <typename T> nce T complex_multiply_add_rotate_270(float16x4_t r, float16x4_t a, float16x4_t b);
template <typename T> nce T complex_multiply_add_rotate_270(float32x2_t r, float32x2_t a, float32x2_t b);
template <typename T> nce T complex_multiply_add_rotate_270(float16x8_t r, float16x8_t a, float16x8_t b);
template <typename T> nce T complex_multiply_add_rotate_270(float32x4_t r, float32x4_t a, float32x4_t b);
template <typename T> nce T dot_product(int32x2_t r, uint8x8_t a, int8x8_t b);
template <typename T> nce T dot_product(int32x4_t r, uint8x16_t a, int8x16_t b);
template <typename T> nce T duplicate(bfloat16_t value);
template <typename T> nce T duplicate(bfloat16x4_t vec);
template <typename T> nce T duplicate(bfloat16x8_t vec);
template <typename T> nce T get(bfloat16x8_t a);
template <typename T> nce T load1(bfloat16_t const *ptr);
template <typename T> nce T load1_duplicate(bfloat16_t const *ptr);
template <typename T> nce T load2(bfloat16_t const *ptr);
template <typename T> nce T load3(bfloat16_t const *ptr);
template <typename T> nce T load4(bfloat16_t const *ptr);
template <typename T> nce T load2_duplicate(bfloat16_t const *ptr);
template <typename T> nce T load3_duplicate(bfloat16_t const *ptr);
template <typename T> nce T load4_duplicate(bfloat16_t const *ptr);
template <typename T> nce T load2(poly64_t const *ptr);
template <typename T> nce T load3(poly64_t const *ptr);
template <typename T> nce T load4(poly64_t const *ptr);
template <typename T> nce T load2_duplicate(poly64_t const *ptr);
template <typename T> nce T load3_duplicate(poly64_t const *ptr);
template <typename T> nce T load4_duplicate(poly64_t const *ptr);
template <typename T> nce T load1_x2(bfloat16_t const *ptr);
template <typename T> nce T load1_x3(bfloat16_t const *ptr);
template <typename T> nce T load1_x4(bfloat16_t const *ptr);
template <typename T> nce T store1(bfloat16_t *ptr, bfloat16x4_t val);
template <typename T> nce T store1(bfloat16_t *ptr, bfloat16x8_t val);
template <typename T> nce T store2(bfloat16_t *ptr, bfloat16x4x2_t val);
template <typename T> nce T store2(bfloat16_t *ptr, bfloat16x8x2_t val);
template <typename T> nce T store3(bfloat16_t *ptr, bfloat16x4x3_t val);
template <typename T> nce T store3(bfloat16_t *ptr, bfloat16x8x3_t val);
template <typename T> nce T store4(bfloat16_t *ptr, bfloat16x4x4_t val);
template <typename T> nce T store4(bfloat16_t *ptr, bfloat16x8x4_t val);
template <typename T> nce T reinterpret(bfloat16x4_t a);
template <typename T> nce T reinterpret(bfloat16x8_t a);
template <typename T> nce T convert(bfloat16x8_t a);
template <typename T> nce T convert(float32x4_t a);
template <typename T> nce T dot_product(float32x2_t r, bfloat16x4_t a, bfloat16x4_t b);
template <typename T> nce T dot_product(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b);
template <typename T> nce T multiply_add_long_widen_bottom(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b);
template <typename T> nce T multiply_add_long_widen_top(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b);
template <typename T> nce T convert_low(bfloat16x8_t a);
template <typename T> nce T convert_high(bfloat16x8_t a);
template <typename T> nce T convert_low(float32x4_t a);
template <typename T> nce T get_high(poly64x2_t a);
template <typename T> nce T get_low(poly64x2_t a);
template <typename T> nce T get_high(bfloat16x8_t a);
template <typename T> nce T get_low(bfloat16x8_t a);

template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(uint8x8_t a) { return vreinterpret_p64_u8(a); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(uint8x8_t a) { return vreinterpret_bf16_u8(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(uint8x16_t a) { return vreinterpretq_p64_u8(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(uint8x16_t a) { return vreinterpretq_p128_u8(a); }
[[gnu::always_inline]] nce uint8x16_t aes_encrypt(uint8x16_t data, uint8x16_t key) { return vaeseq_u8(data, key); }
[[gnu::always_inline]] nce uint8x16_t aes_decrypt(uint8x16_t data, uint8x16_t key) { return vaesdq_u8(data, key); }
[[gnu::always_inline]] nce uint8x16_t aes_mix_columns(uint8x16_t data) { return vaesmcq_u8(data); }
[[gnu::always_inline]] nce uint8x16_t aes_inverse_mix_columns(uint8x16_t data) { return vaesimcq_u8(data); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_bf16_u8(a); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(int8x8_t a) { return vreinterpret_p64_s8(a); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(int8x8_t a) { return vreinterpret_bf16_s8(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(int8x16_t a) { return vreinterpretq_p64_s8(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(int8x16_t a) { return vreinterpretq_p128_s8(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(int8x16_t a) { return vreinterpretq_bf16_s8(a); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(uint16x4_t a) { return vreinterpret_p64_u16(a); }
template <> [[gnu::always_inline]] nce float16x4_t convert(uint16x4_t a) { return vcvt_f16_u16(a); }
template <int n>[[gnu::always_inline]] nce float16x4_t convert(uint16x4_t a) { return vcvt_n_f16_u16(a, n); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(uint16x4_t a) { return vreinterpret_bf16_u16(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(uint16x8_t a) { return vreinterpretq_p64_u16(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(uint16x8_t a) { return vreinterpretq_p128_u16(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(uint16x8_t a) { return vreinterpretq_bf16_u16(a); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(int16x4_t a) { return vreinterpret_p64_s16(a); }
template <> [[gnu::always_inline]] nce float16x4_t convert(int16x4_t a) { return vcvt_f16_s16(a); }
template <int n>[[gnu::always_inline]] nce float16x4_t convert(int16x4_t a) { return vcvt_n_f16_s16(a, n); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(int16x4_t a) { return vreinterpret_bf16_s16(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(int16x8_t a) { return vreinterpretq_p64_s16(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(int16x8_t a) { return vreinterpretq_p128_s16(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(int16x8_t a) { return vreinterpretq_bf16_s16(a); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(int32x2_t a) { return vreinterpret_p64_s32(a); }
template <> [[gnu::always_inline]] nce int32x2_t dot_product(int32x2_t r, uint8x8_t a, int8x8_t b) { return vusdot_s32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce int32x2_t dot_product_lane(int32x2_t r, uint8x8_t a, int8x8_t b) { return vusdot_lane_s32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t dot_product_lane(int32x2_t r, uint8x8_t a, int8x16_t b) { return vusdot_laneq_s32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t dot_product_lane(int32x2_t r, int8x8_t a, uint8x8_t b) { return vsudot_lane_s32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t dot_product_lane(int32x2_t r, int8x8_t a, uint8x16_t b) { return vsudot_laneq_s32(r, a, b, lane); }
template <> [[gnu::always_inline]] nce int32x2_t dot_product(int32x2_t r, int8x8_t a, int8x8_t b) { return vdot_s32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce int32x2_t dot_product_lane(int32x2_t r, int8x8_t a, int8x8_t b) { return vdot_lane_s32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t dot_product_lane(int32x2_t r, int8x8_t a, int8x16_t b) { return vdot_laneq_s32(r, a, b, lane); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(int32x2_t a) { return vreinterpret_bf16_s32(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(int32x4_t a) { return vreinterpretq_p64_s32(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(int32x4_t a) { return vreinterpretq_p128_s32(a); }
template <int lane>[[gnu::always_inline]] nce int32x4_t dot_product_lane(int32x4_t r, uint8x16_t a, int8x8_t b) { return vusdotq_lane_s32(r, a, b, lane); }
[[gnu::always_inline]] nce int32x4_t matrix_multiply_add(int32x4_t r, uint8x16_t a, int8x16_t b) { return vusmmlaq_s32(r, a, b); }
template <> [[gnu::always_inline]] nce int32x4_t dot_product(int32x4_t r, uint8x16_t a, int8x16_t b) { return vusdotq_s32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce int32x4_t dot_product_lane(int32x4_t r, uint8x16_t a, int8x16_t b) { return vusdotq_laneq_s32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t dot_product_lane(int32x4_t r, int8x16_t a, uint8x8_t b) { return vsudotq_lane_s32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t dot_product_lane(int32x4_t r, int8x16_t a, uint8x16_t b) { return vsudotq_laneq_s32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t dot_product_lane(int32x4_t r, int8x16_t a, int8x8_t b) { return vdotq_lane_s32(r, a, b, lane); }
template <> [[gnu::always_inline]] nce int32x4_t dot_product(int32x4_t r, int8x16_t a, int8x16_t b) { return vdotq_s32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce int32x4_t dot_product_lane(int32x4_t r, int8x16_t a, int8x16_t b) { return vdotq_laneq_s32(r, a, b, lane); }
[[gnu::always_inline]] nce int32x4_t matrix_multiply_add(int32x4_t r, int8x16_t a, int8x16_t b) { return vmmlaq_s32(r, a, b); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(int32x4_t a) { return vreinterpretq_bf16_s32(a); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(uint64x1_t a) { return vreinterpret_p64_u64(a); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(uint64x1_t a) { return vreinterpret_bf16_u64(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(uint64x2_t a) { return vreinterpretq_p64_u64(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(uint64x2_t a) { return vreinterpretq_p128_u64(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_bf16_u64(a); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(uint32x2_t a) { return vreinterpret_p64_u32(a); }
template <> [[gnu::always_inline]] nce uint32x2_t dot_product(uint32x2_t r, uint8x8_t a, uint8x8_t b) { return vdot_u32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t dot_product_lane(uint32x2_t r, uint8x8_t a, uint8x8_t b) { return vdot_lane_u32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t dot_product_lane(uint32x2_t r, uint8x8_t a, uint8x16_t b) { return vdot_laneq_u32(r, a, b, lane); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(uint32x2_t a) { return vreinterpret_bf16_u32(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(uint32x4_t a) { return vreinterpretq_p64_u32(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(uint32x4_t a) { return vreinterpretq_p128_u32(a); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t dot_product_lane(uint32x4_t r, uint8x16_t a, uint8x8_t b) { return vdotq_lane_u32(r, a, b, lane); }
template <> [[gnu::always_inline]] nce uint32x4_t dot_product(uint32x4_t r, uint8x16_t a, uint8x16_t b) { return vdotq_u32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t dot_product_lane(uint32x4_t r, uint8x16_t a, uint8x16_t b) { return vdotq_laneq_u32(r, a, b, lane); }
[[gnu::always_inline]] nce uint32x4_t matrix_multiply_add(uint32x4_t r, uint8x16_t a, uint8x16_t b) { return vmmlaq_u32(r, a, b); }
[[gnu::always_inline]] nce uint32x4_t sha1_schedule_update_0(uint32x4_t w0_3, uint32x4_t w4_7, uint32x4_t w8_11) { return vsha1su0q_u32(w0_3, w4_7, w8_11); }
[[gnu::always_inline]] nce uint32x4_t sha1_schedule_update_1(uint32x4_t tw0_3, uint32x4_t w12_15) { return vsha1su1q_u32(tw0_3, w12_15); }
[[gnu::always_inline]] nce uint32x4_t sha256_hash_part_1(uint32x4_t hash_abcd, uint32x4_t hash_efgh, uint32x4_t wk) { return vsha256hq_u32(hash_abcd, hash_efgh, wk); }
[[gnu::always_inline]] nce uint32x4_t sha256_hash_part_2(uint32x4_t hash_efgh, uint32x4_t hash_abcd, uint32x4_t wk) { return vsha256h2q_u32(hash_efgh, hash_abcd, wk); }
[[gnu::always_inline]] nce uint32x4_t sha256_schedule_update_0(uint32x4_t w0_3, uint32x4_t w4_7) { return vsha256su0q_u32(w0_3, w4_7); }
[[gnu::always_inline]] nce uint32x4_t sha256_schedule_update_1(uint32x4_t tw0_3, uint32x4_t w8_11, uint32x4_t w12_15) { return vsha256su1q_u32(tw0_3, w8_11, w12_15); }
[[gnu::always_inline]] nce uint32x4_t sha1_choose(uint32x4_t hash_abcd, uint32_t hash_e, uint32x4_t wk) { return vsha1cq_u32(hash_abcd, hash_e, wk); }
[[gnu::always_inline]] nce uint32x4_t sha1_parity(uint32x4_t hash_abcd, uint32_t hash_e, uint32x4_t wk) { return vsha1pq_u32(hash_abcd, hash_e, wk); }
[[gnu::always_inline]] nce uint32x4_t sha1_majority(uint32x4_t hash_abcd, uint32_t hash_e, uint32x4_t wk) { return vsha1mq_u32(hash_abcd, hash_e, wk); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_bf16_u32(a); }
[[gnu::always_inline]] nce poly64x1_t reinterpret(float16x4_t a) { return vreinterpret_p64_f16(a); }
[[gnu::always_inline]] nce float16x4_t absolute(float16x4_t a) { return vabs_f16(a); }
[[gnu::always_inline]] nce float16x4_t subtract_absolute(float16x4_t a, float16x4_t b) { return vabd_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t reciprocal_estimate(float16x4_t a) { return vrecpe_f16(a); }
[[gnu::always_inline]] nce float16x4_t reciprocal_sqrt_estimate(float16x4_t a) { return vrsqrte_f16(a); }
[[gnu::always_inline]] nce float16x4_t reciprocal_sqrt_step(float16x4_t a, float16x4_t b) { return vrsqrts_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t reciprocal_step(float16x4_t a, float16x4_t b) { return vrecps_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t round(float16x4_t a) { return vrnd_f16(a); }
[[gnu::always_inline]] nce float16x4_t round_to_nearest_with_ties_away_from_zero(float16x4_t a) { return vrnda_f16(a); }
[[gnu::always_inline]] nce float16x4_t round_toward_negative_infinity(float16x4_t a) { return vrndm_f16(a); }
[[gnu::always_inline]] nce float16x4_t round_to_nearest_with_ties_to_even(float16x4_t a) { return vrndn_f16(a); }
[[gnu::always_inline]] nce float16x4_t round_toward_positive_infinity(float16x4_t a) { return vrndp_f16(a); }
[[gnu::always_inline]] nce float16x4_t round_inexact(float16x4_t a) { return vrndx_f16(a); }
[[gnu::always_inline]] nce float16x4_t add(float16x4_t a, float16x4_t b) { return vadd_f16(a, b); }
template <> [[gnu::always_inline]] nce float16x4_t max(float16x4_t a, float16x4_t b) { return vmax_f16(a, b); }
template <> [[gnu::always_inline]] nce float16x4_t max_strict(float16x4_t a, float16x4_t b) { return vmaxnm_f16(a, b); }
template <> [[gnu::always_inline]] nce float16x4_t min(float16x4_t a, float16x4_t b) { return vmin_f16(a, b); }
template <> [[gnu::always_inline]] nce float16x4_t min_strict(float16x4_t a, float16x4_t b) { return vminnm_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t multiply(float16x4_t a, float16x4_t b) { return vmul_f16(a, b); }
template <int lane>[[gnu::always_inline]] nce float16x4_t multiply_lane(float16x4_t a, float16x4_t v) { return vmul_lane_f16(a, v, lane); }
[[gnu::always_inline]] nce float16x4_t multiply_add_fused(float16x4_t a, float16x4_t b, float16x4_t c) { return vfma_f16(a, b, c); }
[[gnu::always_inline]] nce float16x4_t multiply_subtract_fused(float16x4_t a, float16x4_t b, float16x4_t c) { return vfms_f16(a, b, c); }
[[gnu::always_inline]] nce float16x4_t pairwise_add(float16x4_t a, float16x4_t b) { return vpadd_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t pairwise_max(float16x4_t a, float16x4_t b) { return vpmax_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t pairwise_min(float16x4_t a, float16x4_t b) { return vpmin_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t subtract(float16x4_t a, float16x4_t b) { return vsub_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t multiply(float16x4_t a, float16_t n) { return vmul_n_f16(a, n); }
[[gnu::always_inline]] nce uint16x4_t equal_to_zero(float16x4_t a) { return vceqz_f16(a); }
[[gnu::always_inline]] nce uint16x4_t greater_than_or_equal_to_zero(float16x4_t a) { return vcgez_f16(a); }
[[gnu::always_inline]] nce uint16x4_t greater_than_zero(float16x4_t a) { return vcgtz_f16(a); }
[[gnu::always_inline]] nce uint16x4_t less_than_or_equal_to_zero(float16x4_t a) { return vclez_f16(a); }
[[gnu::always_inline]] nce uint16x4_t less_than_zero(float16x4_t a) { return vcltz_f16(a); }
[[gnu::always_inline]] nce uint16x4_t absolute_greater_than_or_equal(float16x4_t a, float16x4_t b) { return vcage_f16(a, b); }
[[gnu::always_inline]] nce uint16x4_t absolute_greater_than(float16x4_t a, float16x4_t b) { return vcagt_f16(a, b); }
[[gnu::always_inline]] nce uint16x4_t absolute_less_than_or_equal(float16x4_t a, float16x4_t b) { return vcale_f16(a, b); }
[[gnu::always_inline]] nce uint16x4_t absolute_less_than(float16x4_t a, float16x4_t b) { return vcalt_f16(a, b); }
[[gnu::always_inline]] nce uint16x4_t equal(float16x4_t a, float16x4_t b) { return vceq_f16(a, b); }
[[gnu::always_inline]] nce uint16x4_t greater_than_or_equal(float16x4_t a, float16x4_t b) { return vcge_f16(a, b); }
[[gnu::always_inline]] nce uint16x4_t greater_than(float16x4_t a, float16x4_t b) { return vcgt_f16(a, b); }
[[gnu::always_inline]] nce uint16x4_t less_than_or_equal(float16x4_t a, float16x4_t b) { return vcle_f16(a, b); }
[[gnu::always_inline]] nce uint16x4_t less_than(float16x4_t a, float16x4_t b) { return vclt_f16(a, b); }
template <> [[gnu::always_inline]] nce int16x4_t convert(float16x4_t a) { return vcvt_s16_f16(a); }
template <> [[gnu::always_inline]] nce uint16x4_t convert(float16x4_t a) { return vcvt_u16_f16(a); }
template <> [[gnu::always_inline]] nce int16x4_t convert_round_to_nearest_with_ties_away_from_zero(float16x4_t a) { return vcvta_s16_f16(a); }
template <> [[gnu::always_inline]] nce uint16x4_t convert_round_to_nearest_with_ties_away_from_zero(float16x4_t a) { return vcvta_u16_f16(a); }
template <> [[gnu::always_inline]] nce int16x4_t convert_round_toward_negative_infinity(float16x4_t a) { return vcvtm_s16_f16(a); }
template <> [[gnu::always_inline]] nce uint16x4_t convert_round_toward_negative_infinity(float16x4_t a) { return vcvtm_u16_f16(a); }
template <> [[gnu::always_inline]] nce int16x4_t convert_round_to_nearest_with_ties_to_even(float16x4_t a) { return vcvtn_s16_f16(a); }
template <> [[gnu::always_inline]] nce uint16x4_t convert_round_to_nearest_with_ties_to_even(float16x4_t a) { return vcvtn_u16_f16(a); }
template <> [[gnu::always_inline]] nce int16x4_t convert_round_toward_positive_infinity(float16x4_t a) { return vcvtp_s16_f16(a); }
template <> [[gnu::always_inline]] nce uint16x4_t convert_round_toward_positive_infinity(float16x4_t a) { return vcvtp_u16_f16(a); }
template <int n>[[gnu::always_inline]] nce int16x4_t convert(float16x4_t a) { return vcvt_n_s16_f16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t convert(float16x4_t a) { return vcvt_n_u16_f16(a, n); }
[[gnu::always_inline]] nce float16x4_t negate(float16x4_t a) { return vneg_f16(a); }
[[gnu::always_inline]] nce float16x4_t complex_add_rotate_90(float16x4_t a, float16x4_t b) { return vcadd_rot90_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t complex_add_rotate_270(float16x4_t a, float16x4_t b) { return vcadd_rot270_f16(a, b); }
template <> [[gnu::always_inline]] nce float16x4_t complex_multiply_add(float16x4_t r, float16x4_t a, float16x4_t b) { return vcmla_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float16x4_t complex_multiply_add_rotate_90(float16x4_t r, float16x4_t a, float16x4_t b) { return vcmla_rot90_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float16x4_t complex_multiply_add_rotate_180(float16x4_t r, float16x4_t a, float16x4_t b) { return vcmla_rot180_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float16x4_t complex_multiply_add_rotate_270(float16x4_t r, float16x4_t a, float16x4_t b) { return vcmla_rot270_f16(r, a, b); }
template <int lane>[[gnu::always_inline]] nce float16x4_t complex_multiply_add_lane(float16x4_t r, float16x4_t a, float16x4_t b) { return vcmla_lane_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t complex_multiply_add_rotate_90_lane(float16x4_t r, float16x4_t a, float16x4_t b) { return vcmla_rot90_lane_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t complex_multiply_add_rotate_180_lane(float16x4_t r, float16x4_t a, float16x4_t b) { return vcmla_rot180_lane_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t complex_multiply_add_rotate_270_lane(float16x4_t r, float16x4_t a, float16x4_t b) { return vcmla_rot270_lane_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t complex_multiply_add_lane(float16x4_t r, float16x4_t a, float16x8_t b) { return vcmla_laneq_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t complex_multiply_add_rotate_90_lane(float16x4_t r, float16x4_t a, float16x8_t b) { return vcmla_rot90_laneq_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t complex_multiply_add_rotate_180_lane(float16x4_t r, float16x4_t a, float16x8_t b) { return vcmla_rot180_laneq_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t complex_multiply_add_rotate_270_lane(float16x4_t r, float16x4_t a, float16x8_t b) { return vcmla_rot270_laneq_f16(r, a, b, lane); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(float16x8_t a) { return vreinterpretq_p64_f16(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(float16x8_t a) { return vreinterpretq_p128_f16(a); }
[[gnu::always_inline]] nce float16x8_t absolute(float16x8_t a) { return vabsq_f16(a); }
[[gnu::always_inline]] nce float16x8_t reciprocal_estimate(float16x8_t a) { return vrecpeq_f16(a); }
[[gnu::always_inline]] nce float16x8_t reciprocal_sqrt_estimate(float16x8_t a) { return vrsqrteq_f16(a); }
[[gnu::always_inline]] nce float16x8_t reciprocal_sqrt_step(float16x8_t a, float16x8_t b) { return vrsqrtsq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t reciprocal_step(float16x8_t a, float16x8_t b) { return vrecpsq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t round(float16x8_t a) { return vrndq_f16(a); }
[[gnu::always_inline]] nce float16x8_t round_to_nearest_with_ties_away_from_zero(float16x8_t a) { return vrndaq_f16(a); }
[[gnu::always_inline]] nce float16x8_t round_toward_negative_infinity(float16x8_t a) { return vrndmq_f16(a); }
[[gnu::always_inline]] nce float16x8_t round_to_nearest_with_ties_to_even(float16x8_t a) { return vrndnq_f16(a); }
[[gnu::always_inline]] nce float16x8_t round_toward_positive_infinity(float16x8_t a) { return vrndpq_f16(a); }
[[gnu::always_inline]] nce float16x8_t round_inexact(float16x8_t a) { return vrndxq_f16(a); }
template <int lane>[[gnu::always_inline]] nce float16x8_t multiply_lane(float16x8_t a, float16x4_t v) { return vmulq_lane_f16(a, v, lane); }
template <> [[gnu::always_inline]] nce float16x8_t max(float16x8_t a, float16x8_t b) { return vmaxq_f16(a, b); }
template <> [[gnu::always_inline]] nce float16x8_t max_strict(float16x8_t a, float16x8_t b) { return vmaxnmq_f16(a, b); }
template <> [[gnu::always_inline]] nce float16x8_t min(float16x8_t a, float16x8_t b) { return vminq_f16(a, b); }
template <> [[gnu::always_inline]] nce float16x8_t min_strict(float16x8_t a, float16x8_t b) { return vminnmq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply_add_fused(float16x8_t a, float16x8_t b, float16x8_t c) { return vfmaq_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t multiply_subtract_fused(float16x8_t a, float16x8_t b, float16x8_t c) { return vfmsq_f16(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t greater_than_zero(float16x8_t a) { return vcgtzq_f16(a); }
[[gnu::always_inline]] nce uint16x8_t less_than_or_equal_to_zero(float16x8_t a) { return vclezq_f16(a); }
[[gnu::always_inline]] nce uint16x8_t less_than_zero(float16x8_t a) { return vcltzq_f16(a); }
[[gnu::always_inline]] nce uint16x8_t absolute_greater_than_or_equal(float16x8_t a, float16x8_t b) { return vcageq_f16(a, b); }
[[gnu::always_inline]] nce uint16x8_t absolute_greater_than(float16x8_t a, float16x8_t b) { return vcagtq_f16(a, b); }
[[gnu::always_inline]] nce uint16x8_t absolute_less_than_or_equal(float16x8_t a, float16x8_t b) { return vcaleq_f16(a, b); }
[[gnu::always_inline]] nce uint16x8_t absolute_less_than(float16x8_t a, float16x8_t b) { return vcaltq_f16(a, b); }
[[gnu::always_inline]] nce uint16x8_t equal(float16x8_t a, float16x8_t b) { return vceqq_f16(a, b); }
[[gnu::always_inline]] nce uint16x8_t greater_than_or_equal(float16x8_t a, float16x8_t b) { return vcgeq_f16(a, b); }
[[gnu::always_inline]] nce uint16x8_t greater_than(float16x8_t a, float16x8_t b) { return vcgtq_f16(a, b); }
[[gnu::always_inline]] nce uint16x8_t less_than_or_equal(float16x8_t a, float16x8_t b) { return vcleq_f16(a, b); }
[[gnu::always_inline]] nce uint16x8_t less_than(float16x8_t a, float16x8_t b) { return vcltq_f16(a, b); }
template <int lane>[[gnu::always_inline]] nce float16x8_t complex_multiply_add_lane(float16x8_t r, float16x8_t a, float16x4_t b) { return vcmlaq_lane_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_90_lane(float16x8_t r, float16x8_t a, float16x4_t b) { return vcmlaq_rot90_lane_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_180_lane(float16x8_t r, float16x8_t a, float16x4_t b) { return vcmlaq_rot180_lane_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_270_lane(float16x8_t r, float16x8_t a, float16x4_t b) { return vcmlaq_rot270_lane_f16(r, a, b, lane); }
template <> [[gnu::always_inline]] nce float16x8_t complex_multiply_add(float16x8_t r, float16x8_t a, float16x8_t b) { return vcmlaq_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_90(float16x8_t r, float16x8_t a, float16x8_t b) { return vcmlaq_rot90_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_180(float16x8_t r, float16x8_t a, float16x8_t b) { return vcmlaq_rot180_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_270(float16x8_t r, float16x8_t a, float16x8_t b) { return vcmlaq_rot270_f16(r, a, b); }
template <int lane>[[gnu::always_inline]] nce float16x8_t complex_multiply_add_lane(float16x8_t r, float16x8_t a, float16x8_t b) { return vcmlaq_laneq_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_90_lane(float16x8_t r, float16x8_t a, float16x8_t b) { return vcmlaq_rot90_laneq_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_180_lane(float16x8_t r, float16x8_t a, float16x8_t b) { return vcmlaq_rot180_laneq_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_270_lane(float16x8_t r, float16x8_t a, float16x8_t b) { return vcmlaq_rot270_laneq_f16(r, a, b, lane); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t a, float16_t n) { return vmulq_n_f16(a, n); }
[[gnu::always_inline]] nce uint16x8_t equal_to_zero(float16x8_t a) { return vceqzq_f16(a); }
[[gnu::always_inline]] nce uint16x8_t greater_than_or_equal_to_zero(float16x8_t a) { return vcgezq_f16(a); }
[[gnu::always_inline]] nce float32x2_t max_strict(float32x2_t a, float32x2_t b) { return vmaxnm_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t min_strict(float32x2_t a, float32x2_t b) { return vminnm_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t round(float32x2_t a) { return vrnd_f32(a); }
[[gnu::always_inline]] nce float32x2_t round_to_nearest_with_ties_to_even(float32x2_t a) { return vrndn_f32(a); }
[[gnu::always_inline]] nce float32x2_t round_toward_negative_infinity(float32x2_t a) { return vrndm_f32(a); }
[[gnu::always_inline]] nce float32x2_t round_toward_positive_infinity(float32x2_t a) { return vrndp_f32(a); }
[[gnu::always_inline]] nce float32x2_t round_to_nearest_with_ties_away_from_zero(float32x2_t a) { return vrnda_f32(a); }
[[gnu::always_inline]] nce float32x2_t round_using_current_mode(float32x2_t a) { return vrndi_f32(a); }
[[gnu::always_inline]] nce float32x2_t round_inexact(float32x2_t a) { return vrndx_f32(a); }
template <> [[gnu::always_inline]] nce int32x2_t convert_round_to_nearest_with_ties_to_even(float32x2_t a) { return vcvtn_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x2_t convert_round_to_nearest_with_ties_to_even(float32x2_t a) { return vcvtn_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32x2_t convert_round_toward_negative_infinity(float32x2_t a) { return vcvtm_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x2_t convert_round_toward_negative_infinity(float32x2_t a) { return vcvtm_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32x2_t convert_round_toward_positive_infinity(float32x2_t a) { return vcvtp_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x2_t convert_round_toward_positive_infinity(float32x2_t a) { return vcvtp_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32x2_t convert_round_to_nearest_with_ties_away_from_zero(float32x2_t a) { return vcvta_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x2_t convert_round_to_nearest_with_ties_away_from_zero(float32x2_t a) { return vcvta_u32_f32(a); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(float32x2_t a) { return vreinterpret_p64_f32(a); }
template <> [[gnu::always_inline]] nce float32x2_t multiply_add_long_fused_low(float32x2_t r, float16x4_t a, float16x4_t b) { return vfmlal_low_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float32x2_t multiply_subtract_long_fused_low(float32x2_t r, float16x4_t a, float16x4_t b) { return vfmlsl_low_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float32x2_t multiply_add_long_fused_high(float32x2_t r, float16x4_t a, float16x4_t b) { return vfmlal_high_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float32x2_t multiply_subtract_long_fused_high(float32x2_t r, float16x4_t a, float16x4_t b) { return vfmlsl_high_f16(r, a, b); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_add_long_fused_lane_low(float32x2_t r, float16x4_t a, float16x4_t b) { return vfmlal_lane_low_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_subtract_long_fused_lane_low(float32x2_t r, float16x4_t a, float16x4_t b) { return vfmlsl_lane_low_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_add_long_fused_lane_high(float32x2_t r, float16x4_t a, float16x4_t b) { return vfmlal_lane_high_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_subtract_long_fused_lane_high(float32x2_t r, float16x4_t a, float16x4_t b) { return vfmlsl_lane_high_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_add_long_fused_lane_low(float32x2_t r, float16x4_t a, float16x8_t b) { return vfmlal_laneq_low_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_subtract_long_fused_lane_low(float32x2_t r, float16x4_t a, float16x8_t b) { return vfmlsl_laneq_low_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_add_long_fused_lane_high(float32x2_t r, float16x4_t a, float16x8_t b) { return vfmlal_laneq_high_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_subtract_long_fused_lane_high(float32x2_t r, float16x4_t a, float16x8_t b) { return vfmlsl_laneq_high_f16(r, a, b, lane); }
[[gnu::always_inline]] nce float32x2_t complex_add_rotate_90(float32x2_t a, float32x2_t b) { return vcadd_rot90_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t complex_add_rotate_270(float32x2_t a, float32x2_t b) { return vcadd_rot270_f32(a, b); }
template <> [[gnu::always_inline]] nce float32x2_t complex_multiply_add(float32x2_t r, float32x2_t a, float32x2_t b) { return vcmla_f32(r, a, b); }
template <> [[gnu::always_inline]] nce float32x2_t complex_multiply_add_rotate_90(float32x2_t r, float32x2_t a, float32x2_t b) { return vcmla_rot90_f32(r, a, b); }
template <> [[gnu::always_inline]] nce float32x2_t complex_multiply_add_rotate_180(float32x2_t r, float32x2_t a, float32x2_t b) { return vcmla_rot180_f32(r, a, b); }
template <> [[gnu::always_inline]] nce float32x2_t complex_multiply_add_rotate_270(float32x2_t r, float32x2_t a, float32x2_t b) { return vcmla_rot270_f32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce float32x2_t complex_multiply_add_lane(float32x2_t r, float32x2_t a, float32x2_t b) { return vcmla_lane_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t complex_multiply_add_rotate_90_lane(float32x2_t r, float32x2_t a, float32x2_t b) { return vcmla_rot90_lane_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t complex_multiply_add_rotate_180_lane(float32x2_t r, float32x2_t a, float32x2_t b) { return vcmla_rot180_lane_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t complex_multiply_add_rotate_270_lane(float32x2_t r, float32x2_t a, float32x2_t b) { return vcmla_rot270_lane_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t complex_multiply_add_lane(float32x2_t r, float32x2_t a, float32x4_t b) { return vcmla_laneq_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t complex_multiply_add_rotate_90_lane(float32x2_t r, float32x2_t a, float32x4_t b) { return vcmla_rot90_laneq_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t complex_multiply_add_rotate_180_lane(float32x2_t r, float32x2_t a, float32x4_t b) { return vcmla_rot180_laneq_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t complex_multiply_add_rotate_270_lane(float32x2_t r, float32x2_t a, float32x4_t b) { return vcmla_rot270_laneq_f32(r, a, b, lane); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(float32x2_t a) { return vreinterpret_bf16_f32(a); }
template <> [[gnu::always_inline]] nce float32x2_t dot_product(float32x2_t r, bfloat16x4_t a, bfloat16x4_t b) { return vbfdot_f32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce float32x2_t dot_product_lane(float32x2_t r, bfloat16x4_t a, bfloat16x4_t b) { return vbfdot_lane_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t dot_product_lane(float32x2_t r, bfloat16x4_t a, bfloat16x8_t b) { return vbfdot_laneq_f32(r, a, b, lane); }
[[gnu::always_inline]] nce float32x4_t round_using_current_mode(float32x4_t a) { return vrndiq_f32(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(float32x4_t a) { return vreinterpretq_p64_f32(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(float32x4_t a) { return vreinterpretq_p128_f32(a); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_long_fused_lane_low(float32x4_t r, float16x8_t a, float16x4_t b) { return vfmlalq_lane_low_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_subtract_long_fused_lane_low(float32x4_t r, float16x8_t a, float16x4_t b) { return vfmlslq_lane_low_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_long_fused_lane_high(float32x4_t r, float16x8_t a, float16x4_t b) { return vfmlalq_lane_high_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_subtract_long_fused_lane_high(float32x4_t r, float16x8_t a, float16x4_t b) { return vfmlslq_lane_high_f16(r, a, b, lane); }
template <> [[gnu::always_inline]] nce float32x4_t multiply_add_long_fused_low(float32x4_t r, float16x8_t a, float16x8_t b) { return vfmlalq_low_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float32x4_t multiply_subtract_long_fused_low(float32x4_t r, float16x8_t a, float16x8_t b) { return vfmlslq_low_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float32x4_t multiply_add_long_fused_high(float32x4_t r, float16x8_t a, float16x8_t b) { return vfmlalq_high_f16(r, a, b); }
template <> [[gnu::always_inline]] nce float32x4_t multiply_subtract_long_fused_high(float32x4_t r, float16x8_t a, float16x8_t b) { return vfmlslq_high_f16(r, a, b); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_long_fused_lane_low(float32x4_t r, float16x8_t a, float16x8_t b) { return vfmlalq_laneq_low_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_subtract_long_fused_lane_low(float32x4_t r, float16x8_t a, float16x8_t b) { return vfmlslq_laneq_low_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_long_fused_lane_high(float32x4_t r, float16x8_t a, float16x8_t b) { return vfmlalq_laneq_high_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_subtract_long_fused_lane_high(float32x4_t r, float16x8_t a, float16x8_t b) { return vfmlslq_laneq_high_f16(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t complex_multiply_add_lane(float32x4_t r, float32x4_t a, float32x2_t b) { return vcmlaq_lane_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_90_lane(float32x4_t r, float32x4_t a, float32x2_t b) { return vcmlaq_rot90_lane_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_180_lane(float32x4_t r, float32x4_t a, float32x2_t b) { return vcmlaq_rot180_lane_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_270_lane(float32x4_t r, float32x4_t a, float32x2_t b) { return vcmlaq_rot270_lane_f32(r, a, b, lane); }
template <> [[gnu::always_inline]] nce float32x4_t complex_multiply_add(float32x4_t r, float32x4_t a, float32x4_t b) { return vcmlaq_f32(r, a, b); }
template <> [[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_90(float32x4_t r, float32x4_t a, float32x4_t b) { return vcmlaq_rot90_f32(r, a, b); }
template <> [[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_180(float32x4_t r, float32x4_t a, float32x4_t b) { return vcmlaq_rot180_f32(r, a, b); }
template <> [[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_270(float32x4_t r, float32x4_t a, float32x4_t b) { return vcmlaq_rot270_f32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce float32x4_t complex_multiply_add_lane(float32x4_t r, float32x4_t a, float32x4_t b) { return vcmlaq_laneq_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_90_lane(float32x4_t r, float32x4_t a, float32x4_t b) { return vcmlaq_rot90_laneq_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_180_lane(float32x4_t r, float32x4_t a, float32x4_t b) { return vcmlaq_rot180_laneq_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_270_lane(float32x4_t r, float32x4_t a, float32x4_t b) { return vcmlaq_rot270_laneq_f32(r, a, b, lane); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(float32x4_t a) { return vreinterpretq_bf16_f32(a); }
template <> [[gnu::always_inline]] nce bfloat16x4_t convert(float32x4_t a) { return vcvt_bf16_f32(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t convert_low(float32x4_t a) { return vcvtq_low_bf16_f32(a); }
template <> [[gnu::always_inline]] nce float32x4_t dot_product(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b) { return vbfdotq_f32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce float32x4_t dot_product_lane(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b) { return vbfdotq_laneq_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t dot_product_lane(float32x4_t r, bfloat16x8_t a, bfloat16x4_t b) { return vbfdotq_lane_f32(r, a, b, lane); }
[[gnu::always_inline]] nce float32x4_t matrix_multiply_add(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b) { return vbfmmlaq_f32(r, a, b); }
template <> [[gnu::always_inline]] nce float32x4_t multiply_add_long_widen_bottom(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b) { return vbfmlalbq_f32(r, a, b); }
template <> [[gnu::always_inline]] nce float32x4_t multiply_add_long_widen_top(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b) { return vbfmlaltq_f32(r, a, b); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_long_widen_bottom_lane(float32x4_t r, bfloat16x8_t a, bfloat16x4_t b) { return vbfmlalbq_lane_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_long_widen_bottom_lane(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b) { return vbfmlalbq_laneq_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_long_widen_top_lane(float32x4_t r, bfloat16x8_t a, bfloat16x4_t b) { return vbfmlaltq_lane_f32(r, a, b, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_long_widen_top_lane(float32x4_t r, bfloat16x8_t a, bfloat16x8_t b) { return vbfmlaltq_laneq_f32(r, a, b, lane); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(poly8x8_t a) { return vreinterpret_p64_p8(a); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(poly8x8_t a) { return vreinterpret_bf16_p8(a); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(poly16x4_t a) { return vreinterpret_p64_p16(a); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(poly16x4_t a) { return vreinterpret_bf16_p16(a); }
[[gnu::always_inline]] nce float64x1_t round_to_nearest_with_ties_to_even(float64x1_t a) { return vrndn_f64(a); }
[[gnu::always_inline]] nce float64x2_t round_to_nearest_with_ties_to_even(float64x2_t a) { return vrndnq_f64(a); }
[[gnu::always_inline]] nce float32_t round_to_nearest_with_ties_to_even(float32_t a) { return vrndns_f32(a); }
[[gnu::always_inline]] nce uint64x1_t equal(poly64x1_t a, poly64x1_t b) { return vceq_p64(a, b); }
[[gnu::always_inline]] nce uint64x2_t equal(poly64x2_t a, poly64x2_t b) { return vceqq_p64(a, b); }
[[gnu::always_inline]] nce uint64x1_t equal_to_zero(poly64x1_t a) { return vceqz_p64(a); }
[[gnu::always_inline]] nce uint64x2_t equal_to_zero(poly64x2_t a) { return vceqzq_p64(a); }
[[gnu::always_inline]] nce uint64x1_t compare_test_nonzero(poly64x1_t a, poly64x1_t b) { return vtst_p64(a, b); }
[[gnu::always_inline]] nce uint64x2_t compare_test_nonzero(poly64x2_t a, poly64x2_t b) { return vtstq_p64(a, b); }
template <int n>[[gnu::always_inline]] nce poly64x1_t shift_left_insert(poly64x1_t a, poly64x1_t b) { return vsli_n_p64(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly64x2_t shift_left_insert(poly64x2_t a, poly64x2_t b) { return vsliq_n_p64(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly64x1_t shift_right_insert(poly64x1_t a, poly64x1_t b) { return vsri_n_p64(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly64x2_t shift_right_insert(poly64x2_t a, poly64x2_t b) { return vsriq_n_p64(a, b, n); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(poly64x1_t a) { return vreinterpret_u64_p64(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(poly8x16_t a) { return vreinterpretq_p64_p8(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(poly8x16_t a) { return vreinterpretq_p128_p8(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(poly16x8_t a) { return vreinterpretq_p64_p16(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(poly16x8_t a) { return vreinterpretq_p128_p16(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(int64x2_t a) { return vreinterpretq_p64_s64(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(int64x2_t a) { return vreinterpretq_p128_s64(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(poly64x2_t a) { return vreinterpretq_u64_p64(a); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(poly64x1_t a) { return vreinterpret_s8_p64(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(poly64x1_t a) { return vreinterpret_s16_p64(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(poly64x1_t a) { return vreinterpret_s32_p64(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(poly64x1_t a) { return vreinterpret_u8_p64(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(poly64x1_t a) { return vreinterpret_u16_p64(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(poly64x1_t a) { return vreinterpret_u32_p64(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(poly64x1_t a) { return vreinterpret_p8_p64(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(poly64x1_t a) { return vreinterpret_p16_p64(a); }
//template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(poly64x1_t a) { return vreinterpret_mf8_p64(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(poly64x1_t a) { return vreinterpret_s64_p64(a); }
template <> [[gnu::always_inline]] nce float16x4_t reinterpret(poly64x1_t a) { return vreinterpret_f16_p64(a); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(poly64x2_t a) { return vreinterpretq_s8_p64(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(poly64x2_t a) { return vreinterpretq_s16_p64(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(poly64x2_t a) { return vreinterpretq_s32_p64(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(poly64x2_t a) { return vreinterpretq_u8_p64(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(poly64x2_t a) { return vreinterpretq_u16_p64(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(poly64x2_t a) { return vreinterpretq_u32_p64(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(poly64x2_t a) { return vreinterpretq_p8_p64(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(poly64x2_t a) { return vreinterpretq_p16_p64(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(poly64x2_t a) { return vreinterpretq_s64_p64(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(poly64x2_t a) { return vreinterpretq_f16_p64(a); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(poly128_t a) { return vreinterpretq_s8_p128(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(poly128_t a) { return vreinterpretq_s16_p128(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(poly128_t a) { return vreinterpretq_s32_p128(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(poly128_t a) { return vreinterpretq_u8_p128(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(poly128_t a) { return vreinterpretq_u16_p128(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(poly128_t a) { return vreinterpretq_u32_p128(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(poly128_t a) { return vreinterpretq_p8_p128(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(poly128_t a) { return vreinterpretq_p16_p128(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(poly128_t a) { return vreinterpretq_u64_p128(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(poly128_t a) { return vreinterpretq_s64_p128(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(poly128_t a) { return vreinterpretq_f16_p128(a); }
#ifdef __clang__
[[gnu::always_inline]] nce poly64x1_t bitwise_select(poly64x1_t a, poly64x1_t b, poly64x1_t c) { return vbsl_p64(a, b, c); }
[[gnu::always_inline]] nce poly64x2_t bitwise_select(poly64x2_t a, poly64x2_t b, poly64x2_t c) { return vbslq_p64(a, b, c); }
#else
[[gnu::always_inline]] nce poly64x1_t bitwise_select(poly64x1_t a, poly64x1_t b, poly64x1_t c) { return vbsl_p64(*(uint64x1_t*)&a, b, c); }
[[gnu::always_inline]] nce poly64x2_t bitwise_select(poly64x2_t a, poly64x2_t b, poly64x2_t c) { return vbslq_p64(*(uint64x2_t*)&a, b, c); }
#endif
template <int lane1, int lane2>[[gnu::always_inline]] nce poly64x1_t copy_lane(poly64x1_t a, poly64x1_t b) { return vcopy_lane_p64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly64x2_t copy_lane(poly64x2_t a, poly64x1_t b) { return vcopyq_lane_p64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly64x1_t copy_lane(poly64x1_t a, poly64x2_t b) { return vcopy_laneq_p64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly64x2_t copy_lane(poly64x2_t a, poly64x2_t b) { return vcopyq_laneq_p64(a, lane1, b, lane2); }
template <> [[gnu::always_inline]] nce poly64x1_t create(uint64_t a) { return vcreate_p64(a); }
template <> [[gnu::always_inline]] nce poly64x1_t duplicate(poly64_t value) { return vdup_n_p64(value); }
template <> [[gnu::always_inline]] nce poly64x2_t duplicate(poly64_t value) { return vdupq_n_p64(value); }
template <int lane>[[gnu::always_inline]] nce poly64x1_t duplicate_lane(poly64x1_t vec) { return vdup_lane_p64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x2_t duplicate_lane_quad(poly64x1_t vec) { return vdupq_lane_p64(vec, lane); }
[[gnu::always_inline]] nce poly64x2_t combine(poly64x1_t low, poly64x1_t high) { return vcombine_p64(low, high); }
template <> [[gnu::always_inline]] nce poly64x1_t get_high(poly64x2_t a) { return vget_high_p64(a); }
template <> [[gnu::always_inline]] nce poly64x1_t get_low(poly64x2_t a) { return vget_low_p64(a); }
template <int lane>[[gnu::always_inline]] nce poly64_t get_lane(poly64x1_t v) { return vget_lane_p64(v, lane); }
template <int lane>[[gnu::always_inline]] nce poly64_t get_lane(poly64x2_t v) { return vgetq_lane_p64(v, lane); }
template <int n>[[gnu::always_inline]] nce poly64x1_t extract(poly64x1_t a, poly64x1_t b) { return vext_p64(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly64x2_t extract(poly64x2_t a, poly64x2_t b) { return vextq_p64(a, b, n); }
template <int lane>[[gnu::always_inline]] nce poly64x1_t set_lane(poly64_t a, poly64x1_t v) { return vset_lane_p64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x2_t set_lane(poly64_t a, poly64x2_t v) { return vsetq_lane_p64(a, v, lane); }
template <> [[gnu::always_inline]] inline poly64x1_t load1(poly64_t const *ptr) { return vld1_p64(ptr); }
template <> [[gnu::always_inline]] inline poly64x2_t load1(poly64_t const *ptr) { return vld1q_p64(ptr); }
template <int lane>[[gnu::always_inline]] nce poly64x1_t load1_lane(poly64_t const *ptr, poly64x1_t src) { return vld1_lane_p64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x2_t load1_lane(poly64_t const *ptr, poly64x2_t src) { return vld1q_lane_p64(ptr, src, lane); }
template <> [[gnu::always_inline]] inline poly64x1_t load1_duplicate(poly64_t const *ptr) { return vld1_dup_p64(ptr); }
template <> [[gnu::always_inline]] inline poly64x2_t load1_duplicate(poly64_t const *ptr) { return vld1q_dup_p64(ptr); }
template <> [[gnu::always_inline]] inline poly64x1x2_t load2(poly64_t const *ptr) { return vld2_p64(ptr); }
template <> [[gnu::always_inline]] inline poly64x1x3_t load3(poly64_t const *ptr) { return vld3_p64(ptr); }
template <> [[gnu::always_inline]] inline poly64x1x4_t load4(poly64_t const *ptr) { return vld4_p64(ptr); }
template <> [[gnu::always_inline]] inline poly64x1x2_t load2_duplicate(poly64_t const *ptr) { return vld2_dup_p64(ptr); }
template <> [[gnu::always_inline]] inline poly64x1x3_t load3_duplicate(poly64_t const *ptr) { return vld3_dup_p64(ptr); }
template <> [[gnu::always_inline]] inline poly64x1x4_t load4_duplicate(poly64_t const *ptr) { return vld4_dup_p64(ptr); }
template <> [[gnu::always_inline]] inline poly64x1x2_t load1_x2(poly64_t const *ptr) { return vld1_p64_x2(ptr); }
template <> [[gnu::always_inline]] inline poly64x2x2_t load1_x2(poly64_t const *ptr) { return vld1q_p64_x2(ptr); }
template <> [[gnu::always_inline]] inline poly64x1x3_t load1_x3(poly64_t const *ptr) { return vld1_p64_x3(ptr); }
template <> [[gnu::always_inline]] inline poly64x2x3_t load1_x3(poly64_t const *ptr) { return vld1q_p64_x3(ptr); }
template <> [[gnu::always_inline]] inline poly64x1x4_t load1_x4(poly64_t const *ptr) { return vld1_p64_x4(ptr); }
template <> [[gnu::always_inline]] inline poly64x2x4_t load1_x4(poly64_t const *ptr) { return vld1q_p64_x4(ptr); }
[[gnu::always_inline]] inline poly128_t load_register(poly128_t const *ptr) { return vldrq_p128(ptr); }
template <> [[gnu::always_inline]] inline void store1(poly64_t *ptr, poly64x1_t val) { return vst1_p64(ptr, val); }
template <> [[gnu::always_inline]] inline void store1(poly64_t *ptr, poly64x2_t val) { return vst1q_p64(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(poly64_t *ptr, poly64x1_t val) { return vst1_lane_p64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(poly64_t *ptr, poly64x2_t val) { return vst1q_lane_p64(ptr, val, lane); }
[[gnu::always_inline]] inline void store2(poly64_t *ptr, poly64x1x2_t val) { return vst2_p64(ptr, val); }
[[gnu::always_inline]] inline void store3(poly64_t *ptr, poly64x1x3_t val) { return vst3_p64(ptr, val); }
[[gnu::always_inline]] inline void store4(poly64_t *ptr, poly64x1x4_t val) { return vst4_p64(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(poly64_t *ptr, poly64x1x2_t val) { return vst1_p64_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(poly64_t *ptr, poly64x2x2_t val) { return vst1q_p64_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(poly64_t *ptr, poly64x1x3_t val) { return vst1_p64_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(poly64_t *ptr, poly64x1x4_t val) { return vst1_p64_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(poly64_t *ptr, poly64x2x4_t val) { return vst1q_p64_x4(ptr, val); }
[[gnu::always_inline]] inline void store_register(poly128_t *ptr, poly128_t val) { return vstrq_p128(ptr, val); }
[[gnu::always_inline]] nce uint32_t sha1_fixed_rotate(uint32_t hash_e) { return vsha1h_u32(hash_e); }
[[gnu::always_inline]] nce poly128_t multiply_long(poly64_t a, poly64_t b) { return vmull_p64(a, b); }
[[gnu::always_inline]] nce poly128_t multiply_long_high(poly64x2_t a, poly64x2_t b) { return vmull_high_p64(a, b); }
#if defined(__ARM_ACLE) && defined(__ARM_FEATURE_CRC32)
[[gnu::always_inline]] nce uint32_t crc32(uint32_t a, uint8_t b) { return __crc32b(a, b); }
[[gnu::always_inline]] nce uint32_t crc32(uint32_t a, uint16_t b) { return __crc32h(a, b); }
[[gnu::always_inline]] nce uint32_t crc32(uint32_t a, uint32_t b) { return __crc32w(a, b); }
[[gnu::always_inline]] nce uint32_t crc32(uint32_t a, uint64_t b) { return __crc32d(a, b); }
[[gnu::always_inline]] nce uint32_t crc32_castagnoli(uint32_t a, uint8_t b) { return __crc32cb(a, b); }
[[gnu::always_inline]] nce uint32_t crc32_castagnoli(uint32_t a, uint16_t b) { return __crc32ch(a, b); }
[[gnu::always_inline]] nce uint32_t crc32_castagnoli(uint32_t a, uint32_t b) { return __crc32cw(a, b); }
[[gnu::always_inline]] nce uint32_t crc32_castagnoli(uint32_t a, uint64_t b) { return __crc32cd(a, b); }
#endif
#if defined(__ARM_ACLE) && defined(__ARM_FEATURE_FP16_SCALAR_ARITHMETIC)
[[gnu::always_inline]] nce float16_t absolute(float16_t a) { return vabsh_f16(a); }
[[gnu::always_inline]] nce float16_t round(float16_t a) { return vrndh_f16(a); }
[[gnu::always_inline]] nce float16_t round_to_nearest_with_ties_away_from_zero(float16_t a) { return vrndah_f16(a); }
[[gnu::always_inline]] nce float16_t round_using_current_mode(float16_t a) { return vrndih_f16(a); }
[[gnu::always_inline]] nce float16_t round_toward_negative_infinity(float16_t a) { return vrndmh_f16(a); }
[[gnu::always_inline]] nce float16_t round_to_nearest_with_ties_to_even(float16_t a) { return vrndnh_f16(a); }
[[gnu::always_inline]] nce float16_t round_toward_positive_infinity(float16_t a) { return vrndph_f16(a); }
[[gnu::always_inline]] nce float16_t round_inexact(float16_t a) { return vrndxh_f16(a); }
[[gnu::always_inline]] nce float16_t square_root(float16_t a) { return vsqrth_f16(a); }
[[gnu::always_inline]] nce float16_t add(float16_t a, float16_t b) { return vaddh_f16(a, b); }
[[gnu::always_inline]] nce float16_t divide(float16_t a, float16_t b) { return vdivh_f16(a, b); }
[[gnu::always_inline]] nce float16_t max_strict(float16_t a, float16_t b) { return vmaxnmh_f16(a, b); }
[[gnu::always_inline]] nce float16_t min_strict(float16_t a, float16_t b) { return vminnmh_f16(a, b); }
[[gnu::always_inline]] nce float16_t multiply(float16_t a, float16_t b) { return vmulh_f16(a, b); }
[[gnu::always_inline]] nce float16_t multiply_add_fused(float16_t a, float16_t b, float16_t c) { return vfmah_f16(a, b, c); }
[[gnu::always_inline]] nce float16_t multiply_subtract_fused(float16_t a, float16_t b, float16_t c) { return vfmsh_f16(a, b, c); }
[[gnu::always_inline]] nce float16_t subtract(float16_t a, float16_t b) { return vsubh_f16(a, b); }
template <> [[gnu::always_inline]] nce float16_t convert(int32_t a) { return vcvth_f16_s32(a); }
template <> [[gnu::always_inline]] nce float16_t convert(uint32_t a) { return vcvth_f16_u32(a); }
template <> [[gnu::always_inline]] nce int32_t convert(float16_t a) { return vcvth_s32_f16(a); }
template <> [[gnu::always_inline]] nce uint32_t convert(float16_t a) { return vcvth_u32_f16(a); }
template <> [[gnu::always_inline]] nce int32_t convert_round_to_nearest_with_ties_away_from_zero(float16_t a) { return vcvtah_s32_f16(a); }
template <> [[gnu::always_inline]] nce uint32_t convert_round_to_nearest_with_ties_away_from_zero(float16_t a) { return vcvtah_u32_f16(a); }
template <> [[gnu::always_inline]] nce int32_t convert_round_toward_negative_infinity(float16_t a) { return vcvtmh_s32_f16(a); }
template <> [[gnu::always_inline]] nce uint32_t convert_round_toward_negative_infinity(float16_t a) { return vcvtmh_u32_f16(a); }
template <> [[gnu::always_inline]] nce int32_t convert_round_to_nearest_with_ties_to_even(float16_t a) { return vcvtnh_s32_f16(a); }
template <> [[gnu::always_inline]] nce uint32_t convert_round_to_nearest_with_ties_to_even(float16_t a) { return vcvtnh_u32_f16(a); }
template <> [[gnu::always_inline]] nce int32_t convert_round_toward_positive_infinity(float16_t a) { return vcvtph_s32_f16(a); }
template <> [[gnu::always_inline]] nce uint32_t convert_round_toward_positive_infinity(float16_t a) { return vcvtph_u32_f16(a); }
template <int n>[[gnu::always_inline]] nce float16_t convert(int32_t a) { return vcvth_n_f16_s32(a, n); }
template <int n>[[gnu::always_inline]] nce float16_t convert(uint32_t a) { return vcvth_n_f16_u32(a, n); }
template <int n>[[gnu::always_inline]] nce int32_t convert(float16_t a) { return vcvth_n_s32_f16(a, n); }
template <int n>[[gnu::always_inline]] nce uint32_t convert(float16_t a) { return vcvth_n_u32_f16(a, n); }
[[gnu::always_inline]] nce float16_t negate(float16_t a) { return vnegh_f16(a); }
#endif
template <> [[gnu::always_inline]] nce bfloat16x4_t create(uint64_t a) { return vcreate_bf16(a); }
template <> [[gnu::always_inline]] nce bfloat16x4_t duplicate(bfloat16_t value) { return vdup_n_bf16(value); }
template <> [[gnu::always_inline]] nce bfloat16x8_t duplicate(bfloat16_t value) { return vdupq_n_bf16(value); }
template <int lane>[[gnu::always_inline]] nce bfloat16x4_t duplicate_lane(bfloat16x4_t vec) { return vdup_lane_bf16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x8_t duplicate_lane_quad(bfloat16x4_t vec) { return vdupq_lane_bf16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x4_t duplicate_lane(bfloat16x8_t vec) { return vdup_laneq_bf16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x8_t duplicate_lane_quad(bfloat16x8_t vec) { return vdupq_laneq_bf16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16_t duplicate_lane(bfloat16x4_t vec) { return vduph_lane_bf16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16_t duplicate_lane(bfloat16x8_t vec) { return vduph_laneq_bf16(vec, lane); }
[[gnu::always_inline]] nce bfloat16x8_t combine(bfloat16x4_t low, bfloat16x4_t high) { return vcombine_bf16(low, high); }
template <> [[gnu::always_inline]] nce bfloat16x4_t get_high(bfloat16x8_t a) { return vget_high_bf16(a); }
template <> [[gnu::always_inline]] nce bfloat16x4_t get_low(bfloat16x8_t a) { return vget_low_bf16(a); }
template <int lane>[[gnu::always_inline]] nce bfloat16_t get_lane(bfloat16x4_t v) { return vget_lane_bf16(v, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16_t get_lane(bfloat16x8_t v) { return vgetq_lane_bf16(v, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x4_t set_lane(bfloat16_t a, bfloat16x4_t v) { return vset_lane_bf16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x8_t set_lane(bfloat16_t a, bfloat16x8_t v) { return vsetq_lane_bf16(a, v, lane); }
template <> [[gnu::always_inline]] inline bfloat16x4_t load1(bfloat16_t const *ptr) { return vld1_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8_t load1(bfloat16_t const *ptr) { return vld1q_bf16(ptr); }
template <int lane>[[gnu::always_inline]] nce bfloat16x4_t load1_lane(bfloat16_t const *ptr, bfloat16x4_t src) { return vld1_lane_bf16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x8_t load1_lane(bfloat16_t const *ptr, bfloat16x8_t src) { return vld1q_lane_bf16(ptr, src, lane); }
template <> [[gnu::always_inline]] inline bfloat16x4_t load1_duplicate(bfloat16_t const *ptr) { return vld1_dup_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8_t load1_duplicate(bfloat16_t const *ptr) { return vld1q_dup_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x4x2_t load2(bfloat16_t const *ptr) { return vld2_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8x2_t load2(bfloat16_t const *ptr) { return vld2q_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x4x3_t load3(bfloat16_t const *ptr) { return vld3_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8x3_t load3(bfloat16_t const *ptr) { return vld3q_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x4x4_t load4(bfloat16_t const *ptr) { return vld4_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8x4_t load4(bfloat16_t const *ptr) { return vld4q_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x4x2_t load2_duplicate(bfloat16_t const *ptr) { return vld2_dup_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8x2_t load2_duplicate(bfloat16_t const *ptr) { return vld2q_dup_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x4x3_t load3_duplicate(bfloat16_t const *ptr) { return vld3_dup_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8x3_t load3_duplicate(bfloat16_t const *ptr) { return vld3q_dup_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x4x4_t load4_duplicate(bfloat16_t const *ptr) { return vld4_dup_bf16(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8x4_t load4_duplicate(bfloat16_t const *ptr) { return vld4q_dup_bf16(ptr); }
template <int lane>[[gnu::always_inline]] nce bfloat16x4x2_t load2_lane(bfloat16_t const *ptr, bfloat16x4x2_t src) { return vld2_lane_bf16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x8x2_t load2_lane(bfloat16_t const *ptr, bfloat16x8x2_t src) { return vld2q_lane_bf16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x4x3_t load3_lane(bfloat16_t const *ptr, bfloat16x4x3_t src) { return vld3_lane_bf16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x8x3_t load3_lane(bfloat16_t const *ptr, bfloat16x8x3_t src) { return vld3q_lane_bf16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x4x4_t load4_lane(bfloat16_t const *ptr, bfloat16x4x4_t src) { return vld4_lane_bf16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce bfloat16x8x4_t load4_lane(bfloat16_t const *ptr, bfloat16x8x4_t src) { return vld4q_lane_bf16(ptr, src, lane); }
template <> [[gnu::always_inline]] inline bfloat16x4x2_t load1_x2(bfloat16_t const *ptr) { return vld1_bf16_x2(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8x2_t load1_x2(bfloat16_t const *ptr) { return vld1q_bf16_x2(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x4x3_t load1_x3(bfloat16_t const *ptr) { return vld1_bf16_x3(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8x3_t load1_x3(bfloat16_t const *ptr) { return vld1q_bf16_x3(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x4x4_t load1_x4(bfloat16_t const *ptr) { return vld1_bf16_x4(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8x4_t load1_x4(bfloat16_t const *ptr) { return vld1q_bf16_x4(ptr); }
template <> [[gnu::always_inline]] inline void store1(bfloat16_t *ptr, bfloat16x4_t val) { return vst1_bf16(ptr, val); }
template <> [[gnu::always_inline]] inline void store1(bfloat16_t *ptr, bfloat16x8_t val) { return vst1q_bf16(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(bfloat16_t *ptr, bfloat16x4_t val) { return vst1_lane_bf16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(bfloat16_t *ptr, bfloat16x8_t val) { return vst1q_lane_bf16(ptr, val, lane); }
template <> [[gnu::always_inline]] inline void store2(bfloat16_t *ptr, bfloat16x4x2_t val) { return vst2_bf16(ptr, val); }
template <> [[gnu::always_inline]] inline void store2(bfloat16_t *ptr, bfloat16x8x2_t val) { return vst2q_bf16(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(bfloat16_t *ptr, bfloat16x4x3_t val) { return vst3_bf16(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(bfloat16_t *ptr, bfloat16x8x3_t val) { return vst3q_bf16(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(bfloat16_t *ptr, bfloat16x4x4_t val) { return vst4_bf16(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(bfloat16_t *ptr, bfloat16x8x4_t val) { return vst4q_bf16(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(bfloat16_t *ptr, bfloat16x4x2_t val) { return vst2_lane_bf16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(bfloat16_t *ptr, bfloat16x8x2_t val) { return vst2q_lane_bf16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(bfloat16_t *ptr, bfloat16x4x3_t val) { return vst3_lane_bf16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(bfloat16_t *ptr, bfloat16x8x3_t val) { return vst3q_lane_bf16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(bfloat16_t *ptr, bfloat16x4x4_t val) { return vst4_lane_bf16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(bfloat16_t *ptr, bfloat16x8x4_t val) { return vst4q_lane_bf16(ptr, val, lane); }
[[gnu::always_inline]] inline void store1_x2(bfloat16_t *ptr, bfloat16x4x2_t val) { return vst1_bf16_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(bfloat16_t *ptr, bfloat16x8x2_t val) { return vst1q_bf16_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(bfloat16_t *ptr, bfloat16x4x3_t val) { return vst1_bf16_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(bfloat16_t *ptr, bfloat16x8x3_t val) { return vst1q_bf16_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(bfloat16_t *ptr, bfloat16x4x4_t val) { return vst1_bf16_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(bfloat16_t *ptr, bfloat16x8x4_t val) { return vst1q_bf16_x4(ptr, val); }
[[gnu::always_inline]] nce bfloat16x4_t reinterpret(int64x1_t a) { return vreinterpret_bf16_s64(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(poly8x16_t a) { return vreinterpretq_bf16_p8(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(poly16x8_t a) { return vreinterpretq_bf16_p16(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(int64x2_t a) { return vreinterpretq_bf16_s64(a); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(poly64x1_t a) { return vreinterpret_bf16_p64(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(poly64x2_t a) { return vreinterpretq_bf16_p64(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(poly128_t a) { return vreinterpretq_bf16_p128(a); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(bfloat16x4_t a) { return vreinterpret_s8_bf16(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(bfloat16x4_t a) { return vreinterpret_s16_bf16(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(bfloat16x4_t a) { return vreinterpret_s32_bf16(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(bfloat16x4_t a) { return vreinterpret_f32_bf16(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(bfloat16x4_t a) { return vreinterpret_u8_bf16(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(bfloat16x4_t a) { return vreinterpret_u16_bf16(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(bfloat16x4_t a) { return vreinterpret_u32_bf16(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(bfloat16x4_t a) { return vreinterpret_p8_bf16(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(bfloat16x4_t a) { return vreinterpret_p16_bf16(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(bfloat16x4_t a) { return vreinterpret_u64_bf16(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(bfloat16x4_t a) { return vreinterpret_s64_bf16(a); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(bfloat16x4_t a) { return vreinterpret_p64_bf16(a); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(bfloat16x8_t a) { return vreinterpretq_s8_bf16(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(bfloat16x8_t a) { return vreinterpretq_s16_bf16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(bfloat16x8_t a) { return vreinterpretq_s32_bf16(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(bfloat16x8_t a) { return vreinterpretq_f32_bf16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(bfloat16x8_t a) { return vreinterpretq_u8_bf16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(bfloat16x8_t a) { return vreinterpretq_u16_bf16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(bfloat16x8_t a) { return vreinterpretq_u32_bf16(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(bfloat16x8_t a) { return vreinterpretq_p8_bf16(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(bfloat16x8_t a) { return vreinterpretq_p16_bf16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(bfloat16x8_t a) { return vreinterpretq_u64_bf16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(bfloat16x8_t a) { return vreinterpretq_s64_bf16(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(bfloat16x8_t a) { return vreinterpretq_p64_bf16(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(bfloat16x8_t a) { return vreinterpretq_p128_bf16(a); }
[[gnu::always_inline]] nce float32x4_t convert(bfloat16x4_t a) { return vcvt_f32_bf16(a); }
template <> [[gnu::always_inline]] nce float32x4_t convert_low(bfloat16x8_t a) { return vcvtq_low_f32_bf16(a); }
template <> [[gnu::always_inline]] nce float32x4_t convert_high(bfloat16x8_t a) { return vcvtq_high_f32_bf16(a); }
[[gnu::always_inline]] nce bfloat16x8_t convert_high(bfloat16x8_t inactive, float32x4_t a) { return vcvtq_high_bf16_f32(inactive, a); }
[[gnu::always_inline]] nce bfloat16_t convert(float32_t a) { return vcvth_bf16_f32(a); }
[[gnu::always_inline]] nce float32_t convert_round_to_nearest_with_ties_away_from_zero(bfloat16_t a) { return vcvtah_f32_bf16(a); }
// clang-format on
}  // namespace neon
#undef nce
#endif // __cplusplus

