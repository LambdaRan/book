

#include <iostream>

template<typename T> 
void f(T &p)
{
    std::cout << p << std::endl;
}
template<typename T> 
void f1(const T &p)
{
    std::cout << p << std::endl;
}
template<typename T> 
void f2(T &&p)
{
    std::cout << p << std::endl;
}

void g(int &&p)
{
    std::cout << p << std::endl;
}

int main(void)
{
    int value = 66;
    int &lvalue = value;
    const int &clvaue = 66;
    int &&rvalue = 66;

    f(value);
    f(std::forward<int&>(32));

    f1(value);
    f1(32);  

    f2(value);
    f2(32);

    g(std::forward<int>(32));

    auto tf1 = std::forward<int&>(value);
    return 0;
}