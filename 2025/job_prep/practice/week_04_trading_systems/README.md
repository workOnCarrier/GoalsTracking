# Week 4 — Trading-System Problem Types & Integrations

Use this folder to stitch the primitives into trading-style pipelines and interview-ready demos.

## Focus Areas
- Latency budgeting and micro-profiling (`steady_clock`, TSC helpers)
- Multi-stage SPSC pipelines (ingest → process → log/risk/match/persist)
- Contended counter designs, snapshot caches, log-free logging, final mock interviews

## Daily Checklist
- **Day 22:** Build a micro-latency profiler and record baseline measurements.
- **Day 23:** Implement a 3-stage pipeline with SPSC queues between stages.
- **Day 24:** Prototype per-thread counters plus aggregation step.
- **Day 25:** Create a lock-free token bucket rate limiter.
- **Day 26:** Implement double-buffered snapshot cache.
- **Day 27:** Design a log-free logging ring buffer.
- **Day 28:** Full mock interview week—time-box questions, benchmark all lock-free structures, produce a portfolio README.

## Artifacts To Drop Here
- Pipeline diagrams, profiling scripts, and rate limiter implementations.
- Final presentation/portfolio materials.

## Definition of Done
- Pipeline demo runs end-to-end with metrics from the benchmark harness.
- Each interview question has at least one recorded dry-run.
- Portfolio README links to the strongest artifacts generated over the month.
