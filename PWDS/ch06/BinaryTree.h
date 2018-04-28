

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <assert.h>

template<typename T>
class BinaryTree 
{
public:
    

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

    Node *header_;
};

#endif // !BINARYTREE_H
