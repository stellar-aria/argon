
#include "argon/vectorize/load.hpp"
#include "cppspec.hpp"
#include "argon.hpp"

// clang-format off
auto vectorize_load = describe("vectorize_load", ${
  it("returns a vectorize_load::Iterator when begin() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize_load(vals);
    expect(std::is_same_v<decltype(vec.begin()), typename argon::vectorize_load<element_type>::iterator>).to_be_true();
  });

  it("returns an end sentinel pointer when end() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize_load(vals);
    expect(std::is_same_v<decltype(vec.end()), element_type*>).to_be_true();
  });

  it("can access all elements of vals", _{
    std::array<int32_t, 512> vals;
    vals.fill(5);

    for (auto val : argon::vectorize_load(vals)){
      for (size_t i = 0; i < decltype(val)::lanes; ++i) {
        expect(val[i]).to_equal(5);
      }
    }
  });
});

CPPSPEC_MAIN(vectorize_load);
