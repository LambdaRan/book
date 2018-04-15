
// 静态链表: 用数组描述的链表 (游标实现法)

// 未被使用的数组元素为备用链表
// 数组第一个元素（下标为0）的cur 存放备用链表的第一个节点的下标
// 数组最后一个元素的cur用来存放第一个插入元素的下标，相当于头节点
// 已存储数据的最后一个元素的cur的值为0




#ifndef STATICLIST_H
#define STATICLIST_H

#include <stddef.h>
#include <assert.h>

template<typename T, size_t S>
class StaticList 
{
public: 
    StaticList()
        : size_(0), capcity_(S)
    {
        _init();
    }
    ~StaticList()
    {
        clear();
    }
    // 在第i个元素之前插入新的元素
    // 如果i大于已存储节点的下标，则存储在最后
    // 成功返回true否则false  
    bool insert(size_t i, const T &value); 

    // 删除第i个元素,如果i大于size则不删除任何元素
    void deletel(size_t i, T &ret);

    void push(const T &value);
    void push_back(const T &value);
    // 如果 i 大于size，返回最后一个元素的值
    T& get(size_t i);    
    // 清空链表
    void clear()
    {
        _init();
        size_ = 0;
    }
    size_t size() const 
    {
        return size_;
    }

    // 迭代器


private:
    struct Component
    {
        Component()
            : cur_(0)
        {}

        T data_; // 数据
        size_t cur_; // 游标，为0表示无指向
    };

    void _init();
    // 若备用链表非空，则返回分配的节点下标，否则返回0
    size_t _malloc_sl();
    void _free_sl(size_t i);

    size_t size_;
    size_t capcity_;
    Component container_[S];
};

template<typename T, size_t S>
inline
void StaticList<T,S>::_init()
{
    for (size_t i = 0; i < capcity_-1; ++i)
    {
        container_[i].cur_ = i + 1;
    }
    container_[capcity_-1].cur_ = 0;        
}
template<typename T, size_t S>
inline
size_t StaticList<T,S>::_malloc_sl()
{
    size_t i = container_[0].cur_;
    if (container_[0].cur_) // 备用链表不空
    {
        container_[0].cur_ = container_[i].cur_;
    }
    return i;
}
template<typename T, size_t S>
inline
void StaticList<T,S>::_free_sl(size_t i)
{
    assert(i <= capcity_-1);

    container_[i].cur_ = container_[0].cur_;
    container_[0].cur_ = i;
}

template<typename T, size_t S>
inline
bool StaticList<T,S>::insert(size_t i, const T &value)
{
    if (i < 1)
    {
        return false;
    }
    if (i > size_+1)
    {
        push_back(value);
        return true;
    }
    size_t k = capcity_ - 1;// 头节点下标
    size_t j = _malloc_sl();
    if (j)
    {
        container_[j].data_ = value;
        for (size_t l = 1; l <= i-1; ++l)
        {
            k = container_[k].cur_;
        }
        container_[j].cur_ = container_[k].cur_;
        container_[k].cur_ = j;
        ++size_;

        return true;
    }
    return false;
}

template<typename T, size_t S>
inline
void StaticList<T,S>::deletel(size_t i, T &ret)
{
    if (i < 1 || i > size_+1)
    {
        return ;
    }
    size_t k = capcity_ - 1;// 头节点下标
    for (size_t j = 0; j <= i-1; ++j)
    {
        k = container_[k].cur_;
    }

    size_t j = container_[k].cur_;
    container_[k].cur_ = container_[j].cur_;
    ret = container_[j].data_;
    _free_sl(j);
    --size_;
}

template<typename T, size_t S>
inline
void StaticList<T,S>::push(const T &value)
{
    size_t j = _malloc_sl();
    if (j) // 头插法插入元素
    {
        container_[j].data_ = value;
        container_[j].cur_ = container_[capcity_ - 1].cur_;
        container_[capcity_ - 1].cur_ = j;
        ++size_;
    }
}
template<typename T, size_t S>
inline
void StaticList<T,S>::push_back(const T &value)
{
    size_t j = _malloc_sl();
    if (j) // 插到最后
    {
        size_t k = capcity_ - 1;
        while (container_[k].cur_)
        {
            k = container_[k].cur_;
        }
        container_[j].data_ = value;
        container_[k].cur_ = j;
        ++size_;
    }
}
template<typename T, size_t S>
inline
T& StaticList<T,S>::get(size_t i)
{
    assert(i <= size_);

    //int k = container_[capcity_ - 1].cur_;
    int k = capcity_ - 1;
    int j = 1;
    //while (k && j < i)
    while (container_[k].cur_ && j < i)
    {
        k = container_[k].cur_;
        ++j;
    }
    if (container_[k].cur_ == 0 || j > i)
    {
        return container_[k].data_;
    }
    else  
    {
        return container_[container_[k].cur_].data_;
    }
}

#endif // !STATICLIST_H
