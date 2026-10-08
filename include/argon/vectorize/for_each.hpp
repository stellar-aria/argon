#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <type_traits>
#include "argon/argon_full.hpp"
#include "argon/store.hpp"
#include "argon/vectorize/first_n.hpp"

/// @file for_each.hpp
/// @brief A loop over `n` elements a vector at a time, final partial vector included, shaped so that Helium
/// compilers turn it into a low-overhead tail-predicated loop.

namespace argon::vectorize {

/// @brief One step of vectorize::for_each: the elements [index(), index() + count()) of the range.
/// @tparam ScalarType The lane type the loop is written in.
/// @tparam full Whether every lane is in range. On NEON the loop body is instantiated with full steps for the
/// whole vectors (plain loads and stores) and once more with a partial step for the tail, whose accesses branch on
/// its scalar count rather than a predicate (see first_n.hpp); on MVE every step is predicated, which is what lets
/// the compiler drop the predication into the loop instructions (dlstp/letp).
template <typename ScalarType, bool full>
class Step {
 public:
  using argon_type = Argon<ScalarType>;                          ///< The vector type of the loop.
  using predicate_type = typename argon_type::argon_bool_type;  ///< The predicate type of active().
  static constexpr std::ptrdiff_t lanes = argon_type::lanes;    ///< Elements per step.

  [[gnu::always_inline]] Step(std::ptrdiff_t index, std::ptrdiff_t remaining) : index_{index}, remaining_{remaining} {}

  /// @brief The index of this step's first element.
  [[gnu::always_inline]] std::ptrdiff_t index() const { return index_; }

  /// @brief The number of this step's lanes inside the range.
  [[gnu::always_inline]] std::ptrdiff_t count() const {
    if constexpr (full) {
      return lanes;
    } else {
      return remaining_ < lanes ? remaining_ : lanes;
    }
  }

  /// @brief The lanes inside the range. Out-of-range lanes load as zero, so use this to keep them out of
  /// reductions such as a minimum.
  [[gnu::always_inline]] predicate_type active() const {
    if constexpr (full) {
      return predicate_type::True();
    } else {
      return predicate_type::FirstN(static_cast<size_t>(remaining_));
    }
  }

  /// @brief Load this step's elements of the array at `base`; out-of-range lanes are zero and not read.
  [[gnu::always_inline]] argon_type Load(const ScalarType* base) const {
    if constexpr (full) {
      return argon_type::Load(base + index_);
    } else {
#ifdef ARGON_PLATFORM_MVE
      return argon_type::Load(base + index_, active());
#else
      return detail::load_first_n(base + index_, static_cast<size_t>(remaining_));
#endif
    }
  }

  /// @brief Store `value` to this step's elements of the array at `base`; out-of-range lanes are not written.
  [[gnu::always_inline]] void Store(ScalarType* base, argon_type value) const {
    if constexpr (full) {
      value.StoreTo(base + index_);
    } else {
#ifdef ARGON_PLATFORM_MVE
      value.StoreTo(base + index_, active());
#else
      detail::store_first_n(base + index_, value, static_cast<size_t>(remaining_));
#endif
    }
  }

  /// @brief Load this step's elements of an array of the narrower integer type N, extending them to lanes.
  template <typename N>
    requires argon::widenable_from<N, ScalarType>
  [[gnu::always_inline]] argon_type LoadWiden(const N* base) const {
    if constexpr (full) {
      return argon_type::LoadWiden(base + index_);
    } else {
#ifdef ARGON_PLATFORM_MVE
      return argon_type::LoadWiden(base + index_, active());
#else
      return detail::load_first_n_widen<N, ScalarType>(base + index_, static_cast<size_t>(remaining_));
#endif
    }
  }

  /// @brief Store the low bits of `value` to this step's elements of an array of the narrower integer type N.
  template <typename N>
    requires argon::widenable_from<N, ScalarType>
  [[gnu::always_inline]] void StoreNarrow(N* base, argon_type value) const {
    if constexpr (full) {
      value.StoreNarrow(base + index_);
    } else {
#ifdef ARGON_PLATFORM_MVE
      value.StoreNarrow(base + index_, active());
#else
      detail::store_first_n_narrow<N, ScalarType>(base + index_, value, static_cast<size_t>(remaining_));
#endif
    }
  }

 private:
  std::ptrdiff_t index_;
  std::ptrdiff_t remaining_;
};

/// @brief Call `body` with a Step for each vector's worth of the elements [0, n), the final partial vector
/// included.
/// @tparam ScalarType The lane type of the loop.
/// @param n The number of elements.
/// @param body A callable taking a Step by value, generic in it (`[&](auto step) { ... }`): on NEON it is called
/// with full steps and then once with a partial one.
/// @details On Helium, GCC and clang compile this into a low-overhead tail-predicated loop (dlstp/letp), with no
/// scalar epilogue: the loop is a signed counter, a vctp of the remaining count, and predicated accesses, the shape
/// they recognise. (GCC does so for float loops only with -fno-trapping-math, since the inactive lanes compute too.)
/// On NEON the whole vectors use plain loads and stores, and the last step loads and stores only its in-range lanes,
/// branching on their count: active() is built only if the body asks for it.
///
/// @code
/// argon::vectorize::for_each<float>(n, [&](auto step) {
///   step.Store(out, step.Load(a) + (step.Load(b) - step.Load(a)) * t);
/// });
/// @endcode
template <typename ScalarType, typename Body>
[[gnu::always_inline]] inline void for_each(std::ptrdiff_t n, Body&& body) {
  constexpr std::ptrdiff_t lanes = Argon<ScalarType>::lanes;
#ifdef ARGON_PLATFORM_MVE
  for (std::ptrdiff_t i = 0; i < n; i += lanes) {
    body(Step<ScalarType, false>{i, n - i});
  }
#else
  std::ptrdiff_t i = 0;
  for (; i + lanes <= n; i += lanes) {
    body(Step<ScalarType, true>{i, lanes});
  }
  if (i < n) {
    body(Step<ScalarType, false>{i, n - i});
  }
#endif
}

/// @brief One step of vectorize::for_each_interleaved: the frames [index(), index() + count()), each of `Stride`
/// interleaved elements (a stereo pair, an RGB pixel), loaded as one vector per channel.
/// @tparam full Whether every lane (frame) is in range: full steps use the structured loads and stores (vld2-vld4,
/// vst2-vst4), which can't be predicated. On NEON partial ones use them on the frames inside the range, a doubleword
/// or one frame at a time, branching on the scalar count; on MVE they gather and scatter each channel under a
/// predicate.
template <typename ScalarType, size_t Stride, bool full>
class InterleavedStep {
 public:
  using argon_type = Argon<ScalarType>;                          ///< The vector type of one channel.
  using frame_type = std::array<argon_type, Stride>;             ///< One vector per channel.
  using predicate_type = typename argon_type::argon_bool_type;  ///< The predicate type of active().
  static constexpr std::ptrdiff_t lanes = argon_type::lanes;    ///< Frames per step.

  [[gnu::always_inline]] InterleavedStep(std::ptrdiff_t index, std::ptrdiff_t remaining)
      : index_{index}, remaining_{remaining} {}

  /// @brief The index of this step's first frame.
  [[gnu::always_inline]] std::ptrdiff_t index() const { return index_; }

  /// @brief The number of this step's frames inside the range.
  [[gnu::always_inline]] std::ptrdiff_t count() const {
    if constexpr (full) {
      return lanes;
    } else {
      return remaining_ < lanes ? remaining_ : lanes;
    }
  }

  /// @brief The lanes (frames) inside the range.
  [[gnu::always_inline]] predicate_type active() const {
    if constexpr (full) {
      return predicate_type::True();
    } else {
      return predicate_type::FirstN(static_cast<size_t>(remaining_));
    }
  }

  /// @brief Load this step's frames of the interleaved array at `base`, one vector per channel; lanes past the end
  /// of the range are zero and not read.
  [[gnu::always_inline]] frame_type Load(const ScalarType* base) const {
    const ScalarType* ptr = base + index_ * std::ptrdiff_t{Stride};
    if constexpr (full) {
      return argon_type::template LoadInterleaved<Stride>(ptr);
    } else {
#ifdef ARGON_PLATFORM_MVE
      const auto offsets = Offsets();
      const auto mask = active();
      frame_type out;
      for (size_t channel = 0; channel < Stride; ++channel) {
        out.data()[channel] = argon_type::LoadGatherOffsetIndex(ptr + channel, offsets, mask);
      }
      return out;
#else
      return detail::load_first_n_interleaved<Stride>(ptr, static_cast<size_t>(remaining_));
#endif
    }
  }

  /// @brief Store one vector per channel, interleaved, to this step's frames of the array at `base`; frames past the
  /// end of the range are not written.
  [[gnu::always_inline]] void Store(ScalarType* base, const frame_type& channels) const {
    ScalarType* ptr = base + index_ * std::ptrdiff_t{Stride};
    if constexpr (full) {
      argon::store_interleaved(ptr, channels);
    } else {
#ifdef ARGON_PLATFORM_MVE
      const auto offsets = Offsets();
      const auto mask = active();
      frame_type vectors = channels;  // the const data() isn't always-inline
      for (size_t channel = 0; channel < Stride; ++channel) {
        vectors.data()[channel].StoreScatterOffsetIndex(ptr + channel, offsets, mask);
      }
#else
      detail::store_first_n_interleaved<Stride>(ptr, channels, static_cast<size_t>(remaining_));
#endif
    }
  }

 private:
  /// Element offsets {0, Stride, 2*Stride, ...} of each frame's first element.
  [[gnu::always_inline]] static typename argon_type::offset_type Offsets() {
    using offset_type = typename argon_type::offset_type;
    return offset_type::Iota(0) * static_cast<typename offset_type::scalar_type>(Stride);
  }

  std::ptrdiff_t index_;
  std::ptrdiff_t remaining_;
};

/// @brief Call `body` with an InterleavedStep for each vector's worth of the `frames` frames of `Stride`
/// interleaved elements, the final partial group included.
/// @tparam ScalarType The element type. @tparam Stride 2, 3 or 4 elements per frame.
/// @param body A callable taking an InterleavedStep by value, generic in it (`[&](auto step) { ... }`).
/// @details Whole groups use vld2-vld4 / vst2-vst4 in a low-overhead loop. The structured loads can't be predicated,
/// so on NEON the last, partial group moves only its in-range frames with them, and on MVE it gathers and scatters
/// each channel under a predicate (a dls/le loop rather than dlstp/letp). On MVE, which has no vld3, stride 3 gathers
/// every group under a predicate instead, which can become a tail-predicated dlstp/letp loop. If every channel gets the
/// same treatment, `for_each` over the interleaved data as flat elements is simpler and faster.
///
/// @code
/// // swap the channels of interleaved stereo
/// argon::vectorize::for_each_interleaved<int16_t, 2>(frames, [&](auto step) {
///   auto [left, right] = step.Load(stereo);
///   step.Store(stereo, {right, left});
/// });
/// @endcode
template <typename ScalarType, size_t Stride, typename Body>
  requires(Stride >= 2 && Stride <= 4)
[[gnu::always_inline]] inline void for_each_interleaved(std::ptrdiff_t frames, Body&& body) {
  constexpr std::ptrdiff_t lanes = Argon<ScalarType>::lanes;
#ifdef ARGON_PLATFORM_MVE
  if constexpr (Stride == 3) {
    for (std::ptrdiff_t i = 0; i < frames; i += lanes) {
      body(InterleavedStep<ScalarType, Stride, false>{i, frames - i});
    }
    return;
  }
#endif
  std::ptrdiff_t i = 0;
  for (; i + lanes <= frames; i += lanes) {
    body(InterleavedStep<ScalarType, Stride, true>{i, lanes});
  }
  if (i < frames) {
    body(InterleavedStep<ScalarType, Stride, false>{i, frames - i});
  }
}

}  // namespace argon::vectorize
