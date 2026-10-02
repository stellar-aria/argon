#!/usr/bin/env bash
# Fails if the probe object contains scalar VFP float arithmetic/comparisons (s-register f32 ops or vmrs),
# i.e. if GCC scalarised an Argon<float> operation instead of using NEON.
# usage: check_neon_float.sh <objdump> <object>
set -euo pipefail
asm=$("$1" -d "$2")
scalar=$(echo "$asm" | grep -cE '\bv(add|sub|mul|mla|mls|cmpe?|div)\.f32\s+s[0-9]+|\bvmrs\b' || true)
vector=$(echo "$asm" | grep -cE '\bv(add|sub|mul|mla|mls|cg[te]|clt|cle|bsl|bit|bif)(\.f32|\.i32)?\s+q[0-9]+' || true)
echo "NEON vector ops: $vector, scalar VFP float ops: $scalar"
if [ "$scalar" -ne 0 ]; then
  echo "$asm" | grep -nE '\bv(add|sub|mul|mla|mls|cmpe?|div)\.f32\s+s[0-9]+|\bvmrs\b' | head
  exit 1
fi
