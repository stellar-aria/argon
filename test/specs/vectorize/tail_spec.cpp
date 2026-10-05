#include "argon.hpp"
#include "argon/vectorize/interleaved.hpp"
#include "argon/vectorize/load.hpp"
#include "argon/vectorize/load_interleaved.hpp"
#include "argon/vectorize/load_store.hpp"
#include "argon/vectorize/store.hpp"
#include "argon/vectorize/store_interleaved.hpp"
#include "cppspec.hpp"
#include <array>
#include <limits>
#include <numeric>
#include <span>
#include <vector>

// clang-format off

// ── load().with_tail() ─────────────────────────────────────────────────────

auto describe_load_tail = describe("load().with_tail()", ${
  it("visits a final partial vector whose out-of-range lanes are zero", _{
    std::array<int32_t, 10> data{};
    std::iota(data.begin(), data.end(), 1);
    size_t vectors = 0;
    std::array<int32_t, 4> last{};
    size_t last_count = 0;
    for (auto p : argon::vectorize::load(data).with_tail()) {
      ++vectors;
      last = (*p).to_array();
      last_count = p.count();
    }
    expect(vectors).to_equal(size_t{3});
    expect(last_count).to_equal(size_t{2});
    expect(last).to_equal(std::array<int32_t, 4>{9, 10, 0, 0});
  });

  it("sums every element, where the plain view drops the remainder", _{
    std::array<int32_t, 10> data{};
    std::iota(data.begin(), data.end(), 1);
    int32_t with_tail = 0, without = 0;
    for (auto p : argon::vectorize::load(data).with_tail()) with_tail += p->ReduceAdd(p.active());
    for (auto v : argon::vectorize::load(data)) without += v.ReduceAdd();
    expect(with_tail).to_equal(55);
    expect(without).to_equal(36);
  });

  it("keeps the zeroed lanes out of a minimum via active()", _{
    std::array<int32_t, 6> data = {9, 8, 7, 6, 5, 4};
    auto big = Argon<int32_t>{std::numeric_limits<int32_t>::max()};
    auto acc = big;
    for (auto p : argon::vectorize::load(data).with_tail()) acc = acc.Min(p.active().Select(*p, big));
    expect(acc.ReduceMin()).to_equal(4);
  });

  it("has no partial vector when the size is a multiple of the lane count", _{
    std::array<uint8_t, 32> data{};
    size_t vectors = 0;
    bool all_full = true;
    for (auto p : argon::vectorize::load(data).with_tail()) {
      ++vectors;
      all_full = all_full && p.full();
    }
    expect(vectors).to_equal(size_t{2});
    expect(all_full).to_be_true();
  });

  it("visits nothing for an empty range", _{
    std::span<const float> empty{};
    size_t vectors = 0;
    for (auto p : argon::vectorize::load(empty).with_tail()) { (void)p; ++vectors; }
    expect(vectors).to_equal(size_t{0});
  });

  it("reports the vector count, partial included", _{
    std::array<uint8_t, 37> data{};
    expect(argon::vectorize::load(data).with_tail().size()).to_equal(size_t{3});
  });
});

// ── store().with_tail() ────────────────────────────────────────────────────

auto describe_store_tail = describe("store().with_tail()", ${
  it("writes every element and nothing past the range", _{
    std::array<int32_t, 12> out{};
    out.fill(-1);
    int32_t next = 1;
    for (auto& p : argon::vectorize::store(std::span{out}.first(10)).with_tail()) {
      p = Argon<int32_t>::Iota(next);
      next += 4;
    }
    expect(out).to_equal(std::array<int32_t, 12>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -1});
  });

  it("writes a uint8 tail", _{
    std::array<uint8_t, 40> out{};
    out.fill(0xEE);
    for (auto& p : argon::vectorize::store(std::span{out}.first(37)).with_tail()) p = Argon<uint8_t>{7};
    std::array<uint8_t, 40> expected{};
    expected.fill(7);
    expected[37] = expected[38] = expected[39] = 0xEE;
    expect(out).to_equal(expected);
  });
});

// ── load_store().with_tail() ───────────────────────────────────────────────

auto describe_load_store_tail = describe("load_store().with_tail()", ${
  it("updates every element in place and nothing past the range", _{
    std::array<float, 8> data = {1, 2, 3, 4, 5, 6, 7, 8};
    for (auto& p : argon::vectorize::load_store(std::span{data}.first(7)).with_tail()) *p = *p * 2.0f;
    expect(data).to_equal(std::array<float, 8>{2, 4, 6, 8, 10, 12, 14, 8});
  });

  it("leaves vectors it only reads untouched", _{
    std::array<int16_t, 20> data{};
    std::iota(data.begin(), data.end(), int16_t{0});
    auto expected = data;
    int32_t sum = 0;
    for (const auto& p : argon::vectorize::load_store(data).with_tail()) sum += p->ReduceAdd(p.active());
    expect(sum).to_equal(190);
    expect(data).to_equal(expected);
  });
});

// ── Iterator fixes ─────────────────────────────────────────────────────────

auto describe_iterators = describe("vectorize iterators", ${
  it("measure load iterator distance in vectors", _{
    std::array<int32_t, 16> data{};
    auto view = argon::vectorize::load(data);
    auto a = view.begin();
    auto b = a + 3;
    expect(b - a).to_equal(std::ptrdiff_t{3});
    expect((a[2]).to_array()).to_equal((*(a + 2)).to_array());
  });

  it("let load_store write back after a read-only vector", _{
    std::array<int32_t, 8> data = {1, 2, 3, 4, 5, 6, 7, 8};
    auto view = argon::vectorize::load_store(data);
    auto cursor = view.begin();
    ++cursor;            // first vector untouched
    *cursor = *cursor + 10;  // second vector modified
    ++cursor;
    expect(data).to_equal(std::array<int32_t, 8>{1, 2, 3, 4, 15, 16, 17, 18});
  });
});

// ── Interleaved views ──────────────────────────────────────────────────────

auto describe_interleaved_tail = describe("interleaved views with_tail()", ${
  it("load_interleaved().with_tail() de-interleaves a partial final group", _{
    // 5 stereo frames of int32: one whole group of 4 frames, then 1 frame
    std::array<int32_t, 10> data = {1, -1, 2, -2, 3, -3, 4, -4, 5, -5};
    std::vector<std::array<int32_t, 4>> left, right;
    std::vector<size_t> counts;
    for (auto p : argon::vectorize::load_interleaved<int32_t, 2>(data).with_tail()) {
      left.push_back((*p)[0].to_array());
      right.push_back((*p)[1].to_array());
      counts.push_back(p.count());
    }
    expect(counts).to_equal(std::vector<size_t>{4, 1});
    expect(left[1]).to_equal(std::array<int32_t, 4>{5, 0, 0, 0});
    expect(right[1]).to_equal(std::array<int32_t, 4>{-5, 0, 0, 0});
  });

  it("store_interleaved().with_tail() writes a partial final group and nothing after it", _{
    std::array<int16_t, 24> out{};
    out.fill(99);
    // 11 frames of stride 2 (22 elements) in a 24-element buffer
    for (auto& p : argon::vectorize::store_interleaved<int16_t, 2>(std::span{out}.first(22)).with_tail()) {
      p = {Argon<int16_t>{1}, Argon<int16_t>{2}};
    }
    std::array<int16_t, 24> expected{};
    for (size_t i = 0; i < 22; ++i) expected[i] = static_cast<int16_t>(i % 2 ? 2 : 1);
    expected[22] = expected[23] = 99;
    expect(out).to_equal(expected);
  });

  it("interleaved<3>().with_tail() updates RGB frames in place, including a partial group", _{
    // 6 RGB frames of float: one group of 4 frames, then 2
    std::array<float, 19> rgb{};
    for (size_t i = 0; i < 18; ++i) rgb[i] = static_cast<float>(i);
    rgb[18] = -1.0f;  // past the range
    for (auto& p : argon::vectorize::interleaved<3, float>(rgb.data(), 18).with_tail()) {
      (*p)[1] = (*p)[1] * 10.0f;  // scale green
    }
    for (size_t frame = 0; frame < 6; ++frame) {
      expect(rgb[frame * 3 + 0]).to_equal(static_cast<float>(frame * 3 + 0));
      expect(rgb[frame * 3 + 1]).to_equal(static_cast<float>(frame * 3 + 1) * 10.0f);
      expect(rgb[frame * 3 + 2]).to_equal(static_cast<float>(frame * 3 + 2));
    }
    expect(rgb[18]).to_equal(-1.0f);
  });

  it("whole groups only: plain views stop at the last whole group of lanes * stride", _{
    // 12 int32 at stride 2 is one whole group of 8; the old rounding (to a multiple of 4) never reached end()
    std::array<int32_t, 12> data{};
    std::iota(data.begin(), data.end(), 0);
    size_t groups = 0;
    for (auto group : argon::vectorize::load_interleaved<int32_t, 2>(data)) { (void)group; ++groups; }
    expect(groups).to_equal(size_t{1});
    std::array<int32_t, 12> out{};
    size_t stores = 0;
    for (auto& group : argon::vectorize::store_interleaved<int32_t, 2>(out)) {
      group = {Argon<int32_t>{7}, Argon<int32_t>{8}};
      ++stores;
    }
    expect(stores).to_equal(size_t{1});
    expect(out[7]).to_equal(8);
    expect(out[8]).to_equal(0);
  });

  it("stores stride-3 groups (scattered on MVE, which has no vst3)", _{
    std::array<uint8_t, 48> out{};
    argon::store_interleaved(out.data(), std::array<Argon<uint8_t>, 3>{Argon<uint8_t>{1}, Argon<uint8_t>{2}, Argon<uint8_t>{3}});
    std::array<uint8_t, 48> expected{};
    for (size_t i = 0; i < 48; ++i) expected[i] = static_cast<uint8_t>(i % 3 + 1);
    expect(out).to_equal(expected);
  });
});

CPPSPEC_MAIN(
  describe_load_tail,
  describe_store_tail,
  describe_load_store_tail,
  describe_iterators,
  describe_interleaved_tail
);
