#include "pool_alloc.h"
#include <assert.h>
#include <iostream>

using namespace std;

PoolAllocator::PoolAllocator(const size_t total_size , const size_t chunk) : Allocator(total_size){
    size_t min_size = sizeof(Node); 
    this->chunk_size = (chunk < min_size) ? min_size : chunk;
    this->chunk_size = (this->chunk_size + 7) & ~7;

    if(total_size % chunk_size != 0)
        throw invalid_argument("Total Size must be a multiple of Chunk Size");
    this->chunk_size = chunk;
}

void PoolAllocator::Init(const size_t total_size) {
    start_ptr = malloc(total_size);
    PoolAllocator::Reset();
}

void PoolAllocator::Reset() {
    used = 0;
    peak = 0;
    //create Free_list
    const int n_chunks = total_size / chunk_size;
    for(int i = 0 ; i<n_chunks ; i++) {
        size_t address = (size_t)start_ptr + i * chunk_size;
        free_list.push((Node *)address);
    }
}

void *PoolAllocator::Alloc(const size_t size , const size_t alignment) {
    if (size > chunk_size) {
        throw std::invalid_argument("Size exceeds chunk size");
    }
    Node *free_pos = free_list.pop();
    if(free_pos == nullptr) 
        throw out_of_range("Pool is exhausted");

    
    used += chunk_size;
    peak = peak > used ? peak : used;
    return (void *)free_pos;
}

void PoolAllocator::DeAlloc(void *ptr) {
    used -= chunk_size;
    free_list.push((Node *)ptr);
}