#pragma once
/// @file simde_neon.hpp
/// @brief SIMDe's NEON implementation (x86 and other non-Arm hosts) under the NEON intrinsic names.
/// @details Only the NEON names are aliased. SIMDe's global SIMDE_ENABLE_NATIVE_ALIASES would also alias its x86
/// emulation onto _mm_* / _mm256_* / __crc32*, which breaks any translation unit that uses the real x86 intrinsics
/// too: one including <immintrin.h> (or <intrin.h>, which MSVC's and Windows' headers pull in) after Argon.

#ifndef SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES
#define SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES
#endif
#ifndef SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES
#define SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES
#endif
#ifndef SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES
#define SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES
#endif
#include <arm/neon.h>

// SIMDe also aliases the ACLE CRC32 intrinsics, whose names x86's <ia32intrin.h> declares as its own functions.
// Argon doesn't use them on non-Arm hosts; drop the aliases so the x86 declarations stay intact.
#undef __crc32b
#undef __crc32h
#undef __crc32w
#undef __crc32d
#undef __crc32cb
#undef __crc32ch
#undef __crc32cw
#undef __crc32cd
