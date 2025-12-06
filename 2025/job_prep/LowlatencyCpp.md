# 1. Core ideas
* std::atomic<T> for integral types and pointers
* memory_order -- relaxed, acquire, release, acq_rel, seq_cst
* Happens-before, data races, tearing
* Atomic RMW: fetch_add, compare_exchange_strong / weak
* fences: atomic_thread_fence
* Explain when memory_order_relaxed is safe ( e.g. counters, stats)

# 2. Lock-Free / wait free data structures
You’re not expected to re-derive Michael–Scott queues on a whiteboard, but you are expected to understand:
## Must know structures
* SPSC ring buffer (bounded queue)
* SPMC / MPSC / MPMC  queues at a conceptual level
* Intrusive single-producer lists / freelists
## Key algorithms / patterns
* Lock-free stack using std::atmic<Node*> + compare_exchange
* ABA problem, tag bits / version counters
* Backoff strategies: spin, yield, sleep, hybrid
## Typical interview tasks
* Implement an SPSC ring buffer using atomics and indices (no locks)
* Explain how you'd extend to MPMC and where it gets tricky
* Given a naive lock-free tack, identify ABA and outline fixes

# 3. Memory Reclamation Techniques
## Low-latency C++ jobs care that you know you can’t just delete nodes whenever:
* Hazard pointers (high-level idea, not full code)
* Epoch-based reclamation / QSBR
* Why shared_ptr is often too slow, and why we may want custom pools/arenas.
## Typical questions
* “In a lock-free stack, how do you know when it’s safe to free a node?”
* “What’s the cost of shared_ptr in a hot path? How would you avoid it?”

# 4. Threading Models and Work Distribution
You should be able to reason about how work flows between threads.
## Core patterns
* Thread pools (fixed size, work stealing vs work sharing)
* Single-threaded hot path + background threads (I/O, logging, persistence)
* Pipelines: stages connected by queues (producer → matcher → risk → logger)
* Affinity & pinning: binding threads to cores, isolating noisy neighbors
* NUMA basics: locality, avoiding cross-socket chatter
## Typical interview tasks
* Design a thread pool: task submission interface, worker loop, shutdown.
* Design a low-latency pipeline for order processing across threads.
* How do you minimize context switches and cache misses in such a design?

# 5. Synchronization Primitives & Their Costs
## Know both how to use and when not to use:
* Mutexes: std::mutex, std::recursive_mutex, std::shared_mutex
* Condition variables vs busy-wait/spin loops
* Reader–writer locks: when readers dominate, when they hurt
* Barriers/latches (std::barrier, std::latch) – for phased work
## Key points
* Why coarse-grained locks kill latency (lock convoying, priority inversion)
* When a spinlock can be better than a mutex (short critical sections on isolated cores)
* Why contention patterns matter more than theoretical complexity
## Typical questions
* “You have a shared map updated frequently; how would you protect it?”
* “When would you choose a spinlock vs std::mutex on Linux?”

# 6. Lock-Free / Low-Contention Algorithms & Patterns
## These are the “fancy” but highly relevant patterns:
* Read-Copy-Update (RCU) style patterns:
  * Readers run without locks, see snapshots
  * Writers build new version then publish via atomic pointer swap
* Seqlocks:
  * Writers take sequence and update; readers retry on mismatch
* Double-buffering (copy-on-write, generation swapping)
* Per-thread data + aggregation (sharded counters / histograms)
## Typical interview discussions
* “You have a config / risk limit object read on every order and updated occasionally. How do you design it for near-zero reader latency?”
* “How would you implement a global counter with millions of increments/sec and minimal contention?”

# 7. C++ Standard Library Concurrency Toolbox
## You don’t have to worship it, but you must know it:
* std::thread, std::jthread (cooperative stop)
* std::future, std::promise, std::async (and why they’re often too heavy for low-latency paths)
* std::condition_variable vs condition_variable_any
* std::atomic specialization for integral, pointer, std::atomic_flag
## Typical questions
* “Show a simple example launching N threads and joining them.”
* “Why might std::async be a poor choice in a low-latency trading engine?”

# 8. False Sharing, Cache Lines & Contention
## Classic low-latency interview land:
* What is false sharing and how to avoid it:
  * cache-line alignment (alignas(64))
  * padding struct fields
* Cache line states (MESI idea-level, not all details)
* Impact of cache misses on tail latency
## Typical questions
* Given a struct with counters updated by different threads, fix it to avoid false sharing.
* Explain how contended atomics degrade throughput and increase latency.

# 9. Timers, Busy-Wait, and Latency vs CPU Trade-offs
* High-resolution clocks: steady_clock, high_resolution_clock (and their pitfalls)
* Busy-wait loops vs sleep_for / condition_variable:
  * When you’re OK burning CPU to cut latency
* Token bucket / leaky bucket rate limiters (often coded in interviews)
* Handling timeouts in lock-free algorithms or queues.

# 10. Practical “Implement This” Problems to Practice
If you can comfortably implement / reason about these in C++17/20 with atomics, you’re in a strong position:
* SPSC ring buffer queue with std::atomic<size_t> head/tail.
* MPSC queue using atomic linked list or a ring buffer with CAS.
* Lock-free stack with std::atomic<Node*> and compare_exchange_weak.
* Thread pool with:
  * Task queue
  * Worker threads
  * Graceful shutdown
* Rate limiter (token bucket) using atomics + time.
* RCU-style shared config:
  * Readers: load atomic pointer and use snapshot
  * Writer: builds new copy and swaps pointer
* Shared stats/counters design with:
  * per-thread counters
  * aggregation without stopping all threads

# How to Turn This into a Study Plan (Concrete)
If I were you, I’d do:
* Week 1–2: Atomics + SPSC/MPSC queues
  * Re-implement ring buffer SPSC: benchmark, play with memory orders.
* Week 3: Thread pools + pipelines
  * Write a small “order pipeline” simulation with 3 stages using threads & queues.
* Week 4: Lock-free stack + reclamation
  * Implement a simple lock-free stack and at least reason about reclamation (even if you don’t code hazard pointers fully).
* Across all weeks:
  * Solve interview-style problems where the twist is “make it low-contention / low-latency”:
    * counters, maps, rate limiters, logging, config updates, etc.

