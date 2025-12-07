# Benchmark Harness

Drop-in harness to measure throughput/latency for each week’s deliverables. Default build uses `-O3 -march=native` and prints CSV-friendly rows.

## Usage
```
g++ -std=c++20 -O3 -march=native main.cpp -lpthread -o bench
./bench --test spsc --iterations 1000000
```

## TODO
- Wire Google Benchmark or custom timers per project.
- Capture metadata (CPU model, governor, core affinity) before each run.
- Commit raw outputs under `results/` in the respective week folders.
