#pragma once
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <span>
#include "argon.hpp"
#include "argon/vectorize.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_FEATURE_MVE
#define simd helium
#else
#define simd neon
#endif

namespace argon {

template <size_t stride, typename scalar_type>
struct vectorize_interleaved : public std::ranges::view_interface<vectorize<scalar_type>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using argon_type = Argon<scalar_type>;
    using value_type = std::array<argon_type, stride>;
    using difference_type = std::ptrdiff_t;

    Iterator() = default;
    Iterator(scalar_type* ptr) : ptr{ptr}, vec{argon_type::template LoadInterleaved<stride>(ptr)} {}

    value_type& operator*() { return vec; }
    value_type* operator->() { return &vec; }
    const value_type& operator*() const { return vec; }
    const value_type* operator->() const { return &vec; }
    Iterator& operator++() {
      store_interleaved(ptr, vec);  // store before increment
      ptr += lanes;
      vec = argon_type::template LoadInterleaved<stride>(ptr);
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }
    friend bool operator==(const Iterator& a, const scalar_type* ptr) { return a.ptr == ptr; }
    friend bool operator!=(const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; }
    friend bool operator!=(const Iterator& a, const scalar_type* ptr) { return a.ptr != ptr; }

   private:
    scalar_type* ptr = nullptr;
    value_type vec;
  };
  static_assert(std::input_or_output_iterator<Iterator>);
  struct ConstIterator {
    using iterator_category = std::forward_iterator_tag;
    using argon_type = Argon<scalar_type>;
    using value_type = std::array<argon_type, stride>;
    using difference_type = std::ptrdiff_t;

    ConstIterator() = default;
    ConstIterator(const scalar_type* ptr) : ptr{ptr}, vec{argon_type::template LoadInterleaved<stride>(ptr)} {}

    const value_type operator*() const { return vec; }
    ConstIterator& operator++() {
      ptr += lanes;
      vec = argon_type::template LoadInterleaved<stride>(ptr);
      return *this;
    }
    ConstIterator operator++(int) {
      ConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return a.ptr == b.ptr; }
    friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.ptr != b.ptr; }

   private:
    const scalar_type* ptr = nullptr;
    value_type vec;
  };
  static_assert(std::input_iterator<ConstIterator>);

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  vectorize_interleaved(scalar_type* start, scalar_type* end)
      : start_{start}, size_{vectorizeable_size(end - start)} {};
  vectorize_interleaved(scalar_type* start, const size_t size) : start_{start}, size_{vectorizeable_size(size)} {};
  vectorize_interleaved(const std::span<scalar_type> span)
      : start_{span.data()}, size_{vectorizeable_size(span.size())} {};

  template <size_t, std::ranges::contiguous_range R>
  vectorize_interleaved(R&& r) : start_{std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

  iterator begin() const { return Iterator(start_); }
  const scalar_type* end() const { return start_ + size_; }
  const_iterator cbegin() const { return ConstIterator(start_); }
  const scalar_type* cend() const { return start_ + size_; }
  size_t size() const { return size_; }

 private:
  scalar_type* start_;
  size_t size_;
};

// template <size_t stride, std::ranges::contiguous_range R>
// vectorize_interleaved(R&& r) -> vectorize_interleaved<stride, std::ranges::range_value_t<R>>;

static_assert(std::ranges::range<vectorize_interleaved<3, int32_t>>);
static_assert(std::ranges::view<vectorize_interleaved<3, int32_t>>);
static_assert(std::movable<vectorize_interleaved<3, int32_t>>);
static_assert(std::ranges::viewable_range<vectorize_interleaved<3, int32_t>>);

}  // namespace argon

#undef simd
