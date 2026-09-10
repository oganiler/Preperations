#!/usr/bin/env bash
# Decode the sealed answers. YOU run this, after you have attempted the problem.
# Usage: ./scripts/reveal.sh <day-dir> [--write]
set -euo pipefail
DIR="${1:?usage: reveal.sh <day-dir> [--write]}"
SEALED="${DIR}/.sealed/session.md.b64"
[[ -f "${SEALED}" ]] || { echo "no sealed file in ${DIR}" >&2; exit 1; }
if [[ "${2:-}" == "--write" ]]; then
  base64 -d "${SEALED}" > "${DIR}/SOLUTION.md"
  echo "written -> ${DIR}/SOLUTION.md"
else
  base64 -d "${SEALED}"
fi
