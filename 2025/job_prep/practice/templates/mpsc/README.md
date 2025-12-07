# MPSC Queue Template

Baseline intrusive single-consumer queue for Week 2 experiments. Each producer owns its node; consumer pops without locking.

## Goals
- Avoid dynamic allocation inside hot path by recycling nodes or using object pools.
- Demonstrate ABA mitigation (tagged pointer, hazard pointer, or deferred reclamation).
- Provide instrumentation hooks for latency/throughput measurement.

## Suggested Tasks
1. Start from `mpsc_queue.cpp`, wiring push/pop and memory ordering.
2. Integrate with the benchmark harness to compare producer counts.
3. Document ABA strategy decisions inside `notes.md` or inline comments.
