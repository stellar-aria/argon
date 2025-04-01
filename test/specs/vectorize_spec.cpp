#include "argon/vectorize.hpp"
#include "cppspec.hpp"
#include "argon.hpp"

// clang-format off
auto vectorize = describe("vectorize", ${
  it("returns a vectorize::Iterator when begin() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize(vals);
    expect(std::is_same_v<decltype(vec.begin()), typename argon::vectorize<element_type>::Iterator>).to_be_true();
  });

  it("returns an end sentinel pointer when end() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize(vals);
    expect(std::is_same_v<decltype(vec.end()), element_type*>).to_be_true();
  });

  it("changes all values when base iterator's size is divisible by lanes", _{
    std::array<int32_t, 512> vals;
    vals.fill(5);

    for (auto& val : argon::vectorize(vals)){
      val = val + 1;
    }
    expect(vals).not_().to_contain(5);
  });

  it("does not changes all values when base iterator's size is not divisible by lanes", _{
    std::array<int32_t, 511> vals;
    vals.fill(5);

    for (auto& val : argon::vectorize(vals)){
      val = val + 1;
    }
    expect(vals[507]).to_equal(6);
    expect(vals[508]).to_equal(5);
    expect(vals[509]).to_equal(5);
    expect(vals[510]).to_equal(5);
  });
});

CPPSPEC_SPEC(vectorize);
