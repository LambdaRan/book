

#include "Rational_0.h"
#include "Rational_1.h"
#include "Rational_2.h"
#include "MemoryPool.h"

#include "../tools/TimeRecord.h"
#include <iostream>

NextOnFreeList *Rational_1::freeList = 0;
MemoryPool<Rational_2> *Rational_2::memPool = 0;

int main(int argc, const char* argv[])
{
    TimeRecord tr;

    Rational_0 *array[1000];
    std::cout << "版本0: 全局函数new() 和　delete()" << std::endl;
    tr.start();
    for (int j = 0; j < 500; ++j)
    {
        for (int i = 0; i < 1000; ++i)
        {
            array[i] = new Rational_0(i);
        }
        for (int i = 0; i < 1000; ++i)
        {
            delete array[i];
        }
    }
    tr.stop();

    Rational_1 *array1[1000];
    std::cout << "版本1: 专用Rational 内存管理器" << std::endl;
    tr.start();
    for (int j = 0; j < 500; ++j)
    {
        for (int i = 0; i < 1000; ++i)
        {
            array1[i] = new Rational_1(i);
        }
        for (int i = 0; i < 1000; ++i)
        {
            delete array1[i];
        }
    }
    tr.stop();

    Rational_2 *array2[1000];
    Rational_2::newMemPool();
    std::cout << "版本2: 固定大小对象的内存池" << std::endl;
    tr.start();
    for (int j = 0; j < 500; ++j)
    {
        for (int i = 0; i < 1000; ++i)
        {
            array2[i] = new Rational_2(i);
        }
        for (int i = 0; i < 1000; ++i)
        {
            delete array2[i];
        }
    }
    tr.stop();
    //Rational_2::deleteMemPool();

    return 0;
}