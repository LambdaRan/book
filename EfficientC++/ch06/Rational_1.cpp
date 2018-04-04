
#include "Rational_1.h"



void Rational_1::expandTheFreeList()
{
    // 分配足够大的对象以包含下一个指针
    size_t size = (sizeof(Rational_1) > sizeof(NextOnFreeList *)) ? sizeof(Rational_1) : sizeof(NextOnFreeList*);

    //NextOnFreeList *runner = static_cast<NextOnFreeList *>(new char[size]);
    NextOnFreeList *runner = reinterpret_cast<NextOnFreeList *>(new char[size]);
    freeList = runner;
    for (int i = 0; i < EXPANSION_SIZE; ++i)
    {
        runner->next = reinterpret_cast<NextOnFreeList *>(new char[size]);
        runner = runner->next;
    }
    runner->next = 0;
}

void Rational_1::deleteMemPool()
{
    NextOnFreeList *nextPtr;
    for (nextPtr = freeList; nextPtr != NULL; nextPtr = freeList)
    {
        freeList = nextPtr->next;
        delete [] nextPtr;
    }
}