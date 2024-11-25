#pragma once
#include "arm_simd/shared/vfpv3_int.hpp"

#ifdef __cplusplus

#define nce [[gnu::always_inline]] inline

namespace helium {
// clang-format off
[[gnu::always_inline]] nce uint8x16_t multiply(uint8x16_t a, uint8_t b) { return vmulq_n_u8(a, b); }
[[gnu::always_inline]] nce int8x16_t multiply(int8x16_t a, int8_t b) { return vmulq_n_s8(a, b); }
[[gnu::always_inline]] nce int8x16_t duplicate(int8_t a) { return vdupq_n_s8(a); }
[[gnu::always_inline]] nce int16x8_t duplicate(int16_t a) { return vdupq_n_s16(a); }
[[gnu::always_inline]] nce int32x4_t duplicate(int32_t a) { return vdupq_n_s32(a); }
[[gnu::always_inline]] nce uint8x16_t duplicate(uint8_t a) { return vdupq_n_u8(a); }
[[gnu::always_inline]] nce uint16x8_t duplicate(uint16_t a) { return vdupq_n_u16(a); }
[[gnu::always_inline]] nce uint32x4_t duplicate(uint32_t a) { return vdupq_n_u32(a); }
[[gnu::always_inline]] inline int8x16_t load1(int8_t const *ptr) { return vld1q_s8(ptr); }
[[gnu::always_inline]] inline int16x8_t load1(int16_t const *ptr) { return vld1q_s16(ptr); }
[[gnu::always_inline]] inline int32x4_t load1(int32_t const *ptr) { return vld1q_s32(ptr); }
[[gnu::always_inline]] inline uint8x16_t load1(uint8_t const *ptr) { return vld1q_u8(ptr); }
[[gnu::always_inline]] inline uint16x8_t load1(uint16_t const *ptr) { return vld1q_u16(ptr); }
[[gnu::always_inline]] inline uint32x4_t load1(uint32_t const *ptr) { return vld1q_u32(ptr); }
// clang-format on
}  // namespace helium
#endif
#undef nce
