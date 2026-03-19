#include "argon.hpp"
#include "cppspec.hpp"
#include <cmath>

// clang-format off

// ── ReciprocalEstimate ─────────────────────────────────────────────────────

auto describe_reciprocal_estimate = describe("ReciprocalEstimate float32", ${
  it("produces an estimate close to 1/x for positive values", _{
    std::array<float, 4> data = {1.0f, 2.0f, 4.0f, 8.0f};
    auto v = Argon<float>::Load(data.data());
    auto est = v.ReciprocalEstimate().to_array();
    // NEON vrecpe gives ~8-bit accuracy; check relative error < 1%
    for (size_t i = 0; i < Argon<float>::lanes; ++i) {
      float expected = 1.0f / data[i];
      float rel_err = std::abs(est[i] - expected) / expected;
      expect(rel_err < 0.01f).to_be_true();
    }
  });
});

// ── ReciprocalStep ─────────────────────────────────────────────────────────

auto describe_reciprocal_step = describe("ReciprocalStep float32", ${
  it("Newton-Raphson step tightens estimate of 1/x", _{
    std::array<float, 4> data = {1.0f, 2.0f, 4.0f, 8.0f};
    auto v = Argon<float>::Load(data.data());
    auto est = v.ReciprocalEstimate();
    // One NR step: est2 = est * step(v, est) = est * (2 - v*est)
    // vrecps(*this, b) = 2 - *this * b; pass est as arg, not *this*est
    auto step = v.ReciprocalStep(est);
    auto refined = (est * step).to_array();
    for (size_t i = 0; i < Argon<float>::lanes; ++i) {
      float expected = 1.0f / data[i];
      float rel_err = std::abs(refined[i] - expected) / expected;
      expect(rel_err < 1e-5f).to_be_true();
    }
  });
});

// ── ReciprocalSqrtEstimate ─────────────────────────────────────────────────

auto describe_reciprocal_sqrt_estimate = describe("ReciprocalSqrtEstimate float32", ${
  it("produces an estimate close to 1/sqrt(x) for positive values", _{
    std::array<float, 4> data = {1.0f, 4.0f, 9.0f, 16.0f};
    auto v = Argon<float>::Load(data.data());
    auto est = v.ReciprocalSqrtEstimate().to_array();
    for (size_t i = 0; i < Argon<float>::lanes; ++i) {
      float expected = 1.0f / std::sqrt(data[i]);
      float rel_err = std::abs(est[i] - expected) / expected;
      expect(rel_err < 0.01f).to_be_true();
    }
  });
});

// ── ReciprocalSqrtStep ─────────────────────────────────────────────────────

auto describe_reciprocal_sqrt_step = describe("ReciprocalSqrtStep float32", ${
  it("Newton-Raphson step tightens estimate of 1/sqrt(x)", _{
    std::array<float, 4> data = {1.0f, 4.0f, 9.0f, 16.0f};
    auto v = Argon<float>::Load(data.data());
    auto est = v.ReciprocalSqrtEstimate();
    // Standard NR for rsqrt: est2 = est * step(v*est, est) * 0.5
    // step(a,b) = (3 - a*b) * 0.5
    // vrsqrts(a,b) = (3-a*b)/2; need (v*est) as receiver, est as arg
    auto refined = (est * (v * est).ReciprocalSqrtStep(est)).to_array();
    for (size_t i = 0; i < Argon<float>::lanes; ++i) {
      float expected = 1.0f / std::sqrt(data[i]);
      float rel_err = std::abs(refined[i] - expected) / expected;
      expect(rel_err < 1e-5f).to_be_true();
    }
  });
});

// ── ReciprocalEstimateRefine ───────────────────────────────────────────────

auto describe_reciprocal_refine = describe("ReciprocalEstimateRefine float32", ${
  it("1 iteration of NR gives high-precision reciprocal", _{
    std::array<float, 4> data = {1.0f, 3.0f, 7.0f, 11.0f};
    auto v = Argon<float>::Load(data.data());
    auto result = v.ReciprocalEstimateRefine(1).to_array();
    for (size_t i = 0; i < Argon<float>::lanes; ++i) {
      float expected = 1.0f / data[i];
      float rel_err = std::abs(result[i] - expected) / expected;
      expect(rel_err < 1e-5f).to_be_true();
    }
  });
});

// ── ReciprocalSqrtEstimateRefine ───────────────────────────────────────────

auto describe_reciprocal_sqrt_refine = describe("ReciprocalSqrtEstimateRefine float32", ${
  it("2 iterations of NR gives high-precision reciprocal square root", _{
    std::array<float, 4> data = {2.0f, 5.0f, 10.0f, 20.0f};
    auto v = Argon<float>::Load(data.data());
    auto result = v.ReciprocalSqrtEstimateRefine(2).to_array();
    for (size_t i = 0; i < Argon<float>::lanes; ++i) {
      float expected = 1.0f / std::sqrt(data[i]);
      float rel_err = std::abs(result[i] - expected) / expected;
      expect(rel_err < 1e-5f).to_be_true();
    }
  });
});

CPPSPEC_MAIN(
  describe_reciprocal_estimate,
  describe_reciprocal_step,
  describe_reciprocal_sqrt_estimate,
  describe_reciprocal_sqrt_step,
  describe_reciprocal_refine,
  describe_reciprocal_sqrt_refine
);
