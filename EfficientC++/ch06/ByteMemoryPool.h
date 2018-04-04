
#ifndef BYTEMEMORYPOOL_H
#define BYTEMEMORYPOOL_H

#include "MemoryChunk.h"

class ByteMemoryPool 
{
public: 
    ByteMemoryPool(size_t initSize = MemoryChunk::DEFAULT_CHUNK_SIZE);
    ~ByteMemoryPool();

    // 从私有内存池分配内存
    inline void *alloc(size_t size);

    // 释放先前从内存池中分配的内存
    inline void free(void *doomed);

private: 
    // 内存块列表。 他是我们的私有存储空间
    MemoryChunk *listOfMemoryChunks;

    // 向我们的私有存储空间添加一个内存块
    void expandStorage(size_t reqSize);
};

ByteMemoryPool::ByteMemoryPool(size_t initSize)
{
    expandStorage(initSize);
}

ByteMemoryPool::~ByteMemoryPool()
{
    MemoryChunk *memChunk = listOfMemoryChunks;

    while (memChunk)
    {
        listOfMemoryChunks = memChunk->nextMemChunk();
        delete memChunk;
        memChunk = listOfMemoryChunks;
    }
}

inline
void *ByteMemoryPool::alloc(size_t requestSize)
{
    size_t space = listOfMemoryChunks->spaceAvailable();
    if (space < requestSize)
    {
        expandStorage(requestSize);
    }

    return listOfMemoryChunks->alloc(requestSize);
}

inline
void ByteMemoryPool::free(void *doomed)
{
    listOfMemoryChunks->free(doomed);
}

void ByteMemoryPool::expandStorage(size_t reqSize)
{
    listOfMemoryChunks = new MemoryChunk(listOfMemoryChunks, reqSize);
}
#endif // !BYTEMEMORYPOOL_H
