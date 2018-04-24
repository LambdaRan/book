

#include <iostream>

int number;
const int &getvalue()
{
    number = 88;
    return number;
}

int main(void)
{

    int num = getvalue();
    std::cout << num << std::endl;

    int n1 = 42;
    const int &nn = n1;
    int n2 = nn;
    
    return 0;
}