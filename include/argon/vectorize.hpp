#pragma once
#include <cstddef>
#include <iterator>
#include <span>
#include "arm_simd/helpers/nonvec.hpp"
#include "arm_simd/helpers/vec128.hpp"

#ifdef __ARM_NEON
#define simd neon
#else
#ifdef __ARM_FEATURE_MVE
#define simd helium
#endif
#endif

template <typename T>
class Argon;

namespace argon {
template <typename scalar_type>
struct vectorize {
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
    Iterator& operator++() {
      vec.StoreTo(ptr);  // store before increment
      ptr += lanes;
      vec = value_type::Load(ptr);
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
  struct ConstIterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = Argon<scalar_type>;
    using difference_type = std::ptrdiff_t;

    ConstIterator() = default;
    ConstIterator(scalar_type const* ptr) : ptr{ptr}, vec{value_type::Load(ptr)} {}

    value_type& operator*() const { return vec; }
    value_type* operator->() const { return &vec; }
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
    friend bool operator==(const ConstIterator& a, const scalar_type* ptr) { return a.ptr == ptr; }
    friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return a.ptr != b.ptr; }
    friend bool operator!=(const ConstIterator& a, const scalar_type* ptr) { return a.ptr != ptr; }

   private:
    scalar_type* ptr = nullptr;
    value_type vec;
  };
  //static_assert(std::forward_iterator<Iterator>);

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  vectorize(scalar_type* start, size_t size) : start_{start}, size_{vectorizeable_size(size)} {};
  vectorize(const std::span<scalar_type> span) : start_{span.data()}, size_{vectorizeable_size(span.size())} {};
  vectorize(scalar_type* start, scalar_type* end) : start_{start}, size_{vectorizeable_size(end - start)} {};

  iterator begin() { return Iterator(start_); }
  scalar_type* end() { return start_ + size_; }
  const_iterator cbegin() const { return ConstIterator(start_); }
  const scalar_type* cend() const { return start_ + size_; }
  size_t size() const { return size_; }

 private:
  scalar_type* start_;
  size_t size_;
};

namespace vectorize_loop {

template <typename intrinsic_type>
class main {
  using scalar_type = simd::NonVec_t<intrinsic_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(scalar_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }

 public:
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = simd::NonVec_t<intrinsic_type>;
    using difference_type = std::ptrdiff_t;

    value_type& operator*() const { return *ptr; }
    value_type* operator->() { return ptr; }
    Iterator& operator++() {
      ptr += lanes;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }

   private:
    value_type* ptr;
  };
  static_assert(std::forward_iterator<Iterator>);

  using iterator = Iterator;
  using const_iterator = const Iterator;

  main(scalar_type* start, size_t size) : store{start, vectorizeable_size(size)} {};
  main(const std::span<scalar_type> span) : store{span.begin(), vectorizeable_size(span.size())} {};
  main(scalar_type* start, scalar_type* end) : store{start, vectorizeable_size(end - start)} {};

  iterator begin() { return store.begin(); }
  const_iterator begin() const { return store.cbegin(); }
  iterator end() { return store.end(); }
  const_iterator end() const { return store.cend(); }
  size_t size() const { return store.size(); }

 private:
  std::span<scalar_type> store;
};

template <typename intrinsic_type>
struct tail : std::span<simd::NonVec_t<intrinsic_type>> {
  using value_type = simd::NonVec_t<intrinsic_type>;

 private:
  using super = std::span<value_type>;
  static constexpr size_t lanes = sizeof(intrinsic_type) / sizeof(value_type);
  static constexpr size_t vectorizeable_size(size_t size) { return size & ~(lanes - 1); }
  static constexpr size_t tail_size(size_t size) { return size & (lanes - 1); }

 public:
  tail(value_type* start, size_t size) : super{start + vectorizeable_size(size), tail_size(size)} {}
  tail(const std::span<value_type> span)
      : super{span.begin() + vectorizeable_size(span.size()), tail_size(span.size())} {}
  tail(value_type* start, value_type* end) : super{start + vectorizeable_size(end - start), tail_size(end - start)} {}
};

}  // namespace vectorize_loop
}  // namespace argon
#undef simd
