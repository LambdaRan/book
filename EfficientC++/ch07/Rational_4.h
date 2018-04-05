
#ifndef RATIONAL_4_H
#define RATIONAL_4_H

#include "MTMemoryPool.h"
#include "MutexLock.h"
#include "../ch06/MemoryPool.h"

class Rational_4 
{
public: 
    Rational_4(int a = 0, int b = 1)
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
        memPool = new MTMemoryPool<MemoryPool<Rational_4>, MutexLock>;
    }

    static void deleteMemPool()
    {
        delete memPool;
    }

private: 
    static MTMemoryPool<MemoryPool<Rational_4>, MutexLock> *memPool;

    int n; // 分子
    int d; // 分母
};

#endif // !RATIONAL_4_H
