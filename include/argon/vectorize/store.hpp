#pragma once
#include <iterator>
#include <ranges>
#include "argon.hpp"
#include "argon/argon_full.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

namespace argon::vectorize {

template <typename ScalarType>
struct store : std::ranges::view_interface<store<ScalarType>> {
  using intrinsic_type = simd::Vec128_t<ScalarType>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(ScalarType);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  struct StoreIterator {
    using iterator_category = std::input_iterator_tag;  ///< The iterator category.
    using difference_type = std::ptrdiff_t;
    using value_type = Argon<ScalarType>;

    StoreIterator() = default;
    StoreIterator(ScalarType* ptr) : ptr_{ptr} {}

    Argon<ScalarType>& operator*() { return vec_; }
    const Argon<ScalarType>& operator*() const { return vec_; }

    StoreIterator& operator+=(int n) {
      vec_.StoreTo(ptr_);
      ptr_ += n * lanes;
      vec_ = {};
      return *this;
    }

    StoreIterator& operator-=(int n) {
      vec_.StoreTo(ptr_);
      ptr_ -= n * lanes;
      vec_ = {};
      return *this;
    }

    StoreIterator operator++(int) {
      StoreIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    StoreIterator operator--(int) {
      StoreIterator tmp = *this;
      --(*this);
      return tmp;
    }

    StoreIterator& operator++() {
      vec_.StoreTo(ptr_);
      ptr_ += lanes;
      vec_ = {};
      return *this;
    }

    StoreIterator& operator--() {
      vec_.StoreTo(ptr_);
      ptr_ -= lanes;
      vec_ = {};
      return *this;
    }

    /// @brief Adds an integer to the iterator and returns a new iterator.
    /// @param n The number of steps to add.
    /// @return The updated iterator.
    StoreIterator operator+(int n) const {
      StoreIterator it = *this;
      it += n;
      return it;
    }

    /// @brief Subtracts an integer from the iterator and returns a new iterator.
    /// @param n The number of steps to subtract.
    /// @return The updated iterator.
    StoreIterator operator-(int n) const {
      StoreIterator it = *this;
      it -= n;
      return it;
    }

    difference_type operator-(const StoreIterator& other) const { return ptr_ - other.ptr_; }

    /// @brief Adds an integer to the iterator and returns a new iterator.
    /// @param n The number of steps to add.
    /// @param it The iterator to add to.
    /// @return The updated iterator.
    friend StoreIterator operator+(const int n, const StoreIterator& it) { return it + n; }

    friend bool operator==(const StoreIterator& a, const StoreIterator& b) { return a.ptr_ == b.ptr_; }
    friend bool operator==(const StoreIterator& a, const ScalarType* ptr) { return a.ptr_ == ptr; }
    friend bool operator!=(const StoreIterator& a, const StoreIterator& b) { return a.ptr_ != b.ptr_; }
    friend bool operator!=(const StoreIterator& a, const ScalarType* ptr) { return a.ptr_ != ptr; }
    friend auto operator<=>(const StoreIterator& a, const StoreIterator& b) { return a.ptr_ <=> b.ptr_; }

   private:
    Argon<ScalarType> vec_{};
    ScalarType* ptr_ = nullptr;
  };
  static_assert(std::sized_sentinel_for<StoreIterator, StoreIterator>);
  static_assert(std::output_iterator<StoreIterator, Argon<ScalarType>>);

  using iterator = StoreIterator;

  iterator begin() { return start_; }
  ScalarType* end() { return start_ + size_; }
  size_t size() const { return size_ / lanes; }

  template <std::ranges::contiguous_range R>
  store(R&& r) : start_{&*std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

 private:
  ScalarType* start_;
  size_t size_;
};
static_assert(std::ranges::range<store<int32_t>>);
static_assert(std::ranges::view<store<int32_t>>);
static_assert(std::movable<store<int32_t>>);
static_assert(std::ranges::viewable_range<store<int32_t>>);

template <std::ranges::contiguous_range R>
store(R&& r) -> store<std::ranges::range_value_t<R>>;

template <typename ScalarType>
store(const std::span<ScalarType>) -> store<ScalarType>;

}  // namespace argon::vectorize
#undef simd
