

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <assert.h>
#include <stdio.h>

#include <iostream>
#include <stack>
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
    void preOrderRecursive() const;
    void preOrderLoop() const;

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

    void _preRecursiveCreateBinaryTree(Node **t);
    void _visit(Node *t) const;
    void _free(Node *t);
    void _preOrderRecursive(Node *h) const;

private:
    Node *header_;
};

template<typename T>
void BinaryTree<T>::_preRecursiveCreateBinaryTree(Node **t)
{
    char ch;
    //std::cin >> ch;
    scanf("%c", &ch);
    if (ch == '#')
        t = NULL;
    else  
    {
		*t = new Node(ch);
        assert(*t);

		_preRecursiveCreateBinaryTree(&(*t)->lchild_);
		_preRecursiveCreateBinaryTree(&(*t)->rchild_);        
    }
}
template<typename T>
inline
void BinaryTree<T>::_visit(Node *t) const
{
    assert(t);
    printf("%c", t->data_);
}

template<typename T>
void BinaryTree<T>::_free(Node *t)
{
    assert(t);
    delete t;
    t = NULL;
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
void BinaryTree<T>::create()
{
    _preRecursiveCreateBinaryTree(&header_);
}
template<typename T>
void BinaryTree<T>::preOrderRecursive() const
{
    _preOrderRecursive(header_);
}
template<typename T>
void BinaryTree<T>::preOrderLoop() const
{
    std::stack<Node *> treeStack;
    treeStack.push(header_);
    while (!treeStack.empty())
    {
        Node *tmp = treeStack.top();
        _visit(tmp);
		if (tmp->rchild_)
			treeStack.push(tmp->rchild_);
		if (tmp->lchild_)
			treeStack.push(tmp->lchild_); 
        treeStack.pop();       
    }
}
#endif // !BINARYTREE_H
