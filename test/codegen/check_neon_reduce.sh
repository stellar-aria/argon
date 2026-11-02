#!/usr/bin/env bash
# Fails if a reduce_* function in the probe object folds on q registers (vext, vdup or vrev of a q register), goes
# through memory (vst1/vld1/str/ldr) or makes a call, or has no pairwise d-register step (vpadd, vpmax, vpmin).
# usage: check_neon_reduce.sh <objdump> <object>
set -euo pipefail
asm=$("$1" -d "$2")
bad='\bv(ext|dup|rev(16|32|64))(\.[0-9a-z]+)*\s+q[0-9]+|\bv(st|ld)[1-4]\b|\b(str|ldr)[bhd]?\b|\bbl\b|\bblx\b'
pairwise='\bvp(add|max|min)(\.[0-9a-z]+)*\s+d[0-9]+'
if ! grep -qE '^[0-9a-f]+ <reduce_[a-z0-9_]+>:' <<<"$asm"; then
  echo "no reduce_* functions found"
  exit 1
fi
failed=0
while read -r f; do
  body=$(echo "$asm" | awk -v f="<$f>:" '$2 == f {on = 1; next} /^[0-9a-f]+ </ {on = 0} on')
  if echo "$body" | grep -qE "$bad"; then
    echo "FAIL $f: folds on q registers, through memory or by a call"
    echo "$body" | grep -E "$bad" | sed 's/^/     /'
    failed=1
  elif ! echo "$body" | grep -qE "$pairwise"; then
    echo "FAIL $f: no pairwise d-register step"
    echo "$body" | sed 's/^/     /'
    failed=1
  else
    echo "ok   $f"
  fi
done < <(echo "$asm" | sed -nE 's/^[0-9a-f]+ <(reduce_[a-z0-9_]+)>:$/\1/p' | sort -u)
exit $failed
