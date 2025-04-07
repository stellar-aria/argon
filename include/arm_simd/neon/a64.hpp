#pragma once
#include "a32.hpp"

#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

#ifdef __cplusplus
namespace neon {
// clang-format off
template <typename T> nce T max(float64x1_t a, float64x1_t b);
template <typename T> nce T max(float64x2_t a, float64x2_t b);
template <typename T> nce T min(float64x1_t a, float64x1_t b);
template <typename T> nce T min(float64x2_t a, float64x2_t b);
template <typename T> nce T max_strict(float64x1_t a, float64x1_t b);
template <typename T> nce T max_strict(float64x2_t a, float64x2_t b);
template <typename T> nce T min_strict(float64x1_t a, float64x1_t b);
template <typename T> nce T min_strict(float64x2_t a, float64x2_t b);

template <typename T> nce T shift_right_saturate_narrow(int16_t a);
template <typename T> nce T shift_right_saturate_narrow(int32_t a);
template <typename T> nce T shift_right_saturate_narrow(int64_t a);
template <typename T> nce T shift_right_saturate_narrow(uint16_t a);
template <typename T> nce T shift_right_saturate_narrow(uint32_t a);
template <typename T> nce T shift_right_saturate_narrow(uint64_t a);
template <typename T> nce T shift_right_saturate_narrow(int8x8_t r, int16x8_t a);
template <typename T> nce T shift_right_saturate_narrow(int16x4_t r, int32x4_t a);
template <typename T> nce T shift_right_saturate_narrow(int32x2_t r, int64x2_t a);
template <typename T> nce T shift_right_saturate_narrow(uint8x8_t r, uint16x8_t a);
template <typename T> nce T shift_right_saturate_narrow(uint16x4_t r, uint32x4_t a);
template <typename T> nce T shift_right_saturate_narrow(uint32x2_t r, uint64x2_t a);
template <typename T> nce T convert(float32_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float32_t a);
template <typename T> nce T convert_round_toward_negative_infinity(float32_t a);
template <typename T> nce T convert_round_toward_positive_infinity(float32_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float32_t a);
template <typename T> nce T convert(float64x1_t a);
template <typename T> nce T convert(float64x2_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float64x1_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float64x2_t a);
template <typename T> nce T convert_round_toward_negative_infinity(float64x1_t a);
template <typename T> nce T convert_round_toward_negative_infinity(float64x2_t a);
template <typename T> nce T convert_round_toward_positive_infinity(float64x1_t a);
template <typename T> nce T convert_round_toward_positive_infinity(float64x2_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float64x1_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float64x2_t a);
template <typename T> nce T convert(float64_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float64_t a);
template <typename T> nce T convert_round_toward_negative_infinity(float64_t a);
template <typename T> nce T convert_round_toward_positive_infinity(float64_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float64_t a);
template <typename T> nce T convert(int32_t a);
template <typename T> nce T convert(uint32_t a);
template <typename T> nce T convert(int64x1_t a);
template <typename T> nce T convert(int64x2_t a);
template <typename T> nce T convert(uint64x1_t a);
template <typename T> nce T convert(uint64x2_t a);
template <typename T> nce T convert(int64_t a);
template <typename T> nce T convert(uint64_t a);
template <typename T> nce T reinterpret(int8x8_t a);
template <typename T> nce T reinterpret(int16x4_t a);
template <typename T> nce T reinterpret(int32x2_t a);
template <typename T> nce T reinterpret(float32x2_t a);
template <typename T> nce T reinterpret(float64x1_t a);
template <typename T> nce T reinterpret(uint8x8_t a);
template <typename T> nce T reinterpret(uint16x4_t a);
template <typename T> nce T reinterpret(uint32x2_t a);
template <typename T> nce T reinterpret(poly16x4_t a);
template <typename T> nce T reinterpret(uint64x1_t a);
template <typename T> nce T reinterpret(int64x1_t a);
template <typename T> nce T reinterpret(float16x4_t a);
template <typename T> nce T reinterpret(int8x16_t a);
template <typename T> nce T reinterpret(int16x8_t a);
template <typename T> nce T reinterpret(int32x4_t a);
template <typename T> nce T reinterpret(float32x4_t a);
template <typename T> nce T reinterpret(float64x2_t a);
template <typename T> nce T reinterpret(uint8x16_t a);
template <typename T> nce T reinterpret(uint16x8_t a);
template <typename T> nce T reinterpret(uint32x4_t a);
template <typename T> nce T reinterpret(poly16x8_t a);
template <typename T> nce T reinterpret(int64x2_t a);
template <typename T> nce T reinterpret(float16x8_t a);
template <typename T> nce T reinterpret(poly64x2_t a);
template <typename T> nce T reinterpret(poly128_t a);
template <typename T> nce T create(uint64_t a);
template <typename T> nce T duplicate(float64_t value);
template <typename T> nce T move(float64_t value);
template <typename T> nce T duplicate(float64x1_t vec);
template <typename T> nce T duplicate(int8x16_t vec);
template <typename T> nce T duplicate(int16x8_t vec);
template <typename T> nce T duplicate(int32x4_t vec);
template <typename T> nce T duplicate(int64x2_t vec);
template <typename T> nce T duplicate(uint8x16_t vec);
template <typename T> nce T duplicate(uint16x8_t vec);
template <typename T> nce T duplicate(uint32x4_t vec);
template <typename T> nce T duplicate(uint64x2_t vec);
template <typename T> nce T duplicate(poly64x2_t vec);
template <typename T> nce T duplicate(float32x4_t vec);
template <typename T> nce T duplicate(poly8x16_t vec);
template <typename T> nce T duplicate(poly16x8_t vec);
template <typename T> nce T duplicate(float64x2_t vec);
template <typename T> nce T get(float64x2_t a);
template <typename T> nce T load1(float64_t const *ptr);
template <typename T> nce T load1_duplicate(float64_t const *ptr);
template <typename T> nce T load2(float64_t const *ptr);
template <typename T> nce T load3(float64_t const *ptr);
template <typename T> nce T load3(int8_t const *ptr);
template <typename T> nce T load4(float64_t const *ptr);
template <typename T> nce T load2_duplicate(float64_t const *ptr);
template <typename T> nce T load3_duplicate(float64_t const *ptr);
template <typename T> nce T load4_duplicate(float64_t const *ptr);
template <typename T> nce T load1_x2(float64_t const *ptr);
template <typename T> nce T load1_x3(float64_t const *ptr);
template <typename T> nce T load1_x4(float64_t const *ptr);
template <typename T> nce T store1(float64_t *ptr, float64x1_t val);
template <typename T> nce T store1(float64_t *ptr, float64x2_t val);
template <typename T> nce T store2(int64_t *ptr, int64x2x2_t val);
template <typename T> nce T store2(uint64_t *ptr, uint64x2x2_t val);
template <typename T> nce T store2(poly64_t *ptr, poly64x2x2_t val);
template <typename T> nce T store2(float64_t *ptr, float64x1x2_t val);
template <typename T> nce T store2(float64_t *ptr, float64x2x2_t val);
template <typename T> nce T store3(int64_t *ptr, int64x2x3_t val);
template <typename T> nce T store3(uint64_t *ptr, uint64x2x3_t val);
template <typename T> nce T store3(poly64_t *ptr, poly64x2x3_t val);
template <typename T> nce T store3(float64_t *ptr, float64x1x3_t val);
template <typename T> nce T store3(float64_t *ptr, float64x2x3_t val);
template <typename T> nce T store4(int64_t *ptr, int64x2x4_t val);
template <typename T> nce T store4(uint64_t *ptr, uint64x2x4_t val);
template <typename T> nce T store4(poly64_t *ptr, poly64x2x4_t val);
template <typename T> nce T store4(float64_t *ptr, float64x1x4_t val);
template <typename T> nce T store4(float64_t *ptr, float64x2x4_t val);
template <typename T> nce T convert(int16_t a);
template <typename T> nce T convert(uint16_t a);
template <typename T> nce T convert(float16_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float16_t a);
template <typename T> nce T convert_round_toward_negative_infinity(float16_t a);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float16_t a);
template <typename T> nce T convert_round_toward_positive_infinity(float16_t a);
template <typename T> nce T duplicate(float16x8_t vec);
template <typename T> nce T reinterpret(bfloat16x4_t a);
template <typename T> nce T reinterpret(bfloat16x8_t a);
template <typename T> nce T get_high(float64x2_t a);
template <typename T> nce T get_low(float64x2_t a);



[[gnu::always_inline]] nce uint8x8_t add_saturate(uint8x8_t a, int8x8_t b) { return vsqadd_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_narrow_high_high(uint8x8_t r, uint16x8_t a, uint16x8_t b) { return vaddhn_high_u16(r, a, b); }
[[gnu::always_inline]] nce uint8x16_t add_round_narrow_high_high(uint8x8_t r, uint16x8_t a, uint16x8_t b) { return vraddhn_high_u16(r, a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_narrow_high_high(uint8x8_t r, uint16x8_t a, uint16x8_t b) { return vsubhn_high_u16(r, a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_round_narrow_high_high(uint8x8_t r, uint16x8_t a, uint16x8_t b) { return vrsubhn_high_u16(r, a, b); }
[[gnu::always_inline]] nce uint8_t reduce_add(uint8x8_t a) { return vaddv_u8(a); }
[[gnu::always_inline]] nce uint16_t reduce_add_long(uint8x8_t a) { return vaddlv_u8(a); }
[[gnu::always_inline]] inline uint8_t reduce_max(uint8x8_t a) { return vmaxv_u8(a); }
[[gnu::always_inline]] inline uint8_t reduce_min(uint8x8_t a) { return vminv_u8(a); }
[[gnu::always_inline]] nce uint8x8_t equal_to_zero(uint8x8_t a) { return vceqz_u8(a); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_high(uint8x8_t r, uint16x8_t a) { return vshrn_high_n_u16(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_saturate_narrow_high(uint8x8_t r, uint16x8_t a) { return vqshrn_high_n_u16(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_round_saturate_narrow_high(uint8x8_t r, uint16x8_t a) { return vqrshrn_high_n_u16(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_round_narrow_high(uint8x8_t r, uint16x8_t a) { return vrshrn_high_n_u16(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_saturate_narrow_unsigned_high(uint8x8_t r, int16x8_t a) { return vqshrun_high_n_s16(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_unsigned_saturate_narrow_high(uint8x8_t r, int16x8_t a) { return vqrshrun_high_n_s16(r, a, n); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(uint8x8_t a) { return vreinterpret_f64_u8(a); }
[[gnu::always_inline]] nce uint8x8_t zip2(uint8x8_t a, uint8x8_t b) { return vzip2_u8(a, b); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint8x8_t copy_lane(uint8x8_t a, uint8x8_t b) { return vcopy_lane_u8(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint8x8_t copy_lane(uint8x8_t a, uint8x16_t b) { return vcopy_laneq_u8(a, lane1, b, lane2); }
[[gnu::always_inline]] nce uint8x8_t reverse_bits(uint8x8_t a) { return vrbit_u8(a); }
[[gnu::always_inline]] nce uint8x8_t zip1(uint8x8_t a, uint8x8_t b) { return vzip1_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t unzip1(uint8x8_t a, uint8x8_t b) { return vuzp1_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t unzip2(uint8x8_t a, uint8x8_t b) { return vuzp2_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t transpose_step_1(uint8x8_t a, uint8x8_t b) { return vtrn1_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t transpose_step_2(uint8x8_t a, uint8x8_t b) { return vtrn2_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t table_extend1_saturate(uint8x8_t a, uint8x16_t t, uint8x8_t idx) { return vqtbx1_u8(a, t, idx); }
[[gnu::always_inline]] nce uint8x16_t move_saturate_narrow_high(uint8x8_t r, uint16x8_t a) { return vqmovn_high_u16(r, a); }
[[gnu::always_inline]] nce uint8x16_t move_unsigned_saturate_narrow_high(uint8x8_t r, int16x8_t a) { return vqmovun_high_s16(r, a); }
[[gnu::always_inline]] nce uint8x8_t table_extend2_saturate(uint8x8_t a, uint8x16x2_t t, uint8x8_t idx) { return vqtbx2_u8(a, t, idx); }
[[gnu::always_inline]] nce uint8x8_t table_extend3_saturate(uint8x8_t a, uint8x16x3_t t, uint8x8_t idx) { return vqtbx3_u8(a, t, idx); }
[[gnu::always_inline]] nce uint8x8_t table_extend4_saturate(uint8x8_t a, uint8x16x4_t t, uint8x8_t idx) { return vqtbx4_u8(a, t, idx); }
[[gnu::always_inline]] nce uint16x8_t add_long_high(uint8x16_t a, uint8x16_t b) { return vaddl_high_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply_long_high(uint8x16_t a, uint8x16_t b) { return vmull_high_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_long_high(uint8x16_t a, uint8x16_t b) { return vsubl_high_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_absolute_long_high(uint8x16_t a, uint8x16_t b) { return vabdl_high_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t pairwise_add(uint8x16_t a, uint8x16_t b) { return vpaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t pairwise_max(uint8x16_t a, uint8x16_t b) { return vpmaxq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t pairwise_min(uint8x16_t a, uint8x16_t b) { return vpminq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_saturate(uint8x16_t a, int8x16_t b) { return vsqaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8_t reduce_add(uint8x16_t a) { return vaddvq_u8(a); }
[[gnu::always_inline]] nce uint16_t reduce_add_long(uint8x16_t a) { return vaddlvq_u8(a); }
[[gnu::always_inline]] inline uint8_t reduce_max(uint8x16_t a) { return vmaxvq_u8(a); }
[[gnu::always_inline]] inline uint8_t reduce_min(uint8x16_t a) { return vminvq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t equal_to_zero(uint8x16_t a) { return vceqzq_u8(a); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_left_long_high(uint8x16_t a) { return vshll_high_n_u8(a, n); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(uint8x16_t a) { return vreinterpretq_f64_u8(a); }
[[gnu::always_inline]] nce uint16x8_t move_long_high(uint8x16_t a) { return vmovl_high_u8(a); }
[[gnu::always_inline]] nce uint8x16_t reverse_bits(uint8x16_t a) { return vrbitq_u8(a); }
template <int lane>[[gnu::always_inline]] nce uint8x8_t duplicate_lane(uint8x16_t vec) { return vdup_laneq_u8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16_t duplicate_lane(uint8x16_t vec) { return vdupq_laneq_u8(vec, lane); }
[[gnu::always_inline]] nce uint8x8_t table_lookup1_saturate(uint8x16_t t, uint8x8_t idx) { return vqtbl1_u8(t, idx); }
[[gnu::always_inline]] nce uint8x16_t zip1(uint8x16_t a, uint8x16_t b) { return vzip1q_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t zip2(uint8x16_t a, uint8x16_t b) { return vzip2q_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t unzip1(uint8x16_t a, uint8x16_t b) { return vuzp1q_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t unzip2(uint8x16_t a, uint8x16_t b) { return vuzp2q_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t transpose_step_1(uint8x16_t a, uint8x16_t b) { return vtrn1q_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t transpose_step_2(uint8x16_t a, uint8x16_t b) { return vtrn2q_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t table_lookup1_saturate(uint8x16_t t, uint8x16_t idx) { return vqtbl1q_u8(t, idx); }
[[gnu::always_inline]] nce uint8x16_t table_extend1_saturate(uint8x16_t a, uint8x16_t t, uint8x16_t idx) { return vqtbx1q_u8(a, t, idx); }


template <int lane1, int lane2>[[gnu::always_inline]] nce uint8x16_t copy_lane(uint8x16_t a, uint8x8_t b) { return vcopyq_lane_u8(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint8x16_t copy_lane(uint8x16_t a, uint8x16_t b) { return vcopyq_laneq_u8(a, lane1, b, lane2); }
[[gnu::always_inline]] nce uint8x16_t table_extend2_saturate(uint8x16_t a, uint8x16x2_t t, uint8x16_t idx) { return vqtbx2q_u8(a, t, idx); }
[[gnu::always_inline]] nce uint8x16_t table_extend3_saturate(uint8x16_t a, uint8x16x3_t t, uint8x16_t idx) { return vqtbx3q_u8(a, t, idx); }
[[gnu::always_inline]] nce uint8x16_t table_extend4_saturate(uint8x16_t a, uint8x16x4_t t, uint8x16_t idx) { return vqtbx4q_u8(a, t, idx); }
[[gnu::always_inline]] nce int8x8_t add_saturate(int8x8_t a, uint8x8_t b) { return vuqadd_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_narrow_high_high(int8x8_t r, int16x8_t a, int16x8_t b) { return vaddhn_high_s16(r, a, b); }
[[gnu::always_inline]] nce int8x16_t add_round_narrow_high_high(int8x8_t r, int16x8_t a, int16x8_t b) { return vraddhn_high_s16(r, a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_narrow_high_high(int8x8_t r, int16x8_t a, int16x8_t b) { return vsubhn_high_s16(r, a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_round_narrow_high_high(int8x8_t r, int16x8_t a, int16x8_t b) { return vrsubhn_high_s16(r, a, b); }
[[gnu::always_inline]] nce int8_t reduce_add(int8x8_t a) { return vaddv_s8(a); }
[[gnu::always_inline]] nce int16_t reduce_add_long(int8x8_t a) { return vaddlv_s8(a); }
[[gnu::always_inline]] inline int8_t reduce_max(int8x8_t a) { return vmaxv_s8(a); }
[[gnu::always_inline]] inline int8_t reduce_min(int8x8_t a) { return vminv_s8(a); }
[[gnu::always_inline]] nce uint8x8_t equal_to_zero(int8x8_t a) { return vceqz_s8(a); }
[[gnu::always_inline]] nce uint8x8_t greater_than_or_equal_to_zero(int8x8_t a) { return vcgez_s8(a); }
[[gnu::always_inline]] nce uint8x8_t less_than_or_equal_to_zero(int8x8_t a) { return vclez_s8(a); }
[[gnu::always_inline]] nce uint8x8_t greater_than_zero(int8x8_t a) { return vcgtz_s8(a); }
[[gnu::always_inline]] nce uint8x8_t less_than_zero(int8x8_t a) { return vcltz_s8(a); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_narrow_high(int8x8_t r, int16x8_t a) { return vshrn_high_n_s16(r, a, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_saturate_narrow_high(int8x8_t r, int16x8_t a) { return vqshrn_high_n_s16(r, a, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_round_saturate_narrow_high(int8x8_t r, int16x8_t a) { return vqrshrn_high_n_s16(r, a, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_round_narrow_high(int8x8_t r, int16x8_t a) { return vrshrn_high_n_s16(r, a, n); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(int8x8_t a) { return vreinterpret_f64_s8(a); }
[[gnu::always_inline]] nce int8x8_t reverse_bits(int8x8_t a) { return vrbit_s8(a); }
[[gnu::always_inline]] nce int8x8_t zip1(int8x8_t a, int8x8_t b) { return vzip1_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t zip2(int8x8_t a, int8x8_t b) { return vzip2_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t unzip1(int8x8_t a, int8x8_t b) { return vuzp1_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t unzip2(int8x8_t a, int8x8_t b) { return vuzp2_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t transpose_step_1(int8x8_t a, int8x8_t b) { return vtrn1_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t transpose_step_2(int8x8_t a, int8x8_t b) { return vtrn2_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t table_extend1_saturate(int8x8_t a, int8x16_t t, uint8x8_t idx) { return vqtbx1_s8(a, t, idx); }
[[gnu::always_inline]] nce int8x16_t move_saturate_narrow_high(int8x8_t r, int16x8_t a) { return vqmovn_high_s16(r, a); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int8x8_t copy_lane(int8x8_t a, int8x8_t b) { return vcopy_lane_s8(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int8x8_t copy_lane(int8x8_t a, int8x16_t b) { return vcopy_laneq_s8(a, lane1, b, lane2); }
[[gnu::always_inline]] nce int8x8_t table_extend2_saturate(int8x8_t a, int8x16x2_t t, uint8x8_t idx) { return vqtbx2_s8(a, t, idx); }
[[gnu::always_inline]] nce int8x8_t table_extend3_saturate(int8x8_t a, int8x16x3_t t, uint8x8_t idx) { return vqtbx3_s8(a, t, idx); }
[[gnu::always_inline]] nce int8x8_t table_extend4_saturate(int8x8_t a, int8x16x4_t t, uint8x8_t idx) { return vqtbx4_s8(a, t, idx); }
[[gnu::always_inline]] nce int8x16_t add_saturate(int8x16_t a, uint8x16_t b) { return vuqaddq_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t add_long_high(int8x16_t a, int8x16_t b) { return vaddl_high_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_long_high(int8x16_t a, int8x16_t b) { return vmull_high_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_long_high(int8x16_t a, int8x16_t b) { return vsubl_high_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_absolute_long_high(int8x16_t a, int8x16_t b) { return vabdl_high_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t pairwise_add(int8x16_t a, int8x16_t b) { return vpaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t pairwise_max(int8x16_t a, int8x16_t b) { return vpmaxq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t pairwise_min(int8x16_t a, int8x16_t b) { return vpminq_s8(a, b); }
[[gnu::always_inline]] nce int8_t reduce_add(int8x16_t a) { return vaddvq_s8(a); }
[[gnu::always_inline]] nce int16_t reduce_add_long(int8x16_t a) { return vaddlvq_s8(a); }
[[gnu::always_inline]] inline int8_t reduce_max(int8x16_t a) { return vmaxvq_s8(a); }
[[gnu::always_inline]] inline int8_t reduce_min(int8x16_t a) { return vminvq_s8(a); }
[[gnu::always_inline]] nce uint8x16_t equal_to_zero(int8x16_t a) { return vceqzq_s8(a); }
[[gnu::always_inline]] nce uint8x16_t greater_than_or_equal_to_zero(int8x16_t a) { return vcgezq_s8(a); }
[[gnu::always_inline]] nce uint8x16_t less_than_or_equal_to_zero(int8x16_t a) { return vclezq_s8(a); }
[[gnu::always_inline]] nce uint8x16_t greater_than_zero(int8x16_t a) { return vcgtzq_s8(a); }
[[gnu::always_inline]] nce uint8x16_t less_than_zero(int8x16_t a) { return vcltzq_s8(a); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_left_long_high(int8x16_t a) { return vshll_high_n_s8(a, n); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(int8x16_t a) { return vreinterpretq_f64_s8(a); }
[[gnu::always_inline]] nce int16x8_t move_long_high(int8x16_t a) { return vmovl_high_s8(a); }
[[gnu::always_inline]] nce int8x16_t reverse_bits(int8x16_t a) { return vrbitq_s8(a); }
template <int lane>[[gnu::always_inline]] nce int8x8_t duplicate_lane(int8x16_t vec) { return vdup_laneq_s8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16_t duplicate_lane(int8x16_t vec) { return vdupq_laneq_s8(vec, lane); }
[[gnu::always_inline]] nce int8x8_t table_lookup1_saturate(int8x16_t t, uint8x8_t idx) { return vqtbl1_s8(t, idx); }
[[gnu::always_inline]] nce int8x16_t table_lookup1_saturate(int8x16_t t, uint8x16_t idx) { return vqtbl1q_s8(t, idx); }
[[gnu::always_inline]] nce int8x16_t zip1(int8x16_t a, int8x16_t b) { return vzip1q_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t zip2(int8x16_t a, int8x16_t b) { return vzip2q_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t unzip1(int8x16_t a, int8x16_t b) { return vuzp1q_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t unzip2(int8x16_t a, int8x16_t b) { return vuzp2q_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t transpose_step_1(int8x16_t a, int8x16_t b) { return vtrn1q_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t transpose_step_2(int8x16_t a, int8x16_t b) { return vtrn2q_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t table_extend1_saturate(int8x16_t a, int8x16_t t, uint8x16_t idx) { return vqtbx1q_s8(a, t, idx); }


template <int lane1, int lane2>[[gnu::always_inline]] nce int8x16_t copy_lane(int8x16_t a, int8x8_t b) { return vcopyq_lane_s8(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int8x16_t copy_lane(int8x16_t a, int8x16_t b) { return vcopyq_laneq_s8(a, lane1, b, lane2); }
[[gnu::always_inline]] nce int8x16_t table_extend2_saturate(int8x16_t a, int8x16x2_t t, uint8x16_t idx) { return vqtbx2q_s8(a, t, idx); }
[[gnu::always_inline]] nce int8x16_t table_extend3_saturate(int8x16_t a, int8x16x3_t t, uint8x16_t idx) { return vqtbx3q_s8(a, t, idx); }
[[gnu::always_inline]] nce int8x16_t table_extend4_saturate(int8x16_t a, int8x16x4_t t, uint8x16_t idx) { return vqtbx4q_s8(a, t, idx); }
[[gnu::always_inline]] nce uint16x4_t add_saturate(uint16x4_t a, int16x4_t b) { return vsqadd_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_narrow_high_high(uint16x4_t r, uint32x4_t a, uint32x4_t b) { return vaddhn_high_u32(r, a, b); }
[[gnu::always_inline]] nce uint16x8_t add_round_narrow_high_high(uint16x4_t r, uint32x4_t a, uint32x4_t b) { return vraddhn_high_u32(r, a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_narrow_high_high(uint16x4_t r, uint32x4_t a, uint32x4_t b) { return vsubhn_high_u32(r, a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_round_narrow_high_high(uint16x4_t r, uint32x4_t a, uint32x4_t b) { return vrsubhn_high_u32(r, a, b); }
[[gnu::always_inline]] nce uint16_t reduce_add(uint16x4_t a) { return vaddv_u16(a); }
[[gnu::always_inline]] nce uint32_t reduce_add_long(uint16x4_t a) { return vaddlv_u16(a); }
[[gnu::always_inline]] inline uint16_t reduce_max(uint16x4_t a) { return vmaxv_u16(a); }
[[gnu::always_inline]] inline uint16_t reduce_min(uint16x4_t a) { return vminv_u16(a); }
[[gnu::always_inline]] nce uint16x4_t equal_to_zero(uint16x4_t a) { return vceqz_u16(a); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(uint16x4_t a) { return vreinterpret_f64_u16(a); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t multiply_add_lane(uint16x4_t a, uint16x4_t b, uint16x8_t v) { return vmla_laneq_u16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t multiply_subtract_lane(uint16x4_t a, uint16x4_t b, uint16x8_t v) { return vmls_laneq_u16(a, b, v, lane); }
[[gnu::always_inline]] nce uint16x4_t zip1(uint16x4_t a, uint16x4_t b) { return vzip1_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t zip2(uint16x4_t a, uint16x4_t b) { return vzip2_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t unzip1(uint16x4_t a, uint16x4_t b) { return vuzp1_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t unzip2(uint16x4_t a, uint16x4_t b) { return vuzp2_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t transpose_step_1(uint16x4_t a, uint16x4_t b) { return vtrn1_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t transpose_step_2(uint16x4_t a, uint16x4_t b) { return vtrn2_u16(a, b); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t multiply_lane(uint16x4_t a, uint16x8_t v) { return vmul_laneq_u16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_long_lane(uint16x4_t a, uint16x8_t v) { return vmull_laneq_u16(a, v, lane); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_saturate_narrow_unsigned_high(uint16x4_t r, int32x4_t a) { return vqshrun_high_n_s32(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_unsigned_saturate_narrow_high(uint16x4_t r, int32x4_t a) { return vqrshrun_high_n_s32(r, a, n); }
[[gnu::always_inline]] nce uint16x8_t move_unsigned_saturate_narrow_high(uint16x4_t r, int32x4_t a) { return vqmovun_high_s32(r, a); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_high(uint16x4_t r, uint32x4_t a) { return vshrn_high_n_u32(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_saturate_narrow_high(uint16x4_t r, uint32x4_t a) { return vqshrn_high_n_u32(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_round_saturate_narrow_high(uint16x4_t r, uint32x4_t a) { return vqrshrn_high_n_u32(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_round_narrow_high(uint16x4_t r, uint32x4_t a) { return vrshrn_high_n_u32(r, a, n); }
[[gnu::always_inline]] nce uint16x8_t move_saturate_narrow_high(uint16x4_t r, uint32x4_t a) { return vqmovn_high_u32(r, a); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint16x4_t copy_lane(uint16x4_t a, uint16x4_t b) { return vcopy_lane_u16(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint16x4_t copy_lane(uint16x4_t a, uint16x8_t b) { return vcopy_laneq_u16(a, lane1, b, lane2); }
[[gnu::always_inline]] nce uint16x8_t add_high(uint16x8_t a, uint8x16_t b) { return vaddw_high_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply_add_long_high(uint16x8_t a, uint8x16_t b, uint8x16_t c) { return vmlal_high_u8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t multiply_subtract_long_high(uint16x8_t a, uint8x16_t b, uint8x16_t c) { return vmlsl_high_u8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t subtract_high(uint16x8_t a, uint8x16_t b) { return vsubw_high_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_absolute_add_high(uint16x8_t a, uint8x16_t b, uint8x16_t c) { return vabal_high_u8(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t add_long_high(uint16x8_t a, uint16x8_t b) { return vaddl_high_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_long_high(uint16x8_t a, uint16x8_t b) { return vmull_high_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_long_high(uint16x8_t a, uint16x8_t b) { return vsubl_high_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_absolute_long_high(uint16x8_t a, uint16x8_t b) { return vabdl_high_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t pairwise_add(uint16x8_t a, uint16x8_t b) { return vpaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t pairwise_max(uint16x8_t a, uint16x8_t b) { return vpmaxq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t pairwise_min(uint16x8_t a, uint16x8_t b) { return vpminq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_saturate(uint16x8_t a, int16x8_t b) { return vsqaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16_t reduce_add(uint16x8_t a) { return vaddvq_u16(a); }
[[gnu::always_inline]] nce uint32_t reduce_add_long(uint16x8_t a) { return vaddlvq_u16(a); }
[[gnu::always_inline]] inline uint16_t reduce_max(uint16x8_t a) { return vmaxvq_u16(a); }
[[gnu::always_inline]] inline uint16_t reduce_min(uint16x8_t a) { return vminvq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t equal_to_zero(uint16x8_t a) { return vceqzq_u16(a); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_left_long_high(uint16x8_t a) { return vshll_high_n_u16(a, n); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(uint16x8_t a) { return vreinterpretq_f64_u16(a); }
[[gnu::always_inline]] nce uint32x4_t move_long_high(uint16x8_t a) { return vmovl_high_u16(a); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_long_lane_high(uint16x8_t a, uint16x4_t v) { return vmull_high_lane_u16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t multiply_add_lane(uint16x8_t a, uint16x8_t b, uint16x8_t v) { return vmlaq_laneq_u16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t multiply_subtract_lane(uint16x8_t a, uint16x8_t b, uint16x8_t v) { return vmlsq_laneq_u16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t multiply_lane(uint16x8_t a, uint16x8_t v) { return vmulq_laneq_u16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_long_lane_high(uint16x8_t a, uint16x8_t v) { return vmull_high_laneq_u16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t duplicate_lane(uint16x8_t vec) { return vdup_laneq_u16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t duplicate_lane(uint16x8_t vec) { return vdupq_laneq_u16(vec, lane); }
[[gnu::always_inline]] nce uint16x8_t zip1(uint16x8_t a, uint16x8_t b) { return vzip1q_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t zip2(uint16x8_t a, uint16x8_t b) { return vzip2q_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t unzip1(uint16x8_t a, uint16x8_t b) { return vuzp1q_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t unzip2(uint16x8_t a, uint16x8_t b) { return vuzp2q_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t transpose_step_1(uint16x8_t a, uint16x8_t b) { return vtrn1q_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t transpose_step_2(uint16x8_t a, uint16x8_t b) { return vtrn2q_u16(a, b); }


[[gnu::always_inline]] nce uint32x4_t multiply_long_high(uint16x8_t a, uint16_t b) { return vmull_high_n_u16(a, b); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint16x8_t copy_lane(uint16x8_t a, uint16x4_t b) { return vcopyq_lane_u16(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint16x8_t copy_lane(uint16x8_t a, uint16x8_t b) { return vcopyq_laneq_u16(a, lane1, b, lane2); }
[[gnu::always_inline]] nce int16x4_t add_saturate(int16x4_t a, uint16x4_t b) { return vuqadd_s16(a, b); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_lane(int16x4_t a, int16x8_t v) { return vqdmull_laneq_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_double_saturate_high_lane(int16x4_t a, int16x8_t v) { return vqdmulh_laneq_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_double_round_saturate_high_lane(int16x4_t a, int16x8_t v) { return vqrdmulh_laneq_s16(a, v, lane); }
[[gnu::always_inline]] nce int16x8_t add_narrow_high_high(int16x4_t r, int32x4_t a, int32x4_t b) { return vaddhn_high_s32(r, a, b); }
[[gnu::always_inline]] nce int16x8_t add_round_narrow_high_high(int16x4_t r, int32x4_t a, int32x4_t b) { return vraddhn_high_s32(r, a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_narrow_high_high(int16x4_t r, int32x4_t a, int32x4_t b) { return vsubhn_high_s32(r, a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_round_narrow_high_high(int16x4_t r, int32x4_t a, int32x4_t b) { return vrsubhn_high_s32(r, a, b); }
[[gnu::always_inline]] nce int16_t reduce_add(int16x4_t a) { return vaddv_s16(a); }
[[gnu::always_inline]] nce int32_t reduce_add_long(int16x4_t a) { return vaddlv_s16(a); }
[[gnu::always_inline]] inline int16_t reduce_max(int16x4_t a) { return vmaxv_s16(a); }
[[gnu::always_inline]] inline int16_t reduce_min(int16x4_t a) { return vminv_s16(a); }
[[gnu::always_inline]] nce uint16x4_t equal_to_zero(int16x4_t a) { return vceqz_s16(a); }
[[gnu::always_inline]] nce uint16x4_t greater_than_or_equal_to_zero(int16x4_t a) { return vcgez_s16(a); }
[[gnu::always_inline]] nce uint16x4_t less_than_or_equal_to_zero(int16x4_t a) { return vclez_s16(a); }
[[gnu::always_inline]] nce uint16x4_t greater_than_zero(int16x4_t a) { return vcgtz_s16(a); }
[[gnu::always_inline]] nce uint16x4_t less_than_zero(int16x4_t a) { return vcltz_s16(a); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(int16x4_t a) { return vreinterpret_f64_s16(a); }
[[gnu::always_inline]] nce int16x4_t zip1(int16x4_t a, int16x4_t b) { return vzip1_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t zip2(int16x4_t a, int16x4_t b) { return vzip2_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t unzip1(int16x4_t a, int16x4_t b) { return vuzp1_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t unzip2(int16x4_t a, int16x4_t b) { return vuzp2_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t transpose_step_1(int16x4_t a, int16x4_t b) { return vtrn1_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t transpose_step_2(int16x4_t a, int16x4_t b) { return vtrn2_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t multiply_double_add_round_saturate_high(int16x4_t a, int16x4_t b, int16x4_t c) { return vqrdmlah_s16(a, b, c); }
[[gnu::always_inline]] nce int16x4_t multiply_double_subtract_round_saturate_high(int16x4_t a, int16x4_t b, int16x4_t c) { return vqrdmlsh_s16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_double_add_round_saturate_high_lane(int16x4_t a, int16x4_t b, int16x4_t v) { return vqrdmlah_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_double_subtract_round_saturate_high_lane(int16x4_t a, int16x4_t b, int16x4_t v) { return vqrdmlsh_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_add_lane(int16x4_t a, int16x4_t b, int16x8_t v) { return vmla_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_subtract_lane(int16x4_t a, int16x4_t b, int16x8_t v) { return vmls_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_double_add_round_saturate_high_lane(int16x4_t a, int16x4_t b, int16x8_t v) { return vqrdmlah_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_double_subtract_round_saturate_high_lane(int16x4_t a, int16x4_t b, int16x8_t v) { return vqrdmlsh_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_lane(int16x4_t a, int16x8_t v) { return vmul_laneq_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_long_lane(int16x4_t a, int16x8_t v) { return vmull_laneq_s16(a, v, lane); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_narrow_high(int16x4_t r, int32x4_t a) { return vshrn_high_n_s32(r, a, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_saturate_narrow_high(int16x4_t r, int32x4_t a) { return vqshrn_high_n_s32(r, a, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_round_saturate_narrow_high(int16x4_t r, int32x4_t a) { return vqrshrn_high_n_s32(r, a, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_round_narrow_high(int16x4_t r, int32x4_t a) { return vrshrn_high_n_s32(r, a, n); }
[[gnu::always_inline]] nce int16x8_t move_saturate_narrow_high(int16x4_t r, int32x4_t a) { return vqmovn_high_s32(r, a); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int16x4_t copy_lane(int16x4_t a, int16x4_t b) { return vcopy_lane_s16(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int16x4_t copy_lane(int16x4_t a, int16x8_t b) { return vcopy_laneq_s16(a, lane1, b, lane2); }
[[gnu::always_inline]] nce int16x8_t add_high(int16x8_t a, int8x16_t b) { return vaddw_high_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_add_long_high(int16x8_t a, int8x16_t b, int8x16_t c) { return vmlal_high_s8(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_long_high(int16x8_t a, int8x16_t b, int8x16_t c) { return vmlsl_high_s8(a, b, c); }
[[gnu::always_inline]] nce int16x8_t subtract_high(int16x8_t a, int8x16_t b) { return vsubw_high_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_absolute_add_high(int16x8_t a, int8x16_t b, int8x16_t c) { return vabal_high_s8(a, b, c); }
[[gnu::always_inline]] nce int16x8_t add_saturate(int16x8_t a, uint16x8_t b) { return vuqaddq_s16(a, b); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_lane_high(int16x8_t a, int16x4_t v) { return vqdmull_high_lane_s16(a, v, lane); }
[[gnu::always_inline]] nce int32x4_t add_long_high(int16x8_t a, int16x8_t b) { return vaddl_high_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_high(int16x8_t a, int16x8_t b) { return vqdmull_high_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_long_high(int16x8_t a, int16x8_t b) { return vmull_high_s16(a, b); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_lane_high(int16x8_t a, int16x8_t v) { return vqdmull_high_laneq_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high_lane(int16x8_t a, int16x8_t v) { return vqdmulhq_laneq_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high_lane(int16x8_t a, int16x8_t v) { return vqrdmulhq_laneq_s16(a, v, lane); }
[[gnu::always_inline]] nce int32x4_t subtract_long_high(int16x8_t a, int16x8_t b) { return vsubl_high_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_absolute_long_high(int16x8_t a, int16x8_t b) { return vabdl_high_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t pairwise_add(int16x8_t a, int16x8_t b) { return vpaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t pairwise_max(int16x8_t a, int16x8_t b) { return vpmaxq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t pairwise_min(int16x8_t a, int16x8_t b) { return vpminq_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_high(int16x8_t a, int16_t b) { return vqdmull_high_n_s16(a, b); }
[[gnu::always_inline]] nce int16_t reduce_add(int16x8_t a) { return vaddvq_s16(a); }
[[gnu::always_inline]] nce int32_t reduce_add_long(int16x8_t a) { return vaddlvq_s16(a); }
[[gnu::always_inline]] inline int16_t reduce_max(int16x8_t a) { return vmaxvq_s16(a); }
[[gnu::always_inline]] inline int16_t reduce_min(int16x8_t a) { return vminvq_s16(a); }
[[gnu::always_inline]] nce uint16x8_t equal_to_zero(int16x8_t a) { return vceqzq_s16(a); }
[[gnu::always_inline]] nce uint16x8_t greater_than_or_equal_to_zero(int16x8_t a) { return vcgezq_s16(a); }
[[gnu::always_inline]] nce uint16x8_t less_than_or_equal_to_zero(int16x8_t a) { return vclezq_s16(a); }
[[gnu::always_inline]] nce uint16x8_t greater_than_zero(int16x8_t a) { return vcgtzq_s16(a); }
[[gnu::always_inline]] nce uint16x8_t less_than_zero(int16x8_t a) { return vcltzq_s16(a); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_left_long_high(int16x8_t a) { return vshll_high_n_s16(a, n); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(int16x8_t a) { return vreinterpretq_f64_s16(a); }
[[gnu::always_inline]] nce int32x4_t move_long_high(int16x8_t a) { return vmovl_high_s16(a); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_long_lane_high(int16x8_t a, int16x4_t v) { return vmull_high_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_add_lane(int16x8_t a, int16x8_t b, int16x8_t v) { return vmlaq_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_subtract_lane(int16x8_t a, int16x8_t b, int16x8_t v) { return vmlsq_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_lane(int16x8_t a, int16x8_t v) { return vmulq_laneq_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_long_lane_high(int16x8_t a, int16x8_t v) { return vmull_high_laneq_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t duplicate_lane(int16x8_t vec) { return vdup_laneq_s16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t duplicate_lane(int16x8_t vec) { return vdupq_laneq_s16(vec, lane); }
[[gnu::always_inline]] nce int16x8_t zip1(int16x8_t a, int16x8_t b) { return vzip1q_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t zip2(int16x8_t a, int16x8_t b) { return vzip2q_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t unzip1(int16x8_t a, int16x8_t b) { return vuzp1q_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t unzip2(int16x8_t a, int16x8_t b) { return vuzp2q_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t transpose_step_1(int16x8_t a, int16x8_t b) { return vtrn1q_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t transpose_step_2(int16x8_t a, int16x8_t b) { return vtrn2q_s16(a, b); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_double_add_round_saturate_high_lane(int16x8_t a, int16x8_t b, int16x4_t v) { return vqrdmlahq_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_double_subtract_round_saturate_high_lane(int16x8_t a, int16x8_t b, int16x4_t v) { return vqrdmlshq_lane_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int16x8_t multiply_double_add_round_saturate_high(int16x8_t a, int16x8_t b, int16x8_t c) { return vqrdmlahq_s16(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_double_subtract_round_saturate_high(int16x8_t a, int16x8_t b, int16x8_t c) { return vqrdmlshq_s16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_double_add_round_saturate_high_lane(int16x8_t a, int16x8_t b, int16x8_t v) { return vqrdmlahq_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_double_subtract_round_saturate_high_lane(int16x8_t a, int16x8_t b, int16x8_t v) { return vqrdmlshq_laneq_s16(a, b, v, lane); }


[[gnu::always_inline]] nce int32x4_t multiply_long_high(int16x8_t a, int16_t b) { return vmull_high_n_s16(a, b); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int16x8_t copy_lane(int16x8_t a, int16x4_t b) { return vcopyq_lane_s16(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int16x8_t copy_lane(int16x8_t a, int16x8_t b) { return vcopyq_laneq_s16(a, lane1, b, lane2); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_lane(int32x2_t a, int32x4_t v) { return vqdmull_laneq_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_double_saturate_high_lane(int32x2_t a, int32x4_t v) { return vqdmulh_laneq_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_double_round_saturate_high_lane(int32x2_t a, int32x4_t v) { return vqrdmulh_laneq_s32(a, v, lane); }
[[gnu::always_inline]] nce int32x2_t add_saturate(int32x2_t a, uint32x2_t b) { return vuqadd_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_narrow_high_high(int32x2_t r, int64x2_t a, int64x2_t b) { return vaddhn_high_s64(r, a, b); }
[[gnu::always_inline]] nce int32x4_t add_round_narrow_high_high(int32x2_t r, int64x2_t a, int64x2_t b) { return vraddhn_high_s64(r, a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_narrow_high_high(int32x2_t r, int64x2_t a, int64x2_t b) { return vsubhn_high_s64(r, a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_round_narrow_high_high(int32x2_t r, int64x2_t a, int64x2_t b) { return vrsubhn_high_s64(r, a, b); }
[[gnu::always_inline]] nce int32_t reduce_add(int32x2_t a) { return vaddv_s32(a); }
[[gnu::always_inline]] nce int64_t reduce_add_long(int32x2_t a) { return vaddlv_s32(a); }
[[gnu::always_inline]] inline int32_t reduce_max(int32x2_t a) { return vmaxv_s32(a); }
[[gnu::always_inline]] inline int32_t reduce_min(int32x2_t a) { return vminv_s32(a); }
[[gnu::always_inline]] nce uint32x2_t equal_to_zero(int32x2_t a) { return vceqz_s32(a); }
[[gnu::always_inline]] nce uint32x2_t greater_than_or_equal_to_zero(int32x2_t a) { return vcgez_s32(a); }
[[gnu::always_inline]] nce uint32x2_t less_than_or_equal_to_zero(int32x2_t a) { return vclez_s32(a); }
[[gnu::always_inline]] nce uint32x2_t greater_than_zero(int32x2_t a) { return vcgtz_s32(a); }
[[gnu::always_inline]] nce uint32x2_t less_than_zero(int32x2_t a) { return vcltz_s32(a); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(int32x2_t a) { return vreinterpret_f64_s32(a); }
[[gnu::always_inline]] nce int32x2_t zip1(int32x2_t a, int32x2_t b) { return vzip1_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t zip2(int32x2_t a, int32x2_t b) { return vzip2_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t unzip1(int32x2_t a, int32x2_t b) { return vuzp1_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t unzip2(int32x2_t a, int32x2_t b) { return vuzp2_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t transpose_step_1(int32x2_t a, int32x2_t b) { return vtrn1_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t transpose_step_2(int32x2_t a, int32x2_t b) { return vtrn2_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t multiply_double_add_round_saturate_high(int32x2_t a, int32x2_t b, int32x2_t c) { return vqrdmlah_s32(a, b, c); }
[[gnu::always_inline]] nce int32x2_t multiply_double_subtract_round_saturate_high(int32x2_t a, int32x2_t b, int32x2_t c) { return vqrdmlsh_s32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_double_add_round_saturate_high_lane(int32x2_t a, int32x2_t b, int32x2_t v) { return vqrdmlah_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_double_subtract_round_saturate_high_lane(int32x2_t a, int32x2_t b, int32x2_t v) { return vqrdmlsh_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_add_lane(int32x2_t a, int32x2_t b, int32x4_t v) { return vmla_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_subtract_lane(int32x2_t a, int32x2_t b, int32x4_t v) { return vmls_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_double_add_round_saturate_high_lane(int32x2_t a, int32x2_t b, int32x4_t v) { return vqrdmlah_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_double_subtract_round_saturate_high_lane(int32x2_t a, int32x2_t b, int32x4_t v) { return vqrdmlsh_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_lane(int32x2_t a, int32x4_t v) { return vmul_laneq_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_long_lane(int32x2_t a, int32x4_t v) { return vmull_laneq_s32(a, v, lane); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_narrow_high(int32x2_t r, int64x2_t a) { return vshrn_high_n_s64(r, a, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_saturate_narrow_high(int32x2_t r, int64x2_t a) { return vqshrn_high_n_s64(r, a, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_round_saturate_narrow_high(int32x2_t r, int64x2_t a) { return vqrshrn_high_n_s64(r, a, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_round_narrow_high(int32x2_t r, int64x2_t a) { return vrshrn_high_n_s64(r, a, n); }
[[gnu::always_inline]] nce int32x4_t move_saturate_narrow_high(int32x2_t r, int64x2_t a) { return vqmovn_high_s64(r, a); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int32x2_t copy_lane(int32x2_t a, int32x2_t b) { return vcopy_lane_s32(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int32x2_t copy_lane(int32x2_t a, int32x4_t b) { return vcopy_laneq_s32(a, lane1, b, lane2); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_add_saturate_long_lane(int32x4_t a, int16x4_t b, int16x8_t v) { return vqdmlal_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_saturate_long_lane(int32x4_t a, int16x4_t b, int16x8_t v) { return vqdmlsl_laneq_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t add_high(int32x4_t a, int16x8_t b) { return vaddw_high_s16(a, b); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_add_saturate_long_lane_high(int32x4_t a, int16x8_t b, int16x4_t v) { return vqdmlal_high_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_saturate_long_lane_high(int32x4_t a, int16x8_t b, int16x4_t v) { return vqdmlsl_high_lane_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t multiply_add_long_high(int32x4_t a, int16x8_t b, int16x8_t c) { return vmlal_high_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_long_high(int32x4_t a, int16x8_t b, int16x8_t c) { return vmlsl_high_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_add_saturate_long_high(int32x4_t a, int16x8_t b, int16x8_t c) { return vqdmlal_high_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_saturate_long_high(int32x4_t a, int16x8_t b, int16x8_t c) { return vqdmlsl_high_s16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_add_saturate_long_lane_high(int32x4_t a, int16x8_t b, int16x8_t v) { return vqdmlal_high_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_saturate_long_lane_high(int32x4_t a, int16x8_t b, int16x8_t v) { return vqdmlsl_high_laneq_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t subtract_absolute_add_high(int32x4_t a, int16x8_t b, int16x8_t c) { return vabal_high_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_add_saturate_long_high(int32x4_t a, int16x8_t b, int16_t c) { return vqdmlal_high_n_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_saturate_long_high(int32x4_t a, int16x8_t b, int16_t c) { return vqdmlsl_high_n_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t subtract_high(int32x4_t a, int16x8_t b) { return vsubw_high_s16(a, b); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_lane_high(int32x4_t a, int32x2_t v) { return vqdmull_high_lane_s32(a, v, lane); }
[[gnu::always_inline]] nce int64x2_t add_long_high(int32x4_t a, int32x4_t b) { return vaddl_high_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_high(int32x4_t a, int32x4_t b) { return vqdmull_high_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_long_high(int32x4_t a, int32x4_t b) { return vmull_high_s32(a, b); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_lane_high(int32x4_t a, int32x4_t v) { return vqdmull_high_laneq_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high_lane(int32x4_t a, int32x4_t v) { return vqdmulhq_laneq_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high_lane(int32x4_t a, int32x4_t v) { return vqrdmulhq_laneq_s32(a, v, lane); }
[[gnu::always_inline]] nce int64x2_t subtract_long_high(int32x4_t a, int32x4_t b) { return vsubl_high_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_absolute_long_high(int32x4_t a, int32x4_t b) { return vabdl_high_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t pairwise_add(int32x4_t a, int32x4_t b) { return vpaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t pairwise_max(int32x4_t a, int32x4_t b) { return vpmaxq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t pairwise_min(int32x4_t a, int32x4_t b) { return vpminq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_saturate(int32x4_t a, uint32x4_t b) { return vuqaddq_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_high(int32x4_t a, int32_t b) { return vqdmull_high_n_s32(a, b); }
[[gnu::always_inline]] nce int32_t reduce_add(int32x4_t a) { return vaddvq_s32(a); }
[[gnu::always_inline]] nce int64_t reduce_add_long(int32x4_t a) { return vaddlvq_s32(a); }
[[gnu::always_inline]] inline int32_t reduce_max(int32x4_t a) { return vmaxvq_s32(a); }
[[gnu::always_inline]] inline int32_t reduce_min(int32x4_t a) { return vminvq_s32(a); }
[[gnu::always_inline]] nce uint32x4_t equal_to_zero(int32x4_t a) { return vceqzq_s32(a); }
[[gnu::always_inline]] nce uint32x4_t greater_than_or_equal_to_zero(int32x4_t a) { return vcgezq_s32(a); }
[[gnu::always_inline]] nce uint32x4_t less_than_or_equal_to_zero(int32x4_t a) { return vclezq_s32(a); }
[[gnu::always_inline]] nce uint32x4_t greater_than_zero(int32x4_t a) { return vcgtzq_s32(a); }
[[gnu::always_inline]] nce uint32x4_t less_than_zero(int32x4_t a) { return vcltzq_s32(a); }
template <int n>[[gnu::always_inline]] nce int64x2_t shift_left_long_high(int32x4_t a) { return vshll_high_n_s32(a, n); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(int32x4_t a) { return vreinterpretq_f64_s32(a); }
[[gnu::always_inline]] nce int64x2_t move_long_high(int32x4_t a) { return vmovl_high_s32(a); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_add_long_lane(int32x4_t a, int16x4_t b, int16x8_t v) { return vmlal_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_subtract_long_lane(int32x4_t a, int16x4_t b, int16x8_t v) { return vmlsl_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_add_long_lane_high(int32x4_t a, int16x8_t b, int16x4_t v) { return vmlal_high_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_subtract_long_lane_high(int32x4_t a, int16x8_t b, int16x4_t v) { return vmlsl_high_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_add_long_lane_high(int32x4_t a, int16x8_t b, int16x8_t v) { return vmlal_high_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_subtract_long_lane_high(int32x4_t a, int16x8_t b, int16x8_t v) { return vmlsl_high_laneq_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t multiply_add_long_high(int32x4_t a, int16x8_t b, int16_t c) { return vmlal_high_n_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_long_high(int32x4_t a, int16x8_t b, int16_t c) { return vmlsl_high_n_s16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_long_lane_high(int32x4_t a, int32x2_t v) { return vmull_high_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_add_lane(int32x4_t a, int32x4_t b, int32x4_t v) { return vmlaq_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_subtract_lane(int32x4_t a, int32x4_t b, int32x4_t v) { return vmlsq_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_lane(int32x4_t a, int32x4_t v) { return vmulq_laneq_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_long_lane_high(int32x4_t a, int32x4_t v) { return vmull_high_laneq_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t duplicate_lane(int32x4_t vec) { return vdup_laneq_s32(vec, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t duplicate_lane_quad(int32x4_t vec) { return vdupq_laneq_s32(vec, lane); }
[[gnu::always_inline]] nce int32x4_t zip1(int32x4_t a, int32x4_t b) { return vzip1q_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t zip2(int32x4_t a, int32x4_t b) { return vzip2q_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t unzip1(int32x4_t a, int32x4_t b) { return vuzp1q_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t unzip2(int32x4_t a, int32x4_t b) { return vuzp2q_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t transpose_step_1(int32x4_t a, int32x4_t b) { return vtrn1q_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t transpose_step_2(int32x4_t a, int32x4_t b) { return vtrn2q_s32(a, b); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_add_round_saturate_high_lane(int32x4_t a, int32x4_t b, int32x2_t v) { return vqrdmlahq_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_round_saturate_high_lane(int32x4_t a, int32x4_t b, int32x2_t v) { return vqrdmlshq_lane_s32(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t multiply_double_add_round_saturate_high(int32x4_t a, int32x4_t b, int32x4_t c) { return vqrdmlahq_s32(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_round_saturate_high(int32x4_t a, int32x4_t b, int32x4_t c) { return vqrdmlshq_s32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_add_round_saturate_high_lane(int32x4_t a, int32x4_t b, int32x4_t v) { return vqrdmlahq_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_round_saturate_high_lane(int32x4_t a, int32x4_t b, int32x4_t v) { return vqrdmlshq_laneq_s32(a, b, v, lane); }


[[gnu::always_inline]] nce int64x2_t multiply_long_high(int32x4_t a, int32_t b) { return vmull_high_n_s32(a, b); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int32x4_t copy_lane(int32x4_t a, int32x2_t b) { return vcopyq_lane_s32(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int32x4_t copy_lane(int32x4_t a, int32x4_t b) { return vcopyq_laneq_s32(a, lane1, b, lane2); }
[[gnu::always_inline]] nce uint64x1_t equal(uint64x1_t a, uint64x1_t b) { return vceq_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t add_saturate(uint64x1_t a, int64x1_t b) { return vsqadd_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t equal_to_zero(uint64x1_t a) { return vceqz_u64(a); }
[[gnu::always_inline]] nce uint64x1_t greater_than_or_equal(uint64x1_t a, uint64x1_t b) { return vcge_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t less_than_or_equal(uint64x1_t a, uint64x1_t b) { return vcle_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t greater_than(uint64x1_t a, uint64x1_t b) { return vcgt_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t less_than(uint64x1_t a, uint64x1_t b) { return vclt_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t compare_test_nonzero(uint64x1_t a, uint64x1_t b) { return vtst_u64(a, b); }
template <> [[gnu::always_inline]] nce float64x1_t convert(uint64x1_t a) { return vcvt_f64_u64(a); }
template <int n>[[gnu::always_inline]] nce float64x1_t convert(uint64x1_t a) { return vcvt_n_f64_u64(a, n); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(uint64x1_t a) { return vreinterpret_f64_u64(a); }
[[gnu::always_inline]] nce float64x1_t bitwise_select(uint64x1_t a, float64x1_t b, float64x1_t c) { return vbsl_f64(a, b, c); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint64x1_t copy_lane(uint64x1_t a, uint64x1_t b) { return vcopy_lane_u64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint64x1_t copy_lane(uint64x1_t a, uint64x2_t b) { return vcopy_laneq_u64(a, lane1, b, lane2); }
template <int lane>[[gnu::always_inline]] nce uint64_t duplicate_lane(uint64x1_t vec) { return vdupd_lane_u64(vec, lane); }
[[gnu::always_inline]] nce uint64x2_t pairwise_add(uint64x2_t a, uint64x2_t b) { return vpaddq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract_absolute_add_high(uint64x2_t a, uint32x4_t b, uint32x4_t c) { return vabal_high_u32(a, b, c); }
[[gnu::always_inline]] nce uint64_t pairwise_add(uint64x2_t a) { return vpaddd_u64(a); }
[[gnu::always_inline]] nce uint64_t reduce_add(uint64x2_t a) { return vaddvq_u64(a); }
[[gnu::always_inline]] nce uint64x2_t equal(uint64x2_t a, uint64x2_t b) { return vceqq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t add_high(uint64x2_t a, uint32x4_t b) { return vaddw_high_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t multiply_add_long_high(uint64x2_t a, uint32x4_t b, uint32x4_t c) { return vmlal_high_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long_high(uint64x2_t a, uint32x4_t b, uint32x4_t c) { return vmlsl_high_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t subtract_high(uint64x2_t a, uint32x4_t b) { return vsubw_high_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t add_saturate(uint64x2_t a, int64x2_t b) { return vsqaddq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t equal_to_zero(uint64x2_t a) { return vceqzq_u64(a); }
[[gnu::always_inline]] nce uint64x2_t greater_than_or_equal(uint64x2_t a, uint64x2_t b) { return vcgeq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t less_than_or_equal(uint64x2_t a, uint64x2_t b) { return vcleq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t greater_than(uint64x2_t a, uint64x2_t b) { return vcgtq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t less_than(uint64x2_t a, uint64x2_t b) { return vcltq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t compare_test_nonzero(uint64x2_t a, uint64x2_t b) { return vtstq_u64(a, b); }
template <> [[gnu::always_inline]] nce float64x2_t convert(uint64x2_t a) { return vcvtq_f64_u64(a); }
template <int n>[[gnu::always_inline]] nce float64x2_t convert(uint64x2_t a) { return vcvtq_n_f64_u64(a, n); }
template <int lane>[[gnu::always_inline]] nce uint64x1_t duplicate_lane(uint64x2_t vec) { return vdup_laneq_u64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t duplicate_lane_quad(uint64x2_t vec) { return vdupq_laneq_u64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce uint64_t duplicate_lane(uint64x2_t vec) { return vdupd_laneq_u64(vec, lane); }
[[gnu::always_inline]] nce uint64x2_t zip1(uint64x2_t a, uint64x2_t b) { return vzip1q_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t zip2(uint64x2_t a, uint64x2_t b) { return vzip2q_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t unzip1(uint64x2_t a, uint64x2_t b) { return vuzp1q_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t unzip2(uint64x2_t a, uint64x2_t b) { return vuzp2q_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t transpose_step_1(uint64x2_t a, uint64x2_t b) { return vtrn1q_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t transpose_step_2(uint64x2_t a, uint64x2_t b) { return vtrn2q_u64(a, b); }


template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_add_long_lane(uint64x2_t a, uint32x2_t b, uint32x4_t v) { return vmlal_laneq_u32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long_lane(uint64x2_t a, uint32x2_t b, uint32x4_t v) { return vmlsl_laneq_u32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_add_long_lane_high(uint64x2_t a, uint32x4_t b, uint32x2_t v) { return vmlal_high_lane_u32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long_lane_high(uint64x2_t a, uint32x4_t b, uint32x2_t v) { return vmlsl_high_lane_u32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_add_long_lane_high(uint64x2_t a, uint32x4_t b, uint32x4_t v) { return vmlal_high_laneq_u32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long_lane_high(uint64x2_t a, uint32x4_t b, uint32x4_t v) { return vmlsl_high_laneq_u32(a, b, v, lane); }
[[gnu::always_inline]] nce uint64x2_t multiply_add_long_high(uint64x2_t a, uint32x4_t b, uint32_t c) { return vmlal_high_n_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long_high(uint64x2_t a, uint32x4_t b, uint32_t c) { return vmlsl_high_n_u32(a, b, c); }
[[gnu::always_inline]] nce float64x2_t bitwise_select(uint64x2_t a, float64x2_t b, float64x2_t c) { return vbslq_f64(a, b, c); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint64x2_t copy_lane(uint64x2_t a, uint64x1_t b) { return vcopyq_lane_u64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint64x2_t copy_lane(uint64x2_t a, uint64x2_t b) { return vcopyq_laneq_u64(a, lane1, b, lane2); }
[[gnu::always_inline]] nce uint32x2_t add_saturate(uint32x2_t a, int32x2_t b) { return vsqadd_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_narrow_high_high(uint32x2_t r, uint64x2_t a, uint64x2_t b) { return vaddhn_high_u64(r, a, b); }
[[gnu::always_inline]] nce uint32x4_t add_round_narrow_high_high(uint32x2_t r, uint64x2_t a, uint64x2_t b) { return vraddhn_high_u64(r, a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_narrow_high_high(uint32x2_t r, uint64x2_t a, uint64x2_t b) { return vsubhn_high_u64(r, a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_round_narrow_high_high(uint32x2_t r, uint64x2_t a, uint64x2_t b) { return vrsubhn_high_u64(r, a, b); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint32x2_t a) { return vaddv_u32(a); }
[[gnu::always_inline]] nce uint64_t reduce_add_long(uint32x2_t a) { return vaddlv_u32(a); }
[[gnu::always_inline]] inline uint32_t reduce_max(uint32x2_t a) { return vmaxv_u32(a); }
[[gnu::always_inline]] inline uint32_t reduce_min(uint32x2_t a) { return vminv_u32(a); }
[[gnu::always_inline]] nce uint32x2_t equal_to_zero(uint32x2_t a) { return vceqz_u32(a); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_narrow_high(uint32x2_t r, uint64x2_t a) { return vshrn_high_n_u64(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_saturate_narrow_high(uint32x2_t r, uint64x2_t a) { return vqshrn_high_n_u64(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_round_saturate_narrow_high(uint32x2_t r, uint64x2_t a) { return vqrshrn_high_n_u64(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_round_narrow_high(uint32x2_t r, uint64x2_t a) { return vrshrn_high_n_u64(r, a, n); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(uint32x2_t a) { return vreinterpret_f64_u32(a); }
[[gnu::always_inline]] nce uint32x4_t move_saturate_narrow_high(uint32x2_t r, uint64x2_t a) { return vqmovn_high_u64(r, a); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t multiply_add_lane(uint32x2_t a, uint32x2_t b, uint32x4_t v) { return vmla_laneq_u32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t multiply_subtract_lane(uint32x2_t a, uint32x2_t b, uint32x4_t v) { return vmls_laneq_u32(a, b, v, lane); }
[[gnu::always_inline]] nce uint32x2_t zip1(uint32x2_t a, uint32x2_t b) { return vzip1_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t zip2(uint32x2_t a, uint32x2_t b) { return vzip2_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t unzip1(uint32x2_t a, uint32x2_t b) { return vuzp1_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t unzip2(uint32x2_t a, uint32x2_t b) { return vuzp2_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t transpose_step_1(uint32x2_t a, uint32x2_t b) { return vtrn1_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t transpose_step_2(uint32x2_t a, uint32x2_t b) { return vtrn2_u32(a, b); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t multiply_lane(uint32x2_t a, uint32x4_t v) { return vmul_laneq_u32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_long_lane(uint32x2_t a, uint32x4_t v) { return vmull_laneq_u32(a, v, lane); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_saturate_narrow_unsigned_high(uint32x2_t r, int64x2_t a) { return vqshrun_high_n_s64(r, a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_unsigned_saturate_narrow_high(uint32x2_t r, int64x2_t a) { return vqrshrun_high_n_s64(r, a, n); }
[[gnu::always_inline]] nce uint32x4_t move_unsigned_saturate_narrow_high(uint32x2_t r, int64x2_t a) { return vqmovun_high_s64(r, a); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint32x2_t copy_lane(uint32x2_t a, uint32x2_t b) { return vcopy_lane_u32(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint32x2_t copy_lane(uint32x2_t a, uint32x4_t b) { return vcopy_laneq_u32(a, lane1, b, lane2); }
[[gnu::always_inline]] nce uint32x4_t add_high(uint32x4_t a, uint16x8_t b) { return vaddw_high_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_add_long_high(uint32x4_t a, uint16x8_t b, uint16x8_t c) { return vmlal_high_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_subtract_long_high(uint32x4_t a, uint16x8_t b, uint16x8_t c) { return vmlsl_high_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t subtract_high(uint32x4_t a, uint16x8_t b) { return vsubw_high_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_absolute_add_high(uint32x4_t a, uint16x8_t b, uint16x8_t c) { return vabal_high_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t add_saturate(uint32x4_t a, int32x4_t b) { return vsqaddq_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t add_long_high(uint32x4_t a, uint32x4_t b) { return vaddl_high_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t multiply_long_high(uint32x4_t a, uint32x4_t b) { return vmull_high_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract_long_high(uint32x4_t a, uint32x4_t b) { return vsubl_high_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract_absolute_long_high(uint32x4_t a, uint32x4_t b) { return vabdl_high_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t pairwise_add(uint32x4_t a, uint32x4_t b) { return vpaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t pairwise_max(uint32x4_t a, uint32x4_t b) { return vpmaxq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t pairwise_min(uint32x4_t a, uint32x4_t b) { return vpminq_u32(a, b); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint32x4_t a) { return vaddvq_u32(a); }
[[gnu::always_inline]] nce uint64_t reduce_add_long(uint32x4_t a) { return vaddlvq_u32(a); }
[[gnu::always_inline]] inline uint32_t reduce_max(uint32x4_t a) { return vmaxvq_u32(a); }
[[gnu::always_inline]] inline uint32_t reduce_min(uint32x4_t a) { return vminvq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t equal_to_zero(uint32x4_t a) { return vceqzq_u32(a); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_left_long_high(uint32x4_t a) { return vshll_high_n_u32(a, n); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(uint32x4_t a) { return vreinterpretq_f64_u32(a); }
[[gnu::always_inline]] nce uint64x2_t move_long_high(uint32x4_t a) { return vmovl_high_u32(a); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_add_long_lane(uint32x4_t a, uint16x4_t b, uint16x8_t v) { return vmlal_laneq_u16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_subtract_long_lane(uint32x4_t a, uint16x4_t b, uint16x8_t v) { return vmlsl_laneq_u16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_add_long_lane_high(uint32x4_t a, uint16x8_t b, uint16x4_t v) { return vmlal_high_lane_u16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_subtract_long_lane_high(uint32x4_t a, uint16x8_t b, uint16x4_t v) { return vmlsl_high_lane_u16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_add_long_lane_high(uint32x4_t a, uint16x8_t b, uint16x8_t v) { return vmlal_high_laneq_u16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_subtract_long_lane_high(uint32x4_t a, uint16x8_t b, uint16x8_t v) { return vmlsl_high_laneq_u16(a, b, v, lane); }
[[gnu::always_inline]] nce uint32x4_t multiply_add_long_high(uint32x4_t a, uint16x8_t b, uint16_t c) { return vmlal_high_n_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_subtract_long_high(uint32x4_t a, uint16x8_t b, uint16_t c) { return vmlsl_high_n_u16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_long_lane_high(uint32x4_t a, uint32x2_t v) { return vmull_high_lane_u32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_add_lane(uint32x4_t a, uint32x4_t b, uint32x4_t v) { return vmlaq_laneq_u32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_subtract_lane(uint32x4_t a, uint32x4_t b, uint32x4_t v) { return vmlsq_laneq_u32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_lane(uint32x4_t a, uint32x4_t v) { return vmulq_laneq_u32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_long_lane_high(uint32x4_t a, uint32x4_t v) { return vmull_high_laneq_u32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t duplicate_lane(uint32x4_t vec) { return vdup_laneq_u32(vec, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t duplicate_lane_quad(uint32x4_t vec) { return vdupq_laneq_u32(vec, lane); }
[[gnu::always_inline]] nce uint32x4_t zip1(uint32x4_t a, uint32x4_t b) { return vzip1q_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t zip2(uint32x4_t a, uint32x4_t b) { return vzip2q_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t unzip1(uint32x4_t a, uint32x4_t b) { return vuzp1q_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t unzip2(uint32x4_t a, uint32x4_t b) { return vuzp2q_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t transpose_step_1(uint32x4_t a, uint32x4_t b) { return vtrn1q_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t transpose_step_2(uint32x4_t a, uint32x4_t b) { return vtrn2q_u32(a, b); }




[[gnu::always_inline]] nce uint64x2_t multiply_long_high(uint32x4_t a, uint32_t b) { return vmull_high_n_u32(a, b); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint32x4_t copy_lane(uint32x4_t a, uint32x2_t b) { return vcopyq_lane_u32(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce uint32x4_t copy_lane(uint32x4_t a, uint32x4_t b) { return vcopyq_laneq_u32(a, lane1, b, lane2); }
[[gnu::always_inline]] nce float16x8_t convert_high(float16x4_t r, float32x4_t a) { return vcvt_high_f16_f32(r, a); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(float16x4_t a) { return vreinterpret_f64_f16(a); }
[[gnu::always_inline]] nce float16x4_t round_using_current_mode(float16x4_t a) { return vrndi_f16(a); }
[[gnu::always_inline]] nce float16x4_t square_root(float16x4_t a) { return vsqrt_f16(a); }
[[gnu::always_inline]] nce float16x4_t divide(float16x4_t a, float16x4_t b) { return vdiv_f16(a, b); }
[[gnu::always_inline]] inline float16_t reduce_max(float16x4_t a) { return vmaxv_f16(a); }
[[gnu::always_inline]] inline float16_t reduce_max_strict(float16x4_t a) { return vmaxnmv_f16(a); }
[[gnu::always_inline]] inline float16_t reduce_min(float16x4_t a) { return vminv_f16(a); }
[[gnu::always_inline]] inline float16_t reduce_min_strict(float16x4_t a) { return vminnmv_f16(a); }
[[gnu::always_inline]] nce float16x4_t multiply_extended(float16x4_t a, float16x4_t b) { return vmulx_f16(a, b); }
template <int lane>[[gnu::always_inline]] nce float16x4_t multiply_extended_lane(float16x4_t a, float16x4_t v) { return vmulx_lane_f16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t multiply_add_fused_lane(float16x4_t a, float16x4_t b, float16x4_t v) { return vfma_lane_f16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t multiply_subtract_fused_lane(float16x4_t a, float16x4_t b, float16x4_t v) { return vfms_lane_f16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t multiply_add_fused_lane(float16x4_t a, float16x4_t b, float16x8_t v) { return vfma_laneq_f16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t multiply_subtract_fused_lane(float16x4_t a, float16x4_t b, float16x8_t v) { return vfms_laneq_f16(a, b, v, lane); }
[[gnu::always_inline]] nce float16x4_t multiply_add_fused(float16x4_t a, float16x4_t b, float16_t n) { return vfma_n_f16(a, b, n); }
[[gnu::always_inline]] nce float16x4_t multiply_subtract_fused(float16x4_t a, float16x4_t b, float16_t n) { return vfms_n_f16(a, b, n); }
[[gnu::always_inline]] nce float16x4_t pairwise_max_strict(float16x4_t a, float16x4_t b) { return vpmaxnm_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t pairwise_min_strict(float16x4_t a, float16x4_t b) { return vpminnm_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t zip1(float16x4_t a, float16x4_t b) { return vzip1_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t zip2(float16x4_t a, float16x4_t b) { return vzip2_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t unzip1(float16x4_t a, float16x4_t b) { return vuzp1_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t unzip2(float16x4_t a, float16x4_t b) { return vuzp2_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t transpose_step_1(float16x4_t a, float16x4_t b) { return vtrn1_f16(a, b); }
[[gnu::always_inline]] nce float16x4_t transpose_step_2(float16x4_t a, float16x4_t b) { return vtrn2_f16(a, b); }
template <int lane>[[gnu::always_inline]] nce float16x4_t multiply_lane(float16x4_t a, float16x8_t v) { return vmul_laneq_f16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4_t multiply_extended_lane(float16x4_t a, float16x8_t v) { return vmulx_laneq_f16(a, v, lane); }
[[gnu::always_inline]] nce float16x4_t multiply_extended(float16x4_t a, float16_t n) { return vmulx_n_f16(a, n); }
[[gnu::always_inline]] nce float32x4_t convert_high(float16x8_t a) { return vcvt_high_f32_f16(a); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(float16x8_t a) { return vreinterpretq_f64_f16(a); }
[[gnu::always_inline]] nce float16x8_t round_using_current_mode(float16x8_t a) { return vrndiq_f16(a); }
[[gnu::always_inline]] nce float16x8_t square_root(float16x8_t a) { return vsqrtq_f16(a); }
[[gnu::always_inline]] nce float16x8_t divide(float16x8_t a, float16x8_t b) { return vdivq_f16(a, b); }
[[gnu::always_inline]] inline float16_t reduce_max(float16x8_t a) { return vmaxvq_f16(a); }
[[gnu::always_inline]] inline float16_t reduce_max_strict(float16x8_t a) { return vmaxnmvq_f16(a); }
[[gnu::always_inline]] inline float16_t reduce_min(float16x8_t a) { return vminvq_f16(a); }
[[gnu::always_inline]] inline float16_t reduce_min_strict(float16x8_t a) { return vminnmvq_f16(a); }
template <int lane>[[gnu::always_inline]] nce float16x8_t multiply_extended_lane(float16x8_t a, float16x4_t v) { return vmulxq_lane_f16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t multiply_lane(float16x8_t a, float16x8_t v) { return vmulq_laneq_f16(a, v, lane); }
[[gnu::always_inline]] nce float16x8_t multiply_extended(float16x8_t a, float16x8_t b) { return vmulxq_f16(a, b); }
template <int lane>[[gnu::always_inline]] nce float16x8_t multiply_extended_lane(float16x8_t a, float16x8_t v) { return vmulxq_laneq_f16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t multiply_add_fused_lane(float16x8_t a, float16x8_t b, float16x4_t v) { return vfmaq_lane_f16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t multiply_subtract_fused_lane(float16x8_t a, float16x8_t b, float16x4_t v) { return vfmsq_lane_f16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t multiply_add_fused_lane(float16x8_t a, float16x8_t b, float16x8_t v) { return vfmaq_laneq_f16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t multiply_subtract_fused_lane(float16x8_t a, float16x8_t b, float16x8_t v) { return vfmsq_laneq_f16(a, b, v, lane); }
[[gnu::always_inline]] nce float16x8_t multiply_add_fused(float16x8_t a, float16x8_t b, float16_t n) { return vfmaq_n_f16(a, b, n); }
[[gnu::always_inline]] nce float16x8_t multiply_subtract_fused(float16x8_t a, float16x8_t b, float16_t n) { return vfmsq_n_f16(a, b, n); }
[[gnu::always_inline]] nce float16x8_t pairwise_add(float16x8_t a, float16x8_t b) { return vpaddq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t pairwise_max(float16x8_t a, float16x8_t b) { return vpmaxq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t pairwise_max_strict(float16x8_t a, float16x8_t b) { return vpmaxnmq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t pairwise_min(float16x8_t a, float16x8_t b) { return vpminq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t pairwise_min_strict(float16x8_t a, float16x8_t b) { return vpminnmq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t zip1(float16x8_t a, float16x8_t b) { return vzip1q_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t zip2(float16x8_t a, float16x8_t b) { return vzip2q_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t unzip1(float16x8_t a, float16x8_t b) { return vuzp1q_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t unzip2(float16x8_t a, float16x8_t b) { return vuzp2q_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t transpose_step_1(float16x8_t a, float16x8_t b) { return vtrn1q_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t transpose_step_2(float16x8_t a, float16x8_t b) { return vtrn2q_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply_extended(float16x8_t a, float16_t n) { return vmulxq_n_f16(a, n); }
template <int lane>[[gnu::always_inline]] nce float16x4_t duplicate_lane(float16x8_t vec) { return vdup_laneq_f16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t duplicate_lane(float16x8_t vec) { return vdupq_laneq_f16(vec, lane); }
[[gnu::always_inline]] nce float32x2_t multiply_extended(float32x2_t a, float32x2_t b) { return vmulx_f32(a, b); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_extended_lane(float32x2_t a, float32x2_t v) { return vmulx_lane_f32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_add_fused_lane(float32x2_t a, float32x2_t b, float32x2_t v) { return vfma_lane_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_subtract_fused_lane(float32x2_t a, float32x2_t b, float32x2_t v) { return vfms_lane_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_add_fused_lane(float32x2_t a, float32x2_t b, float32x4_t v) { return vfma_laneq_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_subtract_fused_lane(float32x2_t a, float32x2_t b, float32x4_t v) { return vfms_laneq_f32(a, b, v, lane); }
[[gnu::always_inline]] nce float32x2_t divide(float32x2_t a, float32x2_t b) { return vdiv_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t square_root(float32x2_t a) { return vsqrt_f32(a); }
[[gnu::always_inline]] nce float32_t pairwise_add(float32x2_t a) { return vpadds_f32(a); }
[[gnu::always_inline]] nce float32_t pairwise_max(float32x2_t a) { return vpmaxs_f32(a); }
[[gnu::always_inline]] nce float32_t pairwise_max_strict(float32x2_t a) { return vpmaxnms_f32(a); }
[[gnu::always_inline]] nce float32_t pairwise_min(float32x2_t a) { return vpmins_f32(a); }
[[gnu::always_inline]] nce float32x2_t pairwise_max_strict(float32x2_t a, float32x2_t b) { return vpmaxnm_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t pairwise_min_strict(float32x2_t a, float32x2_t b) { return vpminnm_f32(a, b); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_extended_lane(float32x2_t a, float32x4_t v) { return vmulx_laneq_f32(a, v, lane); }
[[gnu::always_inline]] nce float32_t pairwise_min_strict(float32x2_t a) { return vpminnms_f32(a); }
[[gnu::always_inline]] nce float32_t reduce_add(float32x2_t a) { return vaddv_f32(a); }
[[gnu::always_inline]] inline float32_t reduce_max(float32x2_t a) { return vmaxv_f32(a); }
[[gnu::always_inline]] inline float32_t reduce_min(float32x2_t a) { return vminv_f32(a); }
[[gnu::always_inline]] inline float32_t reduce_max_strict(float32x2_t a) { return vmaxnmv_f32(a); }
[[gnu::always_inline]] inline float32_t reduce_min_strict(float32x2_t a) { return vminnmv_f32(a); }
[[gnu::always_inline]] nce uint32x2_t equal_to_zero(float32x2_t a) { return vceqz_f32(a); }
[[gnu::always_inline]] nce uint32x2_t greater_than_or_equal_to_zero(float32x2_t a) { return vcgez_f32(a); }
[[gnu::always_inline]] nce uint32x2_t less_than_or_equal_to_zero(float32x2_t a) { return vclez_f32(a); }
[[gnu::always_inline]] nce uint32x2_t greater_than_zero(float32x2_t a) { return vcgtz_f32(a); }
[[gnu::always_inline]] nce uint32x2_t less_than_zero(float32x2_t a) { return vcltz_f32(a); }
[[gnu::always_inline]] nce float32x4_t convert_high(float32x2_t r, float64x2_t a) { return vcvt_high_f32_f64(r, a); }
[[gnu::always_inline]] nce float64x2_t convert(float32x2_t a) { return vcvt_f64_f32(a); }
[[gnu::always_inline]] nce float32x4_t convert_round_to_odd_high(float32x2_t r, float64x2_t a) { return vcvtx_high_f32_f64(r, a); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(float32x2_t a) { return vreinterpret_f64_f32(a); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_add_lane(float32x2_t a, float32x2_t b, float32x4_t v) { return vmla_laneq_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_subtract_lane(float32x2_t a, float32x2_t b, float32x4_t v) { return vmls_laneq_f32(a, b, v, lane); }
[[gnu::always_inline]] nce float32x2_t round_to_32bit_integer(float32x2_t a) { return vrnd32z_f32(a); }
[[gnu::always_inline]] nce float32x2_t round_to_64bit_integer(float32x2_t a) { return vrnd64z_f32(a); }
[[gnu::always_inline]] nce float32x2_t round_to_32bit_integer_using_current_mode(float32x2_t a) { return vrnd32x_f32(a); }
[[gnu::always_inline]] nce float32x2_t round_to_64bit_integer_using_current_mode(float32x2_t a) { return vrnd64x_f32(a); }
[[gnu::always_inline]] nce float32x2_t zip1(float32x2_t a, float32x2_t b) { return vzip1_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t zip2(float32x2_t a, float32x2_t b) { return vzip2_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t unzip1(float32x2_t a, float32x2_t b) { return vuzp1_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t unzip2(float32x2_t a, float32x2_t b) { return vuzp2_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t transpose_step_1(float32x2_t a, float32x2_t b) { return vtrn1_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t transpose_step_2(float32x2_t a, float32x2_t b) { return vtrn2_f32(a, b); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_lane(float32x2_t a, float32x4_t v) { return vmul_laneq_f32(a, v, lane); }
template <int lane1, int lane2>[[gnu::always_inline]] nce float32x2_t copy_lane(float32x2_t a, float32x2_t b) { return vcopy_lane_f32(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce float32x2_t copy_lane(float32x2_t a, float32x4_t b) { return vcopy_laneq_f32(a, lane1, b, lane2); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_extended_lane(float32x4_t a, float32x2_t v) { return vmulxq_lane_f32(a, v, lane); }
[[gnu::always_inline]] nce float32x4_t multiply_extended(float32x4_t a, float32x4_t b) { return vmulxq_f32(a, b); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_extended_lane(float32x4_t a, float32x4_t v) { return vmulxq_laneq_f32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_fused_lane(float32x4_t a, float32x4_t b, float32x2_t v) { return vfmaq_lane_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_subtract_fused_lane(float32x4_t a, float32x4_t b, float32x2_t v) { return vfmsq_lane_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_fused_lane(float32x4_t a, float32x4_t b, float32x4_t v) { return vfmaq_laneq_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_subtract_fused_lane(float32x4_t a, float32x4_t b, float32x4_t v) { return vfmsq_laneq_f32(a, b, v, lane); }
[[gnu::always_inline]] nce float32x4_t divide(float32x4_t a, float32x4_t b) { return vdivq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t square_root(float32x4_t a) { return vsqrtq_f32(a); }
[[gnu::always_inline]] nce float32x4_t pairwise_add(float32x4_t a, float32x4_t b) { return vpaddq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t pairwise_max(float32x4_t a, float32x4_t b) { return vpmaxq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t pairwise_min(float32x4_t a, float32x4_t b) { return vpminq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t pairwise_max_strict(float32x4_t a, float32x4_t b) { return vpmaxnmq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t pairwise_min_strict(float32x4_t a, float32x4_t b) { return vpminnmq_f32(a, b); }
[[gnu::always_inline]] nce float32_t reduce_add(float32x4_t a) { return vaddvq_f32(a); }
[[gnu::always_inline]] inline float32_t reduce_max(float32x4_t a) { return vmaxvq_f32(a); }
[[gnu::always_inline]] inline float32_t reduce_min(float32x4_t a) { return vminvq_f32(a); }
[[gnu::always_inline]] inline float32_t reduce_max_strict(float32x4_t a) { return vmaxnmvq_f32(a); }
[[gnu::always_inline]] inline float32_t reduce_min_strict(float32x4_t a) { return vminnmvq_f32(a); }
[[gnu::always_inline]] nce uint32x4_t equal_to_zero(float32x4_t a) { return vceqzq_f32(a); }
[[gnu::always_inline]] nce uint32x4_t greater_than_or_equal_to_zero(float32x4_t a) { return vcgezq_f32(a); }
[[gnu::always_inline]] nce uint32x4_t less_than_or_equal_to_zero(float32x4_t a) { return vclezq_f32(a); }
[[gnu::always_inline]] nce uint32x4_t greater_than_zero(float32x4_t a) { return vcgtzq_f32(a); }
[[gnu::always_inline]] nce uint32x4_t less_than_zero(float32x4_t a) { return vcltzq_f32(a); }
[[gnu::always_inline]] nce float64x2_t convert_high(float32x4_t a) { return vcvt_high_f64_f32(a); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(float32x4_t a) { return vreinterpretq_f64_f32(a); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_lane(float32x4_t a, float32x4_t v) { return vmulq_laneq_f32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t duplicate_lane(float32x4_t vec) { return vdup_laneq_f32(vec, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t duplicate_lane_quad(float32x4_t vec) { return vdupq_laneq_f32(vec, lane); }
[[gnu::always_inline]] nce float32x4_t round_to_32bit_integer(float32x4_t a) { return vrnd32zq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_to_64bit_integer(float32x4_t a) { return vrnd64zq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_to_32bit_integer_using_current_mode(float32x4_t a) { return vrnd32xq_f32(a); }
[[gnu::always_inline]] nce float32x4_t round_to_64bit_integer_using_current_mode(float32x4_t a) { return vrnd64xq_f32(a); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add_lane(float32x4_t a, float32x4_t b, float32x4_t v) { return vmlaq_laneq_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_subtract_lane(float32x4_t a, float32x4_t b, float32x4_t v) { return vmlsq_laneq_f32(a, b, v, lane); }
[[gnu::always_inline]] nce float32x4_t zip1(float32x4_t a, float32x4_t b) { return vzip1q_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t zip2(float32x4_t a, float32x4_t b) { return vzip2q_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t unzip1(float32x4_t a, float32x4_t b) { return vuzp1q_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t unzip2(float32x4_t a, float32x4_t b) { return vuzp2q_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t transpose_step_1(float32x4_t a, float32x4_t b) { return vtrn1q_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t transpose_step_2(float32x4_t a, float32x4_t b) { return vtrn2q_f32(a, b); }
template <int lane1, int lane2>[[gnu::always_inline]] nce float32x4_t copy_lane(float32x4_t a, float32x2_t b) { return vcopyq_lane_f32(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce float32x4_t copy_lane(float32x4_t a, float32x4_t b) { return vcopyq_laneq_f32(a, lane1, b, lane2); }
[[gnu::always_inline]] nce float64x1_t add(float64x1_t a, float64x1_t b) { return vadd_f64(a, b); }
[[gnu::always_inline]] nce float64x1_t multiply(float64x1_t a, float64x1_t b) { return vmul_f64(a, b); }
[[gnu::always_inline]] nce float64x1_t multiply_extended(float64x1_t a, float64x1_t b) { return vmulx_f64(a, b); }
template <int lane>[[gnu::always_inline]] nce float64x1_t multiply_extended_lane(float64x1_t a, float64x1_t v) { return vmulx_lane_f64(a, v, lane); }
[[gnu::always_inline]] nce float64x1_t multiply_add(float64x1_t a, float64x1_t b, float64x1_t c) { return vmla_f64(a, b, c); }
[[gnu::always_inline]] nce float64x1_t multiply_subtract(float64x1_t a, float64x1_t b, float64x1_t c) { return vmls_f64(a, b, c); }
[[gnu::always_inline]] nce float64x1_t multiply_add_fused(float64x1_t a, float64x1_t b, float64x1_t c) { return vfma_f64(a, b, c); }
template <int lane>[[gnu::always_inline]] nce float64x1_t multiply_add_fused_lane(float64x1_t a, float64x1_t b, float64x1_t v) { return vfma_lane_f64(a, b, v, lane); }
[[gnu::always_inline]] nce float64x1_t multiply_subtract_fused(float64x1_t a, float64x1_t b, float64x1_t c) { return vfms_f64(a, b, c); }
template <int lane>[[gnu::always_inline]] nce float64x1_t multiply_subtract_fused_lane(float64x1_t a, float64x1_t b, float64x1_t v) { return vfms_lane_f64(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64x1_t multiply_add_fused_lane(float64x1_t a, float64x1_t b, float64x2_t v) { return vfma_laneq_f64(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64x1_t multiply_subtract_fused_lane(float64x1_t a, float64x1_t b, float64x2_t v) { return vfms_laneq_f64(a, b, v, lane); }
[[gnu::always_inline]] nce float64x1_t divide(float64x1_t a, float64x1_t b) { return vdiv_f64(a, b); }
[[gnu::always_inline]] nce float64x1_t subtract(float64x1_t a, float64x1_t b) { return vsub_f64(a, b); }
[[gnu::always_inline]] nce float64x1_t subtract_absolute(float64x1_t a, float64x1_t b) { return vabd_f64(a, b); }
[[gnu::always_inline]] nce float64x1_t absolute(float64x1_t a) { return vabs_f64(a); }
template <> [[gnu::always_inline]] nce float64x1_t max(float64x1_t a, float64x1_t b) { return vmax_f64(a, b); }
template <> [[gnu::always_inline]] nce float64x1_t min(float64x1_t a, float64x1_t b) { return vmin_f64(a, b); }
template <> [[gnu::always_inline]] nce float64x1_t max_strict(float64x1_t a, float64x1_t b) { return vmaxnm_f64(a, b); }
template <> [[gnu::always_inline]] nce float64x1_t min_strict(float64x1_t a, float64x1_t b) { return vminnm_f64(a, b); }
[[gnu::always_inline]] nce float64x1_t round(float64x1_t a) { return vrnd_f64(a); }
[[gnu::always_inline]] nce float64x1_t round_toward_negative_infinity(float64x1_t a) { return vrndm_f64(a); }
[[gnu::always_inline]] nce float64x1_t round_toward_positive_infinity(float64x1_t a) { return vrndp_f64(a); }
[[gnu::always_inline]] nce float64x1_t round_to_nearest_with_ties_away_from_zero(float64x1_t a) { return vrnda_f64(a); }
[[gnu::always_inline]] nce float64x1_t round_using_current_mode(float64x1_t a) { return vrndi_f64(a); }
[[gnu::always_inline]] nce float64x1_t round_inexact(float64x1_t a) { return vrndx_f64(a); }
[[gnu::always_inline]] nce float64x1_t reciprocal_estimate(float64x1_t a) { return vrecpe_f64(a); }
[[gnu::always_inline]] nce float64x1_t reciprocal_step(float64x1_t a, float64x1_t b) { return vrecps_f64(a, b); }
[[gnu::always_inline]] nce float64x1_t reciprocal_sqrt_estimate(float64x1_t a) { return vrsqrte_f64(a); }
[[gnu::always_inline]] nce float64x1_t reciprocal_sqrt_step(float64x1_t a, float64x1_t b) { return vrsqrts_f64(a, b); }
[[gnu::always_inline]] nce float64x1_t square_root(float64x1_t a) { return vsqrt_f64(a); }
[[gnu::always_inline]] nce uint64x1_t equal(float64x1_t a, float64x1_t b) { return vceq_f64(a, b); }
template <int lane>[[gnu::always_inline]] nce float64x1_t multiply_extended_lane(float64x1_t a, float64x2_t v) { return vmulx_laneq_f64(a, v, lane); }
[[gnu::always_inline]] nce uint64x1_t equal_to_zero(float64x1_t a) { return vceqz_f64(a); }
[[gnu::always_inline]] nce uint64x1_t greater_than_or_equal(float64x1_t a, float64x1_t b) { return vcge_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t greater_than_or_equal_to_zero(float64x1_t a) { return vcgez_f64(a); }
[[gnu::always_inline]] nce uint64x1_t less_than_or_equal(float64x1_t a, float64x1_t b) { return vcle_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t less_than_or_equal_to_zero(float64x1_t a) { return vclez_f64(a); }
[[gnu::always_inline]] nce uint64x1_t greater_than(float64x1_t a, float64x1_t b) { return vcgt_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t greater_than_zero(float64x1_t a) { return vcgtz_f64(a); }
[[gnu::always_inline]] nce uint64x1_t less_than(float64x1_t a, float64x1_t b) { return vclt_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t less_than_zero(float64x1_t a) { return vcltz_f64(a); }
[[gnu::always_inline]] nce uint64x1_t absolute_greater_than_or_equal(float64x1_t a, float64x1_t b) { return vcage_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t absolute_less_than_or_equal(float64x1_t a, float64x1_t b) { return vcale_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t absolute_greater_than(float64x1_t a, float64x1_t b) { return vcagt_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t absolute_less_than(float64x1_t a, float64x1_t b) { return vcalt_f64(a, b); }
template <> [[gnu::always_inline]] nce int64x1_t convert(float64x1_t a) { return vcvt_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64x1_t convert(float64x1_t a) { return vcvt_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64x1_t convert_round_to_nearest_with_ties_to_even(float64x1_t a) { return vcvtn_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64x1_t convert_round_to_nearest_with_ties_to_even(float64x1_t a) { return vcvtn_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64x1_t convert_round_toward_negative_infinity(float64x1_t a) { return vcvtm_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64x1_t convert_round_toward_negative_infinity(float64x1_t a) { return vcvtm_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64x1_t convert_round_toward_positive_infinity(float64x1_t a) { return vcvtp_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64x1_t convert_round_toward_positive_infinity(float64x1_t a) { return vcvtp_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64x1_t convert_round_to_nearest_with_ties_away_from_zero(float64x1_t a) { return vcvta_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64x1_t convert_round_to_nearest_with_ties_away_from_zero(float64x1_t a) { return vcvta_u64_f64(a); }
template <int n>[[gnu::always_inline]] nce int64x1_t convert(float64x1_t a) { return vcvt_n_s64_f64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x1_t convert(float64x1_t a) { return vcvt_n_u64_f64(a, n); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(float64x1_t a) { return vreinterpret_p64_f64(a); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(float64x1_t a) { return vreinterpret_s8_f64(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(float64x1_t a) { return vreinterpret_s16_f64(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(float64x1_t a) { return vreinterpret_s32_f64(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(float64x1_t a) { return vreinterpret_u8_f64(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(float64x1_t a) { return vreinterpret_u16_f64(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(float64x1_t a) { return vreinterpret_u32_f64(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(float64x1_t a) { return vreinterpret_p8_f64(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(float64x1_t a) { return vreinterpret_p16_f64(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(float64x1_t a) { return vreinterpret_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(float64x1_t a) { return vreinterpret_s64_f64(a); }
template <> [[gnu::always_inline]] nce float16x4_t reinterpret(float64x1_t a) { return vreinterpret_f16_f64(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(float64x1_t a) { return vreinterpret_f32_f64(a); }
template <int lane>[[gnu::always_inline]] nce float64x1_t multiply_lane(float64x1_t a, float64x1_t v) { return vmul_lane_f64(a, v, lane); }
[[gnu::always_inline]] nce float64x1_t multiply_add_fused(float64x1_t a, float64x1_t b, float64_t n) { return vfma_n_f64(a, b, n); }
[[gnu::always_inline]] nce float64x1_t multiply_subtract_fused(float64x1_t a, float64x1_t b, float64_t n) { return vfms_n_f64(a, b, n); }
template <int lane>[[gnu::always_inline]] nce float64x1_t multiply_lane(float64x1_t a, float64x2_t v) { return vmul_laneq_f64(a, v, lane); }
[[gnu::always_inline]] nce float64x1_t multiply(float64x1_t a, float64_t b) { return vmul_n_f64(a, b); }
[[gnu::always_inline]] nce float64x1_t negate(float64x1_t a) { return vneg_f64(a); }
template <int lane>[[gnu::always_inline]] nce float64x1_t duplicate_lane(float64x1_t vec) { return vdup_lane_f64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2_t duplicate_lane_quad(float64x1_t vec) { return vdupq_lane_f64(vec, lane); }
[[gnu::always_inline]] nce float64x2_t combine(float64x1_t low, float64x1_t high) { return vcombine_f64(low, high); }
template <int lane>[[gnu::always_inline]] nce float64_t duplicate_lane(float64x1_t vec) { return vdupd_lane_f64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t get_lane(float64x1_t v) { return vget_lane_f64(v, lane); }
template <int n>[[gnu::always_inline]] nce float64x1_t extract(float64x1_t a, float64x1_t b) { return vext_f64(a, b, n); }
template <int lane1, int lane2>[[gnu::always_inline]] nce float64x1_t copy_lane(float64x1_t a, float64x1_t b) { return vcopy_lane_f64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce float64x1_t copy_lane(float64x1_t a, float64x2_t b) { return vcopy_laneq_f64(a, lane1, b, lane2); }
[[gnu::always_inline]] nce float64x1_t round_to_32bit_integer(float64x1_t a) { return vrnd32z_f64(a); }
[[gnu::always_inline]] nce float64x1_t round_to_64bit_integer(float64x1_t a) { return vrnd64z_f64(a); }
[[gnu::always_inline]] nce float64x1_t round_to_32bit_integer_using_current_mode(float64x1_t a) { return vrnd32x_f64(a); }
[[gnu::always_inline]] nce float64x1_t round_to_64bit_integer_using_current_mode(float64x1_t a) { return vrnd64x_f64(a); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(float64x1_t a) { return vreinterpret_bf16_f64(a); }
template <int lane>[[gnu::always_inline]] nce float64x2_t multiply_extended_lane(float64x2_t a, float64x1_t v) { return vmulxq_lane_f64(a, v, lane); }
[[gnu::always_inline]] nce float64x2_t add(float64x2_t a, float64x2_t b) { return vaddq_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t multiply(float64x2_t a, float64x2_t b) { return vmulq_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t multiply_extended(float64x2_t a, float64x2_t b) { return vmulxq_f64(a, b); }
template <int lane>[[gnu::always_inline]] nce float64x2_t multiply_extended_lane(float64x2_t a, float64x2_t v) { return vmulxq_laneq_f64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2_t multiply_add_fused_lane(float64x2_t a, float64x2_t b, float64x1_t v) { return vfmaq_lane_f64(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2_t multiply_subtract_fused_lane(float64x2_t a, float64x2_t b, float64x1_t v) { return vfmsq_lane_f64(a, b, v, lane); }
[[gnu::always_inline]] nce float64x2_t multiply_add(float64x2_t a, float64x2_t b, float64x2_t c) { return vmlaq_f64(a, b, c); }
[[gnu::always_inline]] nce float64x2_t multiply_subtract(float64x2_t a, float64x2_t b, float64x2_t c) { return vmlsq_f64(a, b, c); }
[[gnu::always_inline]] nce float64x2_t multiply_add_fused(float64x2_t a, float64x2_t b, float64x2_t c) { return vfmaq_f64(a, b, c); }
template <int lane>[[gnu::always_inline]] nce float64x2_t multiply_add_fused_lane(float64x2_t a, float64x2_t b, float64x2_t v) { return vfmaq_laneq_f64(a, b, v, lane); }
[[gnu::always_inline]] nce float64x2_t multiply_subtract_fused(float64x2_t a, float64x2_t b, float64x2_t c) { return vfmsq_f64(a, b, c); }
template <int lane>[[gnu::always_inline]] nce float64x2_t multiply_subtract_fused_lane(float64x2_t a, float64x2_t b, float64x2_t v) { return vfmsq_laneq_f64(a, b, v, lane); }
[[gnu::always_inline]] nce float64x2_t divide(float64x2_t a, float64x2_t b) { return vdivq_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t subtract(float64x2_t a, float64x2_t b) { return vsubq_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t subtract_absolute(float64x2_t a, float64x2_t b) { return vabdq_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t absolute(float64x2_t a) { return vabsq_f64(a); }
template <> [[gnu::always_inline]] nce float64x2_t max(float64x2_t a, float64x2_t b) { return vmaxq_f64(a, b); }
template <> [[gnu::always_inline]] nce float64x2_t min(float64x2_t a, float64x2_t b) { return vminq_f64(a, b); }
template <> [[gnu::always_inline]] nce float64x2_t max_strict(float64x2_t a, float64x2_t b) { return vmaxnmq_f64(a, b); }
template <> [[gnu::always_inline]] nce float64x2_t min_strict(float64x2_t a, float64x2_t b) { return vminnmq_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t round(float64x2_t a) { return vrndq_f64(a); }
[[gnu::always_inline]] nce float64x2_t round_toward_negative_infinity(float64x2_t a) { return vrndmq_f64(a); }
[[gnu::always_inline]] nce float64x2_t round_toward_positive_infinity(float64x2_t a) { return vrndpq_f64(a); }
[[gnu::always_inline]] nce float64x2_t round_to_nearest_with_ties_away_from_zero(float64x2_t a) { return vrndaq_f64(a); }
[[gnu::always_inline]] nce float64x2_t round_using_current_mode(float64x2_t a) { return vrndiq_f64(a); }
[[gnu::always_inline]] nce float64x2_t round_inexact(float64x2_t a) { return vrndxq_f64(a); }
[[gnu::always_inline]] nce float64x2_t reciprocal_estimate(float64x2_t a) { return vrecpeq_f64(a); }
[[gnu::always_inline]] nce float64x2_t reciprocal_step(float64x2_t a, float64x2_t b) { return vrecpsq_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t reciprocal_sqrt_estimate(float64x2_t a) { return vrsqrteq_f64(a); }
[[gnu::always_inline]] nce float64x2_t reciprocal_sqrt_step(float64x2_t a, float64x2_t b) { return vrsqrtsq_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t square_root(float64x2_t a) { return vsqrtq_f64(a); }
[[gnu::always_inline]] nce float64x2_t pairwise_add(float64x2_t a, float64x2_t b) { return vpaddq_f64(a, b); }
[[gnu::always_inline]] nce float64_t pairwise_add(float64x2_t a) { return vpaddd_f64(a); }
[[gnu::always_inline]] nce float64x2_t pairwise_max(float64x2_t a, float64x2_t b) { return vpmaxq_f64(a, b); }
[[gnu::always_inline]] nce float64_t pairwise_max(float64x2_t a) { return vpmaxqd_f64(a); }
[[gnu::always_inline]] nce float64_t pairwise_max_strict(float64x2_t a) { return vpmaxnmqd_f64(a); }
[[gnu::always_inline]] nce float64x2_t pairwise_min(float64x2_t a, float64x2_t b) { return vpminq_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t pairwise_max_strict(float64x2_t a, float64x2_t b) { return vpmaxnmq_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t pairwise_min_strict(float64x2_t a, float64x2_t b) { return vpminnmq_f64(a, b); }
[[gnu::always_inline]] nce float64_t pairwise_min(float64x2_t a) { return vpminqd_f64(a); }
[[gnu::always_inline]] nce float64_t pairwise_min_strict(float64x2_t a) { return vpminnmqd_f64(a); }
[[gnu::always_inline]] nce float64_t reduce_add(float64x2_t a) { return vaddvq_f64(a); }
[[gnu::always_inline]] inline float64_t reduce_max(float64x2_t a) { return vmaxvq_f64(a); }
[[gnu::always_inline]] inline float64_t reduce_min(float64x2_t a) { return vminvq_f64(a); }
[[gnu::always_inline]] inline float64_t reduce_max_strict(float64x2_t a) { return vmaxnmvq_f64(a); }
[[gnu::always_inline]] inline float64_t reduce_min_strict(float64x2_t a) { return vminnmvq_f64(a); }
[[gnu::always_inline]] nce uint64x2_t equal(float64x2_t a, float64x2_t b) { return vceqq_f64(a, b); }
[[gnu::always_inline]] nce uint64x2_t equal_to_zero(float64x2_t a) { return vceqzq_f64(a); }
[[gnu::always_inline]] nce uint64x2_t greater_than_or_equal(float64x2_t a, float64x2_t b) { return vcgeq_f64(a, b); }
[[gnu::always_inline]] nce uint64x2_t greater_than_or_equal_to_zero(float64x2_t a) { return vcgezq_f64(a); }
[[gnu::always_inline]] nce uint64x2_t less_than_or_equal(float64x2_t a, float64x2_t b) { return vcleq_f64(a, b); }
[[gnu::always_inline]] nce uint64x2_t less_than_or_equal_to_zero(float64x2_t a) { return vclezq_f64(a); }
[[gnu::always_inline]] nce uint64x2_t greater_than(float64x2_t a, float64x2_t b) { return vcgtq_f64(a, b); }
[[gnu::always_inline]] nce uint64x2_t greater_than_zero(float64x2_t a) { return vcgtzq_f64(a); }
[[gnu::always_inline]] nce uint64x2_t less_than(float64x2_t a, float64x2_t b) { return vcltq_f64(a, b); }
[[gnu::always_inline]] nce uint64x2_t less_than_zero(float64x2_t a) { return vcltzq_f64(a); }
[[gnu::always_inline]] nce uint64x2_t absolute_greater_than_or_equal(float64x2_t a, float64x2_t b) { return vcageq_f64(a, b); }
[[gnu::always_inline]] nce uint64x2_t absolute_less_than_or_equal(float64x2_t a, float64x2_t b) { return vcaleq_f64(a, b); }
[[gnu::always_inline]] nce uint64x2_t absolute_greater_than(float64x2_t a, float64x2_t b) { return vcagtq_f64(a, b); }
[[gnu::always_inline]] nce uint64x2_t absolute_less_than(float64x2_t a, float64x2_t b) { return vcaltq_f64(a, b); }
template <> [[gnu::always_inline]] nce int64x2_t convert(float64x2_t a) { return vcvtq_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64x2_t convert(float64x2_t a) { return vcvtq_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64x2_t convert_round_to_nearest_with_ties_to_even(float64x2_t a) { return vcvtnq_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64x2_t convert_round_to_nearest_with_ties_to_even(float64x2_t a) { return vcvtnq_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64x2_t convert_round_toward_negative_infinity(float64x2_t a) { return vcvtmq_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64x2_t convert_round_toward_negative_infinity(float64x2_t a) { return vcvtmq_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64x2_t convert_round_toward_positive_infinity(float64x2_t a) { return vcvtpq_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64x2_t convert_round_toward_positive_infinity(float64x2_t a) { return vcvtpq_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64x2_t convert_round_to_nearest_with_ties_away_from_zero(float64x2_t a) { return vcvtaq_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64x2_t convert_round_to_nearest_with_ties_away_from_zero(float64x2_t a) { return vcvtaq_u64_f64(a); }
template <int n>[[gnu::always_inline]] nce int64x2_t convert(float64x2_t a) { return vcvtq_n_s64_f64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t convert(float64x2_t a) { return vcvtq_n_u64_f64(a, n); }
template <> [[gnu::always_inline]] nce float32x2_t convert(float64x2_t a) { return vcvt_f32_f64(a); }
[[gnu::always_inline]] nce float32x2_t convert_round_to_odd(float64x2_t a) { return vcvtx_f32_f64(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(float64x2_t a) { return vreinterpretq_p64_f64(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(float64x2_t a) { return vreinterpretq_p128_f64(a); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(float64x2_t a) { return vreinterpretq_s8_f64(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(float64x2_t a) { return vreinterpretq_s16_f64(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(float64x2_t a) { return vreinterpretq_s32_f64(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(float64x2_t a) { return vreinterpretq_u8_f64(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(float64x2_t a) { return vreinterpretq_u16_f64(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(float64x2_t a) { return vreinterpretq_u32_f64(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(float64x2_t a) { return vreinterpretq_p8_f64(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(float64x2_t a) { return vreinterpretq_p16_f64(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(float64x2_t a) { return vreinterpretq_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(float64x2_t a) { return vreinterpretq_s64_f64(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(float64x2_t a) { return vreinterpretq_f16_f64(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(float64x2_t a) { return vreinterpretq_f32_f64(a); }
template <int lane>[[gnu::always_inline]] nce float64x2_t multiply_lane(float64x2_t a, float64x1_t v) { return vmulq_lane_f64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2_t multiply_lane(float64x2_t a, float64x2_t v) { return vmulq_laneq_f64(a, v, lane); }
[[gnu::always_inline]] nce float64x2_t multiply_add_fused(float64x2_t a, float64x2_t b, float64_t n) { return vfmaq_n_f64(a, b, n); }
[[gnu::always_inline]] nce float64x2_t multiply_subtract_fused(float64x2_t a, float64x2_t b, float64_t n) { return vfmsq_n_f64(a, b, n); }
[[gnu::always_inline]] nce float64x2_t multiply(float64x2_t a, float64_t b) { return vmulq_n_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t negate(float64x2_t a) { return vnegq_f64(a); }
template <int lane>[[gnu::always_inline]] nce float64x1_t duplicate_lane(float64x2_t vec) { return vdup_laneq_f64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2_t duplicate_lane_quad(float64x2_t vec) { return vdupq_laneq_f64(vec, lane); }
template <> [[gnu::always_inline]] nce float64x1_t get_high(float64x2_t a) { return vget_high_f64(a); }
template <> [[gnu::always_inline]] nce float64x1_t get_low(float64x2_t a) { return vget_low_f64(a); }
template <int lane>[[gnu::always_inline]] nce float64_t duplicate_lane(float64x2_t vec) { return vdupd_laneq_f64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t get_lane(float64x2_t v) { return vgetq_lane_f64(v, lane); }
template <int n>[[gnu::always_inline]] nce float64x2_t extract(float64x2_t a, float64x2_t b) { return vextq_f64(a, b, n); }
[[gnu::always_inline]] nce float64x2_t zip1(float64x2_t a, float64x2_t b) { return vzip1q_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t zip2(float64x2_t a, float64x2_t b) { return vzip2q_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t unzip1(float64x2_t a, float64x2_t b) { return vuzp1q_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t unzip2(float64x2_t a, float64x2_t b) { return vuzp2q_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t transpose_step_1(float64x2_t a, float64x2_t b) { return vtrn1q_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t transpose_step_2(float64x2_t a, float64x2_t b) { return vtrn2q_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t complex_add_rotate_90(float64x2_t a, float64x2_t b) { return vcaddq_rot90_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t complex_add_rotate_270(float64x2_t a, float64x2_t b) { return vcaddq_rot270_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t complex_multiply_add(float64x2_t r, float64x2_t a, float64x2_t b) { return vcmlaq_f64(r, a, b); }
[[gnu::always_inline]] nce float64x2_t complex_multiply_add_rotate_90(float64x2_t r, float64x2_t a, float64x2_t b) { return vcmlaq_rot90_f64(r, a, b); }
[[gnu::always_inline]] nce float64x2_t complex_multiply_add_rotate_180(float64x2_t r, float64x2_t a, float64x2_t b) { return vcmlaq_rot180_f64(r, a, b); }
[[gnu::always_inline]] nce float64x2_t complex_multiply_add_rotate_270(float64x2_t r, float64x2_t a, float64x2_t b) { return vcmlaq_rot270_f64(r, a, b); }
template <int lane1, int lane2>[[gnu::always_inline]] nce float64x2_t copy_lane(float64x2_t a, float64x1_t b) { return vcopyq_lane_f64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce float64x2_t copy_lane(float64x2_t a, float64x2_t b) { return vcopyq_laneq_f64(a, lane1, b, lane2); }
[[gnu::always_inline]] nce float64x2_t round_to_32bit_integer(float64x2_t a) { return vrnd32zq_f64(a); }
[[gnu::always_inline]] nce float64x2_t round_to_64bit_integer(float64x2_t a) { return vrnd64zq_f64(a); }
[[gnu::always_inline]] nce float64x2_t round_to_32bit_integer_using_current_mode(float64x2_t a) { return vrnd32xq_f64(a); }
[[gnu::always_inline]] nce float64x2_t round_to_64bit_integer_using_current_mode(float64x2_t a) { return vrnd64xq_f64(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(float64x2_t a) { return vreinterpretq_bf16_f64(a); }
[[gnu::always_inline]] nce uint8x8_t equal_to_zero(poly8x8_t a) { return vceqz_p8(a); }
[[gnu::always_inline]] nce float64x1_t reinterpret(poly8x8_t a) { return vreinterpret_f64_p8(a); }
[[gnu::always_inline]] nce poly8x8_t reverse_bits(poly8x8_t a) { return vrbit_p8(a); }
[[gnu::always_inline]] nce poly8x8_t zip1(poly8x8_t a, poly8x8_t b) { return vzip1_p8(a, b); }
[[gnu::always_inline]] nce poly8x8_t zip2(poly8x8_t a, poly8x8_t b) { return vzip2_p8(a, b); }
[[gnu::always_inline]] nce poly8x8_t unzip1(poly8x8_t a, poly8x8_t b) { return vuzp1_p8(a, b); }
[[gnu::always_inline]] nce poly8x8_t unzip2(poly8x8_t a, poly8x8_t b) { return vuzp2_p8(a, b); }
[[gnu::always_inline]] nce poly8x8_t transpose_step_1(poly8x8_t a, poly8x8_t b) { return vtrn1_p8(a, b); }
[[gnu::always_inline]] nce poly8x8_t transpose_step_2(poly8x8_t a, poly8x8_t b) { return vtrn2_p8(a, b); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly8x8_t copy_lane(poly8x8_t a, poly8x8_t b) { return vcopy_lane_p8(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly8x8_t copy_lane(poly8x8_t a, poly8x16_t b) { return vcopy_laneq_p8(a, lane1, b, lane2); }
[[gnu::always_inline]] nce poly8x8_t table_extend1_saturate(poly8x8_t a, poly8x16_t t, uint8x8_t idx) { return vqtbx1_p8(a, t, idx); }
[[gnu::always_inline]] nce poly8x8_t table_extend2_saturate(poly8x8_t a, poly8x16x2_t t, uint8x8_t idx) { return vqtbx2_p8(a, t, idx); }
[[gnu::always_inline]] nce poly8x8_t table_extend3_saturate(poly8x8_t a, poly8x16x3_t t, uint8x8_t idx) { return vqtbx3_p8(a, t, idx); }
[[gnu::always_inline]] nce poly8x8_t table_extend4_saturate(poly8x8_t a, poly8x16x4_t t, uint8x8_t idx) { return vqtbx4_p8(a, t, idx); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(poly16x4_t a) { return vreinterpret_f64_p16(a); }
[[gnu::always_inline]] nce poly16x4_t zip1(poly16x4_t a, poly16x4_t b) { return vzip1_p16(a, b); }
[[gnu::always_inline]] nce poly16x4_t zip2(poly16x4_t a, poly16x4_t b) { return vzip2_p16(a, b); }
[[gnu::always_inline]] nce poly16x4_t unzip1(poly16x4_t a, poly16x4_t b) { return vuzp1_p16(a, b); }
[[gnu::always_inline]] nce poly16x4_t unzip2(poly16x4_t a, poly16x4_t b) { return vuzp2_p16(a, b); }
[[gnu::always_inline]] nce poly16x4_t transpose_step_1(poly16x4_t a, poly16x4_t b) { return vtrn1_p16(a, b); }
[[gnu::always_inline]] nce poly16x4_t transpose_step_2(poly16x4_t a, poly16x4_t b) { return vtrn2_p16(a, b); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly16x4_t copy_lane(poly16x4_t a, poly16x4_t b) { return vcopy_lane_p16(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly16x4_t copy_lane(poly16x4_t a, poly16x8_t b) { return vcopy_laneq_p16(a, lane1, b, lane2); }
[[gnu::always_inline]] nce int64_t add(int64_t a, int64_t b) { return vaddd_s64(a, b); }
[[gnu::always_inline]] nce uint64_t add(uint64_t a, uint64_t b) { return vaddd_u64(a, b); }
[[gnu::always_inline]] nce int64x2_t add_high(int64x2_t a, int32x4_t b) { return vaddw_high_s32(a, b); }
[[gnu::always_inline]] nce int8_t add_saturate(int8_t a, int8_t b) { return vqaddb_s8(a, b); }
[[gnu::always_inline]] nce int16_t add_saturate(int16_t a, int16_t b) { return vqaddh_s16(a, b); }
[[gnu::always_inline]] nce int32_t add_saturate(int32_t a, int32_t b) { return vqadds_s32(a, b); }
[[gnu::always_inline]] nce int64_t add_saturate(int64_t a, int64_t b) { return vqaddd_s64(a, b); }
[[gnu::always_inline]] nce uint8_t add_saturate(uint8_t a, uint8_t b) { return vqaddb_u8(a, b); }
[[gnu::always_inline]] nce uint16_t add_saturate(uint16_t a, uint16_t b) { return vqaddh_u16(a, b); }
[[gnu::always_inline]] nce uint32_t add_saturate(uint32_t a, uint32_t b) { return vqadds_u32(a, b); }
[[gnu::always_inline]] nce uint64_t add_saturate(uint64_t a, uint64_t b) { return vqaddd_u64(a, b); }
[[gnu::always_inline]] nce int64x1_t add_saturate(int64x1_t a, uint64x1_t b) { return vuqadd_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t add_saturate(int64x2_t a, uint64x2_t b) { return vuqaddq_s64(a, b); }
[[gnu::always_inline]] nce int8_t add_saturate(int8_t a, uint8_t b) { return vuqaddb_s8(a, b); }
[[gnu::always_inline]] nce int16_t add_saturate(int16_t a, uint16_t b) { return vuqaddh_s16(a, b); }
[[gnu::always_inline]] nce int32_t add_saturate(int32_t a, uint32_t b) { return vuqadds_s32(a, b); }
[[gnu::always_inline]] nce int64_t add_saturate(int64_t a, uint64_t b) { return vuqaddd_s64(a, b); }
[[gnu::always_inline]] nce uint8_t add_saturate(uint8_t a, int8_t b) { return vsqaddb_u8(a, b); }
[[gnu::always_inline]] nce uint16_t add_saturate(uint16_t a, int16_t b) { return vsqaddh_u16(a, b); }
[[gnu::always_inline]] nce uint32_t add_saturate(uint32_t a, int32_t b) { return vsqadds_u32(a, b); }
[[gnu::always_inline]] nce uint64_t add_saturate(uint64_t a, int64_t b) { return vsqaddd_u64(a, b); }
[[gnu::always_inline]] nce float32_t multiply_extended(float32_t a, float32_t b) { return vmulxs_f32(a, b); }
[[gnu::always_inline]] nce float64_t multiply_extended(float64_t a, float64_t b) { return vmulxd_f64(a, b); }
template <int lane>[[gnu::always_inline]] nce float32_t multiply_extended_lane(float32_t a, float32x2_t v) { return vmulxs_lane_f32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t multiply_extended_lane(float64_t a, float64x1_t v) { return vmulxd_lane_f64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32_t multiply_extended_lane(float32_t a, float32x4_t v) { return vmulxs_laneq_f32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t multiply_extended_lane(float64_t a, float64x2_t v) { return vmulxd_laneq_f64(a, v, lane); }
[[gnu::always_inline]] nce int64x2_t multiply_add_long_high(int64x2_t a, int32x4_t b, int32x4_t c) { return vmlal_high_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_subtract_long_high(int64x2_t a, int32x4_t b, int32x4_t c) { return vmlsl_high_s32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce float32_t multiply_add_fused_lane(float32_t a, float32_t b, float32x2_t v) { return vfmas_lane_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t multiply_add_fused_lane(float64_t a, float64_t b, float64x1_t v) { return vfmad_lane_f64(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32_t multiply_add_fused_lane(float32_t a, float32_t b, float32x4_t v) { return vfmas_laneq_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t multiply_add_fused_lane(float64_t a, float64_t b, float64x2_t v) { return vfmad_laneq_f64(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32_t multiply_subtract_fused_lane(float32_t a, float32_t b, float32x2_t v) { return vfmss_lane_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t multiply_subtract_fused_lane(float64_t a, float64_t b, float64x1_t v) { return vfmsd_lane_f64(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32_t multiply_subtract_fused_lane(float32_t a, float32_t b, float32x4_t v) { return vfmss_laneq_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t multiply_subtract_fused_lane(float64_t a, float64_t b, float64x2_t v) { return vfmsd_laneq_f64(a, b, v, lane); }
[[gnu::always_inline]] nce int16_t multiply_double_saturate_high(int16_t a, int16_t b) { return vqdmulhh_s16(a, b); }
[[gnu::always_inline]] nce int32_t multiply_double_saturate_high(int32_t a, int32_t b) { return vqdmulhs_s32(a, b); }
[[gnu::always_inline]] nce int16_t multiply_double_round_saturate_high(int16_t a, int16_t b) { return vqrdmulhh_s16(a, b); }
[[gnu::always_inline]] nce int32_t multiply_double_round_saturate_high(int32_t a, int32_t b) { return vqrdmulhs_s32(a, b); }
[[gnu::always_inline]] nce int32_t multiply_double_saturate_long(int16_t a, int16_t b) { return vqdmullh_s16(a, b); }
[[gnu::always_inline]] nce int64_t multiply_double_saturate_long(int32_t a, int32_t b) { return vqdmulls_s32(a, b); }
[[gnu::always_inline]] nce int32_t multiply_double_add_saturate_long(int32_t a, int16_t b, int16_t c) { return vqdmlalh_s16(a, b, c); }
[[gnu::always_inline]] nce int64_t multiply_double_add_saturate_long(int64_t a, int32_t b, int32_t c) { return vqdmlals_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long_high(int64x2_t a, int32x4_t b, int32x4_t c) { return vqdmlal_high_s32(a, b, c); }
[[gnu::always_inline]] nce int32_t multiply_double_subtract_saturate_long(int32_t a, int16_t b, int16_t c) { return vqdmlslh_s16(a, b, c); }
[[gnu::always_inline]] nce int64_t multiply_double_subtract_saturate_long(int64_t a, int32_t b, int32_t c) { return vqdmlsls_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long_high(int64x2_t a, int32x4_t b, int32x4_t c) { return vqdmlsl_high_s32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_add_saturate_long_lane(int32_t a, int16_t b, int16x4_t v) { return vqdmlalh_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64_t multiply_double_add_saturate_long_lane(int64_t a, int32_t b, int32x2_t v) { return vqdmlals_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long_lane_high(int64x2_t a, int32x4_t b, int32x2_t v) { return vqdmlal_high_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long_lane(int64x2_t a, int32x2_t b, int32x4_t v) { return vqdmlal_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_add_saturate_long_lane(int32_t a, int16_t b, int16x8_t v) { return vqdmlalh_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64_t multiply_double_add_saturate_long_lane(int64_t a, int32_t b, int32x4_t v) { return vqdmlals_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long_lane_high(int64x2_t a, int32x4_t b, int32x4_t v) { return vqdmlal_high_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_subtract_saturate_long_lane(int32_t a, int16_t b, int16x4_t v) { return vqdmlslh_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64_t multiply_double_subtract_saturate_long_lane(int64_t a, int32_t b, int32x2_t v) { return vqdmlsls_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long_lane_high(int64x2_t a, int32x4_t b, int32x2_t v) { return vqdmlsl_high_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long_lane(int64x2_t a, int32x2_t b, int32x4_t v) { return vqdmlsl_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_subtract_saturate_long_lane(int32_t a, int16_t b, int16x8_t v) { return vqdmlslh_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64_t multiply_double_subtract_saturate_long_lane(int64_t a, int32_t b, int32x4_t v) { return vqdmlsls_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long_lane_high(int64x2_t a, int32x4_t b, int32x4_t v) { return vqdmlsl_high_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_saturate_long_lane(int16_t a, int16x4_t v) { return vqdmullh_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64_t multiply_double_saturate_long_lane(int32_t a, int32x2_t v) { return vqdmulls_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_saturate_long_lane(int16_t a, int16x8_t v) { return vqdmullh_laneq_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64_t multiply_double_saturate_long_lane(int32_t a, int32x4_t v) { return vqdmulls_laneq_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16_t multiply_double_saturate_high_lane(int16_t a, int16x4_t v) { return vqdmulhh_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_saturate_high_lane(int32_t a, int32x2_t v) { return vqdmulhs_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16_t multiply_double_saturate_high_lane(int16_t a, int16x8_t v) { return vqdmulhh_laneq_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_saturate_high_lane(int32_t a, int32x4_t v) { return vqdmulhs_laneq_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16_t multiply_double_round_saturate_high_lane(int16_t a, int16x4_t v) { return vqrdmulhh_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_round_saturate_high_lane(int32_t a, int32x2_t v) { return vqrdmulhs_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16_t multiply_double_round_saturate_high_lane(int16_t a, int16x8_t v) { return vqrdmulhh_laneq_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_round_saturate_high_lane(int32_t a, int32x4_t v) { return vqrdmulhs_laneq_s32(a, v, lane); }
[[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long_high(int64x2_t a, int32x4_t b, int32_t c) { return vqdmlal_high_n_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long_high(int64x2_t a, int32x4_t b, int32_t c) { return vqdmlsl_high_n_s32(a, b, c); }
[[gnu::always_inline]] nce poly16x8_t multiply_long_high(poly8x16_t a, poly8x16_t b) { return vmull_high_p8(a, b); }
[[gnu::always_inline]] nce int64_t subtract(int64_t a, int64_t b) { return vsubd_s64(a, b); }
[[gnu::always_inline]] nce uint64_t subtract(uint64_t a, uint64_t b) { return vsubd_u64(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_high(int64x2_t a, int32x4_t b) { return vsubw_high_s32(a, b); }
[[gnu::always_inline]] nce int8_t subtract_saturate(int8_t a, int8_t b) { return vqsubb_s8(a, b); }
[[gnu::always_inline]] nce int16_t subtract_saturate(int16_t a, int16_t b) { return vqsubh_s16(a, b); }
[[gnu::always_inline]] nce int32_t subtract_saturate(int32_t a, int32_t b) { return vqsubs_s32(a, b); }
[[gnu::always_inline]] nce int64_t subtract_saturate(int64_t a, int64_t b) { return vqsubd_s64(a, b); }
[[gnu::always_inline]] nce uint8_t subtract_saturate(uint8_t a, uint8_t b) { return vqsubb_u8(a, b); }
[[gnu::always_inline]] nce uint16_t subtract_saturate(uint16_t a, uint16_t b) { return vqsubh_u16(a, b); }
[[gnu::always_inline]] nce uint32_t subtract_saturate(uint32_t a, uint32_t b) { return vqsubs_u32(a, b); }
[[gnu::always_inline]] nce uint64_t subtract_saturate(uint64_t a, uint64_t b) { return vqsubd_u64(a, b); }
[[gnu::always_inline]] nce float32_t absolute_difference(float32_t a, float32_t b) { return vabds_f32(a, b); }
[[gnu::always_inline]] nce float64_t absolute_difference(float64_t a, float64_t b) { return vabdd_f64(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_absolute_add_high(int64x2_t a, int32x4_t b, int32x4_t c) { return vabal_high_s32(a, b, c); }
[[gnu::always_inline]] nce int64x1_t absolute(int64x1_t a) { return vabs_s64(a); }
[[gnu::always_inline]] nce int64_t absolute(int64_t a) { return vabsd_s64(a); }
[[gnu::always_inline]] nce int64x2_t absolute(int64x2_t a) { return vabsq_s64(a); }
[[gnu::always_inline]] nce int64x1_t absolute_saturate(int64x1_t a) { return vqabs_s64(a); }
[[gnu::always_inline]] nce int64x2_t absolute_saturate(int64x2_t a) { return vqabsq_s64(a); }
[[gnu::always_inline]] nce int8_t absolute_saturate(int8_t a) { return vqabsb_s8(a); }
[[gnu::always_inline]] nce int16_t absolute_saturate(int16_t a) { return vqabsh_s16(a); }
[[gnu::always_inline]] nce int32_t absolute_saturate(int32_t a) { return vqabss_s32(a); }
[[gnu::always_inline]] nce int64_t absolute_saturate(int64_t a) { return vqabsd_s64(a); }
[[gnu::always_inline]] nce float32_t reciprocal_estimate(float32_t a) { return vrecpes_f32(a); }
[[gnu::always_inline]] nce float64_t reciprocal_estimate(float64_t a) { return vrecped_f64(a); }
[[gnu::always_inline]] nce float32_t reciprocal_step(float32_t a, float32_t b) { return vrecpss_f32(a, b); }
[[gnu::always_inline]] nce float64_t reciprocal_step(float64_t a, float64_t b) { return vrecpsd_f64(a, b); }
[[gnu::always_inline]] nce float32_t reciprocal_sqrt_estimate(float32_t a) { return vrsqrtes_f32(a); }
[[gnu::always_inline]] nce float64_t reciprocal_sqrt_estimate(float64_t a) { return vrsqrted_f64(a); }
[[gnu::always_inline]] nce float32_t reciprocal_sqrt_step(float32_t a, float32_t b) { return vrsqrtss_f32(a, b); }
[[gnu::always_inline]] nce float64_t reciprocal_sqrt_step(float64_t a, float64_t b) { return vrsqrtsd_f64(a, b); }
[[gnu::always_inline]] nce float32_t reciprocal_exponent(float32_t a) { return vrecpxs_f32(a); }
[[gnu::always_inline]] nce float64_t reciprocal_exponent(float64_t a) { return vrecpxd_f64(a); }
[[gnu::always_inline]] nce int64x2_t pairwise_add(int64x2_t a, int64x2_t b) { return vpaddq_s64(a, b); }
[[gnu::always_inline]] nce int64_t pairwise_add(int64x2_t a) { return vpaddd_s64(a); }
[[gnu::always_inline]] nce int64_t reduce_add(int64x2_t a) { return vaddvq_s64(a); }
[[gnu::always_inline]] nce uint64x1_t equal(int64x1_t a, int64x1_t b) { return vceq_s64(a, b); }
[[gnu::always_inline]] nce uint64x2_t equal(int64x2_t a, int64x2_t b) { return vceqq_s64(a, b); }
[[gnu::always_inline]] nce uint64_t equal(int64_t a, int64_t b) { return vceqd_s64(a, b); }
[[gnu::always_inline]] nce uint64_t equal(uint64_t a, uint64_t b) { return vceqd_u64(a, b); }
[[gnu::always_inline]] nce uint32_t equal(float32_t a, float32_t b) { return vceqs_f32(a, b); }
[[gnu::always_inline]] nce uint64_t equal(float64_t a, float64_t b) { return vceqd_f64(a, b); }
[[gnu::always_inline]] nce uint8x16_t equal_to_zero(poly8x16_t a) { return vceqzq_p8(a); }
[[gnu::always_inline]] nce uint64x1_t equal_to_zero(int64x1_t a) { return vceqz_s64(a); }
[[gnu::always_inline]] nce uint64x2_t equal_to_zero(int64x2_t a) { return vceqzq_s64(a); }
[[gnu::always_inline]] nce uint64_t equal_to_zero(int64_t a) { return vceqzd_s64(a); }
[[gnu::always_inline]] nce uint64_t equal_to_zero(uint64_t a) { return vceqzd_u64(a); }
[[gnu::always_inline]] nce uint32_t equal_to_zero(float32_t a) { return vceqzs_f32(a); }
[[gnu::always_inline]] nce uint64_t equal_to_zero(float64_t a) { return vceqzd_f64(a); }
[[gnu::always_inline]] nce uint64x1_t greater_than_or_equal(int64x1_t a, int64x1_t b) { return vcge_s64(a, b); }
[[gnu::always_inline]] nce uint64x2_t greater_than_or_equal(int64x2_t a, int64x2_t b) { return vcgeq_s64(a, b); }
[[gnu::always_inline]] nce uint64_t greater_than_or_equal(int64_t a, int64_t b) { return vcged_s64(a, b); }
[[gnu::always_inline]] nce uint64_t greater_than_or_equal(uint64_t a, uint64_t b) { return vcged_u64(a, b); }
[[gnu::always_inline]] nce uint32_t greater_than_or_equal(float32_t a, float32_t b) { return vcges_f32(a, b); }
[[gnu::always_inline]] nce uint64_t greater_than_or_equal(float64_t a, float64_t b) { return vcged_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t greater_than_or_equal_to_zero(int64x1_t a) { return vcgez_s64(a); }
[[gnu::always_inline]] nce uint64x2_t greater_than_or_equal_to_zero(int64x2_t a) { return vcgezq_s64(a); }
[[gnu::always_inline]] nce uint64_t greater_than_or_equal_to_zero(int64_t a) { return vcgezd_s64(a); }
[[gnu::always_inline]] nce uint32_t greater_than_or_equal_to_zero(float32_t a) { return vcgezs_f32(a); }
[[gnu::always_inline]] nce uint64_t greater_than_or_equal_to_zero(float64_t a) { return vcgezd_f64(a); }
[[gnu::always_inline]] nce uint64x1_t less_than_or_equal(int64x1_t a, int64x1_t b) { return vcle_s64(a, b); }
[[gnu::always_inline]] nce uint64x2_t less_than_or_equal(int64x2_t a, int64x2_t b) { return vcleq_s64(a, b); }
[[gnu::always_inline]] nce uint64_t less_than_or_equal(int64_t a, int64_t b) { return vcled_s64(a, b); }
[[gnu::always_inline]] nce uint64_t less_than_or_equal(uint64_t a, uint64_t b) { return vcled_u64(a, b); }
[[gnu::always_inline]] nce uint32_t less_than_or_equal(float32_t a, float32_t b) { return vcles_f32(a, b); }
[[gnu::always_inline]] nce uint64_t less_than_or_equal(float64_t a, float64_t b) { return vcled_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t less_than_or_equal_to_zero(int64x1_t a) { return vclez_s64(a); }
[[gnu::always_inline]] nce uint64x2_t less_than_or_equal_to_zero(int64x2_t a) { return vclezq_s64(a); }
[[gnu::always_inline]] nce uint64_t less_than_or_equal_to_zero(int64_t a) { return vclezd_s64(a); }
[[gnu::always_inline]] nce uint32_t less_than_or_equal_to_zero(float32_t a) { return vclezs_f32(a); }
[[gnu::always_inline]] nce uint64_t less_than_or_equal_to_zero(float64_t a) { return vclezd_f64(a); }
[[gnu::always_inline]] nce uint64x1_t greater_than(int64x1_t a, int64x1_t b) { return vcgt_s64(a, b); }
[[gnu::always_inline]] nce uint64x2_t greater_than(int64x2_t a, int64x2_t b) { return vcgtq_s64(a, b); }
[[gnu::always_inline]] nce uint64_t greater_than(int64_t a, int64_t b) { return vcgtd_s64(a, b); }
[[gnu::always_inline]] nce uint64_t greater_than(uint64_t a, uint64_t b) { return vcgtd_u64(a, b); }
[[gnu::always_inline]] nce uint32_t greater_than(float32_t a, float32_t b) { return vcgts_f32(a, b); }
[[gnu::always_inline]] nce uint64_t greater_than(float64_t a, float64_t b) { return vcgtd_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t greater_than_zero(int64x1_t a) { return vcgtz_s64(a); }
[[gnu::always_inline]] nce uint64x2_t greater_than_zero(int64x2_t a) { return vcgtzq_s64(a); }
[[gnu::always_inline]] nce uint64_t greater_than_zero(int64_t a) { return vcgtzd_s64(a); }
[[gnu::always_inline]] nce uint32_t greater_than_zero(float32_t a) { return vcgtzs_f32(a); }
[[gnu::always_inline]] nce uint64_t greater_than_zero(float64_t a) { return vcgtzd_f64(a); }
[[gnu::always_inline]] nce uint64x1_t less_than(int64x1_t a, int64x1_t b) { return vclt_s64(a, b); }
[[gnu::always_inline]] nce uint64x2_t less_than(int64x2_t a, int64x2_t b) { return vcltq_s64(a, b); }
[[gnu::always_inline]] nce uint64_t less_than(int64_t a, int64_t b) { return vcltd_s64(a, b); }
[[gnu::always_inline]] nce uint64_t less_than(uint64_t a, uint64_t b) { return vcltd_u64(a, b); }
[[gnu::always_inline]] nce uint32_t less_than(float32_t a, float32_t b) { return vclts_f32(a, b); }
[[gnu::always_inline]] nce uint64_t less_than(float64_t a, float64_t b) { return vcltd_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t less_than_zero(int64x1_t a) { return vcltz_s64(a); }
[[gnu::always_inline]] nce uint64x2_t less_than_zero(int64x2_t a) { return vcltzq_s64(a); }
[[gnu::always_inline]] nce uint64_t less_than_zero(int64_t a) { return vcltzd_s64(a); }
[[gnu::always_inline]] nce uint32_t less_than_zero(float32_t a) { return vcltzs_f32(a); }
[[gnu::always_inline]] nce uint64_t less_than_zero(float64_t a) { return vcltzd_f64(a); }
[[gnu::always_inline]] nce uint32_t absolute_greater_than_or_equal(float32_t a, float32_t b) { return vcages_f32(a, b); }
[[gnu::always_inline]] nce uint64_t absolute_greater_than_or_equal(float64_t a, float64_t b) { return vcaged_f64(a, b); }
[[gnu::always_inline]] nce uint32_t absolute_less_than_or_equal(float32_t a, float32_t b) { return vcales_f32(a, b); }
[[gnu::always_inline]] nce uint64_t absolute_less_than_or_equal(float64_t a, float64_t b) { return vcaled_f64(a, b); }
[[gnu::always_inline]] nce uint32_t absolute_greater_than(float32_t a, float32_t b) { return vcagts_f32(a, b); }
[[gnu::always_inline]] nce uint64_t absolute_greater_than(float64_t a, float64_t b) { return vcagtd_f64(a, b); }
[[gnu::always_inline]] nce uint32_t absolute_less_than(float32_t a, float32_t b) { return vcalts_f32(a, b); }
[[gnu::always_inline]] nce uint64_t absolute_less_than(float64_t a, float64_t b) { return vcaltd_f64(a, b); }
[[gnu::always_inline]] nce uint64x1_t compare_test_nonzero(int64x1_t a, int64x1_t b) { return vtst_s64(a, b); }
[[gnu::always_inline]] nce uint64x2_t compare_test_nonzero(int64x2_t a, int64x2_t b) { return vtstq_s64(a, b); }
[[gnu::always_inline]] nce uint64_t compare_test_nonzero(int64_t a, int64_t b) { return vtstd_s64(a, b); }
[[gnu::always_inline]] nce uint64_t compare_test_nonzero(uint64_t a, uint64_t b) { return vtstd_u64(a, b); }
[[gnu::always_inline]] nce int64_t shift_left(int64_t a, int64_t b) { return vshld_s64(a, b); }
[[gnu::always_inline]] nce uint64_t shift_left(uint64_t a, int64_t b) { return vshld_u64(a, b); }
template <int n>[[gnu::always_inline]] nce int64_t shift_left(int64_t a) { return vshld_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64_t shift_left(uint64_t a) { return vshld_n_u64(a, n); }
[[gnu::always_inline]] nce int8_t shift_left_saturate(int8_t a, int8_t b) { return vqshlb_s8(a, b); }
[[gnu::always_inline]] nce int16_t shift_left_saturate(int16_t a, int16_t b) { return vqshlh_s16(a, b); }
[[gnu::always_inline]] nce int32_t shift_left_saturate(int32_t a, int32_t b) { return vqshls_s32(a, b); }
[[gnu::always_inline]] nce int64_t shift_left_saturate(int64_t a, int64_t b) { return vqshld_s64(a, b); }
[[gnu::always_inline]] nce uint8_t shift_left_saturate(uint8_t a, int8_t b) { return vqshlb_u8(a, b); }
[[gnu::always_inline]] nce uint16_t shift_left_saturate(uint16_t a, int16_t b) { return vqshlh_u16(a, b); }
[[gnu::always_inline]] nce uint32_t shift_left_saturate(uint32_t a, int32_t b) { return vqshls_u32(a, b); }
[[gnu::always_inline]] nce uint64_t shift_left_saturate(uint64_t a, int64_t b) { return vqshld_u64(a, b); }
template <int n>[[gnu::always_inline]] nce int8_t shift_left_saturate(int8_t a) { return vqshlb_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce int16_t shift_left_saturate(int16_t a) { return vqshlh_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int32_t shift_left_saturate(int32_t a) { return vqshls_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int64_t shift_left_saturate(int64_t a) { return vqshld_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint8_t shift_left_saturate(uint8_t a) { return vqshlb_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint16_t shift_left_saturate(uint16_t a) { return vqshlh_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint32_t shift_left_saturate(uint32_t a) { return vqshls_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint64_t shift_left_saturate(uint64_t a) { return vqshld_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint8_t shift_left_unsigned_saturate(int8_t a) { return vqshlub_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce uint16_t shift_left_unsigned_saturate(int16_t a) { return vqshluh_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce uint32_t shift_left_unsigned_saturate(int32_t a) { return vqshlus_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce uint64_t shift_left_unsigned_saturate(int64_t a) { return vqshlud_n_s64(a, n); }
[[gnu::always_inline]] nce int64_t shift_left_round(int64_t a, int64_t b) { return vrshld_s64(a, b); }
[[gnu::always_inline]] nce uint64_t shift_left_round(uint64_t a, int64_t b) { return vrshld_u64(a, b); }
[[gnu::always_inline]] nce int8_t shift_left_round_saturate(int8_t a, int8_t b) { return vqrshlb_s8(a, b); }
[[gnu::always_inline]] nce int16_t shift_left_round_saturate(int16_t a, int16_t b) { return vqrshlh_s16(a, b); }
[[gnu::always_inline]] nce int32_t shift_left_round_saturate(int32_t a, int32_t b) { return vqrshls_s32(a, b); }
[[gnu::always_inline]] nce int64_t shift_left_round_saturate(int64_t a, int64_t b) { return vqrshld_s64(a, b); }
[[gnu::always_inline]] nce uint8_t shift_left_round_saturate(uint8_t a, int8_t b) { return vqrshlb_u8(a, b); }
[[gnu::always_inline]] nce uint16_t shift_left_round_saturate(uint16_t a, int16_t b) { return vqrshlh_u16(a, b); }
[[gnu::always_inline]] nce uint32_t shift_left_round_saturate(uint32_t a, int32_t b) { return vqrshls_u32(a, b); }
[[gnu::always_inline]] nce uint64_t shift_left_round_saturate(uint64_t a, int64_t b) { return vqrshld_u64(a, b); }
template <int n>[[gnu::always_inline]] nce int64_t shift_left_insert(int64_t a, int64_t b) { return vslid_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint64_t shift_left_insert(uint64_t a, uint64_t b) { return vslid_n_u64(a, b, n); }
template <int n>[[gnu::always_inline]] nce int64_t shift_right(int64_t a) { return vshrd_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64_t shift_right(uint64_t a) { return vshrd_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce int64_t shift_right_round(int64_t a) { return vrshrd_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64_t shift_right_round(uint64_t a) { return vrshrd_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce int64_t shift_right_add(int64_t a, int64_t b) { return vsrad_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint64_t shift_right_add(uint64_t a, uint64_t b) { return vsrad_n_u64(a, b, n); }
template <int n>[[gnu::always_inline]] nce int64_t shift_right_accumulate_round(int64_t a, int64_t b) { return vrsrad_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint64_t shift_right_accumulate_round(uint64_t a, uint64_t b) { return vrsrad_n_u64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint8_t shift_right_saturate_narrow_unsigned(int16_t a) { return vqshrunh_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16_t shift_right_saturate_narrow_unsigned(int32_t a) { return vqshruns_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32_t shift_right_saturate_narrow_unsigned(int64_t a) { return vqshrund_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int8_t shift_right_saturate_narrow(int16_t a) { return vqshrnh_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16_t shift_right_saturate_narrow(int32_t a) { return vqshrns_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32_t shift_right_saturate_narrow(int64_t a) { return vqshrnd_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint8_t shift_right_saturate_narrow(uint16_t a) { return vqshrnh_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16_t shift_right_saturate_narrow(uint32_t a) { return vqshrns_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32_t shift_right_saturate_narrow(uint64_t a) { return vqshrnd_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint8_t shift_right_unsigned_round_saturate_narrow(int16_t a) { return vqrshrunh_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16_t shift_right_unsigned_round_saturate_narrow(int32_t a) { return vqrshruns_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32_t shift_right_unsigned_round_saturate_narrow(int64_t a) { return vqrshrund_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int8_t shift_right_round_saturate_narrow(int16_t a) { return vqrshrnh_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16_t shift_right_round_saturate_narrow(int32_t a) { return vqrshrns_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32_t shift_right_round_saturate_narrow(int64_t a) { return vqrshrnd_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint8_t shift_right_round_saturate_narrow(uint16_t a) { return vqrshrnh_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16_t shift_right_round_saturate_narrow(uint32_t a) { return vqrshrns_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32_t shift_right_round_saturate_narrow(uint64_t a) { return vqrshrnd_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce int64_t shift_right_insert(int64_t a, int64_t b) { return vsrid_n_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint64_t shift_right_insert(uint64_t a, uint64_t b) { return vsrid_n_u64(a, b, n); }
template <> [[gnu::always_inline]] nce int32_t convert(float32_t a) { return vcvts_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32_t convert(float32_t a) { return vcvts_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32_t convert_round_to_nearest_with_ties_to_even(float32_t a) { return vcvtns_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32_t convert_round_to_nearest_with_ties_to_even(float32_t a) { return vcvtns_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32_t convert_round_toward_negative_infinity(float32_t a) { return vcvtms_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32_t convert_round_toward_negative_infinity(float32_t a) { return vcvtms_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32_t convert_round_toward_positive_infinity(float32_t a) { return vcvtps_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32_t convert_round_toward_positive_infinity(float32_t a) { return vcvtps_u32_f32(a); }
template <> [[gnu::always_inline]] nce int32_t convert_round_to_nearest_with_ties_away_from_zero(float32_t a) { return vcvtas_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32_t convert_round_to_nearest_with_ties_away_from_zero(float32_t a) { return vcvtas_u32_f32(a); }
template <> [[gnu::always_inline]] nce int64_t convert(float64_t a) { return vcvtd_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64_t convert(float64_t a) { return vcvtd_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64_t convert_round_to_nearest_with_ties_to_even(float64_t a) { return vcvtnd_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64_t convert_round_to_nearest_with_ties_to_even(float64_t a) { return vcvtnd_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64_t convert_round_toward_negative_infinity(float64_t a) { return vcvtmd_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64_t convert_round_toward_negative_infinity(float64_t a) { return vcvtmd_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64_t convert_round_toward_positive_infinity(float64_t a) { return vcvtpd_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64_t convert_round_toward_positive_infinity(float64_t a) { return vcvtpd_u64_f64(a); }
template <> [[gnu::always_inline]] nce int64_t convert_round_to_nearest_with_ties_away_from_zero(float64_t a) { return vcvtad_s64_f64(a); }
template <> [[gnu::always_inline]] nce uint64_t convert_round_to_nearest_with_ties_away_from_zero(float64_t a) { return vcvtad_u64_f64(a); }
template <int n>[[gnu::always_inline]] nce int32_t convert(float32_t a) { return vcvts_n_s32_f32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32_t convert(float32_t a) { return vcvts_n_u32_f32(a, n); }
template <int n>[[gnu::always_inline]] nce int64_t convert(float64_t a) { return vcvtd_n_s64_f64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64_t convert(float64_t a) { return vcvtd_n_u64_f64(a, n); }
template <> [[gnu::always_inline]] nce float32_t convert(int32_t a) { return vcvts_f32_s32(a); }
template <> [[gnu::always_inline]] nce float32_t convert(uint32_t a) { return vcvts_f32_u32(a); }
template <> [[gnu::always_inline]] nce float64x1_t convert(int64x1_t a) { return vcvt_f64_s64(a); }
template <> [[gnu::always_inline]] nce float64x2_t convert(int64x2_t a) { return vcvtq_f64_s64(a); }
template <> [[gnu::always_inline]] nce float64_t convert(int64_t a) { return vcvtd_f64_s64(a); }
template <> [[gnu::always_inline]] nce float64_t convert(uint64_t a) { return vcvtd_f64_u64(a); }
template <int n>[[gnu::always_inline]] nce float32_t convert(int32_t a) { return vcvts_n_f32_s32(a, n); }
template <int n>[[gnu::always_inline]] nce float32_t convert(uint32_t a) { return vcvts_n_f32_u32(a, n); }
template <int n>[[gnu::always_inline]] nce float64x1_t convert(int64x1_t a) { return vcvt_n_f64_s64(a, n); }
template <int n>[[gnu::always_inline]] nce float64x2_t convert(int64x2_t a) { return vcvtq_n_f64_s64(a, n); }
template <int n>[[gnu::always_inline]] nce float64_t convert(int64_t a) { return vcvtd_n_f64_s64(a, n); }
template <int n>[[gnu::always_inline]] nce float64_t convert(uint64_t a) { return vcvtd_n_f64_u64(a, n); }
[[gnu::always_inline]] nce float32_t convert_round_to_odd(float64_t a) { return vcvtxd_f32_f64(a); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(int64x1_t a) { return vreinterpret_f64_s64(a); }
[[gnu::always_inline]] nce float64x2_t reinterpret(poly8x16_t a) { return vreinterpretq_f64_p8(a); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(poly16x8_t a) { return vreinterpretq_f64_p16(a); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(int64x2_t a) { return vreinterpretq_f64_s64(a); }
[[gnu::always_inline]] nce float64x1_t reinterpret(poly64x1_t a) { return vreinterpret_f64_p64(a); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(poly64x2_t a) { return vreinterpretq_f64_p64(a); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(poly128_t a) { return vreinterpretq_f64_p128(a); }
[[gnu::always_inline]] nce int8_t move_saturate_narrow(int16_t a) { return vqmovnh_s16(a); }
[[gnu::always_inline]] nce int16_t move_saturate_narrow(int32_t a) { return vqmovns_s32(a); }
[[gnu::always_inline]] nce int32_t move_saturate_narrow(int64_t a) { return vqmovnd_s64(a); }
[[gnu::always_inline]] nce uint8_t move_saturate_narrow(uint16_t a) { return vqmovnh_u16(a); }
[[gnu::always_inline]] nce uint16_t move_saturate_narrow(uint32_t a) { return vqmovns_u32(a); }
[[gnu::always_inline]] nce uint32_t move_saturate_narrow(uint64_t a) { return vqmovnd_u64(a); }
[[gnu::always_inline]] nce uint8_t move_unsigned_saturate_narrow(int16_t a) { return vqmovunh_s16(a); }
[[gnu::always_inline]] nce uint16_t move_unsigned_saturate_narrow(int32_t a) { return vqmovuns_s32(a); }
[[gnu::always_inline]] nce uint32_t move_unsigned_saturate_narrow(int64_t a) { return vqmovund_s64(a); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_add_long_lane_high(int64x2_t a, int32x4_t b, int32x2_t v) { return vmlal_high_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_add_long_lane(int64x2_t a, int32x2_t b, int32x4_t v) { return vmlal_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_add_long_lane_high(int64x2_t a, int32x4_t b, int32x4_t v) { return vmlal_high_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_subtract_long_lane_high(int64x2_t a, int32x4_t b, int32x2_t v) { return vmlsl_high_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_subtract_long_lane(int64x2_t a, int32x2_t b, int32x4_t v) { return vmlsl_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_subtract_long_lane_high(int64x2_t a, int32x4_t b, int32x4_t v) { return vmlsl_high_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32_t multiply_lane(float32_t a, float32x2_t v) { return vmuls_lane_f32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t multiply_lane(float64_t a, float64x1_t v) { return vmuld_lane_f64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32_t multiply_lane(float32_t a, float32x4_t v) { return vmuls_laneq_f32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t multiply_lane(float64_t a, float64x2_t v) { return vmuld_laneq_f64(a, v, lane); }
[[gnu::always_inline]] nce int64x2_t multiply_add_long_high(int64x2_t a, int32x4_t b, int32_t c) { return vmlal_high_n_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_subtract_long_high(int64x2_t a, int32x4_t b, int32_t c) { return vmlsl_high_n_s32(a, b, c); }
[[gnu::always_inline]] nce int64x1_t negate(int64x1_t a) { return vneg_s64(a); }
[[gnu::always_inline]] nce int64_t negate(int64_t a) { return vnegd_s64(a); }
[[gnu::always_inline]] nce int64x2_t negate(int64x2_t a) { return vnegq_s64(a); }
[[gnu::always_inline]] nce int64x1_t negate_saturate(int64x1_t a) { return vqneg_s64(a); }
[[gnu::always_inline]] nce int64x2_t negate_saturate(int64x2_t a) { return vqnegq_s64(a); }
[[gnu::always_inline]] nce int8_t negate_saturate(int8_t a) { return vqnegb_s8(a); }
[[gnu::always_inline]] nce int16_t negate_saturate(int16_t a) { return vqnegh_s16(a); }
[[gnu::always_inline]] nce int32_t negate_saturate(int32_t a) { return vqnegs_s32(a); }
[[gnu::always_inline]] nce int64_t negate_saturate(int64_t a) { return vqnegd_s64(a); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int64x1_t copy_lane(int64x1_t a, int64x1_t b) { return vcopy_lane_s64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int64x2_t copy_lane(int64x2_t a, int64x1_t b) { return vcopyq_lane_s64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly8x16_t copy_lane(poly8x16_t a, poly8x8_t b) { return vcopyq_lane_p8(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly16x8_t copy_lane(poly16x8_t a, poly16x4_t b) { return vcopyq_lane_p16(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int64x1_t copy_lane(int64x1_t a, int64x2_t b) { return vcopy_laneq_s64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce int64x2_t copy_lane(int64x2_t a, int64x2_t b) { return vcopyq_laneq_s64(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly8x16_t copy_lane(poly8x16_t a, poly8x16_t b) { return vcopyq_laneq_p8(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce poly16x8_t copy_lane(poly16x8_t a, poly16x8_t b) { return vcopyq_laneq_p16(a, lane1, b, lane2); }
[[gnu::always_inline]] nce poly8x16_t reverse_bits(poly8x16_t a) { return vrbitq_p8(a); }
template <> [[gnu::always_inline]] nce float64x1_t create(uint64_t a) { return vcreate_f64(a); }
template <> [[gnu::always_inline]] nce float64x1_t duplicate(float64_t value) { return vdup_n_f64(value); }
template <> [[gnu::always_inline]] nce float64x2_t duplicate(float64_t value) { return vdupq_n_f64(value); }
template <> [[gnu::always_inline]] nce float64x1_t move(float64_t value) { return vmov_n_f64(value); }
template <> [[gnu::always_inline]] nce float64x2_t move(float64_t value) { return vmovq_n_f64(value); }
template <int lane>[[gnu::always_inline]] nce int64x1_t duplicate_lane(int64x2_t vec) { return vdup_laneq_s64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t duplicate_lane_quad(int64x2_t vec) { return vdupq_laneq_s64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x1_t duplicate_lane(poly64x2_t vec) { return vdup_laneq_p64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x2_t duplicate_lane_quad(poly64x2_t vec) { return vdupq_laneq_p64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8_t duplicate_lane(poly8x16_t vec) { return vdup_laneq_p8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x16_t duplicate_lane_quad(poly8x16_t vec) { return vdupq_laneq_p8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4_t duplicate_lane(poly16x8_t vec) { return vdup_laneq_p16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8_t duplicate_lane_quad(poly16x8_t vec) { return vdupq_laneq_p16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce int64_t duplicate_lane(int64x1_t vec) { return vdupd_lane_s64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce int64_t duplicate_lane(int64x2_t vec) { return vdupd_laneq_s64(vec, lane); }
[[gnu::always_inline]] nce int64x2_t zip1(int64x2_t a, int64x2_t b) { return vzip1q_s64(a, b); }
[[gnu::always_inline]] nce poly64x2_t zip1(poly64x2_t a, poly64x2_t b) { return vzip1q_p64(a, b); }
[[gnu::always_inline]] nce poly8x16_t zip1(poly8x16_t a, poly8x16_t b) { return vzip1q_p8(a, b); }
[[gnu::always_inline]] nce poly16x8_t zip1(poly16x8_t a, poly16x8_t b) { return vzip1q_p16(a, b); }
[[gnu::always_inline]] nce int64x2_t zip2(int64x2_t a, int64x2_t b) { return vzip2q_s64(a, b); }
[[gnu::always_inline]] nce poly64x2_t zip2(poly64x2_t a, poly64x2_t b) { return vzip2q_p64(a, b); }
[[gnu::always_inline]] nce poly8x16_t zip2(poly8x16_t a, poly8x16_t b) { return vzip2q_p8(a, b); }
[[gnu::always_inline]] nce poly16x8_t zip2(poly16x8_t a, poly16x8_t b) { return vzip2q_p16(a, b); }
[[gnu::always_inline]] nce int64x2_t unzip1(int64x2_t a, int64x2_t b) { return vuzp1q_s64(a, b); }
[[gnu::always_inline]] nce poly64x2_t unzip1(poly64x2_t a, poly64x2_t b) { return vuzp1q_p64(a, b); }
[[gnu::always_inline]] nce poly8x16_t unzip1(poly8x16_t a, poly8x16_t b) { return vuzp1q_p8(a, b); }
[[gnu::always_inline]] nce poly16x8_t unzip1(poly16x8_t a, poly16x8_t b) { return vuzp1q_p16(a, b); }
[[gnu::always_inline]] nce int64x2_t unzip2(int64x2_t a, int64x2_t b) { return vuzp2q_s64(a, b); }
[[gnu::always_inline]] nce poly64x2_t unzip2(poly64x2_t a, poly64x2_t b) { return vuzp2q_p64(a, b); }
[[gnu::always_inline]] nce poly8x16_t unzip2(poly8x16_t a, poly8x16_t b) { return vuzp2q_p8(a, b); }
[[gnu::always_inline]] nce poly16x8_t unzip2(poly16x8_t a, poly16x8_t b) { return vuzp2q_p16(a, b); }
[[gnu::always_inline]] nce int64x2_t transpose_step_1(int64x2_t a, int64x2_t b) { return vtrn1q_s64(a, b); }
[[gnu::always_inline]] nce poly64x2_t transpose_step_1(poly64x2_t a, poly64x2_t b) { return vtrn1q_p64(a, b); }
[[gnu::always_inline]] nce poly8x16_t transpose_step_1(poly8x16_t a, poly8x16_t b) { return vtrn1q_p8(a, b); }
[[gnu::always_inline]] nce poly16x8_t transpose_step_1(poly16x8_t a, poly16x8_t b) { return vtrn1q_p16(a, b); }
[[gnu::always_inline]] nce int64x2_t transpose_step_2(int64x2_t a, int64x2_t b) { return vtrn2q_s64(a, b); }
[[gnu::always_inline]] nce poly64x2_t transpose_step_2(poly64x2_t a, poly64x2_t b) { return vtrn2q_p64(a, b); }
[[gnu::always_inline]] nce poly8x16_t transpose_step_2(poly8x16_t a, poly8x16_t b) { return vtrn2q_p8(a, b); }
[[gnu::always_inline]] nce poly16x8_t transpose_step_2(poly16x8_t a, poly16x8_t b) { return vtrn2q_p16(a, b); }
template <int lane>[[gnu::always_inline]] nce float64x1_t set_lane(float64_t a, float64x1_t v) { return vset_lane_f64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2_t set_lane(float64_t a, float64x2_t v) { return vsetq_lane_f64(a, v, lane); }
template <> [[gnu::always_inline]] inline float64x1_t load1(float64_t const *ptr) { return vld1_f64(ptr); }
template <> [[gnu::always_inline]] inline float64x2_t load1(float64_t const *ptr) { return vld1q_f64(ptr); }
template <int lane>[[gnu::always_inline]] nce float64x1_t load1_lane(float64_t const *ptr, float64x1_t src) { return vld1_lane_f64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2_t load1_lane(float64_t const *ptr, float64x2_t src) { return vld1q_lane_f64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x1_t load_acquire1_lane(uint64_t const *ptr, uint64x1_t src) { return vldap1_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t load_acquire1_lane(uint64_t const *ptr, uint64x2_t src) { return vldap1q_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x1_t load_acquire1_lane(int64_t const *ptr, int64x1_t src) { return vldap1_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t load_acquire1_lane(int64_t const *ptr, int64x2_t src) { return vldap1q_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float64x1_t load_acquire1_lane(float64_t const *ptr, float64x1_t src) { return vldap1_lane_f64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2_t load_acquire1_lane(float64_t const *ptr, float64x2_t src) { return vldap1q_lane_f64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x1_t load_acquire1_lane(poly64_t const *ptr, poly64x1_t src) { return vldap1_lane_p64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x2_t load_acquire1_lane(poly64_t const *ptr, poly64x2_t src) { return vldap1q_lane_p64(ptr, src, lane); }
template <> [[gnu::always_inline]] inline float64x1_t load1_duplicate(float64_t const *ptr) { return vld1_dup_f64(ptr); }
template <> [[gnu::always_inline]] inline float64x2_t load1_duplicate(float64_t const *ptr) { return vld1q_dup_f64(ptr); }
template <int lane>[[gnu::always_inline]] nce void store_release1_lane(uint64_t *ptr, uint64x1_t val) { return vstl1_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store_release1_lane(uint64_t *ptr, uint64x2_t val) { return vstl1q_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store_release1_lane(int64_t *ptr, int64x1_t val) { return vstl1_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store_release1_lane(int64_t *ptr, int64x2_t val) { return vstl1q_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store_release1_lane(float64_t *ptr, float64x1_t val) { return vstl1_lane_f64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store_release1_lane(float64_t *ptr, float64x2_t val) { return vstl1q_lane_f64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store_release1_lane(poly64_t *ptr, poly64x1_t val) { return vstl1_lane_p64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store_release1_lane(poly64_t *ptr, poly64x2_t val) { return vstl1q_lane_p64(ptr, val, lane); }
template <> [[gnu::always_inline]] inline int64x2x2_t load2(int64_t const *ptr) { return vld2q_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x2x2_t load2(uint64_t const *ptr) { return vld2q_u64(ptr); }
template <> [[gnu::always_inline]] inline poly64x2x2_t load2(poly64_t const *ptr) { return vld2q_p64(ptr); }
template <> [[gnu::always_inline]] inline float64x1x2_t load2(float64_t const *ptr) { return vld2_f64(ptr); }
template <> [[gnu::always_inline]] inline float64x2x2_t load2(float64_t const *ptr) { return vld2q_f64(ptr); }
template <> [[gnu::always_inline]] inline int64x2x3_t load3(int64_t const *ptr) { return vld3q_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x2x3_t load3(uint64_t const *ptr) { return vld3q_u64(ptr); }
template <> [[gnu::always_inline]] inline poly64x2x3_t load3(poly64_t const *ptr) { return vld3q_p64(ptr); }
template <> [[gnu::always_inline]] inline float64x1x3_t load3(float64_t const *ptr) { return vld3_f64(ptr); }
template <> [[gnu::always_inline]] inline float64x2x3_t load3(float64_t const *ptr) { return vld3q_f64(ptr); }
template <> [[gnu::always_inline]] inline int64x2x4_t load4(int64_t const *ptr) { return vld4q_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x2x4_t load4(uint64_t const *ptr) { return vld4q_u64(ptr); }
template <> [[gnu::always_inline]] inline poly64x2x4_t load4(poly64_t const *ptr) { return vld4q_p64(ptr); }
template <> [[gnu::always_inline]] inline float64x1x4_t load4(float64_t const *ptr) { return vld4_f64(ptr); }
template <> [[gnu::always_inline]] inline float64x2x4_t load4(float64_t const *ptr) { return vld4q_f64(ptr); }
template <> [[gnu::always_inline]] inline int64x2x2_t load2_duplicate(int64_t const *ptr) { return vld2q_dup_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x2x2_t load2_duplicate(uint64_t const *ptr) { return vld2q_dup_u64(ptr); }
template <> [[gnu::always_inline]] inline poly64x2x2_t load2_duplicate(poly64_t const *ptr) { return vld2q_dup_p64(ptr); }
template <> [[gnu::always_inline]] inline float64x1x2_t load2_duplicate(float64_t const *ptr) { return vld2_dup_f64(ptr); }
template <> [[gnu::always_inline]] inline float64x2x2_t load2_duplicate(float64_t const *ptr) { return vld2q_dup_f64(ptr); }
template <> [[gnu::always_inline]] inline int64x2x3_t load3_duplicate(int64_t const *ptr) { return vld3q_dup_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x2x3_t load3_duplicate(uint64_t const *ptr) { return vld3q_dup_u64(ptr); }
template <> [[gnu::always_inline]] inline poly64x2x3_t load3_duplicate(poly64_t const *ptr) { return vld3q_dup_p64(ptr); }
template <> [[gnu::always_inline]] inline float64x1x3_t load3_duplicate(float64_t const *ptr) { return vld3_dup_f64(ptr); }
template <> [[gnu::always_inline]] inline float64x2x3_t load3_duplicate(float64_t const *ptr) { return vld3q_dup_f64(ptr); }
template <> [[gnu::always_inline]] inline int64x2x4_t load4_duplicate(int64_t const *ptr) { return vld4q_dup_s64(ptr); }
template <> [[gnu::always_inline]] inline uint64x2x4_t load4_duplicate(uint64_t const *ptr) { return vld4q_dup_u64(ptr); }
template <> [[gnu::always_inline]] inline poly64x2x4_t load4_duplicate(poly64_t const *ptr) { return vld4q_dup_p64(ptr); }
template <> [[gnu::always_inline]] inline float64x1x4_t load4_duplicate(float64_t const *ptr) { return vld4_dup_f64(ptr); }
template <> [[gnu::always_inline]] inline float64x2x4_t load4_duplicate(float64_t const *ptr) { return vld4q_dup_f64(ptr); }
template <int lane>[[gnu::always_inline]] nce int8x16x2_t load2_lane(int8_t const *ptr, int8x16x2_t src) { return vld2q_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16x2_t load2_lane(uint8_t const *ptr, uint8x16x2_t src) { return vld2q_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x16x2_t load2_lane(poly8_t const *ptr, poly8x16x2_t src) { return vld2q_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x1x2_t load2_lane(int64_t const *ptr, int64x1x2_t src) { return vld2_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2x2_t load2_lane(int64_t const *ptr, int64x2x2_t src) { return vld2q_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x1x2_t load2_lane(uint64_t const *ptr, uint64x1x2_t src) { return vld2_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2x2_t load2_lane(uint64_t const *ptr, uint64x2x2_t src) { return vld2q_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x1x2_t load2_lane(poly64_t const *ptr, poly64x1x2_t src) { return vld2_lane_p64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x2x2_t load2_lane(poly64_t const *ptr, poly64x2x2_t src) { return vld2q_lane_p64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float64x1x2_t load2_lane(float64_t const *ptr, float64x1x2_t src) { return vld2_lane_f64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2x2_t load2_lane(float64_t const *ptr, float64x2x2_t src) { return vld2q_lane_f64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16x3_t load3_lane(int8_t const *ptr, int8x16x3_t src) { return vld3q_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16x3_t load3_lane(uint8_t const *ptr, uint8x16x3_t src) { return vld3q_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x16x3_t load3_lane(poly8_t const *ptr, poly8x16x3_t src) { return vld3q_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x1x3_t load3_lane(int64_t const *ptr, int64x1x3_t src) { return vld3_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2x3_t load3_lane(int64_t const *ptr, int64x2x3_t src) { return vld3q_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x1x3_t load3_lane(uint64_t const *ptr, uint64x1x3_t src) { return vld3_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2x3_t load3_lane(uint64_t const *ptr, uint64x2x3_t src) { return vld3q_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x1x3_t load3_lane(poly64_t const *ptr, poly64x1x3_t src) { return vld3_lane_p64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x2x3_t load3_lane(poly64_t const *ptr, poly64x2x3_t src) { return vld3q_lane_p64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float64x1x3_t load3_lane(float64_t const *ptr, float64x1x3_t src) { return vld3_lane_f64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2x3_t load3_lane(float64_t const *ptr, float64x2x3_t src) { return vld3q_lane_f64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16x4_t load4_lane(int8_t const *ptr, int8x16x4_t src) { return vld4q_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16x4_t load4_lane(uint8_t const *ptr, uint8x16x4_t src) { return vld4q_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x16x4_t load4_lane(poly8_t const *ptr, poly8x16x4_t src) { return vld4q_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x1x4_t load4_lane(int64_t const *ptr, int64x1x4_t src) { return vld4_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2x4_t load4_lane(int64_t const *ptr, int64x2x4_t src) { return vld4q_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x1x4_t load4_lane(uint64_t const *ptr, uint64x1x4_t src) { return vld4_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2x4_t load4_lane(uint64_t const *ptr, uint64x2x4_t src) { return vld4q_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x1x4_t load4_lane(poly64_t const *ptr, poly64x1x4_t src) { return vld4_lane_p64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly64x2x4_t load4_lane(poly64_t const *ptr, poly64x2x4_t src) { return vld4q_lane_p64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float64x1x4_t load4_lane(float64_t const *ptr, float64x1x4_t src) { return vld4_lane_f64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float64x2x4_t load4_lane(float64_t const *ptr, float64x2x4_t src) { return vld4q_lane_f64(ptr, src, lane); }
template <> [[gnu::always_inline]] inline float64x1x2_t load1_x2(float64_t const *ptr) { return vld1_f64_x2(ptr); }
template <> [[gnu::always_inline]] inline float64x2x2_t load1_x2(float64_t const *ptr) { return vld1q_f64_x2(ptr); }
template <> [[gnu::always_inline]] inline float64x1x3_t load1_x3(float64_t const *ptr) { return vld1_f64_x3(ptr); }
template <> [[gnu::always_inline]] inline float64x2x3_t load1_x3(float64_t const *ptr) { return vld1q_f64_x3(ptr); }
template <> [[gnu::always_inline]] inline float64x1x4_t load1_x4(float64_t const *ptr) { return vld1_f64_x4(ptr); }
template <> [[gnu::always_inline]] inline float64x2x4_t load1_x4(float64_t const *ptr) { return vld1q_f64_x4(ptr); }
template <> [[gnu::always_inline]] inline void store1(float64_t *ptr, float64x1_t val) { return vst1_f64(ptr, val); }
template <> [[gnu::always_inline]] inline void store1(float64_t *ptr, float64x2_t val) { return vst1q_f64(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(float64_t *ptr, float64x1_t val) { return vst1_lane_f64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(float64_t *ptr, float64x2_t val) { return vst1q_lane_f64(ptr, val, lane); }
template <> [[gnu::always_inline]] inline void store2(int64_t *ptr, int64x2x2_t val) { return vst2q_s64(ptr, val); }
template <> [[gnu::always_inline]] inline void store2(uint64_t *ptr, uint64x2x2_t val) { return vst2q_u64(ptr, val); }
template <> [[gnu::always_inline]] inline void store2(poly64_t *ptr, poly64x2x2_t val) { return vst2q_p64(ptr, val); }
template <> [[gnu::always_inline]] inline void store2(float64_t *ptr, float64x1x2_t val) { return vst2_f64(ptr, val); }
template <> [[gnu::always_inline]] inline void store2(float64_t *ptr, float64x2x2_t val) { return vst2q_f64(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(int64_t *ptr, int64x2x3_t val) { return vst3q_s64(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(uint64_t *ptr, uint64x2x3_t val) { return vst3q_u64(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(poly64_t *ptr, poly64x2x3_t val) { return vst3q_p64(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(float64_t *ptr, float64x1x3_t val) { return vst3_f64(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(float64_t *ptr, float64x2x3_t val) { return vst3q_f64(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(int64_t *ptr, int64x2x4_t val) { return vst4q_s64(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(uint64_t *ptr, uint64x2x4_t val) { return vst4q_u64(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(poly64_t *ptr, poly64x2x4_t val) { return vst4q_p64(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(float64_t *ptr, float64x1x4_t val) { return vst4_f64(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(float64_t *ptr, float64x2x4_t val) { return vst4q_f64(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(int8_t *ptr, int8x16x2_t val) { return vst2q_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(uint8_t *ptr, uint8x16x2_t val) { return vst2q_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(poly8_t *ptr, poly8x16x2_t val) { return vst2q_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(int64_t *ptr, int64x1x2_t val) { return vst2_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(int64_t *ptr, int64x2x2_t val) { return vst2q_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(uint64_t *ptr, uint64x1x2_t val) { return vst2_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(uint64_t *ptr, uint64x2x2_t val) { return vst2q_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(poly64_t *ptr, poly64x1x2_t val) { return vst2_lane_p64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(poly64_t *ptr, poly64x2x2_t val) { return vst2q_lane_p64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(float64_t *ptr, float64x1x2_t val) { return vst2_lane_f64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(float64_t *ptr, float64x2x2_t val) { return vst2q_lane_f64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(int64_t *ptr, int64x1x3_t val) { return vst3_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(int64_t *ptr, int64x2x3_t val) { return vst3q_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(uint64_t *ptr, uint64x1x3_t val) { return vst3_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(uint64_t *ptr, uint64x2x3_t val) { return vst3q_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(poly64_t *ptr, poly64x1x3_t val) { return vst3_lane_p64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(poly64_t *ptr, poly64x2x3_t val) { return vst3q_lane_p64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(float64_t *ptr, float64x1x3_t val) { return vst3_lane_f64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(float64_t *ptr, float64x2x3_t val) { return vst3q_lane_f64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(int8_t *ptr, int8x16x4_t val) { return vst4q_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(uint8_t *ptr, uint8x16x4_t val) { return vst4q_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(poly8_t *ptr, poly8x16x4_t val) { return vst4q_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(int64_t *ptr, int64x1x4_t val) { return vst4_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(int64_t *ptr, int64x2x4_t val) { return vst4q_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(uint64_t *ptr, uint64x1x4_t val) { return vst4_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(uint64_t *ptr, uint64x2x4_t val) { return vst4q_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(poly64_t *ptr, poly64x1x4_t val) { return vst4_lane_p64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(poly64_t *ptr, poly64x2x4_t val) { return vst4q_lane_p64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(float64_t *ptr, float64x1x4_t val) { return vst4_lane_f64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(float64_t *ptr, float64x2x4_t val) { return vst4q_lane_f64(ptr, val, lane); }
[[gnu::always_inline]] inline void store1_x2(float64_t *ptr, float64x1x2_t val) { return vst1_f64_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(float64_t *ptr, float64x2x2_t val) { return vst1q_f64_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(float64_t *ptr, float64x1x3_t val) { return vst1_f64_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(float64_t *ptr, float64x2x3_t val) { return vst1q_f64_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(float64_t *ptr, float64x1x4_t val) { return vst1_f64_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(float64_t *ptr, float64x2x4_t val) { return vst1q_f64_x4(ptr, val); }
[[gnu::always_inline]] nce poly8x8_t table_lookup1_saturate(poly8x16_t t, uint8x8_t idx) { return vqtbl1_p8(t, idx); }
[[gnu::always_inline]] nce poly8x16_t table_lookup1_saturate(poly8x16_t t, uint8x16_t idx) { return vqtbl1q_p8(t, idx); }
[[gnu::always_inline]] nce int8x8_t table_lookup2_saturate(int8x16x2_t t, uint8x8_t idx) { return vqtbl2_s8(t, idx); }
[[gnu::always_inline]] nce int8x16_t table_lookup2_saturate(int8x16x2_t t, uint8x16_t idx) { return vqtbl2q_s8(t, idx); }
[[gnu::always_inline]] nce uint8x8_t table_lookup2_saturate(uint8x16x2_t t, uint8x8_t idx) { return vqtbl2_u8(t, idx); }
[[gnu::always_inline]] nce uint8x16_t table_lookup2_saturate(uint8x16x2_t t, uint8x16_t idx) { return vqtbl2q_u8(t, idx); }
[[gnu::always_inline]] nce poly8x8_t table_lookup2_saturate(poly8x16x2_t t, uint8x8_t idx) { return vqtbl2_p8(t, idx); }
[[gnu::always_inline]] nce poly8x16_t table_lookup2_saturate(poly8x16x2_t t, uint8x16_t idx) { return vqtbl2q_p8(t, idx); }
[[gnu::always_inline]] nce int8x8_t table_lookup3_saturate(int8x16x3_t t, uint8x8_t idx) { return vqtbl3_s8(t, idx); }
[[gnu::always_inline]] nce int8x16_t table_lookup3_saturate(int8x16x3_t t, uint8x16_t idx) { return vqtbl3q_s8(t, idx); }
[[gnu::always_inline]] nce uint8x8_t table_lookup3_saturate(uint8x16x3_t t, uint8x8_t idx) { return vqtbl3_u8(t, idx); }
[[gnu::always_inline]] nce uint8x16_t table_lookup3_saturate(uint8x16x3_t t, uint8x16_t idx) { return vqtbl3q_u8(t, idx); }
[[gnu::always_inline]] nce poly8x8_t table_lookup3_saturate(poly8x16x3_t t, uint8x8_t idx) { return vqtbl3_p8(t, idx); }
[[gnu::always_inline]] nce poly8x16_t table_lookup3_saturate(poly8x16x3_t t, uint8x16_t idx) { return vqtbl3q_p8(t, idx); }
[[gnu::always_inline]] nce int8x8_t table_lookup4_saturate(int8x16x4_t t, uint8x8_t idx) { return vqtbl4_s8(t, idx); }
[[gnu::always_inline]] nce int8x16_t table_lookup4_saturate(int8x16x4_t t, uint8x16_t idx) { return vqtbl4q_s8(t, idx); }
[[gnu::always_inline]] nce uint8x8_t table_lookup4_saturate(uint8x16x4_t t, uint8x8_t idx) { return vqtbl4_u8(t, idx); }
[[gnu::always_inline]] nce uint8x16_t table_lookup4_saturate(uint8x16x4_t t, uint8x16_t idx) { return vqtbl4q_u8(t, idx); }
[[gnu::always_inline]] nce poly8x8_t table_lookup4_saturate(poly8x16x4_t t, uint8x8_t idx) { return vqtbl4_p8(t, idx); }
[[gnu::always_inline]] nce poly8x16_t table_lookup4_saturate(poly8x16x4_t t, uint8x16_t idx) { return vqtbl4q_p8(t, idx); }
[[gnu::always_inline]] nce poly8x16_t table_extend1_saturate(poly8x16_t a, poly8x16_t t, uint8x16_t idx) { return vqtbx1q_p8(a, t, idx); }
[[gnu::always_inline]] nce poly8x16_t table_extend2_saturate(poly8x16_t a, poly8x16x2_t t, uint8x16_t idx) { return vqtbx2q_p8(a, t, idx); }
[[gnu::always_inline]] nce poly8x16_t table_extend3_saturate(poly8x16_t a, poly8x16x3_t t, uint8x16_t idx) { return vqtbx3q_p8(a, t, idx); }
[[gnu::always_inline]] nce poly8x16_t table_extend4_saturate(poly8x16_t a, poly8x16x4_t t, uint8x16_t idx) { return vqtbx4q_p8(a, t, idx); }
#ifdef __ARM_FEATURE_LUT
template <int index>[[gnu::always_inline]] nce uint8x16_t lookup_table_2bit_index_lane(uint8x8_t vn, uint8x8_t vm) { return vluti2_lane_u8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint8x16_t lookup_table_2bit_index_lane(uint8x8_t vn, uint8x16_t vm) { return vluti2_laneq_u8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint8x16_t lookup_table_2bit_index_lane(uint8x16_t vn, uint8x8_t vm) { return vluti2q_lane_u8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint8x16_t lookup_table_4bit_index_lane(uint8x16_t vn, uint8x8_t vm) { return vluti4q_lane_u8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint8x16_t lookup_table_2bit_index_lane(uint8x16_t vn, uint8x16_t vm) { return vluti2q_laneq_u8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint8x16_t lookup_table_4bit_index_lane(uint8x16_t vn, uint8x16_t vm) { return vluti4q_laneq_u8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int8x16_t lookup_table_2bit_index_lane(int8x8_t vn, uint8x8_t vm) { return vluti2_lane_s8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int8x16_t lookup_table_2bit_index_lane(int8x8_t vn, uint8x16_t vm) { return vluti2_laneq_s8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int8x16_t lookup_table_2bit_index_lane(int8x16_t vn, uint8x8_t vm) { return vluti2q_lane_s8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int8x16_t lookup_table_4bit_index_lane(int8x16_t vn, uint8x8_t vm) { return vluti4q_lane_s8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int8x16_t lookup_table_2bit_index_lane(int8x16_t vn, uint8x16_t vm) { return vluti2q_laneq_s8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int8x16_t lookup_table_4bit_index_lane(int8x16_t vn, uint8x16_t vm) { return vluti4q_laneq_s8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint16x8_t lookup_table_2bit_index_lane(uint16x4_t vn, uint8x8_t vm) { return vluti2_lane_u16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint16x8_t lookup_table_2bit_index_lane(uint16x4_t vn, uint8x16_t vm) { return vluti2_laneq_u16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint16x8_t lookup_table_2bit_index_lane(uint16x8_t vn, uint8x8_t vm) { return vluti2q_lane_u16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint16x8_t lookup_table_2bit_index_lane(uint16x8_t vn, uint8x16_t vm) { return vluti2q_laneq_u16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int16x8_t lookup_table_2bit_index_lane(int16x4_t vn, uint8x8_t vm) { return vluti2_lane_s16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int16x8_t lookup_table_2bit_index_lane(int16x4_t vn, uint8x16_t vm) { return vluti2_laneq_s16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int16x8_t lookup_table_2bit_index_lane(int16x8_t vn, uint8x8_t vm) { return vluti2q_lane_s16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int16x8_t lookup_table_2bit_index_lane(int16x8_t vn, uint8x16_t vm) { return vluti2q_laneq_s16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce float16x8_t lookup_table_2bit_index_lane(float16x4_t vn, uint8x8_t vm) { return vluti2_lane_f16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce float16x8_t lookup_table_2bit_index_lane(float16x4_t vn, uint8x16_t vm) { return vluti2_laneq_f16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce float16x8_t lookup_table_2bit_index_lane(float16x8_t vn, uint8x8_t vm) { return vluti2q_lane_f16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce float16x8_t lookup_table_2bit_index_lane(float16x8_t vn, uint8x16_t vm) { return vluti2q_laneq_f16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly8x16_t lookup_table_2bit_index_lane(poly8x8_t vn, uint8x8_t vm) { return vluti2_lane_p8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly8x16_t lookup_table_2bit_index_lane(poly8x8_t vn, uint8x16_t vm) { return vluti2_laneq_p8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly16x8_t lookup_table_2bit_index_lane(poly16x4_t vn, uint8x8_t vm) { return vluti2_lane_p16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly16x8_t lookup_table_2bit_index_lane(poly16x4_t vn, uint8x16_t vm) { return vluti2_laneq_p16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly8x16_t lookup_table_2bit_index_lane(poly8x16_t vn, uint8x8_t vm) { return vluti2q_lane_p8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly8x16_t lookup_table_2bit_index_lane(poly8x16_t vn, uint8x16_t vm) { return vluti2q_laneq_p8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce bfloat16x8_t lookup_table_2bit_index_lane(bfloat16x4_t vn, uint8x8_t vm) { return vluti2_lane_bf16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce bfloat16x8_t lookup_table_2bit_index_lane(bfloat16x4_t vn, uint8x16_t vm) { return vluti2_laneq_bf16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce bfloat16x8_t lookup_table_2bit_index_lane(bfloat16x8_t vn, uint8x8_t vm) { return vluti2q_lane_bf16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce bfloat16x8_t lookup_table_2bit_index_lane(bfloat16x8_t vn, uint8x16_t vm) { return vluti2q_laneq_bf16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly16x8_t lookup_table_2bit_index_lane(poly16x8_t vn, uint8x8_t vm) { return vluti2q_lane_p16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly16x8_t lookup_table_2bit_index_lane(poly16x8_t vn, uint8x16_t vm) { return vluti2q_laneq_p16(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly8x16_t lookup_table_4bit_index_lane(poly8x16_t vn, uint8x8_t vm) { return vluti4q_lane_p8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly8x16_t lookup_table_4bit_index_lane(poly8x16_t vn, uint8x16_t vm) { return vluti4q_laneq_p8(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint16x8_t lookup_table_4bit_index_lane(uint16x8x2_t vn, uint8x8_t vm) { return vluti4q_lane_u16_x2(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce uint16x8_t lookup_table_4bit_index_lane(uint16x8x2_t vn, uint8x16_t vm) { return vluti4q_laneq_u16_x2(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int16x8_t lookup_table_4bit_index_lane(int16x8x2_t vn, uint8x8_t vm) { return vluti4q_lane_s16_x2(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce int16x8_t lookup_table_4bit_index_lane(int16x8x2_t vn, uint8x16_t vm) { return vluti4q_laneq_s16_x2(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce float16x8_t lookup_table_4bit_index_lane(float16x8x2_t vn, uint8x8_t vm) { return vluti4q_lane_f16_x2(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce float16x8_t lookup_table_4bit_index_lane(float16x8x2_t vn, uint8x16_t vm) { return vluti4q_laneq_f16_x2(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce bfloat16x8_t lookup_table_4bit_index_lane(bfloat16x8x2_t vn, uint8x8_t vm) { return vluti4q_lane_bf16_x2(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce bfloat16x8_t lookup_table_4bit_index_lane(bfloat16x8x2_t vn, uint8x16_t vm) { return vluti4q_laneq_bf16_x2(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly16x8_t lookup_table_4bit_index_lane(poly16x8x2_t vn, uint8x8_t vm) { return vluti4q_lane_p16_x2(vn, vm, index); }
template <int index>[[gnu::always_inline]] nce poly16x8_t lookup_table_4bit_index_lane(poly16x8x2_t vn, uint8x16_t vm) { return vluti4q_laneq_p16_x2(vn, vm, index); }
#endif
[[gnu::always_inline]] nce int16_t multiply_double_add_round_saturate_high(int16_t a, int16_t b, int16_t c) { return vqrdmlahh_s16(a, b, c); }
[[gnu::always_inline]] nce int32_t multiply_double_add_round_saturate_high(int32_t a, int32_t b, int32_t c) { return vqrdmlahs_s32(a, b, c); }
[[gnu::always_inline]] nce int16_t multiply_double_subtract_round_saturate_high(int16_t a, int16_t b, int16_t c) { return vqrdmlshh_s16(a, b, c); }
[[gnu::always_inline]] nce int32_t multiply_double_subtract_round_saturate_high(int32_t a, int32_t b, int32_t c) { return vqrdmlshs_s32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int16_t multiply_double_add_round_saturate_high_lane(int16_t a, int16_t b, int16x4_t v) { return vqrdmlahh_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16_t multiply_double_add_round_saturate_high_lane(int16_t a, int16_t b, int16x8_t v) { return vqrdmlahh_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_add_round_saturate_high_lane(int32_t a, int32_t b, int32x2_t v) { return vqrdmlahs_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_add_round_saturate_high_lane(int32_t a, int32_t b, int32x4_t v) { return vqrdmlahs_laneq_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16_t multiply_double_subtract_round_saturate_high_lane(int16_t a, int16_t b, int16x4_t v) { return vqrdmlshh_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16_t multiply_double_subtract_round_saturate_high_lane(int16_t a, int16_t b, int16x8_t v) { return vqrdmlshh_laneq_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_subtract_round_saturate_high_lane(int32_t a, int32_t b, int32x2_t v) { return vqrdmlshs_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32_t multiply_double_subtract_round_saturate_high_lane(int32_t a, int32_t b, int32x4_t v) { return vqrdmlshs_laneq_s32(a, b, v, lane); }
#ifdef __ARM_FEATURE_FP16_VECTOR_ARITHMETIC
[[gnu::always_inline]] nce float16_t absolute_difference(float16_t a, float16_t b) { return vabdh_f16(a, b); }
[[gnu::always_inline]] nce float16_t reciprocal_estimate(float16_t a) { return vrecpeh_f16(a); }
[[gnu::always_inline]] nce float16_t reciprocal_exponent(float16_t a) { return vrecpxh_f16(a); }
[[gnu::always_inline]] nce float16_t reciprocal_sqrt_estimate(float16_t a) { return vrsqrteh_f16(a); }
[[gnu::always_inline]] nce float16_t reciprocal_sqrt_step(float16_t a, float16_t b) { return vrsqrtsh_f16(a, b); }
[[gnu::always_inline]] nce float16_t reciprocal_step(float16_t a, float16_t b) { return vrecpsh_f16(a, b); }
[[gnu::always_inline]] nce float16_t max(float16_t a, float16_t b) { return vmaxh_f16(a, b); }
[[gnu::always_inline]] nce float16_t min(float16_t a, float16_t b) { return vminh_f16(a, b); }
[[gnu::always_inline]] nce float16_t multiply_extended(float16_t a, float16_t b) { return vmulxh_f16(a, b); }
[[gnu::always_inline]] nce uint16_t equal_to_zero(float16_t a) { return vceqzh_f16(a); }
[[gnu::always_inline]] nce uint16_t greater_than_or_equal_to_zero(float16_t a) { return vcgezh_f16(a); }
[[gnu::always_inline]] nce uint16_t greater_than_zero(float16_t a) { return vcgtzh_f16(a); }
[[gnu::always_inline]] nce uint16_t less_than_or_equal_to_zero(float16_t a) { return vclezh_f16(a); }
[[gnu::always_inline]] nce uint16_t less_than_zero(float16_t a) { return vcltzh_f16(a); }
[[gnu::always_inline]] nce uint16_t absolute_greater_than_or_equal(float16_t a, float16_t b) { return vcageh_f16(a, b); }
[[gnu::always_inline]] nce uint16_t absolute_greater_than(float16_t a, float16_t b) { return vcagth_f16(a, b); }
[[gnu::always_inline]] nce uint16_t absolute_less_than_or_equal(float16_t a, float16_t b) { return vcaleh_f16(a, b); }
[[gnu::always_inline]] nce uint16_t absolute_less_than(float16_t a, float16_t b) { return vcalth_f16(a, b); }
[[gnu::always_inline]] nce uint16_t equal(float16_t a, float16_t b) { return vceqh_f16(a, b); }
[[gnu::always_inline]] nce uint16_t greater_than_or_equal(float16_t a, float16_t b) { return vcgeh_f16(a, b); }
[[gnu::always_inline]] nce uint16_t greater_than(float16_t a, float16_t b) { return vcgth_f16(a, b); }
[[gnu::always_inline]] nce uint16_t less_than_or_equal(float16_t a, float16_t b) { return vcleh_f16(a, b); }
[[gnu::always_inline]] nce uint16_t less_than(float16_t a, float16_t b) { return vclth_f16(a, b); }
template <> [[gnu::always_inline]] nce float16_t convert(int16_t a) { return vcvth_f16_s16(a); }
template <> [[gnu::always_inline]] nce float16_t convert(int64_t a) { return vcvth_f16_s64(a); }
template <> [[gnu::always_inline]] nce float16_t convert(uint16_t a) { return vcvth_f16_u16(a); }
template <> [[gnu::always_inline]] nce float16_t convert(uint64_t a) { return vcvth_f16_u64(a); }
template <> [[gnu::always_inline]] nce int16_t convert(float16_t a) { return vcvth_s16_f16(a); }
template <> [[gnu::always_inline]] nce int64_t convert(float16_t a) { return vcvth_s64_f16(a); }
template <> [[gnu::always_inline]] nce uint16_t convert(float16_t a) { return vcvth_u16_f16(a); }
template <> [[gnu::always_inline]] nce uint64_t convert(float16_t a) { return vcvth_u64_f16(a); }
template <> [[gnu::always_inline]] nce int16_t convert_round_to_nearest_with_ties_away_from_zero(float16_t a) { return vcvtah_s16_f16(a); }
template <> [[gnu::always_inline]] nce int64_t convert_round_to_nearest_with_ties_away_from_zero(float16_t a) { return vcvtah_s64_f16(a); }
template <> [[gnu::always_inline]] nce uint16_t convert_round_to_nearest_with_ties_away_from_zero(float16_t a) { return vcvtah_u16_f16(a); }
template <> [[gnu::always_inline]] nce uint64_t convert_round_to_nearest_with_ties_away_from_zero(float16_t a) { return vcvtah_u64_f16(a); }
template <> [[gnu::always_inline]] nce int16_t convert_round_toward_negative_infinity(float16_t a) { return vcvtmh_s16_f16(a); }
template <> [[gnu::always_inline]] nce int64_t convert_round_toward_negative_infinity(float16_t a) { return vcvtmh_s64_f16(a); }
template <> [[gnu::always_inline]] nce uint16_t convert_round_toward_negative_infinity(float16_t a) { return vcvtmh_u16_f16(a); }
template <> [[gnu::always_inline]] nce uint64_t convert_round_toward_negative_infinity(float16_t a) { return vcvtmh_u64_f16(a); }
template <> [[gnu::always_inline]] nce int16_t convert_round_to_nearest_with_ties_to_even(float16_t a) { return vcvtnh_s16_f16(a); }
template <> [[gnu::always_inline]] nce int64_t convert_round_to_nearest_with_ties_to_even(float16_t a) { return vcvtnh_s64_f16(a); }
template <> [[gnu::always_inline]] nce uint16_t convert_round_to_nearest_with_ties_to_even(float16_t a) { return vcvtnh_u16_f16(a); }
template <> [[gnu::always_inline]] nce uint64_t convert_round_to_nearest_with_ties_to_even(float16_t a) { return vcvtnh_u64_f16(a); }
template <> [[gnu::always_inline]] nce int16_t convert_round_toward_positive_infinity(float16_t a) { return vcvtph_s16_f16(a); }
template <> [[gnu::always_inline]] nce int64_t convert_round_toward_positive_infinity(float16_t a) { return vcvtph_s64_f16(a); }
template <> [[gnu::always_inline]] nce uint16_t convert_round_toward_positive_infinity(float16_t a) { return vcvtph_u16_f16(a); }
template <> [[gnu::always_inline]] nce uint64_t convert_round_toward_positive_infinity(float16_t a) { return vcvtph_u64_f16(a); }
template <int n>[[gnu::always_inline]] nce float16_t convert(int16_t a) { return vcvth_n_f16_s16(a, n); }
template <int n>[[gnu::always_inline]] nce float16_t convert(int64_t a) { return vcvth_n_f16_s64(a, n); }
template <int n>[[gnu::always_inline]] nce float16_t convert(uint16_t a) { return vcvth_n_f16_u16(a, n); }
template <int n>[[gnu::always_inline]] nce float16_t convert(uint64_t a) { return vcvth_n_f16_u64(a, n); }
template <int n>[[gnu::always_inline]] nce int16_t convert(float16_t a) { return vcvth_n_s16_f16(a, n); }
template <int n>[[gnu::always_inline]] nce int64_t convert(float16_t a) { return vcvth_n_s64_f16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16_t convert(float16_t a) { return vcvth_n_u16_f16(a, n); }
template <int n>[[gnu::always_inline]] nce uint64_t convert(float16_t a) { return vcvth_n_u64_f16(a, n); }
template <int lane>[[gnu::always_inline]] nce float16_t multiply_lane(float16_t a, float16x4_t v) { return vmulh_lane_f16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16_t multiply_lane(float16_t a, float16x8_t v) { return vmulh_laneq_f16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16_t multiply_extended_lane(float16_t a, float16x4_t v) { return vmulxh_lane_f16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16_t multiply_extended_lane(float16_t a, float16x8_t v) { return vmulxh_laneq_f16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16_t multiply_add_fused_lane(float16_t a, float16_t b, float16x4_t v) { return vfmah_lane_f16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16_t multiply_add_fused_lane(float16_t a, float16_t b, float16x8_t v) { return vfmah_laneq_f16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16_t multiply_subtract_fused_lane(float16_t a, float16_t b, float16x4_t v) { return vfmsh_lane_f16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16_t multiply_subtract_fused_lane(float16_t a, float16_t b, float16x8_t v) { return vfmsh_laneq_f16(a, b, v, lane); }
#endif

template <int lane1, int lane2>[[gnu::always_inline]] nce bfloat16x4_t copy_lane(bfloat16x4_t a, bfloat16x4_t b) { return vcopy_lane_bf16(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce bfloat16x8_t copy_lane(bfloat16x8_t a, bfloat16x4_t b) { return vcopyq_lane_bf16(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce bfloat16x4_t copy_lane(bfloat16x4_t a, bfloat16x8_t b) { return vcopy_laneq_bf16(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce bfloat16x8_t copy_lane(bfloat16x8_t a, bfloat16x8_t b) { return vcopyq_laneq_bf16(a, lane1, b, lane2); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(bfloat16x4_t a) { return vreinterpret_f64_bf16(a); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(bfloat16x8_t a) { return vreinterpretq_f64_bf16(a); }

}
#endif // __cplusplus
#undef nce
