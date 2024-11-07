#pragma once
#include <arm_neon.h>
#ifdef __cplusplus
#ifdef __clang__
#define nce constexpr
#else
#define nce inline
#endif

namespace neon {
template <int lane>[[gnu::always_inline]] nce float64_t get_lane(float64x1_t v) { return vget_lane_f64(v, lane); }
template <int lane>[[gnu::always_inline]] nce float64_t get_lane(float64x2_t v) { return vgetq_lane_f64(v, lane); }
}
#endif
#undef nce
