

// 线性表链式存储结构  （单链表）
// 数据类型为内建类型


#ifndef LINKLIST_H
#define LINKLIST_H

#include <stddef.h>

#include <iostream>


template<typename T>
class LinkList 
{
public: 
    //typedef T* iterator;

    LinkList()
        : head_(0), iterator_node_(NULL)
    {}

    // 释放链表
    ~LinkList()
    {
        clear();
    }

    // 头插法
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

    // 取第一个节点
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

    // 删除索引处的节点
    void deletel(size_t i, T &ret)
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
    T get(size_t i)
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
    void iterator_init(size_t i = 1)
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
            //std::cout << "iterator_init NULL" << "\n";
        }
        else 
        {
            iterator_node_ = node;
            //std::cout << "iterator_init " << iterator_node_->data_ << "\n";
        }
    }

    bool iterator_end() const 
    {
        if (iterator_node_ == NULL)
        {
            //std::cout << " NULL " ;  
            return true; 
        }
        else  
        {
            //std::cout << " NotNULL " ;  
            return false;             
        }
    }
    // 得到当前节点的值，并移到下一节点
    T *iterator_next()
    {
        if (iterator_end())
        {
            //std::cout << " next NULL " ;
            return NULL;
        }
        else 
        {
            T *t = &iterator_node_->data_;
            iterator_node_ = iterator_node_->next_;
            //std::cout << " next Not NULL " << *t << " " ;
            return t;
        }
    }
    // 反转链表
    void reverse()
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
        head_.next_ = NULL;
    }


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


#endif // !LINKLIST_H
