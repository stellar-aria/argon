#include "argon.hpp"
#include "argon/pointer_vector.hpp"
#include "cppspec.hpp"
#include <array>
#include <cstdint>

// clang-format off

// Semantics measured on QEMU's Cortex-M55: the write-back gather (vldrw ... [q]!) pre-increments.

auto describe_pointer_vector = describe("PointerVector", ${
  it("gathers one element from each pointer", _{
    std::array<int32_t, 40> buf{};
    for (size_t i = 0; i < buf.size(); ++i) buf[i] = static_cast<int32_t>(i);
    argon::PointerVector<const int32_t> p({&buf[0], &buf[10], &buf[20], &buf[30]});
    expect(p.Load().to_array()).to_equal(std::array<int32_t, 4>{0, 10, 20, 30});
    expect(p.Load<8>().to_array()).to_equal(std::array<int32_t, 4>{2, 12, 22, 32});
  });

  it("advances before loading, like the write-back gather", _{
    std::array<int32_t, 40> buf{};
    for (size_t i = 0; i < buf.size(); ++i) buf[i] = static_cast<int32_t>(i);
    argon::PointerVector<const int32_t> p({&buf[0], &buf[10], &buf[20], &buf[30]});
    expect(p.AdvanceAndLoad<4>().to_array()).to_equal(std::array<int32_t, 4>{1, 11, 21, 31});
    expect(p.AdvanceAndLoad<4>().to_array()).to_equal(std::array<int32_t, 4>{2, 12, 22, 32});
    expect(p.pointers()[0]).to_equal(&buf[2]);
    expect(p.pointers()[3]).to_equal(&buf[32]);
  });

  it("walks four channels in lockstep", _{
    // four 8-sample channels, summed sample by sample
    std::array<float, 32> channels{};
    for (size_t c = 0; c < 4; ++c)
      for (size_t s = 0; s < 8; ++s) channels[c * 8 + s] = static_cast<float>((c + 1) * (s + 1));
    argon::PointerVector<const float> p({&channels[0], &channels[8], &channels[16], &channels[24]});
    auto sum = p.Load();
    for (int s = 1; s < 8; ++s) sum = sum + p.AdvanceAndLoad<4>();
    expect(sum.to_array()).to_equal(std::array<float, 4>{36, 72, 108, 144});
  });

  it("scatters and advances", _{
    std::array<uint32_t, 16> out{};
    argon::PointerVector<uint32_t> p({&out[0], &out[4], &out[8], &out[12]});
    p.Store(Argon<uint32_t>{1u, 2u, 3u, 4u});
    p.AdvanceAndStore<8>(Argon<uint32_t>{5u, 6u, 7u, 8u});
    p.Store<-4>(Argon<uint32_t>{9u});
    expect(out).to_equal(std::array<uint32_t, 16>{1, 9, 5, 0, 2, 9, 6, 0, 3, 9, 7, 0, 4, 9, 8, 0});
    expect(p.pointers()[1]).to_equal(&out[6]);
  });

  it("handles 64-bit elements", _{
    std::array<int64_t, 8> buf = {10, 11, 12, 13, -20, -21, -22, -23};
    argon::PointerVector<int64_t> p({&buf[0], &buf[4]});
    expect(p.Load().to_array()).to_equal(std::array<int64_t, 2>{10, -20});
    expect(p.AdvanceAndLoad<16>().to_array()).to_equal(std::array<int64_t, 2>{12, -22});
    p.Store<8>(Argon<int64_t>{int64_t{1} << 40, -1});
    expect(buf[3]).to_equal(int64_t{1} << 40);
    expect(buf[7]).to_equal(int64_t{-1});
    p.AdvanceAndStore<-16>(Argon<int64_t>{7, 8});
    expect(buf[0]).to_equal(int64_t{7});
    expect(buf[4]).to_equal(int64_t{8});
  });
});

CPPSPEC_MAIN(describe_pointer_vector);
