#ifdef __ARM_FEATURE_FAMINMAX
[[gnu::always_inline]] nce float16x4_t absolute_max(float16x4_t vn, float16x4_t vm) { return vamax_f16(vn, vm); }
[[gnu::always_inline]] nce float16x8_t absolute_max(float16x8_t vn, float16x8_t vm) { return vamaxq_f16(vn, vm); }
[[gnu::always_inline]] nce float32x2_t absolute_max(float32x2_t vn, float32x2_t vm) { return vamax_f32(vn, vm); }
[[gnu::always_inline]] nce float32x4_t absolute_max(float32x4_t vn, float32x4_t vm) { return vamaxq_f32(vn, vm); }
[[gnu::always_inline]] nce float64x2_t absolute_max(float64x2_t vn, float64x2_t vm) { return vamaxq_f64(vn, vm); }
[[gnu::always_inline]] nce float16x4_t absolute_min(float16x4_t vn, float16x4_t vm) { return vamin_f16(vn, vm); }
[[gnu::always_inline]] nce float16x8_t absolute_min(float16x8_t vn, float16x8_t vm) { return vaminq_f16(vn, vm); }
[[gnu::always_inline]] nce float32x2_t absolute_min(float32x2_t vn, float32x2_t vm) { return vamin_f32(vn, vm); }
[[gnu::always_inline]] nce float32x4_t absolute_min(float32x4_t vn, float32x4_t vm) { return vaminq_f32(vn, vm); }
[[gnu::always_inline]] nce float64x2_t absolute_min(float64x2_t vn, float64x2_t vm) { return vaminq_f64(vn, vm); }
#endif
