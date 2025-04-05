#include "argon.hpp"
#include "argon/vectorize/store_interleaved.hpp"
#include "cppspec.hpp"

// clang-format off
auto vectorize_store_interleaved = describe("vectorize_store_interleaved", ${
  it("returns a vectorize_store_interleaved::iterator when begin() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize_store_interleaved(vals);
    expect(std::is_same_v<decltype(vec.begin()), typename argon::vectorize_store_interleaved<element_type>::iterator>).to_be_true();
  });

  it("returns an end sentinel pointer when end() is called", _{
    using element_type = int16_t;
    std::array<element_type, 8> vals;
    auto vec = argon::vectorize_store_interleaved(vals);
    expect(std::is_same_v<decltype(vec.end()), element_type*>).to_be_true();
  });

  it("changes all values when base iterator's size is divisible by lanes", _{
    std::array<int32_t, 512> vals;
    vals.fill(5);

    int32_t counter = 0;
    for (auto& [val_a, val_b] : argon::vectorize_store_interleaved(vals)){
      val_a = { counter + 0, counter + 2, counter + 4, counter + 6 };
      val_b = { counter + 1, counter + 3, counter + 5, counter + 7 };
      counter += 8;
    }
    expect(counter).to_equal(512);

    for (size_t i = 0; i < vals.size(); ++i) {
      expect(vals[i]).to_equal(i);
    }
  });
});

CPPSPEC_MAIN(vectorize_store_interleaved);
