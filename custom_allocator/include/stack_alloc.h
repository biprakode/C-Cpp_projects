#ifndef STACK_ALLOC_H
#define STACK_ALLOC_H

#include "allocator.h"

class StackAllocator : public Allocator{
protected:
    void *start = nullptr;
    size_t offset;

public:
    StackAllocator(const size_t total_size);
    ~StackAllocator();

    void Init(const size_t size) override;
    void *Alloc(const size_t size, const size_t alignment = alignof(std::max_align_t)) override;
    void DeAlloc(void *ptr) override;
    void Reset();

private:
    struct AllocationHead {
        size_t padding;
    };
};

#endif