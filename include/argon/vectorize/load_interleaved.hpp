#pragma once
#include <ranges>
#include "argon/argon_full.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

namespace argon::vectorize {

template <typename ScalarType, size_t Stride = 2>
struct load_interleaved : std::ranges::view_interface<load_interleaved<ScalarType, Stride>> {
  using intrinsic_type = simd::Vec128_t<ScalarType>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(ScalarType);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

  static_assert(Stride > 1 && Stride < 5, "Interleaving Loads can only be performed with a stride of 2, 3, or 4");

 public:
  struct LoadInterleavedIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using reference_type = LoadInterleavedIterator&;
    using value_type = std::array<Argon<ScalarType>, Stride>;

    LoadInterleavedIterator() = default;
    LoadInterleavedIterator(ScalarType* ptr) : ptr_{ptr} {}

    std::array<Argon<ScalarType>, Stride> operator*() const {
      return Argon<ScalarType>::template LoadInterleaved<Stride>(ptr_);
    }

    LoadInterleavedIterator& operator+=(int n) {
      ptr_ += n * lanes * Stride;
      return *this;
    }

    LoadInterleavedIterator& operator-=(int n) {
      ptr_ -= n * lanes * Stride;
      return *this;
    }

    LoadInterleavedIterator operator++(int) {
      LoadInterleavedIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    LoadInterleavedIterator& operator++() {
      ptr_ += lanes * Stride;
      return *this;
    }

    LoadInterleavedIterator operator--(int) {
      LoadInterleavedIterator tmp = *this;
      --(*this);
      return tmp;
    }

    LoadInterleavedIterator& operator--() {
      ptr_ -= lanes * Stride;
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
    friend bool operator==(const LoadInterleavedIterator& a, const ScalarType* ptr) { return a.ptr_ == ptr; }
    friend bool operator!=(const LoadInterleavedIterator& a, const LoadInterleavedIterator& b) {
      return a.ptr_ != b.ptr_;
    }
    friend bool operator!=(const LoadInterleavedIterator& a, const ScalarType* ptr) { return a.ptr_ != ptr; }
    friend auto operator<=>(const LoadInterleavedIterator& a, const LoadInterleavedIterator& b) {
      return a.ptr_ <=> b.ptr_;
    }

    friend LoadInterleavedIterator operator+(const int n, const LoadInterleavedIterator& it) { return it + n; }

   private:
    ScalarType* ptr_;
  };
  static_assert(std::sized_sentinel_for<LoadInterleavedIterator, LoadInterleavedIterator>);
  static_assert(std::bidirectional_iterator<LoadInterleavedIterator>);
  static_assert(std::input_iterator<LoadInterleavedIterator>);

  using iterator = LoadInterleavedIterator;

  iterator begin() { return start_; }
  ScalarType* end() { return start_ + size_; }
  size_t size() const { return size_ / (lanes * Stride); }

  template <std::ranges::contiguous_range R>
  load_interleaved(R&& r) : start_{&*std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

 private:
  ScalarType* start_;
  size_t size_;
};

static_assert(std::ranges::range<load_interleaved<int32_t, 2>>);
static_assert(std::ranges::view<load_interleaved<int32_t, 2>>);

template <std::ranges::contiguous_range R, size_t stride = 2>
load_interleaved(R&& r) -> load_interleaved<std::ranges::range_value_t<R>, stride>;

}  // namespace argon::vectorize
#undef simd
