#pragma once
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <span>
#include "argon_full.hpp"
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
struct vectorize : public std::ranges::view_interface<vectorize<scalar_type>> {
  using intrinsic_type = simd::Vec128_t<scalar_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = Argon<scalar_type>;
    using difference_type = std::ptrdiff_t;

    Iterator() = default;
    Iterator(scalar_type* ptr) : ptr{ptr}, vec{value_type::Load(ptr)} {}

    value_type& operator*() { return vec; }
    value_type* operator->() { return &vec; }
    const value_type& operator*() const { return vec; }
    const value_type* operator->() const { return &vec; }
    Iterator& operator++() {
      vec.StoreTo(ptr);  // store before increment
      ptr += lanes;
      vec = value_type::Load(ptr);
      return *this;
    }
    void operator++(int) { ++(*this); }
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
    using value_type = Argon<scalar_type>;
    using difference_type = std::ptrdiff_t;

    ConstIterator() = default;
    ConstIterator(const scalar_type* ptr) : ptr{ptr}, vec{value_type::Load(ptr)} {}

    const value_type operator*() const { return vec; }
    ConstIterator& operator++() {
      ptr += lanes;
      vec = value_type::Load(ptr);
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

  vectorize(scalar_type* start, scalar_type* end) : start_{start}, size_{vectorizeable_size(end - start)} {};
  vectorize(scalar_type* start, const size_t size) : start_{start}, size_{vectorizeable_size(size)} {};
  vectorize(std::span<scalar_type> span) : start_{span.data()}, size_{vectorizeable_size(span.size())} {};

  template <std::ranges::contiguous_range R>
  vectorize(R&& r) : start_{&*std::ranges::begin(r)}, size_{vectorizeable_size(std::ranges::size(r))} {}

  vectorize(vectorize&&) = default;
  vectorize(const vectorize&) = default;
  vectorize& operator=(vectorize&&) = default;
  vectorize& operator=(const vectorize&) = default;

  iterator begin() const { return Iterator(start_); }
  scalar_type* end() const { return start_ + size_; }
  const_iterator cbegin() const { return ConstIterator(start_); }
  const scalar_type* cend() const { return start_ + size_; }
  size_t size() const { return size_; }

 private:
  scalar_type* start_;
  size_t size_;
};

template <std::ranges::contiguous_range R>
vectorize(R&& r) -> vectorize<std::ranges::range_value_t<R>>;

static_assert(std::ranges::range<vectorize<int32_t>>);
static_assert(std::ranges::view<vectorize<int32_t>>);
static_assert(std::movable<vectorize<int32_t>>);
static_assert(std::ranges::viewable_range<vectorize<int32_t>>);

/// @brief Split a span into two spans, one aligned to the vector size and one not
namespace split {

/// @brief Split a span into two spans, with the first span aligned to the vector size
/// @param span The span to split
/// @return A pair of spans, the first divisible by the vector size and the second containing any remaining elements
template <typename scalar_type>
std::pair<std::span<scalar_type>, std::span<scalar_type>> head_aligned(std::span<scalar_type> span) {
  constexpr size_t lanes = sizeof(simd::Vec128_t<scalar_type>) / sizeof(scalar_type);
  return {span.first(span.size() & ~(lanes - 1)), span.last(span.size() & (lanes - 1))};
}

/// @brief Split a span into two spans, with the second span aligned to the vector size
/// @param span The span to split
/// @return A pair of spans, the first containing any remaining elements and the second divisible by the vector size
template <typename scalar_type>
std::pair<std::span<scalar_type>, std::span<scalar_type>> tail_aligned(std::span<scalar_type> span) {
  constexpr size_t lanes = sizeof(simd::Vec128_t<scalar_type>) / sizeof(scalar_type);
  return {span.first(span.size() & (lanes - 1)), span.last(span.size() & ~(lanes - 1))};
}

}  // namespace split
}  // namespace argon
#undef simd
