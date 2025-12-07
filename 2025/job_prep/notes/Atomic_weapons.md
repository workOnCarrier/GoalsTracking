# Daily 30-minute “micro drills” to master atomics & orderings
### 📘 **Herb Sutter – Atomic Weapons (3-part series)**

code snippet
```
for ( auto i = 0; i < rows; ++i)
  for ( auto j = 0; j < cols; ++j)
      a[j*rows + i] += 42
```
can be transformed into more optimised version by the compiler
```
for ( auto j = 0; j < cols; ++j)
  for ( auto i = 0; i < rows; ++i)
      a[j*rows + i] += 42
```
argue why?


