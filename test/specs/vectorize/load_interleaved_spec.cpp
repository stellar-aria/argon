
#include "argon.hpp"
#include "argon/vectorize/load_interleaved.hpp"
#include "cppspec.hpp"

// clang-format off
auto vectorize_load_interleaved = describe("vectorize_load_interleaved", ${
  it("returns a vectorize::load_interleaved::Iterator when begin() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize::load_interleaved(vals);
    expect(std::is_same_v<decltype(vec.begin()), std::ranges::iterator_t<argon::vectorize::load_interleaved<element_type, 2>>>).to_be_true();
  });

  it("returns an end sentinel pointer when end() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize::load_interleaved(vals);
    expect(std::is_same_v<decltype(vec.end()), std::ranges::sentinel_t<argon::vectorize::load_interleaved<element_type, 2>>>).to_be_true();
  });

  it("can access all elements of vals", _{
    std::array<int32_t, 512> vals;
    vals.fill(5);

    for (auto [val_a, val_b] : argon::vectorize::load_interleaved(vals)){
      for (size_t i = 0; i < decltype(val_a)::lanes; ++i) {
        expect(val_a[i]).to_equal(5);
        expect(val_b[i]).to_equal(5);
      }
    }
  });
});

CPPSPEC_MAIN(vectorize_load_interleaved);
