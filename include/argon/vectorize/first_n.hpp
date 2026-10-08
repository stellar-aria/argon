#pragma once
#include <array>
#include <cstddef>
#include <type_traits>
#include "argon/argon_full.hpp"
#include "argon/argon_half.hpp"
#include "argon/features.h"
#include "argon/store.hpp"

/// @file first_n.hpp
/// @brief NEON loads and stores of a loop's final, partial vector, branching on its scalar lane count.
/// @details A partial vector knows how many of its lanes are in range as a scalar. Building a predicate from that
/// count (FirstN) and branching on each of its lanes reads every lane of the mask back into a core register, and on
/// NEON those transfers (vmov.32 r, d[k]) stall the pipeline. These helpers compare the scalar count instead:
/// - when the count covers the low doubleword, it moves as one whole vld1-vld4 / vst1-vst4 of doublewords;
/// - the other in-range lanes (frames, for interleaved data) move one at a time with single-lane loads and stores,
///   each guarded by the next compare of the count, so the first lane out of range ends the walk.
///
/// Every helper takes `0 < count < lanes`: a full vector uses the whole-vector accesses. The lane walks recurse
/// through always-inline templates rather than a lambda, which the compiler may outline once there are many lanes.
/// MVE needs none of this, since its predicate is native and tail-predicated loops are built from vctp, so these are
/// not defined there.

#ifndef ARGON_PLATFORM_MVE
namespace argon::vectorize::detail {

/// @brief `ptr`, as an address the compiler can't relate to its neighbours.
/// @details clang lowers vst1_lane to a plain store of the extracted element, and in ARM (not Thumb) mode it may fold
/// that store's address into a pre-indexed core store (strh r, [r0, r1]!), which has no NEON form and so is fed by a
/// vmov from the lane. An empty asm that claims to change the address keeps each lane store a vst1 to one lane; it
/// emits no instruction.
template <typename ScalarType>
[[gnu::always_inline]] inline ScalarType* opaque_address(ScalarType* ptr) {
#if defined(__arm__) && !defined(__aarch64__) && defined(__GNUC__)
  asm("" : "+r"(ptr));
#endif
  return ptr;
}

/// @brief Load lanes [Lane, half - 1) of the doubleword `v` from `ptr + lane`, while `first + lane < count`.
/// @details The doubleword's last lane is never loaded here: it is in range only when the whole doubleword is,
/// which the callers then load at once.
template <size_t Lane, typename ScalarType>
[[gnu::always_inline]] inline ArgonHalf<ScalarType> load_lanes(ArgonHalf<ScalarType> v,
                                                               const ScalarType* ptr,
                                                               size_t first,
                                                               size_t count) {
  if constexpr (Lane + 1 < ArgonHalf<ScalarType>::lanes) {
    if (first + Lane < count) {
      return load_lanes<Lane + 1>(v.template LoadToLane<Lane>(ptr + Lane), ptr, first, count);
    }
  }
  return v;
}

/// @brief Store lanes [Lane, half - 1) of the doubleword `v` to `ptr + lane`, while `first + lane < count` (see
/// load_lanes()).
template <size_t Lane, typename ScalarType>
[[gnu::always_inline]] inline void store_lanes(ArgonHalf<ScalarType> v, ScalarType* ptr, size_t first, size_t count) {
  if constexpr (Lane + 1 < ArgonHalf<ScalarType>::lanes) {
    if (first + Lane < count) {
      v.template StoreLaneTo<Lane>(opaque_address(ptr + Lane));
      store_lanes<Lane + 1>(v, ptr, first, count);
    }
  }
}

/// Load the first `count` lanes at `ptr` (0 < count < lanes); the rest are zero and not read.
template <typename ScalarType>
[[gnu::always_inline]] inline Argon<ScalarType> load_first_n(const ScalarType* ptr, size_t count) {
  using half_type = ArgonHalf<ScalarType>;
  constexpr size_t half = half_type::lanes;
  const half_type zero{ScalarType{0}};
  if (count >= half) {
    return {half_type::Load(ptr), load_lanes<0>(zero, ptr + half, half, count)};
  }
  return {load_lanes<0>(zero, ptr, 0, count), zero};
}

/// Store the first `count` lanes of `value` to `ptr` (0 < count < lanes); the rest are not written.
template <typename ScalarType>
[[gnu::always_inline]] inline void store_first_n(ScalarType* ptr, Argon<ScalarType> value, size_t count) {
  constexpr size_t half = ArgonHalf<ScalarType>::lanes;
  if (count >= half) {
    value.GetLow().StoreTo(ptr);
    store_lanes<0>(value.GetHigh(), ptr + half, half, count);
  } else {
    store_lanes<0>(value.GetLow(), ptr, 0, count);
  }
}

/// The channels of interleaved data as doublewords, the operand of the structured loads and stores.
template <size_t Stride, typename ScalarType>
using half_multi_type = neon::MultiVector_t<typename ArgonHalf<ScalarType>::vector_type, Stride>;

/// @brief Load frames [Lane, half - 1) of `multi` from `ptr + lane * Stride`, one vld2-vld4 to a lane each, while
/// `first + lane < count` (see load_lanes()).
template <size_t Lane, size_t Stride, typename ScalarType>
[[gnu::always_inline]] inline half_multi_type<Stride, ScalarType> load_frames(half_multi_type<Stride, ScalarType> multi,
                                                                              const ScalarType* ptr,
                                                                              size_t first,
                                                                              size_t count) {
  using half_type = ArgonHalf<ScalarType>;
  if constexpr (Lane + 1 < half_type::lanes) {
    if (first + Lane < count) {
      const auto loaded = half_type::template LoadToLaneInterleaved<Lane, Stride>(multi, ptr + Lane * Stride);
      for (size_t channel = 0; channel < Stride; ++channel)
        multi.val[channel] = loaded[channel].vec();
      return load_frames<Lane + 1, Stride>(multi, ptr, first, count);
    }
  }
  return multi;
}

/// @brief Store frames [Lane, half - 1) of `multi` to `ptr + lane * Stride`, one vst2-vst4 from a lane each, while
/// `first + lane < count` (see load_lanes()).
template <size_t Lane, size_t Stride, typename ScalarType>
[[gnu::always_inline]] inline void store_frames(half_multi_type<Stride, ScalarType> multi,
                                                ScalarType* ptr,
                                                size_t first,
                                                size_t count) {
  using half_type = ArgonHalf<ScalarType>;
  if constexpr (Lane + 1 < half_type::lanes) {
    if (first + Lane < count) {
      argon::store_lane_interleaved<Lane, Stride, ScalarType, typename half_type::vector_type>(ptr + Lane * Stride,
                                                                                               multi);
      store_frames<Lane + 1, Stride>(multi, ptr, first, count);
    }
  }
}

/// Load the first `count` frames (0 < count < lanes) of `Stride` interleaved elements at `ptr`, one vector per
/// channel; lanes past `count` are zero and not read.
template <size_t Stride, typename ScalarType>
[[gnu::always_inline]] inline std::array<Argon<ScalarType>, Stride> load_first_n_interleaved(const ScalarType* ptr,
                                                                                             size_t count) {
  using half_type = ArgonHalf<ScalarType>;
  constexpr size_t half = half_type::lanes;
  half_multi_type<Stride, ScalarType> zero;
  for (size_t channel = 0; channel < Stride; ++channel)
    zero.val[channel] = half_type{ScalarType{0}}.vec();
  half_multi_type<Stride, ScalarType> low = zero;
  half_multi_type<Stride, ScalarType> high = zero;
  if (count >= half) {
    const auto whole = half_type::template LoadInterleaved<Stride>(ptr);
    for (size_t channel = 0; channel < Stride; ++channel)
      low.val[channel] = whole[channel].vec();
    high = load_frames<0, Stride>(zero, ptr + half * Stride, half, count);
  } else {
    low = load_frames<0, Stride>(zero, ptr, 0, count);
  }
  std::array<Argon<ScalarType>, Stride> out;
  for (size_t channel = 0; channel < Stride; ++channel) {
    out[channel] = Argon<ScalarType>{half_type{low.val[channel]}, half_type{high.val[channel]}};
  }
  return out;
}

/// Store the first `count` frames (0 < count < lanes) of `value`, one vector per channel, interleaved to `ptr`;
/// frames past `count` are not written.
template <size_t Stride, typename ScalarType>
[[gnu::always_inline]] inline void store_first_n_interleaved(ScalarType* ptr,
                                                             const std::array<Argon<ScalarType>, Stride>& value,
                                                             size_t count) {
  using half_type = ArgonHalf<ScalarType>;
  constexpr size_t half = half_type::lanes;
  half_multi_type<Stride, ScalarType> low;
  half_multi_type<Stride, ScalarType> high;
  for (size_t channel = 0; channel < Stride; ++channel) {
    low.val[channel] = value[channel].GetLow().vec();
    high.val[channel] = value[channel].GetHigh().vec();
  }
  if (count >= half) {
    argon::store_interleaved<Stride, ScalarType, typename half_type::vector_type>(ptr, low);
    store_frames<0, Stride>(high, ptr + half * Stride, half, count);
  } else {
    store_frames<0, Stride>(low, ptr, 0, count);
  }
}

/// Load the first `count` (0 < count < lanes) elements of the narrower integer type N at `ptr`, extending each to a
/// lane of S; lanes past `count` are zero and not read.
template <typename N, typename S>
[[gnu::always_inline]] inline Argon<S> load_first_n_widen(const N* ptr, size_t count) {
  constexpr size_t lanes = Argon<S>::lanes;
  if constexpr (sizeof(S) == 2 * sizeof(N)) {
    // the narrow lanes fill a doubleword: load them there one by one, then widen with vmovl as a whole load would
    const auto narrow = load_lanes<0>(ArgonHalf<N>{N{0}}, ptr, 0, count);
    const auto wide = neon::move_long(narrow.vec());
    return Argon<std::conditional_t<std::is_signed_v<N>, std::make_signed_t<S>, std::make_unsigned_t<S>>>{wide}
        .template As<S>();
  } else {
    std::array<S, lanes> out{};
    for (size_t i = 0; i < lanes; ++i) {
      if (i < count)
        out[i] = static_cast<S>(ptr[i]);
    }
    return Argon<S>::Load(out.data());
  }
}

/// Store the low bits of the first `count` (0 < count < lanes) lanes of `value` as the narrower integer type N;
/// memory past `count` is not written.
template <typename N, typename S>
[[gnu::always_inline]] inline void store_first_n_narrow(N* ptr, Argon<S> value, size_t count) {
  constexpr size_t lanes = Argon<S>::lanes;
  if constexpr (sizeof(S) == 2 * sizeof(N)) {
    // narrow with vmovn as a whole store would, then store the doubleword's lanes one by one
    using SameSign = std::conditional_t<std::is_signed_v<N>, std::make_signed_t<S>, std::make_unsigned_t<S>>;
    store_lanes<0>(ArgonHalf<N>{neon::move_narrow(value.template As<SameSign>().vec())}, ptr, 0, count);
  } else {
    const auto values = value.to_array();
    for (size_t i = 0; i < lanes; ++i) {
      if (i < count)
        ptr[i] = static_cast<N>(values[i]);
    }
  }
}

}  // namespace argon::vectorize::detail
#endif
