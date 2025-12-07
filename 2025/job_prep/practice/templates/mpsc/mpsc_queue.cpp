#include <atomic>
#include <cstddef>
#include <memory>

struct alignas(64) MpscNode {
    std::atomic<MpscNode *> next{nullptr};
    // payload fields go here
};

class MpscQueue {
public:
    MpscQueue() {
        dummy_.next.store(nullptr, std::memory_order_relaxed);
        head_.store(&dummy_, std::memory_order_relaxed);
        tail_ = &dummy_;
    }

    void push(MpscNode *node) {
        node->next.store(nullptr, std::memory_order_relaxed);
        auto prev = head_.exchange(node, std::memory_order_acq_rel);
        prev->next.store(node, std::memory_order_release);
    }

    MpscNode *pop() {
        auto next = tail_->next.load(std::memory_order_acquire);
        if (!next) {
            return nullptr; // queue empty
        }
        tail_ = next;
        return next;
    }

private:
    std::atomic<MpscNode *> head_;
    MpscNode *tail_;
    MpscNode dummy_{};
};
