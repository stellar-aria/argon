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

template <typename scalar_type>
struct vectorize_store : std::ranges::view_interface<vectorize_store<scalar_type>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  struct StoreIterator {
    using difference_type = std::ptrdiff_t;
    using reference_type = StoreIterator&;
    using pointer_type = Argon<scalar_type>*;
    using value_type = Argon<scalar_type>;

    StoreIterator() = default;
    StoreIterator(scalar_type* ptr) : ptr_{ptr} {}

    Argon<scalar_type>& operator*() { return vec_; }

    StoreIterator& operator++() {
      vec_.StoreTo(ptr_);
      ptr_ += lanes;
      vec_ = {};
      return *this;
    }

    StoreIterator operator++(int) {
      StoreIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    StoreIterator& operator--() {
      vec_.StoreTo(ptr_);
      ptr_ -= lanes;
      vec_ = {};
      return *this;
    }

    StoreIterator operator--(int) {
      StoreIterator tmp = *this;
      --(*this);
      return tmp;
    }

    difference_type operator-(const StoreIterator& other) const { return ptr_ - other.ptr_; }

    friend bool operator==(const StoreIterator& a, const StoreIterator& b) { return a.ptr_ == b.ptr_; }
    friend bool operator==(const StoreIterator& a, const scalar_type* ptr) { return a.ptr_ == ptr; }
    friend bool operator!=(const StoreIterator& a, const StoreIterator& b) { return a.ptr_ != b.ptr_; }
    friend bool operator!=(const StoreIterator& a, const scalar_type* ptr) { return a.ptr_ != ptr; }
    friend auto operator<=>(const StoreIterator& a, const StoreIterator& b) { return a.ptr_ <=> b.ptr_; }

   private:
    Argon<scalar_type> vec_{};
    scalar_type* ptr_ = nullptr;
  };
  static_assert(std::sized_sentinel_for<StoreIterator, StoreIterator>);
  static_assert(std::output_iterator<StoreIterator, Argon<scalar_type>>);

  using iterator = StoreIterator;

  iterator begin() { return start_; }
  scalar_type* end() { return start_ + size_; }
  size_t size() const { return size_ / lanes; }

  template <std::ranges::contiguous_range R>
  vectorize_store(R&& r) : start_{&*std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

 private:
  scalar_type* start_;
  size_t size_;
};
template <std::ranges::contiguous_range R>
vectorize_store(R&& r) -> vectorize_store<std::ranges::range_value_t<R>>;

static_assert(std::ranges::range<vectorize_store<int32_t>>);
static_assert(std::ranges::view<vectorize_store<int32_t>>);

}  // namespace argon
#undef simd
