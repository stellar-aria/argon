#!/usr/bin/env bash
# Fails if any function in the probe object moves a NEON lane or doubleword into a core register
# (vmov.32 rN, dM[k]; vmov.u16/s16/u8/s8 rN, dM[k]; vmov rN, rM, dK; vmov rN, sM), which stalls Cortex-A9 and A7.
# A loop's partial step must branch on its scalar lane count, not read the lanes of a predicate back. Every function
# is checked, not only the tail_* loops, so a helper the compiler kept out of line is checked too.
# usage: check_neon_tail.sh <objdump> <object>
set -euo pipefail
asm=$("$1" -d "$2")
transfer='\bvmov(\.(32|[us](8|16)))?\s+r[0-9]+,\s*(d[0-9]+\[[0-9]+\]|r[0-9]+,\s*d[0-9]+|s[0-9]+\b)'
if ! grep -qE '^[0-9a-f]+ <tail_[a-z0-9_]+>:' <<<"$asm"; then
  echo "no tail_* functions found"
  exit 1
fi
failed=0
while read -r f; do
  body=$(echo "$asm" | awk -v f="<$f>:" '$2 == f {on = 1; next} /^[0-9a-f]+ </ {on = 0} on')
  hits=$(echo "$body" | grep -cE "$transfer" || true)
  if [ "$hits" -eq 0 ]; then
    echo "ok   $f"
  else
    echo "FAIL $f: $hits NEON-to-core transfers"
    echo "$body" | grep -E "$transfer" | sed 's/^/     /'
    failed=1
  fi
done < <(echo "$asm" | sed -nE 's/^[0-9a-f]+ <([^>]+)>:$/\1/p' | sort -u)
exit $failed
