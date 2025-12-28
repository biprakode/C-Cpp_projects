#include "c_alloc.h"
#include <stdlib.h>

void CAllocator::Init(const size_t size) {}
void CAllocator::Reset() {}

void *CAllocator::Alloc(const size_t size, const size_t alignment = 0) {
    return malloc(size);
}

void CAllocator::DeAlloc(void *ptr) {
    free(ptr);
}