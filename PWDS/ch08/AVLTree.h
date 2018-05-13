

#ifndef AVLTREE_H
#define AVLTREE_H

#include <assert.h>

// 插入结点后，最小不平衡子树的BF（balance factor）与它的子树的BF符号相反时，
// 就需要对结点先进行一次旋转以使得符号相同后，再反旋转一次才能完成平衡操作。


template<typename T>
class AVLTree 
{
public: 
    AVLTree()
        : header_(NULL)
    {}
    ~AVLTree()
    {
        //_lastRecursive(header_);
        header_ = NULL;
    }
    
    // 创建AVL
    void insertAVL(const T& value);
private:
    struct Node 
    {
        explicit Node(const T& value)
            : data_(value), bf_(0), lchild_(NULL), rchild_(NULL)
        {}

        T data_;
        int bf_;
        Node *lchild_;
        Node *rchild_;
    };
    // const int LH = 1; // 左高
    // const int EH = 0; // 等高
    // const int RH = -1; // 右高
    enum 
    {
        LH = 1, // 左高
        EH = 0, // 等高
        RH = -1, // 右高
    };
private: 
    AVLTree(const AVLTree&);
    AVLTree& operator=(const AVLTree&);

    // 右旋
    void _r_rotate(Node** p);
    // 左旋
    void _l_rotate(Node** p);
    // 左平衡处理
    void _leftBalence(Node** t);
    // 右平衡处理
    void _rightBalence(Node** t);
    // 构建平衡二叉树
    bool _insertAVL(Node** t, const T& value, int* taller);

    Node *header_;          
};

template<typename T>
inline
void AVLTree<T>::_r_rotate(Node** p)
{
    Node* l = (*p)->lchild_; // l 指向P的左子树
    (*p)->lchild_ = l->rchild_; // l 的右子树挂接到P的左子树
    l->rchild_ = (*p);
    *p = l; // P指向新的根结点
}
template<typename T>
inline
void AVLTree<T>::_l_rotate(Node** p)
{
    Node* r = (*p)->rchild_; // r 指向P的有子树
    (*p)->rchild_ = r->lchild_; // r 的左子树挂接为P的右子树
    r->lchild_ = (*p);
    *p = r; // P指向新的根结点
}
template<typename T>
inline
void AVLTree<T>::_leftBalence(Node** t)
{
    Node* l = (*t)->lchild_;
    
    switch (l->bf_)
    {
        case LH: // 新节点插入在t的左孩子的左子树上，要做单右旋处理
            (*t)->bf_ = l->bf_ = EH;
            _r_rotate(t);
            break;
        case RH: // 新节点插入在t的左孩子的右子树上，要做双旋处理
            Node* lr = l->rchild_;
            
            switch (lr->bf_)
            {
                case LH:
                    (*t)->bf_ = RH;
                    l->bf_ = EH;
                    break;
                case EH:
                    (*t)->bf_ = l->bf_ = EH;
                    break;
                case RH:
                    (*t)->bf_ = EH;
                    l->bf_ = LH;
                    break;
                default:
                    assert(false);
                    break;
            }
            lr->bf_ = EH;
            _l_rotate(&(*t)->lchild_); // 对 T的左子树左旋平衡处理
            _r_rotate(t); // 对T做右旋平衡处理
            break;
        default:
            assert(false);
            break;
    }
}
template<typename T>
inline
void AVLTree<T>::_rightBalence(Node** t)
{
    Node* l = (*t)->lchild_;
    
    switch (l->bf_)
    {
        case LH: // 新节点插入在t的左孩子的左子树上，要做单右旋处理
            (*t)->bf_ = l->bf_ = EH;
            _r_rotate(t);
            break;
        case RH: // 新节点插入在t的左孩子的右子树上，要做双旋处理
            Node* lr = l->rchild_;
            
            switch (lr->bf_)
            {
                case LH:
                    (*t)->bf_ = RH;
                    l->bf_ = EH;
                    break;
                case EH:
                    (*t)->bf_ = l->bf_ = EH;
                    break;
                case RH:
                    (*t)->bf_ = EH;
                    l->bf_ = LH;
                    break;
                default:
                    assert(false);
                    break;
            }
            lr->bf_ = EH;
            _l_rotate(&(*t)->lchild_); // 对 T的左子树左旋平衡处理
            _r_rotate(t); // 对T做右旋平衡处理
            break;
        default:
            assert(false);
            break;
    }
}
template<typename T>
bool AVLTree<T>::_insertAVL(Node** t, const T& value, int* taller)
{
    if (!(*t))
    {
        *t = new T(value);
        *taller = 1;
    }
    else  
    {
        if (value == (*t)->data_)
        {
            // 树中已有相同值的结点则不再插入
            *taller = 0;
            return false;
        }
        else if (value < (*t)->data_)
        {
            // 在左子树中查找
            if (!_insertAVL(&(*t)->lchild_, value, taller))
                return false; //未插入
            if (*taller == 1)
            {
                
                switch ((*t)->bf_)
                {
                    case LH:
                        _leftBalence(t);
                        *taller = 0;
                        break;
                    case EH:
                        (*t)->bf_ = LH;
                        *taller = 1;
                        break;
                    case RH:
                        (*t)->bf_ = EH;
                        *taller = 0;
                        break;
                    default:
                        assert(false);
                        break;
                }
            }
        }
        else  
        {
            // 在右子树中查找
            if (!_insertAVL(&(*t)->rchild_, value, taller))
                return false; //未插入
            if (*taller == 1)
            {
                switch ((*t)->bf_)
                {
                    case LH:
                        (*t)->bf_ = EH;
                        *taller = 0;
                        break;
                    case EH:
                        (*t)->bf_ = RH;
                        *taller = 1;
                        break;
                    case RH:
                        _rightBalence(t);
                        *taller = 0;
                        break;
                    default:
                        assert(false);
                        break;
                }
            }            
        }
    }
    return true;
}
template<typename T>
void AVLTree<T>::insertAVL(const T& value)
{
    int taller = 0;
    _insertAVL(&header_, value, &taller);
}
#endif