#include "argon.hpp"
#include "argon/vectorize/for_each.hpp"
#include "cppspec.hpp"
#include <cstdint>
#include <limits>
#include <numeric>
#include <vector>

// clang-format off

constexpr std::ptrdiff_t sizes[] = {0, 1, 3, 4, 5, 7, 8, 9, 15, 16, 17, 31, 33, 100};

auto describe_for_each = describe("vectorize::for_each", ${
  it("updates every element and nothing past the range (uint8)", _{
    for (auto n : sizes) {
      std::vector<uint8_t> a(n + 16, 7), d(n + 16, 200);
      std::iota(d.begin(), d.begin() + n, uint8_t{1});
      auto expected = d;
      for (std::ptrdiff_t i = 0; i < n; ++i) expected[i] = static_cast<uint8_t>(d[i] + a[i]);
      argon::vectorize::for_each<uint8_t>(n, [&](auto step) { step.Store(d.data(), step.Load(d.data()) + step.Load(a.data())); });
      expect(d).to_equal(expected);
    }
  });

  it("interpolates floats", _{
    for (auto n : sizes) {
      std::vector<float> a(n + 4), b(n + 4), out(n + 4, -1.0f), expected(n + 4, -1.0f);
      for (std::ptrdiff_t i = 0; i < n; ++i) { a[i] = float(i); b[i] = float(3 * i); expected[i] = a[i] + (b[i] - a[i]) * 0.5f; }
      argon::vectorize::for_each<float>(n, [&](auto step) {
        step.Store(out.data(), step.Load(a.data()) + (step.Load(b.data()) - step.Load(a.data())) * 0.5f);
      });
      expect(out).to_equal(expected);
    }
  });

  it("reduces with active() keeping out-of-range lanes out", _{
    for (auto n : sizes) {
      std::vector<int32_t> x(n + 4);
      std::iota(x.begin(), x.end(), 1);
      int32_t sum = 0;
      int32_t smallest = std::numeric_limits<int32_t>::max();
      argon::vectorize::for_each<int32_t>(n, [&](auto step) {
        auto v = step.Load(x.data());
        sum += v.ReduceAdd(step.active());
        smallest = std::min(smallest, step.active().Select(v, Argon<int32_t>{std::numeric_limits<int32_t>::max()}).ReduceMin());
      });
      expect(sum).to_equal(int32_t(n * (n + 1) / 2));
      expect(smallest).to_equal(n > 0 ? int32_t{1} : std::numeric_limits<int32_t>::max());
    }
  });

  it("reports index and count for every step", _{
    std::vector<std::ptrdiff_t> indices, counts;
    argon::vectorize::for_each<int16_t>(19, [&](auto step) { indices.push_back(step.index()); counts.push_back(step.count()); });
    expect(indices).to_equal(std::vector<std::ptrdiff_t>{0, 8, 16});
    expect(counts).to_equal(std::vector<std::ptrdiff_t>{8, 8, 3});
  });

  it("widens int16 samples into int32 lanes and narrows them back", _{
    for (auto n : sizes) {
      std::vector<int16_t> in(n + 8), out(n + 8, int16_t{-1}), expected(n + 8, int16_t{-1});
      for (std::ptrdiff_t i = 0; i < n; ++i) { in[i] = int16_t(i * 700 - 9000); expected[i] = int16_t((int32_t(in[i]) * 3) >> 2); }
      argon::vectorize::for_each<int32_t>(n, [&](auto step) {
        step.StoreNarrow(out.data(), (step.LoadWiden(in.data()) * 3) >> 2);
      });
      expect(out).to_equal(expected);
    }
  });
});

CPPSPEC_MAIN(describe_for_each);
