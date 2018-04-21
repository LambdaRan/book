

#include "SqQueue.h"

#include <iostream>

int main(void)
{

    SqQueue<int, 32> sq;

    sq.push(1);

    std::cout << "empty:" << (sq.empty() ? "true":"false") 
                << " size: " << sq.size() << " capcity: " << sq.capcity() << "\n";

    sq.push(2);
    sq.push(3);
    sq.push(4);
    sq.push(5);
    std::cout << "size: 5 --> " << sq.size() << "\n";
    std::cout << "front: 1 --> " << sq.front() 
              << "\nback: 5 --> " << sq.back() << "\n";
    sq.pop();
    std::cout << "size: 4 --> " << sq.size() << "\n"; 

    // 测试拷贝与赋值运算符
    auto sq2 = sq;
    std::cout << "sq2 infor-->" << "empty:" << (sq2.empty() ? "true":"false") 
                << " size: " << sq2.size() << " capcity: " << sq2.capcity() << "\n";    
    std::cout << "front: 2 --> " << sq2.front() 
              << "\nback: 5 --> " << sq2.back() << "\n";

    SqQueue<int, 32> sq3(sq2);
    std::cout << "sq3 infor-->" << "empty:" << (sq3.empty() ? "true":"false") 
                << " size: " << sq3.size() << " capcity: " << sq3.capcity() << "\n";    
    std::cout << "front: 2 --> " << sq3.front() 
              << "\nback: 5 --> " << sq3.back() << "\n";

    sq.clear();
    std::cout << "size: 0 --> " << sq.size() << "\n"; 

    return 0;
}