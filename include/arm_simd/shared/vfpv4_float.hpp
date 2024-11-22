#pragma once
#include "vfpv3_float.hpp"

#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
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
// clang-format off
template <typename T> nce T reinterpret(uint64x2_t a);
template <typename T> nce T reinterpret(float16x8_t a);
template <typename T> nce T reinterpret(uint8x16_t a);
template <typename T> nce T reinterpret(int8x16_t a);
template <typename T> nce T reinterpret(uint16x8_t a);
template <typename T> nce T reinterpret(int16x8_t a);
template <typename T> nce T reinterpret(int32x4_t a);
template <typename T> nce T reinterpret(uint32x4_t a);
template <typename T> nce T reinterpret(float32x4_t a);
template <typename T> nce T reinterpret(int64x2_t a);

template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint64x2_t a) { return vreinterpretq_f16_u64(a); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(float16x8_t a) { return vreinterpretq_s8_f16(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(float16x8_t a) { return vreinterpretq_s16_f16(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(float16x8_t a) { return vreinterpretq_s32_f16(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(float16x8_t a) { return vreinterpretq_f32_f16(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(float16x8_t a) { return vreinterpretq_u8_f16(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(float16x8_t a) { return vreinterpretq_u16_f16(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(float16x8_t a) { return vreinterpretq_u32_f16(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(float16x8_t a) { return vreinterpretq_u64_f16(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(float16x8_t a) { return vreinterpretq_s64_f16(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint8x16_t a) { return vreinterpretq_f16_u8(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int8x16_t a) { return vreinterpretq_f16_s8(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint16x8_t a) { return vreinterpretq_f16_u16(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int16x8_t a) { return vreinterpretq_f16_s16(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int32x4_t a) { return vreinterpretq_f16_s32(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(uint32x4_t a) { return vreinterpretq_f16_u32(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(float32x4_t a) { return vreinterpretq_f16_f32(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(int64x2_t a) { return vreinterpretq_f16_s64(a); }
template <int lane>[[gnu::always_inline]] nce float16_t get_lane(float16x8_t v) { return vgetq_lane_f16(v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t set_lane(float16_t a, float16x8_t v) { return vsetq_lane_f16(a, v, lane); }
// clang-format on
}
#endif  // __cplusplus
#undef nce
#undef simd
