// Copyright 2025 Katherine Whitlock
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/// @headerfile argon/vectorize/load.hpp
/// @brief Provides a view for loading data from a contiguous range into SIMD vectors.
/// @include vectorize/load.cpp

#pragma once
#include <ranges>
#include "argon/argon_full.hpp"
#include "argon/helpers/size.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd mve
#else
#define simd neon
#endif

namespace argon::vectorize {

/// @brief A view that loads data from a contiguous range into SIMD vectors.
/// @tparam ScalarType The scalar type of the SIMD vector (e.g., int8_t, float32_t).
template <typename ScalarType>
struct load : std::ranges::view_interface<load<ScalarType>> {
  using intrinsic_type = simd::Vec128_t<ScalarType>;  ///< The SIMD vector type.
  static constexpr size_t lanes =
      sizeof(intrinsic_type) / sizeof(ScalarType);  ///< The number of lanes in the SIMD vector.

 public:
  /// @brief The Iterator type for the range.
  /// @note This iterator performs a load operation on every dereference!
  struct LoadIterator {
    using iterator_category = std::bidirectional_iterator_tag;  ///< The iterator category.
    using difference_type = std::ptrdiff_t;                     ///< The difference type.
    using value_type = helpers::ArgonFor_t<intrinsic_type>;     ///< The value type of the iterator.
    using reference_type = value_type&;

    LoadIterator() = default;

    /// @brief Constructs a LoadIterator from a pointer to the data.
    /// @param ptr The pointer to the data.
    LoadIterator(const ScalarType* ptr) : ptr_{ptr} {}

    /// @brief Dereferences the iterator to get the SIMD vector.
    /// @return The SIMD vector loaded from the data.
    /// @note This function `Load`s the data from the pointer and returns it as an Argon vector.
    Argon<ScalarType> operator*() const { return value_type::Load(ptr_); }

    /// @brief Increments the iterator by a number of steps
    /// @param n The number of steps to increment.
    /// @return The updated iterator.
    LoadIterator& operator+=(int n) {
      ptr_ += n * lanes;
      return *this;
    }

    /// @brief Decrements the iterator by a number of steps
    /// @param n The number of steps to decrement.
    /// @return The updated iterator.
    LoadIterator& operator-=(int n) {
      ptr_ -= n * lanes;
      return *this;
    }

    /// @brief Postfix increment operator.
    /// @return The iterator before incrementing.
    LoadIterator operator++(int) {
      LoadIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    /// @brief Prefix increment operator.
    /// @return The updated iterator.
    LoadIterator& operator++() {
      ptr_ += lanes;
      return *this;
    }

    /// @brief Postfix decrement operator.
    /// @return The iterator before decrementing.
    LoadIterator operator--(int) {
      LoadIterator tmp = *this;
      --(*this);
      return tmp;
    }

    /// @brief Prefix decrement operator.
    /// @return The updated iterator.
    LoadIterator& operator--() {
      ptr_ -= lanes;
      return *this;
    }

    /// @brief Adds an integer to the iterator and returns a new iterator.
    /// @param n The number of steps to add.
    /// @return The updated iterator.
    LoadIterator operator+(int n) const {
      LoadIterator it = *this;
      it += n;
      return it;
    }

    /// @brief Subtracts an integer from the iterator and returns a new iterator.
    /// @param n The number of steps to subtract.
    /// @return The updated iterator.
    LoadIterator operator-(int n) const {
      LoadIterator it = *this;
      it -= n;
      return it;
    }

    /// @brief Accesses the element at the given index.
    /// @param n The index of the element to access.
    /// @return A reference to the element at the given index.
    LoadIterator& operator[](int n) const { return *(*this + n); }

    /// @brief Calculates the difference between two iterators.
    /// @param other The other iterator to subtract from this one.
    /// @return The difference between the two iterators.
    difference_type operator-(const LoadIterator& other) const { return ptr_ - other.ptr_; }

    /// @brief Adds an integer to the iterator and returns a new iterator.
    /// @param n The number of steps to add.
    /// @param it The iterator to add to.
    /// @return The updated iterator.
    friend LoadIterator operator+(const int n, const LoadIterator& it) { return it + n; }

    /// @brief Compares LoadIterators for equality.
    friend bool operator==(const LoadIterator& a, const LoadIterator& b) { return a.ptr_ == b.ptr_; }

    /// @copydoc operator==(const LoadIterator&, const LoadIterator&)
    friend bool operator==(const LoadIterator& a, const ScalarType* ptr) { return a.ptr_ == ptr; }

    /// @brief Compares LoadIterators for inequality.
    friend bool operator!=(const LoadIterator& a, const LoadIterator& b) { return a.ptr_ != b.ptr_; }

    /// @copydoc operator!=(const LoadIterator&, const LoadIterator&)
    friend bool operator!=(const LoadIterator& a, const ScalarType* ptr) { return a.ptr_ != ptr; }

    /// @brief Compares LoadIterators
    friend auto operator<=>(const LoadIterator& a, const LoadIterator& b) { return a.ptr_ <=> b.ptr_; }

   private:
    const ScalarType* ptr_;
  };
  static_assert(std::sized_sentinel_for<LoadIterator, LoadIterator>);
  static_assert(std::bidirectional_iterator<LoadIterator>);
  static_assert(std::input_iterator<LoadIterator>);

  using iterator = LoadIterator;       ///< The iterator type for the range.
  using sentinel = const ScalarType*;  ///< The sentinel type for the range.

  /// @brief Returns an iterator to the beginning of the range.
  /// @return An iterator to the beginning of the range.
  iterator begin() { return start_; }

  /// @brief Returns an iterator to the end of the range.
  /// @return An iterator to the end of the range.
  const ScalarType* end() { return start_ + (size_ * lanes); }

  /// @brief Returns the size of the range.
  /// @return The size of the range.
  size_t size() const { return size_; }

  /// @brief Construct a load from a range.
  /// @tparam R The range type.
  /// @param r The range to load data from.
  template <std::ranges::contiguous_range R>
  load(R&& r)
      : start_{&*std::ranges::begin(r)}, size_{helpers::vectorizeable_size<ScalarType>(std::ranges::size(r)) / lanes} {}

  /// @brief Construct a load from a span
  /// @param span The span to load data from.
  load(const std::span<ScalarType> span) : start_{span.data()}, size_{vectorizeable_size(span.size()) / lanes} {}

 private:
  const ScalarType* start_;
  size_t size_;
};

static_assert(std::ranges::range<load<int32_t>>);
static_assert(std::ranges::view<load<int32_t>>);
static_assert(std::movable<load<int32_t>>);
static_assert(std::ranges::viewable_range<load<int32_t>>);

template <std::ranges::contiguous_range R>
load(R&& r) -> load<std::remove_cv_t<std::ranges::range_value_t<R>>>;

template <typename ScalarType>
load(const std::span<ScalarType>) -> load<std::remove_cv_t<ScalarType>>;

}  // namespace argon::vectorize
#undef simd
