# Vectorized Views

The Argon library provides several vectorized views for processing data using SIMD operations. These views work with contiguous ranges and provide iterator-based access to the vectorized data. For hot loops, and for Helium's hardware loops, see also [`vectorize::for_each`](#looping-over-a-whole-range-vectorizefor_each).

## Vectorized read (vectorize::load)

The `load` view presents a read-only view of a contiguous set of data (i.e. a `std::ranges::input_range`). `Load` is lazy, and occurs only on dereference (and on every dereference, as it is not memoized).

```cpp
#include <argon/vectorize/load.hpp>
#include <array>

int main() {
  std::array<int32_t, 512> data;
  data.fill(5);

  // Read data using SIMD loads
  for (auto vec : argon::vectorize::load(data)) {
      // Process loaded data
      // vec is loaded using SIMD load operations
  }
}
```

## Vectorized write (vectorize::store)

The `store` presents a write-only view of a contiguous set of data (i.e. a `std::ranges::output_range`). `StoreTo` is lazy, and occurs _only_ on incrementing or decrementing the iterator.

```cpp
#include <argon/vectorize/store.hpp>
#include <array>

int main() {
  std::array<int32_t, 512> data;
  data.fill(0);

  // Write data using SIMD stores
  for (auto& vec : argon::vectorize::store(data)) {
      vec = {1, 2, 3, 4}; // Values are stored using SIMD store operations
  }
}
```

## Vectorized In-place Read/Write (vectorize::load_store)

The `load_store` view allows you to process data in-place using SIMD operations. Internally,
a vector is stored in the iterator that is loaded on creation, and then stored on increment, before the next element is loaded. Dereferencing accesses the internal stored vector, and will not `Load` again without a manual `.reload()` call.

Note: If you do not need _both_ read _and_ write on the same range, use either `vectorize::load` or `vectorize::store` instead, as `vectorize::load_store` incurs the read latency and writeback penalty of them combined.

```cpp
#include <argon/vectorize.hpp>
#include <array>

int main() {
  std::array<int32_t, 512> data;
  data.fill(5);

  // Increment each element using SIMD operations
  for (auto& vec : argon::vectorize::load_store(data)) {
      vec = vec + 1;
  }
}
```

## Interleaved Data Access

For working with interleaved data (like RGB values), Argon provides specialized views:

### Loading Interleaved Data

```cpp
#include <argon/vectorize/load.hpp>
#include <array>

int main() {
  std::array<int32_t, 512> data; // Interleaved data (e.g. RGBRGBRGB...)

  // Load interleaved data with stride of 3 (RGB)
  for (auto [r, g, b] : argon::vectorize::load_interleaved<3>(data)) {
      // Process r, g, b vectors separately
  }
}
```

### Storing Interleaved Data

```cpp
#include <argon/vectorize/store.hpp>
#include <array>

int main() {
  std::array<int32_t, 512> data;

  // Store interleaved data with stride of 2
  for (auto& [even, odd] : argon::vectorize::store_interleaved<2>(data)) {
      even = {0, 2, 4, 6};  // Even indices
      odd = {1, 3, 5, 7};   // Odd indices
  }
}
```

## Key Features

- All views work with contiguous ranges (arrays, vectors, spans)
- Automatic alignment and size handling
- Efficient SIMD operations through Argon's SIMD wrappers
- Iterator-based interface compatible with C++ ranges
- Support for different data types (int32_t, float, etc.)

## Looping over a whole range (`vectorize::for_each`)

`for_each<T>(n, body)` visits the elements `[0, n)` a vector at a time, final partial vector included. The body
receives a step: `step.Load(ptr)` and `step.Store(ptr, v)` access its elements of any array, `step.LoadWiden` and
`step.StoreNarrow` do so through a narrower integer type, and `step.index()`, `step.count()` and `step.active()`
describe it. Lanes past the end of the range load as zero and are never written.

```cpp
#include <argon/vectorize/for_each.hpp>

// out = a + (b - a) * t, for any n
void mix(float* out, const float* a, const float* b, std::ptrdiff_t n, float t) {
  argon::vectorize::for_each<float>(n, [&](auto step) {
    step.Store(out, step.Load(a) + (step.Load(b) - step.Load(a)) * t);
  });
}

// int16 samples processed in int32 lanes: widened on load, narrowed on store
void gain(int16_t* samples, std::ptrdiff_t n) {
  argon::vectorize::for_each<int32_t>(n, [&](auto step) {
    step.StoreNarrow(samples, (step.LoadWiden(samples) * 3) >> 2);
  });
}
```

Write the body as a generic lambda (`auto step`): on NEON it runs with plain whole-vector steps and then once with a
partial step, so the main loop has no predication at all. On Helium every step is predicated, and the loop is
written in the shape GCC and clang turn into a low-overhead tail-predicated loop (`dlstp`/`letp`): the hardware
counts the remaining elements and predicates the last vector, with no compare-and-branch and no scalar epilogue. A CTest codegen check (`tail_loops_use_dlstp`) keeps it
that way. GCC tail-predicates float loops only with `-fno-trapping-math` (or `-ffast-math`), because the inactive
lanes compute too; without it the loop is still predicated, just with an explicit loop counter.

### `for_each` or `with_tail()`?

Both handle every element, with the same results. Prefer `for_each` for hot loops: its loop is the tightest on every
platform (on AArch64, `ldr q`/op/`str q`/`cmp`/`bne`), it reliably becomes a hardware loop on Helium, and it works
over any number of arrays. Use the `with_tail()` views when you want a range — range-for, `std::ranges`
algorithms, or adding tail handling to existing view-based code. Their loop checks for the partial vector on every
iteration (a well-predicted branch), and on Helium whether they become `dlstp`/`letp` depends on the compiler: GCC
16 converts them for 16- and 32-bit lanes but not 8-bit ones, and clang 23 keeps them predicated but doesn't form a
hardware loop.

If every channel of interleaved data gets the same treatment (a gain, a clamp, a mix), treat it as flat data:
`for_each<int16_t>(frames * 2, ...)` needs no de-interleaving and keeps the hardware loop.

## Including the final partial vector (`with_tail()`)

`load`, `store` and `load_store` skip any elements after the last whole vector. Call `with_tail()` on them to visit
those too, as one final partial vector. Each element is then an `argon::vectorize::Partial`: `*p` is the vector,
`p.count()` how many of its leading lanes are in the range, and `p.active()` those lanes as an `argon::Predicate`.
Lanes past the end of the range load as zero and are never written.

```cpp
#include <argon/vectorize/load.hpp>
#include <argon/vectorize/load_store.hpp>

int32_t sum(std::span<const int32_t> data) {
  int32_t total = 0;
  for (auto p : argon::vectorize::load(data).with_tail()) {
    total += p->ReduceAdd(p.active());  // the zeroed lanes would be harmless here, but not for a minimum
  }
  return total;
}

void scale(std::span<float> data) {
  for (auto& p : argon::vectorize::load_store(data).with_tail()) {
    *p = *p * 3.0f;  // only the lanes inside the range are stored
  }
}
```

On Helium (MVE) every vector is loaded and stored under a `vctp` predicate, so there is no scalar epilogue; whether
the loop also becomes `dlstp`/`letp` depends on the compiler (see above). On NEON the whole vectors use plain loads
and stores; only the final partial vector is loaded and stored lane by lane.

`load_interleaved`, `store_interleaved` and `interleaved` have `with_tail()` too. Their lanes are frames of `Stride`
elements, each element is a `Partial` whose value is one vector per channel, and elements that don't complete a frame
are not visited. Whole groups use `vld2`/`vld3`/`vld4` and the matching stores; since those can't be predicated, even
on Helium, the final partial group is gathered and scattered per channel.

## Notes

1. The number of elements processed in each iteration depends on the SIMD vector size for the target architecture
2. Data size should ideally be aligned to the SIMD vector size
3. Elements after the last whole vector are not processed, unless you use `with_tail()` or `for_each` (see above)
4. Interleaved operations support strides of 2, 3, or 4

## Error Handling

The views handle common errors gracefully:

- Non-contiguous ranges: Will not compile
- Invalid strides: Static assertions prevent invalid stride values
- Sizes that aren't a multiple of the lane count: only whole vectors are processed, unless you use `with_tail()`
