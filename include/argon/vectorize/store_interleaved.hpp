#pragma once
#include <ranges>
#include "argon.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_NEON
#define simd neon
#elifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

namespace argon {

template <size_t stride, typename scalar_type>
struct vectorize_store_interleaved : std::ranges::view_interface<vectorize_store_interleaved<stride, scalar_type>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);

 public:
  struct StoreInterleavedIterator {
    using difference_type = std::ptrdiff_t;
    using reference_type = StoreInterleavedIterator&;

    StoreInterleavedIterator() = default;
    StoreInterleavedIterator(scalar_type* ptr) : ptr_{ptr} {}

    std::array<Argon<scalar_type>, stride>& operator*() { return vecs_; }

    StoreInterleavedIterator& operator++() {
      argon::store_interleaved(ptr_, vecs_);
      ptr_ += lanes;
      vecs_ = {};
      return *this;
    }

    StoreInterleavedIterator operator++(int) {
      StoreInterleavedIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    StoreInterleavedIterator& operator--() {
      ptr_ -= lanes;
      vecs_ = {};
      return *this;
    }

    StoreInterleavedIterator operator--(int) {
      StoreInterleavedIterator tmp = *this;
      --(*this);
      return tmp;
    }

    difference_type operator-(const StoreInterleavedIterator& other) const { return ptr_ - other.ptr_; }

    friend bool operator==(const StoreInterleavedIterator& a, const StoreInterleavedIterator& b) { return a.ptr_ == b.ptr_; }
    friend bool operator==(const StoreInterleavedIterator& a, const scalar_type* ptr) { return a.ptr_ == ptr; }
    friend bool operator!=(const StoreInterleavedIterator& a, const StoreInterleavedIterator& b) { return a.ptr_ != b.ptr_; }
    friend bool operator!=(const StoreInterleavedIterator& a, const scalar_type* ptr) { return a.ptr_ != ptr; }
    friend auto operator<=>(const StoreInterleavedIterator& a, const StoreInterleavedIterator& b) { return a.ptr_ <=> b.ptr_; }

   private:
    std::array<Argon<scalar_type>, stride> vecs_;
    scalar_type* ptr_;
  };
  static_assert(std::sized_sentinel_for<StoreInterleavedIterator, StoreInterleavedIterator>);
  static_assert(std::output_iterator<StoreInterleavedIterator, std::array<Argon<scalar_type>, stride>>);

  using iterator = StoreInterleavedIterator;

  iterator begin() { return start_; }
  scalar_type* end() { return start_ + size_; }
  size_t size() const { return size_ / lanes; }

  template <std::ranges::contiguous_range R>
  vectorize_store_interleaved(R&& r) : start_{std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

 private:
  scalar_type* start_;
  size_t size_;
};

static_assert(std::ranges::range<vectorize_store_interleaved<2, int32_t>>);
static_assert(std::ranges::view<vectorize_store_interleaved<2, int32_t>>);

}  // namespace argon
#undef simd
