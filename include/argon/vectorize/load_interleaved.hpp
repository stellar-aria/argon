#pragma once
#include <ranges>
#include "argon/argon_full.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

namespace argon {

template <typename scalar_type, size_t stride = 2>
struct vectorize_load_interleaved : std::ranges::view_interface<vectorize_load_interleaved<scalar_type, stride>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

  static_assert(stride > 1 && stride < 5, "Interleaving Loads can only be performed with a stride of 2, 3, or 4");

 public:
  struct LoadInterleavedIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using reference_type = LoadInterleavedIterator&;
    using value_type = std::array<Argon<scalar_type>, stride>;

    LoadInterleavedIterator() = default;
    LoadInterleavedIterator(scalar_type* ptr) : ptr_{ptr} {}

    std::array<Argon<scalar_type>, stride> operator*() const {
      return Argon<scalar_type>::template LoadInterleaved<stride>(ptr_);
    }

    LoadInterleavedIterator& operator+=(int n) {
      ptr_ += n * lanes * stride;
      return *this;
    }

    LoadInterleavedIterator& operator-=(int n) {
      ptr_ -= n * lanes * stride;
      return *this;
    }

    LoadInterleavedIterator operator++(int) {
      LoadInterleavedIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    LoadInterleavedIterator& operator++() {
      ptr_ += lanes * stride;
      return *this;
    }

    LoadInterleavedIterator operator--(int) {
      LoadInterleavedIterator tmp = *this;
      --(*this);
      return tmp;
    }

    LoadInterleavedIterator& operator--() {
      ptr_ -= lanes * stride;
      return *this;
    }

    LoadInterleavedIterator operator+(int n) const {
      LoadInterleavedIterator it = *this;
      it += n;
      return it;
    }

    LoadInterleavedIterator operator-(int n) const {
      LoadInterleavedIterator it = *this;
      it -= n;
      return it;
    }

    LoadInterleavedIterator& operator[](int n) const { return *(*this + n); }

    difference_type operator-(const LoadInterleavedIterator& other) const { return ptr_ - other.ptr_; }

    friend bool operator==(const LoadInterleavedIterator& a, const LoadInterleavedIterator& b) {
      return a.ptr_ == b.ptr_;
    }
    friend bool operator==(const LoadInterleavedIterator& a, const scalar_type* ptr) { return a.ptr_ == ptr; }
    friend bool operator!=(const LoadInterleavedIterator& a, const LoadInterleavedIterator& b) {
      return a.ptr_ != b.ptr_;
    }
    friend bool operator!=(const LoadInterleavedIterator& a, const scalar_type* ptr) { return a.ptr_ != ptr; }
    friend auto operator<=>(const LoadInterleavedIterator& a, const LoadInterleavedIterator& b) {
      return a.ptr_ <=> b.ptr_;
    }

    friend LoadInterleavedIterator operator+(const int n, const LoadInterleavedIterator& it) { return it + n; }

   private:
    scalar_type* ptr_;
  };
  static_assert(std::sized_sentinel_for<LoadInterleavedIterator, LoadInterleavedIterator>);
  static_assert(std::bidirectional_iterator<LoadInterleavedIterator>);
  static_assert(std::input_iterator<LoadInterleavedIterator>);

  using iterator = LoadInterleavedIterator;

  iterator begin() { return start_; }
  scalar_type* end() { return start_ + size_; }
  size_t size() const { return size_ / (lanes * stride); }

  template <std::ranges::contiguous_range R>
  vectorize_load_interleaved(R&& r)
      : start_{&*std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

 private:
  scalar_type* start_;
  size_t size_;
};

static_assert(std::ranges::range<vectorize_load_interleaved<int32_t, 2>>);
static_assert(std::ranges::view<vectorize_load_interleaved<int32_t, 2>>);

template <std::ranges::contiguous_range R, size_t stride = 2>
vectorize_load_interleaved(R&& r) -> vectorize_load_interleaved<std::ranges::range_value_t<R>, stride>;

}  // namespace argon
#undef simd
