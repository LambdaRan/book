

#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <stddef.h>

template <typename T>
class MemoryPool 
{
public: 
    MemoryPool(size_t size = EXPANSION_SIZE);
    ~MemoryPool();

    // 从空闲列表中分配Ｔ元素
    void* alloc(size_t size);

    // 返回Ｔ元素到空闲列表中
    void free(void *someElement);
    
private: 
    // 空闲列表的下一元素
    MemoryPool<T> *next;

    // 如果空闲列表为空，按该大小扩展它
    enum { EXPANSION_SIZE = 32 };

    //　添加空闲元素至空闲链表中
    void expandTheFreeList(int howMany);
};

template<typename T>
MemoryPool<T>::MemoryPool(size_t size)
{
    expandTheFreeList(size);
}

template<typename T>
MemoryPool<T>::~MemoryPool()
{
    MemoryPool<T> *nextPtr = next;
    for (nextPtr = next; nextPtr != NULL; nextPtr = next)
    {
        next = next->next;
        delete[] nextPtr;
    }
}

template<typename T> 
inline
void* MemoryPool<T>::alloc(size_t size)
{
    if (!next)
    {
        expandTheFreeList(size);
    }

    MemoryPool<T> *head = next;
    next = head->next;

    return head;
}

template<typename T> 
inline 
void MemoryPool<T>::free(void *doomed)
{
    MemoryPool<T> *head = static_cast<MemoryPool<T> *>(doomed);
    head->next = next;
    next = head;
}
template<typename T> 
inline
void MemoryPool<T>::expandTheFreeList(int howMany)
{
    // 我们必须分配足够大的对象以包含下一个指针
    size_t size = (sizeof(T) > sizeof(MemoryPool<T> *)) ? sizeof(T) : sizeof(MemoryPool<T> *);

    MemoryPool<T> *runner = reinterpret_cast<MemoryPool<T> *>(new char[size]);
    next = runner;
    for (int i = 0; i < howMany; ++i)
    {
        runner->next = reinterpret_cast<MemoryPool<T> *>(new char[size]);
        runner = runner->next;
    }

    runner->next = 0;
}
#endif // !MEMORYPOOL_H
