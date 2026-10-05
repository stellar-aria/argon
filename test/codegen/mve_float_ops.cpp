// Every Argon<float> / Argon<float16_t> operation here must compile to Helium vector instructions on the M55
// (checked by check_mve_float.sh): no scalar VFP float arithmetic or comparisons, and every fma_* function must
// use a fused multiply-accumulate. The reduce_* functions end in a scalar add, but must not go through the stack. GCC scalarises vector-extension float `?:` on MVE, and never contracts
// vector-extension `a + b * c` into vfma there.
#include "argon.hpp"

using F = Argon<float>;
using H = Argon<float16_t>;

#ifdef __clang__
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"  // C names for the checker, C++ types
#endif

extern "C" {

F max(F a, F b) { return a.Max(b); }
F min(F a, F b) { return a.Min(b); }
F max_scalar(F a, float b) { return a.Max(b); }
F min_scalar(F a, float b) { return a.Min(b); }
F clamp(F a) { return a.Max(-1.f).Min(1.f); }
H max_half(H a, H b) { return a.Max(b); }
H min_half(H a, H b) { return a.Min(b); }

F fma_vector(F a, F b, F c) { return a.MultiplyAdd(b, c); }
F fma_scalar(F a, F b, float c) { return a.MultiplyAdd(b, c); }
F fma_scalar_first(F a, float b, F c) { return a.MultiplyAdd(b, c); }
F fma_subtract_vector(F a, F b, F c) { return a.MultiplySubtract(b, c); }
F fma_subtract_scalar(F a, F b, float c) { return a.MultiplySubtract(b, c); }
H fma_half_vector(H a, H b, H c) { return a.MultiplyAdd(b, c); }
H fma_half_scalar(H a, H b, float16_t c) { return a.MultiplyAdd(b, c); }
H fma_half_subtract_vector(H a, H b, H c) { return a.MultiplySubtract(b, c); }

float reduce_add(F a) { return a.ReduceAdd(); }
float16_t reduce_add_half(H a) { return a.ReduceAdd(); }
float reduce_max(F a) { return a.ReduceMax(); }
float reduce_min(F a) { return a.ReduceMin(); }
float16_t reduce_max_half(H a) { return a.ReduceMax(); }
float16_t reduce_min_half(H a) { return a.ReduceMin(); }
}
