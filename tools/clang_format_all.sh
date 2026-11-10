#!/usr/bin/env bash
set -euo pipefail

root_dir="${1:-.}"
cd "$root_dir"

extensions_regex='.*\.(h|t|cc|cpp|hpp|tpp)$'

listFiles() {
    if git rev-parse --is-inside-work-tree &>/dev/null; then
        git ls-files -z --cached --others --exclude-standard
    else
        find . -type f -print0
    fi
}

listFiles \
    | { grep -zE "$extensions_regex" || true; } \
    | while IFS= read -r -d '' file_path; do
          [[ -f "$file_path" ]] && printf '%s\0' "$file_path"
      done \
    | xargs -0 -r -P "$(nproc)" -n 16 clang-format -i --style=file --fallback-style=none