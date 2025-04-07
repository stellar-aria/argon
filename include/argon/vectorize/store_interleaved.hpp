#pragma once
#include <ranges>
#include "argon.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

namespace argon::vectorize {

template <typename scalar_type, size_t stride = 2>
struct store_interleaved : std::ranges::view_interface<store_interleaved<scalar_type, stride>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

  static_assert(stride > 1 && stride < 5, "Interleaving Stores can only be performed with a stride of 2, 3, or 4");

 public:
  struct StoreInterleavedIterator {
    using difference_type = std::ptrdiff_t;
    using reference_type = StoreInterleavedIterator&;

    StoreInterleavedIterator() = default;
    StoreInterleavedIterator(scalar_type* ptr) : ptr_{ptr} {}

    std::array<Argon<scalar_type>, stride>& operator*() { return vecs_; }

    StoreInterleavedIterator& operator++() {
      argon::store_interleaved(ptr_, vecs_);
      ptr_ += lanes * stride;
      vecs_ = {};
      return *this;
    }

    StoreInterleavedIterator operator++(int) {
      StoreInterleavedIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    StoreInterleavedIterator& operator--() {
      ptr_ -= lanes * stride;
      vecs_ = {};
      return *this;
    }

    StoreInterleavedIterator operator--(int) {
      StoreInterleavedIterator tmp = *this;
      --(*this);
      return tmp;
    }

    difference_type operator-(const StoreInterleavedIterator& other) const { return ptr_ - other.ptr_; }

    friend bool operator==(const StoreInterleavedIterator& a, const StoreInterleavedIterator& b) {
      return a.ptr_ == b.ptr_;
    }
    friend bool operator==(const StoreInterleavedIterator& a, const scalar_type* ptr) { return a.ptr_ == ptr; }
    friend bool operator!=(const StoreInterleavedIterator& a, const StoreInterleavedIterator& b) {
      return a.ptr_ != b.ptr_;
    }
    friend bool operator!=(const StoreInterleavedIterator& a, const scalar_type* ptr) { return a.ptr_ != ptr; }
    friend auto operator<=>(const StoreInterleavedIterator& a, const StoreInterleavedIterator& b) {
      return a.ptr_ <=> b.ptr_;
    }

   private:
    std::array<Argon<scalar_type>, stride> vecs_;
    scalar_type* ptr_;
  };
  static_assert(std::sized_sentinel_for<StoreInterleavedIterator, StoreInterleavedIterator>);
  static_assert(std::output_iterator<StoreInterleavedIterator, std::array<Argon<scalar_type>, stride>>);

  using iterator = StoreInterleavedIterator;

  iterator begin() { return start_; }
  scalar_type* end() { return start_ + size_; }
  size_t size() const { return size_ / (lanes * stride); }

  template <std::ranges::contiguous_range R>
  store_interleaved(R&& r) : start_{&*std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

 private:
  scalar_type* start_;
  size_t size_;
};

static_assert(std::ranges::range<store_interleaved<int32_t, 2>>);
static_assert(std::ranges::view<store_interleaved<int32_t, 2>>);

template <std::ranges::contiguous_range R, size_t stride = 2>
store_interleaved(R&& r) -> store_interleaved<std::ranges::range_value_t<R>, stride>;

}  // namespace argon::vectorize
#undef simd
