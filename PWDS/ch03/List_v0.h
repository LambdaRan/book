

// 线性表的顺序存储结构

#ifndef LIST_V0_H
#define LIST_V0_H

#include <stddef.h> // size_t

template<typename T>
class List_v0 
{
public:
    
private: 
    const size_t kDefaultSize = 32;
    size_t size_;
    T container_[kDefaultSize];
};


#endif // !LIST_V0_H
