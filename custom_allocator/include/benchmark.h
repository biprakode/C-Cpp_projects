#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <vector>
#include <string>
#include <functional>
#include "allocator.h"
using namespace std;


#define OPERATION (n_oper)

struct benchmark_result {
    string alloc_name;
    double OperationsPerSec;    // Throughput
    double TimePerOperation;
    size_t oper;
    size_t mem_peak;
};

class Benchmark {
private:
    size_t n_oper;
    chrono::time_point<chrono::high_resolution_clock> Start;
    chrono::time_point<chrono::high_resolution_clock> Finish;
    chrono::milliseconds time_elapsed;

    void PrintResults(const benchmark_result& results) const;
    const benchmark_result buildResults(size_t nOperations, chrono::milliseconds&& ellapsedTime, const size_t memoryUsed) const;

    void SetStartTime() noexcept { Start = std::chrono::high_resolution_clock::now(); }
    void SetFinishTime() noexcept { Finish = std::chrono::high_resolution_clock::now(); }

    void SetElapsedTime() noexcept { time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(Finish - Start); }
    void StartRound() noexcept { SetStartTime(); }
    void FinishRound() noexcept {
        SetFinishTime();
        SetElapsedTime();
    }


public:
    Benchmark() = delete;
    Benchmark(Allocator *allocator , const size_t size , const size_t alignment);
     
    void SingleAlloc(Allocator *allocator , const size_t size , const size_t alignment); // Same size, sequential
    void SingleDealloc(Allocator *allocator , const size_t size , const size_t alignment); // Free in allocation order

    void MultipleAlloc(Allocator *allocator , const vector<size_t> &sizes , const vector<size_t> &alignments); // Different sizes, sequential  
    void MultipleDealloc(Allocator *allocator , const vector<size_t> &sizes , const vector<size_t> &alignments); // Free in allocation order

    void RandomAlloc(Allocator *allocator , const vector<size_t> &sizes , const vector<size_t> &alignments); // Different sizes, random selection
    void RandomDealloc(Allocator *allocator , const vector<size_t> &sizes , const vector<size_t> &alignments); // Free in random order

};


#endif