

#include "Rational_0.h"
#include "Rational_1.h"
#include "Rational_2.h"
#include "MemoryPool.h"

#include "ByteMemoryPool.h"
#include "Rational_3.h"

#include "../tools/TimeRecord.h"
#include <iostream>

NextOnFreeList *Rational_1::freeList = 0;
MemoryPool<Rational_2> *Rational_2::memPool = 0;
ByteMemoryPool *Rational_3::memPool = 0;

// https://stackoverflow.com/questions/3599160/unused-parameter-warnings-in-c
int main(int argc, const char* argv[])
{
    (void)argc;
    (void)argv;

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

    Rational_3 *array3[1000];
    Rational_3::newMemPool();
    std::cout << "版本3: 单线程可变大小内存管理器" << std::endl;
    tr.start();
    for (int j = 0; j < 500; ++j)
    {
        for (int i = 0; i < 1000; ++i)
        {
            array3[i] = new Rational_3(i);
        }
        for (int i = 0; i < 1000; ++i)
        {
            delete array3[i];
        }
    }
    tr.stop();
    Rational_3::deleteMemPool();

    return 0;
}