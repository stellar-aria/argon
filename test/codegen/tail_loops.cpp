// Every tail_* function here must compile to a low-overhead tail-predicated loop (dlstp/letp) on Helium, with no
// scalar epilogue (checked by check_mve_tail.sh, with GCC). vectorize::for_each is written to get one for every lane
// type; the with_tail() views and hand-written FirstN loops get one in the cases checked here.
// Built with -fno-trapping-math: GCC tail-predicates float loops only when inactive lanes may compute freely.
#include <cstddef>
#include <cstdint>
#include <span>
#include "argon.hpp"
#include "argon/vectorize/for_each.hpp"
#include "argon/vectorize/load.hpp"
#include "argon/vectorize/load_store.hpp"
#include "argon/vectorize/store.hpp"

extern "C" {

void tail_scale_int32(int32_t* data, size_t n) {
  for (auto& p : argon::vectorize::load_store(std::span{data, n}).with_tail()) *p = *p * 3;
}

void tail_gain_float(float* data, size_t n, float gain) {
  for (auto& p : argon::vectorize::load_store(std::span{data, n}).with_tail()) *p = *p * gain;
}

void tail_offset_int16(int16_t* data, size_t n) {
  for (auto& p : argon::vectorize::load_store(std::span{data, n}).with_tail()) *p = *p + Argon<int16_t>{int16_t{1}};
}

int32_t tail_sum_int32(const int32_t* data, size_t n) {
  int32_t sum = 0;
  for (auto p : argon::vectorize::load(std::span{data, n}).with_tail()) sum += p->ReduceAdd(p.active());
  return sum;
}

// Not checked: GCC 16 doesn't tail-predicate loops over 8-bit lanes with an unsigned (size_t) count, even written with
// the raw intrinsics. It is still a vctp-predicated low-overhead (dls/le) loop.
void predicated_fill_uint8(uint8_t* data, size_t n, uint8_t value) {
  for (auto& p : argon::vectorize::store(std::span{data, n}).with_tail()) p = Argon<uint8_t>{value};
}

void tail_add_first_n(int32_t* out, const int32_t* a, const int32_t* b, size_t n) {
  using P = Argon<int32_t>::argon_bool_type;
  for (size_t i = 0; i < n; i += Argon<int32_t>::lanes) {
    const auto active = P::FirstN(n - i);
    (Argon<int32_t>::Load(a + i, active) + Argon<int32_t>::Load(b + i, active)).StoreTo(out + i, active);
  }
}

// ── vectorize::for_each, every lane type ──

void tail_for_each_uint8(uint8_t* d, const uint8_t* a, ptrdiff_t n) {
  argon::vectorize::for_each<uint8_t>(n, [&](auto s) { s.Store(d, s.Load(d) + s.Load(a)); });
}

void tail_for_each_fill_uint8(uint8_t* d, ptrdiff_t n, uint8_t value) {
  argon::vectorize::for_each<uint8_t>(n, [&](auto s) { s.Store(d, Argon<uint8_t>{value}); });
}

void tail_for_each_int16(int16_t* d, ptrdiff_t n) {
  argon::vectorize::for_each<int16_t>(n, [&](auto s) { s.Store(d, s.Load(d) + Argon<int16_t>{int16_t{1}}); });
}

void tail_for_each_int32(int32_t* d, ptrdiff_t n) {
  argon::vectorize::for_each<int32_t>(n, [&](auto s) { s.Store(d, s.Load(d) * 3); });
}

void tail_for_each_float(float* out, const float* a, const float* b, ptrdiff_t n, float t) {
  argon::vectorize::for_each<float>(n, [&](auto s) { s.Store(out, s.Load(a) + (s.Load(b) - s.Load(a)) * t); });
}

int32_t tail_for_each_sum(const int32_t* d, ptrdiff_t n) {
  int32_t sum = 0;
  argon::vectorize::for_each<int32_t>(n, [&](auto s) { sum += s.Load(d).ReduceAdd(s.active()); });
  return sum;
}

void tail_for_each_widen_int16(int16_t* out, const int16_t* in, ptrdiff_t n) {
  argon::vectorize::for_each<int32_t>(n, [&](auto s) { s.StoreNarrow(out, (s.LoadWiden(in) * 3) >> 2); });
}

}  // extern "C"
