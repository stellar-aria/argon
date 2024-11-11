#ifdef __ARM_FEATURE_SM3
[[gnu::always_inline]] nce uint32x4_t sm3_ss_1(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vsm3ss1q_u32(a, b, c); }
template <int imm> [[gnu::always_inline]] nce uint32x4_t sm3_tt_1a(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vsm3tt1aq_u32(a, b, c, imm); }
template <int imm> [[gnu::always_inline]] nce uint32x4_t sm3_tt_1b(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vsm3tt1bq_u32(a, b, c, imm); }
template <int imm> [[gnu::always_inline]] nce uint32x4_t sm3_tt_2a(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vsm3tt2aq_u32(a, b, c, imm); }
template <int imm> [[gnu::always_inline]] nce uint32x4_t sm3_tt_2b(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vsm3tt2bq_u32(a, b, c, imm); }
[[gnu::always_inline]] nce uint32x4_t sm3_part_w_1(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vsm3partw1q_u32(a, b, c); }
[[gnu::always_inline]] nce uint32x4_t sm3_part_w_2(uint32x4_t a, uint32x4_t b, uint32x4_t c) { return vsm3partw2q_u32(a, b, c); }
#endif

