// Every tail_* function here must keep its final, partial vector off the NEON-to-core path on AArch32 (checked by
// check_neon_tail.sh): no vmov from a NEON lane or doubleword into a core register, which stalls Cortex-A9 and A7.
// The partial step knows its lane count as a scalar, so it branches on that, not on the lanes of a FirstN predicate.
// Results are written to memory rather than returned, since returning a reduction moves it to a core register.
#include <cstddef>
#include <cstdint>
#include <span>
#include "argon.hpp"
#include "argon/vectorize/for_each.hpp"
#include "argon/vectorize/interleaved.hpp"
#include "argon/vectorize/load.hpp"
#include "argon/vectorize/load_interleaved.hpp"
#include "argon/vectorize/load_store.hpp"
#include "argon/vectorize/store.hpp"
#include "argon/vectorize/store_interleaved.hpp"

extern "C" {

// ── vectorize::for_each ──

void tail_for_each_int32(int32_t* d, ptrdiff_t n) {
  argon::vectorize::for_each<int32_t>(n, [&](auto s) { s.Store(d, s.Load(d) * 3); });
}

void tail_for_each_float(float* out, const float* a, const float* b, ptrdiff_t n, float t) {
  argon::vectorize::for_each<float>(n, [&](auto s) { s.Store(out, s.Load(a) + (s.Load(b) - s.Load(a)) * t); });
}

void tail_for_each_int16(int16_t* d, ptrdiff_t n) {
  argon::vectorize::for_each<int16_t>(n, [&](auto s) { s.Store(d, s.Load(d) + Argon<int16_t>{int16_t{1}}); });
}

void tail_for_each_uint8(uint8_t* d, const uint8_t* a, ptrdiff_t n) {
  argon::vectorize::for_each<uint8_t>(n, [&](auto s) { s.Store(d, s.Load(d) + s.Load(a)); });
}

void tail_for_each_widen_int16(int16_t* out, const int16_t* in, ptrdiff_t n) {
  argon::vectorize::for_each<int32_t>(n, [&](auto s) { s.StoreNarrow(out, (s.LoadWiden(in) * 3) >> 2); });
}

// ── vectorize::for_each_interleaved ──

// A stereo mixer: sum one channel, ride the other's gain, in vectors throughout.
void tail_for_each_interleaved_stereo_int32(int32_t* out, const int32_t* a, const int32_t* b, ptrdiff_t frames) {
  argon::vectorize::for_each_interleaved<int32_t, 2>(frames, [&](auto s) {
    const auto [a_l, a_r] = s.Load(a);
    const auto [b_l, b_r] = s.Load(b);
    s.Store(out, {a_l + b_l, a_r.MultiplyRoundFixedQMax(b_r)});
  });
}

void tail_for_each_interleaved_stereo_int16(int16_t* stereo, ptrdiff_t frames) {
  argon::vectorize::for_each_interleaved<int16_t, 2>(frames, [&](auto s) {
    auto [left, right] = s.Load(stereo);
    s.Store(stereo, {right, left});
  });
}

void tail_for_each_interleaved_rgb_float(float* rgb, ptrdiff_t pixels) {
  argon::vectorize::for_each_interleaved<float, 3>(pixels, [&](auto s) {
    auto c = s.Load(rgb);
    c[0] = c[0] * 0.5f;
    s.Store(rgb, c);
  });
}

void tail_for_each_interleaved_quad_float(float* quad, ptrdiff_t frames) {
  argon::vectorize::for_each_interleaved<float, 4>(frames, [&](auto s) {
    auto c = s.Load(quad);
    s.Store(quad, {c[3], c[2], c[1], c[0]});
  });
}

void tail_for_each_interleaved_rgba_uint8(uint8_t* rgba, ptrdiff_t pixels) {
  argon::vectorize::for_each_interleaved<uint8_t, 4>(pixels, [&](auto s) {
    auto c = s.Load(rgba);
    c[3] = Argon<uint8_t>{uint8_t{255}};
    s.Store(rgba, c);
  });
}

// ── with_tail() views ──

void tail_load_store_int32(int32_t* data, size_t n) {
  for (auto& p : argon::vectorize::load_store(std::span{data, n}).with_tail())
    *p = *p * 3;
}

void tail_load_store_float(float* data, size_t n, float gain) {
  for (auto& p : argon::vectorize::load_store(std::span{data, n}).with_tail())
    *p = *p * gain;
}

void tail_load_sum_int32(Argon<int32_t>* sum, const int32_t* data, size_t n) {
  Argon<int32_t> acc{0};
  for (auto p : argon::vectorize::load(std::span{data, n}).with_tail())
    acc = acc + *p;
  *sum = acc;
}

void tail_store_fill_int16(int16_t* data, size_t n, int16_t value) {
  for (auto& p : argon::vectorize::store(std::span{data, n}).with_tail())
    p = Argon<int16_t>{value};
}

void tail_interleaved_stereo_int32(int32_t* stereo, size_t n) {
  for (auto& p : argon::vectorize::interleaved<2, int32_t>(stereo, n).with_tail()) {
    auto& [left, right] = *p;
    left = left + right;
  }
}

void tail_load_interleaved_sum_float(Argon<float>* sum, const float* rgba, size_t n) {
  Argon<float> acc{0.0f};
  for (auto p : argon::vectorize::load_interleaved<float, 4>(std::span{rgba, n}).with_tail())
    acc = acc + (*p)[1];
  *sum = acc;
}

void tail_store_interleaved_int32(int32_t* stereo, size_t n, int32_t l, int32_t r) {
  for (auto& p : argon::vectorize::store_interleaved<int32_t, 2>(std::span{stereo, n}).with_tail()) {
    p = {Argon<int32_t>{l}, Argon<int32_t>{r}};
  }
}

}  // extern "C"
