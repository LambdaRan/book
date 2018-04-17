
#include <iostream>
inline int get_static()
{
    static int loc = 3;
    return (++loc);
}



int main()
{
    std::cout << "Hello Effective C++ \n";
    std::cout << "value1: " << get_static() << "\n";
    std::cout << "value2: " << get_static() << "\n";
    return 0;
}