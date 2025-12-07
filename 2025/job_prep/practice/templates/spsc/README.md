# SPSC Queue Template

Starter scaffold for the Week 1 project: bounded single-producer/single-consumer queue with no dynamic allocation and cache-aware layout.

## Goals
- Lock-free enqueue/dequeue with head/tail indices stored in separate cache lines.
- Configurable capacity at compile time.
- Hooks for plugging into the benchmark harness.

## Suggested Tasks
1. Fill in `spsc_queue.cpp` with your preferred implementation (ring buffer or double-buffered slots).
2. Add micro-benchmarks using `benchmark_harness/main.cpp` or custom scripts.
3. Record perf counters (`perf stat`, flamegraphs) and drop the notes under `week_01_atomcs_spsc`.

## Deliverables
- Final queue header/source
- Unit/micro tests
- Benchmark report comparing Boost.Lockfree/Folly SPSC
