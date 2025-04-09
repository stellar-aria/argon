#pragma once
#include <arm_mve.h>
#include "neon_int.hpp"
#ifdef __cplusplus
#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

namespace helium {
// clang-format off
template <typename T> nce T create(uint64_t a, uint64_t b);
template <typename T> nce T decrement_duplicate(uint32_t a);
template <typename T> nce T decrement_duplicate(uint32_t *a);
template <typename T> nce T decrement_duplicate(uint32_t a, const int imm, mve_pred16_t p);
template <typename T> nce T decrement_duplicate(uint32_t *a, const int imm, mve_pred16_t p);
template <typename T> nce T decrement_wrap_duplicate(uint32_t a, uint32_t b);
template <typename T> nce T decrement_wrap_duplicate(uint32_t *a, uint32_t b);
template <typename T> nce T decrement_wrap_duplicate(uint32_t a, uint32_t b, const int imm, mve_pred16_t p);
template <typename T> nce T decrement_wrap_duplicate(uint32_t *a, uint32_t b, const int imm, mve_pred16_t p);
template <typename T> nce T increment_duplicate(uint32_t a);
template <typename T> nce T increment_duplicate(uint32_t *a);
template <typename T> nce T increment_duplicate(uint32_t a, const int imm, mve_pred16_t p);
template <typename T> nce T increment_duplicate(uint32_t *a, const int imm, mve_pred16_t p);
template <typename T> nce T increment_wrap_duplicate(uint32_t a, uint32_t b);
template <typename T> nce T increment_wrap_duplicate(uint32_t *a, uint32_t b);
template <typename T> nce T increment_wrap_duplicate(uint32_t a, uint32_t b, const int imm, mve_pred16_t p);
template <typename T> nce T increment_wrap_duplicate(uint32_t *a, uint32_t b, const int imm, mve_pred16_t p);
template <typename T> nce T uninitialized( void);
template <typename T> nce T load_byte(int8_t const *base);
template <typename T> nce T load_byte(uint8_t const *base);
template <typename T> nce T load_byte(int8_t const *base, mve_pred16_t p);
template <typename T> nce T load_byte(uint8_t const *base, mve_pred16_t p);
template <typename T> nce T load_halfword(int16_t const *base);
template <typename T> nce T load_halfword(uint16_t const *base);
template <typename T> nce T load_halfword(int16_t const *base, mve_pred16_t p);
template <typename T> nce T load_halfword(uint16_t const *base, mve_pred16_t p);
template <typename T> nce T load_word_gather_base(uint32x4_t addr);
template <typename T> nce T load_word_gather_base(uint32x4_t addr, const int offset, mve_pred16_t p);
template <typename T> nce T load_word_gather_base(uint32x4_t *addr);
template <typename T> nce T load_word_gather_base(uint32x4_t *addr, const int offset, mve_pred16_t p);
template <typename T> nce T load_doubleword_gather_base(uint64x2_t addr);
template <typename T> nce T load_doubleword_gather_base(uint64x2_t addr, const int offset, mve_pred16_t p);
template <typename T> nce T load_doubleword_gather_base(uint64x2_t *addr);
template <typename T> nce T load_doubleword_gather_base(uint64x2_t *addr, const int offset, mve_pred16_t p);
template <typename T> nce T create_tail_predicate(uint32_t a);
template <typename T> nce T create_tail_predicate(uint32_t a, mve_pred16_t p);
[[gnu::always_inline]] nce uint8x16_t reverse_16bit(uint8x16_t inactive, uint8x16_t a, mve_pred16_t p) { return vrev16q_m_u8(inactive, a, p); }
[[gnu::always_inline]] nce uint8x16_t reverse_32bit(uint8x16_t inactive, uint8x16_t a, mve_pred16_t p) { return vrev32q_m_u8(inactive, a, p); }
[[gnu::always_inline]] nce uint8x16_t reverse_64bit(uint8x16_t inactive, uint8x16_t a, mve_pred16_t p) { return vrev64q_m_u8(inactive, a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint8x16_t a, uint8x16_t b) { return vcmpeqq_u8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vcmpeqq_m_u8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint8x16_t a, uint8x16_t b) { return vcmpneq_u8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vcmpneq_m_u8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint8x16_t a, uint8x16_t b) { return vcmpcsq_u8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vcmpcsq_m_u8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint8x16_t a, uint8x16_t b) { return vcmphiq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t min(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vminq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t max(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmaxq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t subtract_absolute(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vabdq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vaddq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vcmphiq_m_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t min(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vminq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t max(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmaxq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t subtract_absolute(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vabdq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vaddq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add(uint8x16_t inactive, uint8x16_t a, uint8_t b, mve_pred16_t p) { return vaddq_m_n_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t minimum_absolute(uint8x16_t a, int8x16_t b) { return vminaq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t minimum_absolute(uint8x16_t a, int8x16_t b, mve_pred16_t p) { return vminaq_m_s8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t maximum_absolute(uint8x16_t a, int8x16_t b) { return vmaxaq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t maximum_absolute(uint8x16_t a, int8x16_t b, mve_pred16_t p) { return vmaxaq_m_s8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t reverse_16bit(uint8x16_t a, mve_pred16_t p) { return vrev16q_x_u8(a, p); }
[[gnu::always_inline]] nce uint8x16_t reverse_32bit(uint8x16_t a, mve_pred16_t p) { return vrev32q_x_u8(a, p); }
[[gnu::always_inline]] nce uint8x16_t reverse_64bit(uint8x16_t a, mve_pred16_t p) { return vrev64q_x_u8(a, p); }
[[gnu::always_inline]] nce uint8x16_t decrement_duplicate(uint8x16_t inactive, uint32_t a, const int imm, mve_pred16_t p) { return vddupq_m_n_u8(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t decrement_duplicate(uint8x16_t inactive, uint32_t *a, const int imm, mve_pred16_t p) { return vddupq_m_wb_u8(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t decrement_wrap_duplicate(uint8x16_t inactive, uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_m_n_u8(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint8x16_t decrement_wrap_duplicate(uint8x16_t inactive, uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_m_wb_u8(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint8x16_t increment_duplicate(uint8x16_t inactive, uint32_t a, const int imm, mve_pred16_t p) { return vidupq_m_n_u8(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t increment_duplicate(uint8x16_t inactive, uint32_t *a, const int imm, mve_pred16_t p) { return vidupq_m_wb_u8(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t increment_wrap_duplicate(uint8x16_t inactive, uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_m_n_u8(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint8x16_t increment_wrap_duplicate(uint8x16_t inactive, uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_m_wb_u8(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint8x16_t duplicate(uint8x16_t inactive, uint8_t a, mve_pred16_t p) { return vdupq_m_n_u8(inactive, a, p); }
[[gnu::always_inline]] nce uint8x16_t uninitialized(uint8x16_t t) { return vuninitializedq(t); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint8x16_t a, uint8_t b) { return vcmpeqq_n_u8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint8x16_t a, uint8_t b, mve_pred16_t p) { return vcmpeqq_m_n_u8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint8x16_t a, uint8_t b) { return vcmpneq_n_u8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint8x16_t a, uint8_t b, mve_pred16_t p) { return vcmpneq_m_n_u8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint8x16_t a, uint8_t b) { return vcmpcsq_n_u8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint8x16_t a, uint8_t b, mve_pred16_t p) { return vcmpcsq_m_n_u8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint8x16_t a, uint8_t b) { return vcmphiq_n_u8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint8x16_t a, uint8_t b, mve_pred16_t p) { return vcmphiq_m_n_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add(uint8x16_t a, uint8_t b) { return vaddq_n_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add(uint8x16_t a, uint8_t b, mve_pred16_t p) { return vaddq_x_n_u8(a, b, p); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint8x16_t a) { return vaddvq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t add_halve(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vhaddq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add_halve_round(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vrhaddq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add_saturate(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vqaddq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add_halve(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vhaddq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add_halve_round(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vrhaddq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add_halve(uint8x16_t inactive, uint8x16_t a, uint8_t b, mve_pred16_t p) { return vhaddq_m_n_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add_saturate(uint8x16_t inactive, uint8x16_t a, uint8_t b, mve_pred16_t p) { return vqaddq_m_n_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t multiply_high(uint8x16_t a, uint8x16_t b) { return vmulhq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t multiply_high(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmulhq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t multiply_high(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmulhq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_long_bottom_poly(uint8x16_t a, uint8x16_t b) { return vmullbq_poly_p8(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply_long_bottom(uint8x16_t a, uint8x16_t b) { return vmullbq_int_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply_long_bottom_poly(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmullbq_poly_x_p8(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_long_bottom(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmullbq_int_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multply_long_top_poly(uint8x16_t a, uint8x16_t b) { return vmulltq_poly_p8(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply_long_top(uint8x16_t a, uint8x16_t b) { return vmulltq_int_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t multiply(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmulq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t multiply_round_high(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vrmulhq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multply_long_top_poly(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmulltq_poly_x_p8(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_long_top(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmulltq_int_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t multiply(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmulq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t multiply_round_high(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vrmulhq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t multiply(uint8x16_t inactive, uint8x16_t a, uint8_t b, mve_pred16_t p) { return vmulq_m_n_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t multiply_round_high(uint8x16_t a, uint8x16_t b) { return vrmulhq_u8(a, b); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add(uint8x16_t m1, uint8x16_t m2) { return vmladavq_u8(m1, m2); }
[[gnu::always_inline]] nce uint8x16_t subtract(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vsubq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t subtract_halve(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vhsubq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t subtract_saturate(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vqsubq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_clear(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vbicq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_and(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vandq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_xor(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return veorq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_or_not(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vornq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_or(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vorrq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add(uint8x16_t m1, uint8x16_t m2, mve_pred16_t p) { return vmladavq_p_u8(m1, m2, p); }
[[gnu::always_inline]] nce uint8x16_t subtract(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vsubq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t subtract_halve(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vhsubq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t count_leading_zero_bits(uint8x16_t inactive, uint8x16_t a, mve_pred16_t p) { return vclzq_m_u8(inactive, a, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_clear(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vbicq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_and(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vandq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_xor(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return veorq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_not(uint8x16_t inactive, uint8x16_t a, mve_pred16_t p) { return vmvnq_m_u8(inactive, a, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_or_not(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vornq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_or(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vorrq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t multiply_add(uint8x16_t add, uint8x16_t m1, uint8_t m2) { return vmlaq_n_u8(add, m1, m2); }
[[gnu::always_inline]] nce uint8x16_t multiply_add(uint8x16_t add, uint8x16_t m1, uint8_t m2, mve_pred16_t p) { return vmlaq_m_n_u8(add, m1, m2, p); }
[[gnu::always_inline]] nce uint8x16_t multiply_add(uint8x16_t m1, uint8x16_t m2, uint8_t add) { return vmlasq_n_u8(m1, m2, add); }
[[gnu::always_inline]] nce uint8x16_t multiply_add(uint8x16_t m1, uint8x16_t m2, uint8_t add, mve_pred16_t p) { return vmlasq_m_n_u8(m1, m2, add, p); }
[[gnu::always_inline]] nce uint8x16_t subtract(uint8x16_t inactive, uint8x16_t a, uint8_t b, mve_pred16_t p) { return vsubq_m_n_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t subtract_halve(uint8x16_t inactive, uint8x16_t a, uint8_t b, mve_pred16_t p) { return vhsubq_m_n_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t subtract_saturate(uint8x16_t inactive, uint8x16_t a, uint8_t b, mve_pred16_t p) { return vqsubq_m_n_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t complex_add_rotate_90(uint8x16_t a, uint8x16_t b) { return vcaddq_rot90_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t complex_add_rotate_270(uint8x16_t a, uint8x16_t b) { return vcaddq_rot270_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t complex_add_rotate_90(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vcaddq_rot90_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t complex_add_rotate_270(uint8x16_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vcaddq_rot270_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round_saturate(uint8x16_t inactive, uint8x16_t a, int8x16_t b, mve_pred16_t p) { return vqrshlq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left_saturate(uint8x16_t inactive, uint8x16_t a, int8x16_t b, mve_pred16_t p) { return vqshlq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round(uint8x16_t inactive, uint8x16_t a, int8x16_t b, mve_pred16_t p) { return vrshlq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t complex_add_rotate_90(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vcaddq_rot90_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t complex_add_rotate_270(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vcaddq_rot270_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t predicate_select(uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vpselq_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t bit_reverse_shift_right(uint8x16_t inactive, uint8x16_t a, int32_t b, mve_pred16_t p) { return vbrsrq_m_n_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t shift_right_round(uint8x16_t inactive, uint8x16_t a, const int imm, mve_pred16_t p) { return vrshrq_m_n_u8(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t shift_right(uint8x16_t inactive, uint8x16_t a, const int imm, mve_pred16_t p) { return vshrq_m_n_u8(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t shift_right_insert(uint8x16_t a, uint8x16_t b, const int imm, mve_pred16_t p) { return vsriq_m_n_u8(a, b, imm, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left_saturate(uint8x16_t inactive, uint8x16_t a, const int imm, mve_pred16_t p) { return vqshlq_m_n_u8(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round(uint8x16_t a, int8x16_t b, mve_pred16_t p) { return vrshlq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left_unsigned_saturate(uint8x16_t inactive, int8x16_t a, const int imm, mve_pred16_t p) { return vqshluq_m_n_s8(inactive, a, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_round_saturate_bottom(uint8x16_t a, uint16x8_t b) { return vqrshrnbq_n_u16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_round_saturate_bottom(uint8x16_t a, uint16x8_t b, const int imm, mve_pred16_t p) { return vqrshrnbq_m_n_u16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shight_right_narrow_round_saturate_top(uint8x16_t a, uint16x8_t b) { return vqrshrntq_n_u16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shight_right_narrow_round_saturate_top(uint8x16_t a, uint16x8_t b, const int imm, mve_pred16_t p) { return vqrshrntq_m_n_u16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_saturate_bottom(uint8x16_t a, uint16x8_t b) { return vqshrnbq_n_u16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_saturate_bottom(uint8x16_t a, uint16x8_t b, const int imm, mve_pred16_t p) { return vqshrnbq_m_n_u16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_saturate_top(uint8x16_t a, uint16x8_t b) { return vqshrntq_n_u16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_saturate_top(uint8x16_t a, uint16x8_t b, const int imm, mve_pred16_t p) { return vqshrntq_m_n_u16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_round_bottom(uint8x16_t a, uint16x8_t b) { return vrshrnbq_n_u16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_round_bottom(uint8x16_t a, uint16x8_t b, const int imm, mve_pred16_t p) { return vrshrnbq_m_n_u16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_round_top(uint8x16_t a, uint16x8_t b) { return vrshrntq_n_u16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_round_top(uint8x16_t a, uint16x8_t b, const int imm, mve_pred16_t p) { return vrshrntq_m_n_u16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_bottom(uint8x16_t a, uint16x8_t b) { return vshrnbq_n_u16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_bottom(uint8x16_t a, uint16x8_t b, const int imm, mve_pred16_t p) { return vshrnbq_m_n_u16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_top_signed(uint8x16_t a, uint16x8_t b) { return vshrntq_n_u16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round(uint8x16_t a, int32_t b) { return vrshlq_n_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round(uint8x16_t a, int32_t b, mve_pred16_t p) { return vrshlq_m_n_u8(a, b, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_left_carry(uint8x16_t a, uint32_t *b) { return vshlcq_u8(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_left_carry(uint8x16_t a, uint32_t *b, const int imm, mve_pred16_t p) { return vshlcq_m_u8(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_left_long_bottom(uint8x16_t a) { return vshllbq_n_u8(a, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_left_long_bottom(uint8x16_t a, const int imm, mve_pred16_t p) { return vshllbq_x_n_u8(a, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_left_long_top(uint8x16_t a) { return vshlltq_n_u8(a, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t inactive, uint8x16_t a, int8x16_t b, mve_pred16_t p) { return vshlq_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t inactive, uint8x16_t a, const int imm, mve_pred16_t p) { return vshlq_m_n_u8(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left_insert(uint8x16_t a, uint8x16_t b, const int imm, mve_pred16_t p) { return vsliq_m_n_u8(a, b, imm, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t a, int8x16_t b, mve_pred16_t p) { return vshlq_x_u8(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t move_long_bottom(uint8x16_t a) { return vmovlbq_u8(a); }
[[gnu::always_inline]] nce uint16x8_t move_long_bottom(uint8x16_t a, mve_pred16_t p) { return vmovlbq_x_u8(a, p); }
[[gnu::always_inline]] nce uint16x8_t move_long_top(uint8x16_t a) { return vmovltq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_bottom(uint8x16_t a, uint16x8_t b) { return vmovnbq_u16(a, b); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_bottom(uint8x16_t a, uint16x8_t b, mve_pred16_t p) { return vmovnbq_m_u16(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_top(uint8x16_t a, uint16x8_t b) { return vmovntq_u16(a, b); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_top(uint8x16_t a, uint16x8_t b, mve_pred16_t p) { return vmovntq_m_u16(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_saturate_bottom(uint8x16_t a, uint16x8_t b) { return vqmovnbq_u16(a, b); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_saturate_bottom(uint8x16_t a, uint16x8_t b, mve_pred16_t p) { return vqmovnbq_m_u16(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_saturate_top(uint8x16_t a, uint16x8_t b) { return vqmovntq_u16(a, b); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_saturate_top(uint8x16_t a, uint16x8_t b, mve_pred16_t p) { return vqmovntq_m_u16(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_top_signed(uint8x16_t a, uint16x8_t b, const int imm, mve_pred16_t p) { return vshrntq_m_n_u16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_round_saturate_bottom(uint8x16_t a, int16x8_t b) { return vqrshrunbq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_round_saturate_bottom(uint8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vqrshrunbq_m_n_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_round_saturate_top(uint8x16_t a, int16x8_t b) { return vqrshruntq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_round_saturate_top(uint8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vqrshruntq_m_n_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_saturate_bottom(uint8x16_t a, int16x8_t b) { return vqshrunbq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_saturate_bottom(uint8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vqshrunbq_m_n_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_saturate_top(uint8x16_t a, int16x8_t b) { return vqshruntq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_saturate_bottom(uint8x16_t a, int16x8_t b) { return vqmovunbq_s16(a, b); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_saturate_bottom(uint8x16_t a, int16x8_t b, mve_pred16_t p) { return vqmovunbq_m_s16(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_saturate_top(uint8x16_t a, int16x8_t b) { return vqmovuntq_s16(a, b); }
[[gnu::always_inline]] nce uint8x16_t move_narrow_saturate_top(uint8x16_t a, int16x8_t b, mve_pred16_t p) { return vqmovuntq_m_s16(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t shift_right_narrow_saturate_top(uint8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vqshruntq_m_n_s16(a, b, imm, p); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint8x16_t a, mve_pred16_t p) { return vaddvq_p_u8(a, p); }
[[gnu::always_inline]] nce uint8x16_t count_leading_zero_bits(uint8x16_t a, mve_pred16_t p) { return vclzq_x_u8(a, p); }
[[gnu::always_inline]] nce uint8x16_t bitwise_not(uint8x16_t a, mve_pred16_t p) { return vmvnq_x_u8(a, p); }
[[gnu::always_inline]] nce uint16x8_t move_long_top(uint8x16_t a, mve_pred16_t p) { return vmovltq_x_u8(a, p); }
[[gnu::always_inline]] nce uint8x16_t add_halve(uint8x16_t a, uint8_t b) { return vhaddq_n_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_halve(uint8x16_t a, uint8_t b, mve_pred16_t p) { return vhaddq_x_n_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t add_saturate(uint8x16_t a, uint8_t b) { return vqaddq_n_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t multiply(uint8x16_t a, uint8_t b, mve_pred16_t p) { return vmulq_x_n_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t subtract(uint8x16_t a, uint8_t b) { return vsubq_n_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract(uint8x16_t a, uint8_t b, mve_pred16_t p) { return vsubq_x_n_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t subtract_halve(uint8x16_t a, uint8_t b) { return vhsubq_n_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_halve(uint8x16_t a, uint8_t b, mve_pred16_t p) { return vhsubq_x_n_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t subtract_saturate(uint8x16_t a, uint8_t b) { return vqsubq_n_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t bit_reverse_shift_right(uint8x16_t a, int32_t b) { return vbrsrq_n_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t bit_reverse_shift_right(uint8x16_t a, int32_t b, mve_pred16_t p) { return vbrsrq_x_n_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t shift_right_round(uint8x16_t a, const int imm, mve_pred16_t p) { return vrshrq_x_n_u8(a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t shift_right(uint8x16_t a, const int imm, mve_pred16_t p) { return vshrq_x_n_u8(a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round_saturate(uint8x16_t a, int32_t b) { return vqrshlq_n_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round_saturate(uint8x16_t a, int32_t b, mve_pred16_t p) { return vqrshlq_m_n_u8(a, b, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left_saturate(uint8x16_t a, int32_t b) { return vqshlq_r_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left_saturate(uint8x16_t a, int32_t b, mve_pred16_t p) { return vqshlq_m_r_u8(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_long_top(uint8x16_t a, const int imm, mve_pred16_t p) { return vshlltq_x_n_u8(a, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t a) { return vshlq_n_u8(a, imm); }
[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t a, const int imm, mve_pred16_t p) { return vshlq_x_n_u8(a, imm, p); }
[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t a, int32_t b) { return vshlq_r_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t a, int32_t b, mve_pred16_t p) { return vshlq_m_r_u8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t reverse_16bit(int8x16_t inactive, int8x16_t a, mve_pred16_t p) { return vrev16q_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int8x16_t reverse_32bit(int8x16_t inactive, int8x16_t a, mve_pred16_t p) { return vrev32q_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int8x16_t reverse_64bit(int8x16_t inactive, int8x16_t a, mve_pred16_t p) { return vrev64q_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int8x16_t a, int8x16_t b) { return vcmpeqq_s8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vcmpneq_m_s8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int8x16_t a, int8x16_t b) { return vcmpgeq_s8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vcmpgeq_m_s8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int8x16_t a, int8x16_t b) { return vcmpgtq_s8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vcmpgtq_m_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t reverse_64bit(int8x16_t a, mve_pred16_t p) { return vrev64q_x_s8(a, p); }
[[gnu::always_inline]] nce int8x16_t uninitialized(int8x16_t t) { return vuninitializedq(t); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vcmpeqq_m_s8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int8x16_t a, int8x16_t b) { return vcmpneq_s8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int8x16_t a, int8x16_t b) { return vcmpleq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t min(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vminq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vcmpleq_m_s8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int8x16_t a, int8x16_t b) { return vcmpltq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t max(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmaxq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract_absolute(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vabdq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t add(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vaddq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t add_halve(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vhaddq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t add_halve_round(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vrhaddq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t add_saturate(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqaddq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t add_halve(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vhaddq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t add_halve_round(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vrhaddq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t add_halve(int8x16_t inactive, int8x16_t a, int8_t b, mve_pred16_t p) { return vhaddq_m_n_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t add_saturate(int8x16_t inactive, int8x16_t a, int8_t b, mve_pred16_t p) { return vqaddq_m_n_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_high(int8x16_t a, int8x16_t b) { return vmulhq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_high(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmulhq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_high(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmulhq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_long_bottom(int8x16_t a, int8x16_t b) { return vmullbq_int_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_long_bottom(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmullbq_int_x_s8(a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_long_top(int8x16_t a, int8x16_t b) { return vmulltq_int_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmulq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_round_high(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vrmulhq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_add_double_saturate_high(int8x16_t inactive, int8x16_t a, int8x16_t b) { return vqdmladhq_s8(inactive, a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_add_double_saturate_high(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqdmladhq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_add_double_saturate_high_exchange_pairs(int8x16_t inactive, int8x16_t a, int8x16_t b) { return vqdmladhxq_s8(inactive, a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_add_double_saturate_high_exchange_pairs(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqdmladhxq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_add_dual_double_round_saturate_high(int8x16_t inactive, int8x16_t a, int8x16_t b) { return vqrdmladhq_s8(inactive, a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_add_dual_double_round_saturate_high(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqrdmladhq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t mulitply_add_dual_double_round_saturate_high_exchange_pairs(int8x16_t inactive, int8x16_t a, int8x16_t b) { return vqrdmladhxq_s8(inactive, a, b); }
[[gnu::always_inline]] nce int8x16_t mulitply_add_dual_double_round_saturate_high_exchange_pairs(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqrdmladhxq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_long_top(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmulltq_int_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmulq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_round_high(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vrmulhq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply(int8x16_t inactive, int8x16_t a, int8_t b, mve_pred16_t p) { return vmulq_m_n_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_round_high(int8x16_t a, int8x16_t b) { return vrmulhq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract_dual_double_saturate_high(int8x16_t inactive, int8x16_t a, int8x16_t b) { return vqdmlsdhq_s8(inactive, a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract_dual_double_saturate_high(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqdmlsdhq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract_dual_double_saturate_high_exchange_pairs(int8x16_t inactive, int8x16_t a, int8x16_t b) { return vqdmlsdhxq_s8(inactive, a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract_dual_double_saturate_high_exchange_pairs(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqdmlsdhxq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract_dual_double_round_saturate_high(int8x16_t inactive, int8x16_t a, int8x16_t b) { return vqrdmlsdhq_s8(inactive, a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract_dual_double_round_saturate_high(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqrdmlsdhq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract_dual_double_round_saturate_high_exchange_pairs(int8x16_t inactive, int8x16_t a, int8x16_t b) { return vqrdmlsdhxq_s8(inactive, a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract_dual_double_round_saturate_high_exchange_pairs(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqrdmlsdhxq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_double_saturate_high(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqdmulhq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_double_round_saturate_high(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqrdmulhq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vcmpltq_m_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t min(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vminq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t max(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmaxq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract_absolute(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vabdq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t abs(int8x16_t inactive, int8x16_t a, mve_pred16_t p) { return vabsq_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int8x16_t abs_saturate(int8x16_t inactive, int8x16_t a, mve_pred16_t p) { return vqabsq_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int8x16_t add(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vaddq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_add_double_round_saturate_high(int8x16_t m1, int8x16_t m2, int8_t add) { return vqrdmlashq_n_s8(m1, m2, add); }
[[gnu::always_inline]] nce int8x16_t multiply_add_double_round_saturate_high(int8x16_t m1, int8x16_t m2, int8_t add, mve_pred16_t p) { return vqrdmlashq_m_n_s8(m1, m2, add, p); }
[[gnu::always_inline]] nce int8x16_t multiply_double_saturate_high(int8x16_t inactive, int8x16_t a, int8_t b, mve_pred16_t p) { return vqdmulhq_m_n_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_double_saturate_high(int8x16_t a, int8x16_t b) { return vqdmulhq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_double_round_saturate_high(int8x16_t inactive, int8x16_t a, int8_t b, mve_pred16_t p) { return vqrdmulhq_m_n_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_double_round_saturate_high(int8x16_t a, int8x16_t b) { return vqrdmulhq_s8(a, b); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add(int8x16_t m1, int8x16_t m2) { return vmladavq_s8(m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add(int8x16_t m1, int8x16_t m2, mve_pred16_t p) { return vmladavq_p_s8(m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_exchange_pairs(int8x16_t m1, int8x16_t m2) { return vmladavxq_s8(m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_exchange_pairs(int8x16_t m1, int8x16_t m2, mve_pred16_t p) { return vmladavxq_p_s8(m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmlsdavq_p_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t add(int8x16_t inactive, int8x16_t a, int8_t b, mve_pred16_t p) { return vaddq_m_n_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_add(int8x16_t add, int8x16_t m1, int8_t m2) { return vmlaq_n_s8(add, m1, m2); }
[[gnu::always_inline]] nce int8x16_t multiply_add(int8x16_t add, int8x16_t m1, int8_t m2, mve_pred16_t p) { return vmlaq_m_n_s8(add, m1, m2, p); }
[[gnu::always_inline]] nce int8x16_t multiply_add(int8x16_t m1, int8x16_t m2, int8_t add) { return vmlasq_n_s8(m1, m2, add); }
[[gnu::always_inline]] nce int8x16_t multiply_add(int8x16_t m1, int8x16_t m2, int8_t add, mve_pred16_t p) { return vmlasq_m_n_s8(m1, m2, add, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add(int8x16_t a, int8x16_t b) { return vmlsdavq_s8(a, b); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_exchange_pairs(int8x16_t a, int8x16_t b) { return vmlsdavxq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vsubq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract_halve(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vhsubq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract_saturate(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqsubq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_clear(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vbicq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_and(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vandq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_xor(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return veorq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_or_not(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vornq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_or(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vorrq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_270(int8x16_t a, int8x16_t b) { return vcaddq_rot270_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_90(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vcaddq_rot90_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_270(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vcaddq_rot270_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_90_halve(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vhcaddq_rot90_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_exchange_pairs(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmlsdavxq_p_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_90(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vcaddq_rot90_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_270(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vcaddq_rot270_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_90_halve(int8x16_t a, int8x16_t b) { return vhcaddq_rot90_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_90_halve(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vhcaddq_rot90_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_270_halve(int8x16_t a, int8x16_t b) { return vhcaddq_rot270_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_270_halve(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vhcaddq_rot270_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vsubq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract_halve(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vhsubq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t count_leading_sign_bits(int8x16_t inactive, int8x16_t a, mve_pred16_t p) { return vclsq_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int8x16_t count_leading_zero_bits(int8x16_t inactive, int8x16_t a, mve_pred16_t p) { return vclzq_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_clear(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vbicq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t negate(int8x16_t inactive, int8x16_t a, mve_pred16_t p) { return vnegq_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int8x16_t negate_saturate(int8x16_t inactive, int8x16_t a, mve_pred16_t p) { return vqnegq_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_and(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vandq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_xor(int8x16_t a, int8x16_t b, mve_pred16_t p) { return veorq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_not(int8x16_t inactive, int8x16_t a, mve_pred16_t p) { return vmvnq_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_or_not(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vornq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_or(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vorrq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_270_halve(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vhcaddq_rot270_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract(int8x16_t inactive, int8x16_t a, int8_t b, mve_pred16_t p) { return vsubq_m_n_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract_halve(int8x16_t inactive, int8x16_t a, int8_t b, mve_pred16_t p) { return vhsubq_m_n_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract_saturate(int8x16_t inactive, int8x16_t a, int8_t b, mve_pred16_t p) { return vqsubq_m_n_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t complex_add_rotate_90(int8x16_t a, int8x16_t b) { return vcaddq_rot90_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left_round_saturate(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqrshlq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t shift_left_saturate(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vqshlq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t bit_reverse_shift_right(int8x16_t inactive, int8x16_t a, int32_t b, mve_pred16_t p) { return vbrsrq_m_n_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t shift_right_round(int8x16_t inactive, int8x16_t a, const int imm, mve_pred16_t p) { return vrshrq_m_n_s8(inactive, a, imm, p); }
[[gnu::always_inline]] nce int8x16_t shift_right(int8x16_t inactive, int8x16_t a, const int imm, mve_pred16_t p) { return vshrq_m_n_s8(inactive, a, imm, p); }
[[gnu::always_inline]] nce int8x16_t shift_right_insert(int8x16_t a, int8x16_t b, const int imm, mve_pred16_t p) { return vsriq_m_n_s8(a, b, imm, p); }
[[gnu::always_inline]] nce int8x16_t shift_left_saturate(int8x16_t inactive, int8x16_t a, const int imm, mve_pred16_t p) { return vqshlq_m_n_s8(inactive, a, imm, p); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_right_narrow_round_saturate_bottom(int8x16_t a, int16x8_t b) { return vqrshrnbq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce int8x16_t shift_right_narrow_round_saturate_bottom(int8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vqrshrnbq_m_n_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shight_right_narrow_round_saturate_top(int8x16_t a, int16x8_t b) { return vqrshrntq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce int8x16_t shight_right_narrow_round_saturate_top(int8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vqrshrntq_m_n_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_right_narrow_saturate_bottom(int8x16_t a, int16x8_t b) { return vqshrnbq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce int8x16_t shift_right_narrow_saturate_bottom(int8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vqshrnbq_m_n_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_right_narrow_saturate_top(int8x16_t a, int16x8_t b) { return vqshrntq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce int8x16_t shift_right_narrow_saturate_top(int8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vqshrntq_m_n_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_right_narrow_round_bottom(int8x16_t a, int16x8_t b) { return vrshrnbq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce int8x16_t shift_right_narrow_round_bottom(int8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vrshrnbq_m_n_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_right_narrow_round_top(int8x16_t a, int16x8_t b) { return vrshrntq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce int8x16_t shift_right_narrow_round_top(int8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vrshrntq_m_n_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_right_narrow_bottom(int8x16_t a, int16x8_t b) { return vshrnbq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce int8x16_t shift_right_narrow_bottom(int8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vshrnbq_m_n_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_right_narrow_top_signed(int8x16_t a, int16x8_t b) { return vshrntq_n_s16(a, b, imm); }
[[gnu::always_inline]] nce int8x16_t shift_right_narrow_top_signed(int8x16_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vshrntq_m_n_s16(a, b, imm, p); }
[[gnu::always_inline]] nce int8x16_t bit_reverse_shift_right(int8x16_t a, int32_t b) { return vbrsrq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t bit_reverse_shift_right(int8x16_t a, int32_t b, mve_pred16_t p) { return vbrsrq_x_n_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t shift_right_round(int8x16_t a, const int imm, mve_pred16_t p) { return vrshrq_x_n_s8(a, imm, p); }
[[gnu::always_inline]] nce int8x16_t shift_right(int8x16_t a, const int imm, mve_pred16_t p) { return vshrq_x_n_s8(a, imm, p); }
[[gnu::always_inline]] nce int8x16_t shift_left_round_saturate(int8x16_t a, int32_t b) { return vqrshlq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left_round_saturate(int8x16_t a, int32_t b, mve_pred16_t p) { return vqrshlq_m_n_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t shift_left_saturate(int8x16_t a, int32_t b) { return vqshlq_r_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left_saturate(int8x16_t a, int32_t b, mve_pred16_t p) { return vqshlq_m_r_s8(a, b, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t shift_left_unsigned_saturate(int8x16_t a) { return vqshluq_n_s8(a, imm); }
[[gnu::always_inline]] nce int8x16_t shift_left_round(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vrshlq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vshlq_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int8x16_t shift_left_round(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vrshlq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vshlq_x_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t inactive, int8x16_t a, const int imm, mve_pred16_t p) { return vshlq_m_n_s8(inactive, a, imm, p); }
[[gnu::always_inline]] nce int8x16_t shift_left_round(int8x16_t a, int32_t b) { return vrshlq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left_round(int8x16_t a, int32_t b, mve_pred16_t p) { return vrshlq_m_n_s8(a, b, p); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_left_carry(int8x16_t a, uint32_t *b) { return vshlcq_s8(a, b, imm); }
[[gnu::always_inline]] nce int8x16_t shift_left_carry(int8x16_t a, uint32_t *b, const int imm, mve_pred16_t p) { return vshlcq_m_s8(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_left_long_bottom(int8x16_t a) { return vshllbq_n_s8(a, imm); }
[[gnu::always_inline]] nce int16x8_t shift_left_long_bottom(int8x16_t a, const int imm, mve_pred16_t p) { return vshllbq_x_n_s8(a, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_left_long_top(int8x16_t a) { return vshlltq_n_s8(a, imm); }
[[gnu::always_inline]] nce int16x8_t shift_left_long_top(int8x16_t a, const int imm, mve_pred16_t p) { return vshlltq_x_n_s8(a, imm, p); }
template <int imm>[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t a) { return vshlq_n_s8(a, imm); }
[[gnu::always_inline]] nce int8x16_t shift_left_insert(int8x16_t a, int8x16_t b, const int imm, mve_pred16_t p) { return vsliq_m_n_s8(a, b, imm, p); }
[[gnu::always_inline]] nce int16x8_t move_long_bottom(int8x16_t a) { return vmovlbq_s8(a); }
[[gnu::always_inline]] nce int16x8_t move_long_bottom(int8x16_t a, mve_pred16_t p) { return vmovlbq_x_s8(a, p); }
[[gnu::always_inline]] nce int16x8_t move_long_top(int8x16_t a) { return vmovltq_s8(a); }
[[gnu::always_inline]] nce int8x16_t predicate_select(int8x16_t a, int8x16_t b, mve_pred16_t p) { return vpselq_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_add_double_saturate_high(int8x16_t add, int8x16_t m1, int8_t m2) { return vqdmlahq_n_s8(add, m1, m2); }
[[gnu::always_inline]] nce int8x16_t multiply_add_double_saturate_high(int8x16_t add, int8x16_t m1, int8_t m2, mve_pred16_t p) { return vqdmlahq_m_n_s8(add, m1, m2, p); }
[[gnu::always_inline]] nce int8x16_t multiply_add_double_round_saturate_high(int8x16_t add, int8x16_t m1, int8_t m2) { return vqrdmlahq_n_s8(add, m1, m2); }
[[gnu::always_inline]] nce int8x16_t multiply_add_double_round_saturate_high(int8x16_t add, int8x16_t m1, int8_t m2, mve_pred16_t p) { return vqrdmlahq_m_n_s8(add, m1, m2, p); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract_double_saturate_high(int8x16_t m1, int8x16_t m2, int8_t add) { return vqdmlashq_n_s8(m1, m2, add); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract_double_saturate_high(int8x16_t m1, int8x16_t m2, int8_t add, mve_pred16_t p) { return vqdmlashq_m_n_s8(m1, m2, add, p); }
[[gnu::always_inline]] nce int8x16_t move_narrow_bottom(int8x16_t a, int16x8_t b) { return vmovnbq_s16(a, b); }
[[gnu::always_inline]] nce int8x16_t move_narrow_bottom(int8x16_t a, int16x8_t b, mve_pred16_t p) { return vmovnbq_m_s16(a, b, p); }
[[gnu::always_inline]] nce int8x16_t move_narrow_top(int8x16_t a, int16x8_t b) { return vmovntq_s16(a, b); }
[[gnu::always_inline]] nce int8x16_t move_narrow_top(int8x16_t a, int16x8_t b, mve_pred16_t p) { return vmovntq_m_s16(a, b, p); }
[[gnu::always_inline]] nce int8x16_t move_narrow_saturate_bottom(int8x16_t a, int16x8_t b) { return vqmovnbq_s16(a, b); }
[[gnu::always_inline]] nce int8x16_t move_narrow_saturate_bottom(int8x16_t a, int16x8_t b, mve_pred16_t p) { return vqmovnbq_m_s16(a, b, p); }
[[gnu::always_inline]] nce int8x16_t move_narrow_saturate_top(int8x16_t a, int16x8_t b) { return vqmovntq_s16(a, b); }
[[gnu::always_inline]] nce int8x16_t move_narrow_saturate_top(int8x16_t a, int16x8_t b, mve_pred16_t p) { return vqmovntq_m_s16(a, b, p); }
[[gnu::always_inline]] nce int8x16_t reverse_16bit(int8x16_t a, mve_pred16_t p) { return vrev16q_x_s8(a, p); }
[[gnu::always_inline]] nce int8x16_t reverse_32bit(int8x16_t a, mve_pred16_t p) { return vrev32q_x_s8(a, p); }
[[gnu::always_inline]] nce int8x16_t abs(int8x16_t a, mve_pred16_t p) { return vabsq_x_s8(a, p); }
[[gnu::always_inline]] nce int8x16_t count_leading_sign_bits(int8x16_t a, mve_pred16_t p) { return vclsq_x_s8(a, p); }
[[gnu::always_inline]] nce int8x16_t count_leading_zero_bits(int8x16_t a, mve_pred16_t p) { return vclzq_x_s8(a, p); }
[[gnu::always_inline]] nce int8x16_t negate(int8x16_t a, mve_pred16_t p) { return vnegq_x_s8(a, p); }
[[gnu::always_inline]] nce int8x16_t bitwise_not(int8x16_t a, mve_pred16_t p) { return vmvnq_x_s8(a, p); }
[[gnu::always_inline]] nce int16x8_t move_long_top(int8x16_t a, mve_pred16_t p) { return vmovltq_x_s8(a, p); }
[[gnu::always_inline]] nce int8x16_t duplicate(int8x16_t inactive, int8_t a, mve_pred16_t p) { return vdupq_m_n_s8(inactive, a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int8x16_t a, int8_t b) { return vcmpeqq_n_s8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int8x16_t a, int8_t b, mve_pred16_t p) { return vcmpeqq_m_n_s8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int8x16_t a, int8_t b) { return vcmpneq_n_s8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int8x16_t a, int8_t b, mve_pred16_t p) { return vcmpneq_m_n_s8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int8x16_t a, int8_t b) { return vcmpgeq_n_s8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int8x16_t a, int8_t b, mve_pred16_t p) { return vcmpgeq_m_n_s8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int8x16_t a, int8_t b) { return vcmpgtq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add(int8x16_t a, int8_t b, mve_pred16_t p) { return vaddq_x_n_s8(a, b, p); }
[[gnu::always_inline]] nce int32_t reduce_add(int8x16_t a) { return vaddvq_s8(a); }
[[gnu::always_inline]] nce int32_t reduce_add(int8x16_t a, mve_pred16_t p) { return vaddvq_p_s8(a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int8x16_t a, int8_t b, mve_pred16_t p) { return vcmpgtq_m_n_s8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int8x16_t a, int8_t b) { return vcmpleq_n_s8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int8x16_t a, int8_t b, mve_pred16_t p) { return vcmpleq_m_n_s8(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int8x16_t a, int8_t b) { return vcmpltq_n_s8(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int8x16_t a, int8_t b, mve_pred16_t p) { return vcmpltq_m_n_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t add(int8x16_t a, int8_t b) { return vaddq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_halve(int8x16_t a, int8_t b) { return vhaddq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_halve(int8x16_t a, int8_t b, mve_pred16_t p) { return vhaddq_x_n_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t add_saturate(int8x16_t a, int8_t b) { return vqaddq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply(int8x16_t a, int8_t b, mve_pred16_t p) { return vmulq_x_n_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t multiply_double_saturate_high(int8x16_t a, int8_t b) { return vqdmulhq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_double_round_saturate_high(int8x16_t a, int8_t b) { return vqrdmulhq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract(int8x16_t a, int8_t b) { return vsubq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract(int8x16_t a, int8_t b, mve_pred16_t p) { return vsubq_x_n_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract_halve(int8x16_t a, int8_t b) { return vhsubq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_halve(int8x16_t a, int8_t b, mve_pred16_t p) { return vhsubq_x_n_s8(a, b, p); }
[[gnu::always_inline]] nce int8x16_t subtract_saturate(int8x16_t a, int8_t b) { return vqsubq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t a, const int imm, mve_pred16_t p) { return vshlq_x_n_s8(a, imm, p); }
[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t a, int32_t b) { return vshlq_r_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t a, int32_t b, mve_pred16_t p) { return vshlq_m_r_s8(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_long_bottom(uint16x8_t inactive, uint8x16_t a, const int imm, mve_pred16_t p) { return vshllbq_m_n_u8(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t reverse_32bit(uint16x8_t inactive, uint16x8_t a, mve_pred16_t p) { return vrev32q_m_u16(inactive, a, p); }
[[gnu::always_inline]] nce uint16x8_t reverse_64bit(uint16x8_t inactive, uint16x8_t a, mve_pred16_t p) { return vrev64q_m_u16(inactive, a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint16x8_t a, uint16x8_t b) { return vcmpneq_u16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vcmpneq_m_u16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint16x8_t a, uint16x8_t b) { return vcmpcsq_u16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vcmpcsq_m_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t reverse_32bit(uint16x8_t a, mve_pred16_t p) { return vrev32q_x_u16(a, p); }
[[gnu::always_inline]] nce uint16x8_t reverse_64bit(uint16x8_t a, mve_pred16_t p) { return vrev64q_x_u16(a, p); }
[[gnu::always_inline]] nce uint16x8_t decrement_duplicate(uint16x8_t inactive, uint32_t a, const int imm, mve_pred16_t p) { return vddupq_m_n_u16(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t decrement_duplicate(uint16x8_t inactive, uint32_t *a, const int imm, mve_pred16_t p) { return vddupq_m_wb_u16(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t decrement_wrap_duplicate(uint16x8_t inactive, uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_m_n_u16(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint16x8_t decrement_wrap_duplicate(uint16x8_t inactive, uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_m_wb_u16(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint16x8_t increment_duplicate(uint16x8_t inactive, uint32_t a, const int imm, mve_pred16_t p) { return vidupq_m_n_u16(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t increment_duplicate(uint16x8_t inactive, uint32_t *a, const int imm, mve_pred16_t p) { return vidupq_m_wb_u16(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t increment_wrap_duplicate(uint16x8_t inactive, uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_m_n_u16(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint16x8_t increment_wrap_duplicate(uint16x8_t inactive, uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_m_wb_u16(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint16x8_t duplicate(uint16x8_t inactive, uint16_t a, mve_pred16_t p) { return vdupq_m_n_u16(inactive, a, p); }
[[gnu::always_inline]] nce uint16x8_t uninitialized(uint16x8_t t) { return vuninitializedq(t); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint16x8_t a, uint16x8_t b) { return vcmpeqq_u16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint16x8_t a, uint16x8_t b) { return vcmphiq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t min(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vminq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t max(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmaxq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract_absolute(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vabdq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vaddq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vcmpeqq_m_u16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vcmphiq_m_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t min(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vminq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t max(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmaxq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract_absolute(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vabdq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vaddq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add(uint16x8_t inactive, uint16x8_t a, uint16_t b, mve_pred16_t p) { return vaddq_m_n_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t minimum_absolute(uint16x8_t a, int16x8_t b) { return vminaq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t minimum_absolute(uint16x8_t a, int16x8_t b, mve_pred16_t p) { return vminaq_m_s16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t maximum_absolute(uint16x8_t a, int16x8_t b) { return vmaxaq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t maximum_absolute(uint16x8_t a, int16x8_t b, mve_pred16_t p) { return vmaxaq_m_s16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint16x8_t a, uint16_t b) { return vcmpeqq_n_u16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint16x8_t a, uint16_t b, mve_pred16_t p) { return vcmpeqq_m_n_u16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint16x8_t a, uint16_t b) { return vcmpneq_n_u16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint16x8_t a, uint16_t b, mve_pred16_t p) { return vcmpneq_m_n_u16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint16x8_t a, uint16_t b) { return vcmpcsq_n_u16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint16x8_t a, uint16_t b, mve_pred16_t p) { return vcmpcsq_m_n_u16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint16x8_t a, uint16_t b) { return vcmphiq_n_u16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint16x8_t a, uint16_t b, mve_pred16_t p) { return vcmphiq_m_n_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add(uint16x8_t a, uint16_t b) { return vaddq_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add(uint16x8_t a, uint16_t b, mve_pred16_t p) { return vaddq_x_n_u16(a, b, p); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint16x8_t a) { return vaddvq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t multiply_long_bottom_poly(uint16x8_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmullbq_poly_m_p8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_long_bottom(uint16x8_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmullbq_int_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multply_long_top_poly(uint16x8_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmulltq_poly_m_p8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_long_top(uint16x8_t inactive, uint8x16_t a, uint8x16_t b, mve_pred16_t p) { return vmulltq_int_m_u8(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add_halve(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vhaddq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add_halve_round(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vrhaddq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add_saturate(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vqaddq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_high(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmulhq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add_halve(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vhaddq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add_halve_round(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vrhaddq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_long_bottom_poly(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmullbq_poly_x_p16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add_halve(uint16x8_t inactive, uint16x8_t a, uint16_t b, mve_pred16_t p) { return vhaddq_m_n_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add_saturate(uint16x8_t inactive, uint16x8_t a, uint16_t b, mve_pred16_t p) { return vqaddq_m_n_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_high(uint16x8_t a, uint16x8_t b) { return vmulhq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply_high(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmulhq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_long_bottom_poly(uint16x8_t a, uint16x8_t b) { return vmullbq_poly_p16(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_long_bottom(uint16x8_t a, uint16x8_t b) { return vmullbq_int_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_long_bottom(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmullbq_int_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multply_long_top_poly(uint16x8_t a, uint16x8_t b) { return vmulltq_poly_p16(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_long_top(uint16x8_t a, uint16x8_t b) { return vmulltq_int_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmulq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_round_high(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vrmulhq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multply_long_top_poly(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmulltq_poly_x_p16(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_long_top(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmulltq_int_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmulq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_round_high(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vrmulhq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t inactive, uint16x8_t a, uint16_t b, mve_pred16_t p) { return vmulq_m_n_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_round_high(uint16x8_t a, uint16x8_t b) { return vrmulhq_u16(a, b); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add(uint16x8_t m1, uint16x8_t m2) { return vmladavq_u16(m1, m2); }
[[gnu::always_inline]] nce uint16x8_t subtract(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vsubq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract_halve(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vhsubq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract_saturate(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vqsubq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_clear(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vbicq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_and(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vandq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_xor(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return veorq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_or_not(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vornq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_or(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vorrq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add(uint16x8_t m1, uint16x8_t m2, mve_pred16_t p) { return vmladavq_p_u16(m1, m2, p); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_dual_reduce_add(uint16x8_t m1, uint16x8_t m2) { return vmlaldavq_u16(m1, m2); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_dual_reduce_add(uint16x8_t m1, uint16x8_t m2, mve_pred16_t p) { return vmlaldavq_p_u16(m1, m2, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_add(uint16x8_t add, uint16x8_t m1, uint16_t m2) { return vmlaq_n_u16(add, m1, m2); }
[[gnu::always_inline]] nce uint16x8_t multiply_add(uint16x8_t add, uint16x8_t m1, uint16_t m2, mve_pred16_t p) { return vmlaq_m_n_u16(add, m1, m2, p); }
[[gnu::always_inline]] nce uint16x8_t multiply_add(uint16x8_t m1, uint16x8_t m2, uint16_t add) { return vmlasq_n_u16(m1, m2, add); }
[[gnu::always_inline]] nce uint16x8_t multiply_add(uint16x8_t m1, uint16x8_t m2, uint16_t add, mve_pred16_t p) { return vmlasq_m_n_u16(m1, m2, add, p); }
[[gnu::always_inline]] nce uint16x8_t complex_add_rotate_90(uint16x8_t a, uint16x8_t b) { return vcaddq_rot90_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t complex_add_rotate_270(uint16x8_t a, uint16x8_t b) { return vcaddq_rot270_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t complex_add_rotate_90(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vcaddq_rot90_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t complex_add_rotate_270(uint16x8_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vcaddq_rot270_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round(uint16x8_t inactive, uint16x8_t a, int16x8_t b, mve_pred16_t p) { return vrshlq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vsubq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract_halve(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vhsubq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t count_leading_zero_bits(uint16x8_t inactive, uint16x8_t a, mve_pred16_t p) { return vclzq_m_u16(inactive, a, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_clear(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vbicq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_and(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vandq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_xor(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return veorq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_not(uint16x8_t inactive, uint16x8_t a, mve_pred16_t p) { return vmvnq_m_u16(inactive, a, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_or_not(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vornq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_or(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vorrq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t complex_add_rotate_90(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vcaddq_rot90_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t complex_add_rotate_270(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vcaddq_rot270_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract(uint16x8_t inactive, uint16x8_t a, uint16_t b, mve_pred16_t p) { return vsubq_m_n_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract_halve(uint16x8_t inactive, uint16x8_t a, uint16_t b, mve_pred16_t p) { return vhsubq_m_n_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract_saturate(uint16x8_t inactive, uint16x8_t a, uint16_t b, mve_pred16_t p) { return vqsubq_m_n_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round(uint16x8_t a, int16x8_t b, mve_pred16_t p) { return vrshlq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round(uint16x8_t a, int32_t b) { return vrshlq_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round(uint16x8_t a, int32_t b, mve_pred16_t p) { return vrshlq_m_n_u16(a, b, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_left_carry(uint16x8_t a, uint32_t *b) { return vshlcq_u16(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_left_carry(uint16x8_t a, uint32_t *b, const int imm, mve_pred16_t p) { return vshlcq_m_u16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t shift_left_long_bottom(uint16x8_t a) { return vshllbq_n_u16(a, imm); }
[[gnu::always_inline]] nce uint32x4_t shift_left_long_bottom(uint16x8_t a, const int imm, mve_pred16_t p) { return vshllbq_x_n_u16(a, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t shift_left_long_top(uint16x8_t a) { return vshlltq_n_u16(a, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_left_long_top(uint16x8_t inactive, uint8x16_t a, const int imm, mve_pred16_t p) { return vshlltq_m_n_u8(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t inactive, uint16x8_t a, int16x8_t b, mve_pred16_t p) { return vshlq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t a, int16x8_t b, mve_pred16_t p) { return vshlq_x_u16(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_long_top(uint16x8_t a, const int imm, mve_pred16_t p) { return vshlltq_x_n_u16(a, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t a) { return vshlq_n_u16(a, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t inactive, uint16x8_t a, const int imm, mve_pred16_t p) { return vshlq_m_n_u16(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_insert(uint16x8_t a, uint16x8_t b, const int imm, mve_pred16_t p) { return vsliq_m_n_u16(a, b, imm, p); }
[[gnu::always_inline]] nce uint32x4_t move_long_bottom(uint16x8_t a) { return vmovlbq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t move_long_bottom(uint16x8_t inactive, uint8x16_t a, mve_pred16_t p) { return vmovlbq_m_u8(inactive, a, p); }
[[gnu::always_inline]] nce uint32x4_t move_long_bottom(uint16x8_t a, mve_pred16_t p) { return vmovlbq_x_u16(a, p); }
[[gnu::always_inline]] nce uint32x4_t move_long_top(uint16x8_t a) { return vmovltq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t move_long_top(uint16x8_t inactive, uint8x16_t a, mve_pred16_t p) { return vmovltq_m_u8(inactive, a, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round_saturate(uint16x8_t inactive, uint16x8_t a, int16x8_t b, mve_pred16_t p) { return vqrshlq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_saturate(uint16x8_t inactive, uint16x8_t a, int16x8_t b, mve_pred16_t p) { return vqshlq_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t predicate_select(uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vpselq_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t bit_reverse_shift_right(uint16x8_t inactive, uint16x8_t a, int32_t b, mve_pred16_t p) { return vbrsrq_m_n_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_right_round(uint16x8_t inactive, uint16x8_t a, const int imm, mve_pred16_t p) { return vrshrq_m_n_u16(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t shift_right(uint16x8_t inactive, uint16x8_t a, const int imm, mve_pred16_t p) { return vshrq_m_n_u16(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t shift_right_insert(uint16x8_t a, uint16x8_t b, const int imm, mve_pred16_t p) { return vsriq_m_n_u16(a, b, imm, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_saturate(uint16x8_t inactive, uint16x8_t a, const int imm, mve_pred16_t p) { return vqshlq_m_n_u16(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_unsigned_saturate(uint16x8_t inactive, int16x8_t a, const int imm, mve_pred16_t p) { return vqshluq_m_n_s16(inactive, a, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_round_saturate_bottom(uint16x8_t a, int32x4_t b) { return vqrshrunbq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_round_saturate_bottom(uint16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vqrshrunbq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_round_saturate_top(uint16x8_t a, int32x4_t b) { return vqrshruntq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_round_saturate_top(uint16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vqrshruntq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_saturate_bottom(uint16x8_t a, int32x4_t b) { return vqshrunbq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_saturate_bottom(uint16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vqshrunbq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_saturate_top(uint16x8_t a, int32x4_t b) { return vqshruntq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_saturate_bottom(uint16x8_t a, int32x4_t b) { return vqmovunbq_s32(a, b); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_saturate_bottom(uint16x8_t a, int32x4_t b, mve_pred16_t p) { return vqmovunbq_m_s32(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_saturate_top(uint16x8_t a, int32x4_t b) { return vqmovuntq_s32(a, b); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_saturate_top(uint16x8_t a, int32x4_t b, mve_pred16_t p) { return vqmovuntq_m_s32(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_saturate_top(uint16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vqshruntq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_round_saturate_bottom(uint16x8_t a, uint32x4_t b) { return vqrshrnbq_n_u32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_round_saturate_bottom(uint16x8_t a, uint32x4_t b, const int imm, mve_pred16_t p) { return vqrshrnbq_m_n_u32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shight_right_narrow_round_saturate_top(uint16x8_t a, uint32x4_t b) { return vqrshrntq_n_u32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shight_right_narrow_round_saturate_top(uint16x8_t a, uint32x4_t b, const int imm, mve_pred16_t p) { return vqrshrntq_m_n_u32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_saturate_bottom(uint16x8_t a, uint32x4_t b) { return vqshrnbq_n_u32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_saturate_bottom(uint16x8_t a, uint32x4_t b, const int imm, mve_pred16_t p) { return vqshrnbq_m_n_u32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_saturate_top(uint16x8_t a, uint32x4_t b) { return vqshrntq_n_u32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_saturate_top(uint16x8_t a, uint32x4_t b, const int imm, mve_pred16_t p) { return vqshrntq_m_n_u32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_round_bottom(uint16x8_t a, uint32x4_t b) { return vrshrnbq_n_u32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_round_bottom(uint16x8_t a, uint32x4_t b, const int imm, mve_pred16_t p) { return vrshrnbq_m_n_u32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_round_top(uint16x8_t a, uint32x4_t b) { return vrshrntq_n_u32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_round_top(uint16x8_t a, uint32x4_t b, const int imm, mve_pred16_t p) { return vrshrntq_m_n_u32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_bottom(uint16x8_t a, uint32x4_t b) { return vshrnbq_n_u32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_bottom(uint16x8_t a, uint32x4_t b, const int imm, mve_pred16_t p) { return vshrnbq_m_n_u32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_top_signed(uint16x8_t a, uint32x4_t b) { return vshrntq_n_u32(a, b, imm); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_bottom(uint16x8_t a, uint32x4_t b) { return vmovnbq_u32(a, b); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_bottom(uint16x8_t a, uint32x4_t b, mve_pred16_t p) { return vmovnbq_m_u32(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_top(uint16x8_t a, uint32x4_t b) { return vmovntq_u32(a, b); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_top(uint16x8_t a, uint32x4_t b, mve_pred16_t p) { return vmovntq_m_u32(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_saturate_bottom(uint16x8_t a, uint32x4_t b) { return vqmovnbq_u32(a, b); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_saturate_bottom(uint16x8_t a, uint32x4_t b, mve_pred16_t p) { return vqmovnbq_m_u32(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_saturate_top(uint16x8_t a, uint32x4_t b) { return vqmovntq_u32(a, b); }
[[gnu::always_inline]] nce uint16x8_t move_narrow_saturate_top(uint16x8_t a, uint32x4_t b, mve_pred16_t p) { return vqmovntq_m_u32(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_right_narrow_top_signed(uint16x8_t a, uint32x4_t b, const int imm, mve_pred16_t p) { return vshrntq_m_n_u32(a, b, imm, p); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint16x8_t a, mve_pred16_t p) { return vaddvq_p_u16(a, p); }
[[gnu::always_inline]] nce uint16x8_t count_leading_zero_bits(uint16x8_t a, mve_pred16_t p) { return vclzq_x_u16(a, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_not(uint16x8_t a, mve_pred16_t p) { return vmvnq_x_u16(a, p); }
[[gnu::always_inline]] nce uint32x4_t move_long_top(uint16x8_t a, mve_pred16_t p) { return vmovltq_x_u16(a, p); }
[[gnu::always_inline]] nce uint16x8_t add_halve(uint16x8_t a, uint16_t b) { return vhaddq_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_halve(uint16x8_t a, uint16_t b, mve_pred16_t p) { return vhaddq_x_n_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t add_saturate(uint16x8_t a, uint16_t b) { return vqaddq_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t a, uint16_t b, mve_pred16_t p) { return vmulq_x_n_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract(uint16x8_t a, uint16_t b) { return vsubq_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract(uint16x8_t a, uint16_t b, mve_pred16_t p) { return vsubq_x_n_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract_halve(uint16x8_t a, uint16_t b) { return vhsubq_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_halve(uint16x8_t a, uint16_t b, mve_pred16_t p) { return vhsubq_x_n_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t subtract_saturate(uint16x8_t a, uint16_t b) { return vqsubq_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t bitwise_clear(uint16x8_t a, const uint16_t imm) { return vbicq_n_u16(a, imm); }
[[gnu::always_inline]] nce uint16x8_t bitwise_clear(uint16x8_t a, const uint16_t imm, mve_pred16_t p) { return vbicq_m_n_u16(a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_not(uint16x8_t inactive, const uint16_t imm, mve_pred16_t p) { return vmvnq_m_n_u16(inactive, imm, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_or(uint16x8_t a, const uint16_t imm) { return vorrq_n_u16(a, imm); }
[[gnu::always_inline]] nce uint16x8_t bitwise_or(uint16x8_t a, const uint16_t imm, mve_pred16_t p) { return vorrq_m_n_u16(a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t bit_reverse_shift_right(uint16x8_t a, int32_t b) { return vbrsrq_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t bit_reverse_shift_right(uint16x8_t a, int32_t b, mve_pred16_t p) { return vbrsrq_x_n_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_right_round(uint16x8_t a, const int imm, mve_pred16_t p) { return vrshrq_x_n_u16(a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t shift_right(uint16x8_t a, const int imm, mve_pred16_t p) { return vshrq_x_n_u16(a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round_saturate(uint16x8_t a, int32_t b) { return vqrshlq_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round_saturate(uint16x8_t a, int32_t b, mve_pred16_t p) { return vqrshlq_m_n_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left_saturate(uint16x8_t a, int32_t b) { return vqshlq_r_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t shift_left_saturate(uint16x8_t a, int32_t b, mve_pred16_t p) { return vqshlq_m_r_u16(a, b, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t a, const int imm, mve_pred16_t p) { return vshlq_x_n_u16(a, imm, p); }
[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t a, int32_t b) { return vshlq_r_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t a, int32_t b, mve_pred16_t p) { return vshlq_m_r_u16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t reverse_32bit(int16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vrev32q_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t reverse_64bit(int16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vrev64q_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vcmpneq_m_s16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int16x8_t a, int16x8_t b) { return vcmpgeq_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vcmpgeq_m_s16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int16x8_t a, int16x8_t b) { return vcmpgtq_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vcmpgtq_m_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t reverse_64bit(int16x8_t a, mve_pred16_t p) { return vrev64q_x_s16(a, p); }
[[gnu::always_inline]] nce int16x8_t uninitialized(int16x8_t t) { return vuninitializedq(t); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int16x8_t a, int16x8_t b) { return vcmpeqq_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vcmpeqq_m_s16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int16x8_t a, int16x8_t b) { return vcmpneq_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int16x8_t a, int16x8_t b) { return vcmpleq_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vcmpleq_m_s16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int16x8_t a, int16x8_t b) { return vcmpltq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t min(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vminq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t max(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmaxq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract_absolute(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vabdq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t add(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vaddq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vcmpltq_m_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t min(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vminq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t max(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmaxq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract_absolute(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vabdq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t abs(int16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vabsq_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t abs_saturate(int16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vqabsq_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t add(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vaddq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t add(int16x8_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vaddq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t reverse_32bit(int16x8_t a, mve_pred16_t p) { return vrev32q_x_s16(a, p); }
[[gnu::always_inline]] nce int16x8_t abs(int16x8_t a, mve_pred16_t p) { return vabsq_x_s16(a, p); }
[[gnu::always_inline]] nce int32_t reduce_add(int16x8_t a, mve_pred16_t p) { return vaddvq_p_s16(a, p); }
[[gnu::always_inline]] nce int16x8_t duplicate(int16x8_t inactive, int16_t a, mve_pred16_t p) { return vdupq_m_n_s16(inactive, a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int16x8_t a, int16_t b) { return vcmpeqq_n_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int16x8_t a, int16_t b, mve_pred16_t p) { return vcmpeqq_m_n_s16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int16x8_t a, int16_t b) { return vcmpneq_n_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int16x8_t a, int16_t b, mve_pred16_t p) { return vcmpneq_m_n_s16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int16x8_t a, int16_t b) { return vcmpgeq_n_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int16x8_t a, int16_t b, mve_pred16_t p) { return vcmpgeq_m_n_s16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int16x8_t a, int16_t b) { return vcmpgtq_n_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int16x8_t a, int16_t b, mve_pred16_t p) { return vcmpgtq_m_n_s16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int16x8_t a, int16_t b) { return vcmpleq_n_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int16x8_t a, int16_t b, mve_pred16_t p) { return vcmpleq_m_n_s16(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int16x8_t a, int16_t b) { return vcmpltq_n_s16(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int16x8_t a, int16_t b, mve_pred16_t p) { return vcmpltq_m_n_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t add(int16x8_t a, int16_t b) { return vaddq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add(int16x8_t a, int16_t b, mve_pred16_t p) { return vaddq_x_n_s16(a, b, p); }
[[gnu::always_inline]] nce int32_t reduce_add(int16x8_t a) { return vaddvq_s16(a); }
[[gnu::always_inline]] nce int16x8_t multiply_long_bottom(int16x8_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmullbq_int_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_long_top(int16x8_t inactive, int8x16_t a, int8x16_t b, mve_pred16_t p) { return vmulltq_int_m_s8(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t add_halve(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vhaddq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t add_halve_round(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vrhaddq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t add_saturate(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqaddq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t add_halve(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vhaddq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t add_halve_round(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vrhaddq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t add_halve(int16x8_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vhaddq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t add_saturate(int16x8_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vqaddq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_high(int16x8_t a, int16x8_t b) { return vmulhq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_high(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmulhq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_high(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmulhq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_long_bottom(int16x8_t a, int16x8_t b) { return vmullbq_int_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_long_bottom(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmullbq_int_x_s16(a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_long_top(int16x8_t a, int16x8_t b) { return vmulltq_int_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmulq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_round_high(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vrmulhq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_add_double_saturate_high(int16x8_t inactive, int16x8_t a, int16x8_t b) { return vqdmladhq_s16(inactive, a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_add_double_saturate_high(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqdmladhq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_add_double_saturate_high_exchange_pairs(int16x8_t inactive, int16x8_t a, int16x8_t b) { return vqdmladhxq_s16(inactive, a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_add_double_saturate_high_exchange_pairs(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqdmladhxq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_add_dual_double_round_saturate_high(int16x8_t inactive, int16x8_t a, int16x8_t b) { return vqrdmladhq_s16(inactive, a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_add_dual_double_round_saturate_high(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqrdmladhq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t mulitply_add_dual_double_round_saturate_high_exchange_pairs(int16x8_t inactive, int16x8_t a, int16x8_t b) { return vqrdmladhxq_s16(inactive, a, b); }
[[gnu::always_inline]] nce int16x8_t mulitply_add_dual_double_round_saturate_high_exchange_pairs(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqrdmladhxq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_long_top(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmulltq_int_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmulq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_round_high(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vrmulhq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vmulq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_round_high(int16x8_t a, int16x8_t b) { return vrmulhq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_dual_double_saturate_high(int16x8_t inactive, int16x8_t a, int16x8_t b) { return vqdmlsdhq_s16(inactive, a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_dual_double_saturate_high(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqdmlsdhq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_dual_double_saturate_high_exchange_pairs(int16x8_t inactive, int16x8_t a, int16x8_t b) { return vqdmlsdhxq_s16(inactive, a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_dual_double_saturate_high_exchange_pairs(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqdmlsdhxq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_dual_double_round_saturate_high(int16x8_t inactive, int16x8_t a, int16x8_t b) { return vqrdmlsdhq_s16(inactive, a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_dual_double_round_saturate_high(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqrdmlsdhq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_dual_double_round_saturate_high_exchange_pairs(int16x8_t inactive, int16x8_t a, int16x8_t b) { return vqrdmlsdhxq_s16(inactive, a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_dual_double_round_saturate_high_exchange_pairs(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqrdmlsdhxq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqdmulhq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqrdmulhq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_add_double_round_saturate_high(int16x8_t m1, int16x8_t m2, int16_t add) { return vqrdmlashq_n_s16(m1, m2, add); }
[[gnu::always_inline]] nce int16x8_t multiply_add_double_round_saturate_high(int16x8_t m1, int16x8_t m2, int16_t add, mve_pred16_t p) { return vqrdmlashq_m_n_s16(m1, m2, add, p); }
[[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high(int16x8_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vqdmulhq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high(int16x8_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vqrdmulhq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_bottom(int16x8_t a, int16x8_t b) { return vqdmullbq_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_top(int16x8_t a, int16x8_t b) { return vqdmulltq_s16(a, b); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add(int16x8_t m1, int16x8_t m2) { return vmladavq_s16(m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add(int16x8_t m1, int16x8_t m2, mve_pred16_t p) { return vmladavq_p_s16(m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_exchange_pairs(int16x8_t m1, int16x8_t m2) { return vmladavxq_s16(m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_exchange_pairs(int16x8_t m1, int16x8_t m2, mve_pred16_t p) { return vmladavxq_p_s16(m1, m2, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add(int16x8_t m1, int16x8_t m2) { return vmlaldavq_s16(m1, m2); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add(int16x8_t m1, int16x8_t m2, mve_pred16_t p) { return vmlaldavq_p_s16(m1, m2, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_exchange_pairs(int16x8_t m1, int16x8_t m2) { return vmlaldavxq_s16(m1, m2); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_exchange_pairs(int16x8_t m1, int16x8_t m2, mve_pred16_t p) { return vmlaldavxq_p_s16(m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmlsdavq_p_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_add_double_saturate_high(int16x8_t add, int16x8_t m1, int16_t m2) { return vqdmlahq_n_s16(add, m1, m2); }
[[gnu::always_inline]] nce int16x8_t multiply_add_double_saturate_high(int16x8_t add, int16x8_t m1, int16_t m2, mve_pred16_t p) { return vqdmlahq_m_n_s16(add, m1, m2, p); }
[[gnu::always_inline]] nce int16x8_t multiply_add_double_round_saturate_high(int16x8_t add, int16x8_t m1, int16_t m2) { return vqrdmlahq_n_s16(add, m1, m2); }
[[gnu::always_inline]] nce int16x8_t multiply_add_double_round_saturate_high(int16x8_t add, int16x8_t m1, int16_t m2, mve_pred16_t p) { return vqrdmlahq_m_n_s16(add, m1, m2, p); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_double_saturate_high(int16x8_t m1, int16x8_t m2, int16_t add) { return vqdmlashq_n_s16(m1, m2, add); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_double_saturate_high(int16x8_t m1, int16x8_t m2, int16_t add, mve_pred16_t p) { return vqdmlashq_m_n_s16(m1, m2, add, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_exchange_pairs(int16x8_t a, int16x8_t b) { return vmlsdavxq_s16(a, b); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_exchange_pairs(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmlsdavxq_p_s16(a, b, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add(int16x8_t a, int16x8_t b) { return vmlsldavq_s16(a, b); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmlsldavq_p_s16(a, b, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_exchange_pairs(int16x8_t a, int16x8_t b) { return vmlsldavxq_s16(a, b); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_exchange_pairs(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmlsldavxq_p_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t multiply_add(int16x8_t add, int16x8_t m1, int16_t m2) { return vmlaq_n_s16(add, m1, m2); }
[[gnu::always_inline]] nce int16x8_t multiply_add(int16x8_t add, int16x8_t m1, int16_t m2, mve_pred16_t p) { return vmlaq_m_n_s16(add, m1, m2, p); }
[[gnu::always_inline]] nce int16x8_t multiply_add(int16x8_t m1, int16x8_t m2, int16_t add) { return vmlasq_n_s16(m1, m2, add); }
[[gnu::always_inline]] nce int16x8_t multiply_add(int16x8_t m1, int16x8_t m2, int16_t add, mve_pred16_t p) { return vmlasq_m_n_s16(m1, m2, add, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add(int16x8_t a, int16x8_t b) { return vmlsdavq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vsubq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract_halve(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vhsubq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract_saturate(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqsubq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_clear(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vbicq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_and(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vandq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_xor(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return veorq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_or_not(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vornq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_or(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vorrq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_270(int16x8_t a, int16x8_t b) { return vcaddq_rot270_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_90(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vcaddq_rot90_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_270(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vcaddq_rot270_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_270_halve(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vhcaddq_rot270_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vsubq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract_halve(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vhsubq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t count_leading_sign_bits(int16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vclsq_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t count_leading_zero_bits(int16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vclzq_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_clear(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vbicq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t negate(int16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vnegq_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t negate_saturate(int16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vqnegq_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_and(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vandq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_xor(int16x8_t a, int16x8_t b, mve_pred16_t p) { return veorq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_not(int16x8_t inactive, int16x8_t a, mve_pred16_t p) { return vmvnq_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_or_not(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vornq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_or(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vorrq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_90(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vcaddq_rot90_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_270(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vcaddq_rot270_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_90_halve(int16x8_t a, int16x8_t b) { return vhcaddq_rot90_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_90_halve(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vhcaddq_rot90_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_90_halve(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vhcaddq_rot90_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_270_halve(int16x8_t a, int16x8_t b) { return vhcaddq_rot270_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_270_halve(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vhcaddq_rot270_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract(int16x8_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vsubq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract_halve(int16x8_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vhsubq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract_saturate(int16x8_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vqsubq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t complex_add_rotate_90(int16x8_t a, int16x8_t b) { return vcaddq_rot90_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left_round_saturate(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqrshlq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t shift_left_saturate(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqshlq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t bit_reverse_shift_right(int16x8_t inactive, int16x8_t a, int32_t b, mve_pred16_t p) { return vbrsrq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t shift_right_round(int16x8_t inactive, int16x8_t a, const int imm, mve_pred16_t p) { return vrshrq_m_n_s16(inactive, a, imm, p); }
[[gnu::always_inline]] nce int16x8_t shift_right(int16x8_t inactive, int16x8_t a, const int imm, mve_pred16_t p) { return vshrq_m_n_s16(inactive, a, imm, p); }
[[gnu::always_inline]] nce int16x8_t shift_right_insert(int16x8_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vsriq_m_n_s16(a, b, imm, p); }
[[gnu::always_inline]] nce int16x8_t shift_left_saturate(int16x8_t inactive, int16x8_t a, const int imm, mve_pred16_t p) { return vqshlq_m_n_s16(inactive, a, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_right_narrow_round_saturate_bottom(int16x8_t a, int32x4_t b) { return vqrshrnbq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce int16x8_t shift_right_narrow_round_saturate_bottom(int16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vqrshrnbq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shight_right_narrow_round_saturate_top(int16x8_t a, int32x4_t b) { return vqrshrntq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce int16x8_t shight_right_narrow_round_saturate_top(int16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vqrshrntq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_right_narrow_saturate_bottom(int16x8_t a, int32x4_t b) { return vqshrnbq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce int16x8_t shift_right_narrow_saturate_bottom(int16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vqshrnbq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_right_narrow_saturate_top(int16x8_t a, int32x4_t b) { return vqshrntq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce int16x8_t shift_right_narrow_saturate_top(int16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vqshrntq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_right_narrow_round_bottom(int16x8_t a, int32x4_t b) { return vrshrnbq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce int16x8_t shift_right_narrow_round_bottom(int16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vrshrnbq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_right_narrow_round_top(int16x8_t a, int32x4_t b) { return vrshrntq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce int16x8_t shift_right_narrow_round_top(int16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vrshrntq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_right_narrow_bottom(int16x8_t a, int32x4_t b) { return vshrnbq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce int16x8_t shift_right_narrow_bottom(int16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vshrnbq_m_n_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_right_narrow_top_signed(int16x8_t a, int32x4_t b) { return vshrntq_n_s32(a, b, imm); }
[[gnu::always_inline]] nce int16x8_t shift_right_narrow_top_signed(int16x8_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vshrntq_m_n_s32(a, b, imm, p); }
[[gnu::always_inline]] nce int16x8_t bit_reverse_shift_right(int16x8_t a, int32_t b) { return vbrsrq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t bit_reverse_shift_right(int16x8_t a, int32_t b, mve_pred16_t p) { return vbrsrq_x_n_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t shift_right_round(int16x8_t a, const int imm, mve_pred16_t p) { return vrshrq_x_n_s16(a, imm, p); }
[[gnu::always_inline]] nce int16x8_t shift_right(int16x8_t a, const int imm, mve_pred16_t p) { return vshrq_x_n_s16(a, imm, p); }
[[gnu::always_inline]] nce int16x8_t shift_left_round_saturate(int16x8_t a, int32_t b) { return vqrshlq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left_round_saturate(int16x8_t a, int32_t b, mve_pred16_t p) { return vqrshlq_m_n_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t shift_left_saturate(int16x8_t a, int32_t b) { return vqshlq_r_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left_saturate(int16x8_t a, int32_t b, mve_pred16_t p) { return vqshlq_m_r_s16(a, b, p); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t shift_left_unsigned_saturate(int16x8_t a) { return vqshluq_n_s16(a, imm); }
[[gnu::always_inline]] nce int16x8_t shift_left_long_bottom(int16x8_t inactive, int8x16_t a, const int imm, mve_pred16_t p) { return vshllbq_m_n_s8(inactive, a, imm, p); }
[[gnu::always_inline]] nce int16x8_t shift_left_long_top(int16x8_t inactive, int8x16_t a, const int imm, mve_pred16_t p) { return vshlltq_m_n_s8(inactive, a, imm, p); }
[[gnu::always_inline]] nce int16x8_t shift_left_round(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vrshlq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vshlq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int16x8_t shift_left_round(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vrshlq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vshlq_x_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t shift_left_round(int16x8_t a, int32_t b) { return vrshlq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left_round(int16x8_t a, int32_t b, mve_pred16_t p) { return vrshlq_m_n_s16(a, b, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_left_carry(int16x8_t a, uint32_t *b) { return vshlcq_s16(a, b, imm); }
[[gnu::always_inline]] nce int16x8_t shift_left_carry(int16x8_t a, uint32_t *b, const int imm, mve_pred16_t p) { return vshlcq_m_s16(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int32x4_t shift_left_long_bottom(int16x8_t a) { return vshllbq_n_s16(a, imm); }
[[gnu::always_inline]] nce int32x4_t shift_left_long_bottom(int16x8_t a, const int imm, mve_pred16_t p) { return vshllbq_x_n_s16(a, imm, p); }
template <int imm>[[gnu::always_inline]] nce int32x4_t shift_left_long_top(int16x8_t a) { return vshlltq_n_s16(a, imm); }
[[gnu::always_inline]] nce int32x4_t shift_left_long_top(int16x8_t a, const int imm, mve_pred16_t p) { return vshlltq_x_n_s16(a, imm, p); }
template <int imm>[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t a) { return vshlq_n_s16(a, imm); }
[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t inactive, int16x8_t a, const int imm, mve_pred16_t p) { return vshlq_m_n_s16(inactive, a, imm, p); }
[[gnu::always_inline]] nce int16x8_t shift_left_insert(int16x8_t a, int16x8_t b, const int imm, mve_pred16_t p) { return vsliq_m_n_s16(a, b, imm, p); }
[[gnu::always_inline]] nce int32x4_t move_long_bottom(int16x8_t a) { return vmovlbq_s16(a); }
[[gnu::always_inline]] nce int16x8_t move_long_bottom(int16x8_t inactive, int8x16_t a, mve_pred16_t p) { return vmovlbq_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t move_long_bottom(int16x8_t a, mve_pred16_t p) { return vmovlbq_x_s16(a, p); }
[[gnu::always_inline]] nce int32x4_t move_long_top(int16x8_t a) { return vmovltq_s16(a); }
[[gnu::always_inline]] nce int16x8_t move_long_top(int16x8_t inactive, int8x16_t a, mve_pred16_t p) { return vmovltq_m_s8(inactive, a, p); }
[[gnu::always_inline]] nce int16x8_t predicate_select(int16x8_t a, int16x8_t b, mve_pred16_t p) { return vpselq_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t move_narrow_bottom(int16x8_t a, int32x4_t b) { return vmovnbq_s32(a, b); }
[[gnu::always_inline]] nce int16x8_t move_narrow_bottom(int16x8_t a, int32x4_t b, mve_pred16_t p) { return vmovnbq_m_s32(a, b, p); }
[[gnu::always_inline]] nce int16x8_t move_narrow_top(int16x8_t a, int32x4_t b) { return vmovntq_s32(a, b); }
[[gnu::always_inline]] nce int16x8_t move_narrow_top(int16x8_t a, int32x4_t b, mve_pred16_t p) { return vmovntq_m_s32(a, b, p); }
[[gnu::always_inline]] nce int16x8_t move_narrow_saturate_bottom(int16x8_t a, int32x4_t b) { return vqmovnbq_s32(a, b); }
[[gnu::always_inline]] nce int16x8_t move_narrow_saturate_bottom(int16x8_t a, int32x4_t b, mve_pred16_t p) { return vqmovnbq_m_s32(a, b, p); }
[[gnu::always_inline]] nce int16x8_t move_narrow_saturate_top(int16x8_t a, int32x4_t b) { return vqmovntq_s32(a, b); }
[[gnu::always_inline]] nce int16x8_t move_narrow_saturate_top(int16x8_t a, int32x4_t b, mve_pred16_t p) { return vqmovntq_m_s32(a, b, p); }
[[gnu::always_inline]] nce int16x8_t count_leading_sign_bits(int16x8_t a, mve_pred16_t p) { return vclsq_x_s16(a, p); }
[[gnu::always_inline]] nce int16x8_t count_leading_zero_bits(int16x8_t a, mve_pred16_t p) { return vclzq_x_s16(a, p); }
[[gnu::always_inline]] nce int16x8_t negate(int16x8_t a, mve_pred16_t p) { return vnegq_x_s16(a, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_not(int16x8_t a, mve_pred16_t p) { return vmvnq_x_s16(a, p); }
[[gnu::always_inline]] nce int32x4_t move_long_top(int16x8_t a, mve_pred16_t p) { return vmovltq_x_s16(a, p); }
[[gnu::always_inline]] nce int16x8_t add_halve(int16x8_t a, int16_t b) { return vhaddq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add_halve(int16x8_t a, int16_t b, mve_pred16_t p) { return vhaddq_x_n_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t add_saturate(int16x8_t a, int16_t b) { return vqaddq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t a, int16_t b, mve_pred16_t p) { return vmulq_x_n_s16(a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_bottom(int16x8_t a, int16_t b) { return vqdmullbq_n_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_top(int16x8_t a, int16_t b) { return vqdmulltq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract(int16x8_t a, int16_t b) { return vsubq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract(int16x8_t a, int16_t b, mve_pred16_t p) { return vsubq_x_n_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract_halve(int16x8_t a, int16_t b) { return vhsubq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_halve(int16x8_t a, int16_t b, mve_pred16_t p) { return vhsubq_x_n_s16(a, b, p); }
[[gnu::always_inline]] nce int16x8_t subtract_saturate(int16x8_t a, int16_t b) { return vqsubq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t bitwise_clear(int16x8_t a, const int16_t imm) { return vbicq_n_s16(a, imm); }
[[gnu::always_inline]] nce int16x8_t bitwise_clear(int16x8_t a, const int16_t imm, mve_pred16_t p) { return vbicq_m_n_s16(a, imm, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_not(int16x8_t inactive, const int16_t imm, mve_pred16_t p) { return vmvnq_m_n_s16(inactive, imm, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_or(int16x8_t a, const int16_t imm) { return vorrq_n_s16(a, imm); }
[[gnu::always_inline]] nce int16x8_t bitwise_or(int16x8_t a, const int16_t imm, mve_pred16_t p) { return vorrq_m_n_s16(a, imm, p); }
[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t a, const int imm, mve_pred16_t p) { return vshlq_x_n_s16(a, imm, p); }
[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t a, int32_t b) { return vshlq_r_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t a, int32_t b, mve_pred16_t p) { return vshlq_m_r_s16(a, b, p); }
[[gnu::always_inline]] nce int32x4_t reverse_64bit(int32x4_t inactive, int32x4_t a, mve_pred16_t p) { return vrev64q_m_s32(inactive, a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vcmpneq_m_s32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int32x4_t a, int32x4_t b) { return vcmpgeq_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vcmpgeq_m_s32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int32x4_t a, int32x4_t b) { return vcmpgtq_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vcmpgtq_m_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t reverse_64bit(int32x4_t a, mve_pred16_t p) { return vrev64q_x_s32(a, p); }
[[gnu::always_inline]] nce int32x4_t duplicate(int32x4_t inactive, int32_t a, mve_pred16_t p) { return vdupq_m_n_s32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t uninitialized(int32x4_t t) { return vuninitializedq(t); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int32x4_t a, int32x4_t b) { return vcmpeqq_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vcmpeqq_m_s32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int32x4_t a, int32x4_t b) { return vcmpneq_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int32x4_t a, int32x4_t b) { return vcmpleq_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vcmpleq_m_s32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int32x4_t a, int32x4_t b) { return vcmpltq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t min(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vminq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t max(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmaxq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract_absolute(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vabdq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t add(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vaddq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t add_carry_initialized(int32x4_t inactive, int32x4_t a, int32x4_t b, unsigned *carry_out, mve_pred16_t p) { return vadciq_m_s32(inactive, a, b, carry_out, p); }
[[gnu::always_inline]] nce int32x4_t add_carry(int32x4_t inactive, int32x4_t a, int32x4_t b, unsigned *carry, mve_pred16_t p) { return vadcq_m_s32(inactive, a, b, carry, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vcmpltq_m_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t min(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vminq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t max(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmaxq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract_absolute(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vabdq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t abs(int32x4_t inactive, int32x4_t a, mve_pred16_t p) { return vabsq_m_s32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t abs_saturate(int32x4_t inactive, int32x4_t a, mve_pred16_t p) { return vqabsq_m_s32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t add(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vaddq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t add_carry_initialized(int32x4_t a, int32x4_t b, unsigned *carry_out) { return vadciq_s32(a, b, carry_out); }
[[gnu::always_inline]] nce int32x4_t add_carry(int32x4_t a, int32x4_t b, unsigned *carry) { return vadcq_s32(a, b, carry); }
[[gnu::always_inline]] nce int32x4_t add(int32x4_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vaddq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t abs(int32x4_t a, mve_pred16_t p) { return vabsq_x_s32(a, p); }
[[gnu::always_inline]] nce int64_t reduce_add_long(int32x4_t a, mve_pred16_t p) { return vaddlvq_p_s32(a, p); }
[[gnu::always_inline]] nce int32_t reduce_add(int32x4_t a, mve_pred16_t p) { return vaddvq_p_s32(a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int32x4_t a, int32_t b) { return vcmpeqq_n_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(int32x4_t a, int32_t b, mve_pred16_t p) { return vcmpeqq_m_n_s32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int32x4_t a, int32_t b) { return vcmpneq_n_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(int32x4_t a, int32_t b, mve_pred16_t p) { return vcmpneq_m_n_s32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int32x4_t a, int32_t b) { return vcmpgeq_n_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than_or_equal(int32x4_t a, int32_t b, mve_pred16_t p) { return vcmpgeq_m_n_s32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int32x4_t a, int32_t b) { return vcmpgtq_n_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_greater_than(int32x4_t a, int32_t b, mve_pred16_t p) { return vcmpgtq_m_n_s32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int32x4_t a, int32_t b) { return vcmpleq_n_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than_or_equal(int32x4_t a, int32_t b, mve_pred16_t p) { return vcmpleq_m_n_s32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int32x4_t a, int32_t b) { return vcmpltq_n_s32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_less_than(int32x4_t a, int32_t b, mve_pred16_t p) { return vcmpltq_m_n_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t add(int32x4_t a, int32_t b) { return vaddq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add(int32x4_t a, int32_t b, mve_pred16_t p) { return vaddq_x_n_s32(a, b, p); }
[[gnu::always_inline]] nce int64_t reduce_add_long(int32x4_t a) { return vaddlvq_s32(a); }
[[gnu::always_inline]] nce int32_t reduce_add(int32x4_t a) { return vaddvq_s32(a); }
[[gnu::always_inline]] nce int32x4_t multiply_long_bottom(int32x4_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmullbq_int_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_long_top(int32x4_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vmulltq_int_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_bottom(int32x4_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqdmullbq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_top(int32x4_t inactive, int16x8_t a, int16x8_t b, mve_pred16_t p) { return vqdmulltq_m_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_bottom(int32x4_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vqdmullbq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long_top(int32x4_t inactive, int16x8_t a, int16_t b, mve_pred16_t p) { return vqdmulltq_m_n_s16(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t add_halve(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vhaddq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t add_halve_round(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vrhaddq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t add_saturate(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqaddq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t add_halve(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vhaddq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t add_halve_round(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vrhaddq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t add_halve(int32x4_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vhaddq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t add_saturate(int32x4_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vqaddq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_high(int32x4_t a, int32x4_t b) { return vmulhq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_high(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmulhq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_high(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmulhq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_long_bottom(int32x4_t a, int32x4_t b) { return vmullbq_int_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_long_bottom(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmullbq_int_x_s32(a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_long_top(int32x4_t a, int32x4_t b) { return vmulltq_int_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmulq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_round_high(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vrmulhq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_add_double_saturate_high(int32x4_t inactive, int32x4_t a, int32x4_t b) { return vqdmladhq_s32(inactive, a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_add_double_saturate_high(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqdmladhq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_add_double_saturate_high_exchange_pairs(int32x4_t inactive, int32x4_t a, int32x4_t b) { return vqdmladhxq_s32(inactive, a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_add_double_saturate_high_exchange_pairs(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqdmladhxq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_add_dual_double_round_saturate_high(int32x4_t inactive, int32x4_t a, int32x4_t b) { return vqrdmladhq_s32(inactive, a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_add_dual_double_round_saturate_high(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqrdmladhq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t mulitply_add_dual_double_round_saturate_high_exchange_pairs(int32x4_t inactive, int32x4_t a, int32x4_t b) { return vqrdmladhxq_s32(inactive, a, b); }
[[gnu::always_inline]] nce int32x4_t mulitply_add_dual_double_round_saturate_high_exchange_pairs(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqrdmladhxq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_dual_double_saturate_high(int32x4_t inactive, int32x4_t a, int32x4_t b) { return vqdmlsdhq_s32(inactive, a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_dual_double_saturate_high(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqdmlsdhq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_dual_double_saturate_high_exchange_pairs(int32x4_t inactive, int32x4_t a, int32x4_t b) { return vqdmlsdhxq_s32(inactive, a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_dual_double_saturate_high_exchange_pairs(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqdmlsdhxq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_dual_double_round_saturate_high(int32x4_t inactive, int32x4_t a, int32x4_t b) { return vqrdmlsdhq_s32(inactive, a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_dual_double_round_saturate_high(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqrdmlsdhq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_dual_double_round_saturate_high_exchange_pairs(int32x4_t inactive, int32x4_t a, int32x4_t b) { return vqrdmlsdhxq_s32(inactive, a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_dual_double_round_saturate_high_exchange_pairs(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqrdmlsdhxq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqdmulhq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqrdmulhq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_long_top(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmulltq_int_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmulq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_round_high(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vrmulhq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_double_saturate_high(int32x4_t m1, int32x4_t m2, int32_t add, mve_pred16_t p) { return vqdmlashq_m_n_s32(m1, m2, add, p); }
[[gnu::always_inline]] nce int32x4_t multiply_add_double_round_saturate_high(int32x4_t m1, int32x4_t m2, int32_t add) { return vqrdmlashq_n_s32(m1, m2, add); }
[[gnu::always_inline]] nce int32x4_t multiply_add_double_round_saturate_high(int32x4_t m1, int32x4_t m2, int32_t add, mve_pred16_t p) { return vqrdmlashq_m_n_s32(m1, m2, add, p); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high(int32x4_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vqdmulhq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high(int32x4_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vqrdmulhq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_bottom(int32x4_t a, int32x4_t b) { return vqdmullbq_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_top(int32x4_t a, int32x4_t b) { return vqdmulltq_s32(a, b); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add(int32x4_t m1, int32x4_t m2) { return vmladavq_s32(m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add(int32x4_t m1, int32x4_t m2, mve_pred16_t p) { return vmladavq_p_s32(m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_exchange_pairs(int32x4_t m1, int32x4_t m2) { return vmladavxq_s32(m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_exchange_pairs(int32x4_t m1, int32x4_t m2, mve_pred16_t p) { return vmladavxq_p_s32(m1, m2, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add(int32x4_t m1, int32x4_t m2) { return vmlaldavq_s32(m1, m2); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add(int32x4_t m1, int32x4_t m2, mve_pred16_t p) { return vmlaldavq_p_s32(m1, m2, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_exchange_pairs(int32x4_t m1, int32x4_t m2) { return vmlaldavxq_s32(m1, m2); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_exchange_pairs(int32x4_t m1, int32x4_t m2, mve_pred16_t p) { return vmlaldavxq_p_s32(m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmlsdavq_p_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_add(int32x4_t add, int32x4_t m1, int32_t m2) { return vmlaq_n_s32(add, m1, m2); }
[[gnu::always_inline]] nce int32x4_t multiply_add(int32x4_t add, int32x4_t m1, int32_t m2, mve_pred16_t p) { return vmlaq_m_n_s32(add, m1, m2, p); }
[[gnu::always_inline]] nce int32x4_t multiply_add(int32x4_t m1, int32x4_t m2, int32_t add) { return vmlasq_n_s32(m1, m2, add); }
[[gnu::always_inline]] nce int32x4_t multiply_add(int32x4_t m1, int32x4_t m2, int32_t add, mve_pred16_t p) { return vmlasq_m_n_s32(m1, m2, add, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add(int32x4_t a, int32x4_t b) { return vmlsdavq_s32(a, b); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_exchange_pairs(int32x4_t a, int32x4_t b) { return vmlsdavxq_s32(a, b); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_exchange_pairs(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmlsdavxq_p_s32(a, b, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add(int32x4_t a, int32x4_t b) { return vmlsldavq_s32(a, b); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmlsldavq_p_s32(a, b, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_exchange_pairs(int32x4_t a, int32x4_t b) { return vmlsldavxq_s32(a, b); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_exchange_pairs(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmlsldavxq_p_s32(a, b, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_round_dual_reduce_add_high(int32x4_t a, int32x4_t b) { return vrmlaldavhq_s32(a, b); }
[[gnu::always_inline]] nce int64_t multiply_add_long_round_dual_reduce_add_high(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vrmlaldavhq_p_s32(a, b, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_round_dual_reduce_add_high_exchange_pairs(int32x4_t a, int32x4_t b) { return vrmlaldavhxq_s32(a, b); }
[[gnu::always_inline]] nce int64_t multiply_add_long_round_dual_reduce_add_high_exchange_pairs(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vrmlaldavhxq_p_s32(a, b, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_round_dual_reduce_add_high(int32x4_t a, int32x4_t b) { return vrmlsldavhq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_with_carry_initialized(int32x4_t inactive, int32x4_t a, int32x4_t b, unsigned *carry_out, mve_pred16_t p) { return vsbciq_m_s32(inactive, a, b, carry_out, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_round_dual_reduce_add_high(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vrmlsldavhq_p_s32(a, b, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_round_dual_reduce_add_high_exchange_pairs(int32x4_t a, int32x4_t b) { return vrmlsldavhxq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left_round_saturate(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqrshlq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t shift_left_saturate(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqshlq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t bit_reverse_shift_right(int32x4_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vbrsrq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t shift_right_round(int32x4_t inactive, int32x4_t a, const int imm, mve_pred16_t p) { return vrshrq_m_n_s32(inactive, a, imm, p); }
[[gnu::always_inline]] nce int32x4_t shift_right(int32x4_t inactive, int32x4_t a, const int imm, mve_pred16_t p) { return vshrq_m_n_s32(inactive, a, imm, p); }
[[gnu::always_inline]] nce int32x4_t shift_right_insert(int32x4_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vsriq_m_n_s32(a, b, imm, p); }
[[gnu::always_inline]] nce int32x4_t shift_left_saturate(int32x4_t inactive, int32x4_t a, const int imm, mve_pred16_t p) { return vqshlq_m_n_s32(inactive, a, imm, p); }
[[gnu::always_inline]] nce int32x4_t bit_reverse_shift_right(int32x4_t a, int32_t b) { return vbrsrq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t bit_reverse_shift_right(int32x4_t a, int32_t b, mve_pred16_t p) { return vbrsrq_x_n_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t shift_right_round(int32x4_t a, const int imm, mve_pred16_t p) { return vrshrq_x_n_s32(a, imm, p); }
[[gnu::always_inline]] nce int32x4_t shift_right(int32x4_t a, const int imm, mve_pred16_t p) { return vshrq_x_n_s32(a, imm, p); }
[[gnu::always_inline]] nce int32x4_t shift_left_round_saturate(int32x4_t a, int32_t b) { return vqrshlq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left_round_saturate(int32x4_t a, int32_t b, mve_pred16_t p) { return vqrshlq_m_n_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t shift_left_saturate(int32x4_t a, int32_t b) { return vqshlq_r_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left_saturate(int32x4_t a, int32_t b, mve_pred16_t p) { return vqshlq_m_r_s32(a, b, p); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t shift_left_unsigned_saturate(int32x4_t a) { return vqshluq_n_s32(a, imm); }
[[gnu::always_inline]] nce int32x4_t shift_left_long_bottom(int32x4_t inactive, int16x8_t a, const int imm, mve_pred16_t p) { return vshllbq_m_n_s16(inactive, a, imm, p); }
[[gnu::always_inline]] nce int32x4_t shift_left_long_top(int32x4_t inactive, int16x8_t a, const int imm, mve_pred16_t p) { return vshlltq_m_n_s16(inactive, a, imm, p); }
[[gnu::always_inline]] nce int32x4_t shift_left_round(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vrshlq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vshlq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t shift_left_round(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vrshlq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vshlq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t shift_left_round(int32x4_t a, int32_t b) { return vrshlq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left_round(int32x4_t a, int32_t b, mve_pred16_t p) { return vrshlq_m_n_s32(a, b, p); }
template <int imm>[[gnu::always_inline]] nce int32x4_t shift_left_carry(int32x4_t a, uint32_t *b) { return vshlcq_s32(a, b, imm); }
[[gnu::always_inline]] nce int32x4_t shift_left_carry(int32x4_t a, uint32_t *b, const int imm, mve_pred16_t p) { return vshlcq_m_s32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t a) { return vshlq_n_s32(a, imm); }
[[gnu::always_inline]] nce int32x4_t move_long_bottom(int32x4_t inactive, int16x8_t a, mve_pred16_t p) { return vmovlbq_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t move_long_top(int32x4_t inactive, int16x8_t a, mve_pred16_t p) { return vmovltq_m_s16(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t subtract(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vsubq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract_halve(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vhsubq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract_saturate(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqsubq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_clear(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vbicq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_and(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vandq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_xor(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return veorq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_or_not(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vornq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_or(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vorrq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract_with_carry(int32x4_t inactive, int32x4_t a, int32x4_t b, unsigned *carry, mve_pred16_t p) { return vsbcq_m_s32(inactive, a, b, carry, p); }
[[gnu::always_inline]] nce int32x4_t subtract(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vsubq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract_halve(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vhsubq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t count_leading_sign_bits(int32x4_t inactive, int32x4_t a, mve_pred16_t p) { return vclsq_m_s32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t count_leading_zero_bits(int32x4_t inactive, int32x4_t a, mve_pred16_t p) { return vclzq_m_s32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_clear(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vbicq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t negate(int32x4_t inactive, int32x4_t a, mve_pred16_t p) { return vnegq_m_s32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t negate_saturate(int32x4_t inactive, int32x4_t a, mve_pred16_t p) { return vqnegq_m_s32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_and(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vandq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_xor(int32x4_t a, int32x4_t b, mve_pred16_t p) { return veorq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_not(int32x4_t inactive, int32x4_t a, mve_pred16_t p) { return vmvnq_m_s32(inactive, a, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_or_not(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vornq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_or(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vorrq_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract(int32x4_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vsubq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract_halve(int32x4_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vhsubq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract_saturate(int32x4_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vqsubq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_90(int32x4_t a, int32x4_t b) { return vcaddq_rot90_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_270(int32x4_t a, int32x4_t b) { return vcaddq_rot270_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_90(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vcaddq_rot90_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_270(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vcaddq_rot270_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_90_halve(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vhcaddq_rot90_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_270_halve(int32x4_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vhcaddq_rot270_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_round_dual_reduce_add_high_exchange_pairs(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vrmlsldavhxq_p_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_90(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vcaddq_rot90_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_270(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vcaddq_rot270_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vmulq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32x4_t multiply_round_high(int32x4_t a, int32x4_t b) { return vrmulhq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_add_double_saturate_high(int32x4_t add, int32x4_t m1, int32_t m2) { return vqdmlahq_n_s32(add, m1, m2); }
[[gnu::always_inline]] nce int32x4_t multiply_add_double_saturate_high(int32x4_t add, int32x4_t m1, int32_t m2, mve_pred16_t p) { return vqdmlahq_m_n_s32(add, m1, m2, p); }
[[gnu::always_inline]] nce int32x4_t multiply_add_double_round_saturate_high(int32x4_t add, int32x4_t m1, int32_t m2) { return vqrdmlahq_n_s32(add, m1, m2); }
[[gnu::always_inline]] nce int32x4_t multiply_add_double_round_saturate_high(int32x4_t add, int32x4_t m1, int32_t m2, mve_pred16_t p) { return vqrdmlahq_m_n_s32(add, m1, m2, p); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_double_saturate_high(int32x4_t m1, int32x4_t m2, int32_t add) { return vqdmlashq_n_s32(m1, m2, add); }
[[gnu::always_inline]] nce int32x4_t subtract_with_carry_initialized(int32x4_t a, int32x4_t b, unsigned *carry_out) { return vsbciq_s32(a, b, carry_out); }
[[gnu::always_inline]] nce int32x4_t subtract_with_carry(int32x4_t a, int32x4_t b, unsigned *carry) { return vsbcq_s32(a, b, carry); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_90_halve(int32x4_t a, int32x4_t b) { return vhcaddq_rot90_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_90_halve(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vhcaddq_rot90_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_270_halve(int32x4_t a, int32x4_t b) { return vhcaddq_rot270_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t complex_add_rotate_270_halve(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vhcaddq_rot270_x_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t predicate_select(int32x4_t a, int32x4_t b, mve_pred16_t p) { return vpselq_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t inactive, int32x4_t a, const int imm, mve_pred16_t p) { return vshlq_m_n_s32(inactive, a, imm, p); }
[[gnu::always_inline]] nce int32x4_t shift_left_insert(int32x4_t a, int32x4_t b, const int imm, mve_pred16_t p) { return vsliq_m_n_s32(a, b, imm, p); }
[[gnu::always_inline]] nce int32x4_t count_leading_sign_bits(int32x4_t a, mve_pred16_t p) { return vclsq_x_s32(a, p); }
[[gnu::always_inline]] nce int32x4_t count_leading_zero_bits(int32x4_t a, mve_pred16_t p) { return vclzq_x_s32(a, p); }
[[gnu::always_inline]] nce int32x4_t negate(int32x4_t a, mve_pred16_t p) { return vnegq_x_s32(a, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_not(int32x4_t a, mve_pred16_t p) { return vmvnq_x_s32(a, p); }
[[gnu::always_inline]] nce int32x4_t add_halve(int32x4_t a, int32_t b) { return vhaddq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_halve(int32x4_t a, int32_t b, mve_pred16_t p) { return vhaddq_x_n_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t add_saturate(int32x4_t a, int32_t b) { return vqaddq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t a, int32_t b, mve_pred16_t p) { return vmulq_x_n_s32(a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_bottom(int32x4_t a, int32_t b) { return vqdmullbq_n_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_top(int32x4_t a, int32_t b) { return vqdmulltq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract(int32x4_t a, int32_t b) { return vsubq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract(int32x4_t a, int32_t b, mve_pred16_t p) { return vsubq_x_n_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract_halve(int32x4_t a, int32_t b) { return vhsubq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_halve(int32x4_t a, int32_t b, mve_pred16_t p) { return vhsubq_x_n_s32(a, b, p); }
[[gnu::always_inline]] nce int32x4_t subtract_saturate(int32x4_t a, int32_t b) { return vqsubq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t bitwise_clear(int32x4_t a, const int32_t imm) { return vbicq_n_s32(a, imm); }
[[gnu::always_inline]] nce int32x4_t bitwise_clear(int32x4_t a, const int32_t imm, mve_pred16_t p) { return vbicq_m_n_s32(a, imm, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_not(int32x4_t inactive, const int32_t imm, mve_pred16_t p) { return vmvnq_m_n_s32(inactive, imm, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_or(int32x4_t a, const int32_t imm) { return vorrq_n_s32(a, imm); }
[[gnu::always_inline]] nce int32x4_t bitwise_or(int32x4_t a, const int32_t imm, mve_pred16_t p) { return vorrq_m_n_s32(a, imm, p); }
[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t a, const int imm, mve_pred16_t p) { return vshlq_x_n_s32(a, imm, p); }
[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t a, int32_t b) { return vshlq_r_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t a, int32_t b, mve_pred16_t p) { return vshlq_m_r_s32(a, b, p); }
[[gnu::always_inline]] nce uint64x2_t uninitialized(uint64x2_t t) { return vuninitializedq(t); }
[[gnu::always_inline]] nce uint64x2_t multiply_long_bottom(uint64x2_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vmullbq_int_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint64x2_t multiply_long_top(uint64x2_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vmulltq_int_m_u32(inactive, a, b, p); }
template <int offset>[[gnu::always_inline]] nce int64x2_t load_doubleword_gather_base(uint64x2_t addr) { return vldrdq_gather_base_s64(addr, offset); }
template <int offset>[[gnu::always_inline]] nce uint64x2_t load_doubleword_gather_base(uint64x2_t addr) { return vldrdq_gather_base_u64(addr, offset); }
template <> [[gnu::always_inline]] nce int64x2_t load_doubleword_gather_base(uint64x2_t addr, const int offset, mve_pred16_t p) { return vldrdq_gather_base_z_s64(addr, offset, p); }
template <> [[gnu::always_inline]] nce uint64x2_t load_doubleword_gather_base(uint64x2_t addr, const int offset, mve_pred16_t p) { return vldrdq_gather_base_z_u64(addr, offset, p); }
template <int offset>[[gnu::always_inline]] nce int64x2_t load_doubleword_gather_base(uint64x2_t *addr) { return vldrdq_gather_base_wb_s64(addr, offset); }
template <int offset>[[gnu::always_inline]] nce uint64x2_t load_doubleword_gather_base(uint64x2_t *addr) { return vldrdq_gather_base_wb_u64(addr, offset); }
[[gnu::always_inline]] nce uint64x2_t predicate_select(uint64x2_t a, uint64x2_t b, mve_pred16_t p) { return vpselq_u64(a, b, p); }
template <> [[gnu::always_inline]] nce int64x2_t load_doubleword_gather_base(uint64x2_t *addr, const int offset, mve_pred16_t p) { return vldrdq_gather_base_wb_z_s64(addr, offset, p); }
template <> [[gnu::always_inline]] nce uint64x2_t load_doubleword_gather_base(uint64x2_t *addr, const int offset, mve_pred16_t p) { return vldrdq_gather_base_wb_z_u64(addr, offset, p); }
[[gnu::always_inline]] nce void store_doubleword_scatter_base(uint64x2_t addr, const int offset, int64x2_t value) { return vstrdq_scatter_base_s64(addr, offset, value); }
[[gnu::always_inline]] nce void store_doubleword_scatter_base(uint64x2_t addr, const int offset, uint64x2_t value) { return vstrdq_scatter_base_u64(addr, offset, value); }
[[gnu::always_inline]] nce void store_doubleword_scatter_base(uint64x2_t addr, const int offset, int64x2_t value, mve_pred16_t p) { return vstrdq_scatter_base_p_s64(addr, offset, value, p); }
[[gnu::always_inline]] nce void store_doubleword_scatter_base(uint64x2_t addr, const int offset, uint64x2_t value, mve_pred16_t p) { return vstrdq_scatter_base_p_u64(addr, offset, value, p); }
[[gnu::always_inline]] nce void store_doubleword_scatter_base(uint64x2_t *addr, const int offset, int64x2_t value) { return vstrdq_scatter_base_wb_s64(addr, offset, value); }
[[gnu::always_inline]] nce void store_doubleword_scatter_base(uint64x2_t *addr, const int offset, uint64x2_t value) { return vstrdq_scatter_base_wb_u64(addr, offset, value); }
[[gnu::always_inline]] nce void store_doubleword_scatter_base(uint64x2_t *addr, const int offset, int64x2_t value, mve_pred16_t p) { return vstrdq_scatter_base_wb_p_s64(addr, offset, value, p); }
[[gnu::always_inline]] nce void store_doubleword_scatter_base(uint64x2_t *addr, const int offset, uint64x2_t value, mve_pred16_t p) { return vstrdq_scatter_base_wb_p_u64(addr, offset, value, p); }
[[gnu::always_inline]] nce uint32x4_t subtract(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vsubq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_halve(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vhsubq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_saturate(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vqsubq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_clear(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vbicq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_and(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vandq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_xor(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return veorq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_or_not(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vornq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_or(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vorrq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t complex_add_rotate_90(uint32x4_t a, uint32x4_t b) { return vcaddq_rot90_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t complex_add_rotate_270(uint32x4_t a, uint32x4_t b) { return vcaddq_rot270_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t complex_add_rotate_90(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vcaddq_rot90_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t complex_add_rotate_270(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vcaddq_rot270_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_with_carry(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, unsigned *carry, mve_pred16_t p) { return vsbcq_m_u32(inactive, a, b, carry, p); }
[[gnu::always_inline]] nce uint32x4_t subtract(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vsubq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_halve(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vhsubq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t count_leading_zero_bits(uint32x4_t inactive, uint32x4_t a, mve_pred16_t p) { return vclzq_m_u32(inactive, a, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_clear(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vbicq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_and(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vandq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_xor(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return veorq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_not(uint32x4_t inactive, uint32x4_t a, mve_pred16_t p) { return vmvnq_m_u32(inactive, a, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_or_not(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vornq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_or(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vorrq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t complex_add_rotate_90(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vcaddq_rot90_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t complex_add_rotate_270(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vcaddq_rot270_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_with_carry(uint32x4_t a, uint32x4_t b, unsigned *carry) { return vsbcq_u32(a, b, carry); }
[[gnu::always_inline]] nce uint32x4_t subtract(uint32x4_t inactive, uint32x4_t a, uint32_t b, mve_pred16_t p) { return vsubq_m_n_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_halve(uint32x4_t inactive, uint32x4_t a, uint32_t b, mve_pred16_t p) { return vhsubq_m_n_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_saturate(uint32x4_t inactive, uint32x4_t a, uint32_t b, mve_pred16_t p) { return vqsubq_m_n_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t count_leading_zero_bits(uint32x4_t a, mve_pred16_t p) { return vclzq_x_u32(a, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_not(uint32x4_t a, mve_pred16_t p) { return vmvnq_x_u32(a, p); }
[[gnu::always_inline]] nce uint32x4_t subtract(uint32x4_t a, uint32_t b) { return vsubq_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract(uint32x4_t a, uint32_t b, mve_pred16_t p) { return vsubq_x_n_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_halve(uint32x4_t a, uint32_t b) { return vhsubq_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_halve(uint32x4_t a, uint32_t b, mve_pred16_t p) { return vhsubq_x_n_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_saturate(uint32x4_t a, uint32_t b) { return vqsubq_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t bitwise_clear(uint32x4_t a, const uint32_t imm) { return vbicq_n_u32(a, imm); }
[[gnu::always_inline]] nce uint32x4_t bitwise_clear(uint32x4_t a, const uint32_t imm, mve_pred16_t p) { return vbicq_m_n_u32(a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_not(uint32x4_t inactive, const uint32_t imm, mve_pred16_t p) { return vmvnq_m_n_u32(inactive, imm, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_or(uint32x4_t a, const uint32_t imm) { return vorrq_n_u32(a, imm); }
[[gnu::always_inline]] nce uint32x4_t bitwise_or(uint32x4_t a, const uint32_t imm, mve_pred16_t p) { return vorrq_m_n_u32(a, imm, p); }
template <int offset>[[gnu::always_inline]] nce int32x4_t load_word_gather_base(uint32x4_t addr) { return vldrwq_gather_base_s32(addr, offset); }
template <int offset>[[gnu::always_inline]] nce uint32x4_t load_word_gather_base(uint32x4_t addr) { return vldrwq_gather_base_u32(addr, offset); }
template <> [[gnu::always_inline]] nce int32x4_t load_word_gather_base(uint32x4_t addr, const int offset, mve_pred16_t p) { return vldrwq_gather_base_z_s32(addr, offset, p); }
template <> [[gnu::always_inline]] nce uint32x4_t load_word_gather_base(uint32x4_t addr, const int offset, mve_pred16_t p) { return vldrwq_gather_base_z_u32(addr, offset, p); }
template <int offset>[[gnu::always_inline]] nce int32x4_t load_word_gather_base(uint32x4_t *addr) { return vldrwq_gather_base_wb_s32(addr, offset); }
template <int offset>[[gnu::always_inline]] nce uint32x4_t load_word_gather_base(uint32x4_t *addr) { return vldrwq_gather_base_wb_u32(addr, offset); }
[[gnu::always_inline]] nce uint32x4_t shift_left_long_bottom(uint32x4_t inactive, uint16x8_t a, const int imm, mve_pred16_t p) { return vshllbq_m_n_u16(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_long_top(uint32x4_t inactive, uint16x8_t a, const int imm, mve_pred16_t p) { return vshlltq_m_n_u16(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round(uint32x4_t a, int32x4_t b, mve_pred16_t p) { return vrshlq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t a, int32x4_t b, mve_pred16_t p) { return vshlq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round(uint32x4_t inactive, uint32x4_t a, int32x4_t b, mve_pred16_t p) { return vrshlq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t inactive, uint32x4_t a, int32x4_t b, mve_pred16_t p) { return vshlq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round(uint32x4_t a, int32_t b) { return vrshlq_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round(uint32x4_t a, int32_t b, mve_pred16_t p) { return vrshlq_m_n_u32(a, b, p); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t shift_left_carry(uint32x4_t a, uint32_t *b) { return vshlcq_u32(a, b, imm); }
[[gnu::always_inline]] nce uint32x4_t shift_left_carry(uint32x4_t a, uint32_t *b, const int imm, mve_pred16_t p) { return vshlcq_m_u32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t a) { return vshlq_n_u32(a, imm); }
[[gnu::always_inline]] nce uint32x4_t move_long_bottom(uint32x4_t inactive, uint16x8_t a, mve_pred16_t p) { return vmovlbq_m_u16(inactive, a, p); }
[[gnu::always_inline]] nce uint32x4_t move_long_top(uint32x4_t inactive, uint16x8_t a, mve_pred16_t p) { return vmovltq_m_u16(inactive, a, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_unsigned_saturate(uint32x4_t inactive, int32x4_t a, const int imm, mve_pred16_t p) { return vqshluq_m_n_s32(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t reverse_64bit(uint32x4_t inactive, uint32x4_t a, mve_pred16_t p) { return vrev64q_m_u32(inactive, a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint32x4_t a, uint32x4_t b) { return vcmpneq_u32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vcmpneq_m_u32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint32x4_t a, uint32x4_t b) { return vcmpcsq_u32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vcmpcsq_m_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t reverse_64bit(uint32x4_t a, mve_pred16_t p) { return vrev64q_x_u32(a, p); }
[[gnu::always_inline]] nce uint32x4_t decrement_duplicate(uint32x4_t inactive, uint32_t a, const int imm, mve_pred16_t p) { return vddupq_m_n_u32(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t decrement_duplicate(uint32x4_t inactive, uint32_t *a, const int imm, mve_pred16_t p) { return vddupq_m_wb_u32(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t decrement_wrap_duplicate(uint32x4_t inactive, uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_m_n_u32(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint32x4_t decrement_wrap_duplicate(uint32x4_t inactive, uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_m_wb_u32(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint32x4_t increment_duplicate(uint32x4_t inactive, uint32_t a, const int imm, mve_pred16_t p) { return vidupq_m_n_u32(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t increment_duplicate(uint32x4_t inactive, uint32_t *a, const int imm, mve_pred16_t p) { return vidupq_m_wb_u32(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t increment_wrap_duplicate(uint32x4_t inactive, uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_m_n_u32(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint32x4_t increment_wrap_duplicate(uint32x4_t inactive, uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_m_wb_u32(inactive, a, b, imm, p); }
[[gnu::always_inline]] nce uint32x4_t duplicate(uint32x4_t inactive, uint32_t a, mve_pred16_t p) { return vdupq_m_n_u32(inactive, a, p); }
[[gnu::always_inline]] nce uint32x4_t uninitialized(uint32x4_t t) { return vuninitializedq(t); }
[[gnu::always_inline]] nce uint32x4_t minimum_absolute(uint32x4_t a, int32x4_t b) { return vminaq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t minimum_absolute(uint32x4_t a, int32x4_t b, mve_pred16_t p) { return vminaq_m_s32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t maximum_absolute(uint32x4_t a, int32x4_t b) { return vmaxaq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t maximum_absolute(uint32x4_t a, int32x4_t b, mve_pred16_t p) { return vmaxaq_m_s32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint32x4_t a, uint32x4_t b) { return vcmpeqq_u32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint32x4_t a, uint32x4_t b) { return vcmphiq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t min(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vminq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t max(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vmaxq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_absolute(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vabdq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vaddq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add_carry_initialized(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, unsigned *carry_out, mve_pred16_t p) { return vadciq_m_u32(inactive, a, b, carry_out, p); }
[[gnu::always_inline]] nce uint32x4_t add_carry(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, unsigned *carry, mve_pred16_t p) { return vadcq_m_u32(inactive, a, b, carry, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vcmpeqq_m_u32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vcmphiq_m_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t min(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vminq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t max(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vmaxq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_absolute(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vabdq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vaddq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add_carry_initialized(uint32x4_t a, uint32x4_t b, unsigned *carry_out) { return vadciq_u32(a, b, carry_out); }
[[gnu::always_inline]] nce uint32x4_t add_carry(uint32x4_t a, uint32x4_t b, unsigned *carry) { return vadcq_u32(a, b, carry); }
[[gnu::always_inline]] nce uint32x4_t add(uint32x4_t inactive, uint32x4_t a, uint32_t b, mve_pred16_t p) { return vaddq_m_n_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint64_t reduce_add_long(uint32x4_t a, mve_pred16_t p) { return vaddlvq_p_u32(a, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint32x4_t a, uint32_t b) { return vcmpeqq_n_u32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_equal(uint32x4_t a, uint32_t b, mve_pred16_t p) { return vcmpeqq_m_n_u32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint32x4_t a, uint32_t b) { return vcmpneq_n_u32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_not_equal(uint32x4_t a, uint32_t b, mve_pred16_t p) { return vcmpneq_m_n_u32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint32x4_t a, uint32_t b) { return vcmpcsq_n_u32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_higher_or_same(uint32x4_t a, uint32_t b, mve_pred16_t p) { return vcmpcsq_m_n_u32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint32x4_t a, uint32_t b) { return vcmphiq_n_u32(a, b); }
[[gnu::always_inline]] nce mve_pred16_t compare_high(uint32x4_t a, uint32_t b, mve_pred16_t p) { return vcmphiq_m_n_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add(uint32x4_t a, uint32_t b) { return vaddq_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add(uint32x4_t a, uint32_t b, mve_pred16_t p) { return vaddq_x_n_u32(a, b, p); }
[[gnu::always_inline]] nce uint64_t reduce_add_long(uint32x4_t a) { return vaddlvq_u32(a); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint32x4_t a) { return vaddvq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t multiply_long_bottom_poly(uint32x4_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmullbq_poly_m_p16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_long_bottom(uint32x4_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmullbq_int_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multply_long_top_poly(uint32x4_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmulltq_poly_m_p16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_long_top(uint32x4_t inactive, uint16x8_t a, uint16x8_t b, mve_pred16_t p) { return vmulltq_int_m_u16(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add_halve(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vhaddq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add_halve_round(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vrhaddq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add_saturate(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vqaddq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_high(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vmulhq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add_halve(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vhaddq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add_halve_round(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vrhaddq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add_halve(uint32x4_t inactive, uint32x4_t a, uint32_t b, mve_pred16_t p) { return vhaddq_m_n_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add_saturate(uint32x4_t inactive, uint32x4_t a, uint32_t b, mve_pred16_t p) { return vqaddq_m_n_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_high(uint32x4_t a, uint32x4_t b) { return vmulhq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_high(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vmulhq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint64x2_t multiply_long_bottom(uint32x4_t a, uint32x4_t b) { return vmullbq_int_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t multiply_long_bottom(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vmullbq_int_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint64x2_t multiply_long_top(uint32x4_t a, uint32x4_t b) { return vmulltq_int_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vmulq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_round_high(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vrmulhq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint64x2_t multiply_long_top(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vmulltq_int_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vmulq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_round_high(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vrmulhq_x_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t inactive, uint32x4_t a, uint32_t b, mve_pred16_t p) { return vmulq_m_n_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_round_high(uint32x4_t a, uint32x4_t b) { return vrmulhq_u32(a, b); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add(uint32x4_t m1, uint32x4_t m2) { return vmladavq_u32(m1, m2); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add(uint32x4_t m1, uint32x4_t m2, mve_pred16_t p) { return vmladavq_p_u32(m1, m2, p); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_dual_reduce_add(uint32x4_t m1, uint32x4_t m2) { return vmlaldavq_u32(m1, m2); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_round_dual_reduce_add_high(uint32x4_t a, uint32x4_t b) { return vrmlaldavhq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round_saturate(uint32x4_t inactive, uint32x4_t a, int32x4_t b, mve_pred16_t p) { return vqrshlq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_saturate(uint32x4_t inactive, uint32x4_t a, int32x4_t b, mve_pred16_t p) { return vqshlq_m_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_with_carry_initialized(uint32x4_t inactive, uint32x4_t a, uint32x4_t b, unsigned *carry_out, mve_pred16_t p) { return vsbciq_m_u32(inactive, a, b, carry_out, p); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_dual_reduce_add(uint32x4_t m1, uint32x4_t m2, mve_pred16_t p) { return vmlaldavq_p_u32(m1, m2, p); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_round_dual_reduce_add_high(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vrmlaldavhq_p_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t predicate_select(uint32x4_t a, uint32x4_t b, mve_pred16_t p) { return vpselq_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_add(uint32x4_t add, uint32x4_t m1, uint32_t m2) { return vmlaq_n_u32(add, m1, m2); }
[[gnu::always_inline]] nce uint32x4_t multiply_add(uint32x4_t add, uint32x4_t m1, uint32_t m2, mve_pred16_t p) { return vmlaq_m_n_u32(add, m1, m2, p); }
[[gnu::always_inline]] nce uint32x4_t multiply_add(uint32x4_t m1, uint32x4_t m2, uint32_t add) { return vmlasq_n_u32(m1, m2, add); }
[[gnu::always_inline]] nce uint32x4_t multiply_add(uint32x4_t m1, uint32x4_t m2, uint32_t add, mve_pred16_t p) { return vmlasq_m_n_u32(m1, m2, add, p); }
[[gnu::always_inline]] nce uint32x4_t subtract_with_carry_initialized(uint32x4_t a, uint32x4_t b, unsigned *carry_out) { return vsbciq_u32(a, b, carry_out); }
[[gnu::always_inline]] nce uint32x4_t bit_reverse_shift_right(uint32x4_t inactive, uint32x4_t a, int32_t b, mve_pred16_t p) { return vbrsrq_m_n_u32(inactive, a, b, p); }
[[gnu::always_inline]] nce uint32x4_t shift_right_round(uint32x4_t inactive, uint32x4_t a, const int imm, mve_pred16_t p) { return vrshrq_m_n_u32(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t shift_right(uint32x4_t inactive, uint32x4_t a, const int imm, mve_pred16_t p) { return vshrq_m_n_u32(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t shift_right_insert(uint32x4_t a, uint32x4_t b, const int imm, mve_pred16_t p) { return vsriq_m_n_u32(a, b, imm, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_saturate(uint32x4_t inactive, uint32x4_t a, const int imm, mve_pred16_t p) { return vqshlq_m_n_u32(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t inactive, uint32x4_t a, const int imm, mve_pred16_t p) { return vshlq_m_n_u32(inactive, a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_insert(uint32x4_t a, uint32x4_t b, const int imm, mve_pred16_t p) { return vsliq_m_n_u32(a, b, imm, p); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint32x4_t a, mve_pred16_t p) { return vaddvq_p_u32(a, p); }
[[gnu::always_inline]] nce uint32x4_t add_halve(uint32x4_t a, uint32_t b) { return vhaddq_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_halve(uint32x4_t a, uint32_t b, mve_pred16_t p) { return vhaddq_x_n_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t add_saturate(uint32x4_t a, uint32_t b) { return vqaddq_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t a, uint32_t b, mve_pred16_t p) { return vmulq_x_n_u32(a, b, p); }
template <> [[gnu::always_inline]] nce int32x4_t load_word_gather_base(uint32x4_t *addr, const int offset, mve_pred16_t p) { return vldrwq_gather_base_wb_z_s32(addr, offset, p); }
template <> [[gnu::always_inline]] nce uint32x4_t load_word_gather_base(uint32x4_t *addr, const int offset, mve_pred16_t p) { return vldrwq_gather_base_wb_z_u32(addr, offset, p); }
[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t addr, const int offset, int32x4_t value) { return vstrwq_scatter_base_s32(addr, offset, value); }
[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t addr, const int offset, uint32x4_t value) { return vstrwq_scatter_base_u32(addr, offset, value); }
[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t addr, const int offset, int32x4_t value, mve_pred16_t p) { return vstrwq_scatter_base_p_s32(addr, offset, value, p); }
[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t addr, const int offset, uint32x4_t value, mve_pred16_t p) { return vstrwq_scatter_base_p_u32(addr, offset, value, p); }
[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t *addr, const int offset, int32x4_t value) { return vstrwq_scatter_base_wb_s32(addr, offset, value); }
[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t *addr, const int offset, uint32x4_t value) { return vstrwq_scatter_base_wb_u32(addr, offset, value); }
[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t *addr, const int offset, int32x4_t value, mve_pred16_t p) { return vstrwq_scatter_base_wb_p_s32(addr, offset, value, p); }
[[gnu::always_inline]] nce void store_word_scatter_base(uint32x4_t *addr, const int offset, uint32x4_t value, mve_pred16_t p) { return vstrwq_scatter_base_wb_p_u32(addr, offset, value, p); }
[[gnu::always_inline]] nce uint32x4_t bit_reverse_shift_right(uint32x4_t a, int32_t b) { return vbrsrq_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t bit_reverse_shift_right(uint32x4_t a, int32_t b, mve_pred16_t p) { return vbrsrq_x_n_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t shift_right_round(uint32x4_t a, const int imm, mve_pred16_t p) { return vrshrq_x_n_u32(a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t shift_right(uint32x4_t a, const int imm, mve_pred16_t p) { return vshrq_x_n_u32(a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round_saturate(uint32x4_t a, int32_t b) { return vqrshlq_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round_saturate(uint32x4_t a, int32_t b, mve_pred16_t p) { return vqrshlq_m_n_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left_saturate(uint32x4_t a, int32_t b) { return vqshlq_r_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left_saturate(uint32x4_t a, int32_t b, mve_pred16_t p) { return vqshlq_m_r_u32(a, b, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t a, const int imm, mve_pred16_t p) { return vshlq_x_n_u32(a, imm, p); }
[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t a, int32_t b) { return vshlq_r_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t a, int32_t b, mve_pred16_t p) { return vshlq_m_r_u32(a, b, p); }
[[gnu::always_inline]] nce mve_pred16_t predicate_not(mve_pred16_t a) { return vpnot(a); }
template <> [[gnu::always_inline]] nce int8x16_t create(uint64_t a, uint64_t b) { return vcreateq_s8(a, b); }
template <> [[gnu::always_inline]] nce int16x8_t create(uint64_t a, uint64_t b) { return vcreateq_s16(a, b); }
template <> [[gnu::always_inline]] nce int32x4_t create(uint64_t a, uint64_t b) { return vcreateq_s32(a, b); }
template <> [[gnu::always_inline]] nce int64x2_t create(uint64_t a, uint64_t b) { return vcreateq_s64(a, b); }
template <> [[gnu::always_inline]] nce uint8x16_t create(uint64_t a, uint64_t b) { return vcreateq_u8(a, b); }
template <> [[gnu::always_inline]] nce uint16x8_t create(uint64_t a, uint64_t b) { return vcreateq_u16(a, b); }
template <> [[gnu::always_inline]] nce uint32x4_t create(uint64_t a, uint64_t b) { return vcreateq_u32(a, b); }
template <> [[gnu::always_inline]] nce uint64x2_t create(uint64_t a, uint64_t b) { return vcreateq_u64(a, b); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t decrement_duplicate(uint32_t a) { return vddupq_n_u8(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t decrement_duplicate(uint32_t a) { return vddupq_n_u16(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t decrement_duplicate(uint32_t a) { return vddupq_n_u32(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t decrement_duplicate(uint32_t *a) { return vddupq_wb_u8(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t decrement_duplicate(uint32_t *a) { return vddupq_wb_u16(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t decrement_duplicate(uint32_t *a) { return vddupq_wb_u32(a, imm); }
template <> [[gnu::always_inline]] nce uint8x16_t decrement_duplicate(uint32_t a, const int imm, mve_pred16_t p) { return vddupq_x_n_u8(a, imm, p); }
template <> [[gnu::always_inline]] nce uint16x8_t decrement_duplicate(uint32_t a, const int imm, mve_pred16_t p) { return vddupq_x_n_u16(a, imm, p); }
template <> [[gnu::always_inline]] nce uint32x4_t decrement_duplicate(uint32_t a, const int imm, mve_pred16_t p) { return vddupq_x_n_u32(a, imm, p); }
template <> [[gnu::always_inline]] nce uint8x16_t decrement_duplicate(uint32_t *a, const int imm, mve_pred16_t p) { return vddupq_x_wb_u8(a, imm, p); }
template <> [[gnu::always_inline]] nce uint16x8_t decrement_duplicate(uint32_t *a, const int imm, mve_pred16_t p) { return vddupq_x_wb_u16(a, imm, p); }
template <> [[gnu::always_inline]] nce uint32x4_t decrement_duplicate(uint32_t *a, const int imm, mve_pred16_t p) { return vddupq_x_wb_u32(a, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t decrement_wrap_duplicate(uint32_t a, uint32_t b) { return vdwdupq_n_u8(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t decrement_wrap_duplicate(uint32_t a, uint32_t b) { return vdwdupq_n_u16(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t decrement_wrap_duplicate(uint32_t a, uint32_t b) { return vdwdupq_n_u32(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t decrement_wrap_duplicate(uint32_t *a, uint32_t b) { return vdwdupq_wb_u8(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t decrement_wrap_duplicate(uint32_t *a, uint32_t b) { return vdwdupq_wb_u16(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t decrement_wrap_duplicate(uint32_t *a, uint32_t b) { return vdwdupq_wb_u32(a, b, imm); }
template <> [[gnu::always_inline]] nce uint8x16_t decrement_wrap_duplicate(uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_x_n_u8(a, b, imm, p); }
template <> [[gnu::always_inline]] nce uint16x8_t decrement_wrap_duplicate(uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_x_n_u16(a, b, imm, p); }
template <> [[gnu::always_inline]] nce uint32x4_t decrement_wrap_duplicate(uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_x_n_u32(a, b, imm, p); }
template <> [[gnu::always_inline]] nce uint8x16_t decrement_wrap_duplicate(uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_x_wb_u8(a, b, imm, p); }
template <> [[gnu::always_inline]] nce uint16x8_t decrement_wrap_duplicate(uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_x_wb_u16(a, b, imm, p); }
template <> [[gnu::always_inline]] nce uint32x4_t decrement_wrap_duplicate(uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return vdwdupq_x_wb_u32(a, b, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t increment_duplicate(uint32_t a) { return vidupq_n_u8(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t increment_duplicate(uint32_t a) { return vidupq_n_u16(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t increment_duplicate(uint32_t a) { return vidupq_n_u32(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t increment_duplicate(uint32_t *a) { return vidupq_wb_u8(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t increment_duplicate(uint32_t *a) { return vidupq_wb_u16(a, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t increment_duplicate(uint32_t *a) { return vidupq_wb_u32(a, imm); }
template <> [[gnu::always_inline]] nce uint8x16_t increment_duplicate(uint32_t a, const int imm, mve_pred16_t p) { return vidupq_x_n_u8(a, imm, p); }
template <> [[gnu::always_inline]] nce uint16x8_t increment_duplicate(uint32_t a, const int imm, mve_pred16_t p) { return vidupq_x_n_u16(a, imm, p); }
template <> [[gnu::always_inline]] nce uint32x4_t increment_duplicate(uint32_t a, const int imm, mve_pred16_t p) { return vidupq_x_n_u32(a, imm, p); }
template <> [[gnu::always_inline]] nce uint8x16_t increment_duplicate(uint32_t *a, const int imm, mve_pred16_t p) { return vidupq_x_wb_u8(a, imm, p); }
template <> [[gnu::always_inline]] nce uint16x8_t increment_duplicate(uint32_t *a, const int imm, mve_pred16_t p) { return vidupq_x_wb_u16(a, imm, p); }
template <> [[gnu::always_inline]] nce uint32x4_t increment_duplicate(uint32_t *a, const int imm, mve_pred16_t p) { return vidupq_x_wb_u32(a, imm, p); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t increment_wrap_duplicate(uint32_t a, uint32_t b) { return viwdupq_n_u8(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t increment_wrap_duplicate(uint32_t a, uint32_t b) { return viwdupq_n_u16(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t increment_wrap_duplicate(uint32_t a, uint32_t b) { return viwdupq_n_u32(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint8x16_t increment_wrap_duplicate(uint32_t *a, uint32_t b) { return viwdupq_wb_u8(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint16x8_t increment_wrap_duplicate(uint32_t *a, uint32_t b) { return viwdupq_wb_u16(a, b, imm); }
template <int imm>[[gnu::always_inline]] nce uint32x4_t increment_wrap_duplicate(uint32_t *a, uint32_t b) { return viwdupq_wb_u32(a, b, imm); }
template <> [[gnu::always_inline]] nce uint8x16_t increment_wrap_duplicate(uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_x_n_u8(a, b, imm, p); }
template <> [[gnu::always_inline]] nce uint16x8_t increment_wrap_duplicate(uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_x_n_u16(a, b, imm, p); }
template <> [[gnu::always_inline]] nce uint32x4_t increment_wrap_duplicate(uint32_t a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_x_n_u32(a, b, imm, p); }
template <> [[gnu::always_inline]] nce uint8x16_t increment_wrap_duplicate(uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_x_wb_u8(a, b, imm, p); }
template <> [[gnu::always_inline]] nce uint16x8_t increment_wrap_duplicate(uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_x_wb_u16(a, b, imm, p); }
template <> [[gnu::always_inline]] nce uint32x4_t increment_wrap_duplicate(uint32_t *a, uint32_t b, const int imm, mve_pred16_t p) { return viwdupq_x_wb_u32(a, b, imm, p); }
[[gnu::always_inline]] nce int8x16_t duplicate(int8_t a, mve_pred16_t p) { return vdupq_x_n_s8(a, p); }
[[gnu::always_inline]] nce int16x8_t duplicate(int16_t a, mve_pred16_t p) { return vdupq_x_n_s16(a, p); }
[[gnu::always_inline]] nce int32x4_t duplicate(int32_t a, mve_pred16_t p) { return vdupq_x_n_s32(a, p); }
[[gnu::always_inline]] nce uint8x16_t duplicate(uint8_t a, mve_pred16_t p) { return vdupq_x_n_u8(a, p); }
[[gnu::always_inline]] nce uint16x8_t duplicate(uint16_t a, mve_pred16_t p) { return vdupq_x_n_u16(a, p); }
[[gnu::always_inline]] nce uint32x4_t duplicate(uint32_t a, mve_pred16_t p) { return vdupq_x_n_u32(a, p); }
template <> [[gnu::always_inline]] nce int8x16_t uninitialized( void) { return vuninitializedq_s8(void); }
template <> [[gnu::always_inline]] nce int16x8_t uninitialized( void) { return vuninitializedq_s16(void); }
template <> [[gnu::always_inline]] nce int32x4_t uninitialized( void) { return vuninitializedq_s32(void); }
template <> [[gnu::always_inline]] nce int64x2_t uninitialized( void) { return vuninitializedq_s64(void); }
template <> [[gnu::always_inline]] nce uint8x16_t uninitialized( void) { return vuninitializedq_u8(void); }
template <> [[gnu::always_inline]] nce uint16x8_t uninitialized( void) { return vuninitializedq_u16(void); }
template <> [[gnu::always_inline]] nce uint32x4_t uninitialized( void) { return vuninitializedq_u32(void); }
template <> [[gnu::always_inline]] nce uint64x2_t uninitialized( void) { return vuninitializedq_u64(void); }
[[gnu::always_inline]] nce int64x2_t uninitialized(int64x2_t t) { return vuninitializedq(t); }
[[gnu::always_inline]] nce int8_t minimum_across_vector(int8_t a, int8x16_t b) { return vminvq_s8(a, b); }
[[gnu::always_inline]] nce int16_t minimum_across_vector(int16_t a, int16x8_t b) { return vminvq_s16(a, b); }
[[gnu::always_inline]] nce int32_t minimum_across_vector(int32_t a, int32x4_t b) { return vminvq_s32(a, b); }
[[gnu::always_inline]] nce uint8_t minimum_across_vector(uint8_t a, uint8x16_t b) { return vminvq_u8(a, b); }
[[gnu::always_inline]] nce uint16_t minimum_across_vector(uint16_t a, uint16x8_t b) { return vminvq_u16(a, b); }
[[gnu::always_inline]] nce uint32_t minimum_across_vector(uint32_t a, uint32x4_t b) { return vminvq_u32(a, b); }
[[gnu::always_inline]] nce int8_t minimum_across_vector(int8_t a, int8x16_t b, mve_pred16_t p) { return vminvq_p_s8(a, b, p); }
[[gnu::always_inline]] nce int16_t minimum_across_vector(int16_t a, int16x8_t b, mve_pred16_t p) { return vminvq_p_s16(a, b, p); }
[[gnu::always_inline]] nce int32_t minimum_across_vector(int32_t a, int32x4_t b, mve_pred16_t p) { return vminvq_p_s32(a, b, p); }
[[gnu::always_inline]] nce uint8_t minimum_across_vector(uint8_t a, uint8x16_t b, mve_pred16_t p) { return vminvq_p_u8(a, b, p); }
[[gnu::always_inline]] nce uint16_t minimum_across_vector(uint16_t a, uint16x8_t b, mve_pred16_t p) { return vminvq_p_u16(a, b, p); }
[[gnu::always_inline]] nce uint32_t minimum_across_vector(uint32_t a, uint32x4_t b, mve_pred16_t p) { return vminvq_p_u32(a, b, p); }
[[gnu::always_inline]] nce uint8_t minimum_absolute_across_vector(uint8_t a, int8x16_t b) { return vminavq_s8(a, b); }
[[gnu::always_inline]] nce uint16_t minimum_absolute_across_vector(uint16_t a, int16x8_t b) { return vminavq_s16(a, b); }
[[gnu::always_inline]] nce uint32_t minimum_absolute_across_vector(uint32_t a, int32x4_t b) { return vminavq_s32(a, b); }
[[gnu::always_inline]] nce uint8_t minimum_absolute_across_vector(uint8_t a, int8x16_t b, mve_pred16_t p) { return vminavq_p_s8(a, b, p); }
[[gnu::always_inline]] nce uint16_t minimum_absolute_across_vector(uint16_t a, int16x8_t b, mve_pred16_t p) { return vminavq_p_s16(a, b, p); }
[[gnu::always_inline]] nce uint32_t minimum_absolute_across_vector(uint32_t a, int32x4_t b, mve_pred16_t p) { return vminavq_p_s32(a, b, p); }
[[gnu::always_inline]] nce int8_t maximum_across_vector(int8_t a, int8x16_t b) { return vmaxvq_s8(a, b); }
[[gnu::always_inline]] nce int16_t maximum_across_vector(int16_t a, int16x8_t b) { return vmaxvq_s16(a, b); }
[[gnu::always_inline]] nce int32_t maximum_across_vector(int32_t a, int32x4_t b) { return vmaxvq_s32(a, b); }
[[gnu::always_inline]] nce uint8_t maximum_across_vector(uint8_t a, uint8x16_t b) { return vmaxvq_u8(a, b); }
[[gnu::always_inline]] nce uint16_t maximum_across_vector(uint16_t a, uint16x8_t b) { return vmaxvq_u16(a, b); }
[[gnu::always_inline]] nce uint32_t maximum_across_vector(uint32_t a, uint32x4_t b) { return vmaxvq_u32(a, b); }
[[gnu::always_inline]] nce int8_t maximum_across_vector(int8_t a, int8x16_t b, mve_pred16_t p) { return vmaxvq_p_s8(a, b, p); }
[[gnu::always_inline]] nce int16_t maximum_across_vector(int16_t a, int16x8_t b, mve_pred16_t p) { return vmaxvq_p_s16(a, b, p); }
[[gnu::always_inline]] nce int32_t maximum_across_vector(int32_t a, int32x4_t b, mve_pred16_t p) { return vmaxvq_p_s32(a, b, p); }
[[gnu::always_inline]] nce uint8_t maximum_across_vector(uint8_t a, uint8x16_t b, mve_pred16_t p) { return vmaxvq_p_u8(a, b, p); }
[[gnu::always_inline]] nce uint16_t maximum_across_vector(uint16_t a, uint16x8_t b, mve_pred16_t p) { return vmaxvq_p_u16(a, b, p); }
[[gnu::always_inline]] nce uint32_t maximum_across_vector(uint32_t a, uint32x4_t b, mve_pred16_t p) { return vmaxvq_p_u32(a, b, p); }
[[gnu::always_inline]] nce uint8_t maximum_absolute_across_vector(uint8_t a, int8x16_t b) { return vmaxavq_s8(a, b); }
[[gnu::always_inline]] nce uint16_t maximum_absolute_across_vector(uint16_t a, int16x8_t b) { return vmaxavq_s16(a, b); }
[[gnu::always_inline]] nce uint32_t maximum_absolute_across_vector(uint32_t a, int32x4_t b) { return vmaxavq_s32(a, b); }
[[gnu::always_inline]] nce uint8_t maximum_absolute_across_vector(uint8_t a, int8x16_t b, mve_pred16_t p) { return vmaxavq_p_s8(a, b, p); }
[[gnu::always_inline]] nce uint16_t maximum_absolute_across_vector(uint16_t a, int16x8_t b, mve_pred16_t p) { return vmaxavq_p_s16(a, b, p); }
[[gnu::always_inline]] nce uint32_t maximum_absolute_across_vector(uint32_t a, int32x4_t b, mve_pred16_t p) { return vmaxavq_p_s32(a, b, p); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, int8x16_t b, int8x16_t c) { return vabavq_s8(a, b, c); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, int16x8_t b, int16x8_t c) { return vabavq_s16(a, b, c); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, int32x4_t b, int32x4_t c) { return vabavq_s32(a, b, c); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, uint8x16_t b, uint8x16_t c) { return vabavq_u8(a, b, c); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, uint16x8_t b, uint16x8_t c) { return vabavq_u16(a, b, c); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, uint32x4_t b, uint32x4_t c) { return vabavq_u32(a, b, c); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, int8x16_t b, int8x16_t c, mve_pred16_t p) { return vabavq_p_s8(a, b, c, p); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, int16x8_t b, int16x8_t c, mve_pred16_t p) { return vabavq_p_s16(a, b, c, p); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, int32x4_t b, int32x4_t c, mve_pred16_t p) { return vabavq_p_s32(a, b, c, p); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, uint8x16_t b, uint8x16_t c, mve_pred16_t p) { return vabavq_p_u8(a, b, c, p); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, uint16x8_t b, uint16x8_t c, mve_pred16_t p) { return vabavq_p_u16(a, b, c, p); }
[[gnu::always_inline]] nce uint32_t absolute_subtract_add(uint32_t a, uint32x4_t b, uint32x4_t c, mve_pred16_t p) { return vabavq_p_u32(a, b, c, p); }
[[gnu::always_inline]] nce int64_t reduce_add_long(int64_t a, int32x4_t b) { return vaddlvaq_s32(a, b); }
[[gnu::always_inline]] nce uint64_t reduce_add_long(uint64_t a, uint32x4_t b) { return vaddlvaq_u32(a, b); }
[[gnu::always_inline]] nce int64_t reduce_add_long(int64_t a, int32x4_t b, mve_pred16_t p) { return vaddlvaq_p_s32(a, b, p); }
[[gnu::always_inline]] nce uint64_t reduce_add_long(uint64_t a, uint32x4_t b, mve_pred16_t p) { return vaddlvaq_p_u32(a, b, p); }
[[gnu::always_inline]] nce int32_t reduce_add(int32_t a, int8x16_t b) { return vaddvaq_s8(a, b); }
[[gnu::always_inline]] nce int32_t reduce_add(int32_t a, int16x8_t b) { return vaddvaq_s16(a, b); }
[[gnu::always_inline]] nce int32_t reduce_add(int32_t a, int32x4_t b) { return vaddvaq_s32(a, b); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint32_t a, uint8x16_t b) { return vaddvaq_u8(a, b); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint32_t a, uint16x8_t b) { return vaddvaq_u16(a, b); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint32_t a, uint32x4_t b) { return vaddvaq_u32(a, b); }
[[gnu::always_inline]] nce int32_t reduce_add(int32_t a, int8x16_t b, mve_pred16_t p) { return vaddvaq_p_s8(a, b, p); }
[[gnu::always_inline]] nce int32_t reduce_add(int32_t a, int16x8_t b, mve_pred16_t p) { return vaddvaq_p_s16(a, b, p); }
[[gnu::always_inline]] nce int32_t reduce_add(int32_t a, int32x4_t b, mve_pred16_t p) { return vaddvaq_p_s32(a, b, p); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint32_t a, uint8x16_t b, mve_pred16_t p) { return vaddvaq_p_u8(a, b, p); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint32_t a, uint16x8_t b, mve_pred16_t p) { return vaddvaq_p_u16(a, b, p); }
[[gnu::always_inline]] nce uint32_t reduce_add(uint32_t a, uint32x4_t b, mve_pred16_t p) { return vaddvaq_p_u32(a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_long_bottom(int64x2_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmullbq_int_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_long_top(int64x2_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vmulltq_int_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_bottom(int64x2_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vqdmullbq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_bottom(int64x2_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqdmullbq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_top(int64x2_t inactive, int32x4_t a, int32_t b, mve_pred16_t p) { return vqdmulltq_m_n_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long_top(int64x2_t inactive, int32x4_t a, int32x4_t b, mve_pred16_t p) { return vqdmulltq_m_s32(inactive, a, b, p); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate(int32_t add, int8x16_t m1, int8x16_t m2) { return vmladavaq_s8(add, m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate(int32_t add, int16x8_t m1, int16x8_t m2) { return vmladavaq_s16(add, m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate(int32_t add, int32x4_t m1, int32x4_t m2) { return vmladavaq_s32(add, m1, m2); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add_accumulate(uint32_t add, uint8x16_t m1, uint8x16_t m2) { return vmladavaq_u8(add, m1, m2); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add_accumulate(uint32_t add, uint16x8_t m1, uint16x8_t m2) { return vmladavaq_u16(add, m1, m2); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add_accumulate(uint32_t add, uint32x4_t m1, uint32x4_t m2) { return vmladavaq_u32(add, m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate(int32_t add, int8x16_t m1, int8x16_t m2, mve_pred16_t p) { return vmladavaq_p_s8(add, m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate(int32_t add, int16x8_t m1, int16x8_t m2, mve_pred16_t p) { return vmladavaq_p_s16(add, m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate(int32_t add, int32x4_t m1, int32x4_t m2, mve_pred16_t p) { return vmladavaq_p_s32(add, m1, m2, p); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add_accumulate(uint32_t add, uint8x16_t m1, uint8x16_t m2, mve_pred16_t p) { return vmladavaq_p_u8(add, m1, m2, p); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add_accumulate(uint32_t add, uint16x8_t m1, uint16x8_t m2, mve_pred16_t p) { return vmladavaq_p_u16(add, m1, m2, p); }
[[gnu::always_inline]] nce uint32_t multiply_add_dual_reduce_add_accumulate(uint32_t add, uint32x4_t m1, uint32x4_t m2, mve_pred16_t p) { return vmladavaq_p_u32(add, m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate_exchange_pairs(int32_t add, int8x16_t m1, int8x16_t m2) { return vmladavaxq_s8(add, m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate_exchange_pairs(int32_t add, int16x8_t m1, int16x8_t m2) { return vmladavaxq_s16(add, m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate_exchange_pairs(int32_t add, int32x4_t m1, int32x4_t m2) { return vmladavaxq_s32(add, m1, m2); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate_exchange_pairs(int32_t add, int8x16_t m1, int8x16_t m2, mve_pred16_t p) { return vmladavaxq_p_s8(add, m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate_exchange_pairs(int32_t add, int16x8_t m1, int16x8_t m2, mve_pred16_t p) { return vmladavaxq_p_s16(add, m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_add_dual_reduce_add_accumulate_exchange_pairs(int32_t add, int32x4_t m1, int32x4_t m2, mve_pred16_t p) { return vmladavaxq_p_s32(add, m1, m2, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_accumulate(int64_t add, int16x8_t m1, int16x8_t m2) { return vmlaldavaq_s16(add, m1, m2); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_accumulate(int64_t add, int32x4_t m1, int32x4_t m2) { return vmlaldavaq_s32(add, m1, m2); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_dual_reduce_add_accumulate(uint64_t add, uint16x8_t m1, uint16x8_t m2) { return vmlaldavaq_u16(add, m1, m2); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_dual_reduce_add_accumulate(uint64_t add, uint32x4_t m1, uint32x4_t m2) { return vmlaldavaq_u32(add, m1, m2); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_accumulate(int64_t add, int16x8_t m1, int16x8_t m2, mve_pred16_t p) { return vmlaldavaq_p_s16(add, m1, m2, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_accumulate(int64_t add, int32x4_t m1, int32x4_t m2, mve_pred16_t p) { return vmlaldavaq_p_s32(add, m1, m2, p); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_dual_reduce_add_accumulate(uint64_t add, uint16x8_t m1, uint16x8_t m2, mve_pred16_t p) { return vmlaldavaq_p_u16(add, m1, m2, p); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_dual_reduce_add_accumulate(uint64_t add, uint32x4_t m1, uint32x4_t m2, mve_pred16_t p) { return vmlaldavaq_p_u32(add, m1, m2, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_accumulate_exchange_pairs(int64_t add, int16x8_t m1, int16x8_t m2) { return vmlaldavaxq_s16(add, m1, m2); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_accumulate_exchange_pairs(int64_t add, int32x4_t m1, int32x4_t m2) { return vmlaldavaxq_s32(add, m1, m2); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_accumulate_exchange_pairs(int64_t add, int16x8_t m1, int16x8_t m2, mve_pred16_t p) { return vmlaldavaxq_p_s16(add, m1, m2, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_dual_reduce_add_accumulate_exchange_pairs(int64_t add, int32x4_t m1, int32x4_t m2, mve_pred16_t p) { return vmlaldavaxq_p_s32(add, m1, m2, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate(int32_t a, int8x16_t b, int8x16_t c) { return vmlsdavaq_s8(a, b, c); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate(int32_t a, int16x8_t b, int16x8_t c) { return vmlsdavaq_s16(a, b, c); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate(int32_t a, int32x4_t b, int32x4_t c) { return vmlsdavaq_s32(a, b, c); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate(int32_t a, int8x16_t b, int8x16_t c, mve_pred16_t p) { return vmlsdavaq_p_s8(a, b, c, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate(int32_t a, int16x8_t b, int16x8_t c, mve_pred16_t p) { return vmlsdavaq_p_s16(a, b, c, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate(int32_t a, int32x4_t b, int32x4_t c, mve_pred16_t p) { return vmlsdavaq_p_s32(a, b, c, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate_exchange_pairs(int32_t a, int8x16_t b, int8x16_t c) { return vmlsdavaxq_s8(a, b, c); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate_exchange_pairs(int32_t a, int16x8_t b, int16x8_t c) { return vmlsdavaxq_s16(a, b, c); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate_exchange_pairs(int32_t a, int32x4_t b, int32x4_t c) { return vmlsdavaxq_s32(a, b, c); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate_exchange_pairs(int32_t a, int8x16_t b, int8x16_t c, mve_pred16_t p) { return vmlsdavaxq_p_s8(a, b, c, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate_exchange_pairs(int32_t a, int16x8_t b, int16x8_t c, mve_pred16_t p) { return vmlsdavaxq_p_s16(a, b, c, p); }
[[gnu::always_inline]] nce int32_t multiply_subtract_dual_reduce_add_accumulate_exchange_pairs(int32_t a, int32x4_t b, int32x4_t c, mve_pred16_t p) { return vmlsdavaxq_p_s32(a, b, c, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_accumulate(int64_t a, int16x8_t b, int16x8_t c) { return vmlsldavaq_s16(a, b, c); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_accumulate(int64_t a, int32x4_t b, int32x4_t c) { return vmlsldavaq_s32(a, b, c); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_accumulate(int64_t a, int16x8_t b, int16x8_t c, mve_pred16_t p) { return vmlsldavaq_p_s16(a, b, c, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_accumulate(int64_t a, int32x4_t b, int32x4_t c, mve_pred16_t p) { return vmlsldavaq_p_s32(a, b, c, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_accumulate_exchange_pairs(int64_t a, int16x8_t b, int16x8_t c) { return vmlsldavaxq_s16(a, b, c); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_accumulate_exchange_pairs(int64_t a, int32x4_t b, int32x4_t c) { return vmlsldavaxq_s32(a, b, c); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_accumulate_exchange_pairs(int64_t a, int16x8_t b, int16x8_t c, mve_pred16_t p) { return vmlsldavaxq_p_s16(a, b, c, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_dual_reduce_add_accumulate_exchange_pairs(int64_t a, int32x4_t b, int32x4_t c, mve_pred16_t p) { return vmlsldavaxq_p_s32(a, b, c, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_round_dual_reduce_add_high_accumulate(int64_t a, int32x4_t b, int32x4_t c) { return vrmlaldavhaq_s32(a, b, c); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_round_dual_reduce_add_high_accumulate(uint64_t a, uint32x4_t b, uint32x4_t c) { return vrmlaldavhaq_u32(a, b, c); }
[[gnu::always_inline]] nce int64_t multiply_add_long_round_dual_reduce_add_high_accumulate(int64_t a, int32x4_t b, int32x4_t c, mve_pred16_t p) { return vrmlaldavhaq_p_s32(a, b, c, p); }
[[gnu::always_inline]] nce uint64_t multiply_add_long_round_dual_reduce_add_high_accumulate(uint64_t a, uint32x4_t b, uint32x4_t c, mve_pred16_t p) { return vrmlaldavhaq_p_u32(a, b, c, p); }
[[gnu::always_inline]] nce int64_t multiply_add_long_round_dual_reduce_add_high_accumulate_exchange_pairs(int64_t a, int32x4_t b, int32x4_t c) { return vrmlaldavhaxq_s32(a, b, c); }
[[gnu::always_inline]] nce int64_t multiply_add_long_round_dual_reduce_add_high_accumulate_exchange_pairs(int64_t a, int32x4_t b, int32x4_t c, mve_pred16_t p) { return vrmlaldavhaxq_p_s32(a, b, c, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_round_dual_reduce_add_high_accumulate(int64_t a, int32x4_t b, int32x4_t c) { return vrmlsldavhaq_s32(a, b, c); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_round_dual_reduce_add_high_accumulate(int64_t a, int32x4_t b, int32x4_t c, mve_pred16_t p) { return vrmlsldavhaq_p_s32(a, b, c, p); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_round_dual_reduce_add_high_accumulate_exchange_pairs(int64_t a, int32x4_t b, int32x4_t c) { return vrmlsldavhaxq_s32(a, b, c); }
[[gnu::always_inline]] nce int64_t multiply_subtract_long_round_dual_reduce_add_high_accumulate_exchange_pairs(int64_t a, int32x4_t b, int32x4_t c, mve_pred16_t p) { return vrmlsldavhaxq_p_s32(a, b, c, p); }
[[gnu::always_inline]] nce int16x8_t bitwise_not(const int16_t imm) { return vmvnq_n_s16(imm); }
[[gnu::always_inline]] nce int32x4_t bitwise_not(const int32_t imm) { return vmvnq_n_s32(imm); }
[[gnu::always_inline]] nce uint16x8_t bitwise_not(const uint16_t imm) { return vmvnq_n_u16(imm); }
[[gnu::always_inline]] nce uint32x4_t bitwise_not(const uint32_t imm) { return vmvnq_n_u32(imm); }
[[gnu::always_inline]] nce int16x8_t bitwise_not(const int16_t imm, mve_pred16_t p) { return vmvnq_x_n_s16(imm, p); }
[[gnu::always_inline]] nce int32x4_t bitwise_not(const int32_t imm, mve_pred16_t p) { return vmvnq_x_n_s32(imm, p); }
[[gnu::always_inline]] nce uint16x8_t bitwise_not(const uint16_t imm, mve_pred16_t p) { return vmvnq_x_n_u16(imm, p); }
[[gnu::always_inline]] nce uint32x4_t bitwise_not(const uint32_t imm, mve_pred16_t p) { return vmvnq_x_n_u32(imm, p); }
[[gnu::always_inline]] inline int8x16x2_t load2(int8_t const *addr) { return vld2q_s8(addr); }
[[gnu::always_inline]] inline int16x8x2_t load2(int16_t const *addr) { return vld2q_s16(addr); }
[[gnu::always_inline]] inline int32x4x2_t load2(int32_t const *addr) { return vld2q_s32(addr); }
[[gnu::always_inline]] inline uint8x16x2_t load2(uint8_t const *addr) { return vld2q_u8(addr); }
[[gnu::always_inline]] inline uint16x8x2_t load2(uint16_t const *addr) { return vld2q_u16(addr); }
[[gnu::always_inline]] inline uint32x4x2_t load2(uint32_t const *addr) { return vld2q_u32(addr); }
[[gnu::always_inline]] inline int8x16x4_t load4(int8_t const *addr) { return vld4q_s8(addr); }
[[gnu::always_inline]] inline int16x8x4_t load4(int16_t const *addr) { return vld4q_s16(addr); }
[[gnu::always_inline]] inline int32x4x4_t load4(int32_t const *addr) { return vld4q_s32(addr); }
[[gnu::always_inline]] inline uint8x16x4_t load4(uint8_t const *addr) { return vld4q_u8(addr); }
[[gnu::always_inline]] inline uint16x8x4_t load4(uint16_t const *addr) { return vld4q_u16(addr); }
[[gnu::always_inline]] inline uint32x4x4_t load4(uint32_t const *addr) { return vld4q_u32(addr); }
[[gnu::always_inline]] inline int8x16_t load1(int8_t const *base, mve_pred16_t p) { return vld1q_z_s8(base, p); }
[[gnu::always_inline]] inline int16x8_t load1(int16_t const *base, mve_pred16_t p) { return vld1q_z_s16(base, p); }
[[gnu::always_inline]] inline int32x4_t load1(int32_t const *base, mve_pred16_t p) { return vld1q_z_s32(base, p); }
[[gnu::always_inline]] inline uint8x16_t load1(uint8_t const *base, mve_pred16_t p) { return vld1q_z_u8(base, p); }
[[gnu::always_inline]] inline uint16x8_t load1(uint16_t const *base, mve_pred16_t p) { return vld1q_z_u16(base, p); }
[[gnu::always_inline]] inline uint32x4_t load1(uint32_t const *base, mve_pred16_t p) { return vld1q_z_u32(base, p); }
template <> [[gnu::always_inline]] nce int8x16_t load_byte(int8_t const *base) { return vldrbq_s8(base); }
template <> [[gnu::always_inline]] nce int16x8_t load_byte(int8_t const *base) { return vldrbq_s16(base); }
template <> [[gnu::always_inline]] nce int32x4_t load_byte(int8_t const *base) { return vldrbq_s32(base); }
template <> [[gnu::always_inline]] nce uint8x16_t load_byte(uint8_t const *base) { return vldrbq_u8(base); }
template <> [[gnu::always_inline]] nce uint16x8_t load_byte(uint8_t const *base) { return vldrbq_u16(base); }
template <> [[gnu::always_inline]] nce uint32x4_t load_byte(uint8_t const *base) { return vldrbq_u32(base); }
template <> [[gnu::always_inline]] nce int8x16_t load_byte(int8_t const *base, mve_pred16_t p) { return vldrbq_z_s8(base, p); }
template <> [[gnu::always_inline]] nce int16x8_t load_byte(int8_t const *base, mve_pred16_t p) { return vldrbq_z_s16(base, p); }
template <> [[gnu::always_inline]] nce int32x4_t load_byte(int8_t const *base, mve_pred16_t p) { return vldrbq_z_s32(base, p); }
template <> [[gnu::always_inline]] nce uint8x16_t load_byte(uint8_t const *base, mve_pred16_t p) { return vldrbq_z_u8(base, p); }
template <> [[gnu::always_inline]] nce uint16x8_t load_byte(uint8_t const *base, mve_pred16_t p) { return vldrbq_z_u16(base, p); }
template <> [[gnu::always_inline]] nce uint32x4_t load_byte(uint8_t const *base, mve_pred16_t p) { return vldrbq_z_u32(base, p); }
template <> [[gnu::always_inline]] nce int16x8_t load_halfword(int16_t const *base) { return vldrhq_s16(base); }
template <> [[gnu::always_inline]] nce int32x4_t load_halfword(int16_t const *base) { return vldrhq_s32(base); }
template <> [[gnu::always_inline]] nce uint16x8_t load_halfword(uint16_t const *base) { return vldrhq_u16(base); }
template <> [[gnu::always_inline]] nce uint32x4_t load_halfword(uint16_t const *base) { return vldrhq_u32(base); }
template <> [[gnu::always_inline]] nce int16x8_t load_halfword(int16_t const *base, mve_pred16_t p) { return vldrhq_z_s16(base, p); }
template <> [[gnu::always_inline]] nce int32x4_t load_halfword(int16_t const *base, mve_pred16_t p) { return vldrhq_z_s32(base, p); }
template <> [[gnu::always_inline]] nce uint16x8_t load_halfword(uint16_t const *base, mve_pred16_t p) { return vldrhq_z_u16(base, p); }
template <> [[gnu::always_inline]] nce uint32x4_t load_halfword(uint16_t const *base, mve_pred16_t p) { return vldrhq_z_u32(base, p); }
[[gnu::always_inline]] nce int32x4_t load_word(int32_t const *base) { return vldrwq_s32(base); }
[[gnu::always_inline]] nce uint32x4_t load_word(uint32_t const *base) { return vldrwq_u32(base); }
[[gnu::always_inline]] nce int32x4_t load_word(int32_t const *base, mve_pred16_t p) { return vldrwq_z_s32(base, p); }
[[gnu::always_inline]] nce uint32x4_t load_word(uint32_t const *base, mve_pred16_t p) { return vldrwq_z_u32(base, p); }
[[gnu::always_inline]] nce int16x8_t load_halfword_gather_offset(int16_t const *base, uint16x8_t offset) { return vldrhq_gather_offset_s16(base, offset); }
[[gnu::always_inline]] nce int32x4_t load_halfword_gather_offset(int16_t const *base, uint32x4_t offset) { return vldrhq_gather_offset_s32(base, offset); }
[[gnu::always_inline]] nce uint16x8_t load_halfword_gather_offset(uint16_t const *base, uint16x8_t offset) { return vldrhq_gather_offset_u16(base, offset); }
[[gnu::always_inline]] nce uint32x4_t load_halfword_gather_offset(uint16_t const *base, uint32x4_t offset) { return vldrhq_gather_offset_u32(base, offset); }
[[gnu::always_inline]] nce int16x8_t load_halfword_gather_offset(int16_t const *base, uint16x8_t offset, mve_pred16_t p) { return vldrhq_gather_offset_z_s16(base, offset, p); }
[[gnu::always_inline]] nce int32x4_t load_halfword_gather_offset(int16_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrhq_gather_offset_z_s32(base, offset, p); }
[[gnu::always_inline]] nce uint16x8_t load_halfword_gather_offset(uint16_t const *base, uint16x8_t offset, mve_pred16_t p) { return vldrhq_gather_offset_z_u16(base, offset, p); }
[[gnu::always_inline]] nce uint32x4_t load_halfword_gather_offset(uint16_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrhq_gather_offset_z_u32(base, offset, p); }
[[gnu::always_inline]] nce int16x8_t load_halfword_gather_shifted_offset(int16_t const *base, uint16x8_t offset) { return vldrhq_gather_shifted_offset_s16(base, offset); }
[[gnu::always_inline]] nce int32x4_t load_halfword_gather_shifted_offset(int16_t const *base, uint32x4_t offset) { return vldrhq_gather_shifted_offset_s32(base, offset); }
[[gnu::always_inline]] nce uint16x8_t load_halfword_gather_shifted_offset(uint16_t const *base, uint16x8_t offset) { return vldrhq_gather_shifted_offset_u16(base, offset); }
[[gnu::always_inline]] nce uint32x4_t load_halfword_gather_shifted_offset(uint16_t const *base, uint32x4_t offset) { return vldrhq_gather_shifted_offset_u32(base, offset); }
[[gnu::always_inline]] nce int16x8_t load_halfword_gather_shifted_offset(int16_t const *base, uint16x8_t offset, mve_pred16_t p) { return vldrhq_gather_shifted_offset_z_s16(base, offset, p); }
[[gnu::always_inline]] nce int32x4_t load_halfword_gather_shifted_offset(int16_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrhq_gather_shifted_offset_z_s32(base, offset, p); }
[[gnu::always_inline]] nce uint16x8_t load_halfword_gather_shifted_offset(uint16_t const *base, uint16x8_t offset, mve_pred16_t p) { return vldrhq_gather_shifted_offset_z_u16(base, offset, p); }
[[gnu::always_inline]] nce uint32x4_t load_halfword_gather_shifted_offset(uint16_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrhq_gather_shifted_offset_z_u32(base, offset, p); }
[[gnu::always_inline]] nce int8x16_t load_byte_gather_offset(int8_t const *base, uint8x16_t offset) { return vldrbq_gather_offset_s8(base, offset); }
[[gnu::always_inline]] nce int16x8_t load_byte_gather_offset(int8_t const *base, uint16x8_t offset) { return vldrbq_gather_offset_s16(base, offset); }
[[gnu::always_inline]] nce int32x4_t load_byte_gather_offset(int8_t const *base, uint32x4_t offset) { return vldrbq_gather_offset_s32(base, offset); }
[[gnu::always_inline]] nce uint8x16_t load_byte_gather_offset(uint8_t const *base, uint8x16_t offset) { return vldrbq_gather_offset_u8(base, offset); }
[[gnu::always_inline]] nce uint16x8_t load_byte_gather_offset(uint8_t const *base, uint16x8_t offset) { return vldrbq_gather_offset_u16(base, offset); }
[[gnu::always_inline]] nce uint32x4_t load_byte_gather_offset(uint8_t const *base, uint32x4_t offset) { return vldrbq_gather_offset_u32(base, offset); }
[[gnu::always_inline]] nce int8x16_t load_byte_gather_offset(int8_t const *base, uint8x16_t offset, mve_pred16_t p) { return vldrbq_gather_offset_z_s8(base, offset, p); }
[[gnu::always_inline]] nce int16x8_t load_byte_gather_offset(int8_t const *base, uint16x8_t offset, mve_pred16_t p) { return vldrbq_gather_offset_z_s16(base, offset, p); }
[[gnu::always_inline]] nce int32x4_t load_byte_gather_offset(int8_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrbq_gather_offset_z_s32(base, offset, p); }
[[gnu::always_inline]] nce uint8x16_t load_byte_gather_offset(uint8_t const *base, uint8x16_t offset, mve_pred16_t p) { return vldrbq_gather_offset_z_u8(base, offset, p); }
[[gnu::always_inline]] nce uint16x8_t load_byte_gather_offset(uint8_t const *base, uint16x8_t offset, mve_pred16_t p) { return vldrbq_gather_offset_z_u16(base, offset, p); }
[[gnu::always_inline]] nce uint32x4_t load_byte_gather_offset(uint8_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrbq_gather_offset_z_u32(base, offset, p); }
[[gnu::always_inline]] nce int32x4_t load_word_gather_offset(int32_t const *base, uint32x4_t offset) { return vldrwq_gather_offset_s32(base, offset); }
[[gnu::always_inline]] nce uint32x4_t load_word_gather_offset(uint32_t const *base, uint32x4_t offset) { return vldrwq_gather_offset_u32(base, offset); }
[[gnu::always_inline]] nce int32x4_t load_word_gather_offset(int32_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrwq_gather_offset_z_s32(base, offset, p); }
[[gnu::always_inline]] nce uint32x4_t load_word_gather_offset(uint32_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrwq_gather_offset_z_u32(base, offset, p); }
[[gnu::always_inline]] nce int32x4_t load_word_gather_shifted_offset(int32_t const *base, uint32x4_t offset) { return vldrwq_gather_shifted_offset_s32(base, offset); }
[[gnu::always_inline]] nce uint32x4_t load_word_gather_shifted_offset(uint32_t const *base, uint32x4_t offset) { return vldrwq_gather_shifted_offset_u32(base, offset); }
[[gnu::always_inline]] nce int32x4_t load_word_gather_shifted_offset(int32_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrwq_gather_shifted_offset_z_s32(base, offset, p); }
[[gnu::always_inline]] nce uint32x4_t load_word_gather_shifted_offset(uint32_t const *base, uint32x4_t offset, mve_pred16_t p) { return vldrwq_gather_shifted_offset_z_u32(base, offset, p); }
[[gnu::always_inline]] nce int64x2_t load_doubleword_gather_offset(int64_t const *base, uint64x2_t offset) { return vldrdq_gather_offset_s64(base, offset); }
[[gnu::always_inline]] nce uint64x2_t load_doubleword_gather_offset(uint64_t const *base, uint64x2_t offset) { return vldrdq_gather_offset_u64(base, offset); }
[[gnu::always_inline]] nce int64x2_t load_doubleword_gather_offset(int64_t const *base, uint64x2_t offset, mve_pred16_t p) { return vldrdq_gather_offset_z_s64(base, offset, p); }
[[gnu::always_inline]] nce uint64x2_t load_doubleword_gather_offset(uint64_t const *base, uint64x2_t offset, mve_pred16_t p) { return vldrdq_gather_offset_z_u64(base, offset, p); }
[[gnu::always_inline]] nce int64x2_t load_doubleword_gather_shifted_offset(int64_t const *base, uint64x2_t offset) { return vldrdq_gather_shifted_offset_s64(base, offset); }
[[gnu::always_inline]] nce uint64x2_t load_doubleword_gather_shifted_offset(uint64_t const *base, uint64x2_t offset) { return vldrdq_gather_shifted_offset_u64(base, offset); }
[[gnu::always_inline]] nce int64x2_t load_doubleword_gather_shifted_offset(int64_t const *base, uint64x2_t offset, mve_pred16_t p) { return vldrdq_gather_shifted_offset_z_s64(base, offset, p); }
[[gnu::always_inline]] nce uint64x2_t load_doubleword_gather_shifted_offset(uint64_t const *base, uint64x2_t offset, mve_pred16_t p) { return vldrdq_gather_shifted_offset_z_u64(base, offset, p); }
[[gnu::always_inline]] inline void store2(int8_t *addr, int8x16x2_t value) { return vst2q_s8(addr, value); }
[[gnu::always_inline]] inline void store2(int16_t *addr, int16x8x2_t value) { return vst2q_s16(addr, value); }
[[gnu::always_inline]] inline void store2(int32_t *addr, int32x4x2_t value) { return vst2q_s32(addr, value); }
[[gnu::always_inline]] inline void store2(uint8_t *addr, uint8x16x2_t value) { return vst2q_u8(addr, value); }
[[gnu::always_inline]] inline void store2(uint16_t *addr, uint16x8x2_t value) { return vst2q_u16(addr, value); }
[[gnu::always_inline]] inline void store2(uint32_t *addr, uint32x4x2_t value) { return vst2q_u32(addr, value); }
[[gnu::always_inline]] inline void store4(int8_t *addr, int8x16x4_t value) { return vst4q_s8(addr, value); }
[[gnu::always_inline]] inline void store4(int16_t *addr, int16x8x4_t value) { return vst4q_s16(addr, value); }
[[gnu::always_inline]] inline void store4(int32_t *addr, int32x4x4_t value) { return vst4q_s32(addr, value); }
[[gnu::always_inline]] inline void store4(uint8_t *addr, uint8x16x4_t value) { return vst4q_u8(addr, value); }
[[gnu::always_inline]] inline void store4(uint16_t *addr, uint16x8x4_t value) { return vst4q_u16(addr, value); }
[[gnu::always_inline]] inline void store4(uint32_t *addr, uint32x4x4_t value) { return vst4q_u32(addr, value); }
[[gnu::always_inline]] inline void store1(int8_t *base, int8x16_t value, mve_pred16_t p) { return vst1q_p_s8(base, value, p); }
[[gnu::always_inline]] inline void store1(int16_t *base, int16x8_t value, mve_pred16_t p) { return vst1q_p_s16(base, value, p); }
[[gnu::always_inline]] inline void store1(int32_t *base, int32x4_t value, mve_pred16_t p) { return vst1q_p_s32(base, value, p); }
[[gnu::always_inline]] inline void store1(uint8_t *base, uint8x16_t value, mve_pred16_t p) { return vst1q_p_u8(base, value, p); }
[[gnu::always_inline]] inline void store1(uint16_t *base, uint16x8_t value, mve_pred16_t p) { return vst1q_p_u16(base, value, p); }
[[gnu::always_inline]] inline void store1(uint32_t *base, uint32x4_t value, mve_pred16_t p) { return vst1q_p_u32(base, value, p); }
[[gnu::always_inline]] nce void store_byte(int8_t *base, int8x16_t value) { return vstrbq_s8(base, value); }
[[gnu::always_inline]] nce void store_byte(int8_t *base, int16x8_t value) { return vstrbq_s16(base, value); }
[[gnu::always_inline]] nce void store_byte(int8_t *base, int32x4_t value) { return vstrbq_s32(base, value); }
[[gnu::always_inline]] nce void store_byte(uint8_t *base, uint8x16_t value) { return vstrbq_u8(base, value); }
[[gnu::always_inline]] nce void store_byte(uint8_t *base, uint16x8_t value) { return vstrbq_u16(base, value); }
[[gnu::always_inline]] nce void store_byte(uint8_t *base, uint32x4_t value) { return vstrbq_u32(base, value); }
[[gnu::always_inline]] nce void store_byte(int8_t *base, int8x16_t value, mve_pred16_t p) { return vstrbq_p_s8(base, value, p); }
[[gnu::always_inline]] nce void store_byte(int8_t *base, int16x8_t value, mve_pred16_t p) { return vstrbq_p_s16(base, value, p); }
[[gnu::always_inline]] nce void store_byte(int8_t *base, int32x4_t value, mve_pred16_t p) { return vstrbq_p_s32(base, value, p); }
[[gnu::always_inline]] nce void store_byte(uint8_t *base, uint8x16_t value, mve_pred16_t p) { return vstrbq_p_u8(base, value, p); }
[[gnu::always_inline]] nce void store_byte(uint8_t *base, uint16x8_t value, mve_pred16_t p) { return vstrbq_p_u16(base, value, p); }
[[gnu::always_inline]] nce void store_byte(uint8_t *base, uint32x4_t value, mve_pred16_t p) { return vstrbq_p_u32(base, value, p); }
[[gnu::always_inline]] nce void store_halfword(int16_t *base, int16x8_t value) { return vstrhq_s16(base, value); }
[[gnu::always_inline]] nce void store_halfword(int16_t *base, int32x4_t value) { return vstrhq_s32(base, value); }
[[gnu::always_inline]] nce void store_halfword(uint16_t *base, uint16x8_t value) { return vstrhq_u16(base, value); }
[[gnu::always_inline]] nce void store_halfword(uint16_t *base, uint32x4_t value) { return vstrhq_u32(base, value); }
[[gnu::always_inline]] nce void store_halfword(int16_t *base, int16x8_t value, mve_pred16_t p) { return vstrhq_p_s16(base, value, p); }
[[gnu::always_inline]] nce void store_halfword(int16_t *base, int32x4_t value, mve_pred16_t p) { return vstrhq_p_s32(base, value, p); }
[[gnu::always_inline]] nce void store_halfword(uint16_t *base, uint16x8_t value, mve_pred16_t p) { return vstrhq_p_u16(base, value, p); }
[[gnu::always_inline]] nce void store_halfword(uint16_t *base, uint32x4_t value, mve_pred16_t p) { return vstrhq_p_u32(base, value, p); }
[[gnu::always_inline]] nce void store_word(int32_t *base, int32x4_t value) { return vstrwq_s32(base, value); }
[[gnu::always_inline]] nce void store_word(uint32_t *base, uint32x4_t value) { return vstrwq_u32(base, value); }
[[gnu::always_inline]] nce void store_word(int32_t *base, int32x4_t value, mve_pred16_t p) { return vstrwq_p_s32(base, value, p); }
[[gnu::always_inline]] nce void store_word(uint32_t *base, uint32x4_t value, mve_pred16_t p) { return vstrwq_p_u32(base, value, p); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(int8_t *base, uint8x16_t offset, int8x16_t value) { return vstrbq_scatter_offset_s8(base, offset, value); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(int8_t *base, uint16x8_t offset, int16x8_t value) { return vstrbq_scatter_offset_s16(base, offset, value); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(int8_t *base, uint32x4_t offset, int32x4_t value) { return vstrbq_scatter_offset_s32(base, offset, value); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(uint8_t *base, uint8x16_t offset, uint8x16_t value) { return vstrbq_scatter_offset_u8(base, offset, value); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(uint8_t *base, uint16x8_t offset, uint16x8_t value) { return vstrbq_scatter_offset_u16(base, offset, value); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(uint8_t *base, uint32x4_t offset, uint32x4_t value) { return vstrbq_scatter_offset_u32(base, offset, value); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(int8_t *base, uint8x16_t offset, int8x16_t value, mve_pred16_t p) { return vstrbq_scatter_offset_p_s8(base, offset, value, p); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(int8_t *base, uint16x8_t offset, int16x8_t value, mve_pred16_t p) { return vstrbq_scatter_offset_p_s16(base, offset, value, p); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(int8_t *base, uint32x4_t offset, int32x4_t value, mve_pred16_t p) { return vstrbq_scatter_offset_p_s32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(uint8_t *base, uint8x16_t offset, uint8x16_t value, mve_pred16_t p) { return vstrbq_scatter_offset_p_u8(base, offset, value, p); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(uint8_t *base, uint16x8_t offset, uint16x8_t value, mve_pred16_t p) { return vstrbq_scatter_offset_p_u16(base, offset, value, p); }
[[gnu::always_inline]] nce void store_byte_scatter_offset(uint8_t *base, uint32x4_t offset, uint32x4_t value, mve_pred16_t p) { return vstrbq_scatter_offset_p_u32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_halfword_scatter_offset(int16_t *base, uint16x8_t offset, int16x8_t value) { return vstrhq_scatter_offset_s16(base, offset, value); }
[[gnu::always_inline]] nce void store_halfword_scatter_offset(int16_t *base, uint32x4_t offset, int32x4_t value) { return vstrhq_scatter_offset_s32(base, offset, value); }
[[gnu::always_inline]] nce void store_halfword_scatter_offset(uint16_t *base, uint16x8_t offset, uint16x8_t value) { return vstrhq_scatter_offset_u16(base, offset, value); }
[[gnu::always_inline]] nce void store_halfword_scatter_offset(uint16_t *base, uint32x4_t offset, uint32x4_t value) { return vstrhq_scatter_offset_u32(base, offset, value); }
[[gnu::always_inline]] nce void store_halfword_scatter_offset(int16_t *base, uint16x8_t offset, int16x8_t value, mve_pred16_t p) { return vstrhq_scatter_offset_p_s16(base, offset, value, p); }
[[gnu::always_inline]] nce void store_halfword_scatter_offset(int16_t *base, uint32x4_t offset, int32x4_t value, mve_pred16_t p) { return vstrhq_scatter_offset_p_s32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_halfword_scatter_offset(uint16_t *base, uint16x8_t offset, uint16x8_t value, mve_pred16_t p) { return vstrhq_scatter_offset_p_u16(base, offset, value, p); }
[[gnu::always_inline]] nce void store_halfword_scatter_offset(uint16_t *base, uint32x4_t offset, uint32x4_t value, mve_pred16_t p) { return vstrhq_scatter_offset_p_u32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_halfword_scatter_shifted_offset(int16_t *base, uint16x8_t offset, int16x8_t value) { return vstrhq_scatter_shifted_offset_s16(base, offset, value); }
[[gnu::always_inline]] nce void store_halfword_scatter_shifted_offset(int16_t *base, uint32x4_t offset, int32x4_t value) { return vstrhq_scatter_shifted_offset_s32(base, offset, value); }
[[gnu::always_inline]] nce void store_halfword_scatter_shifted_offset(uint16_t *base, uint16x8_t offset, uint16x8_t value) { return vstrhq_scatter_shifted_offset_u16(base, offset, value); }
[[gnu::always_inline]] nce void store_halfword_scatter_shifted_offset(uint16_t *base, uint32x4_t offset, uint32x4_t value) { return vstrhq_scatter_shifted_offset_u32(base, offset, value); }
[[gnu::always_inline]] nce void store_halfword_scatter_shifted_offset(int16_t *base, uint16x8_t offset, int16x8_t value, mve_pred16_t p) { return vstrhq_scatter_shifted_offset_p_s16(base, offset, value, p); }
[[gnu::always_inline]] nce void store_halfword_scatter_shifted_offset(int16_t *base, uint32x4_t offset, int32x4_t value, mve_pred16_t p) { return vstrhq_scatter_shifted_offset_p_s32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_halfword_scatter_shifted_offset(uint16_t *base, uint16x8_t offset, uint16x8_t value, mve_pred16_t p) { return vstrhq_scatter_shifted_offset_p_u16(base, offset, value, p); }
[[gnu::always_inline]] nce void store_halfword_scatter_shifted_offset(uint16_t *base, uint32x4_t offset, uint32x4_t value, mve_pred16_t p) { return vstrhq_scatter_shifted_offset_p_u32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_word_scatter_offset(int32_t *base, uint32x4_t offset, int32x4_t value) { return vstrwq_scatter_offset_s32(base, offset, value); }
[[gnu::always_inline]] nce void store_word_scatter_offset(uint32_t *base, uint32x4_t offset, uint32x4_t value) { return vstrwq_scatter_offset_u32(base, offset, value); }
[[gnu::always_inline]] nce void store_word_scatter_offset(int32_t *base, uint32x4_t offset, int32x4_t value, mve_pred16_t p) { return vstrwq_scatter_offset_p_s32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_word_scatter_offset(uint32_t *base, uint32x4_t offset, uint32x4_t value, mve_pred16_t p) { return vstrwq_scatter_offset_p_u32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_word_scatter_shifted_offset(int32_t *base, uint32x4_t offset, int32x4_t value) { return vstrwq_scatter_shifted_offset_s32(base, offset, value); }
[[gnu::always_inline]] nce void store_word_scatter_shifted_offset(uint32_t *base, uint32x4_t offset, uint32x4_t value) { return vstrwq_scatter_shifted_offset_u32(base, offset, value); }
[[gnu::always_inline]] nce void store_word_scatter_shifted_offset(int32_t *base, uint32x4_t offset, int32x4_t value, mve_pred16_t p) { return vstrwq_scatter_shifted_offset_p_s32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_word_scatter_shifted_offset(uint32_t *base, uint32x4_t offset, uint32x4_t value, mve_pred16_t p) { return vstrwq_scatter_shifted_offset_p_u32(base, offset, value, p); }
[[gnu::always_inline]] nce void store_doubleword_scatter_offset(int64_t *base, uint64x2_t offset, int64x2_t value) { return vstrdq_scatter_offset_s64(base, offset, value); }
[[gnu::always_inline]] nce void store_doubleword_scatter_offset(uint64_t *base, uint64x2_t offset, uint64x2_t value) { return vstrdq_scatter_offset_u64(base, offset, value); }
[[gnu::always_inline]] nce void store_doubleword_scatter_offset(int64_t *base, uint64x2_t offset, int64x2_t value, mve_pred16_t p) { return vstrdq_scatter_offset_p_s64(base, offset, value, p); }
[[gnu::always_inline]] nce void store_doubleword_scatter_offset(uint64_t *base, uint64x2_t offset, uint64x2_t value, mve_pred16_t p) { return vstrdq_scatter_offset_p_u64(base, offset, value, p); }
[[gnu::always_inline]] nce void store_doubleword_scatter_shifted_offset(int64_t *base, uint64x2_t offset, int64x2_t value) { return vstrdq_scatter_shifted_offset_s64(base, offset, value); }
[[gnu::always_inline]] nce void store_doubleword_scatter_shifted_offset(uint64_t *base, uint64x2_t offset, uint64x2_t value) { return vstrdq_scatter_shifted_offset_u64(base, offset, value); }
[[gnu::always_inline]] nce void store_doubleword_scatter_shifted_offset(int64_t *base, uint64x2_t offset, int64x2_t value, mve_pred16_t p) { return vstrdq_scatter_shifted_offset_p_s64(base, offset, value, p); }
[[gnu::always_inline]] nce void store_doubleword_scatter_shifted_offset(uint64_t *base, uint64x2_t offset, uint64x2_t value, mve_pred16_t p) { return vstrdq_scatter_shifted_offset_p_u64(base, offset, value, p); }
[[gnu::always_inline]] nce uint64_t shift_left_round_saturate_long_unsigned(uint64_t value, int32_t shift) { return uqrshll(value, shift); }
[[gnu::always_inline]] nce uint64_t shift_left_round_saturate_long_saturate48_unsigned(uint64_t value, int32_t shift) { return uqrshll_sat48(value, shift); }
template <int shift>[[gnu::always_inline]] nce uint64_t shift_left_long_saturate_unsigned(uint64_t value) { return uqshll(value, shift); }
[[gnu::always_inline]] nce uint32_t shift_left_round_saturate_unsigned(uint32_t value, int32_t shift) { return uqrshl(value, shift); }
template <int shift>[[gnu::always_inline]] nce int64_t shift_left_long_saturate_signed(int64_t value) { return sqshll(value, shift); }
template <int shift>[[gnu::always_inline]] nce uint32_t shift_left_saturate_unsigned(uint32_t value) { return uqshl(value, shift); }
template <int shift>[[gnu::always_inline]] nce int32_t shift_left_saturate_signed(int32_t value) { return sqshl(value, shift); }
[[gnu::always_inline]] nce int64x2_t predicate_select(int64x2_t a, int64x2_t b, mve_pred16_t p) { return vpselq_s64(a, b, p); }
template <> [[gnu::always_inline]] nce mve_pred16_t create_tail_predicate(uint32_t a) { return vctp8q(a); }
template <> [[gnu::always_inline]] nce mve_pred16_t create_tail_predicate(uint32_t a) { return vctp16q(a); }
template <> [[gnu::always_inline]] nce mve_pred16_t create_tail_predicate(uint32_t a) { return vctp32q(a); }
template <> [[gnu::always_inline]] nce mve_pred16_t create_tail_predicate(uint32_t a) { return vctp64q(a); }
template <> [[gnu::always_inline]] nce mve_pred16_t create_tail_predicate(uint32_t a, mve_pred16_t p) { return vctp8q_m(a, p); }
template <> [[gnu::always_inline]] nce mve_pred16_t create_tail_predicate(uint32_t a, mve_pred16_t p) { return vctp16q_m(a, p); }
template <> [[gnu::always_inline]] nce mve_pred16_t create_tail_predicate(uint32_t a, mve_pred16_t p) { return vctp32q_m(a, p); }
template <> [[gnu::always_inline]] nce mve_pred16_t create_tail_predicate(uint32_t a, mve_pred16_t p) { return vctp64q_m(a, p); }
[[gnu::always_inline]] nce uint64_t left_shift_long(uint64_t value, int32_t shift) { return lsll(value, shift); }
[[gnu::always_inline]] nce int64_t shift_right_long_arithmetic(int64_t value, int32_t shift) { return asrl(value, shift); }
[[gnu::always_inline]] nce int64_t shift_right_saturate_round_long_signed(int64_t value, int32_t shift) { return sqrshrl(value, shift); }
[[gnu::always_inline]] nce int64_t shift_right_saturate_round_long_saturate48_signed(int64_t value, int32_t shift) { return sqrshrl_sat48(value, shift); }
[[gnu::always_inline]] nce int32_t shift_right_saturate_round_signed(int32_t value, int32_t shift) { return sqrshr(value, shift); }
template <int shift>[[gnu::always_inline]] nce uint64_t shift_right_round_long_unsigned(uint64_t value) { return urshrl(value, shift); }
template <int shift>[[gnu::always_inline]] nce int64_t shift_right_round_long_signed(int64_t value) { return srshrl(value, shift); }
template <int shift>[[gnu::always_inline]] nce uint32_t shift_right_round_unsigned(uint32_t value) { return urshr(value, shift); }
template <int shift>[[gnu::always_inline]] nce int32_t shift_right_round_signed(int32_t value) { return srshr(value, shift); }
// clang-format on
}  // namespace helium
#endif
