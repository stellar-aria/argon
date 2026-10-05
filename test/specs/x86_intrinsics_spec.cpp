// Argon on x86 (through SIMDe) must leave the real x86 intrinsics usable in the same translation unit: SIMDe's
// global SIMDE_ENABLE_NATIVE_ALIASES would also alias its x86 emulation onto _mm_* / _mm256_*, so Argon enables
// only SIMDe's NEON aliases. The test build defines the global switch for every spec; undo it here.
#undef SIMDE_ENABLE_NATIVE_ALIASES
#include <array>

#include "argon.hpp"
#include "cppspec.hpp"

#if defined(__x86_64__) || defined(__i386__)
#include <immintrin.h>

static float SumSse(const float* p) {
  const __m128 v = _mm_loadu_ps(p);
  const __m128 s = _mm_add_ps(v, _mm_movehl_ps(v, v));
  return _mm_cvtss_f32(_mm_add_ss(s, _mm_shuffle_ps(s, s, 1)));
}

[[gnu::target("avx2,fma")]] static float SumAvx2(const float* p) {
  const __m256 v = _mm256_fmadd_ps(_mm256_loadu_ps(p), _mm256_set1_ps(2.f), _mm256_setzero_ps());
  const __m128 h = _mm_add_ps(_mm256_castps256_ps128(v), _mm256_extractf128_ps(v, 1));
  return SumSse(reinterpret_cast<const float*>(&h));
}

// clang-format off
auto describe_x86 = describe("Argon next to the x86 intrinsics", ${
  it("runs SSE intrinsics and Argon in one translation unit", _{
    const std::array<float, 4> a{1, 2, 3, 4};
    expect(SumSse(a.data())).to_equal(10.0f);
    expect(Argon<float>::Load(a.data()).ReduceAdd()).to_equal(10.0f);
  });

  it("runs an AVX2 + FMA function where the CPU has them", _{
    if (!__builtin_cpu_supports("avx2") || !__builtin_cpu_supports("fma")) return;
    const std::array<float, 8> a{1, 2, 3, 4, 5, 6, 7, 8};
    expect(SumAvx2(a.data())).to_equal(72.0f);
  });
});

CPPSPEC_MAIN(describe_x86);
// clang-format on
#else
CPPSPEC_MAIN();
#endif
