
#include "ThreadBinaryTree.h"

#include <iostream>

//#include <string>

int main()
{
    ThreadBinaryTree<char> bt;
    //std::string strbt = "EDBA##C###HF#G###";
    bt.create();

    //bt.inThreading();
    bt.inThreadingLoop();
    bt.inOrderTraverse_Thr();
    std::cout << "\n";
    return 0;
}