# PROGRESS.md — spaced-repetition ledger

Claude Code reads this **before** selecting anything. Difficulty ladder is driven by the
`Result` column: two consecutive `clean` results in a pattern family unlock `Hard`.

Result values: `clean` | `hints` | `failed` | `pending`

| Date | Concept (fact) | Algorithm pattern | C++ topic | Difficulty | Result | Revisit +7 | Revisit +21 |
|------|----------------|-------------------|-----------|------------|--------|------------|-------------|
| 2026-09-10 | Scaled dot-product attention: why 1/sqrt(d_k) | Sliding window / monotonic deque | Fixed-capacity ring buffer, no heap in loop, `std::span` | Medium | pending | 2026-09-17 | 2026-10-01 |

## Pattern coverage counters

| Family | Sessions | Last seen |
|--------|----------|-----------|
| arrays / two pointers | 0 | — |
| sliding window / monotonic | 1 | 2026-09-10 |
| hash maps | 0 | — |
| binary search | 0 | — |
| stacks / queues | 0 | — |
| linked lists | 0 | — |
| trees | 0 | — |
| graphs / BFS / DFS | 0 | — |
| heaps | 0 | — |
| intervals | 0 | — |
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
| object lifetime / ownership | 1 | 2026-09-10 |
| polymorphism | 0 | — |
| concurrency | 0 | — |
| performance / memory layout | 1 | 2026-09-10 |
