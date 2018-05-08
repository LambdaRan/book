

#include <iostream>

#include <vector>
#include <stdint.h>

int fibonacciRecursive(int n)
{
    if (n <= 0)
        return 0;
    else if (n == 1)
    {
        return 1;
    }
    else  
    {
        return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
    }
}

uint32_t fibonacciLoop(uint32_t n)
{
    std::vector<uint32_t> oldValue(n+1);

    oldValue[0] = 0;
    oldValue[1] = 1;
    for (uint32_t i = 2; i <= n; ++i)
    {
        oldValue[i] = oldValue[i-1] + oldValue[i-2];
    }
    //std::cout << "size: " << oldValue.size() << "\n";
    for (auto v : oldValue)
        std::cout << v << ",";
    std::cout << std::endl;

    return oldValue[n];
}
// # define INT8_MAX		(127)                F(11) = 89               
// # define INT16_MAX		(32767)              F(23) = 28657 
// # define INT32_MAX		(2147483647)         F(48) = 512559680

/* Maximum of unsigned integral types.  */
// # define UINT8_MAX		(255)                F(13) = 233 
// # define UINT16_MAX		(65535)              F(24) = 46368
// # define UINT32_MAX		(4294967295U)        F(51) = 3185141890



//F(24) = 46368
// 斐波那契数列  前25项
//array[25] = [0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368];
int main(void)
{

    std::cout << "Fibonacci test:" << "\n";

    int input;
    std::cin >> input;
    //std::cout << "recursive(" << input << "): " << fibonacciRecursive(input) << "\n";
    std::cout << "iterator(" << input << "): " << fibonacciLoop(input) << "\n";

    return 0;
}