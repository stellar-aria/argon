# Argon

[![License](https://img.shields.io/github/license/stellar-aria/argon.svg?style=flat-square&color=FF0000&label=License)](https://choosealicense.com/licenses/mit/)
![Archs](https://img.shields.io/badge/ARM-v7%20|%20v8+-orange.svg?style=flat-square)
[![C++ Version](https://img.shields.io/badge/C++-23-yellow.svg?style=flat-square)](https://en.wikipedia.org/wiki/C%2B%2B23)
[![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/stellar-aria/argon/tests.yml?style=flat-square&label=Build)](https://github.com/stellar-aria/argon/actions)
[![GitHub Release](https://img.shields.io/github/v/release/stellar-aria/argon?style=flat-square&color=blue&label=Release)](https://github.com/stellar-aria/argon/releases/latest)
[![Argon](https://img.shields.io/badge/Ar-18-8A2BE2?style=flat-square)](https://github.com/stellar-aria/argon)

Argon is a library that provides a sane, minimal-overhead C++ interface to ARM's NEON SIMD intrinsics.

## Why?

Argon grew out of a desire to use C++ abstractions for vector intrinsics, without sacrificing expressiveness or specificity.
Most C++ vector libraries ([highway](https://github.com/google/highway), [xsimd](https://github.com/xtensor-stack/xsimd))
abstract away all platform uniqueness in favor of common denominators. When considering the use case of those libraries, namely
HPC or multi-platform portability, that's a strength. Unfortunately, when you're targeting a very specific subset of those architectures,
or you have one architecture that needs to be optimized above all others, such abstractions fall short.

This is where Argon was created to exist: A NEON-first, others-second zero-overhead abstraction library with modern constructs
and capabilities.

#### What Argon is:

- A low-level intrinsics abstraction layer with sane naming conventions and overloaded functions
- Higher-level encapsulated vector object types built on that layer

#### What Argon is not (yet?):

- A library of optimized commonly used algorithms

## API Documentation

Documentation on usage and internal details (generated by Doxygen) can be found [here](https://stellar-aria.github.io/argon/)

## Examples

### Object-oriented Argon interface

```cpp
#include <argon/argon.hpp>
#include <iostream>

Argon<float> triangle(Argon<float> phase) {
  phase = argon::ternary(phase > 0.5f, 1.f, 0.f) - phase;
  return Argon{-1.f}.MultiplyAdd(phase.Absolute(), 4.f);
}

int main() {
  float frequency = 440.f;
  float phase_increment = frequency / 44100.f;
  Argon<float> phase = Argon{0}.MultiplyAdd(phase_increment, Argon<float>::Iota(0))
  Argon<float> wave = triangle(phase);

  // Print the result
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << "Result[" << i << "]: " << result[i] << std::endl;
  }
}
```

### Low-level NEON interface

```cpp
#include <argon/arm_simd.hpp>
#include <iostream>

int main() {
  // Example: Multiply-add two vectors using NEON
  float32x4_t a = {1.0f, 2.0f, 3.0f, 4.0f};
  float32x4_t b = {5.0f, 6.0f, 7.0f, 8.0f};
  float32x4_t c = {9.0f, 10.0f, 11.0f, 12.0f};

  // Perform vector multiply-add
  float32x4_t result = neon::multiply_add(a, b, c);

  // Print the result
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << "Result[" << i << "]: " << result[i] << std::endl;
  }

  return 0;
}
```

## Key Differences between NEON and MVE

|                               | NEON                          | MVE                             |
| ----------------------------- | ----------------------------- | ------------------------------- |
| Number of quad-word registers | 16                            | 8                               |
| Narrowing support (see note)  | to lower double-word register | to even or odd scalar registers |
| Double-word instructions      | :heavy_check_mark:            | :x:                             |
| 64-bit floating point         | :heavy_check_mark:            | :x:                             |
| Predicated lane instructions  | :x:                           | :heavy_check_mark:              |
| Native Scatter-Gather         | :x:                           | :heavy_check_mark:              |

### Narrowing support

- NEON supports double-word and quad-word operations, MVE only has quad-word.
  - This means that operations that _would_ result in a double-word (such as narrowing) instead go into either the top or bottom registers of the current quadword.
  - i.e. in NEON, an int32x4_t narrow to int16x4_t {x, x, x, x} => {x, x, x, x, o, o, o, o}
  - while in MVE they are placed in the bottom or top of a pair: {x, x, x, x} => {x, o, x, o, x, o, x, o}

## Backend Support

| Backend                        | Architectures            | Status             | Notes                                             |
| ------------------------------ | ------------------------ | ------------------ | ------------------------------------------------- |
| [ARM NEON (ARMv7)][arm-neon]   | VFPv3, VFPv3-FP16, VFPv4 | :white_check_mark: | Primary target                                    |
| [ARM NEON (ARMv8+)][arm-neon]  | AArch32, AArch64         | :white_check_mark: | Primary target                                    |
| [ARM MVE (Helium)][arm-helium] | ARMv8.1-M                | :warning:          | Secondary target (in-progress)                    |
| [SIMDe][simde]                 | x86-64(SSE2/AVX), RISCV  | :white_check_mark: | Tertiary target, used for portability and testing |

## Compatibility

Argon can be compiled using the following tool sets:

Compilers:

- GCC 14.2 or later
- LLVM Embedded Toolchain for ARM 19 or later (ARMv7-A)
- LLVM/Clang 20.1 or later (AArch32/AArch64)
- MSVC 19.44 or later

Testing is currently done across a range of platforms and compilers, including:

### Architectures

| Compiler | ARMv7              | ARMv8              | ARMv8.1-M          | X86-64             |
| -------- | ------------------ | ------------------ | ------------------ | ------------------ |
| GCC      | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
| Clang    | :x:                | :heavy_check_mark: | (TBD)              | :heavy_check_mark: |
| MSVC     | :x:                | (TBD)              | :x:                | :heavy_check_mark: |

### Target ABI

| Compiler | Bare-metal         | Linux              | macOS              | Windows            |
| -------- | ------------------ | ------------------ | ------------------ | ------------------ |
| GCC      | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :warning:\*        |
| Clang    | :warning:\*        | :heavy_check_mark: | :warning:\*\*      | :heavy_check_mark: |
| MSVC     | :x:                | :x:                | :x:                | :heavy_check_mark: |

\*: Windows/GCC (via MinGW64) and Bare-metal/Clang (via the LLVM Embedded Toolchain for ARM) are used regularly but not
tested via CI.

\*\*: In order to compile with Clang on macOS, you'll need to use the brew-bundled versions of libc++, as Apple's system libraries do not support required C++23 features.

### Host Platform

| Host    | ARMv7     | ARMv8              | X86-64             |
| ------- | --------- | ------------------ | ------------------ |
| Linux   | :warning: | :heavy_check_mark: | :heavy_check_mark: |
| macOS   | :x:       | :heavy_check_mark: | :heavy_check_mark: |
| Windows | :x:       | (TBD)              | :heavy_check_mark: |

[arm-neon]: https://developer.arm.com/Architectures/Neon
[arm-helium]: https://developer.arm.com/Architectures/Helium
[simde]: https://github.com/simd-everywhere/simde
[simde-support]: https://github.com/simd-everywhere/simde?tab=readme-ov-file#current-status
