# Week 1 — Atomics, Memory Model & SPSC

Use this folder to implement and track every deliverable from Week 1 of `4_week_study_plan.md`.

## Focus Areas
- `std::atomic` fundamentals, memory orders, fences
- False sharing mitigation and padding strategies
- Bounded SPSC ring buffer design + benchmarks

## Daily Checklist
- **Day 1:** Read Preshing on atomic vs non-atomic ops, watch Herb Sutter “Atomic Weapons” Pt. 1, summarize data race definition.
- **Day 2:** Study compile-time memory ordering, practice configuring `memory_order` on an atomic counter implementation.
- **Day 3:** Deep dive on acquire/release semantics, write a failing example without atomics, then fix it.
- **Day 4:** Research false sharing and apply `alignas(64)` padding to a shared counter prototype.
- **Day 5:** Design and implement a bounded SPSC queue (no dynamic allocation, cache friendly layout).
- **Day 6:** Benchmark your SPSC queue vs Boost.Lockfree and Folly’s `ProducerConsumerQueue`; capture perf tooling commands.
- **Day 7:** Run a weekly review (quiz yourself on the memory model, rebuild SPSC from scratch, study Disruptor fundamentals).

## Artifacts To Drop Here
- `notes/` with reading summaries or diagrams.
- `spsc/` experiments that eventually promote into `templates/spsc` or `benchmark_harness`.
- Benchmark results (`*.md` or `*.csv`).

## Definition of Done
- SPSC queue compiles, passes micro tests, and has at least one benchmark run recorded.
- False sharing mitigation demo committed with before/after measurements.
- Weekly retrospective doc created (`retrospective.md`).
