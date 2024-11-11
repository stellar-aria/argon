#ifdef __ARM_FEATURE_SHA3
[[gnu::always_inline]] nce uint8x16_t exclusive_or(uint8x16_t a, uint8x16_t b, uint8x16_t c) { return veor3q_u8(a, b, c); }
[[gnu::always_inline]] nce int8x16_t exclusive_or(int8x16_t a, int8x16_t b, int8x16_t c) { return veor3q_s8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t exclusive_or(uint16x8_t a, uint16x8_t b, uint16x8_t c) { return veor3q_u16(a, b, c); }
[[gnu::always_inline]] nce int16x8_t exclusive_or(int16x8_t a, int16x8_t b, int16x8_t c) { return veor3q_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t exclusive_or(int32x4_t a, int32x4_t b, int32x4_t c) { return veor3q_s32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t exclusive_or(uint64x2_t a, uint64x2_t b, uint64x2_t c) { return veor3q_u64(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t exclusive_or(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return veor3q_u32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t exclusive_or(int64x2_t a, int64x2_t b, int64x2_t c) { return veor3q_s64(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t rotate_and_xor(uint64x2_t a, uint64x2_t b) { return vrax1q_u64(a, b); }
template <int imm> [[gnu::always_inline]] nce uint64x2_t xor_and_rotate(uint64x2_t a, uint64x2_t b) { return vxarq_u64(a, b, imm); }
[[gnu::always_inline]] nce uint8x16_t bit_clear_xor(uint8x16_t a, uint8x16_t b, uint8x16_t c) { return vbcaxq_u8(a, b, c); }
[[gnu::always_inline]] nce int8x16_t bit_clear_xor(int8x16_t a, int8x16_t b, int8x16_t c) { return vbcaxq_s8(a, b, c); }
[[gnu::always_inline]] nce uint16x8_t bit_clear_xor(uint16x8_t a, uint16x8_t b, uint16x8_t c) { return vbcaxq_u16(a, b, c); }
[[gnu::always_inline]] nce int16x8_t bit_clear_xor(int16x8_t a, int16x8_t b, int16x8_t c) { return vbcaxq_s16(a, b, c); }
[[gnu::always_inline]] nce int32x4_t bit_clear_xor(int32x4_t a, int32x4_t b, int32x4_t c) { return vbcaxq_s32(a, b, c); }
[[gnu::always_inline]] nce uint64x2_t bit_clear_xor(uint64x2_t a, uint64x2_t b, uint64x2_t c) { return vbcaxq_u64(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t bit_clear_xor(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vbcaxq_u32(a, b, c); }
[[gnu::always_inline]] nce int64x2_t bit_clear_xor(int64x2_t a, int64x2_t b, int64x2_t c) { return vbcaxq_s64(a, b, c); }
#endif
