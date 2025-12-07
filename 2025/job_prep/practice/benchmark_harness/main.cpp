#include <chrono>
#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace {
using clock = std::chrono::steady_clock;

struct RunConfig {
    std::string test_name{"spsc"};
    std::size_t iterations{1'000'000};
};

RunConfig parse_args(int argc, char **argv) {
    RunConfig cfg;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--test") == 0 && i + 1 < argc) {
            cfg.test_name = argv[++i];
        } else if (std::strcmp(argv[i], "--iterations") == 0 && i + 1 < argc) {
            cfg.iterations = std::stoull(argv[++i]);
        }
    }
    return cfg;
}

void run_spsc(std::size_t iterations) {
    // TODO: plug in templates/spsc implementation.
    auto start = clock::now();
    for (std::size_t i = 0; i < iterations; ++i) {
        // enqueue/dequeue demo
    }
    auto end = clock::now();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "test=spsc,iterations=" << iterations << ",ns=" << nanos << "\n";
}

} // namespace

int main(int argc, char **argv) {
    const auto cfg = parse_args(argc, argv);

    if (cfg.test_name == "spsc") {
        run_spsc(cfg.iterations);
    } else {
        std::cerr << "Unknown test: " << cfg.test_name << "\n";
        return 1;
    }

    return 0;
}
