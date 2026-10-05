# Design: Cross-Platform Predication

Status: **Proposed** (2026-10-05)

Argon's Helium (MVE) support does not currently compile, and where it does compile, comparisons are silently wrong.
This document proposes a cross-platform predicate type as the foundation for first-class Helium support — predicated
execution, tail-predicated loops, and scatter/gather — while keeping NEON code unchanged in behaviour and codegen.

## Background

### NEON and MVE model "masks" differently

|                     | NEON                                     | MVE (Helium)                                         |
| ------------------- | ---------------------------------------- | ---------------------------------------------------- |
| Compare result      | Full-width mask vector (`uint32x4_t`)     | 16-bit predicate in `VPR.P0` (`mve_pred16_t`)        |
| Predicate layout    | All-ones / all-zeros per lane            | One bit per **byte**; a 32-bit lane owns 4 bits      |
| Masked execution    | None — compute both sides, then `vbsl`   | `vpt`/`vpst` blocks; `_m`, `_x`, `_z` intrinsics     |
| Masked load/store   | None (a load past the end can fault)     | `vld1q_z` / `vst1q_p` suppress inactive-lane faults  |
| Loop tails          | Scalar epilogue                          | `vctp` + `dlstp`/`letp` low-overhead loops            |
| Scatter/gather      | None (lane-by-lane emulation)            | Native, with offset, base, and write-back forms      |

### State before this work

Everything in this section has since been fixed on `helium-build` (steps 0–2); it is kept as the starting point.

- **The M55 build is broken.** Every spec fails to compile with `arm-none-eabi-g++ -mcpu=cortex-m55` (169 errors,
  mostly from `vector.hpp` and `argon_full.hpp`). The M55 CI runner was disabled in `0eb585a`, so this went unnoticed.
- **Comparisons are silently wrong on MVE.** `Vector::Equal` (`vector.hpp:742`) returns `argon_bool_type`, a vector
  type, but `mve::equal` returns `mve_pred16_t`. The scalar constructor broadcasts the predicate bits into every lane:

  ```asm
  vcmp.i32  eq, q0, q1
  vmrs      r3, p0
  vdup.32   q0, r3        ; predicate bits broadcast, not a mask
  ```

- **The `mve::` intrinsic layer is mostly complete.** It already wraps predicated (`_m`/`_x`/`_z`) forms, `vctp`,
  gather/scatter, `vpselq`, and the bottom/top narrowing family. The gap is the `Argon` layer.
- **`CondMonad` (`argon.hpp:197`) cannot be instantiated.** Its constraints name `argon_result_type`, which became
  `argon_bool_type` in the Common→Vector refactor. Its `else_` is also inverted: it selects the *else* value where the
  `if_` condition held. The WIP branch `origin/condmonad` is based on the pre-refactor `Common` class.
- **`vectorize::` views drop the remainder.** `size_ = vectorizeable_size(n) / lanes`, so trailing elements are not
  visited; callers must write their own epilogue.

### Codegen measurements

Compiled with `-O2 -mcpu=cortex-m55 -mfloat-abi=hard`, GCC 14 (`arm-none-eabi-g++`) and Clang.

| Pattern                                                  | Clang                       | GCC                                      |
| -------------------------------------------------------- | --------------------------- | ---------------------------------------- |
| `vpselq(vaddq(a, b), a, p)` — "op, then select"          | `vpt` + `vaddt`             | `vadd` + `vcmp` + `vpsel` (one extra)    |
| Vector-extension `a > c ? a + b : a`                     | `vpt` + `vaddt`             | `vadd` + `vcmp` + `vpsel`                |
| Mask vector → `vcmpneq_n(m, 0)` → `vld1q_z`              | `vpt` + `vldrwt` (folded)   | +4 instructions (`vmov`×2, `vpsel`, `vcmp`) |
| `vctp32q` loop with `vld1q_z` / `vstrwq_p`               | `dlstp.32` / `letp`         | `dlstp.32` / `letp`                      |
| `vcmpgtq(a, b) & vcmpgtq(c, d)`                          | via GPRs (`vmrs`/`ands`/`vmsr`) | via GPRs                            |

Takeaways:

1. Storing a mask vector on MVE and converting at intrinsic boundaries is free on Clang but costs ~4 instructions per
   conversion on GCC — and GCC is the M55 CI toolchain. **MVE must store the native `mve_pred16_t`.**
2. "Compute, then `Select`" is correct on both platforms and already optimal on Clang. Explicit predicated arithmetic
   is a GCC optimisation (one `vpsel`), not a prerequisite.
3. Both compilers form low-overhead tail-predicated loops from `vctp` + `_z`/`_p` intrinsics, so the `vectorize::`
   views can get Helium's tail handling without hand-written assembly.
4. Combining two predicates with `&` round-trips through general-purpose registers. A predicated compare
   (`vcmpgtq_m(c, d, p)`) does it in one instruction.

## Proposal

### 1. `argon::Predicate<VectorType>`

A distinct type returned by every comparison, with platform-specific storage and one public API.

```cpp
namespace argon {
template <typename VectorType>
class Predicate {
 public:
#ifdef ARGON_PLATFORM_MVE
  using storage_type = mve_pred16_t;          // one bit per byte
#else
  using storage_type = Bool_t<VectorType>;    // all-ones / all-zeros per lane
#endif
  static constexpr size_t lanes = /* lanes of VectorType */;

  // Construction
  static Predicate True();                    // every lane active
  static Predicate False();
  static Predicate FirstN(size_t n);          // MVE: vctp{8,16,32,64}q; NEON: index < n

  // Logic
  Predicate operator&(Predicate) const;       // MVE: integer and on the 16-bit value
  Predicate operator|(Predicate) const;
  Predicate operator^(Predicate) const;
  Predicate operator~() const;                // MVE: vpnot

  // Selection
  template <typename V> V Select(V if_true, V if_false) const;   // MVE: vpselq; NEON: vbsl

  // Queries
  bool Any() const;                           // MVE: p != 0; NEON: OR of the two 64-bit halves
  bool All() const;
  bool None() const;
  size_t Count() const;                       // MVE: vaddvq_p(1, p); NEON: popcount / bits per lane
  bool Active(size_t lane) const;
  std::array<bool, lanes> to_array() const;

  // Interop
  Argon<unsigned_scalar> ToMask() const;      // MVE: vpselq(~0, 0, p)
  static Predicate FromMask(Argon<unsigned_scalar>);   // MVE: vcmpneq_n(m, 0)
  storage_type native() const;
};
}
```

`Vector<V>::argon_bool_type` becomes `Predicate<V>`. `Bool_t<V>` stays as the NEON storage type.

**Compatibility (decided).** Comparisons return `Predicate` on every platform. Code that used the old mask vector
keeps compiling through a `[[deprecated]]` implicit conversion to it, on both platforms; `ToMask()` is the
non-deprecated spelling. Two behaviours change: `to_array()` on a comparison result now yields `std::array<bool, N>`
rather than mask lanes, and member calls that only exist on `Argon` (`As<>()`, `BitwiseSelect`, ...) need `ToMask()`
first. `argon::ternary` accepts a `Predicate` or a mask vector, with vector or scalar branches.

### 2. Rebuild `CondMonad` on `Predicate`

`CondMonad` only needs `&`, `~`, and `Select`, so on top of `Predicate` it compiles to `vbsl` chains on NEON and
`vpsel`/VPT blocks on MVE.

- Constrain on `Predicate<V>` instead of `argon_result_type`.
- Fix `else_`: `condition().Select(value(), new_value)`.
- Port `operator&&` / `operator||` / `operator!` from `origin/condmonad`, defined on `Predicate`, not on arbitrary
  vectors.
- Add specs for `if_` / `else_if_` / `else_`, including first-match-wins ordering, on both platforms.
- Retire `origin/condmonad`; it predates the refactor and should not be merged.

```cpp
auto y = argon::if_(x < lo, lo)
             .else_if_(x > hi, hi)
             .else_(x);
```

### 3. Predicated memory operations

These are the operations that `Select` cannot express. A blended load still faults on NEON.

| Argon API                                      | MVE                          | NEON fallback                         |
| ---------------------------------------------- | ---------------------------- | ------------------------------------- |
| `Argon<T>::Load(ptr, Predicate p)`             | `vld1q_z` (inactive = 0)     | lane-by-lane loads of active lanes    |
| `v.StoreTo(ptr, Predicate p)`                  | `vst1q_p`                    | lane-by-lane stores of active lanes   |
| `v.ReduceAdd(Predicate p)`                     | `vaddvq_p`                   | `p.Select(v, 0).ReduceAdd()`          |
| `LoadGatherOffset{Bytes,Index}(base, off, p)`  | `vldr*q_gather_offset_z`     | lane-by-lane                          |
| `StoreScatterOffset{Bytes,Index}(base, off, p)`| `vstr*q_scatter_offset_p`    | lane-by-lane                          |
| `Argon<W>::LoadWiden(const N*, p?)`            | `vldrbq` / `vldrhq` (`_z`)    | `vld1` + `vmovl` (2x), lane by lane   |
| `v.StoreNarrow(N*, p?)`                        | `vstrbq` / `vstrhq` (`_p`)    | `vmovn` + `vst1` (2x), lane by lane   |
| `LoadGatherOffset{Bytes,Index}Widen(N*, off, p?)` | `vldr{b,h}q_gather_*`     | lane-by-lane                          |
| `StoreScatterOffset{Bytes,Index}Narrow(N*, off, p?)` | `vstr{b,h}q_scatter_*` | lane-by-lane                          |

The NEON fallbacks are correct but slow by design. They exist so portable code compiles everywhere, not to be the
NEON fast path.

### 4. Tail handling in `vectorize::`

Two ways to visit every element, with the same results:

- **`with_tail()`**, opt-in on every view so existing loops keep their documented behaviour: each element is a
  `Partial` (`*p`, `p.count()`, `p.active()`); lanes past the end load as zero and are never stored. The interleaved
  views have it too: whole groups use `vld2`–`vld4`, which can't be predicated, and the final partial group is
  gathered and scattered per channel.
- **`vectorize::for_each<T>(n, body)`**, a loop helper whose body gets a step (`Load`/`Store`, `LoadWiden`/
  `StoreNarrow`, `index()`, `count()`, `active()`). On MVE it is a signed counter, a `vctp` of the remaining count
  and predicated accesses — the shape the compilers' tail-predication passes match — and both GCC 16 and clang 23
  turn it into `dlstp`/`letp` for every lane type (floats need `-fno-trapping-math` with GCC). On NEON the body runs
  with plain whole-vector steps and once with a partial step, so the main loop is the tightest of the two.

The views' loop control and predicates are spread across iterator operations, so whether they become `dlstp`/`letp`
depends on how the inlined code simplifies: GCC converts them for 16- and 32-bit lanes but not 8-bit ones, and clang
not at all (it keeps them predicated, with an explicit counter). Hence `for_each` for hot loops, the views for
range-based code. `test/codegen/tail_loops.cpp` (CTest `tail_loops_use_dlstp`, M55) checks the loops GCC converts.

Zeroed inactive lanes are safe for sums but not for min/max/product reductions, so reductions take `active()`.

`vectorize::for_each_interleaved<T, Stride>` uses `vld2`/`vld4` for whole groups and predicated gathers for the last
one (a `dls`/`le` loop rather than `dlstp`, since structured loads can't be predicated), and predicated gathers
throughout for stride 3 on MVE, which has no `vld3` — that one becomes `dlstp`/`letp` (for 8-bit lanes, with clang
only). Data whose channels all get the same treatment can use `for_each` as flat data.

### 5. Predicated arithmetic and compares

`Add`, `Subtract`, `Multiply`, `Max`, `Min`, `SubtractAbs`, the bitwise operations, `Negate` and `Absolute` take
ACLE-style predicated forms:

```cpp
a.Add(b, p);            // _x: inactive lanes unspecified
a.Add(b, p, inactive);  // _m: inactive lanes from `inactive` (pass zero for _z)
```

On MVE these are VPT-predicated instructions (`vpst; vaddt`); on NEON, `_x` is the plain operation and `_m` adds a
`vbsl`. Float `Max`/`Min` go through `Select` on MVE too, since `vmaxnm`'s NaN handling differs from the unpredicated
form. In isolation `_m` is no shorter than `Select` (the destination needs `inactive` moved into it), so the gain
depends on register allocation in real loops.

Comparisons take a predicate as well: `x.LessThan(hi, x > lo)` is active where both hold. On MVE that is one
predicated compare (`vpst; vcmpt`) instead of two compares whose predicates are ANDed through core registers.

## Plan

| Step | Work                                                                                              | Size   |
| ---- | ------------------------------------------------------------------------------------------------- | ------ |
| 0    | **Done** (`helium-build`). Fix the M55 build: `MultiplySubtract` as `a - b*c`, comparison name mapping, gate `Reverse` and lane assignment, guard NEON-only specs; re-enable the M55 CI runner | Small  |
| 1    | **Done** (`helium-build`). `Predicate<V>`, comparisons return it; specs for logic, `Select`, `Any`/`All`/`Count`, `FirstN` on both platforms | Medium |
| 2    | **Done** (`helium-build`). Rebuild `CondMonad` on `Predicate`, fix `else_`, add specs                                        | Small  |
| 3    | **Done** (`helium-build`). Predicated load/store/reduce; complete scatter/gather (stores, predicated); widening loads and narrowing stores, contiguous and as gathers/scatters (`LoadWiden`, `StoreNarrow`, `…Widen`/`…Narrow`) | Medium |
| 4    | **Done** (`helium-build`): opt-in `with_tail()` on every view, and `vectorize::for_each`, the loop that reliably becomes `dlstp`/`letp`; CTest codegen check `tail_loops_use_dlstp` | Medium |
| 5    | **Done** (`helium-build`). Predicated arithmetic overloads and predicated compares                                           | Medium |

Steps 0 and 1 are prerequisites for everything else. Step 1 also fixes the silent `Equal` miscompile.

## Phase 2: Helium's DSP instructions

With predication, gathers and tail loops in place, the remaining gap is the instruction groups that make Helium a
DSP architecture. The `mve::` layer already wraps nearly all of them; the work is an `Argon` API for each, with a
NEON fallback so it stays portable. In order:

| Step | Work | NEON fallback |
| ---- | ---- | ------------- |
| 6  | **Done** (`helium-build`). **`float16` lanes on MVE.** MVE-F supports `f16` vectors, but nothing exercises `Argon<float16_t>` on M55. Specs first, then fix what they find. | n/a (already NEON) |
| 7  | **Done** (`helium-build`). **Bottom/top widening and narrowing:** `vmovlb/t`, `vmullb/t`, `vshllb/t`, `vmovnb/t`, `vqmovnb/t`, `vshrnb/t`. Helium's replacement for NEON's high/low-half long and narrow ops, which are compiled out on MVE today, so there is no portable widen-accumulate-narrow path for integer audio. A `Bottom()`/`Top()` API. | zip/unzip around the long/narrow ops |
| 8  | **Done** (`helium-build`). **Multiply-accumulate dot-product reductions:** `vmladavaq` (32-bit), `vmlaldavaq` (64-bit), `vrmlaldavhaq` (rounded high), and the exchange-pairs forms for complex dot products. FIR filters and convolution. | `vmlal` + pairwise add |
| 9  | **Done** (`helium-build`). **Circular-buffer indices:** `viwdupq`/`vdwdupq` produce wrapping incrementing/decrementing indices in one instruction, feeding gathers: delay lines and wavetables. | `Iota` + compare-and-subtract |
| 10 | **Done** (`helium-build`). **Across-vector min/max:** `ReduceMax`/`ReduceMin` via `vmaxvq`/`vminvq` (they use the shuffle fold on MVE today), plus `ReduceMaxAbs`/`ReduceMinAbs` (`vmaxavq`/`vminavq`, a peak meter in one instruction) and `MaxAbs`/`MinAbs` (`vmaxaq`/`vminaq`). | `vmaxv` on A64, fold on A32 |
| 11 | **Done** (`helium-build`). **Complex arithmetic:** `vcmulq`, `vcmlaq` (with rotations), `vcaddq`, `vhcaddq`. FFTs and IQ. | `vcmla`/`vcadd` from Armv8.3, shuffles below that |
| 12 | **Done** (`helium-build`). **Bit-reversed addressing:** `vbrsrq` for FFT reordering indices. | per-lane bit reverse |
| 13 | **Done** (`helium-build`). **Carry chains:** `vadcq`/`vsbcq` (add/subtract with carry across lanes) and `vshlcq` (whole-vector shift with carry). Bignum, crypto, bitstream packing. | scalar carry propagation |
| 14 | **Done** (`helium-build`), as `argon::PointerVector`. **Gather-base with write-back:** `vldrwq_gather_base_wb`, a vector of addresses that advances on each load. Strided streams and walking several buffers at once. | per-lane loads |

Out of scope: the Armv8.1-M 64-bit scalar shifts (`asrl`, `lsll`, `sqrshrl`); they help fixed-point code but are
scalar instructions.

## Known compiler issues

Clang 23 compiles every MVE intrinsic Argon uses. GCC 16.2 has three bugs around the write-back (`_wb`) intrinsics,
none reported upstream as of 2026-10-05; Argon works around all of them on every GCC version:

1. At `-O0`, a `_wb` dup intrinsic (`viwdupq_wb_u32` etc.) whose write-back pointer is not the address of a local
   fails with "unrecognizable insn". `CircularIndices` and the carry chains pass the address of a local.
2. A predicated `_x_wb` dup intrinsic whose result is discarded segfaults the compiler. Argon always uses results.
3. `vldrwq_gather_base_wb_*` / `vstrwq_scatter_base_wb_*` given a pointer parameter crash the compiler at every
   optimisation level (an internal error in `expand_insn`). GCC compiles the testcase of PR 124870, whose fix to
   these intrinsics' memory modelling was backported to 16.2, but not this form. `PointerVector` uses the
   write-back instructions with clang and a gather (or scatter) plus a `vadd` with GCC.

## Open questions

1. ~~**Breaking change on NEON.**~~ Resolved: comparisons return `Predicate` everywhere, with a deprecated implicit
   conversion to the mask vector.
2. ~~**Predicate granularity on MVE.**~~ Resolved: `Predicate<V>` is typed by `V`, and converts implicitly to the
   predicate of any vector type with the same lane count and width (an `int32` comparison can mask a `float` store).
   Other conversions, such as reusing an `int32` predicate for `uint8` lanes, don't compile.
3. **SVE.** This API is shaped to fit SVE's `svbool_t` later. Is SVE a goal, and if so, should the type be named and
   specified with that in mind now?
4. ~~**NEON tail API.**~~ Resolved: the tail is opt-in (`view.with_tail()`) and predicated on both platforms, so
   portable loops see the same vectors everywhere. MVE predicates every vector with `vctp` (which forms
   `dlstp`/`letp`); NEON uses whole-vector loads and stores except for the final partial vector.