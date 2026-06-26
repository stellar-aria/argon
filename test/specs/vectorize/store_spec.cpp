#include "argon.hpp"
#include "argon/vectorize/load.hpp"
#include "argon/vectorize/store.hpp"
#include "cppspec.hpp"

// clang-format off
auto vectorize_store = describe("vectorize_store", ${
  it("returns a vectorize_store::iterator when begin() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize::store(vals);
    expect(std::is_same_v<decltype(vec.begin()), typename argon::vectorize::store<element_type>::iterator>).to_be_true();
  });

  it("returns an end sentinel pointer when end() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize::store(vals);
    expect(std::is_same_v<decltype(vec.end()), element_type*>).to_be_true();
  });

  it("changes all values when base iterator's size is divisible by lanes", _{
    std::array<int32_t, 512> vals;
    vals.fill(5);

    int32_t counter = 0;
    for (auto& val : argon::vectorize::store(vals)){
      val = { counter, counter + 1, counter + 2, counter + 3 };
      counter += 4;
    }
    expect(counter).to_equal(512);

    for (size_t i = 0; i < vals.size(); ++i) {
      expect(vals[i]).to_equal(i);
    }
  });

  it("only writes the lanes-divisible prefix when size is not divisible by lanes", _{
    // 511 is not a multiple of 4 (int32 lanes); the last 3 elements stay 5
    std::array<int32_t, 511> vals;
    vals.fill(5);

    int32_t counter = 0;
    for (auto& val : argon::vectorize::store(vals)){
      val = { counter, counter + 1, counter + 2, counter + 3 };
      counter += 4;
    }
    expect(counter).to_equal(508);  // floor(511/4)*4

    for (size_t i = 0; i < 508; ++i)
      expect(vals[i]).to_equal(static_cast<int32_t>(i));
    expect(vals[508]).to_equal(5);  // tail untouched
    expect(vals[509]).to_equal(5);
    expect(vals[510]).to_equal(5);
  });
});

CPPSPEC_MAIN(vectorize_store);
