
#include "ThreadBinaryTree.h"

#include <string>

int main()
{
    ThreadBinaryTree<char> bt;
    //std::string strbt = "EDBA##C###HF#G###";
    bt.create();
    
    bt.inThreading();
    std::cout << "\n";
    return 0;
}