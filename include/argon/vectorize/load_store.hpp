/// @headerfile argon/vectorize/load_store.hpp

#pragma once
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <span>
#include "argon/argon_full.hpp"
#include "argon/helpers/argon_for.hpp"
#include "argon/helpers/size.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd mve
#else
#define simd neon
#endif

namespace argon::vectorize {

/// @brief A SIMD vectorized view of a range of data.
/// @tparam ScalarType The type of the elements in the range.

template <typename ScalarType>
struct load_store : public std::ranges::view_interface<load_store<ScalarType>> {
  /// @brief The SIMD vector type used for vectorization.
  using intrinsic_type = simd::Vec128_t<ScalarType>;

  /// The number of lanes in the SIMD vector.
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(ScalarType);

 public:
  /// @brief An iterator for the vectorized view.
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;     ///< The iterator category.
    using value_type = helpers::ArgonFor_t<intrinsic_type>;  ///< The value type of the iterator.
    using difference_type = std::ptrdiff_t;                  ///< The difference type of the iterator.

    Iterator() = default;

    /// @brief Constructs an iterator from a pointer to the start of the range.
    /// @param ptr A pointer to the start of the range.
    Iterator(ScalarType* ptr) : ptr{ptr}, vec{value_type::Load(ptr)} {}

    const value_type& operator*() const { return vec; }

    /// @brief Dereference the iterator to get the current value.
    /// @return A reference to the current value.
    value_type& operator*() {
      dirty_ = true;
      return vec;
    }

    const value_type* operator->() const { return &vec; }

    /// @brief Dereference the iterator to get the current value.
    /// @return A pointer to the current value.
    value_type* operator->() {
      dirty_ = true;
      return &vec;
    }

    /// @brief Increment the iterator to the next value.
    /// @return A reference to the iterator itself.
    Iterator& operator++() {
      if (dirty_) {
        vec.StoreTo(ptr);  // store before increment
      }
      ptr += lanes;
      vec = value_type::Load(ptr);
      return *this;
    }

    /// @brief Postfix increment operator for the iterator.
    void operator++(int) { ++(*this); }

    /// @brief Comparison operators for the iterator.
    /// @return True if the iterators are equal, false otherwise.
    friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }

    /// @copydoc operator==(const Iterator&, const Iterator&)
    friend bool operator==(const Iterator& a, const ScalarType* ptr) { return a.ptr == ptr; }

    /// @brief  Comparison operators for the iterator.
    /// @return True if the iterators are not equal, false otherwise.
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; }

    /// @copydoc operator!=(const Iterator&, const Iterator&)
    friend bool operator!=(const Iterator& a, const ScalarType* ptr) { return a.ptr != ptr; }

    /// @brief  Reload the iterator with the current value.
    void reload() { vec = value_type::Load(ptr); }

   private:
    bool dirty_;
    ScalarType* ptr = nullptr;
    value_type vec;
  };
  static_assert(std::input_or_output_iterator<Iterator>);

  /// @brief A const iterator for the vectorized view.
  struct ConstIterator {
    using iterator_category = std::forward_iterator_tag;     ///< The iterator category.
    using value_type = helpers::ArgonFor_t<intrinsic_type>;  ///< The value type of the iterator.
    using difference_type = std::ptrdiff_t;                  ///< The difference type of the iterator.

    ConstIterator() = default;

    /// @brief Constructs a const iterator from a pointer to the start of the range.
    /// @param ptr A pointer to the start of the range.
    ConstIterator(const ScalarType* ptr) : ptr{ptr}, vec{value_type::Load(ptr)} {}

    /// @brief Dereference the const iterator to get the current value.
    /// @return A reference to the current value.
    const value_type operator*() const { return vec; }

    /// @brief Increment operator for the const iterator.
    /// @return A reference to the const iterator itself.
    ConstIterator& operator++() {
      ptr += lanes;
      vec = value_type::Load(ptr);
      return *this;
    }

    /// @brief Postfix increment operator for the const iterator.
    /// @return A copy of the const iterator before incrementing.
    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    /// @brief Equivalence operator
    /// @return True if the const iterators are equal, false otherwise.
    friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return a.ptr == b.ptr; }

    /// @brief Non-equivalence operator
    /// @return True if the const iterators are not equal, false otherwise.
    friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.ptr != b.ptr; }

   private:
    const ScalarType* ptr = nullptr;
    value_type vec;
  };
  static_assert(std::input_iterator<ConstIterator>);

  using iterator = Iterator;             ///< The iterator type for the vectorized view.
  using const_iterator = ConstIterator;  ///< The const iterator type for the vectorized view.

  /// @brief Constructs a vectorized view from a pointer to the start of the range and the end of the range.
  /// @param start A pointer to the start of the range.
  /// @param end A pointer to the end of the range.
  load_store(ScalarType* start, ScalarType* end)
      : start_{start}, size_{helpers::vectorizeable_size<ScalarType>(end - start) / lanes} {};

  /// @brief Constructs a vectorized view from a pointer to the start of the range and the size of the range.
  /// @param start A pointer to the start of the range.
  /// @param size The size of the range.
  load_store(ScalarType* start, const size_t size)
      : start_{start}, size_{helpers::vectorizeable_size<ScalarType>(size) / lanes} {};

  /// @brief Constructs a vectorized view from a span.
  /// @param span A span representing the range of data.
  load_store(std::span<ScalarType> span)
      : start_{span.data()}, size_{helpers::vectorizeable_size<ScalarType>(span.size()) / lanes} {};

  /// @brief Constructs a vectorized view from a range.
  /// @tparam R The type of the range.
  /// @param r A range representing the range of data.
  template <std::ranges::contiguous_range R>
  load_store(R&& r)
      : start_{&*std::ranges::begin(r)}, size_{helpers::vectorizeable_size<ScalarType>(std::ranges::size(r)) / lanes} {}

  /// @brief Returns an iterator to the beginning
  /// @return An iterator to the start of the view.
  iterator begin() const { return Iterator(start_); }

  /// @brief Returns an iterator to the end
  /// @return An iterator to the end of the view.
  ScalarType* end() const { return start_ + (size_ * lanes); }

  /// @brief Returns a const iterator to the beginning of the range.
  /// @return A const iterator to the start of the view.
  const_iterator cbegin() const { return ConstIterator(start_); }

  /// @brief Returns a const iterator to the end of the range.
  /// @return A const iterator to the end of the view.
  const ScalarType* cend() const { return start_ + (size_ * lanes); }

  /// @brief Get the size of the view.
  /// @return The size of the view.
  /// @note The size is the number of vectorized elements in the view.
  size_t size() const { return size_; }

 private:
  ScalarType* start_;
  size_t size_;
};

/// @brief CTAD for load_store.
/// @tparam R The type of the range.
template <std::ranges::contiguous_range R>
load_store(R&& r) -> load_store<std::ranges::range_value_t<R>>;

static_assert(std::ranges::range<load_store<int32_t>>);
static_assert(std::ranges::view<load_store<int32_t>>);
static_assert(std::movable<load_store<int32_t>>);
static_assert(std::ranges::viewable_range<load_store<int32_t>>);

}  // namespace argon::vectorize
#undef simd
