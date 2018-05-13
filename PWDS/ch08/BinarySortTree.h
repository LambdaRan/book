
#ifndef BINARYSORTTREE_H
#define BINARYSORTTREE_H

// 时间复杂度 均匀分布时 O(log2(n))
// 最坏情况： 有序（斜树） O（n）


#include <assert.h>
//#include <stdio.h>
#include <iostream>
#include <stack>

template<typename T>
class BinarySortTree 
{
public: 
    BinarySortTree()
        : header_(NULL)
    {}
    ~BinarySortTree()
    {
        _lastRecursive(header_);
        header_ = NULL;
    }

    // 前向声明
    //struct Node;
    //Node* searchRecursiveBST(const T& value);
    bool searchRecursiveBST(const T& value);
    bool searchLoopBST(const T& value);
    void insertBST(const T& value);

    void deleteBST(const T& value);

    void midOrderLoop() const;

private:
   struct Node 
   {
        explicit Node(const T& value)
            : data_(value), lchild_(NULL), rchild_(NULL)
        {}

        T data_;
        Node *lchild_;
        Node *rchild_;
   };

private: 
    BinarySortTree(const BinarySortTree&);
    BinarySortTree& operator=(const BinarySortTree&);

    bool _searchRecursiveBST(Node* t, const T& value, Node* f, Node** p);
    bool _searchLoopBST(const T& value, Node** p);
    void _insertBST(Node** t, const T& value);
    void _lastRecursive(Node *t);
    void _visit(Node *t) const;
    void _deleteNode(Node** t);
    void _deleteBST(Node** t, const T& value);

    Node *header_;        
};

// 递归查找二叉排序中是否存在value
// t 当前结点   value：要查找的值
// f 双亲结点   p 指向查找到的结点
template<typename T>
bool BinarySortTree<T>::_searchRecursiveBST(Node* t, const T& value, Node* f, Node** p)
{
    if (!t)
    {
        *p = f;
        return false;
    }
    else if (value == t->data_) // 假设类型T支持关系运算符
    {
        *p = t;
        return true;
    }
    else if (value < t->data_)
    {
        return _searchRecursiveBST(t->lchild_, value, t, p);
    }
    else  
    {
        return _searchRecursiveBST(t->rchild_, value, t, p);
    }
}
template<typename T>
bool BinarySortTree<T>::searchRecursiveBST(const T& value)
{
    Node *p = NULL;
    return _searchRecursiveBST(header_, value, NULL, &p);
    // bool ret = _searchRecursiveBST(header_, value, NULL, &p);
    // if (ret)
    //     std::cout << "searchRecursiveBST: find " << p->data_ << "\n";    
    // return ret;
}
template<typename T>
bool BinarySortTree<T>::_searchLoopBST(const T& value, Node** p)
{
    *p = header_;
    if ((*p) != NULL)
    {
        if (value == (*p)->data_)
        {
            return true;
        }
        else  
        {
            Node* cur = NULL;
            if (value < (*p)->data_)
                cur = (*p)->lchild_;
            else  
                cur = (*p)->rchild_;
            while (cur != NULL)
            {
                *p = cur;
                if (value == cur->data_)
                {
                    return true;
                }
                else if (value < cur->data_)
                {
                    cur = cur->lchild_;
                }
                else  
                {
                    cur = cur->rchild_;
                }
            }
            return false;            
        }
    }
    return false;
}
template<typename T>
bool BinarySortTree<T>::searchLoopBST(const T& value)
{
    Node* p = NULL;
    return _searchLoopBST(value, &p);
    // bool ret = _searchLoopBST(value, &p);
    // if (ret)
    //     std::cout << "searchLoopBST: find " << p->data_ << "\n";    
    // return ret;
}
template<typename T>
void BinarySortTree<T>::_insertBST(Node** t, const T& value)
{
    Node* p = NULL;
    Node* s = NULL;
    if (!_searchRecursiveBST(*t, value, NULL, &p)) // 查找不成功
    {
        s = new Node(value);
        assert(s);
        if (!p) 
        {
            *t = s; // 插入s为新结点
        }
        else if (value < p->data_)
        {
            p->lchild_ = s;
        }
        else  
        {
            p->rchild_ = s;
        }
    }
}
template<typename T>
void BinarySortTree<T>::insertBST(const T& value)
{
    _insertBST(&header_, value);
}

template<typename T>
void BinarySortTree<T>::_lastRecursive(Node *t)
{
    if (t == NULL)
        return;
    _lastRecursive(t->lchild_);
    _lastRecursive(t->rchild_);
    delete t;
    t = NULL;
}
template<typename T>
inline
void BinarySortTree<T>::_visit(Node *t) const
{
    assert(t != NULL);
    //printf("%d", t->data_);
    std::cout << t->data_ << " ";

}
template<typename T>
void BinarySortTree<T>::_deleteNode(Node** t)
{
    Node* q = *t;;
    if ((*t)->rchild_ == NULL) // 右子树为空，只需重接它的左子树
    {
        *t = (*t)->lchild_;
        delete q;
    }
    else if ((*t)->lchild_ == NULL) // 左子树为空，只需重接它的右子树
    {
        *t = (*t)->rchild_;
        delete q;        
    }
    else // 左右子树都不空  
    {
        Node *s = (*t)->lchild_;
        while (s->rchild_) // 转左，然后找t结点中序遍历的前驱结点
        {
            q = s;  // q 指向 s 结点的前驱结点
            s = s->rchild_;
        }
        (*t)->data_ = s->data_; // s 指向被删除节点的直接前驱
        if (q != (*t))
            q->rchild_ = s->lchild_; // 重接q的右子树
        else  
            q->lchild_ = s->lchild_; // 重接q的左子树

        delete s;
    }
}
template<typename T>
void BinarySortTree<T>::_deleteBST(Node** t, const T& value)
{
    if (!*t)
        return ;
    else  
    {
        if (value == (*t)->data_)
        {
            _deleteNode(t);
        }
        else if (value < (*t)->data_)
        {
            _deleteBST(&(*t)->lchild_, value);
        }
        else  
        {
            _deleteBST(&(*t)->rchild_, value);
        }
    }
}
template<typename T>
void BinarySortTree<T>::deleteBST(const T& value)
{
    _deleteBST(&header_, value);
}
template<typename T>
void BinarySortTree<T>::midOrderLoop() const
{
    std::stack<Node*> stk;
    Node *cur = header_;
    while (cur != NULL || !stk.empty())
    {
        while (cur != NULL)
        {
            stk.push(cur);
            cur = cur->lchild_;
        }

        if (!stk.empty())
        {
            cur = stk.top();
            stk.pop();
            _visit(cur);
            cur = cur->rchild_;
        }
    }
}
#endif // !BINARYSORTTREE_H
