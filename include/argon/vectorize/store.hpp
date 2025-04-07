#pragma once
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

template <typename ScalarType, size_t Stride = 1>
struct store;

template <typename ScalarType>
struct store<ScalarType, 1> : std::ranges::view_interface<store<ScalarType>> {
  using intrinsic_type = simd::Vec128_t<ScalarType>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(ScalarType);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  struct StoreIterator {
    using difference_type = std::ptrdiff_t;
    using reference_type = StoreIterator&;
    using pointer_type = Argon<ScalarType>*;
    using value_type = Argon<ScalarType>;

    StoreIterator() = default;
    StoreIterator(ScalarType* ptr) : ptr_{ptr} {}

    Argon<ScalarType>& operator*() { return vec_; }

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

template <typename ScalarType, size_t stride>
struct store : std::ranges::view_interface<store<ScalarType, stride>> {
  using intrinsic_type = simd::Vec128_t<ScalarType>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(ScalarType);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

  static_assert(stride > 1 && stride < 5, "Interleaving Stores can only be performed with a stride of 2, 3, or 4");

 public:
  struct StoreInterleavedIterator {
    using difference_type = std::ptrdiff_t;
    using reference_type = StoreInterleavedIterator&;

    StoreInterleavedIterator() = default;
    StoreInterleavedIterator(ScalarType* ptr) : ptr_{ptr} {}

    std::array<Argon<ScalarType>, stride>& operator*() { return vecs_; }

    StoreInterleavedIterator& operator++() {
      argon::store(ptr_, vecs_);
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
    friend bool operator==(const StoreInterleavedIterator& a, const ScalarType* ptr) { return a.ptr_ == ptr; }
    friend bool operator!=(const StoreInterleavedIterator& a, const StoreInterleavedIterator& b) {
      return a.ptr_ != b.ptr_;
    }
    friend bool operator!=(const StoreInterleavedIterator& a, const ScalarType* ptr) { return a.ptr_ != ptr; }
    friend auto operator<=>(const StoreInterleavedIterator& a, const StoreInterleavedIterator& b) {
      return a.ptr_ <=> b.ptr_;
    }

   private:
    std::array<Argon<ScalarType>, stride> vecs_;
    ScalarType* ptr_;
  };
  static_assert(std::sized_sentinel_for<StoreInterleavedIterator, StoreInterleavedIterator>);
  static_assert(std::output_iterator<StoreInterleavedIterator, std::array<Argon<ScalarType>, stride>>);

  using iterator = StoreInterleavedIterator;

  iterator begin() { return start_; }
  ScalarType* end() { return start_ + size_; }
  size_t size() const { return size_ / (lanes * stride); }

  template <std::ranges::contiguous_range R>
  store(R&& r) : start_{&*std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

 private:
  ScalarType* start_;
  size_t size_;
};

static_assert(std::ranges::range<store<int32_t, 2>>);
static_assert(std::ranges::view<store<int32_t, 2>>);

template <size_t Stride = 1, std::ranges::contiguous_range R>
store(R&& r) -> store<std::ranges::range_value_t<R>, Stride>;

template <size_t Stride = 1, typename ScalarType>
store(const std::span<ScalarType>) -> store<ScalarType, Stride>;

static_assert(std::ranges::range<store<int32_t>>);
static_assert(std::ranges::view<store<int32_t>>);

}  // namespace argon::vectorize
#undef simd
