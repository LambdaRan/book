

#include "LinkQueue.h"

#include <iostream>

int main(void)
{

    LinkQueue<int> lq;

    lq.push(1);

    std::cout << "empty:" << (lq.empty() ? "true":"false") 
                << " size: " << lq.size() << "\n";

    lq.push(2);
    lq.push(3);
    lq.push(4);
    lq.push(5);
    std::cout << "size: 5 --> " << lq.size() << "\n";
    std::cout << "front: 1 --> " << lq.front() 
              << "\nback: 5 --> " << lq.back() << "\n";
    lq.pop();
    std::cout << "size: 4 --> " << lq.size() << "\n"; 

    // 测试拷贝与赋值运算符
    auto lq2 = lq;
    std::cout << "lq2 infor-->" << "empty:" << (lq2.empty() ? "true":"false") 
                << " size: " << lq2.size() << "\n";    
    std::cout << "front: 2 --> " << lq2.front() 
              << "\nback: 5 --> " << lq2.back() << "\n";

    LinkQueue<int> lq3(lq2);
    std::cout << "lq3 infor-->" << "empty:" << (lq3.empty() ? "true":"false") 
                << " size: " << lq3.size() << "\n";    
    std::cout << "front: 2 --> " << lq3.front() 
              << "\nback: 5 --> " << lq3.back() << "\n";

    lq.clear();
    std::cout << "size: 0 --> " << lq.size() << "\n"; 

    return 0;
}