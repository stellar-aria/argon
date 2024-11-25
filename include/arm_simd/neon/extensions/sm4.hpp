#ifdef __ARM_FEATURE_SM4
[[gnu::always_inline]] nce uint32x4_t sm4_encode(uint32x4_t a, uint32x4_t b) { return vsm4eq_u32(a, b); }
[[gnu::always_inline]] nce uint32x4_t sm4_encode_key(uint32x4_t a, uint32x4_t b) { return vsm4ekeyq_u32(a, b); }
#endif
