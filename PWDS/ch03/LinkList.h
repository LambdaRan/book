

// 线性表链式存储结构  （单链表）
// 数据类型为内建类型


#ifndef LINKLIST_H
#define LINKLIST_H

#include <stddef.h>

template<typename T>
class LinkList 
{
public: 
    LinkList()
        : head_(0)
    {}

    // 释放链表
    ~LinkList()
    {
        clear();
    }

    void push(T value)
    {
        Node *tmp = new Node(value);
        tmp->next_ = head_.next_;
        head_.next_ = tmp;
    }

    void append(T value)
    {
        Node *node = &head_;
        while (node->next_)
        {
            node = node->next_;
        }

        Node *tmp = new Node(value);
        node->next_ = tmp;
    }

    T pop()
    {
        Node *tmp = head_.next_;
        head_.next_ = tmp->next_;
        T t = tmp->data_;
        delete tmp;
        return t;
    }

    // 如果索引大于链表大小 直接把新节点插入链尾
    void insert(size_t i, T value)
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

    T get(size_t i)
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
            return 0;
        }

        return node->data_;
    }

    void reverse()
    {

    }

    size_t size() const 
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

    void clear()
    {
        while (head_.next_)
        {
            Node *tmp = head_.next_;
            head_.next_ = tmp->next_;
            delete tmp;
        }
    }


private:
    struct Node 
    {
        Node(T value)
            : data_(value), next_(nullptr)
        {}

        T data_;
        Node *next_;
    };

    // 栈空间 头节点
    Node head_;
};


#endif // !LINKLIST_H
