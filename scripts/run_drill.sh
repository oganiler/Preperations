#!/usr/bin/env bash
# Build + run one day's drill with sanitizers, then static analysis.
# Usage: ./scripts/run_drill.sh <day-dir> [--release]
set -euo pipefail
DIR="${1:?usage: run_drill.sh <day-dir> [--release]}"
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CXX="${CXX:-g++}"
STD="-std=c++20"
WARN="-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion"
INC="-I${ROOT}/common -I${DIR}"
OUT="${DIR}/drill"

if [[ "${2:-}" == "--release" ]]; then
  MODE="-O2 -DNDEBUG"
  echo "== build (release, for timing) =="
else
  MODE="-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer"
  echo "== build (ASan + UBSan) =="
fi

# shellcheck disable=SC2086
"${CXX}" ${STD} ${MODE} ${WARN} ${INC} "${DIR}/solution.cpp" "${DIR}/tests.cpp" -o "${OUT}"
echo "== run =="
"${OUT}"

if command -v clang-tidy >/dev/null 2>&1; then
  echo "== clang-tidy (automotive-flavoured subset) =="
  clang-tidy "${DIR}/solution.cpp" -- ${STD} ${INC} || true
else
  echo "== clang-tidy not installed - skipping static analysis =="
  echo "   sudo apt-get install clang-tidy"
fi
