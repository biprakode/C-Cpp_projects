#include "benchmark.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <random>
#include <cassert>

using namespace std;

void Benchmark::SingleAlloc(Allocator *allocator, const size_t size) {
    std::cout << "BENCHMARK: ALLOCATION" << '\n';
    std::cout << "\tSize:     \t" << size << '\n';
    cout << "\tOperations: \t" << n_oper << '\n';

    StartRound();

    for (auto oper = 0u; oper < n_oper; ++oper) {
        allocator->Alloc(size, 16); 
    }

    FinishRound();

    benchmark_result bench = buildResults(n_oper, std::move(time_elapsed), allocator->peak);
    PrintResults(bench);
}

void Benchmark::SingleDealloc(Allocator *allocator, const size_t size) {
    std::cout << "BENCHMARK: ALLOCATION" << '\n';
    std::cout << "\tSize:     \t" << size << '\n';
    cout << "\tOperations: \t" << n_oper << '\n';

    StartRound();
    vector<void*> addrs(n_oper);

    for (auto oper = 0u; oper < n_oper; ++oper) {
        addrs[oper] = allocator->Alloc(size, 16);
    }

    for (auto oper = n_oper; oper > 0; --oper) {
        allocator->DeAlloc(addrs[oper - 1]);
    }

    FinishRound();

    benchmark_result bench = buildResults(n_oper, std::move(time_elapsed), allocator->peak);
    PrintResults(bench);
}

void Benchmark::MultipleAlloc(Allocator *allocator, const vector<size_t> &sizes) {
    for (size_t i = 0; i < sizes.size(); ++i) {
        SingleAlloc(allocator, sizes[i]);
    }
}

void Benchmark::MultipleDealloc(Allocator *allocator, const vector<size_t> &sizes) {
    for (size_t i = 0; i < sizes.size(); ++i) {
        SingleDealloc(allocator, sizes[i]);
    }
}

void Benchmark::RandomAlloc(Allocator *allocator, const vector<size_t> &sizes) {
    std::cout << "BENCHMARK: RANDOM ALLOCATION" << '\n';
    std::cout << "\tSize range: \t" << sizes.size() << " different sizes" << '\n';
    std::cout << "\tOperations: \t" << n_oper << '\n';

    srand(static_cast<unsigned>(time(nullptr)));
    
    StartRound();

    for (size_t oper = 0; oper < n_oper; ++oper) {
        size_t random_idx = rand() % sizes.size();
        size_t random_size = sizes[random_idx];        
        allocator->Alloc(random_size, 16);
    }

    FinishRound();
    
    benchmark_result bench = buildResults(n_oper, std::move(time_elapsed), allocator->peak);
    PrintResults(bench);
}

void Benchmark::RandomDealloc(Allocator *allocator, const vector<size_t> &sizes) {
    std::cout << "BENCHMARK: RANDOM ALLOCATION" << '\n';
    std::cout << "\tSize range: \t" << sizes.size() << " different sizes" << '\n';
    std::cout << "\tOperations: \t" << n_oper << '\n';

    srand(static_cast<unsigned>(time(nullptr)));
    vector<void*> addrs(n_oper);
    
    StartRound();

    for (size_t oper = 0; oper < n_oper; ++oper) {
        size_t random_idx = rand() % sizes.size();
        size_t random_size = sizes[random_idx];
        addrs[oper] = allocator->Alloc(random_size, 16);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(addrs.begin(), addrs.end(), g);

    for (size_t oper = 0; oper < n_oper; ++oper) {
        allocator->DeAlloc(addrs[oper]);
    }
    
    FinishRound();
    
    benchmark_result bench = buildResults(n_oper, std::move(time_elapsed), allocator->peak);
    PrintResults(bench);
}


void Benchmark::PrintResults(const benchmark_result& results) const {
    std::cout << "\tRESULTS:" << '\n';
    std::cout << "\t\tOperations:    \t" << results.oper << '\n';
    std::cout << "\t\tTime elapsed: \t" << results.Microseconds.count() << " us" << '\n';
    std::cout << "\t\tOp per sec:    \t" << results.OperationsPerSec << " ops/us" << '\n';
    std::cout << "\t\tTimer per op:  \t" << results.TimePerOperation << " us/ops" << '\n';
    std::cout << "\t\tMemory peak:   \t" << results.mem_peak << " bytes" << '\n';
    std::cout << '\n';
}

const benchmark_result Benchmark::buildResults(size_t nOperations, chrono::microseconds&& elapsedTime, const size_t memoryPeak) const {
    benchmark_result results;
    results.oper = nOperations;
    results.Microseconds = std::move(elapsedTime);
    
    // Prevents division by zero
    double ms = static_cast<double>(results.Microseconds.count());
    if (ms > 0) {
        results.OperationsPerSec = results.oper / ms;
        results.TimePerOperation = ms / static_cast<double>(results.oper);
    } else {
        results.OperationsPerSec = 0;
        results.TimePerOperation = 0;
    }
    
    results.mem_peak = memoryPeak;
    return results;
}