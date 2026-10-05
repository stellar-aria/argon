#!/usr/bin/env bash
# Fails if the probe object contains scalar VFP float arithmetic or comparisons (s-register f16/f32 ops, or
# vmrs APSR_nzcv), i.e. if GCC scalarised an Argon float operation instead of using Helium, or if an fma_*
# function has no fused multiply-accumulate (vfma / vfms / vfmas).
# usage: check_mve_float.sh <objdump> <object>
set -euo pipefail
asm=$("$1" -d "$2")
scalar_re='\bv(add|sub|mul|div|fma|fms|cmpe?|maxnm|minnm|sel[a-z]*)\.f(16|32)\s+s[0-9]+|\bvmrs\s+APSR_nzcv'
scalar=$(echo "$asm" | grep -cE "$scalar_re" || true)
echo "scalar VFP float ops: $scalar"
failed=0
if [ "$scalar" -ne 0 ]; then
  echo "$asm" | grep -nE "$scalar_re" | head
  failed=1
fi
functions=$(echo "$asm" | grep -oE '^[0-9a-f]+ <fma_[a-z0-9_]+>:' | grep -oE 'fma_[a-z0-9_]+' || true)
if [ -z "$functions" ]; then
  echo "no fma_* functions found"
  exit 1
fi
for f in $functions; do
  body=$(echo "$asm" | awk -v f="<$f>:" '$2 == f {on = 1; next} /^[0-9a-f]+ </ {on = 0} on')
  if echo "$body" | grep -qE '\bvfm(a|s|as)\.f(16|32)\s+q'; then
    echo "ok   $f"
  else
    echo "FAIL $f: no vfma/vfms"
    echo "$body" | sed 's/^/     /'
    failed=1
  fi
done
exit $failed
