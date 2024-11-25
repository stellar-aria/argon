#ifdef __ARM_FEATURE_FP8
template <typename T> nce T reinterpret(mfloat8x8_t a);
template <typename T> nce T reinterpret(mfloat8x16_t a);
template <typename T> nce T duplicate(mfloat8_t value);
template <typename T> nce T move(mfloat8_t value);
template <typename T> nce T duplicate(mfloat8x8_t vec);
template <typename T> nce T duplicate(mfloat8x16_t vec);
template <typename T> nce T get(mfloat8x16_t a);
template <typename T> nce T load1(mfloat8_t const *ptr);
template <typename T> nce T load1_duplicate(mfloat8_t const *ptr);
template <typename T> nce T load2(mfloat8_t const *ptr);
template <typename T> nce T load4(mfloat8_t const *ptr);
template <typename T> nce T load2_duplicate(mfloat8_t const *ptr);
template <typename T> nce T load3_duplicate(mfloat8_t const *ptr);
template <typename T> nce T load4_duplicate(mfloat8_t const *ptr);
template <typename T> nce T load1_x2(mfloat8_t const *ptr);
template <typename T> nce T load1_x3(mfloat8_t const *ptr);
template <typename T> nce T load1_x4(mfloat8_t const *ptr);
template <typename T> nce T store1(mfloat8_t *ptr, mfloat8x8_t val);
template <typename T> nce T store1(mfloat8_t *ptr, mfloat8x16_t val);
template <typename T> nce T store2(mfloat8_t *ptr, mfloat8x8x2_t val);
template <typename T> nce T store2(mfloat8_t *ptr, mfloat8x16x2_t val);
template <typename T> nce T store3(mfloat8_t *ptr, mfloat8x8x3_t val);
template <typename T> nce T store3(mfloat8_t *ptr, mfloat8x16x3_t val);
template <typename T> nce T store4(mfloat8_t *ptr, mfloat8x8x4_t val);
template <typename T> nce T store4(mfloat8_t *ptr, mfloat8x16x4_t val);

[[gnu::always_inline]] nce float16x4_t scale_exponent(float16x4_t vn, int16x4_t vm) { return vscale_f16(vn, vm); }
[[gnu::always_inline]] nce float16x8_t scale_exponent(float16x8_t vn, int16x8_t vm) { return vscaleq_f16(vn, vm); }
[[gnu::always_inline]] nce float32x2_t scale_exponent(float32x2_t vn, int32x2_t vm) { return vscale_f32(vn, vm); }
[[gnu::always_inline]] nce float32x4_t scale_exponent(float32x4_t vn, int32x4_t vm) { return vscaleq_f32(vn, vm); }
[[gnu::always_inline]] nce float64x2_t scale_exponent(float64x2_t vn, int64x2_t vm) { return vscaleq_f64(vn, vm); }

[[gnu::always_inline]] inline void store1_x4(int8_t *ptr, int8x8x4_t val) { return vst1_mf8_x4(ptr, val); }
[[gnu::always_inline]] inline void store1_x4(int8_t *ptr, int8x16x4_t val) { return vst1q_mf8_x4(ptr, val); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(uint8x8_t a) { return vreinterpret_mf8_u8(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(uint8x16_t a) { return vreinterpretq_mf8_u8(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(int8x8_t a) { return vreinterpret_mf8_s8(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(int8x16_t a) { return vreinterpretq_mf8_s8(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(uint16x4_t a) { return vreinterpret_mf8_u16(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(uint16x8_t a) { return vreinterpretq_mf8_u16(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(int16x4_t a) { return vreinterpret_mf8_s16(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(int16x8_t a) { return vreinterpretq_mf8_s16(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(int32x2_t a) { return vreinterpret_mf8_s32(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(int32x4_t a) { return vreinterpretq_mf8_s32(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(uint64x1_t a) { return vreinterpret_mf8_u64(a); }
[[gnu::always_inline]] nce mfloat8x16_t reinterpret(uint64x2_t a) { return vreinterpretq_mf8_u64(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(uint32x2_t a) { return vreinterpret_mf8_u32(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(uint32x4_t a) { return vreinterpretq_mf8_u32(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(float16x4_t a) { return vreinterpret_mf8_f16(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(float16x8_t a) { return vreinterpretq_mf8_f16(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(float32x2_t a) { return vreinterpret_mf8_f32(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(float32x4_t a) { return vreinterpretq_mf8_f32(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(float64x1_t a) { return vreinterpret_mf8_f64(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(float64x2_t a) { return vreinterpretq_mf8_f64(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(poly16x4_t a) { return vreinterpret_mf8_p16(a); }
template <> [[gnu::always_inline]] nce int8x8_t reinterpret(mfloat8x8_t a) { return vreinterpret_s8_mf8(a); }
template <> [[gnu::always_inline]] nce int16x4_t reinterpret(mfloat8x8_t a) { return vreinterpret_s16_mf8(a); }
template <> [[gnu::always_inline]] nce int32x2_t reinterpret(mfloat8x8_t a) { return vreinterpret_s32_mf8(a); }
template <> [[gnu::always_inline]] nce float32x2_t reinterpret(mfloat8x8_t a) { return vreinterpret_f32_mf8(a); }
template <> [[gnu::always_inline]] nce uint8x8_t reinterpret(mfloat8x8_t a) { return vreinterpret_u8_mf8(a); }
template <> [[gnu::always_inline]] nce uint16x4_t reinterpret(mfloat8x8_t a) { return vreinterpret_u16_mf8(a); }
template <> [[gnu::always_inline]] nce uint32x2_t reinterpret(mfloat8x8_t a) { return vreinterpret_u32_mf8(a); }
template <> [[gnu::always_inline]] nce poly16x4_t reinterpret(mfloat8x8_t a) { return vreinterpret_p16_mf8(a); }
template <> [[gnu::always_inline]] nce uint64x1_t reinterpret(mfloat8x8_t a) { return vreinterpret_u64_mf8(a); }
template <> [[gnu::always_inline]] nce int64x1_t reinterpret(mfloat8x8_t a) { return vreinterpret_s64_mf8(a); }
template <> [[gnu::always_inline]] nce float64x1_t reinterpret(mfloat8x8_t a) { return vreinterpret_f64_mf8(a); }
template <> [[gnu::always_inline]] nce poly64x1_t reinterpret(mfloat8x8_t a) { return vreinterpret_p64_mf8(a); }
template <> [[gnu::always_inline]] nce float16x4_t reinterpret(mfloat8x8_t a) { return vreinterpret_f16_mf8(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(int64x1_t a) { return vreinterpret_mf8_s64(a); }
template <> [[gnu::always_inline]] nce int8x16_t reinterpret(mfloat8x16_t a) { return vreinterpretq_s8_mf8(a); }
template <> [[gnu::always_inline]] nce int16x8_t reinterpret(mfloat8x16_t a) { return vreinterpretq_s16_mf8(a); }
template <> [[gnu::always_inline]] nce int32x4_t reinterpret(mfloat8x16_t a) { return vreinterpretq_s32_mf8(a); }
template <> [[gnu::always_inline]] nce float32x4_t reinterpret(mfloat8x16_t a) { return vreinterpretq_f32_mf8(a); }
template <> [[gnu::always_inline]] nce uint8x16_t reinterpret(mfloat8x16_t a) { return vreinterpretq_u8_mf8(a); }
template <> [[gnu::always_inline]] nce uint16x8_t reinterpret(mfloat8x16_t a) { return vreinterpretq_u16_mf8(a); }
template <> [[gnu::always_inline]] nce uint32x4_t reinterpret(mfloat8x16_t a) { return vreinterpretq_u32_mf8(a); }
template <> [[gnu::always_inline]] nce poly16x8_t reinterpret(mfloat8x16_t a) { return vreinterpretq_p16_mf8(a); }
template <> [[gnu::always_inline]] nce uint64x2_t reinterpret(mfloat8x16_t a) { return vreinterpretq_u64_mf8(a); }
template <> [[gnu::always_inline]] nce int64x2_t reinterpret(mfloat8x16_t a) { return vreinterpretq_s64_mf8(a); }
template <> [[gnu::always_inline]] nce float64x2_t reinterpret(mfloat8x16_t a) { return vreinterpretq_f64_mf8(a); }
template <> [[gnu::always_inline]] nce poly64x2_t reinterpret(mfloat8x16_t a) { return vreinterpretq_p64_mf8(a); }
template <> [[gnu::always_inline]] nce poly128_t reinterpret(mfloat8x16_t a) { return vreinterpretq_p128_mf8(a); }
template <> [[gnu::always_inline]] nce float16x8_t reinterpret(mfloat8x16_t a) { return vreinterpretq_f16_mf8(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(poly16x8_t a) { return vreinterpretq_mf8_p16(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(int64x2_t a) { return vreinterpretq_mf8_s64(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(poly64x2_t a) { return vreinterpretq_mf8_p64(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(poly128_t a) { return vreinterpretq_mf8_p128(a); }
template <int lane1, int lane2>[[gnu::always_inline]] nce mfloat8x8_t copy_lane(mfloat8x8_t a, mfloat8x8_t b) { return vcopy_lane_mf8(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce mfloat8x16_t copy_lane(mfloat8x16_t a, mfloat8x8_t b) { return vcopyq_lane_mf8(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce mfloat8x8_t copy_lane(mfloat8x8_t a, mfloat8x16_t b) { return vcopy_laneq_mf8(a, lane1, b, lane2); }
template <int lane1, int lane2>[[gnu::always_inline]] nce mfloat8x16_t copy_lane(mfloat8x16_t a, mfloat8x16_t b) { return vcopyq_laneq_mf8(a, lane1, b, lane2); }
template <> [[gnu::always_inline]] nce mfloat8x8_t create(uint64_t a) { return vcreate_mf8(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t duplicate(mfloat8_t value) { return vdup_n_mf8(value); }
template <> [[gnu::always_inline]] nce mfloat8x16_t duplicate(mfloat8_t value) { return vdupq_n_mf8(value); }
template <> [[gnu::always_inline]] nce mfloat8x8_t move(mfloat8_t value) { return vmov_n_mf8(value); }
template <> [[gnu::always_inline]] nce mfloat8x16_t move(mfloat8_t value) { return vmovq_n_mf8(value); }
template <int lane>[[gnu::always_inline]] nce mfloat8x8_t duplicate_lane(mfloat8x8_t vec) { return vdup_lane_mf8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8x16_t duplicate_lane(mfloat8x8_t vec) { return vdupq_lane_mf8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8x8_t duplicate_lane(mfloat8x16_t vec) { return vdup_laneq_mf8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8x16_t duplicate_lane(mfloat8x16_t vec) { return vdupq_laneq_mf8(vec, lane); }
[[gnu::always_inline]] nce mfloat8x16_t combine(mfloat8x8_t low, mfloat8x8_t high) { return vcombine_mf8(low, high); }
template <> [[gnu::always_inline]] nce mfloat8x8_t get_high(mfloat8x16_t a) { return vget_high_mf8(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t get_low(mfloat8x16_t a) { return vget_low_mf8(a); }
template <int lane>[[gnu::always_inline]] nce mfloat8_t duplicate_lane(mfloat8x8_t vec) { return vdupb_lane_mf8(vec, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8_t duplicate_lane(mfloat8x16_t vec) { return vdupb_laneq_mf8(vec, lane); }
template <int n>[[gnu::always_inline]] nce mfloat8x8_t extract(mfloat8x8_t a, mfloat8x8_t b) { return vext_mf8(a, b, n); }
template <int n>[[gnu::always_inline]] nce mfloat8x16_t extract(mfloat8x16_t a, mfloat8x16_t b) { return vextq_mf8(a, b, n); }
[[gnu::always_inline]] nce mfloat8x8_t reverse_64bit(mfloat8x8_t vec) { return vrev64_mf8(vec); }
[[gnu::always_inline]] nce mfloat8x16_t reverse_64bit(mfloat8x16_t vec) { return vrev64q_mf8(vec); }
[[gnu::always_inline]] nce mfloat8x8_t reverse_32bit(mfloat8x8_t vec) { return vrev32_mf8(vec); }
[[gnu::always_inline]] nce mfloat8x16_t reverse_32bit(mfloat8x16_t vec) { return vrev32q_mf8(vec); }
[[gnu::always_inline]] nce mfloat8x8_t reverse_16bit(mfloat8x8_t vec) { return vrev16_mf8(vec); }
[[gnu::always_inline]] nce mfloat8x16_t reverse_16bit(mfloat8x16_t vec) { return vrev16q_mf8(vec); }
[[gnu::always_inline]] nce mfloat8x8_t zip1(mfloat8x8_t a, mfloat8x8_t b) { return vzip1_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x16_t zip1(mfloat8x16_t a, mfloat8x16_t b) { return vzip1q_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x8_t zip2(mfloat8x8_t a, mfloat8x8_t b) { return vzip2_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x16_t zip2(mfloat8x16_t a, mfloat8x16_t b) { return vzip2q_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x8x2_t zip(mfloat8x8_t a, mfloat8x8_t b) { return vzip_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x16x2_t zip(mfloat8x16_t a, mfloat8x16_t b) { return vzipq_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x8_t unzip1(mfloat8x8_t a, mfloat8x8_t b) { return vuzp1_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x16_t unzip1(mfloat8x16_t a, mfloat8x16_t b) { return vuzp1q_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x8_t unzip2(mfloat8x8_t a, mfloat8x8_t b) { return vuzp2_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x16_t unzip2(mfloat8x16_t a, mfloat8x16_t b) { return vuzp2q_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x8x2_t unzip(mfloat8x8_t a, mfloat8x8_t b) { return vuzp_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x16x2_t unzip(mfloat8x16_t a, mfloat8x16_t b) { return vuzpq_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x8_t transpose_step_1(mfloat8x8_t a, mfloat8x8_t b) { return vtrn1_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x16_t transpose_step_1(mfloat8x16_t a, mfloat8x16_t b) { return vtrn1q_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x8_t transpose_step_2(mfloat8x8_t a, mfloat8x8_t b) { return vtrn2_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x16_t transpose_step_2(mfloat8x16_t a, mfloat8x16_t b) { return vtrn2q_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x8x2_t transpose(mfloat8x8_t a, mfloat8x8_t b) { return vtrn_mf8(a, b); }
[[gnu::always_inline]] nce mfloat8x16x2_t transpose(mfloat8x16_t a, mfloat8x16_t b) { return vtrnq_mf8(a, b); }
template <int lane>[[gnu::always_inline]] nce mfloat8x8_t set_lane(mfloat8_t a, mfloat8x8_t v) { return vset_lane_mf8(a, v, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8x16_t set_lane(mfloat8_t a, mfloat8x16_t v) { return vsetq_lane_mf8(a, v, lane); }
template <> [[gnu::always_inline]] inline mfloat8x8_t load1(mfloat8_t const *ptr) { return vld1_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16_t load1(mfloat8_t const *ptr) { return vld1q_mf8(ptr); }
template <int lane>[[gnu::always_inline]] nce mfloat8x8_t load1_lane(mfloat8_t const *ptr, mfloat8x8_t src) { return vld1_lane_mf8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8x16_t load1_lane(mfloat8_t const *ptr, mfloat8x16_t src) { return vld1q_lane_mf8(ptr, src, lane); }
template <> [[gnu::always_inline]] inline mfloat8x8_t load1_duplicate(mfloat8_t const *ptr) { return vld1_dup_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16_t load1_duplicate(mfloat8_t const *ptr) { return vld1q_dup_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x8x2_t load2(mfloat8_t const *ptr) { return vld2_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16x2_t load2(mfloat8_t const *ptr) { return vld2q_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x8x3_t load3(int8_t const *ptr) { return vld3_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16x3_t load3(int8_t const *ptr) { return vld3q_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x8x4_t load4(mfloat8_t const *ptr) { return vld4_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16x4_t load4(mfloat8_t const *ptr) { return vld4q_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x8x2_t load2_duplicate(mfloat8_t const *ptr) { return vld2_dup_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16x2_t load2_duplicate(mfloat8_t const *ptr) { return vld2q_dup_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x8x3_t load3_duplicate(mfloat8_t const *ptr) { return vld3_dup_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16x3_t load3_duplicate(mfloat8_t const *ptr) { return vld3q_dup_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x8x4_t load4_duplicate(mfloat8_t const *ptr) { return vld4_dup_mf8(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16x4_t load4_duplicate(mfloat8_t const *ptr) { return vld4q_dup_mf8(ptr); }
template <int lane>[[gnu::always_inline]] nce mfloat8x8x2_t load2_lane(mfloat8_t const *ptr, mfloat8x8x2_t src) { return vld2_lane_mf8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8x16x2_t load2_lane(mfloat8_t const *ptr, mfloat8x16x2_t src) { return vld2q_lane_mf8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8x8x3_t load3_lane(mfloat8_t const *ptr, mfloat8x8x3_t src) { return vld3_lane_mf8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8x16x3_t load3_lane(mfloat8_t const *ptr, mfloat8x16x3_t src) { return vld3q_lane_mf8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8x8x4_t load4_lane(mfloat8_t const *ptr, mfloat8x8x4_t src) { return vld4_lane_mf8(ptr, src, lane); }
template <int lane>[[gnu::always_inline]] nce mfloat8x16x4_t load4_lane(mfloat8_t const *ptr, mfloat8x16x4_t src) { return vld4q_lane_mf8(ptr, src, lane); }
template <> [[gnu::always_inline]] inline mfloat8x8x2_t load1_x2(mfloat8_t const *ptr) { return vld1_mf8_x2(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16x2_t load1_x2(mfloat8_t const *ptr) { return vld1q_mf8_x2(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x8x3_t load1_x3(mfloat8_t const *ptr) { return vld1_mf8_x3(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16x3_t load1_x3(mfloat8_t const *ptr) { return vld1q_mf8_x3(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x8x4_t load1_x4(mfloat8_t const *ptr) { return vld1_mf8_x4(ptr); }
template <> [[gnu::always_inline]] inline mfloat8x16x4_t load1_x4(mfloat8_t const *ptr) { return vld1q_mf8_x4(ptr); }
template <> [[gnu::always_inline]] inline void store1(mfloat8_t *ptr, mfloat8x8_t val) { return vst1_mf8(ptr, val); }
template <> [[gnu::always_inline]] inline void store1(mfloat8_t *ptr, mfloat8x16_t val) { return vst1q_mf8(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(mfloat8_t *ptr, mfloat8x8_t val) { return vst1_lane_mf8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store1_lane(mfloat8_t *ptr, mfloat8x16_t val) { return vst1q_lane_mf8(ptr, val, lane); }
template <> [[gnu::always_inline]] inline void store2(mfloat8_t *ptr, mfloat8x8x2_t val) { return vst2_mf8(ptr, val); }
template <> [[gnu::always_inline]] inline void store2(mfloat8_t *ptr, mfloat8x16x2_t val) { return vst2q_mf8(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(mfloat8_t *ptr, mfloat8x8x3_t val) { return vst3_mf8(ptr, val); }
template <> [[gnu::always_inline]] inline void store3(mfloat8_t *ptr, mfloat8x16x3_t val) { return vst3q_mf8(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(mfloat8_t *ptr, mfloat8x8x4_t val) { return vst4_mf8(ptr, val); }
template <> [[gnu::always_inline]] inline void store4(mfloat8_t *ptr, mfloat8x16x4_t val) { return vst4q_mf8(ptr, val); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(mfloat8_t *ptr, mfloat8x8x2_t val) { return vst2_lane_mf8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(mfloat8_t *ptr, mfloat8x8x3_t val) { return vst3_lane_mf8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(mfloat8_t *ptr, mfloat8x8x4_t val) { return vst4_lane_mf8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store2_lane(mfloat8_t *ptr, mfloat8x16x2_t val) { return vst2q_lane_mf8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store3_lane(mfloat8_t *ptr, mfloat8x16x3_t val) { return vst3q_lane_mf8(ptr, val, lane); }
template <int lane>[[gnu::always_inline]] nce void store4_lane(mfloat8_t *ptr, mfloat8x16x4_t val) { return vst4q_lane_mf8(ptr, val, lane); }
[[gnu::always_inline]] inline void store1_x2(mfloat8_t *ptr, mfloat8x8x2_t val) { return vst1_mf8_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x2(mfloat8_t *ptr, mfloat8x16x2_t val) { return vst1q_mf8_x2(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(mfloat8_t *ptr, mfloat8x8x3_t val) { return vst1_mf8_x3(ptr, val); }
[[gnu::always_inline]] inline void store1_x3(mfloat8_t *ptr, mfloat8x16x3_t val) { return vst1q_mf8_x3(ptr, val); }
[[gnu::always_inline]] nce mfloat8x8_t table_lookup1(mfloat8x8_t a, uint8x8_t idx) { return vtbl1_mf8(a, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_extend1(mfloat8x8_t a, mfloat8x8_t b, uint8x8_t idx) { return vtbx1_mf8(a, b, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_lookup2(mfloat8x8x2_t a, uint8x8_t idx) { return vtbl2_mf8(a, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_lookup3(mfloat8x8x3_t a, uint8x8_t idx) { return vtbl3_mf8(a, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_lookup4(mfloat8x8x4_t a, uint8x8_t idx) { return vtbl4_mf8(a, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_lookup1_saturate(mfloat8x16_t t, uint8x8_t idx) { return vqtbl1_mf8(t, idx); }
[[gnu::always_inline]] nce mfloat8x16_t table_lookup1_saturate(mfloat8x16_t t, uint8x16_t idx) { return vqtbl1q_mf8(t, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_lookup2_saturate(mfloat8x16x2_t t, uint8x8_t idx) { return vqtbl2_mf8(t, idx); }
[[gnu::always_inline]] nce mfloat8x16_t table_lookup2_saturate(mfloat8x16x2_t t, uint8x16_t idx) { return vqtbl2q_mf8(t, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_lookup3_saturate(mfloat8x16x3_t t, uint8x8_t idx) { return vqtbl3_mf8(t, idx); }
[[gnu::always_inline]] nce mfloat8x16_t table_lookup3_saturate(mfloat8x16x3_t t, uint8x16_t idx) { return vqtbl3q_mf8(t, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_lookup4_saturate(mfloat8x16x4_t t, uint8x8_t idx) { return vqtbl4_mf8(t, idx); }
[[gnu::always_inline]] nce mfloat8x16_t table_lookup4_saturate(mfloat8x16x4_t t, uint8x16_t idx) { return vqtbl4q_mf8(t, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_extend2(mfloat8x8_t a, mfloat8x8x2_t b, uint8x8_t idx) { return vtbx2_mf8(a, b, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_extend3(mfloat8x8_t a, mfloat8x8x3_t b, uint8x8_t idx) { return vtbx3_mf8(a, b, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_extend4(mfloat8x8_t a, mfloat8x8x4_t b, uint8x8_t idx) { return vtbx4_mf8(a, b, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_extend1_saturate(mfloat8x8_t a, mfloat8x16_t t, uint8x8_t idx) { return vqtbx1_mf8(a, t, idx); }
[[gnu::always_inline]] nce mfloat8x16_t table_extend1_saturate(mfloat8x16_t a, mfloat8x16_t t, uint8x16_t idx) { return vqtbx1q_mf8(a, t, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_extend2_saturate(mfloat8x8_t a, mfloat8x16x2_t t, uint8x8_t idx) { return vqtbx2_mf8(a, t, idx); }
[[gnu::always_inline]] nce mfloat8x16_t table_extend2_saturate(mfloat8x16_t a, mfloat8x16x2_t t, uint8x16_t idx) { return vqtbx2q_mf8(a, t, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_extend3_saturate(mfloat8x8_t a, mfloat8x16x3_t t, uint8x8_t idx) { return vqtbx3_mf8(a, t, idx); }
[[gnu::always_inline]] nce mfloat8x16_t table_extend3_saturate(mfloat8x16_t a, mfloat8x16x3_t t, uint8x16_t idx) { return vqtbx3q_mf8(a, t, idx); }
[[gnu::always_inline]] nce mfloat8x8_t table_extend4_saturate(mfloat8x8_t a, mfloat8x16x4_t t, uint8x8_t idx) { return vqtbx4_mf8(a, t, idx); }
[[gnu::always_inline]] nce mfloat8x16_t table_extend4_saturate(mfloat8x16_t a, mfloat8x16x4_t t, uint8x16_t idx) { return vqtbx4q_mf8(a, t, idx); }
template <> [[gnu::always_inline]] nce bfloat16x4_t reinterpret(mfloat8x8_t a) { return vreinterpret_bf16_mf8(a); }
template <> [[gnu::always_inline]] nce bfloat16x8_t reinterpret(mfloat8x16_t a) { return vreinterpretq_bf16_mf8(a); }
template <> [[gnu::always_inline]] nce mfloat8x8_t reinterpret(bfloat16x4_t a) { return vreinterpret_mf8_bf16(a); }
template <> [[gnu::always_inline]] nce mfloat8x16_t reinterpret(bfloat16x8_t a) { return vreinterpretq_mf8_bf16(a); }
#endif
