
// 顺序栈
// 不执行边界检查

#ifndef SQSTACK_H
#define SQSTACK_H

#include <stdint.h>
#include <assert.h>


template<typename T, size_t S>
class SqStack 
{
public: 
    SqStack();
    ~SqStack();

    void push(const T &value);
    void pop();
    T& top() const;
    bool empty() const;
    size_t size() const;
    size_t capcity() const;

private: 
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
    assert(top_+1 <= capcity_);
    ++top_;
    container_[top_] = value;
}

template<typename T, size_t S>
inline
void SqStack<T,S>::pop()
{
    --top_;
}
template<typename T, size_t S>
inline
T& top() const
{
    return container_[top_];
}
template<typename T, size_t S>
inline
bool empty() const
{
    return top_ == -1;
}
template<typename T, size_t S>
inline
size_t size() const
{
    return top_+1;
}
template<typename T, size_t S>
inline
size_t capcity() const
{
    return capcity_;
}

#endif // !SQSTACK_H