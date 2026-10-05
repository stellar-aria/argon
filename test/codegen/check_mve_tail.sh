#!/usr/bin/env bash
# Fails unless every tail_* function in the probe object is a low-overhead tail-predicated loop: dlstp ... letp.
# usage: check_mve_tail.sh <objdump> <object>
set -euo pipefail
asm=$("$1" -d "$2")
functions=$(echo "$asm" | grep -oE '^[0-9a-f]+ <tail_[a-z0-9_]+>:' | grep -oE 'tail_[a-z0-9_]+' || true)
if [ -z "$functions" ]; then
  echo "no tail_* functions found"
  exit 1
fi
failed=0
for f in $functions; do
  body=$(echo "$asm" | awk -v f="<$f>:" '$2 == f {on = 1; next} /^[0-9a-f]+ </ {on = 0} on')
  if echo "$body" | grep -qE '\bdlstp\.' && echo "$body" | grep -qE '\bletp\b'; then
    echo "ok   $f"
  else
    echo "FAIL $f: no dlstp/letp loop"
    echo "$body" | sed 's/^/     /'
    failed=1
  fi
done
exit $failed
