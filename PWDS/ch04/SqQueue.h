
// 队列的顺序存储结构

#ifndef SQQUEUE_H
#define SQQUEUE_H

#include <stddef.h>
#include <assert.h>

// 存在一个问题 SqQueue<int, 5>SqQueue<int, 10>具现两个不同的类型
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
class SqQueue 
{
public:
    SqQueue();
    ~SqQueue();

    void push(const T &value);
    void pop();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    void clear();
    size_t size() const;
    size_t capcity() const;
    bool empty() const;
    bool full() const;
    // default copy constructor and copy assignment
private:
    size_t front_;
    size_t rear_;
    size_t capcity_;
    T container_[S];
};
template<typename T, size_t S>
inline
SqQueue<T, S>::SqQueue()
    : front_(0), rear_(0), capcity_(S)
{}

template<typename T, size_t S>
inline
SqQueue<T, S>::~SqQueue()
{
    clear();
}
template<typename T, size_t S>
inline
void SqQueue<T, S>::push(const T &value)
{
    assert(!full());
    //if ((rear_+1) % capcity_ != front_) // 队列满判断
    //{
        container_[rear_] = value;
        rear_ = (rear_ + 1) % capcity_;
    //}
}
template<typename T, size_t S>
inline
void SqQueue<T, S>::pop()
{
    assert(!empty());
    //if (front_ != rear_)// 队列空判断
    //{
        front_ = (front_ + 1) % capcity_;
    //}
}
template<typename T, size_t S>
inline
T& SqQueue<T, S>::front()
{
    //return container_[front_];

    // 避免代码重复：
    // non-const函数调用其const兄弟是一个避免代码重复的安全做法
    return const_cast<T&>(static_cast<const SqQueue<T, S>&>(*this).front());
}
template<typename T, size_t S>
inline
const T& SqQueue<T, S>::front() const
{
    return container_[front_];    
}

template<typename T, size_t S>
inline
T& SqQueue<T, S>::back()
{
    size_t index = (rear_ + capcity_ - 1) % capcity_;
    return container_[index];
}
template<typename T, size_t S>
inline
const T& SqQueue<T, S>::back() const
{
    size_t index = (rear_ + capcity_ - 1) % capcity_;
    return container_[index];
}
template<typename T, size_t S>
inline
void SqQueue<T, S>::clear()
{
    front_ = rear_ = 0;
}
template<typename T, size_t S>
inline
size_t SqQueue<T, S>::size() const
{
    return (rear_ + capcity_ - front_) % capcity_;
}
template<typename T, size_t S>
inline
size_t SqQueue<T, S>::capcity() const
{
    return capcity_;
}
template<typename T, size_t S>
inline
bool SqQueue<T, S>::empty() const
{
    return front_ == rear_;
}
template<typename T, size_t S>
inline
bool SqQueue<T, S>::full() const
{
    return (rear_+1) % capcity_ == front_;
}
#endif // !SQQUEUE_H
