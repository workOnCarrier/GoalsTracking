# Week 3 — Lock-Free Algorithms & Memory Reclamation

Dedicate this space to Treiber stacks, hazard pointers, epoch GC, RCU, and seqlocks.

## Focus Areas
- Lock-free stack (Treiber) correctness and benchmarking
- Memory reclamation strategies: hazard pointers, epoch-based GC
- RCU-patterned readers plus seqlock implementations for read-mostly data

## Daily Checklist
- **Day 15:** Implement a Treiber stack with CAS push/pop.
- **Day 16:** Demonstrate failure due to premature delete; document the scenario.
- **Day 17:** Build a minimal single-thread hazard pointer manager.
- **Day 18:** Add epoch-based reclamation to the stack.
- **Day 19:** Prototype an RCU-style shared config (publish pointer, readers use acquire loads).
- **Day 20:** Implement seqlock read/write loops and measure read-mostly gains.
- **Day 21:** Weekly review—optimize one data structure, run benchmarks across 1/2/4/8 threads, document findings.

## Artifacts To Drop Here
- `stack/`, `hazptr/`, `epoch/`, `rcu/`, and `seqlock/` experiments.
- Memory reclamation design docs and timing tables.

## Definition of Done
- At least one stack version guarded by hazard pointers or epochs with proof of correctness notes.
- RCU demo wired into `templates/rcu` or referenced from here.
- Multi-thread benchmark results logged for every structure touched this week.
