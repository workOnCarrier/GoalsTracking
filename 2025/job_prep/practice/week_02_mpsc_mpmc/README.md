# Week 2 — MPSC/MPMC, Threading Models & Affinity

This week extends the queue work into multi-producer scenarios and explores scheduling/NUMA concerns.

## Focus Areas
- CAS loops, ABA mitigation via tagged pointers or hazard pointers
- Intrusive MPSC queue patterns and basic thread pools
- NUMA-awareness, thread pinning, and benchmarking false sharing fixes at scale

## Daily Checklist
- **Day 8:** Review strong vs weak CAS semantics, implement a spinlock using CAS.
- **Day 9:** Study the ABA problem, prototype a tagged pointer or hazard-pointer fix.
- **Day 10:** Implement an intrusive linked-list MPSC queue (multiple producers, single consumer).
- **Day 11:** Compare work stealing vs sharing vs single-hot-path threading models, build a baseline thread pool.
- **Day 12:** Extend the thread pool with cooperative cancellation informed by Taskflow internals.
- **Day 13:** Explore NUMA impacts, experiment with `taskset`/`sched_setaffinity`, record latency deltas.
- **Day 14:** Weekly review—build an MPMC ring buffer using CAS, resolve false sharing, benchmark vs Boost.Lockfree.

## Artifacts To Drop Here
- `mpsc/` and `mpmc/` prototypes prior to promoting them into `templates`.
- Thread pool experiments and affinity scripts.
- Benchmark logs comparing pinned vs non-pinned runs.

## Definition of Done
- Callable MPSC + MPMC queue implementations with reproducible tests.
- Evidence of ABA mitigation (write-up or code comment referencing approach).
- Thread pool supports graceful cancellation and captures NUMA learnings.
