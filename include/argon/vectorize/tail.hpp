#pragma once
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <ranges>
#include "argon/argon_full.hpp"

/// @file tail.hpp
/// @brief Vectorized views that also visit the final, partial vector of a range (see `with_tail()` on the views).

namespace argon::vectorize {

/// @brief One vector of a range, and how many of its leading lanes lie inside the range.
/// @tparam ScalarType The element type of the range.
/// @details Every vector of a `with_tail()` view is full except possibly the last. Lanes past the end of the range
/// are zero when loaded and are never written when stored; use active() to keep them out of reductions such as
/// minimum or maximum, where a zero would matter.
template <typename ScalarType>
class Partial {
 public:
  using vector_type = Argon<ScalarType>;                          ///< The vector type.
  using predicate_type = typename vector_type::argon_bool_type;  ///< The predicate type for active().
  static constexpr size_t lanes = vector_type::lanes;            ///< The number of lanes in the vector.

  Partial() = default;

  /// @brief A vector whose first `remaining` lanes are in the range (`lanes` or more means all of them).
  Partial(vector_type value, size_t remaining) : value_{value}, remaining_{remaining} {}

  /// @brief The vector. Lanes past the end of the range are zero after a load.
  vector_type& operator*() { return value_; }
  /// @copydoc operator*()
  const vector_type& operator*() const { return value_; }
  /// @brief Member access on the vector.
  vector_type* operator->() { return &value_; }
  /// @copydoc operator->()
  const vector_type* operator->() const { return &value_; }

  /// @brief Replace the vector; only the lanes inside the range are stored.
  Partial& operator=(vector_type value) {
    value_ = value;
    return *this;
  }

  /// @brief The number of leading lanes inside the range.
  size_t count() const { return std::min(remaining_, lanes); }
  /// @brief Whether every lane is inside the range.
  bool full() const { return remaining_ >= lanes; }
  /// @brief The lanes inside the range, as a predicate.
  predicate_type active() const { return predicate_type::FirstN(remaining_); }

  /// @brief The elements left in the range from this vector on; FirstN of it is active().
  size_t remaining() const { return remaining_; }

 private:
  vector_type value_{ScalarType{0}};
  size_t remaining_ = 0;  // unclamped: FirstN (vctp on MVE) saturates, and a clamp here keeps the loop from tail
                          // predicating
};

namespace detail {
/// Load the first `count` elements at `ptr` (all lanes when count >= lanes); the rest are zero and not read.
template <typename ScalarType>
Argon<ScalarType> load_partial(const ScalarType* ptr, size_t count) {
  using vector_type = Argon<ScalarType>;
#ifdef ARGON_PLATFORM_MVE
  // Always predicate: a vctp-predicated loop is what the compiler turns into dlstp/letp.
  return vector_type::Load(ptr, vector_type::argon_bool_type::FirstN(count));
#else
  return count >= vector_type::lanes ? vector_type::Load(ptr)
                                     : vector_type::Load(ptr, vector_type::argon_bool_type::FirstN(count));
#endif
}

/// Store the first `count` lanes of `value` to `ptr` (all lanes when count >= lanes).
template <typename ScalarType>
void store_partial(ScalarType* ptr, Argon<ScalarType> value, size_t count) {
  using vector_type = Argon<ScalarType>;
#ifdef ARGON_PLATFORM_MVE
  value.StoreTo(ptr, vector_type::argon_bool_type::FirstN(count));
#else
  if (count >= vector_type::lanes) {
    value.StoreTo(ptr);
  } else {
    value.StoreTo(ptr, vector_type::argon_bool_type::FirstN(count));
  }
#endif
}

/// Shared position-keeping for the tail iterators: positions are element indices, so the iterator never forms a
/// pointer past the end of the range.
template <typename PointerType>
struct TailCursor {
  static constexpr size_t lanes = Argon<std::remove_const_t<PointerType>>::lanes;

  PointerType* base = nullptr;
  size_t index = 0;
  size_t count = 0;

  PointerType* ptr() const { return base + index; }
  /// Elements left from the current position (not clamped to the lane count; FirstN saturates).
  size_t remaining() const { return count - index; }
  bool done() const { return index >= count; }
};
}  // namespace detail

/// @brief Read-only view of a range as vectors, including a final partial vector. See load::with_tail().
template <typename ScalarType>
class load_tail : public std::ranges::view_interface<load_tail<ScalarType>> {
  static constexpr size_t lanes = Argon<ScalarType>::lanes;

 public:
  /// @brief Iterator over the vectors of the range; dereferences to a Partial.
  struct Iterator {
    using value_type = Partial<ScalarType>;  ///< The value type of the iterator.
    using difference_type = std::ptrdiff_t;  ///< The difference type of the iterator.

    Iterator() = default;
    Iterator(detail::TailCursor<const ScalarType> cursor) : cursor_{cursor} {}

    /// @brief Load the current vector; lanes past the end of the range are zero and not read.
    value_type operator*() const {
      const size_t n = cursor_.remaining();
      return {detail::load_partial(cursor_.ptr(), n), n};
    }

    Iterator& operator++() {
      cursor_.index += lanes;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++*this;
      return tmp;
    }

    friend bool operator==(const Iterator& a, const Iterator& b) { return a.cursor_.index == b.cursor_.index; }
    friend bool operator==(const Iterator& it, std::default_sentinel_t) { return it.cursor_.done(); }

   private:
    detail::TailCursor<const ScalarType> cursor_;
  };
  static_assert(std::forward_iterator<Iterator>);

  load_tail() = default;
  /// @brief View `count` elements starting at `start`.
  load_tail(const ScalarType* start, size_t count) : start_{start}, count_{count} {}

  Iterator begin() const { return Iterator{{start_, 0, count_}}; }
  std::default_sentinel_t end() const { return {}; }
  /// @brief The number of vectors, counting a final partial one.
  size_t size() const { return (count_ + lanes - 1) / lanes; }

 private:
  const ScalarType* start_ = nullptr;
  size_t count_ = 0;
};

/// @brief Write-only view of a range as vectors, including a final partial vector. See store::with_tail().
/// @details Each vector is stored when the iterator advances; only the lanes inside the range are written.
template <typename ScalarType>
class store_tail : public std::ranges::view_interface<store_tail<ScalarType>> {
  static constexpr size_t lanes = Argon<ScalarType>::lanes;

 public:
  /// @brief Iterator over the vectors of the range; dereferences to a Partial to assign.
  struct Iterator {
    using value_type = Partial<ScalarType>;  ///< The value type of the iterator.
    using difference_type = std::ptrdiff_t;  ///< The difference type of the iterator.

    Iterator() = default;
    Iterator(detail::TailCursor<ScalarType> cursor)
        : cursor_{cursor}, current_{Argon<ScalarType>{}, cursor.done() ? 0 : cursor.remaining()} {}

    value_type& operator*() { return current_; }
    const value_type& operator*() const { return current_; }

    /// @brief Store the current vector's lanes inside the range, then move to the next vector.
    Iterator& operator++() {
      detail::store_partial(cursor_.ptr(), *current_, current_.remaining());
      cursor_.index += lanes;
      current_ = value_type{Argon<ScalarType>{}, cursor_.done() ? 0 : cursor_.remaining()};
      return *this;
    }
    void operator++(int) { ++*this; }

    friend bool operator==(const Iterator& it, std::default_sentinel_t) { return it.cursor_.done(); }

   private:
    detail::TailCursor<ScalarType> cursor_;
    value_type current_;
  };
  static_assert(std::input_or_output_iterator<Iterator>);

  store_tail() = default;
  /// @brief View `count` elements starting at `start`.
  store_tail(ScalarType* start, size_t count) : start_{start}, count_{count} {}

  Iterator begin() const { return Iterator{{start_, 0, count_}}; }
  std::default_sentinel_t end() const { return {}; }
  /// @brief The number of vectors, counting a final partial one.
  size_t size() const { return (count_ + lanes - 1) / lanes; }

 private:
  ScalarType* start_ = nullptr;
  size_t count_ = 0;
};

/// @brief In-place read/write view of a range as vectors, including a final partial vector. See
/// load_store::with_tail().
/// @details A vector is loaded on first access and, if it was accessed mutably, stored when the iterator advances;
/// only the lanes inside the range are read or written.
template <typename ScalarType>
class load_store_tail : public std::ranges::view_interface<load_store_tail<ScalarType>> {
  static constexpr size_t lanes = Argon<ScalarType>::lanes;

 public:
  /// @brief Iterator over the vectors of the range; dereferences to a Partial to read and modify.
  struct Iterator {
    using value_type = Partial<ScalarType>;  ///< The value type of the iterator.
    using difference_type = std::ptrdiff_t;  ///< The difference type of the iterator.

    Iterator() = default;
    Iterator(detail::TailCursor<ScalarType> cursor) : cursor_{cursor} {}

    value_type& operator*() {
      load();
      dirty_ = true;
      return current_;
    }
    const value_type& operator*() const {
      load();
      return current_;
    }

    /// @brief Store the current vector if it was modified, then move to the next vector.
    Iterator& operator++() {
      if (dirty_) {
        detail::store_partial(cursor_.ptr(), *current_, current_.remaining());
      }
      cursor_.index += lanes;
      loaded_ = dirty_ = false;
      return *this;
    }
    void operator++(int) { ++*this; }

    friend bool operator==(const Iterator& it, std::default_sentinel_t) { return it.cursor_.done(); }

   private:
    void load() const {
      if (!loaded_) {
        const size_t n = cursor_.remaining();
        current_ = value_type{detail::load_partial(static_cast<const ScalarType*>(cursor_.ptr()), n), n};
        loaded_ = true;
      }
    }

    detail::TailCursor<ScalarType> cursor_;
    mutable value_type current_;
    mutable bool loaded_ = false;
    bool dirty_ = false;
  };
  static_assert(std::input_or_output_iterator<Iterator>);

  load_store_tail() = default;
  /// @brief View `count` elements starting at `start`.
  load_store_tail(ScalarType* start, size_t count) : start_{start}, count_{count} {}

  Iterator begin() const { return Iterator{{start_, 0, count_}}; }
  std::default_sentinel_t end() const { return {}; }
  /// @brief The number of vectors, counting a final partial one.
  size_t size() const { return (count_ + lanes - 1) / lanes; }

 private:
  ScalarType* start_ = nullptr;
  size_t count_ = 0;
};

}  // namespace argon::vectorize
