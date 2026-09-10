#!/usr/bin/env bash
# Scaffold a new training day. Usage: ./scripts/new_day.sh <topic-slug> [YYYY-MM-DD]
set -euo pipefail
SLUG="${1:?usage: new_day.sh <topic-slug> [date]}"
DATE="${2:-$(date +%F)}"
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DIR="${ROOT}/days/${DATE}_${SLUG}"
if [[ -d "${DIR}" ]]; then echo "exists: ${DIR}" >&2; exit 1; fi
mkdir -p "${DIR}/.sealed"
cp -r "${ROOT}/templates/day_template/." "${DIR}/"
echo "${DIR}"
