

#ifndef THREADBINARYTREE
#define THREADBINARYTREE

// 线索二叉树
// n个节点的二叉树，有2n个指针域，n-1条分支，（2n-（n-1））=n+1个空指针域
#include <assert.h>

#include <iostream>

template<typename T>
class ThreadBinaryTree 
{
public: 
    ThreadBinaryTree()
        : header_(NULL), headerNode_(0)
    {}

    // ~ThreadBinaryTree()
    // {
    //     _lastRecursiveClear(header_);
    // }

    void create();
    // 中序遍历线索化
    void inThreading();



private: 
    struct BiThrNode
    {
        BiThrNode(const T& value)
            :data_(value),lchild_(NULL), rchild_(NULL), ltag_(false), rtag_(false)
        {}
        T data_;
        BiThrNode *lchild_;
        BiThrNode *rchild_;

        bool ltag_; // 为0指向左孩子，为1指向前驱
        bool rtag_; // 上同
    };

    ThreadBinaryTree(const ThreadBinaryTree&);
    ThreadBinaryTree& operator=(const ThreadBinaryTree&);

    BiThrNode* _preRecursiveCreateBinaryTree();
    void _free(BiThrNode *t);
    void _lastRecursiveClear(BiThrNode *h);
    // 中序遍历线索化
    void _inThreading(BiThrNode **pre, BiThrNode *cur) const;
private:
    BiThrNode *header_; // 头指针
    //BiThrNode *root_; // 头指针
    BiThrNode headerNode_; // 头结点  
};

template<typename T>
void ThreadBinaryTree<T>::_free(BiThrNode *t)
{
    assert(t != NULL);
    delete t;
    t = NULL;
}
// 后序清空二叉树
template<typename T>
void ThreadBinaryTree<T>::_lastRecursiveClear(BiThrNode *h)
{
	if (h == NULL) 
		return;
	_lastRecursiveClear(h->lchild_);
	_lastRecursiveClear(h->rchild_);
	_free(h);     
}
template<typename T>
typename ThreadBinaryTree<T>::BiThrNode* ThreadBinaryTree<T>::_preRecursiveCreateBinaryTree()
{
    char ch;
    BiThrNode *t = NULL;
    scanf("%c", &ch);
    if (ch == '#')
        t = NULL;
    else  
    {
		t = new BiThrNode(ch);
        assert(t != NULL);

		t->lchild_ = _preRecursiveCreateBinaryTree();
		t->rchild_ = _preRecursiveCreateBinaryTree();        
    }
    return t;
}
template<typename T>
void ThreadBinaryTree<T>::create()
{
    header_ = _preRecursiveCreateBinaryTree();
}
// pre 始终指向刚刚访问过的结点
// cur 当前结点
template<typename T>
void ThreadBinaryTree<T>::_inThreading(BiThrNode **pre, BiThrNode *cur) const
{
    if (cur != NULL)
    {
        _inThreading(pre, cur->lchild_); // 递归左子树线索化
        //assert(cur != NULL);
        if (cur->lchild_ == NULL) // 没有左子树
        {
            cur->ltag_ = true; // 前驱线索
            cur->lchild_ = (*pre); // 左孩子指针指向前驱
        }

        //assert(pre_ != NULL);
        if ((*pre)->rchild_ == NULL) // 前驱没有右孩子
        {
            (*pre)->rtag_ = true; // 后继线索
            (*pre)->rchild_ = cur; // 前驱右孩子指针指向后继（当前结点cur）
        }

        (*pre) = cur;
        _inThreading(pre, cur->rchild_); // 递归右子树线索化
    }
}
template<typename T>
void ThreadBinaryTree<T>::inThreading()
{
    BiThrNode *mpre = &headerNode_;
    _inThreading(&mpre, header_);
    std::cout << " inThreading: mpre " << mpre->data_ << "\n";
}


#endif // !THREADBINARYTREE