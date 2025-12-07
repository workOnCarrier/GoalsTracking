# RCU Snapshot Template

Skeleton for the Week 3 RCU-style shared configuration demo. Readers perform plain loads with acquire semantics; writers publish new snapshots and retire old ones through hazard/epoch logic.

## Goals
- Demonstrate pointer publishing with release/acquire semantics.
- Provide a safe reclamation hook (hazard pointer, epoch GC, or manual quiescent state tracking).
- Show how to attach the snapshot to the mock trading pipeline.

## Suggested Tasks
1. Implement the reader/writer API in `rcu_snapshot.cpp`.
2. Add tests that spawn multiple reader threads to prove wait-free lookups.
3. Plug into the Week 4 pipeline as the shared config component.
