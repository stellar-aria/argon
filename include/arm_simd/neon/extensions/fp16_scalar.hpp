#ifdef __ARM_FEATURE_FP16_SCALAR_ARITHMETIC
#include <arm_fp16.h>

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
