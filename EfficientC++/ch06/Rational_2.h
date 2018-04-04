
#ifndef RATIONAL_2_H
#define RATIONAL_2_H

#include "MemoryPool.h"

class Rational_2
{
public: 
    Rational_2(int a = 0, int b = 1)
        : n(a), d(b)
    {}
    
    void *operator new(size_t size)
    {
        return memPool->alloc(size);
    }

    void operator delete(void *doomed, size_t size)
    {
        (void)size;
        memPool->free(doomed);
    }
    
    static void newMemPool()
    {
        memPool = new MemoryPool<Rational_2>;
    }

    static void deleteMemPool()
    {
        delete memPool;
    }

private: 
    static MemoryPool<Rational_2> *memPool;

    int n; // 分子
    int d; // 分母
};

#endif