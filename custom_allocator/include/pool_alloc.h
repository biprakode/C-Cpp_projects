#ifndef POOL_ALLOCATOR
#define POOL_ALLOCATOR

#include "allocator.h"
#include "stack_linked_list.h"

class PoolAllocator : public Allocator {
private:
    struct  FreeHead{};
    using Node = Stack_Linked_List<FreeHead>::Node;
    Stack_Linked_List<FreeHead> free_list;
    void *start_ptr = nullptr;
    size_t chunk_size;

public:
    PoolAllocator(const size_t total_size , const size_t chunk);
    virtual ~PoolAllocator() noexcept override = default;

    void Init(const size_t size) override;
    void *Alloc(const size_t size , const size_t alignment) override;
    void DeAlloc(void *ptr) override;
    void Reset() override;
};

#endif