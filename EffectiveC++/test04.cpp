
#include <iostream>

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
};
class Derived : public Base
{
public:
    void print2()
    {
        std::cout << "derived2" << std::endl;
    }
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
int main()
{
    std::cout << "Hello Effective C++ \n";

    Derived dd;

    dd.print1();
    dd.print2();

    return 0;
}