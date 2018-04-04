
#ifndef RATIONAL_3_H
#define RATIONAL_3_H

#include "ByteMemoryPool.h"

class Rational_3
{
public: 
    Rational_3(int a = 0, int b = 1)
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
        memPool = new ByteMemoryPool;
    }

    static void deleteMemPool()
    {
        delete memPool;
    }

private: 
    static ByteMemoryPool *memPool;

    int n; // 分子
    int d; // 分母
};

#endif