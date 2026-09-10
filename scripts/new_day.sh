#!/usr/bin/env bash
# Scaffold a new training day.
# Usage: ./scripts/new_day.sh <category> <topic-slug> [YYYY-MM-DD]
#   category: leetcode | cpp-topic | cv
set -euo pipefail
CAT="${1:?usage: new_day.sh <category> <topic-slug> [date]   category: leetcode|cpp-topic|cv}"
SLUG="${2:?usage: new_day.sh <category> <topic-slug> [date]}"
DATE="${3:-$(date +%F)}"
case "${CAT}" in
  leetcode|cpp-topic|cv) ;;
  *) echo "unknown category '${CAT}' (expected: leetcode | cpp-topic | cv)" >&2; exit 1 ;;
esac
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DIR="${ROOT}/days/${CAT}/${DATE}_${SLUG}"
if [[ -d "${DIR}" ]]; then echo "exists: ${DIR}" >&2; exit 1; fi
mkdir -p "${DIR}/.sealed"
cp -r "${ROOT}/templates/day_template/." "${DIR}/"
echo "${DIR}"
