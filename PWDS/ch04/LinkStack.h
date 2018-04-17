

// 栈的链式存储结构

#ifndef LINKSTACK_H
#define LINKSTACK_H

#include <stddef.h>
#include <assert.h>


template<typename T>
class LinkStack 
{
public:
    LinkStack();
    ~LinkStack();

    void push(const T &value);
    void pop();
    T& top();

    size_t size() const;
    bool empty() const;

private:
    LinkStack(const LinkStack&);
    LinkStack& operator=(const LinkStack&);

    struct Node 
    {
        explicit Node(const T &value)
            : data_(value), next_(NULL)
        {}
        
        T data_;
        Node *next_;
    };

    size_t size_;
    Node *top_;
};

template<typename T>
inline
LinkStack<T>::LinkStack()
    : size_(0), top_(NULL)
{}

template<typename T>
inline
LinkStack<T>::~LinkStack()
{
    Node *tmp = NULL;
    while (top_)
    {
        tmp = top_;
        top_ = top_->next_;
        delete tmp;
    }
    size_ = 0;
}

template<typename T>
inline
void LinkStack<T>::push(const T &value)
{
    Node *tmp = new Node(value);
    tmp->next_ = top_;
    top_ = tmp;
    ++size_;
}
template<typename T>
inline
void LinkStack<T>::pop()
{
    //assert();
    if (top_)
    {
        Node *tmp = top_;
        top_ = top_->next_;
        delete tmp;
        --size_;
    }
}
template<typename T>
inline
T& LinkStack<T>::top()
{
    assert(top_ != NULL);
    return top_->data_;
}
template<typename T>
inline
size_t LinkStack<T>::size() const
{
    return size_;
}
template<typename T>
inline
bool LinkStack<T>::empty() const
{
    return size_ == 0;
}

#endif // !LINKSTACK_H


