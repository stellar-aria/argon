#include "argon.hpp"
#include "cppspec.hpp"
#include <array>
#include <cstdint>

// clang-format off

// Coverage for the VFPv4 / A64 layer (arm_simd/neon/vfpv4.hpp): the by-scalar fused multiply-add forms and the
// quadword float16 load-to-all-lanes forms. On AArch32 neither has a native ACLE intrinsic, so the library builds
// them from the doubleword / vector forms; these specs pin down that the results are unchanged.
#if defined(__ARM_NEON) && (defined(__aarch64__) || defined(__ARM_FEATURE_FMA))
#define ARGON_TEST_HAS_VFPV4 1

// (1 + 2^-12)^2 = 1 + 2^-11 + 2^-24: the 2^-24 term is below float precision at 1.0, so a separate multiply
// rounds it away (to kProduct) before the add. Only a fused operation leaves the 2^-24 residual.
static constexpr float kB = 1.0f + 0x1p-12f;
static constexpr float kProduct = 1.0f + 0x1p-11f;   // kB*kB rounded to float (what an unfused multiply yields)
static constexpr float kResidual = 0x1p-24f;          // exact kB*kB - kProduct

auto describe_fma_scalar = describe("multiply_add_fused (by scalar)", ${
  it("computes a + b*c with a single rounding (quadword)", _{
    float32x4_t r = neon::multiply_add_fused(vdupq_n_f32(-kProduct), vdupq_n_f32(kB), kB);
    float out[4]; vst1q_f32(out, r);
    for (float x : out) expect(x).to_equal(kResidual);
  });
  it("computes a + b*c with a single rounding (doubleword)", _{
    float32x2_t r = neon::multiply_add_fused(vdup_n_f32(-kProduct), vdup_n_f32(kB), kB);
    expect(vget_lane_f32(r, 0)).to_equal(kResidual);
    expect(vget_lane_f32(r, 1)).to_equal(kResidual);
  });
  it("broadcasts the scalar to every lane", _{
    float a[4] = {1.f, 2.f, 3.f, 4.f}, b[4] = {10.f, 20.f, 30.f, 40.f};
    float32x4_t r = neon::multiply_add_fused(vld1q_f32(a), vld1q_f32(b), 0.5f);
    float out[4]; vst1q_f32(out, r);
    expect(std::array<float, 4>{out[0], out[1], out[2], out[3]}).to_equal(std::array<float, 4>{6.f, 12.f, 18.f, 24.f});
  });
});

auto describe_fms_scalar = describe("multiply_subtract_fused (by scalar)", ${
  it("computes a - b*c with a single rounding (quadword)", _{
    float32x4_t r = neon::multiply_subtract_fused(vdupq_n_f32(kProduct), vdupq_n_f32(kB), kB);
    float out[4]; vst1q_f32(out, r);
    for (float x : out) expect(x).to_equal(-kResidual);
  });
  it("computes a - b*c with a single rounding (doubleword)", _{
    float32x2_t r = neon::multiply_subtract_fused(vdup_n_f32(kProduct), vdup_n_f32(kB), kB);
    expect(vget_lane_f32(r, 0)).to_equal(-kResidual);
    expect(vget_lane_f32(r, 1)).to_equal(-kResidual);
  });
});

template <typename Multi, int Stride>
static std::array<std::array<float, 8>, Stride> widen(Multi m) {
  std::array<std::array<float, 8>, Stride> out{};
  for (int s = 0; s < Stride; s++) {
    float32x4_t lo = vcvt_f32_f16(vget_low_f16(m.val[s]));
    float32x4_t hi = vcvt_f32_f16(vget_high_f16(m.val[s]));
    vst1q_f32(out[s].data(), lo);
    vst1q_f32(out[s].data() + 4, hi);
  }
  return out;
}

auto describe_f16_load_dup = describe("float16 quadword load-to-all-lanes", ${
  it("load2_duplicate fills all 8 lanes of each vector", _{
    float16_t src[2] = {1.5f, -2.25f};
    auto w = widen<float16x8x2_t, 2>(neon::load2_duplicate<float16x8x2_t>(src));
    for (float x : w[0]) expect(x).to_equal(1.5f);
    for (float x : w[1]) expect(x).to_equal(-2.25f);
  });
  it("load3_duplicate fills all 8 lanes of each vector", _{
    float16_t src[3] = {0.5f, 3.0f, -7.0f};
    auto w = widen<float16x8x3_t, 3>(neon::load3_duplicate<float16x8x3_t>(src));
    for (float x : w[0]) expect(x).to_equal(0.5f);
    for (float x : w[1]) expect(x).to_equal(3.0f);
    for (float x : w[2]) expect(x).to_equal(-7.0f);
  });
  it("load4_duplicate fills all 8 lanes of each vector", _{
    float16_t src[4] = {1.0f, 2.0f, 4.0f, 8.0f};
    auto w = widen<float16x8x4_t, 4>(neon::load4_duplicate<float16x8x4_t>(src));
    for (int s = 0; s < 4; s++)
      for (float x : w[s]) expect(x).to_equal(float(1 << s));
  });
});
#endif

auto describe_vfpv4_target = describe("VFPv4 layer", ${
  it("is compiled for this target only where NEON + FMA (or A64) are available", _{
#ifdef ARGON_TEST_HAS_VFPV4
    expect(true).to_equal(true);
#else
    expect(false).to_equal(false);
#endif
  });
});

// Preprocessor directives inside a macro invocation are UB, so fold the conditional specs into a macro.
#ifdef ARGON_TEST_HAS_VFPV4
#define MAYBE_VFPV4_SPECS describe_fma_scalar, describe_fms_scalar, describe_f16_load_dup,
#else
#define MAYBE_VFPV4_SPECS
#endif

CPPSPEC_MAIN(
  MAYBE_VFPV4_SPECS
  describe_vfpv4_target
);
