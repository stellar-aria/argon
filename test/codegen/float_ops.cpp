// Every Argon<float> operation here must compile to 128-bit NEON on AArch32 (checked by check_neon_float.sh).
// GCC scalarises generic vector-extension float arithmetic, comparisons and ?: to VFP there (NEON flushes
// denormals, so it isn't IEEE), and its arm_neon.h implements vc{lt,gt,le,ge}q_f32 the same way.
#include "argon.hpp"

using F = Argon<float>;
using U = Argon<uint32_t>;

F add(F a, F b) { return a + b; }
F subtract(F a, F b) { return a - b; }
F multiply(F a, F b) { return a * b; }
F multiply_scalar(F a, float b) { return a * b; }
F multiply_add(F a, F b, F c) { return a.MultiplyAdd(b, c); }
F multiply_add_scalar(F a, F b, float c) { return a.MultiplyAdd(b, c); }
F multiply_subtract(F a, F b, F c) { return a.MultiplySubtract(b, c); }
U less_than(F a, F b) { return a < b; }
U greater_than(F a, F b) { return a > b; }
U less_equal(F a, F b) { return a <= b; }
U greater_equal(F a, F b) { return a >= b; }
F select(U m, F a, F b) { return argon::ternary(m, a, b); }
F select_scalars(U m, float a, float b) { return argon::ternary(m, a, b); }
