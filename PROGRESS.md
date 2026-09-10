# PROGRESS.md — spaced-repetition ledger

Claude Code reads this **before** selecting anything. Difficulty ladder is driven by the
`Result` column: two consecutive `clean` results in a pattern family unlock `Hard`.

Result values: `clean` | `hints` | `failed` | `pending`
`Time (min)`: wall clock on Part 2 (the C++ challenge) only, not the whole session.
Articulation values: `fluent` | `halting` | `silent` — scale defined in any day's `notes.md` §7.
Correct code you cannot narrate is a `silent` row, not a `clean` one.
Category values: `leetcode` | `cpp-topic` | `cv` — see "Category coverage" below.

| Date | Cat | Concept (fact) | Algorithm pattern | C++ topic | Difficulty | Result | Time (min) | Articulation | Revisit +7 | Revisit +21 |
|------|-----|----------------|-------------------|-----------|------------|--------|------------|--------------|------------|-------------|
| 2026-09-11 | cv | Scaled dot-product attention: why 1/sqrt(d_k) | Union-find / graph connectivity | Ownership of caller-provided buffers, bounded scratch, explicit conversions | Medium | pending | — | — | 2026-09-18 | 2026-10-02 |

> A 2026-09-10 sliding-window session was generated and discarded unattempted at the
> candidate's request (stock LeetCode problem behind a radar framing). It was never
> attempted, so it earns no row and no revisit.

## Category coverage

Rotate across all three. `cv` is the preferred category when a problem can carry a real
algorithm *and* a real C++ design question at the same time — that combination is the target,
not a domain veneer over a stock problem.

| Category | What it is | Sessions | Last seen |
|----------|-----------|----------|-----------|
| `leetcode` | Pure algorithm/data-structure practice, no domain dressing | 0 | — |
| `cpp-topic` | Ownership, RAII, lifetime, move, templates, concurrency lead; algorithm secondary | 0 | — |
| `cv` | Perception/geometry problem where the domain drives the design | 1 | 2026-09-11 |

## Pattern coverage counters

| Family | Sessions | Last seen |
|--------|----------|-----------|
| arrays / two pointers | 0 | — |
| sliding window / monotonic | 0 | — |
| hash maps | 0 | — |
| binary search | 0 | — |
| stacks / queues | 0 | — |
| linked lists | 0 | — |
| trees | 0 | — |
| graphs / BFS / DFS | 0 | — |
| union-find / connectivity | 1 | 2026-09-11 |
| heaps | 0 | — |
| intervals | 0 | — |
| geometry / robust fitting | 0 | — |
| recursion / backtracking | 0 | — |
| dynamic programming | 0 | — |
| bit manipulation | 0 | — |

## C++ topic coverage

| Topic | Sessions | Last seen |
|-------|----------|-----------|
| STL / iterators | 0 | — |
| RAII | 0 | — |
| smart pointers | 0 | — |
| const correctness | 0 | — |
| move semantics | 0 | — |
| templates | 0 | — |
| object lifetime / ownership | 1 | 2026-09-11 |
| polymorphism | 0 | — |
| concurrency | 0 | — |
| performance / memory layout | 0 | — |
