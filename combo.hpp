#pragma once
#include <arm_neon.h>
#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <type_traits>
#include <span>
#pragma once
#include <arm_neon.h>
#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

namespace neon {

template <typename T> nce T convert(float32x2_t a);
template <typename T> nce T convert(float32x4_t a);
template <typename T> nce T convert(int32x2_t a);
template <typename T> nce T convert(int32x4_t a);
template <typename T> nce T convert(uint32x2_t a);
template <typename T> nce T convert(uint32x4_t a);
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
template <typename T> nce T reinterpret(int8x16_t a);
template <typename T> nce T reinterpret(int16x8_t a);
template <typename T> nce T reinterpret(int32x4_t a);
template <typename T> nce T reinterpret(float32x4_t a);
template <typename T> nce T reinterpret(uint8x16_t a);
template <typename T> nce T reinterpret(uint16x8_t a);
template <typename T> nce T reinterpret(uint32x4_t a);
template <typename T> nce T reinterpret(poly8x16_t a);
template <typename T> nce T reinterpret(poly16x8_t a);
template <typename T> nce T reinterpret(uint64x2_t a);
template <typename T> nce T reinterpret(int64x2_t a);
template <typename T> nce T create(uint64_t a);
template <typename T> nce T duplicate_element(int8_t value);
template <typename T> nce T duplicate_element(int16_t value);
template <typename T> nce T duplicate_element(int32_t value);
template <typename T> nce T duplicate_element(int64_t value);
template <typename T> nce T duplicate_element(uint8_t value);
template <typename T> nce T duplicate_element(uint16_t value);
template <typename T> nce T duplicate_element(uint32_t value);
template <typename T> nce T duplicate_element(uint64_t value);
template <typename T> nce T duplicate_element(float32_t value);
template <typename T> nce T duplicate_element(poly8_t value);
template <typename T> nce T duplicate_element(poly16_t value);
template <typename T> nce T move(int8_t value);
template <typename T> nce T move(int16_t value);
template <typename T> nce T move(int32_t value);
template <typename T> nce T move(int64_t value);
template <typename T> nce T move(uint8_t value);
template <typename T> nce T move(uint16_t value);
template <typename T> nce T move(uint32_t value);
template <typename T> nce T move(uint64_t value);
template <typename T> nce T move(float32_t value);
template <typename T> nce T move(poly8_t value);
template <typename T> nce T move(poly16_t value);
template <typename T> nce T duplicate_element(int8x8_t vec);
template <typename T> nce T duplicate_element(int16x4_t vec);
template <typename T> nce T duplicate_element(int32x2_t vec);
template <typename T> nce T duplicate_element(int64x1_t vec);
template <typename T> nce T duplicate_element(uint8x8_t vec);
template <typename T> nce T duplicate_element(uint16x4_t vec);
template <typename T> nce T duplicate_element(uint32x2_t vec);
template <typename T> nce T duplicate_element(uint64x1_t vec);
template <typename T> nce T duplicate_element(float32x2_t vec);
template <typename T> nce T duplicate_element(poly8x8_t vec);
template <typename T> nce T duplicate_element(poly16x4_t vec);
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
nce void store1(int8_t *ptr, int8x8_t val);
nce void store1(int8_t *ptr, int8x16_t val);
nce void store1(int16_t *ptr, int16x4_t val);
nce void store1(int16_t *ptr, int16x8_t val);
nce void store1(int32_t *ptr, int32x2_t val);
nce void store1(int32_t *ptr, int32x4_t val);
nce void store1(int64_t *ptr, int64x1_t val);
nce void store1(int64_t *ptr, int64x2_t val);
nce void store1(uint8_t *ptr, uint8x8_t val);
nce void store1(uint8_t *ptr, uint8x16_t val);
nce void store1(uint16_t *ptr, uint16x4_t val);
nce void store1(uint16_t *ptr, uint16x8_t val);
nce void store1(uint32_t *ptr, uint32x2_t val);
nce void store1(uint32_t *ptr, uint32x4_t val);
nce void store1(uint64_t *ptr, uint64x1_t val);
nce void store1(uint64_t *ptr, uint64x2_t val);
nce void store1(float32_t *ptr, float32x2_t val);
nce void store1(float32_t *ptr, float32x4_t val);
nce void store1(poly8_t *ptr, poly8x8_t val);
nce void store1(poly8_t *ptr, poly8x16_t val);
nce void store1(poly16_t *ptr, poly16x4_t val);
nce void store1(poly16_t *ptr, poly16x8_t val);
nce void store2(int8_t *ptr, int8x8x2_t val);
nce void store2(int16_t *ptr, int16x4x2_t val);
nce void store2(int16_t *ptr, int16x8x2_t val);
nce void store2(int32_t *ptr, int32x2x2_t val);
nce void store2(int32_t *ptr, int32x4x2_t val);
nce void store2(uint8_t *ptr, uint8x8x2_t val);
nce void store2(uint16_t *ptr, uint16x4x2_t val);
nce void store2(uint16_t *ptr, uint16x8x2_t val);
nce void store2(uint32_t *ptr, uint32x2x2_t val);
nce void store2(uint32_t *ptr, uint32x4x2_t val);
nce void store2(float32_t *ptr, float32x2x2_t val);
nce void store2(float32_t *ptr, float32x4x2_t val);
nce void store2(poly8_t *ptr, poly8x8x2_t val);
nce void store2(poly16_t *ptr, poly16x4x2_t val);
nce void store2(poly16_t *ptr, poly16x8x2_t val);
nce void store3(int8_t *ptr, int8x8x3_t val);
nce void store3(int8_t *ptr, int8x16x3_t val);
nce void store3(int16_t *ptr, int16x4x3_t val);
nce void store3(int16_t *ptr, int16x8x3_t val);
nce void store3(int32_t *ptr, int32x2x3_t val);
nce void store3(int32_t *ptr, int32x4x3_t val);
nce void store3(uint8_t *ptr, uint8x8x3_t val);
nce void store3(uint8_t *ptr, uint8x16x3_t val);
nce void store3(uint16_t *ptr, uint16x4x3_t val);
nce void store3(uint16_t *ptr, uint16x8x3_t val);
nce void store3(uint32_t *ptr, uint32x2x3_t val);
nce void store3(uint32_t *ptr, uint32x4x3_t val);
nce void store3(float32_t *ptr, float32x2x3_t val);
nce void store3(float32_t *ptr, float32x4x3_t val);
nce void store3(poly8_t *ptr, poly8x8x3_t val);
nce void store3(poly8_t *ptr, poly8x16x3_t val);
nce void store3(poly16_t *ptr, poly16x4x3_t val);
nce void store3(poly16_t *ptr, poly16x8x3_t val);
nce void store4(int8_t *ptr, int8x8x4_t val);
nce void store4(int16_t *ptr, int16x4x4_t val);
nce void store4(int16_t *ptr, int16x8x4_t val);
nce void store4(int32_t *ptr, int32x2x4_t val);
nce void store4(int32_t *ptr, int32x4x4_t val);
nce void store4(uint8_t *ptr, uint8x8x4_t val);
nce void store4(uint16_t *ptr, uint16x4x4_t val);
nce void store4(uint16_t *ptr, uint16x8x4_t val);
nce void store4(uint32_t *ptr, uint32x2x4_t val);
nce void store4(uint32_t *ptr, uint32x4x4_t val);
nce void store4(float32_t *ptr, float32x2x4_t val);
nce void store4(float32_t *ptr, float32x4x4_t val);
nce void store4(poly8_t *ptr, poly8x8x4_t val);
nce void store4(poly16_t *ptr, poly16x4x4_t val);
nce void store4(poly16_t *ptr, poly16x8x4_t val);
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
[[gnu::always_inline]] nce uint8x8_t subtract_high(uint8x8_t a, uint8x8_t b) { return vhsub_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract_saturate(uint8x8_t a, uint8x8_t b) { return vqsub_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract_abs(uint8x8_t a, uint8x8_t b) { return vabd_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_abs_long(uint8x8_t a, uint8x8_t b) { return vabdl_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract_abs_add(uint8x8_t a, uint8x8_t b, uint8x8_t c) { return vaba_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x8_t max(uint8x8_t a, uint8x8_t b) { return vmax_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t min(uint8x8_t a, uint8x8_t b) { return vmin_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t add_pairwise(uint8x8_t a, uint8x8_t b) { return vpadd_u8(a, b); }
[[gnu::always_inline]] nce uint16x4_t add_pairwise_long(uint8x8_t a) { return vpaddl_u8(a); }
[[gnu::always_inline]] nce uint8x8_t max_pairwise(uint8x8_t a, uint8x8_t b) { return vpmax_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t min_pairwise(uint8x8_t a, uint8x8_t b) { return vpmin_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t equal(uint8x8_t a, uint8x8_t b) { return vceq_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t greater_than_or_equal(uint8x8_t a, uint8x8_t b) { return vcge_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t less_than_or_equal(uint8x8_t a, uint8x8_t b) { return vcle_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t greater_than(uint8x8_t a, uint8x8_t b) { return vcgt_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t less_than(uint8x8_t a, uint8x8_t b) { return vclt_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t and_test_nonzero(uint8x8_t a, uint8x8_t b) { return vtst_u8(a, b); }
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
[[gnu::always_inline]] nce uint8x8_t not_bitwise(uint8x8_t a) { return vmvn_u8(a); }
[[gnu::always_inline]] nce uint8x8_t and_bitwise(uint8x8_t a, uint8x8_t b) { return vand_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t or_bitwise(uint8x8_t a, uint8x8_t b) { return vorr_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t xor_bitwise(uint8x8_t a, uint8x8_t b) { return veor_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t or_not_bitwise(uint8x8_t a, uint8x8_t b) { return vorn_u8(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce int8x8_t count_leading_sign_bits(uint8x8_t a) { return vcls_u8(a); }
#endif
[[gnu::always_inline]] nce uint8x8_t count_leading_zero_bits(uint8x8_t a) { return vclz_u8(a); }
[[gnu::always_inline]] nce uint8x8_t count_active_bits(uint8x8_t a) { return vcnt_u8(a); }
[[gnu::always_inline]] nce uint8x8_t clear_bitwise(uint8x8_t a, uint8x8_t b) { return vbic_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t select_bitwise(uint8x8_t a, uint8x8_t b, uint8x8_t c) { return vbsl_u8(a, b, c); }
[[gnu::always_inline]] nce int8x8_t select_bitwise(uint8x8_t a, int8x8_t b, int8x8_t c) { return vbsl_s8(a, b, c); }
[[gnu::always_inline]] nce poly8x8_t select_bitwise(uint8x8_t a, poly8x8_t b, poly8x8_t c) { return vbsl_p8(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint8x8_t duplicate_element(uint8x8_t vec) { return vdup_lane_u8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16_t duplicate_element(uint8x8_t vec) { return vdupq_lane_u8(vec, lane); }
[[gnu::always_inline]] nce uint8x16_t combine(uint8x8_t low, uint8x8_t high) { return vcombine_u8(low, high); }
template <int lane>[[gnu::always_inline]] nce uint8_t get(uint8x8_t v) { return vget_lane_u8(v, lane); }
template <int n>[[gnu::always_inline]] nce uint8x8_t extract(uint8x8_t a, uint8x8_t b) { return vext_u8(a, b, n); }
[[gnu::always_inline]] nce uint8x8_t reverse_64bit(uint8x8_t vec) { return vrev64_u8(vec); }
[[gnu::always_inline]] nce uint8x8_t reverse_32bit(uint8x8_t vec) { return vrev32_u8(vec); }
[[gnu::always_inline]] nce uint8x8_t reverse_16bit(uint8x8_t vec) { return vrev16_u8(vec); }
[[gnu::always_inline]] nce uint8x8x2_t zip(uint8x8_t a, uint8x8_t b) { return vzip_u8(a, b); }
[[gnu::always_inline]] nce uint8x8x2_t unzip(uint8x8_t a, uint8x8_t b) { return vuzp_u8(a, b); }
[[gnu::always_inline]] nce uint8x8x2_t transpose(uint8x8_t a, uint8x8_t b) { return vtrn_u8(a, b); }
[[gnu::always_inline]] nce uint8x8_t table_lookup1(uint8x8_t a, uint8x8_t idx) { return vtbl1_u8(a, idx); }
[[gnu::always_inline]] nce uint8x8_t table_lookup_extension1(uint8x8_t a, uint8x8_t b, uint8x8_t idx) { return vtbx1_u8(a, b, idx); }
[[gnu::always_inline]] nce uint8x8_t table_lookup_extension2(uint8x8_t a, uint8x8x2_t b, uint8x8_t idx) { return vtbx2_u8(a, b, idx); }
[[gnu::always_inline]] nce uint8x8_t table_lookup_extension3(uint8x8_t a, uint8x8x3_t b, uint8x8_t idx) { return vtbx3_u8(a, b, idx); }
[[gnu::always_inline]] nce uint8x8_t table_lookup_extension4(uint8x8_t a, uint8x8x4_t b, uint8x8_t idx) { return vtbx4_u8(a, b, idx); }
[[gnu::always_inline]] nce uint8x16_t add(uint8x16_t a, uint8x16_t b) { return vaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_halve(uint8x16_t a, uint8x16_t b) { return vhaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_halve_round(uint8x16_t a, uint8x16_t b) { return vrhaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t add_saturate(uint8x16_t a, uint8x16_t b) { return vqaddq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t multiply(uint8x16_t a, uint8x16_t b) { return vmulq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t multiply_add(uint8x16_t a, uint8x16_t b, uint8x16_t c) { return vmlaq_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x16_t multiply_subtract(uint8x16_t a, uint8x16_t b, uint8x16_t c) { return vmlsq_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x16_t subtract(uint8x16_t a, uint8x16_t b) { return vsubq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_high(uint8x16_t a, uint8x16_t b) { return vhsubq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_saturate(uint8x16_t a, uint8x16_t b) { return vqsubq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_abs(uint8x16_t a, uint8x16_t b) { return vabdq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t subtract_abs_add(uint8x16_t a, uint8x16_t b, uint8x16_t c) { return vabaq_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x16_t max(uint8x16_t a, uint8x16_t b) { return vmaxq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t min(uint8x16_t a, uint8x16_t b) { return vminq_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_pairwise_long(uint8x16_t a) { return vpaddlq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t equal(uint8x16_t a, uint8x16_t b) { return vceqq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t greater_than_or_equal(uint8x16_t a, uint8x16_t b) { return vcgeq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t less_than_or_equal(uint8x16_t a, uint8x16_t b) { return vcleq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t greater_than(uint8x16_t a, uint8x16_t b) { return vcgtq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t less_than(uint8x16_t a, uint8x16_t b) { return vcltq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t and_test_nonzero(uint8x16_t a, uint8x16_t b) { return vtstq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t a, int8x16_t b) { return vshlq_u8(a, b); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_left(uint8x16_t a) { return vshlq_n_u8(a, n); }
[[gnu::always_inline]] nce uint8x16_t shift_left_saturate(uint8x16_t a, int8x16_t b) { return vqshlq_u8(a, b); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_left_saturate(uint8x16_t a) { return vqshlq_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_left_insert(uint8x16_t a, uint8x16_t b) { return vsliq_n_u8(a, b, n); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round(uint8x16_t a, int8x16_t b) { return vrshlq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t shift_left_round_saturate(uint8x16_t a, int8x16_t b) { return vqrshlq_u8(a, b); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right(uint8x16_t a) { return vshrq_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_round(uint8x16_t a) { return vrshrq_n_u8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_accumulate(uint8x16_t a, uint8x16_t b) { return vsraq_n_u8(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_accumulate_round(uint8x16_t a, uint8x16_t b) { return vrsraq_n_u8(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_right_insert(uint8x16_t a, uint8x16_t b) { return vsriq_n_u8(a, b, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint8x16_t a) { return vreinterpretq_s8_u8(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_s16_u8(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint8x16_t a) { return vreinterpretq_s32_u8(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint8x16_t a) { return vreinterpretq_f32_u8(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_u16_u8(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(uint8x16_t a) { return vreinterpretq_u32_u8(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(uint8x16_t a) { return vreinterpretq_p8_u8(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_p16_u8(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(uint8x16_t a) { return vreinterpretq_u64_u8(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint8x16_t a) { return vreinterpretq_s64_u8(a); }
[[gnu::always_inline]] nce uint8x16_t not_bitwise(uint8x16_t a) { return vmvnq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t and_bitwise(uint8x16_t a, uint8x16_t b) { return vandq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t or_bitwise(uint8x16_t a, uint8x16_t b) { return vorrq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t xor_bitwise(uint8x16_t a, uint8x16_t b) { return veorq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t or_not_bitwise(uint8x16_t a, uint8x16_t b) { return vornq_u8(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce int8x16_t count_leading_sign_bits(uint8x16_t a) { return vclsq_u8(a); }
#endif
[[gnu::always_inline]] nce uint8x16_t count_leading_zero_bits(uint8x16_t a) { return vclzq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t count_active_bits(uint8x16_t a) { return vcntq_u8(a); }
[[gnu::always_inline]] nce uint8x16_t clear_bitwise(uint8x16_t a, uint8x16_t b) { return vbicq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16_t select_bitwise(uint8x16_t a, uint8x16_t b, uint8x16_t c) { return vbslq_u8(a, b, c); }
[[gnu::always_inline]] nce uint8x8_t get_high(uint8x16_t a) { return vget_high_u8(a); }
[[gnu::always_inline]] nce uint8x8_t get_low(uint8x16_t a) { return vget_low_u8(a); }
template <int lane>[[gnu::always_inline]] nce uint8_t get(uint8x16_t v) { return vgetq_lane_u8(v, lane); }
template <int n>[[gnu::always_inline]] nce uint8x16_t extract(uint8x16_t a, uint8x16_t b) { return vextq_u8(a, b, n); }
[[gnu::always_inline]] nce uint8x16_t reverse_64bit(uint8x16_t vec) { return vrev64q_u8(vec); }
[[gnu::always_inline]] nce uint8x16_t reverse_32bit(uint8x16_t vec) { return vrev32q_u8(vec); }
[[gnu::always_inline]] nce uint8x16_t reverse_16bit(uint8x16_t vec) { return vrev16q_u8(vec); }
[[gnu::always_inline]] nce uint8x16x2_t zip(uint8x16_t a, uint8x16_t b) { return vzipq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16x2_t unzip(uint8x16_t a, uint8x16_t b) { return vuzpq_u8(a, b); }
[[gnu::always_inline]] nce uint8x16x2_t transpose(uint8x16_t a, uint8x16_t b) { return vtrnq_u8(a, b); }
[[gnu::always_inline]] nce int8x16_t select_bitwise(uint8x16_t a, int8x16_t b, int8x16_t c) { return vbslq_s8(a, b, c); }
[[gnu::always_inline]] nce poly8x16_t select_bitwise(uint8x16_t a, poly8x16_t b, poly8x16_t c) { return vbslq_p8(a, b, c); }
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
[[gnu::always_inline]] nce int8x8_t subtract_high(int8x8_t a, int8x8_t b) { return vhsub_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract_saturate(int8x8_t a, int8x8_t b) { return vqsub_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract_abs(int8x8_t a, int8x8_t b) { return vabd_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_abs_long(int8x8_t a, int8x8_t b) { return vabdl_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract_abs_add(int8x8_t a, int8x8_t b, int8x8_t c) { return vaba_s8(a, b, c); }
[[gnu::always_inline]] nce int8x8_t abs(int8x8_t a) { return vabs_s8(a); }
[[gnu::always_inline]] nce int8x8_t abs_saturate(int8x8_t a) { return vqabs_s8(a); }
[[gnu::always_inline]] nce int8x8_t max(int8x8_t a, int8x8_t b) { return vmax_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t min(int8x8_t a, int8x8_t b) { return vmin_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t add_pairwise(int8x8_t a, int8x8_t b) { return vpadd_s8(a, b); }
[[gnu::always_inline]] nce int16x4_t add_pairwise_long(int8x8_t a) { return vpaddl_s8(a); }
[[gnu::always_inline]] nce int8x8_t max_pairwise(int8x8_t a, int8x8_t b) { return vpmax_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t min_pairwise(int8x8_t a, int8x8_t b) { return vpmin_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t equal(int8x8_t a, int8x8_t b) { return vceq_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t greater_than_or_equal(int8x8_t a, int8x8_t b) { return vcge_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t less_than_or_equal(int8x8_t a, int8x8_t b) { return vcle_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t greater_than(int8x8_t a, int8x8_t b) { return vcgt_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t less_than(int8x8_t a, int8x8_t b) { return vclt_s8(a, b); }
[[gnu::always_inline]] nce uint8x8_t and_test_nonzero(int8x8_t a, int8x8_t b) { return vtst_s8(a, b); }
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
[[gnu::always_inline]] nce int8x8_t not_bitwise(int8x8_t a) { return vmvn_s8(a); }
[[gnu::always_inline]] nce int8x8_t and_bitwise(int8x8_t a, int8x8_t b) { return vand_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t or_bitwise(int8x8_t a, int8x8_t b) { return vorr_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t xor_bitwise(int8x8_t a, int8x8_t b) { return veor_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t or_not_bitwise(int8x8_t a, int8x8_t b) { return vorn_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t count_leading_sign_bits(int8x8_t a) { return vcls_s8(a); }
[[gnu::always_inline]] nce int8x8_t count_leading_zero_bits(int8x8_t a) { return vclz_s8(a); }
[[gnu::always_inline]] nce int8x8_t count_active_bits(int8x8_t a) { return vcnt_s8(a); }
[[gnu::always_inline]] nce int8x8_t clear_bitwise(int8x8_t a, int8x8_t b) { return vbic_s8(a, b); }
template <int lane>[[gnu::always_inline]] nce int8x8_t duplicate_element(int8x8_t vec) { return vdup_lane_s8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16_t duplicate_element(int8x8_t vec) { return vdupq_lane_s8(vec, lane); }
[[gnu::always_inline]] nce int8x16_t combine(int8x8_t low, int8x8_t high) { return vcombine_s8(low, high); }
template <int lane>[[gnu::always_inline]] nce int8_t get(int8x8_t v) { return vget_lane_s8(v, lane); }
template <int n>[[gnu::always_inline]] nce int8x8_t extract(int8x8_t a, int8x8_t b) { return vext_s8(a, b, n); }
[[gnu::always_inline]] nce int8x8_t reverse_64bit(int8x8_t vec) { return vrev64_s8(vec); }
[[gnu::always_inline]] nce int8x8_t reverse_32bit(int8x8_t vec) { return vrev32_s8(vec); }
[[gnu::always_inline]] nce int8x8_t reverse_16bit(int8x8_t vec) { return vrev16_s8(vec); }
[[gnu::always_inline]] nce int8x8x2_t zip(int8x8_t a, int8x8_t b) { return vzip_s8(a, b); }
[[gnu::always_inline]] nce int8x8x2_t unzip(int8x8_t a, int8x8_t b) { return vuzp_s8(a, b); }
[[gnu::always_inline]] nce int8x8x2_t transpose(int8x8_t a, int8x8_t b) { return vtrn_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t table_lookup1(int8x8_t a, int8x8_t idx) { return vtbl1_s8(a, idx); }
[[gnu::always_inline]] nce int8x8_t table_lookup_extension1(int8x8_t a, int8x8_t b, int8x8_t idx) { return vtbx1_s8(a, b, idx); }
[[gnu::always_inline]] nce int8x8_t table_lookup_extension2(int8x8_t a, int8x8x2_t b, int8x8_t idx) { return vtbx2_s8(a, b, idx); }
[[gnu::always_inline]] nce int8x8_t table_lookup_extension3(int8x8_t a, int8x8x3_t b, int8x8_t idx) { return vtbx3_s8(a, b, idx); }
[[gnu::always_inline]] nce int8x8_t table_lookup_extension4(int8x8_t a, int8x8x4_t b, int8x8_t idx) { return vtbx4_s8(a, b, idx); }
[[gnu::always_inline]] nce int8x16_t add(int8x16_t a, int8x16_t b) { return vaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_halve(int8x16_t a, int8x16_t b) { return vhaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_halve_round(int8x16_t a, int8x16_t b) { return vrhaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t add_saturate(int8x16_t a, int8x16_t b) { return vqaddq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply(int8x16_t a, int8x16_t b) { return vmulq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply_add(int8x16_t a, int8x16_t b, int8x16_t c) { return vmlaq_s8(a, b, c); }
[[gnu::always_inline]] nce int8x16_t multiply_subtract(int8x16_t a, int8x16_t b, int8x16_t c) { return vmlsq_s8(a, b, c); }
[[gnu::always_inline]] nce int8x16_t subtract(int8x16_t a, int8x16_t b) { return vsubq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_high(int8x16_t a, int8x16_t b) { return vhsubq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_saturate(int8x16_t a, int8x16_t b) { return vqsubq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_abs(int8x16_t a, int8x16_t b) { return vabdq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t subtract_abs_add(int8x16_t a, int8x16_t b, int8x16_t c) { return vabaq_s8(a, b, c); }
[[gnu::always_inline]] nce int8x16_t abs(int8x16_t a) { return vabsq_s8(a); }
[[gnu::always_inline]] nce int8x16_t abs_saturate(int8x16_t a) { return vqabsq_s8(a); }
[[gnu::always_inline]] nce int8x16_t max(int8x16_t a, int8x16_t b) { return vmaxq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t min(int8x16_t a, int8x16_t b) { return vminq_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t add_pairwise_long(int8x16_t a) { return vpaddlq_s8(a); }
[[gnu::always_inline]] nce uint8x16_t equal(int8x16_t a, int8x16_t b) { return vceqq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t greater_than_or_equal(int8x16_t a, int8x16_t b) { return vcgeq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t less_than_or_equal(int8x16_t a, int8x16_t b) { return vcleq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t greater_than(int8x16_t a, int8x16_t b) { return vcgtq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t less_than(int8x16_t a, int8x16_t b) { return vcltq_s8(a, b); }
[[gnu::always_inline]] nce uint8x16_t and_test_nonzero(int8x16_t a, int8x16_t b) { return vtstq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t a, int8x16_t b) { return vshlq_s8(a, b); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_left(int8x16_t a) { return vshlq_n_s8(a, n); }
[[gnu::always_inline]] nce int8x16_t shift_left_saturate(int8x16_t a, int8x16_t b) { return vqshlq_s8(a, b); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_left_saturate(int8x16_t a) { return vqshlq_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x16_t shift_left_unsigned_saturate(int8x16_t a) { return vqshluq_n_s8(a, n); }
[[gnu::always_inline]] nce int8x16_t shift_left_round(int8x16_t a, int8x16_t b) { return vrshlq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t shift_left_round_saturate(int8x16_t a, int8x16_t b) { return vqrshlq_s8(a, b); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_left_insert(int8x16_t a, int8x16_t b) { return vsliq_n_s8(a, b, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right(int8x16_t a) { return vshrq_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_round(int8x16_t a) { return vrshrq_n_s8(a, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_accumulate(int8x16_t a, int8x16_t b) { return vsraq_n_s8(a, b, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_accumulate_round(int8x16_t a, int8x16_t b) { return vrsraq_n_s8(a, b, n); }
template <int n>[[gnu::always_inline]] nce int8x16_t shift_right_insert(int8x16_t a, int8x16_t b) { return vsriq_n_s8(a, b, n); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(int8x16_t a) { return vreinterpretq_s16_s8(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(int8x16_t a) { return vreinterpretq_s32_s8(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int8x16_t a) { return vreinterpretq_f32_s8(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int8x16_t a) { return vreinterpretq_u8_s8(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int8x16_t a) { return vreinterpretq_u16_s8(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int8x16_t a) { return vreinterpretq_u32_s8(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(int8x16_t a) { return vreinterpretq_p8_s8(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(int8x16_t a) { return vreinterpretq_p16_s8(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int8x16_t a) { return vreinterpretq_u64_s8(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(int8x16_t a) { return vreinterpretq_s64_s8(a); }
[[gnu::always_inline]] nce int8x16_t negate(int8x16_t a) { return vnegq_s8(a); }
[[gnu::always_inline]] nce int8x16_t negate_saturate(int8x16_t a) { return vqnegq_s8(a); }
[[gnu::always_inline]] nce int8x16_t not_bitwise(int8x16_t a) { return vmvnq_s8(a); }
[[gnu::always_inline]] nce int8x16_t and_bitwise(int8x16_t a, int8x16_t b) { return vandq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t or_bitwise(int8x16_t a, int8x16_t b) { return vorrq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t xor_bitwise(int8x16_t a, int8x16_t b) { return veorq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t or_not_bitwise(int8x16_t a, int8x16_t b) { return vornq_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t count_leading_sign_bits(int8x16_t a) { return vclsq_s8(a); }
[[gnu::always_inline]] nce int8x16_t count_leading_zero_bits(int8x16_t a) { return vclzq_s8(a); }
[[gnu::always_inline]] nce int8x16_t count_active_bits(int8x16_t a) { return vcntq_s8(a); }
[[gnu::always_inline]] nce int8x16_t clear_bitwise(int8x16_t a, int8x16_t b) { return vbicq_s8(a, b); }
[[gnu::always_inline]] nce int8x8_t get_high(int8x16_t a) { return vget_high_s8(a); }
[[gnu::always_inline]] nce int8x8_t get_low(int8x16_t a) { return vget_low_s8(a); }
template <int lane>[[gnu::always_inline]] nce int8_t get(int8x16_t v) { return vgetq_lane_s8(v, lane); }
template <int n>[[gnu::always_inline]] nce int8x16_t extract(int8x16_t a, int8x16_t b) { return vextq_s8(a, b, n); }
[[gnu::always_inline]] nce int8x16_t reverse_64bit(int8x16_t vec) { return vrev64q_s8(vec); }
[[gnu::always_inline]] nce int8x16_t reverse_32bit(int8x16_t vec) { return vrev32q_s8(vec); }
[[gnu::always_inline]] nce int8x16_t reverse_16bit(int8x16_t vec) { return vrev16q_s8(vec); }
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
[[gnu::always_inline]] nce uint16x4_t subtract_high(uint16x4_t a, uint16x4_t b) { return vhsub_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract_saturate(uint16x4_t a, uint16x4_t b) { return vqsub_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract_abs(uint16x4_t a, uint16x4_t b) { return vabd_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_abs_long(uint16x4_t a, uint16x4_t b) { return vabdl_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract_abs_add(uint16x4_t a, uint16x4_t b, uint16x4_t c) { return vaba_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t max(uint16x4_t a, uint16x4_t b) { return vmax_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t min(uint16x4_t a, uint16x4_t b) { return vmin_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t add_pairwise(uint16x4_t a, uint16x4_t b) { return vpadd_u16(a, b); }
[[gnu::always_inline]] nce uint32x2_t add_pairwise_long(uint16x4_t a) { return vpaddl_u16(a); }
[[gnu::always_inline]] nce uint16x4_t add_pairwise_accumulate_long(uint16x4_t a, uint8x8_t b) { return vpadal_u8(a, b); }
[[gnu::always_inline]] nce uint16x4_t max_pairwise(uint16x4_t a, uint16x4_t b) { return vpmax_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t min_pairwise(uint16x4_t a, uint16x4_t b) { return vpmin_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t equal(uint16x4_t a, uint16x4_t b) { return vceq_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t greater_than_or_equal(uint16x4_t a, uint16x4_t b) { return vcge_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t less_than_or_equal(uint16x4_t a, uint16x4_t b) { return vcle_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t greater_than(uint16x4_t a, uint16x4_t b) { return vcgt_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t less_than(uint16x4_t a, uint16x4_t b) { return vclt_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t and_test_nonzero(uint16x4_t a, uint16x4_t b) { return vtst_u16(a, b); }
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
template <int lane>[[gnu::always_inline]] nce uint16x4_t multiply_add(uint16x4_t a, uint16x4_t b, uint16x4_t v) { return vmla_lane_u16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t multiply_subtract(uint16x4_t a, uint16x4_t b, uint16x4_t v) { return vmls_lane_u16(a, b, v, lane); }
[[gnu::always_inline]] nce uint16x4_t multiply_add(uint16x4_t a, uint16x4_t b, uint16_t c) { return vmla_n_u16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t multiply(uint16x4_t a, uint16x4_t v) { return vmul_lane_u16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_long(uint16x4_t a, uint16x4_t v) { return vmull_lane_u16(a, v, lane); }
[[gnu::always_inline]] nce uint16x4_t multiply_subtract(uint16x4_t a, uint16x4_t b, uint16_t c) { return vmls_n_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t not_bitwise(uint16x4_t a) { return vmvn_u16(a); }
[[gnu::always_inline]] nce uint16x4_t and_bitwise(uint16x4_t a, uint16x4_t b) { return vand_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t or_bitwise(uint16x4_t a, uint16x4_t b) { return vorr_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t xor_bitwise(uint16x4_t a, uint16x4_t b) { return veor_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t or_not_bitwise(uint16x4_t a, uint16x4_t b) { return vorn_u16(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce int16x4_t count_leading_sign_bits(uint16x4_t a) { return vcls_u16(a); }
#endif
[[gnu::always_inline]] nce uint16x4_t count_leading_zero_bits(uint16x4_t a) { return vclz_u16(a); }
[[gnu::always_inline]] nce uint16x4_t clear_bitwise(uint16x4_t a, uint16x4_t b) { return vbic_u16(a, b); }
[[gnu::always_inline]] nce uint16x4_t select_bitwise(uint16x4_t a, uint16x4_t b, uint16x4_t c) { return vbsl_u16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t duplicate_element(uint16x4_t vec) { return vdup_lane_u16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t duplicate_element(uint16x4_t vec) { return vdupq_lane_u16(vec, lane); }
[[gnu::always_inline]] nce uint16x8_t combine(uint16x4_t low, uint16x4_t high) { return vcombine_u16(low, high); }
template <int lane>[[gnu::always_inline]] nce uint16_t get(uint16x4_t v) { return vget_lane_u16(v, lane); }
template <int n>[[gnu::always_inline]] nce uint16x4_t extract(uint16x4_t a, uint16x4_t b) { return vext_u16(a, b, n); }
[[gnu::always_inline]] nce uint16x4_t reverse_64bit(uint16x4_t vec) { return vrev64_u16(vec); }
[[gnu::always_inline]] nce uint16x4_t reverse_32bit(uint16x4_t vec) { return vrev32_u16(vec); }
[[gnu::always_inline]] nce uint16x4x2_t zip(uint16x4_t a, uint16x4_t b) { return vzip_u16(a, b); }
[[gnu::always_inline]] nce uint16x4x2_t unzip(uint16x4_t a, uint16x4_t b) { return vuzp_u16(a, b); }
[[gnu::always_inline]] nce uint16x4x2_t transpose(uint16x4_t a, uint16x4_t b) { return vtrn_u16(a, b); }
[[gnu::always_inline]] nce int16x4_t select_bitwise(uint16x4_t a, int16x4_t b, int16x4_t c) { return vbsl_s16(a, b, c); }
[[gnu::always_inline]] nce poly16x4_t select_bitwise(uint16x4_t a, poly16x4_t b, poly16x4_t c) { return vbsl_p16(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t multiply(uint16x4_t a, uint16_t b) { return vmul_n_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_long(uint16x4_t a, uint16_t b) { return vmull_n_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add(uint16x8_t a, uint8x8_t b) { return vaddw_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply_add_long(uint16x8_t a, uint8x8_t b, uint8x8_t c) { return vmlal_u8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t multiply_subtract_long(uint16x8_t a, uint8x8_t b, uint8x8_t c) { return vmlsl_u8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t subtract(uint16x8_t a, uint8x8_t b) { return vsubw_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_abs_add(uint16x8_t a, uint8x8_t b, uint8x8_t c) { return vabal_u8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t add(uint16x8_t a, uint16x8_t b) { return vaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_halve(uint16x8_t a, uint16x8_t b) { return vhaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_halve_round(uint16x8_t a, uint16x8_t b) { return vrhaddq_u16(a, b); }
[[gnu::always_inline]] nce uint8x8_t add_narrow_high(uint16x8_t a, uint16x8_t b) { return vaddhn_u16(a, b); }
[[gnu::always_inline]] nce uint8x8_t add_round_narrow_high(uint16x8_t a, uint16x8_t b) { return vraddhn_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t add_saturate(uint16x8_t a, uint16x8_t b) { return vqaddq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t a, uint16x8_t b) { return vmulq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t multiply_add(uint16x8_t a, uint16x8_t b, uint16x8_t c) { return vmlaq_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t multiply_subtract(uint16x8_t a, uint16x8_t b, uint16x8_t c) { return vmlsq_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t subtract(uint16x8_t a, uint16x8_t b) { return vsubq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_high(uint16x8_t a, uint16x8_t b) { return vhsubq_u16(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract_narrow_high(uint16x8_t a, uint16x8_t b) { return vsubhn_u16(a, b); }
[[gnu::always_inline]] nce uint8x8_t subtract_round_narrow_high(uint16x8_t a, uint16x8_t b) { return vrsubhn_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_saturate(uint16x8_t a, uint16x8_t b) { return vqsubq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_abs(uint16x8_t a, uint16x8_t b) { return vabdq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t subtract_abs_add(uint16x8_t a, uint16x8_t b, uint16x8_t c) { return vabaq_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t max(uint16x8_t a, uint16x8_t b) { return vmaxq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t min(uint16x8_t a, uint16x8_t b) { return vminq_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_pairwise_long(uint16x8_t a) { return vpaddlq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t add_pairwise_accumulate_long(uint16x8_t a, uint8x16_t b) { return vpadalq_u8(a, b); }
[[gnu::always_inline]] nce uint16x8_t equal(uint16x8_t a, uint16x8_t b) { return vceqq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t greater_than_or_equal(uint16x8_t a, uint16x8_t b) { return vcgeq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t less_than_or_equal(uint16x8_t a, uint16x8_t b) { return vcleq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t greater_than(uint16x8_t a, uint16x8_t b) { return vcgtq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t less_than(uint16x8_t a, uint16x8_t b) { return vcltq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t and_test_nonzero(uint16x8_t a, uint16x8_t b) { return vtstq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t shift_left_saturate(uint16x8_t a, int16x8_t b) { return vqshlq_u16(a, b); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_left_saturate(uint16x8_t a) { return vqshlq_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_left_insert(uint16x8_t a, uint16x8_t b) { return vsliq_n_u16(a, b, n); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round(uint16x8_t a, int16x8_t b) { return vrshlq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t shift_left_round_saturate(uint16x8_t a, int16x8_t b) { return vqrshlq_u16(a, b); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right(uint16x8_t a) { return vshrq_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_round(uint16x8_t a) { return vrshrq_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_accumulate(uint16x8_t a, uint16x8_t b) { return vsraq_n_u16(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_accumulate_round(uint16x8_t a, uint16x8_t b) { return vrsraq_n_u16(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_narrow(uint16x8_t a) { return vshrn_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t qshrn(uint16x8_t a) { return vqshrn_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_saturate_narrow(uint16x8_t a) { return vqrshrn_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_round_saturate_narrow(uint16x8_t a) { return vrshrn_n_u16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_right_insert(uint16x8_t a, uint16x8_t b) { return vsriq_n_u16(a, b, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint16x8_t a) { return vreinterpretq_s8_u16(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint16x8_t a) { return vreinterpretq_s16_u16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint16x8_t a) { return vreinterpretq_s32_u16(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint16x8_t a) { return vreinterpretq_f32_u16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(uint16x8_t a) { return vreinterpretq_u8_u16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(uint16x8_t a) { return vreinterpretq_u32_u16(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(uint16x8_t a) { return vreinterpretq_p8_u16(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(uint16x8_t a) { return vreinterpretq_p16_u16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(uint16x8_t a) { return vreinterpretq_u64_u16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint16x8_t a) { return vreinterpretq_s64_u16(a); }
[[gnu::always_inline]] nce uint8x8_t move_narrow(uint16x8_t a) { return vmovn_u16(a); }
[[gnu::always_inline]] nce uint8x8_t move_saturate_narrow(uint16x8_t a) { return vqmovn_u16(a); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t multiply_add(uint16x8_t a, uint16x8_t b, uint16x4_t v) { return vmlaq_lane_u16(a, b, v, lane); }
[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t a, int16x8_t b) { return vshlq_u16(a, b); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_left(uint16x8_t a) { return vshlq_n_u16(a, n); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t a, uint16x4_t v) { return vmulq_lane_u16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t multiply_subtract(uint16x8_t a, uint16x8_t b, uint16x4_t v) { return vmlsq_lane_u16(a, b, v, lane); }
[[gnu::always_inline]] nce uint16x8_t multiply_add(uint16x8_t a, uint16x8_t b, uint16_t c) { return vmlaq_n_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t multiply_subtract(uint16x8_t a, uint16x8_t b, uint16_t c) { return vmlsq_n_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t not_bitwise(uint16x8_t a) { return vmvnq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t and_bitwise(uint16x8_t a, uint16x8_t b) { return vandq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t or_bitwise(uint16x8_t a, uint16x8_t b) { return vorrq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t xor_bitwise(uint16x8_t a, uint16x8_t b) { return veorq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t or_not_bitwise(uint16x8_t a, uint16x8_t b) { return vornq_u16(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce int16x8_t count_leading_sign_bits(uint16x8_t a) { return vclsq_u16(a); }
#endif
[[gnu::always_inline]] nce uint16x8_t count_leading_zero_bits(uint16x8_t a) { return vclzq_u16(a); }
[[gnu::always_inline]] nce uint16x8_t clear_bitwise(uint16x8_t a, uint16x8_t b) { return vbicq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8_t select_bitwise(uint16x8_t a, uint16x8_t b, uint16x8_t c) { return vbslq_u16(a, b, c); }
[[gnu::always_inline]] nce uint16x4_t get_high(uint16x8_t a) { return vget_high_u16(a); }
[[gnu::always_inline]] nce uint16x4_t get_low(uint16x8_t a) { return vget_low_u16(a); }
template <int lane>[[gnu::always_inline]] nce uint16_t get(uint16x8_t v) { return vgetq_lane_u16(v, lane); }
template <int n>[[gnu::always_inline]] nce uint16x8_t extract(uint16x8_t a, uint16x8_t b) { return vextq_u16(a, b, n); }
[[gnu::always_inline]] nce uint16x8_t reverse_64bit(uint16x8_t vec) { return vrev64q_u16(vec); }
[[gnu::always_inline]] nce uint16x8_t reverse_32bit(uint16x8_t vec) { return vrev32q_u16(vec); }
[[gnu::always_inline]] nce uint16x8x2_t zip(uint16x8_t a, uint16x8_t b) { return vzipq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8x2_t unzip(uint16x8_t a, uint16x8_t b) { return vuzpq_u16(a, b); }
[[gnu::always_inline]] nce uint16x8x2_t transpose(uint16x8_t a, uint16x8_t b) { return vtrnq_u16(a, b); }
[[gnu::always_inline]] nce int16x8_t select_bitwise(uint16x8_t a, int16x8_t b, int16x8_t c) { return vbslq_s16(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t multiply(uint16x8_t a, uint16_t b) { return vmulq_n_u16(a, b); }
[[gnu::always_inline]] nce poly16x8_t select_bitwise(uint16x8_t a, poly16x8_t b, poly16x8_t c) { return vbslq_p16(a, b, c); }
[[gnu::always_inline]] nce int16x4_t add_pairwise_accumulate_long(int16x4_t a, int8x8_t b) { return vpadal_s8(a, b); }
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
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long(int16x4_t a, int16x4_t v) { return vqdmull_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_double_saturate_high(int16x4_t a, int16x4_t v) { return vqdmulh_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_double_round_saturate_high(int16x4_t a, int16x4_t v) { return vqrdmulh_lane_s16(a, v, lane); }
[[gnu::always_inline]] nce int16x4_t subtract(int16x4_t a, int16x4_t b) { return vsub_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_long(int16x4_t a, int16x4_t b) { return vsubl_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_high(int16x4_t a, int16x4_t b) { return vhsub_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_saturate(int16x4_t a, int16x4_t b) { return vqsub_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_abs(int16x4_t a, int16x4_t b) { return vabd_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_abs_long(int16x4_t a, int16x4_t b) { return vabdl_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_abs_add(int16x4_t a, int16x4_t b, int16x4_t c) { return vaba_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_long(int16x4_t a, int16_t b) { return vqdmull_n_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t multiply_double_saturate_high(int16x4_t a, int16_t b) { return vqdmulh_n_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t multiply_double_round_saturate_high(int16x4_t a, int16_t b) { return vqrdmulh_n_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t abs(int16x4_t a) { return vabs_s16(a); }
[[gnu::always_inline]] nce int16x4_t abs_saturate(int16x4_t a) { return vqabs_s16(a); }
[[gnu::always_inline]] nce int16x4_t max(int16x4_t a, int16x4_t b) { return vmax_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t min(int16x4_t a, int16x4_t b) { return vmin_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t add_pairwise(int16x4_t a, int16x4_t b) { return vpadd_s16(a, b); }
[[gnu::always_inline]] nce int32x2_t add_pairwise_long(int16x4_t a) { return vpaddl_s16(a); }
[[gnu::always_inline]] nce int16x4_t max_pairwise(int16x4_t a, int16x4_t b) { return vpmax_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t min_pairwise(int16x4_t a, int16x4_t b) { return vpmin_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t equal(int16x4_t a, int16x4_t b) { return vceq_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t greater_than_or_equal(int16x4_t a, int16x4_t b) { return vcge_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t less_than_or_equal(int16x4_t a, int16x4_t b) { return vcle_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t greater_than(int16x4_t a, int16x4_t b) { return vcgt_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t less_than(int16x4_t a, int16x4_t b) { return vclt_s16(a, b); }
[[gnu::always_inline]] nce uint16x4_t and_test_nonzero(int16x4_t a, int16x4_t b) { return vtst_s16(a, b); }
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
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_add(int16x4_t a, int16x4_t b, int16x4_t v) { return vmla_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply_subtract(int16x4_t a, int16x4_t b, int16x4_t v) { return vmls_lane_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int16x4_t multiply_add(int16x4_t a, int16x4_t b, int16_t c) { return vmla_n_s16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int16x4_t multiply(int16x4_t a, int16x4_t v) { return vmul_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_long(int16x4_t a, int16x4_t v) { return vmull_lane_s16(a, v, lane); }
[[gnu::always_inline]] nce int16x4_t multiply_subtract(int16x4_t a, int16x4_t b, int16_t c) { return vmls_n_s16(a, b, c); }
[[gnu::always_inline]] nce int16x4_t negate(int16x4_t a) { return vneg_s16(a); }
[[gnu::always_inline]] nce int16x4_t negate_saturate(int16x4_t a) { return vqneg_s16(a); }
[[gnu::always_inline]] nce int16x4_t not_bitwise(int16x4_t a) { return vmvn_s16(a); }
[[gnu::always_inline]] nce int16x4_t and_bitwise(int16x4_t a, int16x4_t b) { return vand_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t or_bitwise(int16x4_t a, int16x4_t b) { return vorr_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t xor_bitwise(int16x4_t a, int16x4_t b) { return veor_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t or_not_bitwise(int16x4_t a, int16x4_t b) { return vorn_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t count_leading_sign_bits(int16x4_t a) { return vcls_s16(a); }
[[gnu::always_inline]] nce int16x4_t count_leading_zero_bits(int16x4_t a) { return vclz_s16(a); }
[[gnu::always_inline]] nce int16x4_t clear_bitwise(int16x4_t a, int16x4_t b) { return vbic_s16(a, b); }
template <int lane>[[gnu::always_inline]] nce int16x4_t duplicate_element(int16x4_t vec) { return vdup_lane_s16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t duplicate_element(int16x4_t vec) { return vdupq_lane_s16(vec, lane); }
[[gnu::always_inline]] nce int16x8_t combine(int16x4_t low, int16x4_t high) { return vcombine_s16(low, high); }
template <int lane>[[gnu::always_inline]] nce int16_t get(int16x4_t v) { return vget_lane_s16(v, lane); }
template <int n>[[gnu::always_inline]] nce int16x4_t extract(int16x4_t a, int16x4_t b) { return vext_s16(a, b, n); }
[[gnu::always_inline]] nce int16x4_t reverse_64bit(int16x4_t vec) { return vrev64_s16(vec); }
[[gnu::always_inline]] nce int16x4_t reverse_32bit(int16x4_t vec) { return vrev32_s16(vec); }
[[gnu::always_inline]] nce int16x4x2_t zip(int16x4_t a, int16x4_t b) { return vzip_s16(a, b); }
[[gnu::always_inline]] nce int16x4x2_t unzip(int16x4_t a, int16x4_t b) { return vuzp_s16(a, b); }
[[gnu::always_inline]] nce int16x4x2_t transpose(int16x4_t a, int16x4_t b) { return vtrn_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t multiply(int16x4_t a, int16_t b) { return vmul_n_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_long(int16x4_t a, int16_t b) { return vmull_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add(int16x8_t a, int8x8_t b) { return vaddw_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_add_long(int16x8_t a, int8x8_t b, int8x8_t c) { return vmlal_s8(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract_long(int16x8_t a, int8x8_t b, int8x8_t c) { return vmlsl_s8(a, b, c); }
[[gnu::always_inline]] nce int16x8_t subtract(int16x8_t a, int8x8_t b) { return vsubw_s8(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_abs_add(int16x8_t a, int8x8_t b, int8x8_t c) { return vabal_s8(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high(int16x8_t a, int16x4_t v) { return vqdmulhq_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high(int16x8_t a, int16x4_t v) { return vqrdmulhq_lane_s16(a, v, lane); }
[[gnu::always_inline]] nce int16x8_t add(int16x8_t a, int16x8_t b) { return vaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add_halve(int16x8_t a, int16x8_t b) { return vhaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add_halve_round(int16x8_t a, int16x8_t b) { return vrhaddq_s16(a, b); }
[[gnu::always_inline]] nce int8x8_t add_narrow_high(int16x8_t a, int16x8_t b) { return vaddhn_s16(a, b); }
[[gnu::always_inline]] nce int8x8_t add_round_narrow_high(int16x8_t a, int16x8_t b) { return vraddhn_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t add_saturate(int16x8_t a, int16x8_t b) { return vqaddq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t a, int16x8_t b) { return vmulq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_add(int16x8_t a, int16x8_t b, int16x8_t c) { return vmlaq_s16(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract(int16x8_t a, int16x8_t b, int16x8_t c) { return vmlsq_s16(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high(int16x8_t a, int16x8_t b) { return vqdmulhq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high(int16x8_t a, int16x8_t b) { return vqrdmulhq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract(int16x8_t a, int16x8_t b) { return vsubq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_high(int16x8_t a, int16x8_t b) { return vhsubq_s16(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract_narrow_high(int16x8_t a, int16x8_t b) { return vsubhn_s16(a, b); }
[[gnu::always_inline]] nce int8x8_t subtract_round_narrow_high(int16x8_t a, int16x8_t b) { return vrsubhn_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_saturate(int16x8_t a, int16x8_t b) { return vqsubq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_abs(int16x8_t a, int16x8_t b) { return vabdq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t subtract_abs_add(int16x8_t a, int16x8_t b, int16x8_t c) { return vabaq_s16(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_double_saturate_high(int16x8_t a, int16_t b) { return vqdmulhq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply_double_round_saturate_high(int16x8_t a, int16_t b) { return vqrdmulhq_n_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t abs(int16x8_t a) { return vabsq_s16(a); }
[[gnu::always_inline]] nce int16x8_t abs_saturate(int16x8_t a) { return vqabsq_s16(a); }
[[gnu::always_inline]] nce int16x8_t max(int16x8_t a, int16x8_t b) { return vmaxq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t min(int16x8_t a, int16x8_t b) { return vminq_s16(a, b); }
[[gnu::always_inline]] nce int32x4_t add_pairwise_long(int16x8_t a) { return vpaddlq_s16(a); }
[[gnu::always_inline]] nce int16x8_t add_pairwise_accumulate_long(int16x8_t a, int8x16_t b) { return vpadalq_s8(a, b); }
[[gnu::always_inline]] nce uint16x8_t equal(int16x8_t a, int16x8_t b) { return vceqq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t greater_than_or_equal(int16x8_t a, int16x8_t b) { return vcgeq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t less_than_or_equal(int16x8_t a, int16x8_t b) { return vcleq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t greater_than(int16x8_t a, int16x8_t b) { return vcgtq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t less_than(int16x8_t a, int16x8_t b) { return vcltq_s16(a, b); }
[[gnu::always_inline]] nce uint16x8_t and_test_nonzero(int16x8_t a, int16x8_t b) { return vtstq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t a, int16x8_t b) { return vshlq_s16(a, b); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_left(int16x8_t a) { return vshlq_n_s16(a, n); }
[[gnu::always_inline]] nce int16x8_t shift_left_saturate(int16x8_t a, int16x8_t b) { return vqshlq_s16(a, b); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_left_saturate(int16x8_t a) { return vqshlq_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x8_t shift_left_unsigned_saturate(int16x8_t a) { return vqshluq_n_s16(a, n); }
[[gnu::always_inline]] nce int16x8_t shift_left_round(int16x8_t a, int16x8_t b) { return vrshlq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t shift_left_round_saturate(int16x8_t a, int16x8_t b) { return vqrshlq_s16(a, b); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_left_insert(int16x8_t a, int16x8_t b) { return vsliq_n_s16(a, b, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right(int16x8_t a) { return vshrq_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_round(int16x8_t a) { return vrshrq_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_accumulate(int16x8_t a, int16x8_t b) { return vsraq_n_s16(a, b, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_accumulate_round(int16x8_t a, int16x8_t b) { return vrsraq_n_s16(a, b, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_narrow(int16x8_t a) { return vshrn_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t qshrun(int16x8_t a) { return vqshrun_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t qshrn(int16x8_t a) { return vqshrn_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce uint8x8_t shift_right_unsigned_saturate_narrow(int16x8_t a) { return vqrshrun_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_saturate_narrow(int16x8_t a) { return vqrshrn_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int8x8_t shift_right_round_saturate_narrow(int16x8_t a) { return vrshrn_n_s16(a, n); }
template <int n>[[gnu::always_inline]] nce int16x8_t shift_right_insert(int16x8_t a, int16x8_t b) { return vsriq_n_s16(a, b, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(int16x8_t a) { return vreinterpretq_s8_s16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(int16x8_t a) { return vreinterpretq_s32_s16(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int16x8_t a) { return vreinterpretq_f32_s16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int16x8_t a) { return vreinterpretq_u8_s16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int16x8_t a) { return vreinterpretq_u16_s16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int16x8_t a) { return vreinterpretq_u32_s16(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(int16x8_t a) { return vreinterpretq_p8_s16(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(int16x8_t a) { return vreinterpretq_p16_s16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int16x8_t a) { return vreinterpretq_u64_s16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(int16x8_t a) { return vreinterpretq_s64_s16(a); }
[[gnu::always_inline]] nce int8x8_t move_narrow(int16x8_t a) { return vmovn_s16(a); }
[[gnu::always_inline]] nce int8x8_t move_saturate_narrow(int16x8_t a) { return vqmovn_s16(a); }
[[gnu::always_inline]] nce uint8x8_t move_unsigned_saturate_narrow(int16x8_t a) { return vqmovun_s16(a); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t a, int16x4_t v) { return vmulq_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_add(int16x8_t a, int16x8_t b, int16x4_t v) { return vmlaq_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t multiply_subtract(int16x8_t a, int16x8_t b, int16x4_t v) { return vmlsq_lane_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int16x8_t multiply_add(int16x8_t a, int16x8_t b, int16_t c) { return vmlaq_n_s16(a, b, c); }
[[gnu::always_inline]] nce int16x8_t multiply_subtract(int16x8_t a, int16x8_t b, int16_t c) { return vmlsq_n_s16(a, b, c); }
[[gnu::always_inline]] nce int16x8_t negate(int16x8_t a) { return vnegq_s16(a); }
[[gnu::always_inline]] nce int16x8_t negate_saturate(int16x8_t a) { return vqnegq_s16(a); }
[[gnu::always_inline]] nce int16x8_t not_bitwise(int16x8_t a) { return vmvnq_s16(a); }
[[gnu::always_inline]] nce int16x8_t and_bitwise(int16x8_t a, int16x8_t b) { return vandq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t or_bitwise(int16x8_t a, int16x8_t b) { return vorrq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t xor_bitwise(int16x8_t a, int16x8_t b) { return veorq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t or_not_bitwise(int16x8_t a, int16x8_t b) { return vornq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t count_leading_sign_bits(int16x8_t a) { return vclsq_s16(a); }
[[gnu::always_inline]] nce int16x8_t count_leading_zero_bits(int16x8_t a) { return vclzq_s16(a); }
[[gnu::always_inline]] nce int16x8_t clear_bitwise(int16x8_t a, int16x8_t b) { return vbicq_s16(a, b); }
[[gnu::always_inline]] nce int16x4_t get_high(int16x8_t a) { return vget_high_s16(a); }
[[gnu::always_inline]] nce int16x4_t get_low(int16x8_t a) { return vget_low_s16(a); }
template <int lane>[[gnu::always_inline]] nce int16_t get(int16x8_t v) { return vgetq_lane_s16(v, lane); }
template <int n>[[gnu::always_inline]] nce int16x8_t extract(int16x8_t a, int16x8_t b) { return vextq_s16(a, b, n); }
[[gnu::always_inline]] nce int16x8_t reverse_64bit(int16x8_t vec) { return vrev64q_s16(vec); }
[[gnu::always_inline]] nce int16x8_t reverse_32bit(int16x8_t vec) { return vrev32q_s16(vec); }
[[gnu::always_inline]] nce int16x8x2_t zip(int16x8_t a, int16x8_t b) { return vzipq_s16(a, b); }
[[gnu::always_inline]] nce int16x8x2_t unzip(int16x8_t a, int16x8_t b) { return vuzpq_s16(a, b); }
[[gnu::always_inline]] nce int16x8x2_t transpose(int16x8_t a, int16x8_t b) { return vtrnq_s16(a, b); }
[[gnu::always_inline]] nce int16x8_t multiply(int16x8_t a, int16_t b) { return vmulq_n_s16(a, b); }
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
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long(int32x2_t a, int32x2_t v) { return vqdmull_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_double_saturate_high(int32x2_t a, int32x2_t v) { return vqdmulh_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_double_round_saturate_high(int32x2_t a, int32x2_t v) { return vqrdmulh_lane_s32(a, v, lane); }
[[gnu::always_inline]] nce int32x2_t subtract(int32x2_t a, int32x2_t b) { return vsub_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_long(int32x2_t a, int32x2_t b) { return vsubl_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_high(int32x2_t a, int32x2_t b) { return vhsub_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_saturate(int32x2_t a, int32x2_t b) { return vqsub_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_abs(int32x2_t a, int32x2_t b) { return vabd_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_abs_long(int32x2_t a, int32x2_t b) { return vabdl_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_abs_add(int32x2_t a, int32x2_t b, int32x2_t c) { return vaba_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_saturate_long(int32x2_t a, int32_t b) { return vqdmull_n_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t multiply_double_saturate_high(int32x2_t a, int32_t b) { return vqdmulh_n_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t multiply_double_round_saturate_high(int32x2_t a, int32_t b) { return vqrdmulh_n_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t abs(int32x2_t a) { return vabs_s32(a); }
[[gnu::always_inline]] nce int32x2_t abs_saturate(int32x2_t a) { return vqabs_s32(a); }
[[gnu::always_inline]] nce int32x2_t max(int32x2_t a, int32x2_t b) { return vmax_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t min(int32x2_t a, int32x2_t b) { return vmin_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t add_pairwise(int32x2_t a, int32x2_t b) { return vpadd_s32(a, b); }
[[gnu::always_inline]] nce int64x1_t add_pairwise_long(int32x2_t a) { return vpaddl_s32(a); }
[[gnu::always_inline]] nce int32x2_t add_pairwise_accumulate_long(int32x2_t a, int16x4_t b) { return vpadal_s16(a, b); }
[[gnu::always_inline]] nce int32x2_t max_pairwise(int32x2_t a, int32x2_t b) { return vpmax_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t min_pairwise(int32x2_t a, int32x2_t b) { return vpmin_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t equal(int32x2_t a, int32x2_t b) { return vceq_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t greater_than_or_equal(int32x2_t a, int32x2_t b) { return vcge_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t less_than_or_equal(int32x2_t a, int32x2_t b) { return vcle_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t greater_than(int32x2_t a, int32x2_t b) { return vcgt_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t less_than(int32x2_t a, int32x2_t b) { return vclt_s32(a, b); }
[[gnu::always_inline]] nce uint32x2_t and_test_nonzero(int32x2_t a, int32x2_t b) { return vtst_s32(a, b); }
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
template <int n>[[gnu::always_inline]] nce float32x2_t convert(int32x2_t a) { return vcvt_n_f32_s32(a, n); }
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
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_add(int32x2_t a, int32x2_t b, int32x2_t v) { return vmla_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply_subtract(int32x2_t a, int32x2_t b, int32x2_t v) { return vmls_lane_s32(a, b, v, lane); }
[[gnu::always_inline]] nce int32x2_t multiply_add(int32x2_t a, int32x2_t b, int32_t c) { return vmla_n_s32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int32x2_t multiply(int32x2_t a, int32x2_t v) { return vmul_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_long(int32x2_t a, int32x2_t v) { return vmull_lane_s32(a, v, lane); }
[[gnu::always_inline]] nce int32x2_t multiply_subtract(int32x2_t a, int32x2_t b, int32_t c) { return vmls_n_s32(a, b, c); }
[[gnu::always_inline]] nce int32x2_t negate(int32x2_t a) { return vneg_s32(a); }
[[gnu::always_inline]] nce int32x2_t negate_saturate(int32x2_t a) { return vqneg_s32(a); }
[[gnu::always_inline]] nce int32x2_t not_bitwise(int32x2_t a) { return vmvn_s32(a); }
[[gnu::always_inline]] nce int32x2_t and_bitwise(int32x2_t a, int32x2_t b) { return vand_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t or_bitwise(int32x2_t a, int32x2_t b) { return vorr_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t xor_bitwise(int32x2_t a, int32x2_t b) { return veor_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t or_not_bitwise(int32x2_t a, int32x2_t b) { return vorn_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t count_leading_sign_bits(int32x2_t a) { return vcls_s32(a); }
[[gnu::always_inline]] nce int32x2_t count_leading_zero_bits(int32x2_t a) { return vclz_s32(a); }
[[gnu::always_inline]] nce int32x2_t clear_bitwise(int32x2_t a, int32x2_t b) { return vbic_s32(a, b); }
template <int lane>[[gnu::always_inline]] nce int32x2_t duplicate_element(int32x2_t vec) { return vdup_lane_s32(vec, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t duplicate_element(int32x2_t vec) { return vdupq_lane_s32(vec, lane); }
[[gnu::always_inline]] nce int32x4_t combine(int32x2_t low, int32x2_t high) { return vcombine_s32(low, high); }
template <int lane>[[gnu::always_inline]] nce int32_t get(int32x2_t v) { return vget_lane_s32(v, lane); }
template <int n>[[gnu::always_inline]] nce int32x2_t extract(int32x2_t a, int32x2_t b) { return vext_s32(a, b, n); }
[[gnu::always_inline]] nce int32x2_t reverse_64bit(int32x2_t vec) { return vrev64_s32(vec); }
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
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_add_saturate_long(int32x4_t a, int16x4_t b, int16x4_t v) { return vqdmlal_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_saturate_long(int32x4_t a, int16x4_t b, int16x4_t v) { return vqdmlsl_lane_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t subtract_abs_add(int32x4_t a, int16x4_t b, int16x4_t c) { return vabal_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_add_saturate_long(int32x4_t a, int16x4_t b, int16_t c) { return vqdmlal_n_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_subtract_saturate_long(int32x4_t a, int16x4_t b, int16_t c) { return vqdmlsl_n_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t subtract(int32x4_t a, int16x4_t b) { return vsubw_s16(a, b); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high(int32x4_t a, int32x2_t v) { return vqdmulhq_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high(int32x4_t a, int32x2_t v) { return vqrdmulhq_lane_s32(a, v, lane); }
[[gnu::always_inline]] nce int32x4_t add(int32x4_t a, int32x4_t b) { return vaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_halve(int32x4_t a, int32x4_t b) { return vhaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_halve_round(int32x4_t a, int32x4_t b) { return vrhaddq_s32(a, b); }
[[gnu::always_inline]] nce int16x4_t add_narrow_high(int32x4_t a, int32x4_t b) { return vaddhn_s32(a, b); }
[[gnu::always_inline]] nce int16x4_t add_round_narrow_high(int32x4_t a, int32x4_t b) { return vraddhn_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t add_saturate(int32x4_t a, int32x4_t b) { return vqaddq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t a, int32x4_t b) { return vmulq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_add(int32x4_t a, int32x4_t b, int32x4_t c) { return vmlaq_s32(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract(int32x4_t a, int32x4_t b, int32x4_t c) { return vmlsq_s32(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high(int32x4_t a, int32x4_t b) { return vqdmulhq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high(int32x4_t a, int32x4_t b) { return vqrdmulhq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract(int32x4_t a, int32x4_t b) { return vsubq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_high(int32x4_t a, int32x4_t b) { return vhsubq_s32(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_narrow_high(int32x4_t a, int32x4_t b) { return vsubhn_s32(a, b); }
[[gnu::always_inline]] nce int16x4_t subtract_round_narrow_high(int32x4_t a, int32x4_t b) { return vrsubhn_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_saturate(int32x4_t a, int32x4_t b) { return vqsubq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_abs(int32x4_t a, int32x4_t b) { return vabdq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t subtract_abs_add(int32x4_t a, int32x4_t b, int32x4_t c) { return vabaq_s32(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_double_saturate_high(int32x4_t a, int32_t b) { return vqdmulhq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply_double_round_saturate_high(int32x4_t a, int32_t b) { return vqrdmulhq_n_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t abs(int32x4_t a) { return vabsq_s32(a); }
[[gnu::always_inline]] nce int32x4_t abs_saturate(int32x4_t a) { return vqabsq_s32(a); }
[[gnu::always_inline]] nce int32x4_t max(int32x4_t a, int32x4_t b) { return vmaxq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t min(int32x4_t a, int32x4_t b) { return vminq_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t add_pairwise_long(int32x4_t a) { return vpaddlq_s32(a); }
[[gnu::always_inline]] nce int32x4_t add_pairwise_accumulate_long(int32x4_t a, int16x8_t b) { return vpadalq_s16(a, b); }
[[gnu::always_inline]] nce uint32x4_t equal(int32x4_t a, int32x4_t b) { return vceqq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t greater_than_or_equal(int32x4_t a, int32x4_t b) { return vcgeq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t less_than_or_equal(int32x4_t a, int32x4_t b) { return vcleq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t greater_than(int32x4_t a, int32x4_t b) { return vcgtq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t less_than(int32x4_t a, int32x4_t b) { return vcltq_s32(a, b); }
[[gnu::always_inline]] nce uint32x4_t and_test_nonzero(int32x4_t a, int32x4_t b) { return vtstq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t a, int32x4_t b) { return vshlq_s32(a, b); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_left(int32x4_t a) { return vshlq_n_s32(a, n); }
[[gnu::always_inline]] nce int32x4_t shift_left_saturate(int32x4_t a, int32x4_t b) { return vqshlq_s32(a, b); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_left_saturate(int32x4_t a) { return vqshlq_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_left_unsigned_saturate(int32x4_t a) { return vqshluq_n_s32(a, n); }
[[gnu::always_inline]] nce int32x4_t shift_left_round(int32x4_t a, int32x4_t b) { return vrshlq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t shift_left_round_saturate(int32x4_t a, int32x4_t b) { return vqrshlq_s32(a, b); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_left_insert(int32x4_t a, int32x4_t b) { return vsliq_n_s32(a, b, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right(int32x4_t a) { return vshrq_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_round(int32x4_t a) { return vrshrq_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_accumulate(int32x4_t a, int32x4_t b) { return vsraq_n_s32(a, b, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_accumulate_round(int32x4_t a, int32x4_t b) { return vrsraq_n_s32(a, b, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_narrow(int32x4_t a) { return vshrn_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t qshrun(int32x4_t a) { return vqshrun_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t qshrn(int32x4_t a) { return vqshrn_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_unsigned_saturate_narrow(int32x4_t a) { return vqrshrun_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_saturate_narrow(int32x4_t a) { return vqrshrn_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int16x4_t shift_right_round_saturate_narrow(int32x4_t a) { return vrshrn_n_s32(a, n); }
template <int n>[[gnu::always_inline]] nce int32x4_t shift_right_insert(int32x4_t a, int32x4_t b) { return vsriq_n_s32(a, b, n); }
template <> [[gnu::always_inline]] nce float32x4_t convert(int32x4_t a) { return vcvtq_f32_s32(a); }
template <int n>[[gnu::always_inline]] nce float32x4_t convert(int32x4_t a) { return vcvtq_n_f32_s32(a, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(int32x4_t a) { return vreinterpretq_s8_s32(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(int32x4_t a) { return vreinterpretq_s16_s32(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int32x4_t a) { return vreinterpretq_f32_s32(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int32x4_t a) { return vreinterpretq_u8_s32(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int32x4_t a) { return vreinterpretq_u16_s32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int32x4_t a) { return vreinterpretq_u32_s32(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(int32x4_t a) { return vreinterpretq_p8_s32(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(int32x4_t a) { return vreinterpretq_p16_s32(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int32x4_t a) { return vreinterpretq_u64_s32(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(int32x4_t a) { return vreinterpretq_s64_s32(a); }
[[gnu::always_inline]] nce int16x4_t move_narrow(int32x4_t a) { return vmovn_s32(a); }
[[gnu::always_inline]] nce int16x4_t move_saturate_narrow(int32x4_t a) { return vqmovn_s32(a); }
[[gnu::always_inline]] nce uint16x4_t move_unsigned_saturate_narrow(int32x4_t a) { return vqmovun_s32(a); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_add_long(int32x4_t a, int16x4_t b, int16x4_t v) { return vmlal_lane_s16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_subtract_long(int32x4_t a, int16x4_t b, int16x4_t v) { return vmlsl_lane_s16(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t multiply_add_long(int32x4_t a, int16x4_t b, int16_t c) { return vmlal_n_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract_long(int32x4_t a, int16x4_t b, int16_t c) { return vmlsl_n_s16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t a, int32x2_t v) { return vmulq_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_add(int32x4_t a, int32x4_t b, int32x2_t v) { return vmlaq_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t multiply_subtract(int32x4_t a, int32x4_t b, int32x2_t v) { return vmlsq_lane_s32(a, b, v, lane); }
[[gnu::always_inline]] nce int32x4_t multiply_add(int32x4_t a, int32x4_t b, int32_t c) { return vmlaq_n_s32(a, b, c); }
[[gnu::always_inline]] nce int32x4_t multiply_subtract(int32x4_t a, int32x4_t b, int32_t c) { return vmlsq_n_s32(a, b, c); }
[[gnu::always_inline]] nce int32x4_t negate(int32x4_t a) { return vnegq_s32(a); }
[[gnu::always_inline]] nce int32x4_t negate_saturate(int32x4_t a) { return vqnegq_s32(a); }
[[gnu::always_inline]] nce int32x4_t not_bitwise(int32x4_t a) { return vmvnq_s32(a); }
[[gnu::always_inline]] nce int32x4_t and_bitwise(int32x4_t a, int32x4_t b) { return vandq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t or_bitwise(int32x4_t a, int32x4_t b) { return vorrq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t xor_bitwise(int32x4_t a, int32x4_t b) { return veorq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t or_not_bitwise(int32x4_t a, int32x4_t b) { return vornq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t count_leading_sign_bits(int32x4_t a) { return vclsq_s32(a); }
[[gnu::always_inline]] nce int32x4_t count_leading_zero_bits(int32x4_t a) { return vclzq_s32(a); }
[[gnu::always_inline]] nce int32x4_t clear_bitwise(int32x4_t a, int32x4_t b) { return vbicq_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t get_high(int32x4_t a) { return vget_high_s32(a); }
[[gnu::always_inline]] nce int32x2_t get_low(int32x4_t a) { return vget_low_s32(a); }
template <int lane>[[gnu::always_inline]] nce int32_t get(int32x4_t v) { return vgetq_lane_s32(v, lane); }
template <int n>[[gnu::always_inline]] nce int32x4_t extract(int32x4_t a, int32x4_t b) { return vextq_s32(a, b, n); }
[[gnu::always_inline]] nce int32x4_t reverse_64bit(int32x4_t vec) { return vrev64q_s32(vec); }
[[gnu::always_inline]] nce int32x4x2_t zip(int32x4_t a, int32x4_t b) { return vzipq_s32(a, b); }
[[gnu::always_inline]] nce int32x4x2_t unzip(int32x4_t a, int32x4_t b) { return vuzpq_s32(a, b); }
[[gnu::always_inline]] nce int32x4x2_t transpose(int32x4_t a, int32x4_t b) { return vtrnq_s32(a, b); }
[[gnu::always_inline]] nce int32x4_t multiply(int32x4_t a, int32_t b) { return vmulq_n_s32(a, b); }
[[gnu::always_inline]] nce uint64x1_t add(uint64x1_t a, uint64x1_t b) { return vadd_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t add_saturate(uint64x1_t a, uint64x1_t b) { return vqadd_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t subtract(uint64x1_t a, uint64x1_t b) { return vsub_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t subtract_saturate(uint64x1_t a, uint64x1_t b) { return vqsub_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t add_pairwise_accumulate_long(uint64x1_t a, uint32x2_t b) { return vpadal_u32(a, b); }
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
[[gnu::always_inline]] nce uint64x1_t and_bitwise(uint64x1_t a, uint64x1_t b) { return vand_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t or_bitwise(uint64x1_t a, uint64x1_t b) { return vorr_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t xor_bitwise(uint64x1_t a, uint64x1_t b) { return veor_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t or_not_bitwise(uint64x1_t a, uint64x1_t b) { return vorn_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t clear_bitwise(uint64x1_t a, uint64x1_t b) { return vbic_u64(a, b); }
[[gnu::always_inline]] nce uint64x1_t select_bitwise(uint64x1_t a, uint64x1_t b, uint64x1_t c) { return vbsl_u64(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint64x1_t duplicate_element(uint64x1_t vec) { return vdup_lane_u64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t duplicate_element(uint64x1_t vec) { return vdupq_lane_u64(vec, lane); }
[[gnu::always_inline]] nce uint64x2_t combine(uint64x1_t low, uint64x1_t high) { return vcombine_u64(low, high); }
template <int lane>[[gnu::always_inline]] nce uint64_t get(uint64x1_t v) { return vget_lane_u64(v, lane); }
template <int n>[[gnu::always_inline]] nce uint64x1_t extract(uint64x1_t a, uint64x1_t b) { return vext_u64(a, b, n); }
[[gnu::always_inline]] nce int64x1_t select_bitwise(uint64x1_t a, int64x1_t b, int64x1_t c) { return vbsl_s64(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t add(uint64x2_t a, uint64x2_t b) { return vaddq_u64(a, b); }
[[gnu::always_inline]] nce uint32x2_t add_narrow_high(uint64x2_t a, uint64x2_t b) { return vaddhn_u64(a, b); }
[[gnu::always_inline]] nce uint32x2_t add_round_narrow_high(uint64x2_t a, uint64x2_t b) { return vraddhn_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t add_saturate(uint64x2_t a, uint64x2_t b) { return vqaddq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract(uint64x2_t a, uint64x2_t b) { return vsubq_u64(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_narrow_high(uint64x2_t a, uint64x2_t b) { return vsubhn_u64(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_round_narrow_high(uint64x2_t a, uint64x2_t b) { return vrsubhn_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract_saturate(uint64x2_t a, uint64x2_t b) { return vqsubq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t shift_left_saturate(uint64x2_t a, int64x2_t b) { return vqshlq_u64(a, b); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_left_saturate(uint64x2_t a) { return vqshlq_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_left_insert(uint64x2_t a, uint64x2_t b) { return vsliq_n_u64(a, b, n); }
[[gnu::always_inline]] nce uint64x2_t add(uint64x2_t a, uint32x2_t b) { return vaddw_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t multiply_add_long(uint64x2_t a, uint32x2_t b, uint32x2_t c) { return vmlal_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long(uint64x2_t a, uint32x2_t b, uint32x2_t c) { return vmlsl_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t subtract(uint64x2_t a, uint32x2_t b) { return vsubw_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract_abs_add(uint64x2_t a, uint32x2_t b, uint32x2_t c) { return vabal_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t shift_left_round(uint64x2_t a, int64x2_t b) { return vrshlq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t shift_left_round_saturate(uint64x2_t a, int64x2_t b) { return vqrshlq_u64(a, b); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_right(uint64x2_t a) { return vshrq_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_right_round(uint64x2_t a) { return vrshrq_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_right_accumulate(uint64x2_t a, uint64x2_t b) { return vsraq_n_u64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_right_accumulate_round(uint64x2_t a, uint64x2_t b) { return vrsraq_n_u64(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_narrow(uint64x2_t a) { return vshrn_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t qshrn(uint64x2_t a) { return vqshrn_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_saturate_narrow(uint64x2_t a) { return vqrshrn_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_round_saturate_narrow(uint64x2_t a) { return vrshrn_n_u64(a, n); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_right_insert(uint64x2_t a, uint64x2_t b) { return vsriq_n_u64(a, b, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint64x2_t a) { return vreinterpretq_s8_u64(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_s16_u64(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint64x2_t a) { return vreinterpretq_s32_u64(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint64x2_t a) { return vreinterpretq_f32_u64(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(uint64x2_t a) { return vreinterpretq_u8_u64(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_u16_u64(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(uint64x2_t a) { return vreinterpretq_u32_u64(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(uint64x2_t a) { return vreinterpretq_p8_u64(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_p16_u64(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint64x2_t a) { return vreinterpretq_s64_u64(a); }
[[gnu::always_inline]] nce uint32x2_t move_narrow(uint64x2_t a) { return vmovn_u64(a); }
[[gnu::always_inline]] nce uint32x2_t move_saturate_narrow(uint64x2_t a) { return vqmovn_u64(a); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_add_long(uint64x2_t a, uint32x2_t b, uint32x2_t v) { return vmlal_lane_u32(a, b, v, lane); }
[[gnu::always_inline]] nce uint64x2_t add_pairwise_accumulate_long(uint64x2_t a, uint32x4_t b) { return vpadalq_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t shift_left(uint64x2_t a, int64x2_t b) { return vshlq_u64(a, b); }
template <int n>[[gnu::always_inline]] nce uint64x2_t shift_left(uint64x2_t a) { return vshlq_n_u64(a, n); }
[[gnu::always_inline]] nce uint64x2_t and_bitwise(uint64x2_t a, uint64x2_t b) { return vandq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t or_bitwise(uint64x2_t a, uint64x2_t b) { return vorrq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t xor_bitwise(uint64x2_t a, uint64x2_t b) { return veorq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t or_not_bitwise(uint64x2_t a, uint64x2_t b) { return vornq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t clear_bitwise(uint64x2_t a, uint64x2_t b) { return vbicq_u64(a, b); }
[[gnu::always_inline]] nce uint64x2_t select_bitwise(uint64x2_t a, uint64x2_t b, uint64x2_t c) { return vbslq_u64(a, b, c); }
[[gnu::always_inline]] nce uint64x1_t get_high(uint64x2_t a) { return vget_high_u64(a); }
[[gnu::always_inline]] nce uint64x1_t get_low(uint64x2_t a) { return vget_low_u64(a); }
template <int lane>[[gnu::always_inline]] nce uint64_t get(uint64x2_t v) { return vgetq_lane_u64(v, lane); }
template <int n>[[gnu::always_inline]] nce uint64x2_t extract(uint64x2_t a, uint64x2_t b) { return vextq_u64(a, b, n); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long(uint64x2_t a, uint32x2_t b, uint32x2_t v) { return vmlsl_lane_u32(a, b, v, lane); }
[[gnu::always_inline]] nce uint64x2_t multiply_add_long(uint64x2_t a, uint32x2_t b, uint32_t c) { return vmlal_n_u32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t multiply_subtract_long(uint64x2_t a, uint32x2_t b, uint32_t c) { return vmlsl_n_u32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t select_bitwise(uint64x2_t a, int64x2_t b, int64x2_t c) { return vbslq_s64(a, b, c); }
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
[[gnu::always_inline]] nce uint32x2_t subtract_high(uint32x2_t a, uint32x2_t b) { return vhsub_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_saturate(uint32x2_t a, uint32x2_t b) { return vqsub_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_abs(uint32x2_t a, uint32x2_t b) { return vabd_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t subtract_abs_long(uint32x2_t a, uint32x2_t b) { return vabdl_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t subtract_abs_add(uint32x2_t a, uint32x2_t b, uint32x2_t c) { return vaba_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t max(uint32x2_t a, uint32x2_t b) { return vmax_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t min(uint32x2_t a, uint32x2_t b) { return vmin_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t reciprocal_estimate(uint32x2_t a) { return vrecpe_u32(a); }
[[gnu::always_inline]] nce uint32x2_t reciprocal_sqrt_estimate(uint32x2_t a) { return vrsqrte_u32(a); }
[[gnu::always_inline]] nce uint32x2_t add_pairwise(uint32x2_t a, uint32x2_t b) { return vpadd_u32(a, b); }
[[gnu::always_inline]] nce uint64x1_t add_pairwise_long(uint32x2_t a) { return vpaddl_u32(a); }
[[gnu::always_inline]] nce uint32x2_t add_pairwise_accumulate_long(uint32x2_t a, uint16x4_t b) { return vpadal_u16(a, b); }
[[gnu::always_inline]] nce uint32x2_t max_pairwise(uint32x2_t a, uint32x2_t b) { return vpmax_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t min_pairwise(uint32x2_t a, uint32x2_t b) { return vpmin_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t equal(uint32x2_t a, uint32x2_t b) { return vceq_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t greater_than_or_equal(uint32x2_t a, uint32x2_t b) { return vcge_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t less_than_or_equal(uint32x2_t a, uint32x2_t b) { return vcle_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t greater_than(uint32x2_t a, uint32x2_t b) { return vcgt_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t less_than(uint32x2_t a, uint32x2_t b) { return vclt_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t and_test_nonzero(uint32x2_t a, uint32x2_t b) { return vtst_u32(a, b); }
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
template <int n>[[gnu::always_inline]] nce float32x2_t convert(uint32x2_t a) { return vcvt_n_f32_u32(a, n); }
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
template <int lane>[[gnu::always_inline]] nce uint32x2_t multiply_add(uint32x2_t a, uint32x2_t b, uint32x2_t v) { return vmla_lane_u32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t multiply_subtract(uint32x2_t a, uint32x2_t b, uint32x2_t v) { return vmls_lane_u32(a, b, v, lane); }
[[gnu::always_inline]] nce uint32x2_t multiply_add(uint32x2_t a, uint32x2_t b, uint32_t c) { return vmla_n_u32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t multiply(uint32x2_t a, uint32x2_t v) { return vmul_lane_u32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t multiply_long(uint32x2_t a, uint32x2_t v) { return vmull_lane_u32(a, v, lane); }
[[gnu::always_inline]] nce uint32x2_t multiply_subtract(uint32x2_t a, uint32x2_t b, uint32_t c) { return vmls_n_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t not_bitwise(uint32x2_t a) { return vmvn_u32(a); }
[[gnu::always_inline]] nce uint32x2_t and_bitwise(uint32x2_t a, uint32x2_t b) { return vand_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t or_bitwise(uint32x2_t a, uint32x2_t b) { return vorr_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t xor_bitwise(uint32x2_t a, uint32x2_t b) { return veor_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t or_not_bitwise(uint32x2_t a, uint32x2_t b) { return vorn_u32(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce int32x2_t count_leading_sign_bits(uint32x2_t a) { return vcls_u32(a); }
#endif
[[gnu::always_inline]] nce uint32x2_t count_leading_zero_bits(uint32x2_t a) { return vclz_u32(a); }
[[gnu::always_inline]] nce int32x2_t select_bitwise(uint32x2_t a, int32x2_t b, int32x2_t c) { return vbsl_s32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t clear_bitwise(uint32x2_t a, uint32x2_t b) { return vbic_u32(a, b); }
[[gnu::always_inline]] nce uint32x2_t select_bitwise(uint32x2_t a, uint32x2_t b, uint32x2_t c) { return vbsl_u32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t duplicate_element(uint32x2_t vec) { return vdup_lane_u32(vec, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t duplicate_element(uint32x2_t vec) { return vdupq_lane_u32(vec, lane); }
[[gnu::always_inline]] nce uint32x4_t combine(uint32x2_t low, uint32x2_t high) { return vcombine_u32(low, high); }
template <int lane>[[gnu::always_inline]] nce uint32_t get(uint32x2_t v) { return vget_lane_u32(v, lane); }
template <int n>[[gnu::always_inline]] nce uint32x2_t extract(uint32x2_t a, uint32x2_t b) { return vext_u32(a, b, n); }
[[gnu::always_inline]] nce uint32x2_t reverse_64bit(uint32x2_t vec) { return vrev64_u32(vec); }
[[gnu::always_inline]] nce uint32x2x2_t zip(uint32x2_t a, uint32x2_t b) { return vzip_u32(a, b); }
[[gnu::always_inline]] nce uint32x2x2_t unzip(uint32x2_t a, uint32x2_t b) { return vuzp_u32(a, b); }
[[gnu::always_inline]] nce uint32x2x2_t transpose(uint32x2_t a, uint32x2_t b) { return vtrn_u32(a, b); }
[[gnu::always_inline]] nce float32x2_t select_bitwise(uint32x2_t a, float32x2_t b, float32x2_t c) { return vbsl_f32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t multiply(uint32x2_t a, uint32_t b) { return vmul_n_u32(a, b); }
[[gnu::always_inline]] nce uint64x2_t multiply_long(uint32x2_t a, uint32_t b) { return vmull_n_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add(uint32x4_t a, uint16x4_t b) { return vaddw_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_add_long(uint32x4_t a, uint16x4_t b, uint16x4_t c) { return vmlal_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_subtract_long(uint32x4_t a, uint16x4_t b, uint16x4_t c) { return vmlsl_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t subtract(uint32x4_t a, uint16x4_t b) { return vsubw_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_abs_add(uint32x4_t a, uint16x4_t b, uint16x4_t c) { return vabal_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t a, int32x4_t b) { return vshlq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add(uint32x4_t a, uint32x4_t b) { return vaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_halve(uint32x4_t a, uint32x4_t b) { return vhaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_halve_round(uint32x4_t a, uint32x4_t b) { return vrhaddq_u32(a, b); }
[[gnu::always_inline]] nce uint16x4_t add_narrow_high(uint32x4_t a, uint32x4_t b) { return vaddhn_u32(a, b); }
[[gnu::always_inline]] nce uint16x4_t add_round_narrow_high(uint32x4_t a, uint32x4_t b) { return vraddhn_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t add_saturate(uint32x4_t a, uint32x4_t b) { return vqaddq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t a, uint32x4_t b) { return vmulq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t multiply_add(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vmlaq_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_subtract(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vmlsq_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t subtract(uint32x4_t a, uint32x4_t b) { return vsubq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_high(uint32x4_t a, uint32x4_t b) { return vhsubq_u32(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract_narrow_high(uint32x4_t a, uint32x4_t b) { return vsubhn_u32(a, b); }
[[gnu::always_inline]] nce uint16x4_t subtract_round_narrow_high(uint32x4_t a, uint32x4_t b) { return vrsubhn_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_saturate(uint32x4_t a, uint32x4_t b) { return vqsubq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_abs(uint32x4_t a, uint32x4_t b) { return vabdq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t subtract_abs_add(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vabaq_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t max(uint32x4_t a, uint32x4_t b) { return vmaxq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t min(uint32x4_t a, uint32x4_t b) { return vminq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t reciprocal_estimate(uint32x4_t a) { return vrecpeq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t reciprocal_sqrt_estimate(uint32x4_t a) { return vrsqrteq_u32(a); }
[[gnu::always_inline]] nce uint64x2_t add_pairwise_long(uint32x4_t a) { return vpaddlq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t add_pairwise_accumulate_long(uint32x4_t a, uint16x8_t b) { return vpadalq_u16(a, b); }
[[gnu::always_inline]] nce uint32x4_t equal(uint32x4_t a, uint32x4_t b) { return vceqq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t greater_than_or_equal(uint32x4_t a, uint32x4_t b) { return vcgeq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t less_than_or_equal(uint32x4_t a, uint32x4_t b) { return vcleq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t greater_than(uint32x4_t a, uint32x4_t b) { return vcgtq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t less_than(uint32x4_t a, uint32x4_t b) { return vcltq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t and_test_nonzero(uint32x4_t a, uint32x4_t b) { return vtstq_u32(a, b); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_left(uint32x4_t a) { return vshlq_n_u32(a, n); }
[[gnu::always_inline]] nce uint32x4_t shift_left_saturate(uint32x4_t a, int32x4_t b) { return vqshlq_u32(a, b); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_left_saturate(uint32x4_t a) { return vqshlq_n_u32(a, n); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round(uint32x4_t a, int32x4_t b) { return vrshlq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t shift_left_round_saturate(uint32x4_t a, int32x4_t b) { return vqrshlq_u32(a, b); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_left_insert(uint32x4_t a, uint32x4_t b) { return vsliq_n_u32(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right(uint32x4_t a) { return vshrq_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_round(uint32x4_t a) { return vrshrq_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_accumulate(uint32x4_t a, uint32x4_t b) { return vsraq_n_u32(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_accumulate_round(uint32x4_t a, uint32x4_t b) { return vrsraq_n_u32(a, b, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_narrow(uint32x4_t a) { return vshrn_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t qshrn(uint32x4_t a) { return vqshrn_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_saturate_narrow(uint32x4_t a) { return vqrshrn_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint16x4_t shift_right_round_saturate_narrow(uint32x4_t a) { return vrshrn_n_u32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t shift_right_insert(uint32x4_t a, uint32x4_t b) { return vsriq_n_u32(a, b, n); }
template <> [[gnu::always_inline]] nce float32x4_t convert(uint32x4_t a) { return vcvtq_f32_u32(a); }
template <int n>[[gnu::always_inline]] nce float32x4_t convert(uint32x4_t a) { return vcvtq_n_f32_u32(a, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(uint32x4_t a) { return vreinterpretq_s8_u32(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_s16_u32(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(uint32x4_t a) { return vreinterpretq_s32_u32(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(uint32x4_t a) { return vreinterpretq_f32_u32(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(uint32x4_t a) { return vreinterpretq_u8_u32(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_u16_u32(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(uint32x4_t a) { return vreinterpretq_p8_u32(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_p16_u32(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(uint32x4_t a) { return vreinterpretq_u64_u32(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(uint32x4_t a) { return vreinterpretq_s64_u32(a); }
[[gnu::always_inline]] nce uint16x4_t move_narrow(uint32x4_t a) { return vmovn_u32(a); }
[[gnu::always_inline]] nce uint16x4_t move_saturate_narrow(uint32x4_t a) { return vqmovn_u32(a); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_add_long(uint32x4_t a, uint16x4_t b, uint16x4_t v) { return vmlal_lane_u16(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_subtract_long(uint32x4_t a, uint16x4_t b, uint16x4_t v) { return vmlsl_lane_u16(a, b, v, lane); }
[[gnu::always_inline]] nce uint32x4_t multiply_add_long(uint32x4_t a, uint16x4_t b, uint16_t c) { return vmlal_n_u16(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_subtract_long(uint32x4_t a, uint16x4_t b, uint16_t c) { return vmlsl_n_u16(a, b, c); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t a, uint32x2_t v) { return vmulq_lane_u32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_add(uint32x4_t a, uint32x4_t b, uint32x2_t v) { return vmlaq_lane_u32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t multiply_subtract(uint32x4_t a, uint32x4_t b, uint32x2_t v) { return vmlsq_lane_u32(a, b, v, lane); }
[[gnu::always_inline]] nce uint32x4_t multiply_add(uint32x4_t a, uint32x4_t b, uint32_t c) { return vmlaq_n_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply_subtract(uint32x4_t a, uint32x4_t b, uint32_t c) { return vmlsq_n_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t not_bitwise(uint32x4_t a) { return vmvnq_u32(a); }
[[gnu::always_inline]] nce uint32x4_t and_bitwise(uint32x4_t a, uint32x4_t b) { return vandq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t or_bitwise(uint32x4_t a, uint32x4_t b) { return vorrq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t xor_bitwise(uint32x4_t a, uint32x4_t b) { return veorq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t or_not_bitwise(uint32x4_t a, uint32x4_t b) { return vornq_u32(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce int32x4_t count_leading_sign_bits(uint32x4_t a) { return vclsq_u32(a); }
#endif
[[gnu::always_inline]] nce uint32x4_t count_leading_zero_bits(uint32x4_t a) { return vclzq_u32(a); }
[[gnu::always_inline]] nce int32x4_t select_bitwise(uint32x4_t a, int32x4_t b, int32x4_t c) { return vbslq_s32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t clear_bitwise(uint32x4_t a, uint32x4_t b) { return vbicq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t select_bitwise(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vbslq_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x2_t get_high(uint32x4_t a) { return vget_high_u32(a); }
[[gnu::always_inline]] nce uint32x2_t get_low(uint32x4_t a) { return vget_low_u32(a); }
template <int lane>[[gnu::always_inline]] nce uint32_t get(uint32x4_t v) { return vgetq_lane_u32(v, lane); }
template <int n>[[gnu::always_inline]] nce uint32x4_t extract(uint32x4_t a, uint32x4_t b) { return vextq_u32(a, b, n); }
[[gnu::always_inline]] nce uint32x4_t reverse_64bit(uint32x4_t vec) { return vrev64q_u32(vec); }
[[gnu::always_inline]] nce uint32x4x2_t zip(uint32x4_t a, uint32x4_t b) { return vzipq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4x2_t unzip(uint32x4_t a, uint32x4_t b) { return vuzpq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4x2_t transpose(uint32x4_t a, uint32x4_t b) { return vtrnq_u32(a, b); }
[[gnu::always_inline]] nce float32x4_t select_bitwise(uint32x4_t a, float32x4_t b, float32x4_t c) { return vbslq_f32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t multiply(uint32x4_t a, uint32_t b) { return vmulq_n_u32(a, b); }
[[gnu::always_inline]] nce float32x2_t add(float32x2_t a, float32x2_t b) { return vadd_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t multiply(float32x2_t a, float32x2_t b) { return vmul_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t multiply_add(float32x2_t a, float32x2_t b, float32x2_t c) {
#ifdef __ARM_FEATURE_FMA
    return vfma_f32(a, b, c);
#else
    return vmla_f32(a, b, c);
#endif
}
[[gnu::always_inline]] nce float32x2_t multiply_subtract(float32x2_t a, float32x2_t b, float32x2_t c) {
#ifdef __ARM_FEATURE_FMA
    return vfms_f32(a, b, c);
#else
    return vmls_f32(a, b, c);
#endif
}
[[gnu::always_inline]] nce float32x2_t subtract(float32x2_t a, float32x2_t b) { return vsub_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t subtract_abs(float32x2_t a, float32x2_t b) { return vabd_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t abs(float32x2_t a) { return vabs_f32(a); }
[[gnu::always_inline]] nce float32x2_t max(float32x2_t a, float32x2_t b) { return vmax_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t min(float32x2_t a, float32x2_t b) { return vmin_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t reciprocal_estimate(float32x2_t a) { return vrecpe_f32(a); }
[[gnu::always_inline]] nce float32x2_t reciprocal_step(float32x2_t a, float32x2_t b) { return vrecps_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t reciprocal_sqrt_estimate(float32x2_t a) { return vrsqrte_f32(a); }
[[gnu::always_inline]] nce float32x2_t reciprocal_sqrt_step(float32x2_t a, float32x2_t b) { return vrsqrts_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t add_pairwise(float32x2_t a, float32x2_t b) { return vpadd_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t max_pairwise(float32x2_t a, float32x2_t b) { return vpmax_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t min_pairwise(float32x2_t a, float32x2_t b) { return vpmin_f32(a, b); }
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
template <int n>[[gnu::always_inline]] nce int32x2_t convert(float32x2_t a) { return vcvt_n_s32_f32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t convert(float32x2_t a) { return vcvt_n_u32_f32(a, n); }
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
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_add(float32x2_t a, float32x2_t b, float32x2_t v) { return vmla_lane_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply_subtract(float32x2_t a, float32x2_t b, float32x2_t v) { return vmls_lane_f32(a, b, v, lane); }
[[gnu::always_inline]] nce float32x2_t multiply_add(float32x2_t a, float32x2_t b, float32_t c) { return vmla_n_f32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce float32x2_t multiply(float32x2_t a, float32x2_t v) { return vmul_lane_f32(a, v, lane); }
[[gnu::always_inline]] nce float32x2_t multiply_subtract(float32x2_t a, float32x2_t b, float32_t c) { return vmls_n_f32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce float32x2_t duplicate_element(float32x2_t vec) { return vdup_lane_f32(vec, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t duplicate_element(float32x2_t vec) { return vdupq_lane_f32(vec, lane); }
[[gnu::always_inline]] nce float32x4_t combine(float32x2_t low, float32x2_t high) { return vcombine_f32(low, high); }
template <int lane>[[gnu::always_inline]] nce float32_t get(float32x2_t v) { return vget_lane_f32(v, lane); }
template <int n>[[gnu::always_inline]] nce float32x2_t extract(float32x2_t a, float32x2_t b) { return vext_f32(a, b, n); }
[[gnu::always_inline]] nce float32x2_t reverse_64bit(float32x2_t vec) { return vrev64_f32(vec); }
[[gnu::always_inline]] nce float32x2x2_t zip(float32x2_t a, float32x2_t b) { return vzip_f32(a, b); }
[[gnu::always_inline]] nce float32x2x2_t unzip(float32x2_t a, float32x2_t b) { return vuzp_f32(a, b); }
[[gnu::always_inline]] nce float32x2x2_t transpose(float32x2_t a, float32x2_t b) { return vtrn_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t multiply(float32x2_t a, float32_t b) { return vmul_n_f32(a, b); }
[[gnu::always_inline]] nce float32x2_t negate(float32x2_t a) { return vneg_f32(a); }
[[gnu::always_inline]] nce float32x4_t add(float32x4_t a, float32x4_t b) { return vaddq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t a, float32x4_t b) { return vmulq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t multiply_add(float32x4_t a, float32x4_t b, float32x4_t c) {
#ifdef __ARM_FEATURE_FMA
    return vfmaq_f32(a, b, c);
#else
    return vmlaq_f32(a, b, c);
#endif
}
[[gnu::always_inline]] nce float32x4_t multiply_subtract(float32x4_t a, float32x4_t b, float32x4_t c) { return vmlsq_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t subtract(float32x4_t a, float32x4_t b) { return vsubq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t subtract_abs(float32x4_t a, float32x4_t b) { return vabdq_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t abs(float32x4_t a) { return vabsq_f32(a); }
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
template <> [[gnu::always_inline]] nce int32x4_t convert(float32x4_t a) { return vcvtq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t convert(float32x4_t a) { return vcvtq_u32_f32(a); }
template <int n>[[gnu::always_inline]] nce int32x4_t convert(float32x4_t a) { return vcvtq_n_s32_f32(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x4_t convert(float32x4_t a) { return vcvtq_n_u32_f32(a, n); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(float32x4_t a) { return vreinterpretq_s8_f32(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(float32x4_t a) { return vreinterpretq_s16_f32(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(float32x4_t a) { return vreinterpretq_s32_f32(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(float32x4_t a) { return vreinterpretq_u8_f32(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(float32x4_t a) { return vreinterpretq_u16_f32(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(float32x4_t a) { return vreinterpretq_u32_f32(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(float32x4_t a) { return vreinterpretq_p8_f32(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(float32x4_t a) { return vreinterpretq_p16_f32(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(float32x4_t a) { return vreinterpretq_u64_f32(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(float32x4_t a) { return vreinterpretq_s64_f32(a); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t a, float32x2_t v) { return vmulq_lane_f32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_add(float32x4_t a, float32x4_t b, float32x2_t v) { return vmlaq_lane_f32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t multiply_subtract(float32x4_t a, float32x4_t b, float32x2_t v) { return vmlsq_lane_f32(a, b, v, lane); }
[[gnu::always_inline]] nce float32x4_t multiply_add(float32x4_t a, float32x4_t b, float32_t c) { return vmlaq_n_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t multiply_subtract(float32x4_t a, float32x4_t b, float32_t c) { return vmlsq_n_f32(a, b, c); }
[[gnu::always_inline]] nce float32x4_t multiply(float32x4_t a, float32_t b) { return vmulq_n_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t negate(float32x4_t a) { return vnegq_f32(a); }
[[gnu::always_inline]] nce float32x2_t get_high(float32x4_t a) { return vget_high_f32(a); }
[[gnu::always_inline]] nce float32x2_t get_low(float32x4_t a) { return vget_low_f32(a); }
template <int lane>[[gnu::always_inline]] nce float32_t get(float32x4_t v) { return vgetq_lane_f32(v, lane); }
template <int n>[[gnu::always_inline]] nce float32x4_t extract(float32x4_t a, float32x4_t b) { return vextq_f32(a, b, n); }
[[gnu::always_inline]] nce float32x4_t reverse_64bit(float32x4_t vec) { return vrev64q_f32(vec); }
[[gnu::always_inline]] nce float32x4x2_t zip(float32x4_t a, float32x4_t b) { return vzipq_f32(a, b); }
[[gnu::always_inline]] nce float32x4x2_t unzip(float32x4_t a, float32x4_t b) { return vuzpq_f32(a, b); }
[[gnu::always_inline]] nce float32x4x2_t transpose(float32x4_t a, float32x4_t b) { return vtrnq_f32(a, b); }
[[gnu::always_inline]] nce poly8x8_t multiply(poly8x8_t a, poly8x8_t b) { return vmul_p8(a, b); }
[[gnu::always_inline]] nce poly16x8_t multiply_long(poly8x8_t a, poly8x8_t b) { return vmull_p8(a, b); }
[[gnu::always_inline]] nce uint8x8_t equal(poly8x8_t a, poly8x8_t b) { return vceq_p8(a, b); }
[[gnu::always_inline]] nce uint8x8_t and_test_nonzero(poly8x8_t a, poly8x8_t b) { return vtst_p8(a, b); }
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
[[gnu::always_inline]] nce poly8x8_t not_bitwise(poly8x8_t a) { return vmvn_p8(a); }
[[gnu::always_inline]] nce poly8x8_t count_active_bits(poly8x8_t a) { return vcnt_p8(a); }
template <int lane>[[gnu::always_inline]] nce poly8x8_t duplicate_element(poly8x8_t vec) { return vdup_lane_p8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x16_t duplicate_element(poly8x8_t vec) { return vdupq_lane_p8(vec, lane); }
[[gnu::always_inline]] nce poly8x16_t combine(poly8x8_t low, poly8x8_t high) { return vcombine_p8(low, high); }
template <int lane>[[gnu::always_inline]] nce poly8_t get(poly8x8_t v) { return vget_lane_p8(v, lane); }
template <int n>[[gnu::always_inline]] nce poly8x8_t extract(poly8x8_t a, poly8x8_t b) { return vext_p8(a, b, n); }
[[gnu::always_inline]] nce poly8x8_t reverse_64bit(poly8x8_t vec) { return vrev64_p8(vec); }
[[gnu::always_inline]] nce poly8x8_t reverse_32bit(poly8x8_t vec) { return vrev32_p8(vec); }
[[gnu::always_inline]] nce poly8x8_t reverse_16bit(poly8x8_t vec) { return vrev16_p8(vec); }
[[gnu::always_inline]] nce poly8x8_t table_lookup1(poly8x8_t a, uint8x8_t idx) { return vtbl1_p8(a, idx); }
[[gnu::always_inline]] nce poly8x8x2_t zip(poly8x8_t a, poly8x8_t b) { return vzip_p8(a, b); }
[[gnu::always_inline]] nce poly8x8x2_t unzip(poly8x8_t a, poly8x8_t b) { return vuzp_p8(a, b); }
[[gnu::always_inline]] nce poly8x8x2_t transpose(poly8x8_t a, poly8x8_t b) { return vtrn_p8(a, b); }
[[gnu::always_inline]] nce poly8x8_t table_lookup_extension1(poly8x8_t a, poly8x8_t b, uint8x8_t idx) { return vtbx1_p8(a, b, idx); }
#ifdef __clang__
[[gnu::always_inline]] nce poly8x8_t add(poly8x8_t a, poly8x8_t b) { return vadd_p8(a, b); }
#endif
[[gnu::always_inline]] nce poly8x8_t table_lookup_extension2(poly8x8_t a, poly8x8x2_t b, uint8x8_t idx) { return vtbx2_p8(a, b, idx); }
[[gnu::always_inline]] nce poly8x8_t table_lookup_extension3(poly8x8_t a, poly8x8x3_t b, uint8x8_t idx) { return vtbx3_p8(a, b, idx); }
[[gnu::always_inline]] nce poly8x8_t table_lookup_extension4(poly8x8_t a, poly8x8x4_t b, uint8x8_t idx) { return vtbx4_p8(a, b, idx); }
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
template <int lane>[[gnu::always_inline]] nce poly16x4_t duplicate_element(poly16x4_t vec) { return vdup_lane_p16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8_t duplicate_element(poly16x4_t vec) { return vdupq_lane_p16(vec, lane); }
[[gnu::always_inline]] nce poly16x8_t combine(poly16x4_t low, poly16x4_t high) { return vcombine_p16(low, high); }
template <int lane>[[gnu::always_inline]] nce poly16_t get(poly16x4_t v) { return vget_lane_p16(v, lane); }
template <int n>[[gnu::always_inline]] nce poly16x4_t extract(poly16x4_t a, poly16x4_t b) { return vext_p16(a, b, n); }
[[gnu::always_inline]] nce poly16x4_t reverse_64bit(poly16x4_t vec) { return vrev64_p16(vec); }
[[gnu::always_inline]] nce poly16x4_t reverse_32bit(poly16x4_t vec) { return vrev32_p16(vec); }
[[gnu::always_inline]] nce poly16x4x2_t zip(poly16x4_t a, poly16x4_t b) { return vzip_p16(a, b); }
[[gnu::always_inline]] nce poly16x4x2_t unzip(poly16x4_t a, poly16x4_t b) { return vuzp_p16(a, b); }
[[gnu::always_inline]] nce poly16x4x2_t transpose(poly16x4_t a, poly16x4_t b) { return vtrn_p16(a, b); }
#ifdef __clang__
[[gnu::always_inline]] nce poly16x4_t add(poly16x4_t a, poly16x4_t b) { return vadd_p16(a, b); }
#endif
[[gnu::always_inline]] nce int64x1_t add(int64x1_t a, int64x1_t b) { return vadd_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t add(int64x2_t a, int64x2_t b) { return vaddq_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t add(int64x2_t a, int32x2_t b) { return vaddw_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t add_narrow_high(int64x2_t a, int64x2_t b) { return vaddhn_s64(a, b); }
[[gnu::always_inline]] nce int32x2_t add_round_narrow_high(int64x2_t a, int64x2_t b) { return vraddhn_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t add_saturate(int64x1_t a, int64x1_t b) { return vqadd_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t add_saturate(int64x2_t a, int64x2_t b) { return vqaddq_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t multiply_add_long(int64x2_t a, int32x2_t b, int32x2_t c) { return vmlal_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_subtract_long(int64x2_t a, int32x2_t b, int32x2_t c) { return vmlsl_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long(int64x2_t a, int32x2_t b, int32x2_t c) { return vqdmlal_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long(int64x2_t a, int32x2_t b, int32x2_t c) { return vqdmlsl_s32(a, b, c); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long(int64x2_t a, int32x2_t b, int32x2_t v) { return vqdmlal_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long(int64x2_t a, int32x2_t b, int32x2_t v) { return vqdmlsl_lane_s32(a, b, v, lane); }
[[gnu::always_inline]] nce int64x2_t multiply_double_add_saturate_long(int64x2_t a, int32x2_t b, int32_t c) { return vqdmlal_n_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_double_subtract_saturate_long(int64x2_t a, int32x2_t b, int32_t c) { return vqdmlsl_n_s32(a, b, c); }
[[gnu::always_inline]] nce poly8x16_t multiply(poly8x16_t a, poly8x16_t b) { return vmulq_p8(a, b); }
[[gnu::always_inline]] nce int64x1_t subtract(int64x1_t a, int64x1_t b) { return vsub_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract(int64x2_t a, int64x2_t b) { return vsubq_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract(int64x2_t a, int32x2_t b) { return vsubw_s32(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_narrow_high(int64x2_t a, int64x2_t b) { return vsubhn_s64(a, b); }
[[gnu::always_inline]] nce int32x2_t subtract_round_narrow_high(int64x2_t a, int64x2_t b) { return vrsubhn_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t subtract_saturate(int64x1_t a, int64x1_t b) { return vqsub_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_saturate(int64x2_t a, int64x2_t b) { return vqsubq_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t subtract_abs_add(int64x2_t a, int32x2_t b, int32x2_t c) { return vabal_s32(a, b, c); }
[[gnu::always_inline]] nce int64x1_t add_pairwise_accumulate_long(int64x1_t a, int32x2_t b) { return vpadal_s32(a, b); }
[[gnu::always_inline]] nce int64x2_t add_pairwise_accumulate_long(int64x2_t a, int32x4_t b) { return vpadalq_s32(a, b); }
[[gnu::always_inline]] nce uint8x16_t equal(poly8x16_t a, poly8x16_t b) { return vceqq_p8(a, b); }
[[gnu::always_inline]] nce uint8x16_t and_test_nonzero(poly8x16_t a, poly8x16_t b) { return vtstq_p8(a, b); }
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
template <int n>[[gnu::always_inline]] nce uint32x2_t qshrun(int64x2_t a) { return vqshrun_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t qshrn(int64x2_t a) { return vqshrn_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce uint32x2_t shift_right_unsigned_saturate_narrow(int64x2_t a) { return vqrshrun_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right_saturate_narrow(int64x2_t a) { return vqrshrn_n_s64(a, n); }
template <int n>[[gnu::always_inline]] nce int32x2_t shift_right_round_saturate_narrow(int64x2_t a) { return vrshrn_n_s64(a, n); }
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
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(int64x2_t a) { return vreinterpretq_s8_s64(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(int64x2_t a) { return vreinterpretq_s16_s64(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(int64x2_t a) { return vreinterpretq_s32_s64(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(int64x2_t a) { return vreinterpretq_f32_s64(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(int64x2_t a) { return vreinterpretq_u8_s64(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(int64x2_t a) { return vreinterpretq_u16_s64(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(int64x2_t a) { return vreinterpretq_u32_s64(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(int64x2_t a) { return vreinterpretq_p8_s64(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(int64x2_t a) { return vreinterpretq_p16_s64(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(int64x2_t a) { return vreinterpretq_u64_s64(a); }
[[gnu::always_inline]] nce int32x2_t move_narrow(int64x2_t a) { return vmovn_s64(a); }
[[gnu::always_inline]] nce int32x2_t move_saturate_narrow(int64x2_t a) { return vqmovn_s64(a); }
[[gnu::always_inline]] nce uint32x2_t move_unsigned_saturate_narrow(int64x2_t a) { return vqmovun_s64(a); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_add_long(int64x2_t a, int32x2_t b, int32x2_t v) { return vmlal_lane_s32(a, b, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t multiply_subtract_long(int64x2_t a, int32x2_t b, int32x2_t v) { return vmlsl_lane_s32(a, b, v, lane); }
[[gnu::always_inline]] nce int64x2_t multiply_add_long(int64x2_t a, int32x2_t b, int32_t c) { return vmlal_n_s32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t multiply_subtract_long(int64x2_t a, int32x2_t b, int32_t c) { return vmlsl_n_s32(a, b, c); }
[[gnu::always_inline]] nce poly8x16_t not_bitwise(poly8x16_t a) { return vmvnq_p8(a); }
[[gnu::always_inline]] nce int64x1_t and_bitwise(int64x1_t a, int64x1_t b) { return vand_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t and_bitwise(int64x2_t a, int64x2_t b) { return vandq_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t or_bitwise(int64x1_t a, int64x1_t b) { return vorr_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t or_bitwise(int64x2_t a, int64x2_t b) { return vorrq_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t xor_bitwise(int64x1_t a, int64x1_t b) { return veor_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t xor_bitwise(int64x2_t a, int64x2_t b) { return veorq_s64(a, b); }
[[gnu::always_inline]] nce int64x1_t or_not_bitwise(int64x1_t a, int64x1_t b) { return vorn_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t or_not_bitwise(int64x2_t a, int64x2_t b) { return vornq_s64(a, b); }
[[gnu::always_inline]] nce poly8x16_t count_active_bits(poly8x16_t a) { return vcntq_p8(a); }
[[gnu::always_inline]] nce int64x1_t clear_bitwise(int64x1_t a, int64x1_t b) { return vbic_s64(a, b); }
[[gnu::always_inline]] nce int64x2_t clear_bitwise(int64x2_t a, int64x2_t b) { return vbicq_s64(a, b); }
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
template <> [[gnu::always_inline]] nce int8x8_t duplicate_element(int8_t value) { return vdup_n_s8(value); }
template <> [[gnu::always_inline]] nce int8x16_t duplicate_element(int8_t value) { return vdupq_n_s8(value); }
template <> [[gnu::always_inline]] nce int16x4_t duplicate_element(int16_t value) { return vdup_n_s16(value); }
template <> [[gnu::always_inline]] nce int16x8_t duplicate_element(int16_t value) { return vdupq_n_s16(value); }
template <> [[gnu::always_inline]] nce int32x2_t duplicate_element(int32_t value) { return vdup_n_s32(value); }
template <> [[gnu::always_inline]] nce int32x4_t duplicate_element(int32_t value) { return vdupq_n_s32(value); }
template <> [[gnu::always_inline]] nce int64x1_t duplicate_element(int64_t value) { return vdup_n_s64(value); }
template <> [[gnu::always_inline]] nce int64x2_t duplicate_element(int64_t value) { return vdupq_n_s64(value); }
template <> [[gnu::always_inline]] nce uint8x8_t duplicate_element(uint8_t value) { return vdup_n_u8(value); }
template <> [[gnu::always_inline]] nce uint8x16_t duplicate_element(uint8_t value) { return vdupq_n_u8(value); }
template <> [[gnu::always_inline]] nce uint16x4_t duplicate_element(uint16_t value) { return vdup_n_u16(value); }
template <> [[gnu::always_inline]] nce uint16x8_t duplicate_element(uint16_t value) { return vdupq_n_u16(value); }
template <> [[gnu::always_inline]] nce uint32x2_t duplicate_element(uint32_t value) { return vdup_n_u32(value); }
template <> [[gnu::always_inline]] nce uint32x4_t duplicate_element(uint32_t value) { return vdupq_n_u32(value); }
template <> [[gnu::always_inline]] nce uint64x1_t duplicate_element(uint64_t value) { return vdup_n_u64(value); }
template <> [[gnu::always_inline]] nce uint64x2_t duplicate_element(uint64_t value) { return vdupq_n_u64(value); }
template <> [[gnu::always_inline]] nce float32x2_t duplicate_element(float32_t value) { return vdup_n_f32(value); }
template <> [[gnu::always_inline]] nce float32x4_t duplicate_element(float32_t value) { return vdupq_n_f32(value); }
template <> [[gnu::always_inline]] nce poly8x8_t duplicate_element(poly8_t value) { return vdup_n_p8(value); }
template <> [[gnu::always_inline]] nce poly8x16_t duplicate_element(poly8_t value) { return vdupq_n_p8(value); }
template <> [[gnu::always_inline]] nce poly16x4_t duplicate_element(poly16_t value) { return vdup_n_p16(value); }
template <> [[gnu::always_inline]] nce poly16x8_t duplicate_element(poly16_t value) { return vdupq_n_p16(value); }
template <> [[gnu::always_inline]] nce int8x8_t move(int8_t value) { return vmov_n_s8(value); }
template <> [[gnu::always_inline]] nce int8x16_t move(int8_t value) { return vmovq_n_s8(value); }
template <> [[gnu::always_inline]] nce int16x4_t move(int16_t value) { return vmov_n_s16(value); }
template <> [[gnu::always_inline]] nce int16x8_t move(int16_t value) { return vmovq_n_s16(value); }
template <> [[gnu::always_inline]] nce int32x2_t move(int32_t value) { return vmov_n_s32(value); }
template <> [[gnu::always_inline]] nce int32x4_t move(int32_t value) { return vmovq_n_s32(value); }
template <> [[gnu::always_inline]] nce int64x1_t move(int64_t value) { return vmov_n_s64(value); }
template <> [[gnu::always_inline]] nce int64x2_t move(int64_t value) { return vmovq_n_s64(value); }
template <> [[gnu::always_inline]] nce uint8x8_t move(uint8_t value) { return vmov_n_u8(value); }
template <> [[gnu::always_inline]] nce uint8x16_t move(uint8_t value) { return vmovq_n_u8(value); }
template <> [[gnu::always_inline]] nce uint16x4_t move(uint16_t value) { return vmov_n_u16(value); }
template <> [[gnu::always_inline]] nce uint16x8_t move(uint16_t value) { return vmovq_n_u16(value); }
template <> [[gnu::always_inline]] nce uint32x2_t move(uint32_t value) { return vmov_n_u32(value); }
template <> [[gnu::always_inline]] nce uint32x4_t move(uint32_t value) { return vmovq_n_u32(value); }
template <> [[gnu::always_inline]] nce uint64x1_t move(uint64_t value) { return vmov_n_u64(value); }
template <> [[gnu::always_inline]] nce uint64x2_t move(uint64_t value) { return vmovq_n_u64(value); }
template <> [[gnu::always_inline]] nce float32x2_t move(float32_t value) { return vmov_n_f32(value); }
template <> [[gnu::always_inline]] nce float32x4_t move(float32_t value) { return vmovq_n_f32(value); }
template <> [[gnu::always_inline]] nce poly8x8_t move(poly8_t value) { return vmov_n_p8(value); }
template <> [[gnu::always_inline]] nce poly8x16_t move(poly8_t value) { return vmovq_n_p8(value); }
template <> [[gnu::always_inline]] nce poly16x4_t move(poly16_t value) { return vmov_n_p16(value); }
template <> [[gnu::always_inline]] nce poly16x8_t move(poly16_t value) { return vmovq_n_p16(value); }
template <int lane>[[gnu::always_inline]] nce int64x1_t duplicate_element(int64x1_t vec) { return vdup_lane_s64(vec, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t duplicate_element(int64x1_t vec) { return vdupq_lane_s64(vec, lane); }
[[gnu::always_inline]] nce int64x2_t combine(int64x1_t low, int64x1_t high) { return vcombine_s64(low, high); }
[[gnu::always_inline]] nce int64x1_t get_high(int64x2_t a) { return vget_high_s64(a); }
[[gnu::always_inline]] nce poly8x8_t get_high(poly8x16_t a) { return vget_high_p8(a); }
[[gnu::always_inline]] nce poly16x4_t get_high(poly16x8_t a) { return vget_high_p16(a); }
[[gnu::always_inline]] nce int64x1_t get_low(int64x2_t a) { return vget_low_s64(a); }
[[gnu::always_inline]] nce poly8x8_t get_low(poly8x16_t a) { return vget_low_p8(a); }
[[gnu::always_inline]] nce poly16x4_t get_low(poly16x8_t a) { return vget_low_p16(a); }
template <int lane>[[gnu::always_inline]] nce int64_t get(int64x1_t v) { return vget_lane_s64(v, lane); }
template <int lane>[[gnu::always_inline]] nce int64_t get(int64x2_t v) { return vgetq_lane_s64(v, lane); }
template <int lane>[[gnu::always_inline]] nce poly8_t get(poly8x16_t v) { return vgetq_lane_p8(v, lane); }
template <int lane>[[gnu::always_inline]] nce poly16_t get(poly16x8_t v) { return vgetq_lane_p16(v, lane); }
template <int n>[[gnu::always_inline]] nce int64x1_t extract(int64x1_t a, int64x1_t b) { return vext_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce int64x2_t extract(int64x2_t a, int64x2_t b) { return vextq_s64(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly8x16_t extract(poly8x16_t a, poly8x16_t b) { return vextq_p8(a, b, n); }
template <int n>[[gnu::always_inline]] nce poly16x8_t extract(poly16x8_t a, poly16x8_t b) { return vextq_p16(a, b, n); }
[[gnu::always_inline]] nce poly8x16_t reverse_64bit(poly8x16_t vec) { return vrev64q_p8(vec); }
[[gnu::always_inline]] nce poly16x8_t reverse_64bit(poly16x8_t vec) { return vrev64q_p16(vec); }
[[gnu::always_inline]] nce poly8x16_t reverse_32bit(poly8x16_t vec) { return vrev32q_p8(vec); }
[[gnu::always_inline]] nce poly16x8_t reverse_32bit(poly16x8_t vec) { return vrev32q_p16(vec); }
[[gnu::always_inline]] nce poly8x16_t reverse_16bit(poly8x16_t vec) { return vrev16q_p8(vec); }
[[gnu::always_inline]] nce poly8x16x2_t zip(poly8x16_t a, poly8x16_t b) { return vzipq_p8(a, b); }
[[gnu::always_inline]] nce poly16x8x2_t zip(poly16x8_t a, poly16x8_t b) { return vzipq_p16(a, b); }
[[gnu::always_inline]] nce poly8x16x2_t unzip(poly8x16_t a, poly8x16_t b) { return vuzpq_p8(a, b); }
[[gnu::always_inline]] nce poly16x8x2_t unzip(poly16x8_t a, poly16x8_t b) { return vuzpq_p16(a, b); }
[[gnu::always_inline]] nce poly8x16x2_t transpose(poly8x16_t a, poly8x16_t b) { return vtrnq_p8(a, b); }
[[gnu::always_inline]] nce poly16x8x2_t transpose(poly16x8_t a, poly16x8_t b) { return vtrnq_p16(a, b); }
template <int lane>[[gnu::always_inline]] nce uint8x8_t set(uint8_t a, uint8x8_t v) { return vset_lane_u8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t set(uint16_t a, uint16x4_t v) { return vset_lane_u16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t set(uint32_t a, uint32x2_t v) { return vset_lane_u32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x1_t set(uint64_t a, uint64x1_t v) { return vset_lane_u64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int8x8_t set(int8_t a, int8x8_t v) { return vset_lane_s8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t set(int16_t a, int16x4_t v) { return vset_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t set(int32_t a, int32x2_t v) { return vset_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x1_t set(int64_t a, int64x1_t v) { return vset_lane_s64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8_t set(poly8_t a, poly8x8_t v) { return vset_lane_p8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4_t set(poly16_t a, poly16x4_t v) { return vset_lane_p16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t set(float32_t a, float32x2_t v) { return vset_lane_f32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16_t set(uint8_t a, uint8x16_t v) { return vsetq_lane_u8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t set(uint16_t a, uint16x8_t v) { return vsetq_lane_u16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t set(uint32_t a, uint32x4_t v) { return vsetq_lane_u32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t set(uint64_t a, uint64x2_t v) { return vsetq_lane_u64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16_t set(int8_t a, int8x16_t v) { return vsetq_lane_s8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t set(int16_t a, int16x8_t v) { return vsetq_lane_s16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t set(int32_t a, int32x4_t v) { return vsetq_lane_s32(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t set(int64_t a, int64x2_t v) { return vsetq_lane_s64(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x16_t set(poly8_t a, poly8x16_t v) { return vsetq_lane_p8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8_t set(poly16_t a, poly16x8_t v) { return vsetq_lane_p16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t set(float32_t a, float32x4_t v) { return vsetq_lane_f32(a, v, lane); }
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
template <int lane>[[gnu::always_inline]] nce int8x8_t load1(int8_t const *ptr, int8x8_t src) { return vld1_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x16_t load1(int8_t const *ptr, int8x16_t src) { return vld1q_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4_t load1(int16_t const *ptr, int16x4_t src) { return vld1_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8_t load1(int16_t const *ptr, int16x8_t src) { return vld1q_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2_t load1(int32_t const *ptr, int32x2_t src) { return vld1_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4_t load1(int32_t const *ptr, int32x4_t src) { return vld1q_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x1_t load1(int64_t const *ptr, int64x1_t src) { return vld1_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int64x2_t load1(int64_t const *ptr, int64x2_t src) { return vld1q_lane_s64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x8_t load1(uint8_t const *ptr, uint8x8_t src) { return vld1_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x16_t load1(uint8_t const *ptr, uint8x16_t src) { return vld1q_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4_t load1(uint16_t const *ptr, uint16x4_t src) { return vld1_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8_t load1(uint16_t const *ptr, uint16x8_t src) { return vld1q_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2_t load1(uint32_t const *ptr, uint32x2_t src) { return vld1_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4_t load1(uint32_t const *ptr, uint32x4_t src) { return vld1q_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x1_t load1(uint64_t const *ptr, uint64x1_t src) { return vld1_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint64x2_t load1(uint64_t const *ptr, uint64x2_t src) { return vld1q_lane_u64(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2_t load1(float32_t const *ptr, float32x2_t src) { return vld1_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4_t load1(float32_t const *ptr, float32x4_t src) { return vld1q_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8_t load1(poly8_t const *ptr, poly8x8_t src) { return vld1_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x16_t load1(poly8_t const *ptr, poly8x16_t src) { return vld1q_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4_t load1(poly16_t const *ptr, poly16x4_t src) { return vld1_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8_t load1(poly16_t const *ptr, poly16x8_t src) { return vld1q_lane_p16(ptr, src, lane); }
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
[[gnu::always_inline]] inline int64x1x2_t load2(int64_t const *ptr) { return vld2_s64(ptr); }
[[gnu::always_inline]] inline uint64x1x2_t load2(uint64_t const *ptr) { return vld2_u64(ptr); }
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
[[gnu::always_inline]] inline int64x1x3_t load3(int64_t const *ptr) { return vld3_s64(ptr); }
[[gnu::always_inline]] inline uint64x1x3_t load3(uint64_t const *ptr) { return vld3_u64(ptr); }
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
[[gnu::always_inline]] inline int64x1x4_t load4(int64_t const *ptr) { return vld4_s64(ptr); }
[[gnu::always_inline]] inline uint64x1x4_t load4(uint64_t const *ptr) { return vld4_u64(ptr); }
template <> [[gnu::always_inline]] inline int8x8x2_t load2_duplicate(int8_t const *ptr) { return vld2_dup_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x4x2_t load2_duplicate(int16_t const *ptr) { return vld2_dup_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x2x2_t load2_duplicate(int32_t const *ptr) { return vld2_dup_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x2_t load2_duplicate(uint8_t const *ptr) { return vld2_dup_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x2_t load2_duplicate(uint16_t const *ptr) { return vld2_dup_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x2_t load2_duplicate(uint32_t const *ptr) { return vld2_dup_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x2x2_t load2_duplicate(float32_t const *ptr) { return vld2_dup_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x2_t load2_duplicate(poly8_t const *ptr) { return vld2_dup_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x2_t load2_duplicate(poly16_t const *ptr) { return vld2_dup_p16(ptr); }
[[gnu::always_inline]] inline int64x1x2_t load2_duplicate(int64_t const *ptr) { return vld2_dup_s64(ptr); }
[[gnu::always_inline]] inline uint64x1x2_t load2_duplicate(uint64_t const *ptr) { return vld2_dup_u64(ptr); }
template <> [[gnu::always_inline]] inline int8x8x3_t load3_duplicate(int8_t const *ptr) { return vld3_dup_s8(ptr); }
template <> [[gnu::always_inline]] inline int16x4x3_t load3_duplicate(int16_t const *ptr) { return vld3_dup_s16(ptr); }
template <> [[gnu::always_inline]] inline int32x2x3_t load3_duplicate(int32_t const *ptr) { return vld3_dup_s32(ptr); }
template <> [[gnu::always_inline]] inline uint8x8x3_t load3_duplicate(uint8_t const *ptr) { return vld3_dup_u8(ptr); }
template <> [[gnu::always_inline]] inline uint16x4x3_t load3_duplicate(uint16_t const *ptr) { return vld3_dup_u16(ptr); }
template <> [[gnu::always_inline]] inline uint32x2x3_t load3_duplicate(uint32_t const *ptr) { return vld3_dup_u32(ptr); }
template <> [[gnu::always_inline]] inline float32x2x3_t load3_duplicate(float32_t const *ptr) { return vld3_dup_f32(ptr); }
template <> [[gnu::always_inline]] inline poly8x8x3_t load3_duplicate(poly8_t const *ptr) { return vld3_dup_p8(ptr); }
template <> [[gnu::always_inline]] inline poly16x4x3_t load3_duplicate(poly16_t const *ptr) { return vld3_dup_p16(ptr); }
[[gnu::always_inline]] inline int64x1x3_t load3_duplicate(int64_t const *ptr) { return vld3_dup_s64(ptr); }
[[gnu::always_inline]] inline uint64x1x3_t load3_duplicate(uint64_t const *ptr) { return vld3_dup_u64(ptr); }
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
template <int lane>[[gnu::always_inline]] nce int16x4x2_t load2(int16_t const *ptr, int16x4x2_t src) { return vld2_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8x2_t load2(int16_t const *ptr, int16x8x2_t src) { return vld2q_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2x2_t load2(int32_t const *ptr, int32x2x2_t src) { return vld2_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4x2_t load2(int32_t const *ptr, int32x4x2_t src) { return vld2q_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4x2_t load2(uint16_t const *ptr, uint16x4x2_t src) { return vld2_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8x2_t load2(uint16_t const *ptr, uint16x8x2_t src) { return vld2q_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2x2_t load2(uint32_t const *ptr, uint32x2x2_t src) { return vld2_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4x2_t load2(uint32_t const *ptr, uint32x4x2_t src) { return vld2q_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2x2_t load2(float32_t const *ptr, float32x2x2_t src) { return vld2_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4x2_t load2(float32_t const *ptr, float32x4x2_t src) { return vld2q_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4x2_t load2(poly16_t const *ptr, poly16x4x2_t src) { return vld2_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8x2_t load2(poly16_t const *ptr, poly16x8x2_t src) { return vld2q_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x8x2_t load2(int8_t const *ptr, int8x8x2_t src) { return vld2_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x8x2_t load2(uint8_t const *ptr, uint8x8x2_t src) { return vld2_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8x2_t load2(poly8_t const *ptr, poly8x8x2_t src) { return vld2_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4x3_t load3(int16_t const *ptr, int16x4x3_t src) { return vld3_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8x3_t load3(int16_t const *ptr, int16x8x3_t src) { return vld3q_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2x3_t load3(int32_t const *ptr, int32x2x3_t src) { return vld3_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4x3_t load3(int32_t const *ptr, int32x4x3_t src) { return vld3q_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4x3_t load3(uint16_t const *ptr, uint16x4x3_t src) { return vld3_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8x3_t load3(uint16_t const *ptr, uint16x8x3_t src) { return vld3q_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2x3_t load3(uint32_t const *ptr, uint32x2x3_t src) { return vld3_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4x3_t load3(uint32_t const *ptr, uint32x4x3_t src) { return vld3q_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2x3_t load3(float32_t const *ptr, float32x2x3_t src) { return vld3_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4x3_t load3(float32_t const *ptr, float32x4x3_t src) { return vld3q_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4x3_t load3(poly16_t const *ptr, poly16x4x3_t src) { return vld3_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8x3_t load3(poly16_t const *ptr, poly16x8x3_t src) { return vld3q_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x8x3_t load3(int8_t const *ptr, int8x8x3_t src) { return vld3_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x8x3_t load3(uint8_t const *ptr, uint8x8x3_t src) { return vld3_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8x3_t load3(poly8_t const *ptr, poly8x8x3_t src) { return vld3_lane_p8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x4x4_t load4(int16_t const *ptr, int16x4x4_t src) { return vld4_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int16x8x4_t load4(int16_t const *ptr, int16x8x4_t src) { return vld4q_lane_s16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x2x4_t load4(int32_t const *ptr, int32x2x4_t src) { return vld4_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int32x4x4_t load4(int32_t const *ptr, int32x4x4_t src) { return vld4q_lane_s32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x4x4_t load4(uint16_t const *ptr, uint16x4x4_t src) { return vld4_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint16x8x4_t load4(uint16_t const *ptr, uint16x8x4_t src) { return vld4q_lane_u16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x2x4_t load4(uint32_t const *ptr, uint32x2x4_t src) { return vld4_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint32x4x4_t load4(uint32_t const *ptr, uint32x4x4_t src) { return vld4q_lane_u32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x2x4_t load4(float32_t const *ptr, float32x2x4_t src) { return vld4_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float32x4x4_t load4(float32_t const *ptr, float32x4x4_t src) { return vld4q_lane_f32(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x4x4_t load4(poly16_t const *ptr, poly16x4x4_t src) { return vld4_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly16x8x4_t load4(poly16_t const *ptr, poly16x8x4_t src) { return vld4q_lane_p16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce int8x8x4_t load4(int8_t const *ptr, int8x8x4_t src) { return vld4_lane_s8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce uint8x8x4_t load4(uint8_t const *ptr, uint8x8x4_t src) { return vld4_lane_u8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce poly8x8x4_t load4(poly8_t const *ptr, poly8x8x4_t src) { return vld4_lane_p8(ptr, src, lane); }
#ifdef __clang__
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
template <> [[gnu::always_inline]] inline int8x16x3_t load1_x3(int8_t const *ptr) { return vld1q_s8_x3(ptr); }
template <> [[gnu::always_inline]] inline int16x4x3_t load1_x3(int16_t const *ptr) { return vld1_s16_x3(ptr); }
template <> [[gnu::always_inline]] inline int16x8x3_t load1_x3(int16_t const *ptr) { return vld1q_s16_x3(ptr); }
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
template <> [[gnu::always_inline]] inline int8x16x4_t load1_x4(int8_t const *ptr) { return vld1q_s8_x4(ptr); }
template <> [[gnu::always_inline]] inline int16x4x4_t load1_x4(int16_t const *ptr) { return vld1_s16_x4(ptr); }
template <> [[gnu::always_inline]] inline int16x8x4_t load1_x4(int16_t const *ptr) { return vld1q_s16_x4(ptr); }
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
#endif
[[gnu::always_inline]] inline void store1(int8_t *ptr, int8x8_t val) { return vst1_s8(ptr, val); }
[[gnu::always_inline]] inline void store1(int8_t *ptr, int8x16_t val) { return vst1q_s8(ptr, val); }
[[gnu::always_inline]] inline void store1(int16_t *ptr, int16x4_t val) { return vst1_s16(ptr, val); }
[[gnu::always_inline]] inline void store1(int16_t *ptr, int16x8_t val) { return vst1q_s16(ptr, val); }
[[gnu::always_inline]] inline void store1(int32_t *ptr, int32x2_t val) { return vst1_s32(ptr, val); }
[[gnu::always_inline]] inline void store1(int32_t *ptr, int32x4_t val) { return vst1q_s32(ptr, val); }
[[gnu::always_inline]] inline void store1(int64_t *ptr, int64x1_t val) { return vst1_s64(ptr, val); }
[[gnu::always_inline]] inline void store1(int64_t *ptr, int64x2_t val) { return vst1q_s64(ptr, val); }
[[gnu::always_inline]] inline void store1(uint8_t *ptr, uint8x8_t val) { return vst1_u8(ptr, val); }
[[gnu::always_inline]] inline void store1(uint8_t *ptr, uint8x16_t val) { return vst1q_u8(ptr, val); }
[[gnu::always_inline]] inline void store1(uint16_t *ptr, uint16x4_t val) { return vst1_u16(ptr, val); }
[[gnu::always_inline]] inline void store1(uint16_t *ptr, uint16x8_t val) { return vst1q_u16(ptr, val); }
[[gnu::always_inline]] inline void store1(uint32_t *ptr, uint32x2_t val) { return vst1_u32(ptr, val); }
[[gnu::always_inline]] inline void store1(uint32_t *ptr, uint32x4_t val) { return vst1q_u32(ptr, val); }
[[gnu::always_inline]] inline void store1(uint64_t *ptr, uint64x1_t val) { return vst1_u64(ptr, val); }
[[gnu::always_inline]] inline void store1(uint64_t *ptr, uint64x2_t val) { return vst1q_u64(ptr, val); }
[[gnu::always_inline]] inline void store1(float32_t *ptr, float32x2_t val) { return vst1_f32(ptr, val); }
[[gnu::always_inline]] inline void store1(float32_t *ptr, float32x4_t val) { return vst1q_f32(ptr, val); }
[[gnu::always_inline]] inline void store1(poly8_t *ptr, poly8x8_t val) { return vst1_p8(ptr, val); }
[[gnu::always_inline]] inline void store1(poly8_t *ptr, poly8x16_t val) { return vst1q_p8(ptr, val); }
[[gnu::always_inline]] inline void store1(poly16_t *ptr, poly16x4_t val) { return vst1_p16(ptr, val); }
[[gnu::always_inline]] inline void store1(poly16_t *ptr, poly16x8_t val) { return vst1q_p16(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store1(int8_t *ptr, int8x8_t val) { return vst1_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(int8_t *ptr, int8x16_t val) { return vst1q_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(int16_t *ptr, int16x4_t val) { return vst1_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(int16_t *ptr, int16x8_t val) { return vst1q_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(int32_t *ptr, int32x2_t val) { return vst1_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(int32_t *ptr, int32x4_t val) { return vst1q_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(int64_t *ptr, int64x1_t val) { return vst1_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(int64_t *ptr, int64x2_t val) { return vst1q_lane_s64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(uint8_t *ptr, uint8x8_t val) { return vst1_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(uint8_t *ptr, uint8x16_t val) { return vst1q_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(uint16_t *ptr, uint16x4_t val) { return vst1_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(uint16_t *ptr, uint16x8_t val) { return vst1q_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(uint32_t *ptr, uint32x2_t val) { return vst1_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(uint32_t *ptr, uint32x4_t val) { return vst1q_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(uint64_t *ptr, uint64x1_t val) { return vst1_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(uint64_t *ptr, uint64x2_t val) { return vst1q_lane_u64(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(float32_t *ptr, float32x2_t val) { return vst1_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(float32_t *ptr, float32x4_t val) { return vst1q_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(poly8_t *ptr, poly8x8_t val) { return vst1_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(poly8_t *ptr, poly8x16_t val) { return vst1q_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(poly16_t *ptr, poly16x4_t val) { return vst1_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1(poly16_t *ptr, poly16x8_t val) { return vst1q_lane_p16(ptr, val, lane); }
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
template <int lane>[[gnu::always_inline]] nce void store2(int8_t *ptr, int8x8x2_t val) { return vst2_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(uint8_t *ptr, uint8x8x2_t val) { return vst2_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(poly8_t *ptr, poly8x8x2_t val) { return vst2_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(int8_t *ptr, int8x8x3_t val) { return vst3_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(uint8_t *ptr, uint8x8x3_t val) { return vst3_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(poly8_t *ptr, poly8x8x3_t val) { return vst3_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(int8_t *ptr, int8x8x4_t val) { return vst4_lane_s8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(uint8_t *ptr, uint8x8x4_t val) { return vst4_lane_u8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(poly8_t *ptr, poly8x8x4_t val) { return vst4_lane_p8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(int16_t *ptr, int16x4x2_t val) { return vst2_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(int16_t *ptr, int16x8x2_t val) { return vst2q_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(int32_t *ptr, int32x2x2_t val) { return vst2_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(int32_t *ptr, int32x4x2_t val) { return vst2q_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(uint16_t *ptr, uint16x4x2_t val) { return vst2_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(uint16_t *ptr, uint16x8x2_t val) { return vst2q_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(uint32_t *ptr, uint32x2x2_t val) { return vst2_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(uint32_t *ptr, uint32x4x2_t val) { return vst2q_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(float32_t *ptr, float32x2x2_t val) { return vst2_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(float32_t *ptr, float32x4x2_t val) { return vst2q_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(poly16_t *ptr, poly16x4x2_t val) { return vst2_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2(poly16_t *ptr, poly16x8x2_t val) { return vst2q_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(int16_t *ptr, int16x4x3_t val) { return vst3_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(int16_t *ptr, int16x8x3_t val) { return vst3q_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(int32_t *ptr, int32x2x3_t val) { return vst3_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(int32_t *ptr, int32x4x3_t val) { return vst3q_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(uint16_t *ptr, uint16x4x3_t val) { return vst3_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(uint16_t *ptr, uint16x8x3_t val) { return vst3q_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(uint32_t *ptr, uint32x2x3_t val) { return vst3_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(uint32_t *ptr, uint32x4x3_t val) { return vst3q_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(float32_t *ptr, float32x2x3_t val) { return vst3_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(float32_t *ptr, float32x4x3_t val) { return vst3q_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(poly16_t *ptr, poly16x4x3_t val) { return vst3_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3(poly16_t *ptr, poly16x8x3_t val) { return vst3q_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(int16_t *ptr, int16x4x4_t val) { return vst4_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(int16_t *ptr, int16x8x4_t val) { return vst4q_lane_s16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(int32_t *ptr, int32x2x4_t val) { return vst4_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(int32_t *ptr, int32x4x4_t val) { return vst4q_lane_s32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(uint16_t *ptr, uint16x4x4_t val) { return vst4_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(uint16_t *ptr, uint16x8x4_t val) { return vst4q_lane_u16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(uint32_t *ptr, uint32x2x4_t val) { return vst4_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(uint32_t *ptr, uint32x4x4_t val) { return vst4q_lane_u32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(float32_t *ptr, float32x2x4_t val) { return vst4_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(float32_t *ptr, float32x4x4_t val) { return vst4q_lane_f32(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(poly16_t *ptr, poly16x4x4_t val) { return vst4_lane_p16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4(poly16_t *ptr, poly16x8x4_t val) { return vst4q_lane_p16(ptr, val, lane); }
#ifdef __clang__
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

#ifdef __aarch64__
[[gnu::always_inline]] nce float32x2_t divide(float32x2_t a, float32x2_t b) { return vdiv_f32(a, b); }
[[gnu::always_inline]] nce float32x4_t divide(float32x4_t a, float32x4_t b) { return vdivq_f32(a, b); }
[[gnu::always_inline]] nce float64x1_t divide(float64x1_t a, float64x1_t b) { return vdiv_f64(a, b); }
[[gnu::always_inline]] nce float64x2_t divide(float64x2_t a, float64x2_t b) { return vdivq_f64(a, b); }
#endif

}  // namespace neon
#undef nce
#pragma once
#include <arm_neon.h>


#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

namespace neon {
template <typename T>
struct make_unsigned;
template <typename T>
struct make_signed;

template <>
struct make_unsigned<int8x8_t> {
  using type = uint8x8_t;
};
template <>
struct make_unsigned<int8x16_t> {
  using type = uint8x16_t;
};

template <>
struct make_unsigned<uint8x8_t> {
  using type = uint8x8_t;
};
template <>
struct make_unsigned<uint8x16_t> {
  using type = uint8x16_t;
};

template <>
struct make_signed<uint8x8_t> {
  using type = int8x8_t;
};
template <>
struct make_signed<uint8x16_t> {
  using type = int8x16_t;
};

template <>
struct make_signed<int8x8_t> {
  using type = int8x8_t;
};
template <>
struct make_signed<int8x16_t> {
  using type = int8x16_t;
};

template <>
struct make_unsigned<int16x4_t> {
  using type = uint16x4_t;
};
template <>
struct make_unsigned<int16x8_t> {
  using type = uint16x8_t;
};

template <>
struct make_unsigned<uint16x4_t> {
  using type = uint16x4_t;
};
template <>
struct make_unsigned<uint16x8_t> {
  using type = uint16x8_t;
};

template <>
struct make_signed<uint16x4_t> {
  using type = int16x4_t;
};
template <>
struct make_signed<uint16x8_t> {
  using type = int16x8_t;
};

template <>
struct make_signed<int16x4_t> {
  using type = int16x4_t;
};
template <>
struct make_signed<int16x8_t> {
  using type = int16x8_t;
};

template <>
struct make_unsigned<int32x2_t> {
  using type = uint32x2_t;
};
template <>
struct make_unsigned<int32x4_t> {
  using type = uint32x4_t;
};

template <>
struct make_unsigned<uint32x2_t> {
  using type = uint32x2_t;
};
template <>
struct make_unsigned<uint32x4_t> {
  using type = uint32x4_t;
};

template <>
struct make_signed<uint32x2_t> {
  using type = int32x2_t;
};
template <>
struct make_signed<uint32x4_t> {
  using type = int32x4_t;
};

template <>
struct make_signed<int32x2_t> {
  using type = int32x2_t;
};
template <>
struct make_signed<int32x4_t> {
  using type = int32x4_t;
};

template <>
struct make_unsigned<int64x1_t> {
  using type = uint64x1_t;
};
template <>
struct make_unsigned<int64x2_t> {
  using type = uint64x2_t;
};

template <>
struct make_unsigned<uint64x1_t> {
  using type = uint64x1_t;
};
template <>
struct make_unsigned<uint64x2_t> {
  using type = uint64x2_t;
};

template <>
struct make_signed<uint64x1_t> {
  using type = int64x1_t;
};
template <>
struct make_signed<uint64x2_t> {
  using type = int64x2_t;
};

template <>
struct make_signed<int64x1_t> {
  using type = int64x1_t;
};
template <>
struct make_signed<int64x2_t> {
  using type = int64x2_t;
};

template <>
struct make_signed<float32x2_t> {
  using type = float32x2_t;
};
template <>
struct make_signed<float32x4_t> {
  using type = float32x4_t;
};

template <typename T>
struct NonVec;
template <>
struct NonVec<int8x8_t> {
  using type = int8_t;
};
template <>
struct NonVec<uint8x8_t> {
  using type = uint8_t;
};
template <>
struct NonVec<int16x4_t> {
  using type = int16_t;
};
template <>
struct NonVec<uint16x4_t> {
  using type = uint16_t;
};
template <>
struct NonVec<int32x2_t> {
  using type = int32_t;
};
template <>
struct NonVec<uint32x2_t> {
  using type = uint32_t;
};
template <>
struct NonVec<int64x1_t> {
  using type = int64_t;
};
template <>
struct NonVec<uint64x1_t> {
  using type = uint64_t;
};
template <>
struct NonVec<float32x2_t> {
  using type = float;
};

template <>
struct NonVec<int8x16_t> {
  using type = int8_t;
};
template <>
struct NonVec<uint8x16_t> {
  using type = uint8_t;
};
template <>
struct NonVec<int16x8_t> {
  using type = int16_t;
};
template <>
struct NonVec<uint16x8_t> {
  using type = uint16_t;
};
template <>
struct NonVec<int32x4_t> {
  using type = int32_t;
};
template <>
struct NonVec<uint32x4_t> {
  using type = uint32_t;
};
template <>
struct NonVec<int64x2_t> {
  using type = int64_t;
};
template <>
struct NonVec<uint64x2_t> {
  using type = uint64_t;
};
template <>
struct NonVec<float32x4_t> {
  using type = float;
};

template <typename T>
constexpr bool is_doubleword_v =
    std::is_same_v<T, uint8x8_t> || std::is_same_v<T, uint16x4_t> || std::is_same_v<T, uint32x2_t> ||
    std::is_same_v<T, uint64x1_t> || std::is_same_v<T, int8x8_t> || std::is_same_v<T, int16x4_t> ||
    std::is_same_v<T, int32x2_t> || std::is_same_v<T, int64x1_t> || std::is_same_v<T, float32x2_t>;

template <typename T>
constexpr bool is_quadword_v =
    std::is_same_v<T, uint8x16_t> || std::is_same_v<T, uint16x8_t> || std::is_same_v<T, uint32x4_t> ||
    std::is_same_v<T, uint64x2_t> || std::is_same_v<T, int8x16_t> || std::is_same_v<T, int16x8_t> ||
    std::is_same_v<T, int32x4_t> || std::is_same_v<T, int64x2_t> || std::is_same_v<T, float32x4_t>;

template <typename T>
concept is_doubleword = is_doubleword_v<T>;

template <typename T>
concept is_quadword = is_quadword_v<T>;

template <typename T>
concept is_vector_type = is_doubleword<T> || is_quadword<T>;

template <typename T>
nce auto get(T vec, const int i);

template <>
nce auto get(uint8x16_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    case 4:
      return neon::get<4>(vec);
    case 5:
      return neon::get<5>(vec);
    case 6:
      return neon::get<6>(vec);
    case 7:
      return neon::get<7>(vec);
    case 8:
      return neon::get<8>(vec);
    case 9:
      return neon::get<9>(vec);
    case 10:
      return neon::get<10>(vec);
    case 11:
      return neon::get<11>(vec);
    case 12:
      return neon::get<12>(vec);
    case 13:
      return neon::get<13>(vec);
    case 14:
      return neon::get<14>(vec);
    case 15:
      return neon::get<15>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(int8x16_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    case 4:
      return neon::get<4>(vec);
    case 5:
      return neon::get<5>(vec);
    case 6:
      return neon::get<6>(vec);
    case 7:
      return neon::get<7>(vec);
    case 8:
      return neon::get<8>(vec);
    case 9:
      return neon::get<9>(vec);
    case 10:
      return neon::get<10>(vec);
    case 11:
      return neon::get<11>(vec);
    case 12:
      return neon::get<12>(vec);
    case 13:
      return neon::get<13>(vec);
    case 14:
      return neon::get<14>(vec);
    case 15:
      return neon::get<15>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(uint8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    case 4:
      return neon::get<4>(vec);
    case 5:
      return neon::get<5>(vec);
    case 6:
      return neon::get<6>(vec);
    case 7:
      return neon::get<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(int8x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    case 4:
      return neon::get<4>(vec);
    case 5:
      return neon::get<5>(vec);
    case 6:
      return neon::get<6>(vec);
    case 7:
      return neon::get<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(uint16x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    case 4:
      return neon::get<4>(vec);
    case 5:
      return neon::get<5>(vec);
    case 6:
      return neon::get<6>(vec);
    case 7:
      return neon::get<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(int16x8_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    case 4:
      return neon::get<4>(vec);
    case 5:
      return neon::get<5>(vec);
    case 6:
      return neon::get<6>(vec);
    case 7:
      return neon::get<7>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(uint16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(int16x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(uint32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(int32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(float32x4_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    case 2:
      return neon::get<2>(vec);
    case 3:
      return neon::get<3>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(uint32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(int32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(uint64x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(int64x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(float32x2_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    case 1:
      return neon::get<1>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(uint64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce auto get(int64x1_t vec, const int i) {
  switch (i) {
    case 0:
      return neon::get<0>(vec);
    default:
      __builtin_unreachable();
  }
}

template <typename T>
nce T set(T vec, const int i, typename NonVec<T>::type a);

template <>
nce uint8x16_t set(uint8x16_t vec, const int i, uint8_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    case 4:
      return neon::set<4>(a, vec);
    case 5:
      return neon::set<5>(a, vec);
    case 6:
      return neon::set<6>(a, vec);
    case 7:
      return neon::set<7>(a, vec);
    case 8:
      return neon::set<8>(a, vec);
    case 9:
      return neon::set<9>(a, vec);
    case 10:
      return neon::set<10>(a, vec);
    case 11:
      return neon::set<11>(a, vec);
    case 12:
      return neon::set<12>(a, vec);
    case 13:
      return neon::set<13>(a, vec);
    case 14:
      return neon::set<14>(a, vec);
    case 15:
      return neon::set<15>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x16_t set(int8x16_t vec, const int i, int8_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    case 4:
      return neon::set<4>(a, vec);
    case 5:
      return neon::set<5>(a, vec);
    case 6:
      return neon::set<6>(a, vec);
    case 7:
      return neon::set<7>(a, vec);
    case 8:
      return neon::set<8>(a, vec);
    case 9:
      return neon::set<9>(a, vec);
    case 10:
      return neon::set<10>(a, vec);
    case 11:
      return neon::set<11>(a, vec);
    case 12:
      return neon::set<12>(a, vec);
    case 13:
      return neon::set<13>(a, vec);
    case 14:
      return neon::set<14>(a, vec);
    case 15:
      return neon::set<15>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint8x8_t set(uint8x8_t vec, const int i, uint8_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    case 4:
      return neon::set<4>(a, vec);
    case 5:
      return neon::set<5>(a, vec);
    case 6:
      return neon::set<6>(a, vec);
    case 7:
      return neon::set<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int8x8_t set(int8x8_t vec, const int i, int8_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    case 4:
      return neon::set<4>(a, vec);
    case 5:
      return neon::set<5>(a, vec);
    case 6:
      return neon::set<6>(a, vec);
    case 7:
      return neon::set<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x8_t set(uint16x8_t vec, const int i, uint16_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    case 4:
      return neon::set<4>(a, vec);
    case 5:
      return neon::set<5>(a, vec);
    case 6:
      return neon::set<6>(a, vec);
    case 7:
      return neon::set<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x8_t set(int16x8_t vec, const int i, int16_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    case 4:
      return neon::set<4>(a, vec);
    case 5:
      return neon::set<5>(a, vec);
    case 6:
      return neon::set<6>(a, vec);
    case 7:
      return neon::set<7>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint16x4_t set(uint16x4_t vec, const int i, uint16_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int16x4_t set(int16x4_t vec, const int i, int16_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x4_t set(uint32x4_t vec, const int i, uint32_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x4_t set(int32x4_t vec, const int i, int32_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x4_t set(float32x4_t vec, const int i, float32_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    case 2:
      return neon::set<2>(a, vec);
    case 3:
      return neon::set<3>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint32x2_t set(uint32x2_t vec, const int i, uint32_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int32x2_t set(int32x2_t vec, const int i, int32_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x2_t set(uint64x2_t vec, const int i, uint64_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x2_t set(int64x2_t vec, const int i, int64_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce float32x2_t set(float32x2_t vec, const int i, float32_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    case 1:
      return neon::set<1>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce uint64x1_t set(uint64x1_t vec, const int i, uint64_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    default:
      __builtin_unreachable();
  }
}

template <>
nce int64x1_t set(int64x1_t vec, const int i, int64_t a) {
  switch (i) {
    case 0:
      return neon::set<0>(a, vec);
    default:
      __builtin_unreachable();
  }
}

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

}  // namespace neon
#undef nce
#include <cassert>

#ifdef __clang__
#define ace [[gnu::always_inline]] constexpr
#else
#define ace [[gnu::always_inline]] inline
#endif

namespace argon {
namespace impl {
template <typename type>
struct Vec64 {};
template <typename type>
struct Vec128 {};

template <> struct Vec64<int8_t> {using type = int8x8_t; };
template <> struct Vec128<int8_t>  {using type = int8x16_t; };

template <> struct Vec64<uint8_t> {using type = uint8x8_t; };
template <> struct Vec128<uint8_t>  {using type = uint8x16_t; };

template <> struct Vec64<int16_t> {using type = int16x4_t; };
template <> struct Vec128<int16_t>  {using type = int16x8_t; };

template <> struct Vec64<uint16_t> {using type = uint16x4_t; };
template <> struct Vec128<uint16_t>  {using type = uint16x8_t; };

template <> struct Vec64<int32_t> {using type = int32x2_t; };
template <> struct Vec128<int32_t>  {using type = int32x4_t; };

template <> struct Vec64<uint32_t> {using type = uint32x2_t; };
template <> struct Vec128<uint32_t>  {using type = uint32x4_t; };

template <> struct Vec64<int64_t> {using type = int64x1_t; };
template <> struct Vec128<int64_t>  {using type = int64x2_t; };

template <> struct Vec64<uint64_t> {using type = uint64x1_t; };
template <> struct Vec128<uint64_t>  {using type = uint64x2_t; };

template <> struct Vec64<float> {using type = float32x2_t; };
template <> struct Vec128<float>  {using type = float32x4_t; };

template <typename T> struct NextLarger;
template <> struct NextLarger<int8_t> {using type = int16_t; };
template <> struct NextLarger<uint8_t> {using type = uint16_t; };
template <> struct NextLarger<int16_t> {using type = int32_t; };
template <> struct NextLarger<uint16_t> {using type = uint32_t; };
template <> struct NextLarger<int32_t> {using type = int64_t; };
template <> struct NextLarger<uint32_t> {using type = uint64_t; };
template <> struct NextLarger<float> {using type = double; };

template <typename T> struct Result;
template <> struct Result<int8x8_t> {using type = uint8x8_t; };
template <> struct Result<uint8x8_t> {using type = uint8x8_t; };
template <> struct Result<int16x4_t> {using type = uint16x4_t; };
template <> struct Result<uint16x4_t> {using type = uint16x4_t; };
template <> struct Result<int32x2_t> {using type = uint32x2_t; };
template <> struct Result<uint32x2_t> {using type = uint32x2_t; };
template <> struct Result<int8x16_t> {using type = uint8x16_t; };
template <> struct Result<uint8x16_t> {using type = uint8x16_t; };
template <> struct Result<int16x8_t> {using type = uint16x8_t; };
template <> struct Result<uint16x8_t> {using type = uint16x8_t; };
template <> struct Result<int32x4_t> {using type = uint32x4_t; };
template <> struct Result<uint32x4_t> {using type = uint32x4_t; };
template <> struct Result<int64x1_t> {using type = uint64x1_t; };
template <> struct Result<uint64x1_t> {using type = uint64x1_t; };
template <> struct Result<int64x2_t> {using type = uint64x2_t; };
template <> struct Result<uint64x2_t> {using type = uint64x2_t; };
template <> struct Result<float32x2_t> {using type = uint32x2_t; };
template <> struct Result<float32x4_t> {using type = uint32x4_t; };


template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename vector_type>
class FloatCommon {
  using base_type = neon::NonVec<vector_type>::type;

 public:
  using T = FloatCommon<vector_type>;
};

template <typename vector_type>
class Lane;

template <typename vector_type>
class Common {
  using base_type = neon::NonVec<vector_type>::type;
  using result_type = Result<vector_type>::type;

 public:
  using T = Common<vector_type>;
  static constexpr size_t lanes = (neon::is_quadword_v<vector_type> ? 16 : 8) / sizeof(base_type);

  constexpr Common() : vec_{0} {};
  constexpr Common(vector_type vector) : vec_(vector){};
  ace Common(base_type base) : vec_(LoadCopy(base)){};
  ace Common(base_type const* base_ptr) : vec_(Load(base_ptr)){};
  ace Common(std::span<base_type> slice) : vec_(Load(slice.data())){
    static_assert(slice.size() == lanes);
  };
  ace Common(std::initializer_list<base_type> value_list) : vec_(Load(value_list.begin())) {};

  ace T operator=(base_type b) { return vec_ = LoadCopy(b); }

  ace T operator-() const { return Negate(); }

  ace T operator+(T b) const { return Add(b); }
  ace T operator-(T b) const { return Subtract(b); }
  ace T operator*(T b) const { return Multiply(b); }
  ace T operator/(T b) const { return Divide(b); }

  ace T operator+=(T b) { return vec_ = Add(b); }
  ace T operator-=(T b) { return vec_ = Subtract(b); }
  ace T operator*=(T b) { return vec_ = Multiply(b); }
  ace T operator/=(T b) { return vec_ = Divide(b); }

  ace Common<result_type> operator==(T b) const { return Equal(b); }
  ace Common<result_type> operator<(T b) const { return LessThan(b); }
  ace Common<result_type> operator>(T b) const { return GreaterThan(b); }
  ace Common<result_type> operator<=(T b) const { return LessThanOrEqual(b); }
  ace Common<result_type> operator>=(T b) const { return GreaterThanOrEqual(b); }

  ace T operator++() const { return Add(1); }
  ace T operator--() const { return Subtract(1); }

  ace T operator&(T b) const { return AndBitwise(b); }
  ace T operator|(T b) const { return OrBitwise(b); }
  ace T operator^(T b) const { return XorBitwise(b); }
  ace T operator~() const { return NotBitwise(); }

  ace Lane<vector_type> operator[](const int i) const { return Lane{vec_, i}; }

  ace T operator>>(const int i) const { return ShiftRight(i); }
  ace T operator<<(const int i) const { return ShiftLeft(i); }

  [[gnu::always_inline]] constexpr operator vector_type() const { return vec_; }

  ace std::array<base_type, lanes> as_array() {
    std::array<base_type, lanes> out{0};
    Store(out.data());
    return out;
  }

  ace vector_type vec() const { return vec_; }

  ace base_type Get(const int i) const { return neon::get<vector_type>(vec_, i); }

  ace base_type Set(const int i, base_type b) const { return neon::set(vec_, i, b); }

  ace T ShiftRight(const int i) const { return neon::shift_right(vec_, i); }

  ace T ShiftLeft(const int i) const { return neon::shift_left(vec_, i); }

  ace T Negate() const { return neon::negate(vec_); }

  ace T Add(T b) const { return neon::add(vec_, b); }

  ace T AddHalve(T b) const { return neon::add_halve(vec_, b); }

  ace T AddHalveRound(T b) const { return neon::add_halve_round(vec_, b); }

  ace T AddSaturate(T b) const { return neon::add_saturate(vec_, b); }

  ace T Multiply(T b) const { return neon::multiply(vec_, b); }

  ace T MultiplyAdd(T b, T c) const { return neon::multiply_add(vec_, b, c); }

  ace T MultiplySubtract(T b, T c) const { return neon::multiply_subtract(vec_, b, c); }

  ace T Subtract(T b) const { return neon::subtract(vec_, b); }

  ace T SubtractHigh(T b) const { return neon::subtract_high(vec_, b); }

  ace T SubtractSaturate(T b) const { return neon::subtract_saturate(vec_, b); }

  ace T SubtractAbs(T b) const { return neon::subtract_abs(vec_, b); }

  ace T SubtractAbsAdd(T b, T c) const { return neon::subtract_abs_add(vec_, b, c); }

  ace T Divide(T b) const requires std::floating_point<base_type> {
#ifdef __aarch64__
    return neon::divide(vec_, b);
#else
    return this->map2(b, [](base_type lane1, base_type lane2) {
        return lane1 / lane2;
    });
#endif
    }

  ace T Max(T b) const { return neon::max(vec_, b); }

  ace T Min(T b) const { return neon::min(vec_, b); }

  ace T AddPairwise(T b) const { return neon::add_pairwise(vec_, b); }

  ace T MaxPairwise(T b) const { return neon::max_pairwise(vec_, b); }

  ace T MinPairwise(T b) const { return neon::min_pairwise(vec_, b); }

  ace Common<result_type> Equal(T b) const { return neon::equal(vec_, b); }

  ace Common<result_type> GreaterThanOrEqual(T b) const { return neon::greater_than_or_equal(vec_, b); }

  ace Common<result_type> LessThanOrEqual(T b) const { return neon::less_than_or_equal(vec_, b); }

  ace Common<result_type> GreaterThan(T b) const { return neon::greater_than(vec_, b); }

  ace Common<result_type> LessThan(T b) const { return neon::less_than(vec_, b); }

  ace T AndTestNonzero(T b) const { return neon::and_test_nonzero(vec_, b); }

  ace T ShiftLeft(Common<typename neon::make_signed<vector_type>::type> b) const { return neon::shift_left(vec_, b); }

  ace T ShiftLeftSaturate(Common<typename neon::make_signed<vector_type>::type> b) const {
    return neon::shift_left_saturate(vec_, b);
  }

  template <int n>
  ace T ShiftLeftSaturate() const {
    return neon::shift_left_saturate<n>(vec_);
  }

  ace T ShiftLeftRound(T b) const { return neon::shift_left_round(vec_, b); }

  ace T ShiftLeftRoundSaturate(T b) const { return neon::shift_left_round_saturate(vec_, b); }

  template <int n>
  ace uint16x8_t ShiftLeftLong() const {
    return neon::shift_left_long<n>(vec_);
  }

  template <int n>
  ace T ShiftLeftInsert(T b) const {
    return neon::shift_left_insert<n>(vec_, b);
  }

  template <int n>
  ace T ShiftRight() const {
    return neon::shift_right<n>(vec_);
  }

  template <int n>
  ace T ShiftRightRound() const {
    return neon::shift_right_round<n>(vec_);
  }

  template <int n>
  ace T ShiftRightAccumulate(T b) const {
    return neon::shift_right_accumulate<n>(vec_, b);
  }

  template <int n>
  ace T ShiftRightAccumulateRound(T b) const {
    return neon::shift_right_accumulate_round<n>(vec_, b);
  }

  template <int n>
  ace T ShiftRightInsert(T b) const {
    return neon::shift_right_insert<n>(vec_, b);
  }

  ace static T Load(base_type const* ptr) { return neon::load1<vector_type>(ptr); }
  ace static T Load2(base_type const* ptr) { return neon::load2<vector_type>(ptr); }
  ace static T Load3(base_type const* ptr) { return neon::load3<vector_type>(ptr); }
  ace static T Load4(base_type const* ptr) { return neon::load4<vector_type>(ptr); }

  ace void Store(base_type* ptr) { neon::store1(ptr, vec_); }
  ace void Store2(base_type* ptr) { neon::store2(ptr, vec_); }
  ace void Store3(base_type* ptr) { neon::store3(ptr, vec_); }
  ace void Store4(base_type* ptr) { neon::store4(ptr, vec_); }

  template <int lane>
  ace void StoreLane(base_type* ptr) {
    neon::store1<lane>(ptr, vec_);
  }

  template <int lane>
  ace void StoreLane2(base_type* ptr) {
    neon::store2<lane>(ptr, vec_);
  }

  template <int lane>
  ace void StoreLane3(base_type* ptr) {
    neon::store3<lane>(ptr, vec_);
  }

  template <int lane>
  ace void StoreLane4(base_type* ptr) {
    neon::store4<lane>(ptr, vec_);
  }

  ace static T LoadCopy(base_type b) { return neon::duplicate_element<vector_type>(b); }
  ace static T Move(base_type b) { return neon::move<vector_type>(b); }

  ace T NotBitwise() const { return neon::not_bitwise(vec_); }

  ace T AndBitwise(T b) const { return neon::and_bitwise(vec_, b); }

  ace T OrBitwise(T b) const { return neon::or_bitwise(vec_, b); }

  ace T XorBitwise(T b) const { return neon::xor_bitwise(vec_, b); }

  ace T OrNotBitwise(T b) const { return neon::or_not_bitwise(vec_, b); }

  ace typename neon::make_signed<vector_type>::type CountLeadingSignBits() const {
    return neon::count_leading_sign_bits(vec_);
  }

  ace T CountLeadingZeroBits() const { return neon::count_leading_zero_bits(vec_); }

  ace T CountActiveBits() const { return neon::count_active_bits(vec_); }

  ace T ClearBitwise(T b) const { return neon::clear_bitwise(vec_, b); }

  ace T SelectBitwise(T b, T c) const { return neon::select_bitwise(vec_, b, c); }

  template <int lane>
  ace T DuplicateElement() const {
    return neon::duplicate_element(vec_, lane);
  }

  template <int lane>
  ace uint8x16_t DuplicateElement() const {
    return neon::duplicate_element(vec_, lane);
  }

  ace uint8x16_t Combine(T high) const { return neon::combine(vec_, high); }

  template <int lane>
  ace uint8_t Get() const {
    return neon::get(vec_, lane);
  }

  template <int n>
  ace T Extract(T b) const {
    return neon::extract(vec_, b, n);
  }

  ace T Reverse64bit() const { return neon::reverse_64bit(vec_); }

  ace T Reverse32bit() const { return neon::reverse_32bit(vec_); }

  ace T Reverse16bit() const { return neon::reverse_16bit(vec_); }

  ace uint8x8x2_t Zip(T b) const { return neon::zip(vec_, b); }

  uint8x8x2_t Unzip(T b) { return neon::unzip(vec_, b); }

  ace uint8x8x2_t Transpose(T b) const { return neon::transpose(vec_, b); }

  ace static int size() { return lanes; }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<base_type(base_type)>>
  ace T map(FuncType body) const {
    T out;
    for (int i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<base_type(base_type, base_type)>>
  ace T map2(T other, FuncType body) const {
    T out;
    for (int i = 0; i < lanes; ++i) {
      out[i] = body(vec_[i], other.vec_[i]);
    }
    return out;
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(base_type&)>>
  ace void each(FuncType body) {
    for (int i = 0; i < lanes; ++i) {
      body(vec_[i]);
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(base_type&, int)>>
  ace void each_lane(FuncType body) {
    for (int i = 0; i < lanes; ++i) {
      body(vec_[i], i);
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_(FuncType true_branch) {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch();
      }
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void()>>
  ace void if_else(FuncType true_branch, FuncType false_branch) {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch();
      } else {
        false_branch();
      }
    }
  }

  template <typename FuncType>
    requires std::convertible_to<FuncType, std::function<void(int)>>
  ace void if_lane(FuncType true_branch) {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch(i);
      }
    }
  }

  template <typename FuncType1, typename FuncType2>
    requires std::convertible_to<FuncType1, std::function<void(int)>> &&
             std::convertible_to<FuncType2, std::function<void(int)>>
  ace void if_else_lane(FuncType1 true_branch, FuncType2 false_branch) {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        true_branch(i);
      } else {
        false_branch(i);
      }
    }
  }

  ace bool any() {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] != 0) {
        return true;
      }
    }
    return false;
  }

  ace bool all() {
    for (int i = 0; i < lanes; ++i) {
      if (vec_[i] == 0) {
        return false;
      }
    }
    return true;
  }

 protected:
  vector_type vec_;
};

template <typename vector_type>
class Lane {
  using base_type = neon::NonVec<vector_type>::type;

 public:
  using T = Lane<vector_type>;

  ace Lane(vector_type vec, const int lane) : vec_(vec), lane_(lane){};

  ace operator neon::NonVec<vector_type>::type() { return neon::get(vec_, lane_); }

  ace Common<vector_type> operator=(base_type b) { return neon::set(vec_, lane_, b); }
  ace Common<vector_type> operator=(T t) { return neon::set(vec_, lane_, neon::get(t.vec_, t.lane_)); }

  ace Common<vector_type> operator+=(base_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) + b); }
  ace Common<vector_type> operator-=(base_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) - b); }
  ace Common<vector_type> operator*=(base_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) * b); }
  ace Common<vector_type> operator/=(base_type b) { return neon::set(vec_, lane_, neon::get(vec_, lane_) / b); }

 private:
  vector_type vec_;
  const int lane_;
};

}  // namespace impl

template <typename base>
class Neon128;

template <typename base_type>
class Neon64 : public impl::Common<typename impl::Vec64<base_type>::type> {
  using T = impl::Common<typename impl::Vec64<base_type>::type>;
  using next_larger_type = impl::NextLarger<base_type>::type;

 public:
  using vector_type = impl::Vec64<base_type>::type;

  static_assert(neon::is_doubleword_v<vector_type>);

  static constexpr size_t bytes = 8;
  static constexpr size_t lanes = bytes / sizeof(base_type);

  constexpr Neon64() : T(){};
  constexpr Neon64(vector_type vector) : T(vector){};
  constexpr Neon64(base_type base) : T(base){};
  constexpr Neon64(base_type const* base_ptr) : T(base_ptr){};
  constexpr Neon64(T&& in) : T(in){};
  constexpr Neon64(std::initializer_list<base_type> value_list) : T(value_list) {};

  ace Neon128<next_larger_type> AddLong(T b) const { return neon::add_long(this->vec_, b); }
  ace Neon128<next_larger_type> MultiplyLong(T b) const { return neon::multiply_long(this->vec_, b); }
  ace Neon128<next_larger_type> SubtractLong(T b) const { return neon::subtract_long(this->vec_, b); }
  ace Neon128<next_larger_type> MoveLong() const { return neon::move_long(this->vec_); }

  ace Neon128<next_larger_type> SubtractAbsLong(T b) const { return neon::subtract_abs_long(this->vec_, b); }
  ace Neon128<next_larger_type> AddPairwiseLong() const { return neon::add_pairwise_long(this->vec_); }

  ace T TableLookup1(T idx) const { return neon::table_lookup1(this->vec_, idx); }
  ace T TableLookupExtension1(T b, T idx) const { return neon::table_lookup_extension1(this->vec_, b, idx); }
  ace T TableLookupExtension2(uint8x8x2_t b, T idx) const { return neon::table_lookup_extension2(this->vec_, b, idx); }
  ace T TableLookupExtension3(uint8x8x3_t b, T idx) const { return neon::table_lookup_extension3(this->vec_, b, idx); }
  ace T TableLookupExtension4(uint8x8x4_t b, T idx) const { return neon::table_lookup_extension4(this->vec_, b, idx); }
};

template <typename base_type>
class Neon128 : public impl::Common<typename impl::Vec128<base_type>::type> {
  using T = impl::Common<typename impl::Vec128<base_type>::type>;

 public:
  using vector_type = impl::Vec128<base_type>::type;
  constexpr Neon128() : T(){};
  constexpr Neon128(vector_type vector) : T(vector){};
  constexpr Neon128(base_type base) : T(base){};
  constexpr Neon128(base_type const* base_ptr) : T(base_ptr){};
  constexpr Neon128(T&& in) : T(in){};
  constexpr Neon128(std::initializer_list<base_type> value_list) : T(value_list) {};

  static_assert(neon::is_quadword_v<vector_type>);

  static constexpr size_t bytes = 16;
  static constexpr size_t lanes = bytes / sizeof(base_type);

  ace Neon64<vector_type> GetHigh() { return vget_high_u8(this->vec_); }
  ace Neon64<vector_type> GetLow() { return vget_low_u8(this->vec_); }
};

template <typename NeonType, neon::is_vector_type V>
ace NeonType reinterpret(impl::Common<V> in) {
  static_assert(!std::is_same_v<typename NeonType::vector_type, V>);
  return NeonType{neon::reinterpret<typename NeonType::vector_type>(in.vec())};
}

template <typename NeonType, neon::is_vector_type V>
ace NeonType reinterpret(V in) {
  static_assert(!std::is_same_v<typename NeonType::vector_type, V>);
  return NeonType{neon::reinterpret<typename NeonType::vector_type>(in)};
}

template <neon::is_vector_type V>
ace impl::Common<V> operator+(typename neon::NonVec<V>::type a, impl::Common<V> b) {
  return b.Add(a);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator-(typename neon::NonVec<V>::type a, impl::Common<V> b) {
  return impl::Common<V>{a}.Subtract(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator*(typename neon::NonVec<V>::type a, impl::Common<V> b) {
  return b.Multiply(a);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator/(typename neon::NonVec<V>::type a, impl::Common<V> b) {
  return impl::Common<V>{a}.Divide(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator+(impl::Common<V> a, typename neon::NonVec<V>::type b) {
  return a.Add(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator-(impl::Common<V> a, typename neon::NonVec<V>::type b) {
  return a.Subtract(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator*(impl::Common<V> a, typename neon::NonVec<V>::type b) {
  return a.Multiply(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator/(impl::Common<V> a, typename neon::NonVec<V>::type b) {
  return a.Divide(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator+(V a, impl::Common<V> b) {
  return impl::Common<V>{a}.Add(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator-(V a, impl::Common<V> b) {
  return impl::Common<V>{a}.Subtract(b);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator*(V a, impl::Common<V> b) {
  return impl::Common<V>{a}.Multiply(a);
}

template <neon::is_vector_type V>
ace impl::Common<V> operator/(V a, impl::Common<V> b) {
  return impl::Common<V>{a}.Divide(b);
}

}  // namespace argon
#undef ace
