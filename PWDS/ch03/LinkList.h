

// 线性表链式存储结构  （单链表）
// 数据类型为内建类型


#ifndef LINKLIST_H
#define LINKLIST_H

#include <stddef.h>

template<typename T>
class LinkList 
{
public: 
    //typedef T* iterator;
    using iterator = T*;

    LinkList()
        : head_(0), iterator_node_(NULL)
    {}

    // 释放链表
    ~LinkList()
    {
        clear();
    }

    void push(const T &value);
    void append(const T &value);
    void pop(T &ret);
    void insert(size_t i, const T &value);
    void deletel(size_t i, T &ret);
    T& get(size_t i);

    void iterator_begin(size_t i = 1);
    bool iterator_end() const;
    iterator iterator_next();

    void reverse();
    size_t size() const;
    void clear();
private:
    struct Node 
    {
        Node(const T &value)
            : data_(value), next_(NULL)
        {}

        T data_;
        Node *next_;
    };

    // 栈空间 头节点
    Node head_;

    // 迭代器变量
    Node *iterator_node_;
};
// 头插法
template<typename T>
void LinkList<T>::push(const T &value)
{
    Node *tmp = new Node(value);
    tmp->next_ = head_.next_;
    head_.next_ = tmp;
}
template<typename T>
void LinkList<T>::append(const T &value)
{
    Node *node = &head_;
    while (node->next_)
    {
        node = node->next_;
    }

    Node *tmp = new Node(value);
    node->next_ = tmp;
}

// 取第一个节点
template<typename T>
void LinkList<T>::pop(T &ret)
{
    Node *tmp = head_.next_;
    head_.next_ = tmp->next_;
    ret = tmp->data_;
    delete tmp;
}

// 如果索引大于链表大小 直接把新节点插入链尾
template<typename T>
void LinkList<T>::insert(size_t i, const T &value)
{
    Node *node = &head_;
    size_t j = 1;
    while (node->next_ && j < i)
    {
        node = node->next_;
        ++j;
    }

    Node *tmp = new Node(value);
    if (!node->next_ || j > i) // 最后一个节点
    {
        node->next_ = tmp;
    }
    else 
    {
        tmp->next_ = node->next_->next_;
        node->next_ = tmp;
    }
}

// 删除索引处的节点
template<typename T>
void LinkList<T>::deletel(size_t i, T &ret)
{
    Node *node = &head_;
    size_t j = 1;
    while (node->next_ && j < i)
    {
        node = node->next_;
        ++j;
    }

    if (!node->next_ || j > i) // 最后一个节点
    {
        return;
    }  
    else 
    {
        Node *tmp = node->next_;
        node->next_ = tmp->next_;
        ret = tmp->data_;
        delete tmp;
    }      
}

// 如果索引大于链表大小 直接返回最后节点
template<typename T>
inline
T& LinkList<T>::get(size_t i)
{
    Node *node = &head_;
    size_t j = 1;
    while (node->next_ && j < i)
    {
        node = node->next_;
        ++j;
    }

    if (!node->next_ || j > i)
    {
        return node->data_;
    }
    else 
    {
        return node->next_->data_ ;
    }
}

// 单链表简单迭代器
template<typename T>
inline
void LinkList<T>::iterator_begin(size_t i)
{
    Node *node = head_.next_;
    size_t j = 1;
    while (node && j < i)
    {
        node = node->next_;
        ++j;
    }
    if (!node || j > i)
    {
        iterator_node_ = NULL;
    }
    else 
    {
        iterator_node_ = node;
    }
}
template<typename T>
inline
bool LinkList<T>::iterator_end() const 
{
    if (iterator_node_ == NULL)
    { 
        return true; 
    }
    else  
    { 
        return false;             
    }
}
// 得到当前节点的值，并移到下一节点
template<typename T>
typename LinkList<T>::iterator LinkList<T>::iterator_next()
{
    if (iterator_end())
    {
        return NULL;
    }
    else 
    {
        T *t = &iterator_node_->data_;
        iterator_node_ = iterator_node_->next_;
        return t;
    }
}
// 反转链表
template<typename T>
inline
void LinkList<T>::reverse()
{
    Node *list = head_.next_;
    Node *head = NULL;
    Node *next;

    for (; list; list = next)
    {
        next = list->next_;
        list->next_ = head;
        head = list;
    }

    head_.next_ = head;
}
template<typename T>
inline
size_t LinkList<T>::size() const 
{
    size_t cnt = 0;
    Node *node = head_.next_;
    while (node)
    {
        ++cnt;
        node = node->next_;
    }
    return cnt;
}
template<typename T>
void LinkList<T>::clear()
{
    while (head_.next_)
    {
        Node *tmp = head_.next_;
        head_.next_ = tmp->next_;
        delete tmp;
    }
    head_.next_ = NULL;
}


#endif // !LINKLIST_H
