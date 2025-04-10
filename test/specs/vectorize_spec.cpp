#include "argon.hpp"
#include "argon/vectorize/load_store.hpp"
#include "argon/vectorize/ptr.hpp"
#include "cppspec.hpp"

// clang-format off
auto vectorize = describe("vectorize", ${
  it("returns a vectorize::Iterator when begin() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize::load_store(vals);
    expect(std::is_same_v<decltype(vec.begin()), typename argon::vectorize::load_store<element_type>::Iterator>).to_be_true();
  });

  it("returns an end sentinel pointer when end() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize::load_store(vals);
    expect(std::is_same_v<decltype(vec.end()), element_type*>).to_be_true();
  });

  it("changes all values when base iterator's size is divisible by lanes", _{
    std::array<int32_t, 512> vals;
    vals.fill(5);

    for (auto& val : argon::vectorize::load_store(vals)){
      val = val + 1;
    }
    expect(vals).not_().to_contain(5);
  });

  it("does not changes all values when base iterator's size is not divisible by lanes", _{
    std::array<int32_t, 511> vals;
    vals.fill(5);

    for (auto& val : argon::vectorize::load_store(vals)){
      val = val + 1;
    }
    expect(vals[507]).to_equal(6);
    expect(vals[508]).to_equal(5);
    expect(vals[509]).to_equal(5);
    expect(vals[510]).to_equal(5);
  });

  it("vectorize_ptr can be zipped together", _{
    std::array<int32_t, 512> vals1;
    std::array<int32_t, 512> vals2;
    vals1.fill(5);
    vals2.fill(6);
    using vectorized = argon::vectorize::ptr<int32_t>;

    for (auto&& [val1, val2] : std::ranges::zip_view(vectorized(vals1), vectorized(vals2))){
      *val1 = val1->Add(*val2);
    }
    expect(vals1).not_().to_contain(5);
    expect(vals1).to_contain(11);
  });
});

CPPSPEC_MAIN(vectorize);
