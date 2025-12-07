#include <atomic>
#include <array>
#include <cstddef>
#include <optional>

// Simple bounded SPSC ring buffer template.
template <typename T, std::size_t Capacity>
class SpscRing {
    static_assert((Capacity & (Capacity - 1)) == 0, "Capacity must be power of two for cheap masking");

public:
    bool enqueue(const T &value) {
        const auto head = head_.load(std::memory_order_relaxed);
        const auto next_head = (head + 1) & mask_;
        if (next_head == tail_.load(std::memory_order_acquire)) {
            return false; // queue full
        }

        buffer_[head] = value;
        head_.store(next_head, std::memory_order_release);
        return true;
    }

    std::optional<T> dequeue() {
        const auto tail = tail_.load(std::memory_order_relaxed);
        if (tail == head_.load(std::memory_order_acquire)) {
            return std::nullopt; // queue empty
        }

        T value = buffer_[tail];
        tail_.store((tail + 1) & mask_, std::memory_order_release);
        return value;
    }

private:
    alignas(64) std::atomic<std::size_t> head_{0};
    alignas(64) std::atomic<std::size_t> tail_{0};
    static constexpr std::size_t mask_ = Capacity - 1;
    std::array<T, Capacity> buffer_{};
};
