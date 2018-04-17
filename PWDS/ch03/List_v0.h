

// 线性表的顺序存储结构
// 只能存储内建类型

#ifndef LIST_V0_H
#define LIST_V0_H

#include <stddef.h> // size_t
#include <assert.h>

#include <algorithm> // std::find()
#include <iterator> // std::begin() std::end()

template<typename T, size_t S>
class List_v0 
{
public:
    List_v0()
        : size_(0), capcity_(S)
    {}

    bool empty() const 
    {
        return size_ == 0;
    }

    void clear() 
    {
        size_ = 0;
    }

    // 不检查是否越界
    T& get(size_t index) const 
    {
        return container_[index];
    }

    size_t find(const T &value) const 
    {
        return std::end(container_) - std::find(std::begin(container_), std::end(container_), value) ;
    }

    // 不检查越界
    void push(const T &value)
    {
        assert( size_ <= capcity_);

        container_[size_] = value;
        ++size_;
    }

    // 不检查越界
    void insert(size_t index, const T &value)
    {
        assert(index <= size_+1);
        assert(size_+1 <= capcity_);

        for (int i = size_; i > index; --i)
        {
            container_[i+1] = container_[i];
        }
        container_[index] = value;
        ++size_;
    }
    // 不检查越界
    void deletel(size_t index, T &ret)
    {
        assert(index >= 0 && index <= size_-1);
        assert(size_-1 >= 0);

        ret = container_[index];
        for (int i = index; i < size_; ++i)
        {
            container_[i] = container_[i+1];
        }
        --size_;
    }

    size_t size() const 
    {
        return size_;
    }

    size_t capcity() const 
    {
        return capcity_;
    }

private: 
    List_v0(const List_v0&);
    List_v0& operator=(const List_v0&);

    size_t size_;
    size_t capcity_;
    T container_[S];
};


#endif // !LIST_V0_H
