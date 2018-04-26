
// 顺序栈
// 不执行边界检查

#ifndef SQSTACK_H
#define SQSTACK_H

#include <stdint.h>
#include <stddef.h>
#include <assert.h>

// 存在一个问题 SqStack<int, 5>和SqStack<int, 10>具现两个不同的类型
// 这是template引出代码膨胀的典型例子
// 解决办法：effective C++ 条款44
// 提取只有类型模板参数为一个base模板， 其中定义存储大小和数据区域的指针，derived class实际存储数据
// template<typename T>
// class SqStackBase
// {
// protected:
//     SqStackBase(size_t n, T* mem)
//         : size_(n), data_(mem)
//     {}

// private: 
//     size_t size_;
//     T* data_;
// };
// template<typename T, size_t S>
// class SqStack : private SqStackBase<T>
// {
// public:
//     SqStack()
//         : SqStackBase<T>(container_, S)
//     {}
// private: 
//     T container_[S];
// };
template<typename T, size_t S>
class SqStack 
{
public: 
    SqStack();
    ~SqStack();

    void push(const T &value);
    void pop();
    T& top();
    bool empty() const;
    size_t size() const;
    size_t capcity() const;

private:
    SqStack(const SqStack&);
    SqStack& operator=(const SqStack&);
    
    int32_t top_;
    size_t capcity_;
    T container_[S];
};

template<typename T, size_t S>
inline
SqStack<T,S>::SqStack()
    : top_(-1), capcity_(S)
{}

template<typename T, size_t S>
inline
SqStack<T,S>::~SqStack()
{
    top_ = -1;
}

template<typename T, size_t S>
inline
void SqStack<T,S>::push(const T &value)
{
    assert(static_cast<size_t>(top_+1) <= capcity_);

    ++top_;
    container_[top_] = value;
}

template<typename T, size_t S>
inline
void SqStack<T,S>::pop()
{
    assert(top_ >= 0);

    --top_;
}
template<typename T, size_t S>
inline
T& SqStack<T,S>::top()
{
    return container_[top_];
}
template<typename T, size_t S>
inline
bool SqStack<T,S>::empty() const
{
    return top_ == -1;
}
template<typename T, size_t S>
inline
size_t SqStack<T,S>::size() const
{
    return top_+1;
}
template<typename T, size_t S>
inline
size_t SqStack<T,S>::capcity() const
{
    return capcity_;
}

#endif // !SQSTACK_H