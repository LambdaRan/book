

#ifndef THREADBINARYTREE
#define THREADBINARYTREE

// 线索二叉树
// n个节点的二叉树，有2n个指针域，n-1条分支，（2n-（n-1））=n+1个空指针域
#include <assert.h>
#include <stdio.h>

#include <stack>

template<typename T>
class ThreadBinaryTree 
{
public: 
    ThreadBinaryTree()
        : header_(NULL), headerNode_(0)
    {}

    ~ThreadBinaryTree()
    {
        _clear();
    }

    void create();
    // 中序遍历线索化
    void inThreading();
    void inThreadingLoop();
    // 遍历线索二叉树
    void inOrderTraverse_Thr() const;



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
    void _visit(BiThrNode *t) const;
    void _free(BiThrNode *t);
    void _clear();
    // 中序遍历线索化
    void _inThreadingRecursive(BiThrNode **pre, BiThrNode *cur) const;
    // 中序遍历
    void _inOrderTraverse_Thr(const BiThrNode *t) const;
private:
    BiThrNode *header_; // 头指针
    BiThrNode headerNode_; // 头结点  
};
template<typename T>
inline
void ThreadBinaryTree<T>::_visit(BiThrNode *t) const
{
    assert(t != NULL);
    printf("%c", t->data_);
}

template<typename T>
void ThreadBinaryTree<T>::_free(BiThrNode *t)
{
    assert(t != NULL);
    delete t;
    t = NULL;
}
// 后序清空二叉树
template<typename T>
void ThreadBinaryTree<T>::_clear()
{
    BiThrNode *pheader = &headerNode_;
    while (header_ != pheader)
    {
        BiThrNode *tmp = header_;
        header_ = header_->rchild_;
        _free(tmp);
    }
    header_ = NULL;
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
void ThreadBinaryTree<T>::_inThreadingRecursive(BiThrNode **pre, BiThrNode *cur) const
{
    if (cur != NULL)
    {
        _inThreadingRecursive(pre, cur->lchild_); // 递归左子树线索化
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
        _inThreadingRecursive(pre, cur->rchild_); // 递归右子树线索化
    }
}
template<typename T>
void ThreadBinaryTree<T>::inThreadingLoop()
{
    std::stack<BiThrNode *> stk;
    BiThrNode *pre = &headerNode_;
    pre->lchild_ = header_;
    BiThrNode *cur = header_;
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
            // 线索化
            if (cur->lchild_ == NULL)
            {
                cur->ltag_ = true;
                cur->lchild_ = pre;
            }
            if (pre->rchild_ == NULL)
            {
                pre->rtag_ = true;
                pre->rchild_ = cur;
            }
            pre = cur;

            cur = cur->rchild_;
        }
    }

    pre->rtag_ = true;
    pre->rchild_ = &headerNode_;

    headerNode_.rtag_ = true;
    headerNode_.rchild_ = pre;
}
template<typename T>
void ThreadBinaryTree<T>::inThreading()
{
    BiThrNode *mpre = &headerNode_;
    mpre->lchild_ = header_;
    _inThreadingRecursive(&mpre, header_);

    mpre->rtag_ = true;
    mpre->rchild_ = &headerNode_;

    headerNode_.rtag_ = true;
    headerNode_.rchild_ = mpre;
}

// 中序遍历二叉线索链表表示的二叉树
// t 为头结点
template<typename T>
void ThreadBinaryTree<T>::_inOrderTraverse_Thr(const BiThrNode *t) const
{

    BiThrNode *p = t->lchild_; // p 指向根节点
    while (p != t) // 空树或遍历结束时，p == t
    {
        while (p->ltag_ == false) // 当ltag == false时循环到中序序列的第一个结点
            p = p->lchild_;
        _visit(p);

        while (p->rtag_ == true && p->rchild_ != t)
        {
            p = p->rchild_;
            _visit(p);
        }

        p = p->rchild_; // p指向其右子树
    }
}
template<typename T>
void ThreadBinaryTree<T>::inOrderTraverse_Thr() const
{
    _inOrderTraverse_Thr(&headerNode_);
}
#endif // !THREADBINARYTREE