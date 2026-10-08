#!/usr/bin/env bash
# Fails if the probe object calls, or holds an out-of-line copy of, any Argon function: a member of Argon or
# ArgonHalf, or anything in the argon, neon or mve namespaces. It also fails on any call to a standard library
# function, which inside Argon's loops is a helper such as std::min or std::array::operator[] that the library doesn't
# mark always-inline. The probe is compiled with -fno-inline-functions, under which clang emits and calls whatever
# isn't marked [[gnu::always_inline]]. The check is on mangled names, so a lambda that merely takes an Argon argument
# isn't flagged.
# usage: check_inline.sh <objdump> <object>
set -euo pipefail
asm=$("$1" -dr "$2")
argon='_ZN[KVRO]*(5Argon|9ArgonHalf|5argon|4neon|3mve)[^ >+]*'
std='_Z(N[KVRO]*)?St[^ >+]*'
if ! grep -qE '^[0-9a-f]+ <inline_[a-z0-9_]+>:' <<<"$asm"; then
  echo "no inline_* functions found"
  exit 1
fi
# call relocations (bl/blx on Arm, call on x86) and the out-of-line bodies themselves
call='R_(ARM_(CALL|JUMP24|THM_CALL|THM_JUMP24)|X86_64_(PLT32|PC32)|AARCH64_(CALL|JUMP)26)\s+'
calls=$(grep -E "$call$argon" <<<"$asm" || true)
std_calls=$(grep -E "$call$std" <<<"$asm" || true)
bodies=$(grep -E "^[0-9a-f]+ <$argon>:" <<<"$asm" || true)
echo "calls to Argon functions: $(grep -c . <<<"$calls" || true)," \
  "out-of-line Argon functions: $(grep -c . <<<"$bodies" || true)," \
  "calls to standard library functions: $(grep -c . <<<"$std_calls" || true)"
if [ -n "$calls$bodies$std_calls" ]; then
  { echo "$calls"; echo "$bodies"; echo "$std_calls"; } | grep -oE "$argon|$std" | sort | uniq -c | sort -rn |
    while read -r n sym; do echo "  $n x $(c++filt "$sym" 2>/dev/null || echo "$sym")"; done
  exit 1
fi
