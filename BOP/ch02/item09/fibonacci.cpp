

#include <iostream>

#include <vector>

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

int fibonacciLoop(int n)
{
    std::vector<int> oldValue(n+1);

    oldValue[0] = 0;
    oldValue[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        oldValue[i] = oldValue[i-1] + oldValue[i-2];
    }

    return oldValue[n];
}
int main(void)
{

    std::cout << "Fibonacci test:" << "\n";

    std::cout << "recursive: " << fibonacciRecursive(10) << "\n";
    std::cout << "iterator: " << fibonacciLoop(10) << "\n";

    return 0;
}