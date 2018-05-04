

#ifndef THREADBINARYTREE
#define THREADBINARYTREE

// 线索二叉树
// n个节点的二叉树，有2n个指针域，n-1条分支，（2n-（n-1））=n+1个空指针域


template<typename T>
class ThreadBinaryTree 
{
public: 
    ThreadBinaryTree()
        : header_(NULL)
    {}

    // 中序遍历线索化
    void inThreading() const;

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

    // 中序遍历线索化
    void _inThreading(BiThrNode **pre, BiThrNode *cur) const;
private:
    BiThrNode *header_;
};

// pre 始终指向刚刚访问过的结点
// cur 当前结点
template<typename T>
void ThreadBinaryTree<T>::_inThreading(BiThrNode **pre, BiThrNode *cur) const
{
    if (cur)
    {
        _inThreading(pre, cur->lchild_); // 递归左子树线索化
        if (cur->lchild_ == NULL) // 没有左子树
        {
            cur->ltag_ = true; // 前驱线索
            cur->lchild_ = *pre; // 左孩子指针指向前驱
        }

        if ((*pre)->rchild_ == NULL) // 前驱没有右孩子
        {
            (*pre)->rtag_ = true; // 后继线索
            (*pre)->rchild_ = cur; // 前驱右孩子指针指向后继（当前结点cur）
        }
        *pre = cur;
        _inThreading(pre, cur->rchild_); // 递归右子树线索化
    }
}
template<typename T>
void ThreadBinaryTree<T>::inThreading() const
{
    BiThrNode *mpre = NULL;
    _inThreading(&mpre, header_);
}


#endif // !THREADBINARYTREE