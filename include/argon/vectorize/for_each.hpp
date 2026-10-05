#pragma once
#include <algorithm>
#include <cstddef>
#include <type_traits>
#include "argon/argon_full.hpp"

/// @file for_each.hpp
/// @brief A loop over `n` elements a vector at a time, final partial vector included, shaped so that Helium
/// compilers turn it into a low-overhead tail-predicated loop.

namespace argon::vectorize {

/// @brief One step of vectorize::for_each: the elements [index(), index() + count()) of the range.
/// @tparam ScalarType The lane type the loop is written in.
/// @tparam full Whether every lane is in range. On NEON the loop body is instantiated with full steps for the
/// whole vectors (plain loads and stores) and once more with a partial step for the tail; on MVE every step is
/// predicated, which is what lets the compiler drop the predication into the loop instructions (dlstp/letp).
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
      return std::min(remaining_, lanes);
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
      return argon_type::Load(base + index_, active());
    }
  }

  /// @brief Store `value` to this step's elements of the array at `base`; out-of-range lanes are not written.
  [[gnu::always_inline]] void Store(ScalarType* base, argon_type value) const {
    if constexpr (full) {
      value.StoreTo(base + index_);
    } else {
      value.StoreTo(base + index_, active());
    }
  }

  /// @brief Load this step's elements of an array of the narrower integer type N, extending them to lanes.
  template <typename N>
    requires argon::widenable_from<N, ScalarType>
  [[gnu::always_inline]] argon_type LoadWiden(const N* base) const {
    if constexpr (full) {
      return argon_type::LoadWiden(base + index_);
    } else {
      return argon_type::LoadWiden(base + index_, active());
    }
  }

  /// @brief Store the low bits of `value` to this step's elements of an array of the narrower integer type N.
  template <typename N>
    requires argon::widenable_from<N, ScalarType>
  [[gnu::always_inline]] void StoreNarrow(N* base, argon_type value) const {
    if constexpr (full) {
      value.StoreNarrow(base + index_);
    } else {
      value.StoreNarrow(base + index_, active());
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
/// On NEON the whole vectors use plain loads and stores and only the last step is predicated.
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

}  // namespace argon::vectorize
