#include "c_alloc.h"
#include <stdlib.h>

CAllocator::CAllocator() : Allocator(0) {}

void CAllocator::Init(const size_t size) {
    this->total_size = size;
}

void CAllocator::Reset() {}

void *CAllocator::Alloc(const size_t size, const size_t alignment) {
    used += size;
    peak = max(peak, used);
    return malloc(size);
}

void CAllocator::DeAlloc(void *ptr) {
    free(ptr);
}

CAllocator::~CAllocator() {}