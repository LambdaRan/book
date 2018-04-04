#ifndef RATIONAL_1_H
#define RATIONAL_1_H

#include <stddef.h>
#include <iostream>


//using namespace std;

class NextOnFreeList
{
public: 
    NextOnFreeList *next;
};

class Rational_1
{
public: 
    Rational_1(int a = 0, int b = 1)
        : n(a), d(b)
    {}
    
    //inline void *operator new(size_t size);
    //inline void operator delete(void *doomd, size_t size);

    void *operator new(size_t size)
    {
        if (0 == freeList)// 如果列表为空，则将其填满
        {
            expandTheFreeList();
        }

        NextOnFreeList *head = freeList;
        freeList = head->next;

        return head;
    }

    void operator delete(void *doomed, size_t size)
    {
        NextOnFreeList *head = static_cast<NextOnFreeList *>(doomed);
        head->next = freeList;
        freeList = head;
    }
    
    static void newMemPool()
    {
        expandTheFreeList();
    }

    static void deleteMemPool();

private: 
    static NextOnFreeList *freeList;// Rational_1 对象的空闲列表
    static void expandTheFreeList();
    enum { EXPANSION_SIZE = 32 };

    int n; // 分子
    int d; // 分母
};

#endif // !RATIONAL_H