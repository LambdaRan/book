



#ifndef STATICLIST_H
#define STATICLIST_H

#include <stddef.h>

template<typename T, size_t S>
class StaticList 
{
public: 
    StaticList()
        : capcity_(S)
    {
        for (int i = 0; i < capcity_-1; ++i)
        {
            container_[i].cur_ = i + 1;
        }
        container_[capcity_-1].cur_ = 0;
    }

private: 
    struct Component
    {
        Component(const T &value)
            : data_(value), cur_(0)
        {}

        T data_; // 数据
        size_t cur_; // 游标，为0表示无指向
    };

    Component container_[S];
    size_t capcity_;
};



#endif // !STATICLIST_H
