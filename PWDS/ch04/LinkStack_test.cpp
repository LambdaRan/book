


#include "LinkStack.h"

#include <stddef.h>

#include <iostream>

int main(void)
{
    LinkStack<int> ss;
    std::cout << "LinkStack size: " << ss.size() 
              << " isEmpty: " << ((ss.empty()? "true":"false")) << std::endl;

    ss.push(1);
    ss.push(2);
    ss.push(3);
    ss.push(4);
    ss.push(5);
    std::cout << "LinkStack size: 5 --> " << ss.size() << " isEmpty: " << ((ss.empty()? "true":"false")) << "\n";

    std::cout << "LinkStack top: 5 --> " << ss.top() << "\n";
    size_t msize = ss.size();
    for (size_t i = 0; i < msize; ++i)
    {
        std::cout << " " << ss.top() << " ";
        ss.pop();
    }
    std::cout <<  "\n LinkStack size: 0 --> " << ss.size() << "\n";

    return 0;
}