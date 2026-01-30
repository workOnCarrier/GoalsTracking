#include "atomic_counter.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

namespace {

void expect_equal(std::int64_t expected, std::int64_t actual, const char* label) {
    if (expected != actual) {
        std::cerr << "[FAIL] " << label << ": expected " << expected << ", got " << actual << '\n';
        std::exit(EXIT_FAILURE);
    }
}

void test_increment_load() {
    AtomicCounter counter;
    const std::size_t threads = 8;
    const std::size_t iterations = 50'000;

    std::vector<std::thread> workers;
    workers.reserve(threads);

    for (std::size_t i = 0; i < threads; ++i) {
        workers.emplace_back([&counter]() {
            for (std::size_t j = 0; j < iterations; ++j) {
                counter.increment();
            }
        });
    }

    for (auto& worker : workers) {
        worker.join();
    }

    expect_equal(static_cast<std::int64_t>(threads * iterations), counter.get(), "increment saturation");
}

void test_add_subtract_balance() {
    AtomicCounter counter;
    const std::size_t threads = 4;
    const std::size_t iterations = 10'000;

    std::vector<std::thread> workers;
    workers.reserve(threads * 2);

    for (std::size_t i = 0; i < threads; ++i) {
        workers.emplace_back([&counter]() {
            for (std::size_t j = 0; j < iterations; ++j) {
                counter.add(3);
                counter.subtract(2);
            }
        });
        workers.emplace_back([&counter]() {
            for (std::size_t j = 0; j < iterations; ++j) {
                counter.add(5);
                counter.subtract(5);
            }
        });
    }

    for (auto& worker : workers) {
        worker.join();
    }

    expect_equal(static_cast<std::int64_t>(threads * iterations), counter.get(), "add/subtract balance");
}

void test_reset_and_lock_free() {
    AtomicCounter counter(123);
    expect_equal(123, counter.get(), "initial value");
    counter.reset(-10);
    expect_equal(-10, counter.get(), "reset value");

    if (!counter.is_lock_free()) {
        std::cerr << "[WARN] AtomicCounter is not lock-free on this platform." << '\n';
    }
}

}

int main() {
    auto start = std::chrono::steady_clock::now();

    test_increment_load();
    test_add_subtract_balance();
    test_reset_and_lock_free();

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "All AtomicCounter tests passed in " << elapsed_ms << " ms" << std::endl;
    return 0;
}
