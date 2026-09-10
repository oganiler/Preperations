#!/usr/bin/env bash
# Seal the answer document so it cannot be read by accident (or by Claude).
# Usage: ./scripts/seal.sh <day-dir> <answers.md>
set -euo pipefail
DIR="${1:?usage: seal.sh <day-dir> <answers.md>}"
SRC="${2:?usage: seal.sh <day-dir> <answers.md>}"
mkdir -p "${DIR}/.sealed"
base64 -w 0 "${SRC}" > "${DIR}/.sealed/session.md.b64"
shred -u "${SRC}" 2>/dev/null || rm -f "${SRC}"
echo "sealed -> ${DIR}/.sealed/session.md.b64"
