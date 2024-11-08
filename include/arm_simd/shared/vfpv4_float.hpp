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

#define nce inline

namespace simd {
// clang-format off
template <typename T> nce T reinterpret(uint64x2_t a);
template <typename T> nce T reinterpret(float16x8_t a);
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
template <int lane>[[gnu::always_inline]] nce float16_t get_lane(float16x8_t v) { return vgetq_lane_f16(v, lane); }
template <int lane>[[gnu::always_inline]] nce float16x8_t set_lane(float16_t a, float16x8_t v) { return vsetq_lane_f16(a, v, lane); }
// clang-format on
}
#endif
#undef nce
#undef simd
