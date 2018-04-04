

// 把不同大小的内存块连接起来形成块序列
#ifndef MEMORYCHUNK_H
#define MEMORYCHUNK_H

class MemoryChunk 
{
public: 
    MemoryChunk(MemoryChunk *nextChunk, size_t chunkSize);
    ~MemoryChunk();

    inline void *alloc(size_t size);
    inline void free(void *doomed);

    // 指向列表下一内存块的指针
    MemoryChunk *nextMemChunk()
    {
        return next;
    }

    // 当前内存块剩余空间大小
    size_t spaceAvailable()
    {
        return chunkSize - bytesAlreadAllocated;
    }

    // 这是一个内存块的默认大小
    enum { DEFAULT_CHUNK_SIZE = 4096 };
    //const size_t DEFAULT_CHUNK_SIZE = 4096;
private: 
    MemoryChunk *next;
    void *mem;

    // 一个内存块的默认大小
    size_t chunkSize;

    // 当前内存块中已分配的字节数
    size_t bytesAlreadAllocated;
};

MemoryChunk::MemoryChunk(MemoryChunk *nextChunk, size_t reqSize)
{
    chunkSize = (reqSize > DEFAULT_CHUNK_SIZE) ? reqSize : DEFAULT_CHUNK_SIZE;
    next = nextChunk;
    bytesAlreadAllocated = 0;
    mem = new char[chunkSize];
}

MemoryChunk::~MemoryChunk()
{
    delete mem;
}

void *MemoryChunk::alloc(size_t requestSize)
{
    void *addr = reinterpret_cast<void *>(reinterpret_cast<size_t>(mem) + bytesAlreadAllocated);
    bytesAlreadAllocated += requestSize;
    return addr;
}

inline
void MemoryChunk::free(void *doomed)
{
    (void)doomed;
    // 无操作
}
#endif // !MEMORYCHUNK_H
  