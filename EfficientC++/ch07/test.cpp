

#include "Rational_4.h"

#include "../tools/TimeRecord.h"
#include <iostream>

MTMemoryPool<MemoryPool<Rational_4>, MutexLock> *Rational_4::memPool = 0;
int main(int argc, const char* argv[])
{
    (void)argc;
    (void)argv;

    TimeRecord tr;

    Rational_4 *array4[1000];
    Rational_4::newMemPool();
    std::cout << "版本4: 多线程内存池" << std::endl;
    tr.start();
    for (int j = 0; j < 500; ++j)
    {
        for (int i = 0; i < 1000; ++i)
        {
            array4[i] = new Rational_4(i);
        }
        for (int i = 0; i < 1000; ++i)
        {
            delete array4[i];
        }
    }
    tr.stop();
    //Rational_4::deleteMemPool();

    return 0;
}