#pragma once
#include <arm_neon.h>
#ifdef __cplusplus
#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

namespace neon {
// clang-format off
template <typename T> nce T reinterpret(float16x4_t a);
template <typename T> nce T reinterpret(uint64x2_t a);
template <typename T> nce T reinterpret(float16x8_t a);
template <typename T> nce T load1(float16_t const *ptr);
template <typename T> nce T load1_duplicate(float16_t const *ptr);
template <typename T> nce T load2(float16_t const *ptr);
template <typename T> nce T load3(float16_t const *ptr);
template <typename T> nce T load4(float16_t const *ptr);
template <typename T> nce T load2_duplicate(float16_t const *ptr);
template <typename T> nce T load3_duplicate(float16_t const *ptr);
template <typename T> nce T load4_duplicate(float16_t const *ptr);
template <typename T> nce T load1_x2(float16_t const *ptr);
template <typename T> nce T load1_x3(float16_t const *ptr);
template <typename T> nce T load1_x4(float16_t const *ptr);
template <typename T> nce T store1(float16_t *ptr, float16x4_t val);
template <typename T> nce T store1(float16_t *ptr, float16x8_t val);
template <typename T> nce T store2(float16_t *ptr, float16x4x2_t val);
template <typename T> nce T store2(float16_t *ptr, float16x8x2_t val);
template <typename T> nce T store3(float16_t *ptr, float16x4x3_t val);
template <typename T> nce T store3(float16_t *ptr, float16x8x3_t val);
template <typename T> nce T store4(float16_t *ptr, float16x4x4_t val);
template <typename T> nce T store4(float16_t *ptr, float16x8x4_t val);
template <typename T> nce T duplicate(float16_t value);
template <typename T> nce T duplicate(float16x4_t vec);
template <typename T> nce T move(float16_t value);
template <typename T> nce T load1_x3(bfloat16_t const *ptr);
[[gnu::always_inline]] nce float16x4_t reinterpret(uint8x8_t a) { return vreinterpret_f16_u8(a); }
[[gnu::always_inline]] nce float16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_f16_u8(a); }
[[gnu::always_inline]] nce float16x4_t reinterpret(int8x8_t a) { return vreinterpret_f16_s8(a); }
[[gnu::always_inline]] nce float16x8_t reinterpret(int8x16_t a) { return vreinterpretq_f16_s8(a); }
[[gnu::always_inline]] nce float16x4_t reinterpret(uint16x4_t a) { return vreinterpret_f16_u16(a); }
[[gnu::always_inline]] nce float16x4_t bitwise_select(uint16x4_t a, float16x4_t b, float16x4_t c) { return vbsl_f16(a, b, c); }
[[gnu::always_inline]] nce float16x8_t reinterpret(uint16x8_t a) { return vreinterpretq_f16_u16(a); }
[[gnu::always_inline]] nce float16x8_t bitwise_select(uint16x8_t a, float16x8_t b, float16x8_t c) { return vbslq_f16(a, b, c); }
[[gnu::always_inline]] nce float16x4_t reinterpret(int16x4_t a) { return vreinterpret_f16_s16(a); }
[[gnu::always_inline]] nce float16x8_t reinterpret(int16x8_t a) { return vreinterpretq_f16_s16(a); }
[[gnu::always_inline]] nce float16x4_t reinterpret(int32x2_t a) { return vreinterpret_f16_s32(a); }
[[gnu::always_inline]] nce float16x8_t reinterpret(int32x4_t a) { return vreinterpretq_f16_s32(a); }
[[gnu::always_inline]] nce float16x4_t reinterpret(uint64x1_t a) { return vreinterpret_f16_u64(a); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(uint64x2_t a) { return vreinterpretq_f64_u64(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_f16_u64(a); }
[[gnu::always_inline]] nce float16x4_t reinterpret(uint32x2_t a) { return vreinterpret_f16_u32(a); }
[[gnu::always_inline]] nce float16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_f16_u32(a); }
[[gnu::always_inline]] nce float32x4_t convert(float16x4_t a) { return vcvt_f32_f16(a); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(float16x4_t a) { return vreinterpret_s8_f16(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(float16x4_t a) { return vreinterpret_s16_f16(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(float16x4_t a) { return vreinterpret_s32_f16(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(float16x4_t a) { return vreinterpret_f32_f16(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(float16x4_t a) { return vreinterpret_u8_f16(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(float16x4_t a) { return vreinterpret_u16_f16(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(float16x4_t a) { return vreinterpret_u32_f16(a); }
template <> [[gnu::always_inline]] nce poly8x8_t reinterpret(float16x4_t a) { return vreinterpret_p8_f16(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(float16x4_t a) { return vreinterpret_p16_f16(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(float16x4_t a) { return vreinterpret_u64_f16(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(float16x4_t a) { return vreinterpret_s64_f16(a); }
[[gnu::always_inline]] nce float16x8_t combine(float16x4_t low, float16x4_t high) { return vcombine_f16(low, high); }
template <int lane>[[gnu::always_inline]] nce float16_t get_lane(float16x4_t v) { return vget_lane_f16(v, lane); }
[[gnu::always_inline]] nce float16x4x2_t zip(float16x4_t a, float16x4_t b) { return vzip_f16(a, b); }
[[gnu::always_inline]] nce float16x4x2_t unzip(float16x4_t a, float16x4_t b) { return vuzp_f16(a, b); }
[[gnu::always_inline]] nce float16x4x2_t transpose(float16x4_t a, float16x4_t b) { return vtrn_f16(a, b); }
template <int lane>[[gnu::always_inline]] nce float16x4_t duplicate_lane(float16x4_t vec) { return vdup_lane_f16(vec, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t duplicate_lane(float16x4_t vec) { return vdupq_lane_f16(vec, lane); }
template <int n>[[gnu::always_inline]] nce float16x4_t extract(float16x4_t a, float16x4_t b) { return vext_f16(a, b, n); }
[[gnu::always_inline]] nce float16x4_t reverse_64bit(float16x4_t vec) { return vrev64_f16(vec); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(float16x8_t a) { return vreinterpretq_s8_f16(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(float16x8_t a) { return vreinterpretq_s16_f16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(float16x8_t a) { return vreinterpretq_s32_f16(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(float16x8_t a) { return vreinterpretq_f32_f16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(float16x8_t a) { return vreinterpretq_u8_f16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(float16x8_t a) { return vreinterpretq_u16_f16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(float16x8_t a) { return vreinterpretq_u32_f16(a); }
template <> [[gnu::always_inline]] nce poly8x16_t reinterpret(float16x8_t a) { return vreinterpretq_p8_f16(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(float16x8_t a) { return vreinterpretq_p16_f16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(float16x8_t a) { return vreinterpretq_u64_f16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(float16x8_t a) { return vreinterpretq_s64_f16(a); }
[[gnu::always_inline]] nce float16x4_t get_high(float16x8_t a) { return vget_high_f16(a); }
[[gnu::always_inline]] nce float16x4_t get_low(float16x8_t a) { return vget_low_f16(a); }
template <int lane>[[gnu::always_inline]] nce float16_t get_lane(float16x8_t v) { return vgetq_lane_f16(v, lane); }
[[gnu::always_inline]] nce float16x8x2_t zip(float16x8_t a, float16x8_t b) { return vzipq_f16(a, b); }
[[gnu::always_inline]] nce float16x8x2_t unzip(float16x8_t a, float16x8_t b) { return vuzpq_f16(a, b); }
[[gnu::always_inline]] nce float16x8x2_t transpose(float16x8_t a, float16x8_t b) { return vtrnq_f16(a, b); }
template <int n>[[gnu::always_inline]] nce float16x8_t extract(float16x8_t a, float16x8_t b) { return vextq_f16(a, b, n); }
[[gnu::always_inline]] nce float16x8_t reverse_64bit(float16x8_t vec) { return vrev64q_f16(vec); }
[[gnu::always_inline]] nce float16x4_t reinterpret(float32x2_t a) { return vreinterpret_f16_f32(a); }
[[gnu::always_inline]] nce float16x4_t convert(float32x4_t a) { return vcvt_f16_f32(a); }
[[gnu::always_inline]] nce float16x8_t reinterpret(float32x4_t a) { return vreinterpretq_f16_f32(a); }
[[gnu::always_inline]] nce float16x4_t reinterpret(poly8x8_t a) { return vreinterpret_f16_p8(a); }
[[gnu::always_inline]] nce float16x4_t reinterpret(poly16x4_t a) { return vreinterpret_f16_p16(a); }
[[gnu::always_inline]] nce float16x4_t reinterpret(int64x1_t a) { return vreinterpret_f16_s64(a); }
[[gnu::always_inline]] nce float16x8_t reinterpret(poly8x16_t a) { return vreinterpretq_f16_p8(a); }
[[gnu::always_inline]] nce float16x8_t reinterpret(poly16x8_t a) { return vreinterpretq_f16_p16(a); }
[[gnu::always_inline]] nce float16x8_t reinterpret(int64x2_t a) { return vreinterpretq_f16_s64(a); }
[[gnu::always_inline]] nce float16x4_t create(uint64_t a) { return vcreate_f16(a); }
template <int lane>[[gnu::always_inline]] nce float16x4_t set_lane(float16_t a, float16x4_t v) { return vset_lane_f16(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t set_lane(float16_t a, float16x8_t v) { return vsetq_lane_f16(a, v, lane); }
template <> [[gnu::always_inline]] inline float16x4_t load1(float16_t const *ptr) { return vld1_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x8_t load1(float16_t const *ptr) { return vld1q_f16(ptr); }
template <int lane>[[gnu::always_inline]] nce float16x4_t load1_lane(float16_t const *ptr, float16x4_t src) { return vld1_lane_f16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t load1_lane(float16_t const *ptr, float16x8_t src) { return vld1q_lane_f16(ptr, src, lane); }
template <> [[gnu::always_inline]] inline float16x4_t load1_duplicate(float16_t const *ptr) { return vld1_dup_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x8_t load1_duplicate(float16_t const *ptr) { return vld1q_dup_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x4x2_t load2(float16_t const *ptr) { return vld2_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x8x2_t load2(float16_t const *ptr) { return vld2q_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x4x3_t load3(float16_t const *ptr) { return vld3_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x8x3_t load3(float16_t const *ptr) { return vld3q_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x4x4_t load4(float16_t const *ptr) { return vld4_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x8x4_t load4(float16_t const *ptr) { return vld4q_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x4x2_t load2_duplicate(float16_t const *ptr) { return vld2_dup_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x8x2_t load2_duplicate(float16_t const *ptr) { return vld2q_dup_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x4x3_t load3_duplicate(float16_t const *ptr) { return vld3_dup_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x8x3_t load3_duplicate(float16_t const *ptr) { return vld3q_dup_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x4x4_t load4_duplicate(float16_t const *ptr) { return vld4_dup_f16(ptr); }
template <> [[gnu::always_inline]] inline float16x8x4_t load4_duplicate(float16_t const *ptr) { return vld4q_dup_f16(ptr); }
template <int lane>[[gnu::always_inline]] nce float16x4x2_t load2_lane(float16_t const *ptr, float16x4x2_t src) { return vld2_lane_f16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8x2_t load2_lane(float16_t const *ptr, float16x8x2_t src) { return vld2q_lane_f16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4x3_t load3_lane(float16_t const *ptr, float16x4x3_t src) { return vld3_lane_f16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8x3_t load3_lane(float16_t const *ptr, float16x8x3_t src) { return vld3q_lane_f16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float16x4x4_t load4_lane(float16_t const *ptr, float16x4x4_t src) { return vld4_lane_f16(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8x4_t load4_lane(float16_t const *ptr, float16x8x4_t src) { return vld4q_lane_f16(ptr, src, lane); }
template <> [[gnu::always_inline]] inline float16x4x2_t load1_x2(float16_t const *ptr) { return vld1_f16_x2(ptr); }
template <> [[gnu::always_inline]] inline float16x8x2_t load1_x2(float16_t const *ptr) { return vld1q_f16_x2(ptr); }
template <> [[gnu::always_inline]] inline float16x4x3_t load1_x3(float16_t const *ptr) { return vld1_f16_x3(ptr); }
template <> [[gnu::always_inline]] inline float16x8x3_t load1_x3(float16_t const *ptr) { return vld1q_f16_x3(ptr); }
template <> [[gnu::always_inline]] inline float16x4x4_t load1_x4(float16_t const *ptr) { return vld1_f16_x4(ptr); }
template <> [[gnu::always_inline]] inline float16x8x4_t load1_x4(float16_t const *ptr) { return vld1q_f16_x4(ptr); }
template <> [[gnu::always_inline]] inline void store1(float16_t *ptr, float16x4_t val) { return vst1_f16(ptr, val); }
template <> [[gnu::always_inline]] inline void store1(float16_t *ptr, float16x8_t val) { return vst1q_f16(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(float16_t *ptr, float16x4_t val) { return vst1_lane_f16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(float16_t *ptr, float16x8_t val) { return vst1q_lane_f16(ptr, val, lane); }
template <> [[gnu::always_inline]] inline void store2(float16_t *ptr, float16x4x2_t val) { return vst2_f16(ptr, val); }
template <> [[gnu::always_inline]] inline void store2(float16_t *ptr, float16x8x2_t val) { return vst2q_f16(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(float16_t *ptr, float16x4x3_t val) { return vst3_f16(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(float16_t *ptr, float16x8x3_t val) { return vst3q_f16(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(float16_t *ptr, float16x4x4_t val) { return vst4_f16(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(float16_t *ptr, float16x8x4_t val) { return vst4q_f16(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(float16_t *ptr, float16x4x2_t val) { return vst2_lane_f16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(float16_t *ptr, float16x8x2_t val) { return vst2q_lane_f16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(float16_t *ptr, float16x4x3_t val) { return vst3_lane_f16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(float16_t *ptr, float16x8x3_t val) { return vst3q_lane_f16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(float16_t *ptr, float16x4x4_t val) { return vst4_lane_f16(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(float16_t *ptr, float16x8x4_t val) { return vst4q_lane_f16(ptr, val, lane); }
[[gnu::always_inline]] inline void store1_x2(float16_t *ptr, float16x4x2_t val) { return vst1_f16_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(float16_t *ptr, float16x8x2_t val) { return vst1q_f16_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(float16_t *ptr, float16x4x3_t val) { return vst1_f16_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(float16_t *ptr, float16x8x3_t val) { return vst1q_f16_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(float16_t *ptr, float16x4x4_t val) { return vst1_f16_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(float16_t *ptr, float16x8x4_t val) { return vst1q_f16_x4(ptr, val); }
template <> [[gnu::always_inline]] nce float16x4_t duplicate(float16_t value) { return vdup_n_f16(value); }
template <> [[gnu::always_inline]] nce float16x8_t duplicate(float16_t value) { return vdupq_n_f16(value); }
template <> [[gnu::always_inline]] nce float16x4_t move(float16_t value) { return vmov_n_f16(value); }
template <> [[gnu::always_inline]] nce float16x8_t move(float16_t value) { return vmovq_n_f16(value); }
template <> [[gnu::always_inline]] inline bfloat16x4x3_t load1_x3(bfloat16_t const *ptr) { return vld1_bf16_x3(ptr); }
template <> [[gnu::always_inline]] inline bfloat16x8x3_t load1_x3(bfloat16_t const *ptr) { return vld1q_bf16_x3(ptr); }
// clang-format on
}  // namespace neon
#endif
#undef nce
