# Interview readiness — daily routine

Claude Code runs a 45–75 minute session per day. `CLAUDE.md` is the contract it reads
automatically on every session; `ROUTINE.md` is the original brief; `PROGRESS.md` is the
spaced-repetition ledger it must consult before choosing anything.

## Daily loop

```bash
claude                                   # in the repo root

> generate today's session               # Claude reads PROGRESS.md, scaffolds days/<date>_<slug>/
# read fact.md, answer the question out loud
# read problem.md, write solution.cpp    # 25-40 min, timer on

./scripts/run_drill.sh days/<date>_<slug>            # ASan + UBSan + tests
./scripts/run_drill.sh days/<date>_<slug> --release  # timing number

> review my solution                     # Claude interviews first, then reviews
./scripts/reveal.sh days/<date>_<slug>   # only after you have attempted everything
> update PROGRESS.md with today's result
```

## Why solutions are sealed

`days/*/.sealed/session.md.b64` is base64. That is not security — it stops accidental
spoilers from `cat`, from editor previews, from `grep -r`, and from Claude pulling the
answer into context while helping you. `CLAUDE.md` forbids it from decoding those files
unless you say `reveal`.

## Requirements

- g++ 11+ or clang 14+ (C++20: `std::span` is used)
- optional: `clang-tidy` for the static-analysis pass — `sudo apt-get install clang-tidy`
- no other dependencies; the test harness is a single header in `common/`

## Layout

```
CLAUDE.md              behavioural contract for Claude Code
ROUTINE.md             the standing session brief
PROGRESS.md            spaced-repetition ledger + coverage counters
scripts/               new_day.sh · run_drill.sh · seal.sh · reveal.sh
common/drill_test.hpp  dependency-free test harness
templates/day_template scaffold copied into each new day
days/<date>_<slug>/    fact.md · problem.md · problem.h · solution.cpp · tests.cpp
                       python_transfer.md · drill.md · .sealed/
```
