#include "stack_alloc.h"
#include "padding.h"
#include "allocator.h"

#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;

StackAllocator::StackAllocator(const size_t total_size) : Allocator(total_size) {
    Init(total_size);
}

void StackAllocator::Init(const size_t total_size){
    if(start != nullptr) {
        free(start);
    }
    start = malloc(total_size);
    offset = 0;
}

StackAllocator:: ~StackAllocator() {
    free(start);
    start = nullptr;
}

void *StackAllocator::Alloc(const size_t size , const size_t alignment) {
    const size_t cur_adr = (size_t)start + offset;
    const size_t padding = Padder::calculate_padding_header(cur_adr , alignment , sizeof(AllocationHead));
    
    if(offset + padding + size > total_size) {
        throw std::out_of_range("Arena exhausted");
    }
    offset += padding;
    
    size_t next_adr = cur_adr + padding;
    size_t header_adr = next_adr - sizeof(AllocationHead);
    AllocationHead alloc_header{padding};
    AllocationHead *alloc_header_ptr = reinterpret_cast<AllocationHead*>(reinterpret_cast<void*>(header_adr));
    *alloc_header_ptr = alloc_header;

    offset += size;
    used = offset;
    peak = peak > used ? peak : used;

    return (void *)next_adr;
}

void StackAllocator::DeAlloc(void *ptr) {
    const size_t current_adr = (size_t)ptr;
    const size_t header_adr = current_adr - sizeof(AllocationHead);
    const AllocationHead *alloc_head{(AllocationHead *) header_adr};

    offset = current_adr - alloc_head->padding - (size_t)start;
    used = offset;
}

void StackAllocator::Reset() {
    used = 0;
    offset = 0;
    //start not touched (arena allocated)
}