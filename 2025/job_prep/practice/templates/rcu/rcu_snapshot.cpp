#include <atomic>
#include <memory>
#include <utility>

// Minimal RCU-style config wrapper for pointer-sized snapshots.
template <typename Snapshot>
class RcuSnapshot {
public:
    RcuSnapshot() = default;

    void publish(std::shared_ptr<Snapshot> next) {
        auto old = snapshot_.load(std::memory_order_acquire);
        snapshot_.store(next, std::memory_order_release);
        retire(old);
    }

    std::shared_ptr<const Snapshot> read() const {
        return snapshot_.load(std::memory_order_acquire);
    }

private:
    void retire(const std::shared_ptr<Snapshot> &old) {
        // Hook to integrate hazard pointers, epochs, or deferred deletion queues.
        retired_hand_off_(old);
    }

    std::atomic<std::shared_ptr<Snapshot>> snapshot_{nullptr};
    void (*retired_hand_off_)(std::shared_ptr<Snapshot>) = [](std::shared_ptr<Snapshot>) {};
};
