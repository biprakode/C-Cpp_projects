#ifndef ALLOC_H
#define ALLOC_H

#include <iostream>
using namespace std;

class Allocator {
protected:
    size_t total_size;
    size_t used;
    size_t peak;
public:
    Allocator(const size_t total) : total_size(total) , used(0) , peak(0) {}
    virtual ~Allocator() {total_size = 0;}
    virtual void *Alloc(const size_t size , const size_t alignment) = 0;
    virtual void DeAlloc(void *ptr) = 0;
    virtual void Reset() = 0;
};

#endif