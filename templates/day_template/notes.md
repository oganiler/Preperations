# Notes — <date> · <pattern>

Your file. Claude scaffolds it, never writes into it, and reads it only when you ask.
Fill it top to bottom, in order. Do not skip ahead to §6.

## 1. Fact — my answer, before revealing

Said out loud, under 2 minutes. Write what you actually said, not what you wish you had said.

-

## 2. Approach — written before the first line of the implementation

- Data structure:
- Invariant (what must hold at the top of every iteration):
- Time, and why:
- Auxiliary space, and why:
- Where the allocations happen:

## 3. Prediction — before the first build

Build only after this section is filled in. You get no sanitizer in a live round.

- Cases I expect to fail:
- Boundaries I am unsure about (`k == 1`, `k == n`, all-equal, negatives, overflow):
- Sanitizer findings I expect:

Actual, after `run_drill.sh`:

## 4. Python transfer — my answers

1.
2.
3.

## 5. Drill — my answers, 60 s each, no notes

1.
2.
3.

## 6. After the reveal — the delta

The point of the whole session is this section. Be specific: "revise attention" is not a note.

**Wrong — did not know it:**

**Knew it, could not say it in 60 seconds:**
(a different failure with a different fix — this one needs rehearsal, not reading)

**Vocabulary or naming I lacked:**

**What I would say differently in a live round:**

## 7. Self-assessment

- **Time on Part 2** (wall clock, minutes):
- **Articulation** — `fluent` | `halting` | `silent`
  - `fluent` — narrated approach and complexity with no backtracking; would pass a live round
  - `halting` — got there, but with restarts, dead ends, or re-deriving out loud
  - `silent` — code correct, could not explain the invariant or the complexity when asked
- **Result** — `clean` | `hints` | `failed`
  - `clean` — correct on the first sanitizer run, met the complexity **and** the allocation
    budget, needed none of Claude's questions, and could narrate it. All five.
  - `hints` — one of Claude's questions exposed the bug, or the harness caught something I
    had not predicted, or I read part of the hint ladder.
  - `failed` — missed the required complexity, ran out of time, or opened the reference
    solution.

Then tell Claude: `update PROGRESS.md, result: <x>, time: <n>, articulation: <y>`
