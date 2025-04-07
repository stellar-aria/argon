#if defined(__ARM_ACLE) && defined(__ARM_FEATURE_CRC32)
[[gnu::always_inline]] nce uint32_t crc32(uint32_t a, uint8_t b) { return __crc32b(a, b); }
[[gnu::always_inline]] nce uint32_t crc32(uint32_t a, uint16_t b) { return __crc32h(a, b); }
[[gnu::always_inline]] nce uint32_t crc32(uint32_t a, uint32_t b) { return __crc32w(a, b); }
[[gnu::always_inline]] nce uint32_t crc32(uint32_t a, uint64_t b) { return __crc32d(a, b); }
[[gnu::always_inline]] nce uint32_t crc32_castagnoli(uint32_t a, uint8_t b) { return __crc32cb(a, b); }
[[gnu::always_inline]] nce uint32_t crc32_castagnoli(uint32_t a, uint16_t b) { return __crc32ch(a, b); }
[[gnu::always_inline]] nce uint32_t crc32_castagnoli(uint32_t a, uint32_t b) { return __crc32cw(a, b); }
[[gnu::always_inline]] nce uint32_t crc32_castagnoli(uint32_t a, uint64_t b) { return __crc32cd(a, b); }
#endif
