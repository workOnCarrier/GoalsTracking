# Memory Ordering
https://preshing.com/20120515/memory-reordering-caught-in-the-act/

### learning points
* sem_wait
* asm volatile ("" ::: "memory") // to prevent compiler reordering
* sem_post
* MersenneTwister
* Benaphore
* Setting CPU affinity in code
  * cpu_set_t
  * CPU_ZERO /  CPU_SET
  * pthread_setaffinity_np(threadid, sizeof(cpu_set_t), cpuset_var)
* asm volatile("mfence" ::: "memory") // to prevent memory reordering
  * microsoft -- https://learn.microsoft.com/en-sg/windows/win32/api/winnt/nf-winnt-memorybarrier?redirectedfrom=MSDN

## C++ atomic types and operations
https://www.open-std.org/JTC1/sc22/wg21/docs/papers/2007/n2427.html

