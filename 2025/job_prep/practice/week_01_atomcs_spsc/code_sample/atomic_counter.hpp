#ifndef CODE_SAMPLE_ATOMIC_COUNTER_HPP
#define CODE_SAMPLE_ATOMIC_COUNTER_HPP

#include <atomic>
#include <cstdint>

class AtomicCounter {
public:
    using value_type = std::int64_t;

    explicit AtomicCounter(value_type initial = 0) noexcept : value_(initial) {}

    bool is_lock_free() const noexcept { return value_.is_lock_free(); }

    value_type increment(std::memory_order order = std::memory_order_relaxed) noexcept {
        return value_.fetch_add(1, order) + 1;
    }

    value_type decrement(std::memory_order order = std::memory_order_relaxed) noexcept {
        return value_.fetch_sub(1, order) - 1;
    }

    value_type add(value_type delta, std::memory_order order = std::memory_order_relaxed) noexcept {
        return value_.fetch_add(delta, order) + delta;
    }

    value_type subtract(value_type delta, std::memory_order order = std::memory_order_relaxed) noexcept {
        return value_.fetch_sub(delta, order) - delta;
    }

    value_type get(std::memory_order order = std::memory_order_seq_cst) const noexcept {
        return value_.load(order);
    }

    void reset(value_type desired = 0, std::memory_order order = std::memory_order_seq_cst) noexcept {
        value_.store(desired, order);
    }

private:
    std::atomic<value_type> value_;
};

#endif // CODE_SAMPLE_ATOMIC_COUNTER_HPP
