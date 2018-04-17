

#include "SqStack.h"

#include <stddef.h>

#include <iostream>

int main(void)
{
    SqStack<int, 32> ss;
    std::cout << "SqStack size: " << ss.size() << " capcity: " << ss.capcity() 
              << " isEmpty: " << ((ss.empty()? "true":"false")) << std::endl;

    ss.push(1);
    ss.push(2);
    ss.push(3);
    ss.push(4);
    ss.push(5);
    std::cout << "SqStack size: 5 --> " << ss.size() << " isEmpty: " << ((ss.empty()? "true":"false")) << "\n";

    std::cout << "SqStack top: 5 --> " << ss.top() << "\n";
    size_t msize = ss.size();
    for (size_t i = 0; i < msize; ++i)
    {
        std::cout << " " << ss.top() << " ";
        ss.pop();
    }
    std::cout <<  "\nSqStack size: 0 --> " << ss.size() << "\n";

    return 0;
}