
// 队列链式存储结构

#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <stddef.h>
#include <assert.h>

template<typename T>
class LinkQueue 
{
public:
    LinkQueue();
    ~LinkQueue();

    LinkQueue(const LinkQueue&);
    LinkQueue& operator=(const LinkQueue&);

    void push(const T &value);
    void pop();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    void clear();
    size_t size() const;
    bool empty() const;
private:

    struct Node 
    {
        explicit Node(const T &value)
            : data_(value), next_(NULL)
        {}
        
        T data_;
        Node *next_;
    };

    size_t size_;
    Node header_; // 头节点
    //Node *front_;
    Node *rear_;
};

template<typename T>
inline
LinkQueue<T>::LinkQueue()
    : size_(0), header_(0), rear_(&header_) // 存在一个问题header_(0)
{}

template<typename T>
LinkQueue<T>::~LinkQueue()
{
    clear();
}
template<typename T>
LinkQueue<T>::LinkQueue(const LinkQueue<T> &rhs)
    : size_(0), header_(0), rear_(&header_) // 存在一个问题header_(0)
{
    Node *tmp = rhs.header_.next_;
    while (tmp)
    {
        push(tmp->data_);
        tmp = tmp->next_;
    }
}

template<typename T>
typename LinkQueue<T>::LinkQueue& LinkQueue<T>::operator=(const LinkQueue &rhs)
{
    if (this != &rhs) // 防止自我赋值
    {
        clear();
        rear_ = &header_;
        Node *tmp = rhs.next_;
        while (tmp)
        {
            push(tmp->data_);
            tmp = tmp->next_;
        }
    } 
    return *this;       
}

template<typename T>
void LinkQueue<T>::push(const T &value)
{
    Node *node = new Node(value);
    rear_->next_ = node;
    rear_ = node;
    ++size_;
}
template<typename T>
void LinkQueue<T>::pop()
{
    Node *node = header_.next_;
    header_.next_ = node->next_;
    delete node;
    --size_;
}

template<typename T>
inline
T& LinkQueue<T>::front()
{
    assert(header_.next_ != NULL);
    return header_.next_->data_;
}
template<typename T>
inline
const T& LinkQueue<T>::front() const
{
    assert(header_.next_ != NULL);
    return header_.next_->data_;
}

template<typename T>
inline
T& LinkQueue<T>::back()
{
    return const_cast<T&>(static_cast<const LinkQueue<T>&>(*this).back());
}
template<typename T>
inline
const T& LinkQueue<T>::back() const
{
    return rear_->data_;
}
template<typename T>
void LinkQueue<T>::clear()
{
    Node *tmp = NULL;
    while (header_.next_)
    {
        tmp = header_.next_;
        header_.next_ = tmp->next_;
        delete tmp;
    }
    size_ = 0;
}
template<typename T>
inline
size_t LinkQueue<T>::size() const
{
    return size_;
}

template<typename T>
inline
bool LinkQueue<T>::empty() const
{
    return size_ == 0;
}
#endif // !LINKQUEUE_H

