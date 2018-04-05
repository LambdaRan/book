

#ifndef MTMEMORYPOOL_H
#define MTMEMORYPOOL_H

#include "stddef.h"

template<typename POOLTYPE, typename LOCK>
class MTMemoryPool
{
public: 
    // 从freeList里分配一个元素
    inline void *alloc(size_t size);

    //　返回一个元素给freeList
    inline void free(void *someElement);

private: 
    POOLTYPE stPool;//单线程池
    LOCK theLock;
};

template<typename M, typename L>
inline
void *MTMemoryPool<M,L>::alloc(size_t size)
{
    void *mem;
    theLock.lock();
    mem = stPool.alloc(size);
    theLock.unlock();

    return mem;
}

template<typename M, typename L>
inline
void MTMemoryPool<M,L>::free(void *doomed)
{
    theLock.lock();
    stPool.free(doomed);
    theLock.unlock();
}
#endif // !MTMEMORYPOOL_H
