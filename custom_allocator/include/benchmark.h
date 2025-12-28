#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <vector>
#include <string>
#include <functional>
#include "allocator.h"
using namespace std;

#define OPERATIONS (n_oper)

struct benchmark_result {
    double OperationsPerSec;    // Throughput
    double TimePerOperation;
    chrono::microseconds Microseconds;
    size_t oper;
    size_t mem_peak;
};

class Benchmark {
private:
    size_t n_oper;
    chrono::time_point<chrono::high_resolution_clock> Start;
    chrono::time_point<chrono::high_resolution_clock> Finish;
    chrono::microseconds time_elapsed;

    void PrintResults(const benchmark_result& results) const;
    const benchmark_result buildResults(size_t nOperations, chrono::microseconds&& ellapsedTime, const size_t memoryUsed) const;

    void SetStartTime() noexcept { Start = std::chrono::high_resolution_clock::now(); }
    void SetFinishTime() noexcept { Finish = std::chrono::high_resolution_clock::now(); }

    void SetElapsedTime() noexcept { time_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(Finish - Start); }
    void StartRound() noexcept { SetStartTime(); }
    void FinishRound() noexcept {
        SetFinishTime();
        SetElapsedTime();
    }


public:
    Benchmark() = delete;
    Benchmark(const unsigned int nOperations ) : n_oper{nOperations} {}
         
    void SingleAlloc(Allocator *allocator , const size_t size ); // Same size, sequential
    void SingleDealloc(Allocator *allocator , const size_t size); // Free in allocation order

    void MultipleAlloc(Allocator *allocator , const vector<size_t> &sizes); // Different sizes, sequential  
    void MultipleDealloc(Allocator *allocator , const vector<size_t> &sizes); // Free in allocation order

    void RandomAlloc(Allocator *allocator , const vector<size_t> &sizes); // Different sizes, random selection
    void RandomDealloc(Allocator *allocator , const vector<size_t> &sizes); // Free in random order

};


#endif