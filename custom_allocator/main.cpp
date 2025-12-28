#include <iostream>
#include <cstddef>
#include <vector>
using namespace std;


#include "benchmark.h"
#include "allocator.h"
#include "stack_alloc.h"

#define NUM_OPERATIONS 1e4

int main() {
    const std::size_t A = static_cast<std::size_t>(1e9);
    const std::size_t B = static_cast<std::size_t>(1e8);

    const std::vector<std::size_t> ALLOCATION_SIZES {32, 64, 256, 512, 1024, 2048, 4096};

    Allocator * stackAllocator = new StackAllocator(A);
    Benchmark benchmark(NUM_OPERATIONS);

    std::cout << "STACK" << std::endl;
    benchmark.MultipleAlloc(stackAllocator, ALLOCATION_SIZES);
    benchmark.MultipleDealloc(stackAllocator, ALLOCATION_SIZES);
    benchmark.RandomAlloc(stackAllocator, ALLOCATION_SIZES);
    benchmark.RandomDealloc(stackAllocator, ALLOCATION_SIZES);

    delete stackAllocator;
}