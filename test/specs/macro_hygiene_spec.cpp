// Argon's helper macros (simd, ace, nce) are internal: every header undefines them again, so including one
// on its own leaves nothing behind in the includer's namespace of names.
#include "argon/lane.hpp"
#include "arm_simd/helpers/get_lane.hpp"
#include "arm_simd/helpers/load.hpp"
#include "arm_simd/helpers/multivector.hpp"
#if defined(simd) || defined(ace) || defined(nce)
#error "an Argon header leaked one of its internal macros (simd, ace or nce)"
#endif
#include "argon.hpp"
#include "cppspec.hpp"

// clang-format off
auto hygiene = describe("header macro hygiene", ${
  it("leaves no internal macro defined after including individual headers", _{ expect(true).to_equal(true); });
});

CPPSPEC_MAIN(hygiene);
