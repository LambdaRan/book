

#include <stdlib.h>

#include <unistd.h>

int main(void)
{
    for (;;)
    {
        for (int i = 0; i < 9600000; ++i)
            ;
        usleep(10);
    }
    return 0;
}