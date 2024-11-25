#ifdef __ARM_FEATURE_SHA512
[[gnu::always_inline]] nce uint64x2_t sha512_hash_part_1(uint64x2_t hash_ed, uint64x2_t hash_gf, uint64x2_t kwh_kwh2) { return vsha512hq_u64(hash_ed, hash_gf, kwh_kwh2); }
[[gnu::always_inline]] nce uint64x2_t sha512_hash_part_2(uint64x2_t sum_ab, uint64x2_t hash_c_, uint64x2_t hash_ab) { return vsha512h2q_u64(sum_ab, hash_c_, hash_ab); }
[[gnu::always_inline]] nce uint64x2_t sha512_schedule_update_0(uint64x2_t w0_1, uint64x2_t w2_) { return vsha512su0q_u64(w0_1, w2_); }
[[gnu::always_inline]] nce uint64x2_t sha512_schedule_update_1(uint64x2_t s01_s02, uint64x2_t w14_15, uint64x2_t w9_10) { return vsha512su1q_u64(s01_s02, w14_15, w9_10); }
#endif
