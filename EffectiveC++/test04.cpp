
#include <iostream>

#include <assert.h>

class Base 
{
public:
    void print1()
    {
        std::cout << "base1" << std::endl;
    }
    void print2()
    {
        std::cout << "base2" << std::endl;
    }
    static const int kcon = 32;
    enum {ONE, TWO};
};
class Derived : public Base
{
public:
    int x;
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
int main()
{
    std::cout << "Hello Effective C++ \n";

    Derived dd;

    static_assert(sizeof(Derived) == sizeof(int), "sizeof(Derived) != sizeof(int)");

    return 0;
}