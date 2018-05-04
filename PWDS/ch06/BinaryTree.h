

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <assert.h>
#include <stdio.h>

#include <iostream>
#include <stack>
#include <queue>
//#include <string>

template<typename T>
class BinaryTree 
{
public:
    BinaryTree()
        : header_(NULL)
    {}
    ~BinaryTree()
    {}


    void create();
    // 先序递归遍历二叉树
    void preOrderRecursive() const;
    void preOrderLoop() const;
    void preOrderLoopTwo() const;

    // 中序与后序递归遍历二叉树可参考先序遍历

    // 中序遍历二叉树
    //void midOrderRecursive() const;
    void midOrderLoop() const;

    // 后序遍历二叉树
    //void afterOrderRecursive() const;
    void afterOrderLoop() const;

    // 层序遍历
    void levelOrderLoop() const;

    // 树的结点个数
    int countRecursive() const;
    int countLoop() const;

    // 树的高度
    int height() const;

private:
    struct Node 
    {
        explicit Node(const T &value)
            : data_(value), lchild_(NULL), rchild_(NULL)
        {}

        T data_;
        Node *lchild_;
        Node *rchild_;
    };

private:
    BinaryTree(const BinaryTree&);
    BinaryTree& operator=(const BinaryTree&);

    Node* _preRecursiveCreateBinaryTree();
    void _visit(Node *t) const;
    void _free(Node *t);
    void _preOrderRecursive(Node *h) const;
    int _countRecursive(Node *t) const;
    int _height(Node *) const;

private:
    Node *header_;
};

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::_preRecursiveCreateBinaryTree()
{
    char ch;
    Node *t = NULL;
    scanf("%c", &ch);
    if (ch == '#')
        t = NULL;
    else  
    {
		t = new Node(ch);
        assert(t != NULL);

		t->lchild_ = _preRecursiveCreateBinaryTree();
		t->rchild_ = _preRecursiveCreateBinaryTree();        
    }
    return t;
}
template<typename T>
inline
void BinaryTree<T>::_visit(Node *t) const
{
    assert(t != NULL);
    printf("%c", t->data_);
}

template<typename T>
void BinaryTree<T>::_free(Node *t)
{
    assert(t != NULL);
    delete t;
    t = NULL;
}
template<typename T>
void BinaryTree<T>::create()
{
    header_ = _preRecursiveCreateBinaryTree();
}

// 先序遍历二叉树（递归实现）
template<typename T>
void BinaryTree<T>::_preOrderRecursive(Node *h) const
{
	if (h == NULL) 
		return;
	_visit(h); 
	_preOrderRecursive(h->lchild_);
	_preOrderRecursive(h->rchild_);
}
template<typename T>
void BinaryTree<T>::preOrderRecursive() const
{
    _preOrderRecursive(header_);
}
// 先序遍历
template<typename T>
void BinaryTree<T>::preOrderLoop() const
{
    std::stack<Node *> treeStack;
    treeStack.push(header_);
    while (!treeStack.empty())
    {
        Node *tmp = treeStack.top();
        treeStack.pop();
        _visit(tmp);
		if (tmp->rchild_ != NULL)
			treeStack.push(tmp->rchild_);
		if (tmp->lchild_ != NULL)
			treeStack.push(tmp->lchild_); 
    }
}
template<typename T>
void BinaryTree<T>::preOrderLoopTwo() const
{
    std::stack<Node *> stk;
    Node *cur = header_;
    while (cur != NULL || !stk.empty())
    {
        while (cur != NULL)
        {
            _visit(cur);
            stk.push(cur);
            cur = cur->lchild_;
        }
        if (!stk.empty())
        {
            cur = stk.top();
            stk.pop();
            cur = cur->rchild_;
        }
    }
}

// 中序遍历
template<typename T>
void BinaryTree<T>::midOrderLoop() const
{
    std::stack<Node *> stk;
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

// 后序遍历
template<typename T>
void BinaryTree<T>::afterOrderLoop() const
{
    std::stack<Node *> stk;
    Node *cur = header_; // 指向当前要检查的节点  
    Node *preVisit = NULL; // 指向前一个被访问的节点 

    while (cur != NULL || !stk.empty())
    {
        while (cur != NULL) // 一直向左走直到为空  
        {
            stk.push(cur);
            cur = cur->lchild_;
        }
        cur = stk.top();
        // 当前节点的右孩子如果为空或者已经被访问，则访问当前节点
        if (cur->rchild_ == NULL || cur->rchild_ == preVisit)
        {
            _visit(cur);
            preVisit = cur;
            stk.pop();
            cur = NULL;
        }
        else  
        {
            cur = cur->rchild_;
        }
    }        
}

// 层序遍历
template<typename T>
void BinaryTree<T>::levelOrderLoop() const
{
    std::queue<Node*> que;
    Node *cur = header_;
    if (cur != NULL)
        que.push(cur);
    while (!que.empty())
    {
        cur = que.front();
        que.pop();
        _visit(cur);
        if (cur->lchild_ != NULL)
            que.push(cur->lchild_);
        if (cur->rchild_ != NULL)
            que.push(cur->rchild_);
    }
}

// 统计树的结点个数
template<typename T>
int BinaryTree<T>::_countRecursive(Node *t) const
{
    if (t == NULL)
        return 0;
    return _countRecursive(t->lchild_) + _countRecursive(t->rchild_) + 1;
}
template<typename T>
inline
int BinaryTree<T>::countRecursive() const
{
    return _countRecursive(header_);
}
// 非递归　利用层次遍历计算节点个数或其他非递归遍历算法
template<typename T>
int BinaryTree<T>::countLoop() const
{
	int count = 0;
    std::queue<Node*> que;
    Node *cur = header_;
    if (cur != NULL)
        que.push(cur);
    while (!que.empty())
    {
        cur = que.front();
        que.pop();
        ++count;
        if (cur->lchild_ != NULL)
            que.push(cur->lchild_);
        if (cur->rchild_ != NULL)
            que.push(cur->rchild_);
    }    
	return count;
}
// 递归计算高度
template<typename T>
int BinaryTree<T>::_height(Node *h) const
{
	int u, v;
	if (h == NULL)
		return -1;
	u = _height(h->lchild_);
	v = _height(h->rchild_);
	return u > v ? u+1 : v+1;
}
template<typename T>
inline
int BinaryTree<T>::height() const
{
    return _height(header_);
}
#endif // !BINARYTREE_H
