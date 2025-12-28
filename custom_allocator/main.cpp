#include <iostream>
#include <cstddef>
#include <vector>
using namespace std;

#define POOL_TOTAL 536870912

#include "benchmark.h"
#include "allocator.h"
#include "stack_alloc.h"
#include "pool_alloc.h"
#include "c_alloc.h"

#define NUM_OPERATIONS 1e4

int main() {
    const std::size_t A = static_cast<std::size_t>(1e9);
    const std::size_t B = static_cast<std::size_t>(1e8);

    const std::vector<std::size_t> ALLOCATION_SIZES {32, 64, 256, 512, 1024, 2048, 4096};

    Allocator *stackAllocator = new StackAllocator(A);
    Allocator *poolAllocator = new PoolAllocator(POOL_TOTAL, (size_t)4096);
    Allocator *cAllocator = new CAllocator();
    Benchmark benchmark(NUM_OPERATIONS);

    st::cout << "C" << std::endl;
    benchmark.MultipleAlloc(cAllocator, ALLOCATION_SIZES);
    benchmark.MultipleDealloc(cAllocator, ALLOCATION_SIZES);
    benchmark.RandomAlloc(cAllocator, ALLOCATION_SIZES);
    benchmark.RandomDealloc(cAllocator, ALLOCATION_SIZES);

    std::cout << "STACK" << std::endl;
    benchmark.MultipleAlloc(stackAllocator, ALLOCATION_SIZES);
    benchmark.MultipleDealloc(stackAllocator, ALLOCATION_SIZES);
    benchmark.RandomAlloc(stackAllocator, ALLOCATION_SIZES);
    benchmark.RandomDealloc(stackAllocator, ALLOCATION_SIZES);

    std::cout << "POOL" << std::endl;
    poolAllocator->Init(POOL_TOTAL);
    benchmark.MultipleAlloc(poolAllocator, ALLOCATION_SIZES);
    benchmark.MultipleDealloc(poolAllocator, ALLOCATION_SIZES);
    benchmark.RandomAlloc(poolAllocator, ALLOCATION_SIZES);
    benchmark.RandomDealloc(poolAllocator, ALLOCATION_SIZES);

    delete stackAllocator;
    delete poolAllocator;
}