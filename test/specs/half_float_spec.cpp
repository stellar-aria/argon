#include "argon.hpp"
#include "cppspec.hpp"
#include <array>
#include <cmath>
#include <limits>

// clang-format off

// Argon<float16_t> wherever half-precision vector arithmetic exists: MVE-F (Cortex-M55) or NEON with
// FEAT_FP16 (Cortex-A55). Results are compared as float so the spec doesn't depend on printing __fp16.
#if (defined(__ARM_FEATURE_MVE) && (__ARM_FEATURE_MVE & 2)) || defined(__ARM_FEATURE_FP16_VECTOR_ARITHMETIC)

using H = Argon<float16_t>;
using PH = argon::Predicate<H::vector_type>;

static std::array<float, 8> floats(H v) {
  auto halves = v.to_array();
  std::array<float, 8> out{};
  for (size_t i = 0; i < 8; ++i) out[i] = static_cast<float>(halves[i]);
  return out;
}

static H halves(std::array<float, 8> values) {
  std::array<float16_t, 8> h{};
  for (size_t i = 0; i < 8; ++i) h[i] = static_cast<float16_t>(values[i]);
  return H::Load(h.data());
}

auto describe_construction = describe("Argon<float16_t> construction", ${
  it("broadcasts a scalar", _{
    expect(floats(H{static_cast<float16_t>(1.5f)})).to_equal(std::array<float, 8>{1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f});
  });

  it("loads and stores", _{
    std::array<float16_t, 8> data{};
    for (size_t i = 0; i < 8; ++i) data[i] = static_cast<float16_t>(i * 0.5f);
    std::array<float16_t, 8> out{};
    H::Load(data.data()).StoreTo(out.data());
    for (size_t i = 0; i < 8; ++i) expect(static_cast<float>(out[i])).to_equal(static_cast<float>(data[i]));
  });

  it("reads and writes lanes", _{
    auto v = halves({0, 1, 2, 3, 4, 5, 6, 7});
    expect(static_cast<float>(static_cast<float16_t>(v[5]))).to_equal(5.0f);
    v[2] = static_cast<float16_t>(-2.0f);
    expect(floats(v)).to_equal(std::array<float, 8>{0, 1, -2, 3, 4, 5, 6, 7});
  });
});

auto describe_arithmetic = describe("Argon<float16_t> arithmetic", ${
  it("adds, subtracts and multiplies", _{
    auto a = halves({1, 2, 3, 4, 5, 6, 7, 8});
    auto b = halves({0.5f, 0.5f, 0.5f, 0.5f, 2, 2, 2, 2});
    expect(floats(a + b)).to_equal(std::array<float, 8>{1.5f, 2.5f, 3.5f, 4.5f, 7, 8, 9, 10});
    expect(floats(a - b)).to_equal(std::array<float, 8>{0.5f, 1.5f, 2.5f, 3.5f, 3, 4, 5, 6});
    expect(floats(a * b)).to_equal(std::array<float, 8>{0.5f, 1, 1.5f, 2, 10, 12, 14, 16});
  });

  it("multiply-adds", _{
    auto acc = halves({1, 1, 1, 1, 1, 1, 1, 1});
    auto r = acc.MultiplyAdd(halves({1, 2, 3, 4, 5, 6, 7, 8}), halves({2, 2, 2, 2, 2, 2, 2, 2}));
    expect(floats(r)).to_equal(std::array<float, 8>{3, 5, 7, 9, 11, 13, 15, 17});
  });

  it("multiply-adds and multiply-subtracts by a scalar", _{
    auto acc = halves({1, 1, 1, 1, 1, 1, 1, 1});
    auto b = halves({1, 2, 3, 4, 5, 6, 7, 8});
    expect(floats(acc.MultiplyAdd(b, static_cast<float16_t>(2)))).to_equal(std::array<float, 8>{3, 5, 7, 9, 11, 13, 15, 17});
    expect(floats(acc.MultiplySubtract(b, static_cast<float16_t>(2)))).to_equal(std::array<float, 8>{-1, -3, -5, -7, -9, -11, -13, -15});
    expect(floats(acc.MultiplySubtract(b, halves({2, 2, 2, 2, 2, 2, 2, 2})))).to_equal(std::array<float, 8>{-1, -3, -5, -7, -9, -11, -13, -15});
  });

  it("takes max, min, abs and negates", _{
    auto a = halves({-1, 2, -3, 4, -5, 6, -7, 8});
    auto z = halves({0, 0, 0, 0, 0, 0, 0, 0});
    expect(floats(a.Max(z))).to_equal(std::array<float, 8>{0, 2, 0, 4, 0, 6, 0, 8});
    expect(floats(a.Min(z))).to_equal(std::array<float, 8>{-1, 0, -3, 0, -5, 0, -7, 0});
    expect(floats(a.Absolute())).to_equal(std::array<float, 8>{1, 2, 3, 4, 5, 6, 7, 8});
    expect(floats(a.Negate())).to_equal(std::array<float, 8>{1, -2, 3, -4, 5, -6, 7, -8});
  });

  it("takes IEEE maxNum / minNum: a NaN gives the other operand, +0 > -0", _{
    const float nan = std::numeric_limits<float>::quiet_NaN();
    auto a = halves({1, nan, -0.0f, 0, 4, -4, nan, 2});
    auto b = halves({2, 3, 0, -0.0f, nan, -5, 1, 2});
    expect(floats(a.MaxNumber(b))).to_equal(std::array<float, 8>{2, 3, 0, 0, 4, -4, 1, 2});
    expect(floats(a.MinNumber(b))).to_equal(std::array<float, 8>{1, 3, -0.0f, -0.0f, 4, -5, 1, 2});
    expect(std::signbit(floats(a.MaxNumber(b))[2])).to_be_false();
    expect(std::signbit(floats(a.MinNumber(b))[3])).to_be_true();
  });

  it("finds the maximum and minimum in every lane", _{
    for (size_t at = 0; at < 8; ++at) {
      std::array<float, 8> values = {1.5f, -2, 0.25f, 3, -0.5f, 2, 1, -1};
      values[at] = 100;
      expect(static_cast<float>(halves(values).ReduceMax())).to_equal(100.0f);
      values[at] = -100;
      expect(static_cast<float>(halves(values).ReduceMin())).to_equal(-100.0f);
    }
  });

  it("sums the lanes", _{
    expect(static_cast<float>(halves({1, 2, 3, 4, 5, 6, 7, 8}).ReduceAdd())).to_equal(36.0f);
  });

  it("reverses the lanes", _{
    expect(floats(halves({0, 1, 2, 3, 4, 5, 6, 7}).Reverse())).to_equal(std::array<float, 8>{7, 6, 5, 4, 3, 2, 1, 0});
  });
});

auto describe_predicates = describe("Argon<float16_t> predicates", ${
  it("compares lanes", _{
    auto a = halves({1, 2, 3, 4, 5, 6, 7, 8});
    auto b = halves({4, 4, 4, 4, 4, 4, 4, 4});
    expect((a < b).to_array()).to_equal(std::array<bool, 8>{true, true, true, false, false, false, false, false});
    expect((a == b).to_array()).to_equal(std::array<bool, 8>{false, false, false, true, false, false, false, false});
    expect((a >= b).Count()).to_equal(size_t{5});
  });

  it("selects and runs predicated operations", _{
    auto a = halves({1, 2, 3, 4, 5, 6, 7, 8});
    auto p = a > halves({4, 4, 4, 4, 4, 4, 4, 4});
    auto z = halves({0, 0, 0, 0, 0, 0, 0, 0});
    expect(floats(p.Select(a, z))).to_equal(std::array<float, 8>{0, 0, 0, 0, 5, 6, 7, 8});
    expect(floats(a.Add(a, p, z))).to_equal(std::array<float, 8>{0, 0, 0, 0, 10, 12, 14, 16});
  });

  it("loads and stores a tail", _{
    std::array<float16_t, 8> data{};
    for (size_t i = 0; i < 8; ++i) data[i] = static_cast<float16_t>(i + 1);
    expect(floats(H::Load(data.data(), PH::FirstN(3)))).to_equal(std::array<float, 8>{1, 2, 3, 0, 0, 0, 0, 0});
    std::array<float16_t, 8> out{};
    H{static_cast<float16_t>(9.0f)}.StoreTo(out.data(), PH::FirstN(2));
    expect(static_cast<float>(out[1])).to_equal(9.0f);
    expect(static_cast<float>(out[2])).to_equal(0.0f);
  });

  it("gathers by index", _{
    std::array<float16_t, 16> table{};
    for (size_t i = 0; i < 16; ++i) table[i] = static_cast<float16_t>(i * 2);
    auto v = H::LoadGatherOffsetIndex(table.data(), Argon<uint16_t>{15, 0, 7, 1, 14, 2, 13, 3});
    expect(floats(v)).to_equal(std::array<float, 8>{30, 0, 14, 2, 28, 4, 26, 6});
  });
});

CPPSPEC_MAIN(
  describe_construction,
  describe_arithmetic,
  describe_predicates
);

#else
CPPSPEC_MAIN()
#endif
