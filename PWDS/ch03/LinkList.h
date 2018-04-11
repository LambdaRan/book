

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
        while (head_.next_)
        {
            Node *tmp = head_.next_;
            head_.next_ = tmp->next_;
            delete tmp;
        }
    }

    void push(T value)
    {
        Node *tmp = new Node(value);
        tmp->next_ = head_.next_;
        head_.next_ = tmp;
    }

    void append(T value)
    {

    }

    T pop()
    {
        Node *tmp = head_.next_;
        head_.next_ = tmp->next_;
        T t = tmp->data_;
        delete tmp;
        return t;
    }

    void reverse()
    {

    }

    size_t length() const 
    {

    }

    void clear()
    {

    }


private:
    struct Node 
    {
        Node(T valude)
            : data_(valud), next_(nullptr)
        {}

        T data_;
        Node *next_;
    };

    // 栈空间 头节点
    Node head_;
};


#endif // !LINKLIST_H
