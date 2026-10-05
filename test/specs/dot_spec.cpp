#include "argon.hpp"
#include "cppspec.hpp"
#include <array>
#include <cstdint>
#include <limits>

// clang-format off

// Scalar references for Helium's vmladav family. Every platform must match them, including wraparound.

using Form = argon::DotForm;

template <typename T>
std::array<T, Argon<T>::lanes> sample(int seed) {
  const T values[] = {std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), T(0), T(1), T(-1),
                      T(std::numeric_limits<T>::max() / 3), T(std::numeric_limits<T>::min() / 5), T(97)};
  std::array<T, Argon<T>::lanes> out{};
  for (size_t i = 0; i < out.size(); ++i) out[i] = values[(i * 5 + seed) % 8];
  return out;
}

/// A two's-complement 128-bit integer: just enough arithmetic for the references.
struct I128 {
  uint64_t lo = 0, hi = 0;
  static I128 from(int64_t v) { return {static_cast<uint64_t>(v), v < 0 ? ~uint64_t{0} : 0}; }
  static I128 from_unsigned(uint64_t v) { return {v, 0}; }
  I128 operator+(I128 o) const {
    I128 r{lo + o.lo, hi + o.hi};
    r.hi += r.lo < lo;
    return r;
  }
  I128 negate() const { return I128{~lo, ~hi} + I128{1, 0}; }
  /// Arithmetic shift right by 8, then truncate to 64 bits.
  uint64_t shift8() const { return (lo >> 8) | (hi << 56); }
};

/// The terms Σ of `form`, exact, as 128-bit values.
template <typename T>
std::array<I128, Argon<T>::lanes> terms(const std::array<T, Argon<T>::lanes>& a, const std::array<T, Argon<T>::lanes>& b,
                                        Form form) {
  const bool exchange = form == Form::Exchange || form == Form::SubtractExchange;
  std::array<I128, Argon<T>::lanes> out{};
  for (size_t i = 0; i < out.size(); ++i) {
    const size_t j = exchange ? (i ^ 1) : i;
    I128 p = std::is_signed_v<T> ? I128::from(int64_t{a[i]} * int64_t{b[j]})
                                 : I128::from_unsigned(uint64_t(a[i]) * uint64_t(b[j]));
    // vmlsdav: a[2i]·b[2i] − a[2i+1]·b[2i+1]; vmlsdavx: a[2i+1]·b[2i] − a[2i]·b[2i+1]
    const bool negate = form == Form::Subtract ? (i & 1) : (form == Form::SubtractExchange && !(i & 1));
    out[i] = negate ? p.negate() : p;
  }
  return out;
}

template <typename T>
I128 sum_ref(const std::array<T, Argon<T>::lanes>& a, const std::array<T, Argon<T>::lanes>& b, Form form, I128 acc) {
  for (auto t : terms<T>(a, b, form)) acc = acc + t;
  return acc;
}

template <typename T>
void check_dot(auto& self, Form form) {
  using V = Argon<T>;
  auto a_in = sample<T>(0), b_in = sample<T>(3);
  auto a = V::Load(a_in.data()), b = V::Load(b_in.data());
  using D = typename V::dot_type;
  const D acc = static_cast<D>(12345);
  const auto ref = static_cast<D>(sum_ref<T>(a_in, b_in, form, I128::from(acc)).lo);
  D got{};
  switch (form) {
    case Form::Plain: got = a.DotProduct(b, acc); break;
    case Form::Exchange: if constexpr (std::is_signed_v<T>) got = a.template DotProduct<Form::Exchange>(b, acc); break;
    case Form::Subtract: if constexpr (std::is_signed_v<T>) got = a.template DotProduct<Form::Subtract>(b, acc); break;
    case Form::SubtractExchange: if constexpr (std::is_signed_v<T>) got = a.template DotProduct<Form::SubtractExchange>(b, acc); break;
  }
  expect(got).to_equal(ref);
}

template <typename T>
void check_dot_long(auto& self, Form form) {
  using V = Argon<T>;
  auto a_in = sample<T>(1), b_in = sample<T>(6);
  auto a = V::Load(a_in.data()), b = V::Load(b_in.data());
  using D = typename V::dot_long_type;
  const D acc = static_cast<D>(-987654321);
  const auto ref = static_cast<D>(sum_ref<T>(a_in, b_in, form, std::is_signed_v<T> ? I128::from(int64_t(acc)) : I128::from_unsigned(uint64_t(acc))).lo);
  D got{};
  switch (form) {
    case Form::Plain: got = a.DotProductLong(b, acc); break;
    case Form::Exchange: if constexpr (std::is_signed_v<T>) got = a.template DotProductLong<Form::Exchange>(b, acc); break;
    case Form::Subtract: if constexpr (std::is_signed_v<T>) got = a.template DotProductLong<Form::Subtract>(b, acc); break;
    case Form::SubtractExchange: if constexpr (std::is_signed_v<T>) got = a.template DotProductLong<Form::SubtractExchange>(b, acc); break;
  }
  expect(got).to_equal(ref);
}

template <typename T>
void check_round_high(auto& self, Form form) {
  using V = Argon<T>;
  auto a_in = sample<T>(2), b_in = sample<T>(7);
  auto a = V::Load(a_in.data()), b = V::Load(b_in.data());
  using D = typename V::dot_long_type;
  const D acc = static_cast<D>(4242);
  // acc + Σ floor((p + 128) / 256), each product rounded on its own
  uint64_t ref_sum = uint64_t(acc);
  for (auto t : terms<T>(a_in, b_in, form)) ref_sum += (t + I128{128, 0}).shift8();
  const auto ref = static_cast<D>(ref_sum);
  D got{};
  switch (form) {
    case Form::Plain: got = a.DotProductRoundHigh(b, acc); break;
    case Form::Exchange: if constexpr (std::is_signed_v<T>) got = a.template DotProductRoundHigh<Form::Exchange>(b, acc); break;
    case Form::Subtract: if constexpr (std::is_signed_v<T>) got = a.template DotProductRoundHigh<Form::Subtract>(b, acc); break;
    case Form::SubtractExchange: if constexpr (std::is_signed_v<T>) got = a.template DotProductRoundHigh<Form::SubtractExchange>(b, acc); break;
  }
  expect(got).to_equal(ref);
}

constexpr Form all_forms[] = {Form::Plain, Form::Exchange, Form::Subtract, Form::SubtractExchange};

auto describe_dot = describe("DotProduct", ${
  it("int8, every form", _{ for (auto f : all_forms) check_dot<int8_t>(self, f); });
  it("uint8", _{ check_dot<uint8_t>(self, Form::Plain); });
  it("int16, every form", _{ for (auto f : all_forms) check_dot<int16_t>(self, f); });
  it("uint16", _{ check_dot<uint16_t>(self, Form::Plain); });
  it("int32, every form (wrapping)", _{ for (auto f : all_forms) check_dot<int32_t>(self, f); });
  it("uint32 (wrapping)", _{ check_dot<uint32_t>(self, Form::Plain); });
  it("defaults the accumulator to zero", _{
    auto a = Argon<int16_t>{1, 2, 3, 4, 5, 6, 7, 8};
    expect(a.DotProduct(Argon<int16_t>{2})).to_equal(int32_t{72});
  });
});

auto describe_dot_long = describe("DotProductLong", ${
  it("int16, every form", _{ for (auto f : all_forms) check_dot_long<int16_t>(self, f); });
  it("uint16", _{ check_dot_long<uint16_t>(self, Form::Plain); });
  it("int32, every form", _{ for (auto f : all_forms) check_dot_long<int32_t>(self, f); });
  it("uint32", _{ check_dot_long<uint32_t>(self, Form::Plain); });
});

auto describe_round_high = describe("DotProductRoundHigh", ${
  it("int32, every form", _{ for (auto f : all_forms) check_round_high<int32_t>(self, f); });
  it("uint32", _{ check_round_high<uint32_t>(self, Form::Plain); });
});

auto describe_round_high_rounding = describe("DotProductRoundHigh rounding", ${
  it("rounds each product separately", _{
    // 128/256 rounds up to 1 per product, so two of them give 2; 64/256 rounds to 0, so four of them give 0
    expect(Argon<int32_t>{128, 128, 0, 0}.DotProductRoundHigh(Argon<int32_t>{1})).to_equal(int64_t{2});
    expect(Argon<int32_t>{64, 64, 64, 64}.DotProductRoundHigh(Argon<int32_t>{1})).to_equal(int64_t{0});
    expect(Argon<int32_t>{-129, 0, 0, 0}.DotProductRoundHigh(Argon<int32_t>{1}, int64_t{10})).to_equal(int64_t{9});
  });
});

auto describe_complex = describe("ComplexDotProduct", ${
  it("multiplies interleaved complex pairs", _{
    // (1+2i)(3+4i) + (5+6i)(7+8i) + (−1+0i)(2−3i) + (0+1i)(0+1i) = (−5+10i) + (−13+82i) + (−2+3i) + (−1)
    auto a = Argon<int16_t>{1, 2, 5, 6, -1, 0, 0, 1};
    auto b = Argon<int16_t>{3, 4, 7, 8, 2, -3, 0, 1};
    auto [re, im] = a.ComplexDotProduct(b);
    expect(re).to_equal(int32_t{-21});
    expect(im).to_equal(int32_t{95});
  });
});

CPPSPEC_MAIN(
  describe_dot,
  describe_dot_long,
  describe_round_high,
  describe_round_high_rounding,
  describe_complex
);
