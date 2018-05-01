

#include "BinaryTree.h"

#include <string>

int main()
{
    BinaryTree<char> bt;
    //std::string strbt = "EDBA##C###HF#G###";
    bt.create();
    bt.preOrderRecursive();
    bt.preOrderLoop();

    return 0;
}