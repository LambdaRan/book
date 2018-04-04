

#include "TimeRecord.h"
#include <unistd.h>

#include <iostream>

int main(int argc, const char *argv[])
{
    std::cout << "Test TimeRecord" << std::endl;
    TimeRecord tr;

    std::cout << "1 s --> 1000ms" << std::endl;
    tr.start();
    sleep(1);
    tr.stop();

    std::cout << "10 us --> 0.1ms" << std::endl;
    tr.start();
    usleep(10);
    tr.stop();

    return 0;
}