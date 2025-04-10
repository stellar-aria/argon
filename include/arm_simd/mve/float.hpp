#pragma once
#include <arm_mve.h>
#include "neon_float.hpp"
#ifdef __cplusplus
#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

namespace mve {
// clang-format off
template <typename T> nce T create(uint64_t a, uint64_t b);
template <typename T> nce T uninitialized();
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float16x8_t a, mve_pred16_t p);
template <typename T> nce T convert_round_to_nearest_with_ties_away_from_zero(float32x4_t a, mve_pred16_t p);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float16x8_t a, mve_pred16_t p);
template <typename T> nce T convert_round_to_nearest_with_ties_to_even(float32x4_t a, mve_pred16_t p);
template <typename T> nce T convert_round_toward_positive_infinity(float16x8_t a, mve_pred16_t p);
template <typename T> nce T convert_round_toward_positive_infinity(float32x4_t a, mve_pred16_t p);
template <typename T> nce T convert_round_toward_negative_infinity(float16x8_t a, mve_pred16_t p);
template <typename T> nce T convert_round_toward_negative_infinity(float32x4_t a, mve_pred16_t p);
template <typename T> nce T convert(float16x8_t inactive, int16x8_t a, mve_pred16_t p);
template <typename T> nce T convert(float16x8_t inactive, uint16x8_t a, mve_pred16_t p);
template <typename T> nce T convert(float32x4_t inactive, int32x4_t a, mve_pred16_t p);
template <typename T> nce T convert(float32x4_t inactive, uint32x4_t a, mve_pred16_t p);
template <typename T> nce T convert(uint16x8_t a, mve_pred16_t p);
template <typename T> nce T convert(int16x8_t a, mve_pred16_t p);
template <typename T> nce T convert(int32x4_t a, mve_pred16_t p);
template <typename T> nce T convert(uint32x4_t a, mve_pred16_t p);
template <typename T> nce T convert(int16x8_t inactive, float16x8_t a, mve_pred16_t p);
template <typename T> nce T convert(int32x4_t inactive, float32x4_t a, mve_pred16_t p);
template <typename T> nce T convert(uint16x8_t inactive, float16x8_t a, mve_pred16_t p);
template <typename T> nce T convert(uint32x4_t inactive, float32x4_t a, mve_pred16_t p);
template <typename T> nce T convert(float16x8_t a, mve_pred16_t p);
template <typename T> nce T convert(float32x4_t a, mve_pred16_t p);
[[gnu::always_inline]] nce uint16x8_t convert_round_to_nearest_with_ties_away_from_zero(uint16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtaq_m_u16_f16(inactive, a, p); }
[[gnu::always_inline]] nce uint16x8_t convert_round_to_nearest_with_ties_to_even(uint16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtnq_m_u16_f16(inactive, a, p); }
[[gnu::always_inline]] nce uint16x8_t convert_round_toward_positive_infinity(uint16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtpq_m_u16_f16(inactive, a, p); }
[[gnu::always_inline]] nce uint16x8_t convert_round_toward_negative_infinity(uint16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtmq_m_u16_f16(inactive, a, p); }
template <> [[gnu::always_inline]] nce uint16x8_t convert(uint16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtq_m_u16_f16(inactive, a, p); }
template <int imm6>[[gnu::always_inline]] nce uint16x8_t convert(uint16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtq_m_n_u16_f16(inactive, a, imm6, p); }
template <> [[gnu::always_inline]] nce float16x8_t convert(uint16x8_t a, mve_pred16_t p) { return vcvtq_x_f16_u16(a, p); }
template <int imm6>[[gnu::always_inline]] nce float16x8_t convert(uint16x8_t a, mve_pred16_t p) { return vcvtq_x_n_f16_u16(a, imm6, p); }
[[gnu::always_inline]] nce int16x8_t convert_round_to_nearest_with_ties_away_from_zero(int16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtaq_m_s16_f16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t convert_round_to_nearest_with_ties_to_even(int16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtnq_m_s16_f16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t convert_round_toward_positive_infinity(int16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtpq_m_s16_f16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t convert_round_toward_negative_infinity(int16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtmq_m_s16_f16(inactive, a, p); }
template <> [[gnu::always_inline]] nce int16x8_t convert(int16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtq_m_s16_f16(inactive, a, p); }
template <int imm6>[[gnu::always_inline]] nce int16x8_t convert(int16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtq_m_n_s16_f16(inactive, a, imm6, p); }
template <> [[gnu::always_inline]] nce float16x8_t convert(int16x8_t a, mve_pred16_t p) { return vcvtq_x_f16_s16(a, p); }
template <int imm6>[[gnu::always_inline]] nce float16x8_t convert(int16x8_t a, mve_pred16_t p) { return vcvtq_x_n_f16_s16(a, imm6, p); }
[[gnu::always_inline]] nce int32x4_t convert_round_to_nearest_with_ties_away_from_zero(int32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtaq_m_s32_f32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t convert_round_to_nearest_with_ties_to_even(int32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtnq_m_s32_f32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t convert_round_toward_positive_infinity(int32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtpq_m_s32_f32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t convert_round_toward_negative_infinity(int32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtmq_m_s32_f32(inactive, a, p); }
template <> [[gnu::always_inline]] nce int32x4_t convert(int32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtq_m_s32_f32(inactive, a, p); }
template <int imm6>[[gnu::always_inline]] nce int32x4_t convert(int32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtq_m_n_s32_f32(inactive, a, imm6, p); }
template <> [[gnu::always_inline]] nce float32x4_t convert(int32x4_t a, mve_pred16_t p) { return vcvtq_x_f32_s32(a, p); }
template <int imm6>[[gnu::always_inline]] nce float32x4_t convert(int32x4_t a, mve_pred16_t p) { return vcvtq_x_n_f32_s32(a, imm6, p); }
template <int offset>[[gnu::always_inline]] nce float32x4_t load_word_gather_base(uint32x4_t addr) { return vldrwq_gather_base_f32(addr, offset); }
template <int offset>[[gnu::always_inline]] nce float32x4_t load_word_gather_base(uint32x4_t addr, mve_pred16_t p) { return vldrwq_gather_base_z_f32(addr, offset, p); }
template <int offset>[[gnu::always_inline]] nce float32x4_t load_word_gather_base(uint32x4_t *addr) { return vldrwq_gather_base_wb_f32(addr, offset); }
template <int offset>[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t addr, float32x4_t value) { return vstrwq_scatter_base_f32(addr, offset, value); }
template <int offset>[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t addr, float32x4_t value, mve_pred16_t p) { return vstrwq_scatter_base_p_f32(addr, offset, value, p); }
template <int offset>[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t *addr, float32x4_t value) { return vstrwq_scatter_base_wb_f32(addr, offset, value); }
template <int offset>[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t *addr, float32x4_t value, mve_pred16_t p) { return vstrwq_scatter_base_wb_p_f32(addr, offset, value, p); }
[[gnu::always_inline]] nce uint32x4_t convert_round_to_nearest_with_ties_away_from_zero(uint32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtaq_m_u32_f32(inactive, a, p); }
[[gnu::always_inline]] nce uint32x4_t convert_round_to_nearest_with_ties_to_even(uint32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtnq_m_u32_f32(inactive, a, p); }
[[gnu::always_inline]] nce uint32x4_t convert_round_toward_positive_infinity(uint32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtpq_m_u32_f32(inactive, a, p); }
[[gnu::always_inline]] nce uint32x4_t convert_round_toward_negative_infinity(uint32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtmq_m_u32_f32(inactive, a, p); }
template <> [[gnu::always_inline]] nce uint32x4_t convert(uint32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtq_m_u32_f32(inactive, a, p); }
template <int imm6>[[gnu::always_inline]] nce uint32x4_t convert(uint32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vcvtq_m_n_u32_f32(inactive, a, imm6, p); }
template <int offset>[[gnu::always_inline]] nce float32x4_t load_word_gather_base(uint32x4_t *addr, mve_pred16_t p) { return vldrwq_gather_base_wb_z_f32(addr, offset, p); }
template <> [[gnu::always_inline]] nce float32x4_t convert(uint32x4_t a, mve_pred16_t p) { return vcvtq_x_f32_u32(a, p); }
template <int imm6>[[gnu::always_inline]] nce float32x4_t convert(uint32x4_t a, mve_pred16_t p) { return vcvtq_x_n_f32_u32(a, imm6, p); }
[[gnu::always_inline]] nce float16x8_t reverse_32bit(float16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vrev32q_m_f16(inactive, a, p); }
[[gnu::always_inline]] nce float16x8_t reverse_64bit(float16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vrev64q_m_f16(inactive, a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(float16x8_t a, float16x8_t b) { return vcmpeqq_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmpeqq_m_f16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(float16x8_t a, float16x8_t b) { return vcmpneq_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmpneq_m_f16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(float16x8_t a, float16x8_t b) { return vcmpgeq_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmpgeq_m_f16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(float16x8_t a, float16x8_t b) { return vcmpgtq_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmpgtq_m_f16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(float16x8_t a, float16x8_t b) { return vcmpleq_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmpleq_m_f16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(float16x8_t a, float16x8_t b) { return vcmpltq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t min(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vminnmq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t max(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vmaxnmq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmpltq_m_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t min(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vminnmq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t min_reduce_add(float16x8_t a, float16x8_t b) { return vminnmaq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t min_reduce_add(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vminnmaq_m_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t max(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vmaxnmq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t max_add(float16x8_t a, float16x8_t b) { return vmaxnmaq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t max_add(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vmaxnmaq_m_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t reverse_32bit(float16x8_t a, mve_pred16_t p) { return vrev32q_x_f16(a, p); }
[[gnu::always_inline]] nce float16x8_t reverse_64bit(float16x8_t a, mve_pred16_t p) { return vrev64q_x_f16(a, p); }
[[gnu::always_inline]] nce float16x8_t duplicate(float16x8_t inactive, float16_t a, mve_pred16_t p) { return vdupq_m_n_f16(inactive, a, p); }
[[gnu::always_inline]] nce float16x8_t uninitialized(float16x8_t t) { return vuninitializedq(t); }
[[gnu::always_inline]] nce float16x8_t subtract_absolute(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vabdq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t add(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vaddq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vmulq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t subtract(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vsubq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t subtract_absolute(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vabdq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t abs(float16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vabsq_m_f16(inactive, a, p); }
[[gnu::always_inline]] nce float16x8_t add(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vaddq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vmulq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t subtract(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vsubq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t add(float16x8_t inactive, float16x8_t a, float16_t b, mve_pred16_t p) { return vaddq_m_n_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t inactive, float16x8_t a, float16_t b, mve_pred16_t p) { return vmulq_m_n_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply_add_scalar_fused(float16x8_t m1, float16x8_t m2, float16_t add) { return vfmasq_n_f16(m1, m2, add); }
[[gnu::always_inline]] nce float16x8_t multiply_add_scalar_fused(float16x8_t m1, float16x8_t m2, float16_t add, mve_pred16_t p) { return vfmasq_m_n_f16(m1, m2, add, p); }
[[gnu::always_inline]] nce float16x8_t subtract(float16x8_t inactive, float16x8_t a, float16_t b, mve_pred16_t p) { return vsubq_m_n_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t abs(float16x8_t a, mve_pred16_t p) { return vabsq_x_f16(a, p); }
[[gnu::always_inline]] nce float16x8_t add(float16x8_t a, float16_t b) { return vaddq_n_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t add(float16x8_t a, float16_t b, mve_pred16_t p) { return vaddq_x_n_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply(float16x8_t a, float16_t b, mve_pred16_t p) { return vmulq_x_n_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t subtract(float16x8_t a, float16_t b) { return vsubq_n_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t subtract(float16x8_t a, float16_t b, mve_pred16_t p) { return vsubq_x_n_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t round(float16x8_t a) { return vrndq_f16(a); }
[[gnu::always_inline]] nce float16x8_t round(float16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vrndq_m_f16(inactive, a, p); }
[[gnu::always_inline]] nce float16x8_t round(float16x8_t a, mve_pred16_t p) { return vrndq_x_f16(a, p); }
[[gnu::always_inline]] nce float16x8_t round_to_nearest_with_ties_to_even(float16x8_t a) { return vrndnq_f16(a); }
[[gnu::always_inline]] nce float16x8_t round_to_nearest_with_ties_to_even(float16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vrndnq_m_f16(inactive, a, p); }
[[gnu::always_inline]] nce float16x8_t round_toward_negative_infinity(float16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vrndmq_m_f16(inactive, a, p); }
[[gnu::always_inline]] nce float16x8_t round_toward_positive_infinity(float16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vrndpq_m_f16(inactive, a, p); }
[[gnu::always_inline]] nce float16x8_t round_to_nearest_with_ties_to_even(float16x8_t a, mve_pred16_t p) { return vrndnq_x_f16(a, p); }
[[gnu::always_inline]] nce float16x8_t round_toward_negative_infinity(float16x8_t a) { return vrndmq_f16(a); }
[[gnu::always_inline]] nce float16x8_t round_toward_negative_infinity(float16x8_t a, mve_pred16_t p) { return vrndmq_x_f16(a, p); }
[[gnu::always_inline]] nce float16x8_t round_toward_positive_infinity(float16x8_t a) { return vrndpq_f16(a); }
[[gnu::always_inline]] nce float16x8_t bitwise_and(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vandq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t round_toward_positive_infinity(float16x8_t a, mve_pred16_t p) { return vrndpq_x_f16(a, p); }
[[gnu::always_inline]] nce float16x8_t round_to_nearest_with_ties_away_from_zero(float16x8_t a) { return vrndaq_f16(a); }
[[gnu::always_inline]] nce float16x8_t round_to_nearest_with_ties_away_from_zero(float16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vrndaq_m_f16(inactive, a, p); }
[[gnu::always_inline]] nce float16x8_t round_to_nearest_with_ties_away_from_zero(float16x8_t a, mve_pred16_t p) { return vrndaq_x_f16(a, p); }
[[gnu::always_inline]] nce float16x8_t round_inexact(float16x8_t a) { return vrndxq_f16(a); }
[[gnu::always_inline]] nce float16x8_t convert_bottom(float16x8_t a, float32x4_t b) { return vcvtbq_f16_f32(a, b); }
[[gnu::always_inline]] nce float16x8_t convert_bottom(float16x8_t a, float32x4_t b, mve_pred16_t p) { return vcvtbq_m_f16_f32(a, b, p); }
[[gnu::always_inline]] nce float16x8_t convert_top(float16x8_t a, float32x4_t b) { return vcvttq_f16_f32(a, b); }
template <> [[gnu::always_inline]] nce int16x8_t convert_round_to_nearest_with_ties_away_from_zero(float16x8_t a, mve_pred16_t p) { return vcvtaq_x_s16_f16(a, p); }
template <> [[gnu::always_inline]] nce uint16x8_t convert_round_to_nearest_with_ties_away_from_zero(float16x8_t a, mve_pred16_t p) { return vcvtaq_x_u16_f16(a, p); }
template <> [[gnu::always_inline]] nce int16x8_t convert_round_to_nearest_with_ties_to_even(float16x8_t a, mve_pred16_t p) { return vcvtnq_x_s16_f16(a, p); }
template <> [[gnu::always_inline]] nce uint16x8_t convert_round_to_nearest_with_ties_to_even(float16x8_t a, mve_pred16_t p) { return vcvtnq_x_u16_f16(a, p); }
template <> [[gnu::always_inline]] nce int16x8_t convert_round_toward_positive_infinity(float16x8_t a, mve_pred16_t p) { return vcvtpq_x_s16_f16(a, p); }
template <> [[gnu::always_inline]] nce uint16x8_t convert_round_toward_positive_infinity(float16x8_t a, mve_pred16_t p) { return vcvtpq_x_u16_f16(a, p); }
template <> [[gnu::always_inline]] nce int16x8_t convert_round_toward_negative_infinity(float16x8_t a, mve_pred16_t p) { return vcvtmq_x_s16_f16(a, p); }
template <> [[gnu::always_inline]] nce uint16x8_t convert_round_toward_negative_infinity(float16x8_t a, mve_pred16_t p) { return vcvtmq_x_u16_f16(a, p); }
[[gnu::always_inline]] nce float32x4_t convert_bottom(float16x8_t a) { return vcvtbq_f32_f16(a); }
[[gnu::always_inline]] nce float32x4_t convert_bottom(float16x8_t a, mve_pred16_t p) { return vcvtbq_x_f32_f16(a, p); }
[[gnu::always_inline]] nce float32x4_t convert_top(float16x8_t a) { return vcvttq_f32_f16(a); }
template <> [[gnu::always_inline]] nce float16x8_t convert(float16x8_t inactive, uint16x8_t a, mve_pred16_t p) { return vcvtq_m_f16_u16(inactive, a, p); }
template <int imm6>[[gnu::always_inline]] nce float16x8_t convert(float16x8_t inactive, uint16x8_t a, mve_pred16_t p) { return vcvtq_m_n_f16_u16(inactive, a, imm6, p); }
template <> [[gnu::always_inline]] nce float16x8_t convert(float16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vcvtq_m_f16_s16(inactive, a, p); }
template <int imm6>[[gnu::always_inline]] nce float16x8_t convert(float16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vcvtq_m_n_f16_s16(inactive, a, imm6, p); }
[[gnu::always_inline]] nce float16x8_t bitwise_clear(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vbicq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t bitwise_xor(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return veorq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t bitwise_or_not(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vornq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t complex_add_rotate_90(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcaddq_rot90_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t bitwise_xor(float16x8_t a, float16x8_t b, mve_pred16_t p) { return veorq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t bitwise_or_not(float16x8_t a, float16x8_t b) { return vornq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t bitwise_or_not(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vornq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t bitwise_or(float16x8_t a, float16x8_t b) { return vorrq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t bitwise_or(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vorrq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t complex_add_rotate_270(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcaddq_rot270_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add(float16x8_t a, float16x8_t b, float16x8_t c, mve_pred16_t p) { return vcmlaq_m_f16(a, b, c, p); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_90(float16x8_t a, float16x8_t b, float16x8_t c, mve_pred16_t p) { return vcmlaq_rot90_m_f16(a, b, c, p); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_180(float16x8_t a, float16x8_t b, float16x8_t c, mve_pred16_t p) { return vcmlaq_rot180_m_f16(a, b, c, p); }
[[gnu::always_inline]] nce float16x8_t complex_multiply_add_rotate_270(float16x8_t a, float16x8_t b, float16x8_t c, mve_pred16_t p) { return vcmlaq_rot270_m_f16(a, b, c, p); }
[[gnu::always_inline]] nce float16x8_t multiply_complex(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmulq_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply_complex_rotate_90(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmulq_rot90_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply_complex_rotate_180(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmulq_rot180_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t round_inexact(float16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vrndxq_m_f16(inactive, a, p); }
[[gnu::always_inline]] nce float16x8_t bitwise_clear(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vbicq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t negate(float16x8_t inactive, float16x8_t a, mve_pred16_t p) { return vnegq_m_f16(inactive, a, p); }
[[gnu::always_inline]] nce float16x8_t bitwise_and(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vandq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t bitwise_or(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vorrq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t complex_add_rotate_90(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcaddq_rot90_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t complex_add_rotate_270(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcaddq_rot270_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply_complex(float16x8_t a, float16x8_t b) { return vcmulq_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply_complex_rotate_90(float16x8_t a, float16x8_t b) { return vcmulq_rot90_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply_complex_rotate_180(float16x8_t a, float16x8_t b) { return vcmulq_rot180_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply_complex_rotate_270(float16x8_t a, float16x8_t b) { return vcmulq_rot270_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t multiply_complex_rotate_270(float16x8_t inactive, float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmulq_rot270_m_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply_complex(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmulq_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply_complex_rotate_90(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmulq_rot90_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply_complex_rotate_180(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmulq_rot180_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t multiply_complex_rotate_270(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vcmulq_rot270_x_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t predicate_select(float16x8_t a, float16x8_t b, mve_pred16_t p) { return vpselq_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t bit_reverse_shift_right(float16x8_t inactive, float16x8_t a, int32_t b, mve_pred16_t p) { return vbrsrq_m_n_f16(inactive, a, b, p); }
[[gnu::always_inline]] nce float16x8_t convert_top(float16x8_t a, float32x4_t b, mve_pred16_t p) { return vcvttq_m_f16_f32(a, b, p); }
[[gnu::always_inline]] nce float16x8_t round_inexact(float16x8_t a, mve_pred16_t p) { return vrndxq_x_f16(a, p); }
[[gnu::always_inline]] nce float16x8_t negate(float16x8_t a, mve_pred16_t p) { return vnegq_x_f16(a, p); }
[[gnu::always_inline]] nce float32x4_t convert_top(float16x8_t a, mve_pred16_t p) { return vcvttq_x_f32_f16(a, p); }
template <> [[gnu::always_inline]] nce int16x8_t convert(float16x8_t a, mve_pred16_t p) { return vcvtq_x_s16_f16(a, p); }
template <> [[gnu::always_inline]] nce uint16x8_t convert(float16x8_t a, mve_pred16_t p) { return vcvtq_x_u16_f16(a, p); }
template <int imm6>[[gnu::always_inline]] nce int16x8_t convert(float16x8_t a, mve_pred16_t p) { return vcvtq_x_n_s16_f16(a, imm6, p); }
template <int imm6>[[gnu::always_inline]] nce uint16x8_t convert(float16x8_t a, mve_pred16_t p) { return vcvtq_x_n_u16_f16(a, imm6, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(float16x8_t a, float16_t b) { return vcmpeqq_n_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(float16x8_t a, float16_t b, mve_pred16_t p) { return vcmpeqq_m_n_f16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(float16x8_t a, float16_t b) { return vcmpneq_n_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(float16x8_t a, float16_t b, mve_pred16_t p) { return vcmpneq_m_n_f16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(float16x8_t a, float16_t b) { return vcmpgeq_n_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(float16x8_t a, float16_t b, mve_pred16_t p) { return vcmpgeq_m_n_f16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(float16x8_t a, float16_t b) { return vcmpgtq_n_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(float16x8_t a, float16_t b, mve_pred16_t p) { return vcmpgtq_m_n_f16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(float16x8_t a, float16_t b) { return vcmpleq_n_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(float16x8_t a, float16_t b, mve_pred16_t p) { return vcmpleq_m_n_f16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(float16x8_t a, float16_t b) { return vcmpltq_n_f16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(float16x8_t a, float16_t b, mve_pred16_t p) { return vcmpltq_m_n_f16(a, b, p); }
[[gnu::always_inline]] nce float16x8_t bit_reverse_shift_right(float16x8_t a, int32_t b) { return vbrsrq_n_f16(a, b); }
[[gnu::always_inline]] nce float16x8_t bit_reverse_shift_right(float16x8_t a, int32_t b, mve_pred16_t p) { return vbrsrq_x_n_f16(a, b, p); }
template <> [[gnu::always_inline]] nce float32x4_t convert(float32x4_t inactive, int32x4_t a, mve_pred16_t p) { return vcvtq_m_f32_s32(inactive, a, p); }
template <int imm6>[[gnu::always_inline]] nce float32x4_t convert(float32x4_t inactive, int32x4_t a, mve_pred16_t p) { return vcvtq_m_n_f32_s32(inactive, a, imm6, p); }
template <> [[gnu::always_inline]] nce float32x4_t convert(float32x4_t inactive, uint32x4_t a, mve_pred16_t p) { return vcvtq_m_f32_u32(inactive, a, p); }
template <int imm6>[[gnu::always_inline]] nce float32x4_t convert(float32x4_t inactive, uint32x4_t a, mve_pred16_t p) { return vcvtq_m_n_f32_u32(inactive, a, imm6, p); }
[[gnu::always_inline]] nce float32x4_t convert_bottom(float32x4_t inactive, float16x8_t a, mve_pred16_t p) { return vcvtbq_m_f32_f16(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t convert_top(float32x4_t inactive, float16x8_t a, mve_pred16_t p) { return vcvttq_m_f32_f16(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t reverse_64bit(float32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vrev64q_m_f32(inactive, a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(float32x4_t a, float32x4_t b) { return vcmpeqq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t reverse_64bit(float32x4_t a, mve_pred16_t p) { return vrev64q_x_f32(a, p); }
[[gnu::always_inline]] nce float32x4_t duplicate(float32x4_t inactive, float32_t a, mve_pred16_t p) { return vdupq_m_n_f32(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t uninitialized(float32x4_t t) { return vuninitializedq(t); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmpeqq_m_f32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(float32x4_t a, float32x4_t b) { return vcmpneq_f32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmpneq_m_f32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(float32x4_t a, float32x4_t b) { return vcmpgeq_f32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmpgeq_m_f32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(float32x4_t a, float32x4_t b) { return vcmpgtq_f32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(float32x4_t a, float32x4_t b) { return vcmpleq_f32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmpleq_m_f32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(float32x4_t a, float32x4_t b) { return vcmpltq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t min(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vminnmq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmpltq_m_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t min(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vminnmq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t min_reduce_add(float32x4_t a, float32x4_t b) { return vminnmaq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t max(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vmaxnmq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmpgtq_m_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t min_reduce_add(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vminnmaq_m_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t max(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vmaxnmq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t max_add(float32x4_t a, float32x4_t b) { return vmaxnmaq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t subtract_absolute(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vabdq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t add(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vaddq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vmulq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t subtract(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vsubq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t bitwise_clear(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vbicq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t bitwise_and(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vandq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t bitwise_xor(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return veorq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t bitwise_or_not(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vornq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t complex_add_rotate_90(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcaddq_rot90_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t bitwise_xor(float32x4_t a, float32x4_t b, mve_pred16_t p) { return veorq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t bitwise_or_not(float32x4_t a, float32x4_t b) { return vornq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t bitwise_or_not(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vornq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t bitwise_or(float32x4_t a, float32x4_t b) { return vorrq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t bitwise_or(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vorrq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t complex_add_rotate_270(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcaddq_rot270_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add(float32x4_t a, float32x4_t b, float32x4_t c, mve_pred16_t p) { return vcmlaq_m_f32(a, b, c, p); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_90(float32x4_t a, float32x4_t b, float32x4_t c, mve_pred16_t p) { return vcmlaq_rot90_m_f32(a, b, c, p); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_180(float32x4_t a, float32x4_t b, float32x4_t c, mve_pred16_t p) { return vcmlaq_rot180_m_f32(a, b, c, p); }
[[gnu::always_inline]] nce float32x4_t complex_multiply_add_rotate_270(float32x4_t a, float32x4_t b, float32x4_t c, mve_pred16_t p) { return vcmlaq_rot270_m_f32(a, b, c, p); }
[[gnu::always_inline]] nce float32x4_t multiply_complex(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmulq_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply_complex_rotate_90(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmulq_rot90_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply_complex_rotate_180(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmulq_rot180_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t max_add(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vmaxnmaq_m_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t subtract_absolute(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vabdq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t abs(float32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vabsq_m_f32(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t add(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vaddq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vmulq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t subtract(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vsubq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t round(float32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vrndq_m_f32(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t round_to_nearest_with_ties_to_even(float32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vrndnq_m_f32(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t round_toward_negative_infinity(float32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vrndmq_m_f32(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t round_toward_positive_infinity(float32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vrndpq_m_f32(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t round_to_nearest_with_ties_away_from_zero(float32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vrndaq_m_f32(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t round_inexact(float32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vrndxq_m_f32(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t bitwise_clear(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vbicq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t negate(float32x4_t inactive, float32x4_t a, mve_pred16_t p) { return vnegq_m_f32(inactive, a, p); }
[[gnu::always_inline]] nce float32x4_t bitwise_and(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vandq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t bitwise_or(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vorrq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t complex_add_rotate_90(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcaddq_rot90_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t complex_add_rotate_270(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcaddq_rot270_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply_complex(float32x4_t a, float32x4_t b) { return vcmulq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t multiply_complex_rotate_90(float32x4_t a, float32x4_t b) { return vcmulq_rot90_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t multiply_complex_rotate_180(float32x4_t a, float32x4_t b) { return vcmulq_rot180_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t multiply_complex_rotate_270(float32x4_t a, float32x4_t b) { return vcmulq_rot270_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t multiply_complex_rotate_270(float32x4_t inactive, float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmulq_rot270_m_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply_complex(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmulq_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply_complex_rotate_90(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmulq_rot90_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply_complex_rotate_180(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmulq_rot180_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply_complex_rotate_270(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vcmulq_rot270_x_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t predicate_select(float32x4_t a, float32x4_t b, mve_pred16_t p) { return vpselq_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t add(float32x4_t inactive, float32x4_t a, float32_t b, mve_pred16_t p) { return vaddq_m_n_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t inactive, float32x4_t a, float32_t b, mve_pred16_t p) { return vmulq_m_n_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply_add_scalar_fused(float32x4_t m1, float32x4_t m2, float32_t add) { return vfmasq_n_f32(m1, m2, add); }
[[gnu::always_inline]] nce float32x4_t multiply_add_scalar_fused(float32x4_t m1, float32x4_t m2, float32_t add, mve_pred16_t p) { return vfmasq_m_n_f32(m1, m2, add, p); }
[[gnu::always_inline]] nce float32x4_t subtract(float32x4_t inactive, float32x4_t a, float32_t b, mve_pred16_t p) { return vsubq_m_n_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t bit_reverse_shift_right(float32x4_t inactive, float32x4_t a, int32_t b, mve_pred16_t p) { return vbrsrq_m_n_f32(inactive, a, b, p); }
[[gnu::always_inline]] nce float32x4_t abs(float32x4_t a, mve_pred16_t p) { return vabsq_x_f32(a, p); }
[[gnu::always_inline]] nce float32x4_t round(float32x4_t a, mve_pred16_t p) { return vrndq_x_f32(a, p); }
[[gnu::always_inline]] nce float32x4_t round_to_nearest_with_ties_to_even(float32x4_t a, mve_pred16_t p) { return vrndnq_x_f32(a, p); }
[[gnu::always_inline]] nce float32x4_t round_toward_negative_infinity(float32x4_t a, mve_pred16_t p) { return vrndmq_x_f32(a, p); }
[[gnu::always_inline]] nce float32x4_t round_toward_positive_infinity(float32x4_t a, mve_pred16_t p) { return vrndpq_x_f32(a, p); }
[[gnu::always_inline]] nce float32x4_t round_to_nearest_with_ties_away_from_zero(float32x4_t a, mve_pred16_t p) { return vrndaq_x_f32(a, p); }
[[gnu::always_inline]] nce float32x4_t round_inexact(float32x4_t a, mve_pred16_t p) { return vrndxq_x_f32(a, p); }
[[gnu::always_inline]] nce float32x4_t negate(float32x4_t a, mve_pred16_t p) { return vnegq_x_f32(a, p); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_to_nearest_with_ties_away_from_zero(float32x4_t a, mve_pred16_t p) { return vcvtaq_x_s32_f32(a, p); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_to_nearest_with_ties_away_from_zero(float32x4_t a, mve_pred16_t p) { return vcvtaq_x_u32_f32(a, p); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_to_nearest_with_ties_to_even(float32x4_t a, mve_pred16_t p) { return vcvtnq_x_s32_f32(a, p); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_to_nearest_with_ties_to_even(float32x4_t a, mve_pred16_t p) { return vcvtnq_x_u32_f32(a, p); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_toward_positive_infinity(float32x4_t a, mve_pred16_t p) { return vcvtpq_x_s32_f32(a, p); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_toward_positive_infinity(float32x4_t a, mve_pred16_t p) { return vcvtpq_x_u32_f32(a, p); }
template <> [[gnu::always_inline]] nce int32x4_t convert_round_toward_negative_infinity(float32x4_t a, mve_pred16_t p) { return vcvtmq_x_s32_f32(a, p); }
template <> [[gnu::always_inline]] nce uint32x4_t convert_round_toward_negative_infinity(float32x4_t a, mve_pred16_t p) { return vcvtmq_x_u32_f32(a, p); }
template <> [[gnu::always_inline]] nce int32x4_t convert(float32x4_t a, mve_pred16_t p) { return vcvtq_x_s32_f32(a, p); }
template <> [[gnu::always_inline]] nce uint32x4_t convert(float32x4_t a, mve_pred16_t p) { return vcvtq_x_u32_f32(a, p); }
template <int imm6>[[gnu::always_inline]] nce int32x4_t convert(float32x4_t a, mve_pred16_t p) { return vcvtq_x_n_s32_f32(a, imm6, p); }
template <int imm6>[[gnu::always_inline]] nce uint32x4_t convert(float32x4_t a, mve_pred16_t p) { return vcvtq_x_n_u32_f32(a, imm6, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(float32x4_t a, float32_t b) { return vcmpeqq_n_f32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(float32x4_t a, float32_t b, mve_pred16_t p) { return vcmpeqq_m_n_f32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(float32x4_t a, float32_t b) { return vcmpneq_n_f32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(float32x4_t a, float32_t b, mve_pred16_t p) { return vcmpneq_m_n_f32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(float32x4_t a, float32_t b) { return vcmpgeq_n_f32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(float32x4_t a, float32_t b, mve_pred16_t p) { return vcmpgeq_m_n_f32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(float32x4_t a, float32_t b) { return vcmpgtq_n_f32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(float32x4_t a, float32_t b, mve_pred16_t p) { return vcmpgtq_m_n_f32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(float32x4_t a, float32_t b) { return vcmpleq_n_f32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(float32x4_t a, float32_t b, mve_pred16_t p) { return vcmpleq_m_n_f32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(float32x4_t a, float32_t b) { return vcmpltq_n_f32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(float32x4_t a, float32_t b, mve_pred16_t p) { return vcmpltq_m_n_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t add(float32x4_t a, float32_t b) { return vaddq_n_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t add(float32x4_t a, float32_t b, mve_pred16_t p) { return vaddq_x_n_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t a, float32_t b, mve_pred16_t p) { return vmulq_x_n_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t subtract(float32x4_t a, float32_t b) { return vsubq_n_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t subtract(float32x4_t a, float32_t b, mve_pred16_t p) { return vsubq_x_n_f32(a, b, p); }
[[gnu::always_inline]] nce float32x4_t bit_reverse_shift_right(float32x4_t a, int32_t b) { return vbrsrq_n_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t bit_reverse_shift_right(float32x4_t a, int32_t b, mve_pred16_t p) { return vbrsrq_x_n_f32(a, b, p); }
template <> [[gnu::always_inline]] nce float16x8_t create(uint64_t a, uint64_t b) { return vcreateq_f16(a, b); }
template <> [[gnu::always_inline]] nce float32x4_t create(uint64_t a, uint64_t b) { return vcreateq_f32(a, b); }
[[gnu::always_inline]] nce float16x8_t duplicate(float16_t a, mve_pred16_t p) { return vdupq_x_n_f16(a, p); }
[[gnu::always_inline]] nce float32x4_t duplicate(float32_t a, mve_pred16_t p) { return vdupq_x_n_f32(a, p); }
template <> [[gnu::always_inline]] nce float16x8_t uninitialized() { return vuninitializedq_f16(); }
template <> [[gnu::always_inline]] nce float32x4_t uninitialized() { return vuninitializedq_f32(); }
[[gnu::always_inline]] nce float16_t min_reduce_min(float16_t a, float16x8_t b) { return vminnmvq_f16(a, b); }
[[gnu::always_inline]] nce float32_t min_reduce_min(float32_t a, float32x4_t b) { return vminnmvq_f32(a, b); }
[[gnu::always_inline]] nce float16_t min_reduce_min(float16_t a, float16x8_t b, mve_pred16_t p) { return vminnmvq_p_f16(a, b, p); }
[[gnu::always_inline]] nce float32_t min_reduce_min(float32_t a, float32x4_t b, mve_pred16_t p) { return vminnmvq_p_f32(a, b, p); }
[[gnu::always_inline]] nce float16_t min_reduce_min_add(float16_t a, float16x8_t b) { return vminnmavq_f16(a, b); }
[[gnu::always_inline]] nce float32_t min_reduce_min_add(float32_t a, float32x4_t b) { return vminnmavq_f32(a, b); }
[[gnu::always_inline]] nce float16_t min_reduce_min_add(float16_t a, float16x8_t b, mve_pred16_t p) { return vminnmavq_p_f16(a, b, p); }
[[gnu::always_inline]] nce float32_t min_reduce_min_add(float32_t a, float32x4_t b, mve_pred16_t p) { return vminnmavq_p_f32(a, b, p); }
[[gnu::always_inline]] nce float16_t max_reduce_max(float16_t a, float16x8_t b) { return vmaxnmvq_f16(a, b); }
[[gnu::always_inline]] nce float32_t max_reduce_max(float32_t a, float32x4_t b) { return vmaxnmvq_f32(a, b); }
[[gnu::always_inline]] nce float16_t max_reduce_max(float16_t a, float16x8_t b, mve_pred16_t p) { return vmaxnmvq_p_f16(a, b, p); }
[[gnu::always_inline]] nce float32_t max_reduce_max(float32_t a, float32x4_t b, mve_pred16_t p) { return vmaxnmvq_p_f32(a, b, p); }
[[gnu::always_inline]] nce float16_t max_reduce_max_add(float16_t a, float16x8_t b) { return vmaxnmavq_f16(a, b); }
[[gnu::always_inline]] nce float32_t max_reduce_max_add(float32_t a, float32x4_t b) { return vmaxnmavq_f32(a, b); }
[[gnu::always_inline]] nce float16_t max_reduce_max_add(float16_t a, float16x8_t b, mve_pred16_t p) { return vmaxnmavq_p_f16(a, b, p); }
[[gnu::always_inline]] nce float32_t max_reduce_max_add(float32_t a, float32x4_t b, mve_pred16_t p) { return vmaxnmavq_p_f32(a, b, p); }
[[gnu::always_inline]] inline float16x8x2_t load2(float16_t const *addr) { return vld2q_f16(addr); }
[[gnu::always_inline]] inline float32x4x2_t load2(float32_t const *addr) { return vld2q_f32(addr); }
[[gnu::always_inline]] inline float16x8x4_t load4(float16_t const *addr) { return vld4q_f16(addr); }
[[gnu::always_inline]] inline float32x4x4_t load4(float32_t const *addr) { return vld4q_f32(addr); }
[[gnu::always_inline]] inline float16x8_t load1(float16_t const *base, mve_pred16_t p) { return vld1q_z_f16(base, p); }
[[gnu::always_inline]] inline float32x4_t load1(float32_t const *base, mve_pred16_t p) { return vld1q_z_f32(base, p); }
[[gnu::always_inline]] nce float16x8_t load_halfword(float16_t const *base) { return vldrhq_f16(base); }
[[gnu::always_inline]] nce float16x8_t load_halfword(float16_t const *base, mve_pred16_t p) { return vldrhq_z_f16(base, p); }
[[gnu::always_inline]] nce float32x4_t load_word(float32_t const *base) { return vldrwq_f32(base); }
[[gnu::always_inline]] nce float32x4_t load_word(float32_t const *base, mve_pred16_t p) { return vldrwq_z_f32(base, p); }
[[gnu::always_inline]] nce float16x8_t load_halfword_gather_offset(float16_t const *base, uint16x8_t offset) { return vldrhq_gather_offset_f16(base, offset); }
[[gnu::always_inline]] nce float16x8_t load_halfword_gather_offset(float16_t const *base, uint16x8_t offset, mve_pred16_t p) { return vldrhq_gather_offset_z_f16(base, offset, p); }
[[gnu::always_inline]] nce float16x8_t load_halfword_gather_shifted_offset(float16_t const *base, uint16x8_t offset) { return vldrhq_gather_shifted_offset_f16(base, offset); }
[[gnu::always_inline]] nce float16x8_t load_halfword_gather_shifted_offset(float16_t const *base, uint16x8_t offset, mve_pred16_t p) { return vldrhq_gather_shifted_offset_z_f16(base, offset, p); }
[[gnu::always_inline]] nce float32x4_t load_word_gather_offset(float32_t const *base, uint32x4_t offset) { return vldrwq_gather_offset_f32(base, offset); }
[[gnu::always_inline]] nce float32x4_t load_word_gather_offset(float32_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrwq_gather_offset_z_f32(base, offset, p); }
[[gnu::always_inline]] nce float32x4_t load_word_gather_shifted_offset(float32_t const *base, uint32x4_t offset) { return vldrwq_gather_shifted_offset_f32(base, offset); }
[[gnu::always_inline]] nce float32x4_t load_word_gather_shifted_offset(float32_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrwq_gather_shifted_offset_z_f32(base, offset, p); }
[[gnu::always_inline]] inline void store2(float16_t *addr, float16x8x2_t value) { return vst2q_f16(addr, value); }
[[gnu::always_inline]] inline void store2(float32_t *addr, float32x4x2_t value) { return vst2q_f32(addr, value); }
[[gnu::always_inline]] inline void store4(float16_t *addr, float16x8x4_t value) { return vst4q_f16(addr, value); }
[[gnu::always_inline]] inline void store4(float32_t *addr, float32x4x4_t value) { return vst4q_f32(addr, value); }
[[gnu::always_inline]] inline void store1(float16_t *base, float16x8_t value, mve_pred16_t p) { return vst1q_p_f16(base, value, p); }
[[gnu::always_inline]] inline void store1(float32_t *base, float32x4_t value, mve_pred16_t p) { return vst1q_p_f32(base, value, p); }
[[gnu::always_inline]] nce void store_halfword(float16_t *base, float16x8_t value) { return vstrhq_f16(base, value); }
[[gnu::always_inline]] nce void store_halfword(float16_t *base, float16x8_t value, mve_pred16_t p) { return vstrhq_p_f16(base, value, p); }
[[gnu::always_inline]] nce void store_word(float32_t *base, float32x4_t value) { return vstrwq_f32(base, value); }
[[gnu::always_inline]] nce void store_word(float32_t *base, float32x4_t value, mve_pred16_t p) { return vstrwq_p_f32(base, value, p); }
[[gnu::always_inline]] nce void store_halfword_scatter_offset(float16_t *base, uint16x8_t offset, float16x8_t value) { return vstrhq_scatter_offset_f16(base, offset, value); }
[[gnu::always_inline]] nce void store_halfword_scatter_offset(float16_t *base, uint16x8_t offset, float16x8_t value, mve_pred16_t p) { return vstrhq_scatter_offset_p_f16(base, offset, value, p); }
[[gnu::always_inline]] nce void store_halfword_scatter_shifted_offset(float16_t *base, uint16x8_t offset, float16x8_t value) { return vstrhq_scatter_shifted_offset_f16(base, offset, value); }
[[gnu::always_inline]] nce void store_halfword_scatter_shifted_offset(float16_t *base, uint16x8_t offset, float16x8_t value, mve_pred16_t p) { return vstrhq_scatter_shifted_offset_p_f16(base, offset, value, p); }
[[gnu::always_inline]] nce void store_word_scatter_offset(float32_t *base, uint32x4_t offset, float32x4_t value) { return vstrwq_scatter_offset_f32(base, offset, value); }
[[gnu::always_inline]] nce void store_word_scatter_offset(float32_t *base, uint32x4_t offset, float32x4_t value, mve_pred16_t p) { return vstrwq_scatter_offset_p_f32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_word_scatter_shifted_offset(float32_t *base, uint32x4_t offset, float32x4_t value) { return vstrwq_scatter_shifted_offset_f32(base, offset, value); }
[[gnu::always_inline]] nce void store_word_scatter_shifted_offset(float32_t *base, uint32x4_t offset, float32x4_t value, mve_pred16_t p) { return vstrwq_scatter_shifted_offset_p_f32(base, offset, value, p); }
// clang-format on
}  // namespace mve
#endif
#undef nce
