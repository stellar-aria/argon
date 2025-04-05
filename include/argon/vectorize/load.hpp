#pragma once
#include <ranges>
#include "argon/argon_full.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_NEON
#define simd neon
#elifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

namespace argon {

template <typename scalar_type>
struct vectorize_load : std::ranges::view_interface<vectorize_load<scalar_type>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }
 public:
  struct LoadIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using reference_type = LoadIterator&;
    using pointer_type = Argon<scalar_type>*;
    using value_type = Argon<scalar_type>;

    LoadIterator() = default;
    LoadIterator(scalar_type* ptr) : ptr_{ptr} {}

    Argon<scalar_type> operator*() const { return value_type::Load(ptr_); }

    LoadIterator& operator+=(int n) {
      ptr_ += n * lanes;
      return *this;
    }

    LoadIterator& operator-=(int n) {
      ptr_ -= n * lanes;
      return *this;
    }

    LoadIterator operator++(int) {
      LoadIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    LoadIterator& operator++() {
      ptr_ += lanes;
      return *this;
    }

    LoadIterator operator--(int) {
      LoadIterator tmp = *this;
      --(*this);
      return tmp;
    }

    LoadIterator& operator--() {
      ptr_ -= lanes;
      return *this;
    }

    LoadIterator operator+(int n) const {
      LoadIterator it = *this;
      it += n;
      return it;
    }

    LoadIterator operator-(int n) const {
      LoadIterator it = *this;
      it -= n;
      return it;
    }

    LoadIterator& operator[](int n) const { return *(*this + n); }

    difference_type operator-(const LoadIterator& other) const { return ptr_ - other.ptr_; }

    friend bool operator==(const LoadIterator& a, const LoadIterator& b) { return a.ptr_ == b.ptr_; }
    friend bool operator==(const LoadIterator& a, const scalar_type* ptr) { return a.ptr_ == ptr; }
    friend bool operator!=(const LoadIterator& a, const LoadIterator& b) { return a.ptr_ != b.ptr_; }
    friend bool operator!=(const LoadIterator& a, const scalar_type* ptr) { return a.ptr_ != ptr; }
    friend auto operator<=>(const LoadIterator& a, const LoadIterator& b) { return a.ptr_ <=> b.ptr_; }

    friend LoadIterator operator+(const int n, const LoadIterator& it) { return it + n; }

   private:
    scalar_type* ptr_;
  };
  static_assert(std::sized_sentinel_for<LoadIterator, LoadIterator>);
  static_assert(std::bidirectional_iterator<LoadIterator>);
  static_assert(std::input_iterator<LoadIterator>);

  using iterator = LoadIterator;

  iterator begin() { return start_; }
  scalar_type* end() { return start_ + size_; }
  size_t size() const { return size_ / lanes; }

  template <std::ranges::contiguous_range R>
  vectorize_load(R&& r) : start_{&*std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

 private:
  scalar_type* start_;
  size_t size_;
};
static_assert(std::ranges::range<vectorize_load<int32_t>>);
static_assert(std::ranges::view<vectorize_load<int32_t>>);

template <std::ranges::contiguous_range R>
vectorize_load(R&& r) -> vectorize_load<std::ranges::range_value_t<R>>;

}  // namespace argon
#undef simd
