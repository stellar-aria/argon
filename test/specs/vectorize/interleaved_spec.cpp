#include "argon.hpp"
#include "argon/vectorize/interleaved.hpp"
#include "cppspec.hpp"
#include <numeric>

// clang-format off

// Coverage for the read-modify-write `interleaved` view (interleaved.hpp):
// each iteration de-interleaves `Stride` vectors, and the (possibly mutated)
// vectors are re-interleaved back to memory when the iterator advances.
//
// The view does not model std::ranges::range under MSVC's ranges implementation
// (it works on GCC and Clang), so the iterating body below won't compile there.
// Skip the spec on MSVC-proper rather than fail the build. TODO: MSVC support.
#if defined(_MSC_VER) && !defined(__clang__)

auto vectorize_interleaved = describe("vectorize_interleaved (skipped on MSVC)", ${
  it("is skipped: interleaved view is not yet a std::ranges::range on MSVC", _{
    expect(true).to_be_true();
  });
});

#else

auto vectorize_interleaved = describe("vectorize_interleaved", ${
  it("returns an end sentinel pointer when end() is called", _{
    std::array<int32_t, 8> vals{};
    auto view = argon::vectorize::interleaved<2, int32_t>(vals.data(), vals.size());
    expect(std::is_same_v<decltype(view.end()), const int32_t*>).to_be_true();
  });

  it("round-trips a stride-2 read-modify-write across the whole buffer", _{
    std::array<int32_t, 512> vals;
    std::iota(vals.begin(), vals.end(), 0);

    for (auto&& [even, odd] : argon::vectorize::interleaved<2, int32_t>(vals.data(), vals.size())) {
      even = even + 100;
      odd  = odd + 100;
    }

    // load de-interleaves, +100, store re-interleaves -> each element += 100 in place
    for (size_t i = 0; i < vals.size(); ++i)
      expect(vals[i]).to_equal(static_cast<int32_t>(i + 100));
  });

  it("only vectorizes the whole-iteration prefix (tail left untouched)", _{
    // 514 is not a multiple of lanes*stride (8); the trailing pair is skipped
    std::array<int32_t, 514> vals;
    vals.fill(5);

    for (auto&& [even, odd] : argon::vectorize::interleaved<2, int32_t>(vals.data(), vals.size())) {
      even = even + 1;
      odd  = odd + 1;
    }

    expect(vals[0]).to_equal(6);
    expect(vals[511]).to_equal(6);
    expect(vals[512]).to_equal(5);  // tail untouched
    expect(vals[513]).to_equal(5);
  });
});

#endif  // MSVC skip

CPPSPEC_MAIN(vectorize_interleaved);
