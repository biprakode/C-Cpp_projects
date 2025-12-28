#ifndef C_ALLOCATOR
#define C_ALLOCATOR

#include "allocator.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


class CAllocator : public Allocator {
public:
    CAllocator();
    ~CAllocator();

    void Init(const size_t size) override;
    void *Alloc(const size_t size, const size_t alignment = 0) override;
    void DeAlloc(void *ptr) override;
    void Reset();
};

#endif