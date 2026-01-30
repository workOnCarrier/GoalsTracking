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


### notes on atomicity
https://learn.microsoft.com/en-gb/windows/win32/dxtecharts/lockless-programming?redirectedfrom=MSDN
If multiple thread read and write data, the theads reading may read intermediate values where write is torn.
The simplest way is to use locks/critical section to ensure reading and writing are exclusive.

Issues that can occur using locks / critical section
* priority inversion
* deadlocks

#### Windows: -- using critical section
```
// Initialize
CRITICAL_SECTION cs;
InitializeCriticalSection(&cs);

// Use
void ManipulateSharedData()
{
    EnterCriticalSection(&cs);
    // Manipulate stuff...
    LeaveCriticalSection(&cs);
}

// Destroy
DeleteCriticalSection(&cs);
```
#### Posix: -- mutex / semaphores
TBD

### Lockless programming
Family of techniques for safely manipulating shared data without using locks.
Challenges in lockless programming
* non-atomic operations
* operations reordering by compiler or processor

Assumptions
* Reads and Writes of naturally aligned native types are atomic. 
As long as the memory bus is at least as wide as the type being read / written, CPU reads / writes in single bus transaction. This makes them atomic.
* Types more than the bus size would need multiple instructions. The thread in middle of operating such data might be swapped with another thead and if that thread operates on same memory, there would be torn data.
* Using single instruction to read-modify-write (e.g. inc on x86/x64) would be atomic in single processor system, yet may be non-atmic in view of multi-processor systems, so requires lock prefix .

#### Gauranteeing Atmoicity
Achieved using below combinations
* Naturally atomic operations
* Locks to wrap composite operations
* Operating system functions that implement atomic versions of popular composite operations

e.g.
```
// This write is not atomic because it is not natively aligned.
DWORD* pData = (DWORD*)(pChar + 1);
*pData = 0;

// This is not atomic because it is three separate operations.
++g_globalCounter;

// This write is atomic.
g_alignedGlobal = 0;

// This read is atomic.
DWORD local = g_alignedGlobal;

//---------

// Incrementing our variable in a safe lockless way.
InterlockedIncrement(&g_globalCounter);
```


#### Reordering
reordering of writes can happen depending upon the address of L2 cache that is being written onto -- due to concept of store-gather buffer implementation. e.g. three variables are written - at 1) 0x1000, 2)0x2000, 3)0x1004. Store-gather clubbing may put 1,3 in one buffer and 2 in another buffer and the flushing of buffer ordering will store the data out of sequence with respect to the intended store sequence, potentially causing a torn write from another thread's perspective.

X86 and x64 CPU reordering reads ahead of writes is possible, if the locations are different.
write ahead of previos read is not done for x86 and x64.
This breaks Dekker's algo .. 
e.g. for the code
```
volatile bool f0 = false;
volatile bool f1 = false;
void P0Acquire(){
  // Indicates intention to enter critical region
  f0 = true;
  // check for other thread in or entering critical region
  while ( f1 ){
    // Handle contention
  }
  // critical region
  ...
  f0 = false;
}
void P1Acquire(){
  // Indicates intention to enter critical region
  f1 = true;
  // check for other thread in or entering critical region
  while (f0){
    // Handle contention
  }
  // critical region
  ...
  f1 = false;
}
```
For this code segment, P0Acquire can read before f0 write makes it to shared storage, while f0 in P1Acquire can read before f1 write make3s it to shared storage.... resulting in both threads entering the critical section.

For same locations being read and written to x86 and x64 do not reorder read across write, while PowerPc can do so.

## Read Acquire and Write Release barriers
_Read Acquire_: This is read of a flag / variable coupled with barrier against reordering ... indicating -- gaining ownership of a resource.
_Write Release_: This is a write of a flag / vairable coupled with a barrier against reordering.

### Preventing Compiler Reordering
* Windows
  * ReadWriteBarrier()
  * _ReadBarrier()
  * WriteBarrier()
* POSIX
  * TBD

### Preventing CPU Reordering
* Windows (x86, X64)
  * MemoryBarrier -- #include <Winnt.h> -- acts as a full barrier preventing all reordering of reads and writes across barrier.
* XBox / PowerPC
  * lwsync (__lwsync intrinsic #include <ppcintrinsics.h>) -- light weight sync 
  This only ensures writes before lwsync make it to L2 cache before any writes that follow. Also reads after lwsync don't get older data from L2. It does not prevent a read moving ahead of previous write.
  * sync -- this is full barrier that blocks reordering of read before write across sync

OS support on Windows
* Interlocked.... 
