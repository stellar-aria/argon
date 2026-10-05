#!/usr/bin/env bash
# Fails if the probe object contains scalar VFP float arithmetic or comparisons (s-register f16/f32 ops, or
# vmrs APSR_nzcv) outside the reduce_* functions, i.e. if GCC scalarised an Argon float operation instead of using
# Helium; if an fma_* function has no fused multiply-accumulate (vfma / vfms / vfmas); or if a reduce_* function
# goes through the stack.
# usage: check_mve_float.sh <objdump> <object>
set -euo pipefail
asm=$("$1" -d "$2")
body_of() { echo "$asm" | awk -v f="<$1>:" '$2 == f {on = 1; next} /^[0-9a-f]+ </ {on = 0} on'; }
functions_named() { echo "$asm" | grep -oE "^[0-9a-f]+ <$1[a-z0-9_]*>:" | grep -oE "$1[a-z0-9_]*" || true; }
all=$(echo "$asm" | grep -oE '^[0-9a-f]+ <[a-z][a-z0-9_]*>:' | grep -oE '[a-z][a-z0-9_]*' || true)
scalar_re='\bv(add|sub|mul|div|fma|fms|cmpe?|maxnm|minnm|sel[a-z]*)\.f(16|32)\s+s[0-9]+|\bvmrs\s+APSR_nzcv'
failed=0
for kind in fma_ maxnum_ reduce_; do
  if [ -z "$(functions_named $kind)" ]; then
    echo "no ${kind}* functions found"
    exit 1
  fi
done
for f in $all; do
  case $f in reduce_*) continue ;; esac
  if body_of "$f" | grep -qE "$scalar_re"; then
    echo "FAIL $f: scalar VFP float ops"
    body_of "$f" | grep -E "$scalar_re" | sed 's/^/     /'
    failed=1
  fi
done
for f in $(functions_named fma_); do
  if body_of "$f" | grep -qE '\bvfm(a|s|as)\.f(16|32)\s+q'; then
    echo "ok   $f"
  else
    echo "FAIL $f: no vfma/vfms"
    body_of "$f" | sed 's/^/     /'
    failed=1
  fi
done
for f in $(functions_named maxnum_); do
  if body_of "$f" | grep -qE '\bv(max|min)nm\.f(16|32)\s+q'; then
    echo "ok   $f"
  else
    echo "FAIL $f: no vmaxnm/vminnm"
    body_of "$f" | sed 's/^/     /'
    failed=1
  fi
done
for f in $(functions_named reduce_); do
  if body_of "$f" | grep -qE '\[sp\b|\bsp, #'; then
    echo "FAIL $f: goes through the stack"
    body_of "$f" | sed 's/^/     /'
    failed=1
  else
    echo "ok   $f"
  fi
done
exit $failed
