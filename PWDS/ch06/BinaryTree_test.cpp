

#include "BinaryTree.h"

#include <string>

int main()
{
    BinaryTree<char> bt;
    //std::string strbt = "EDBA##C###HF#G###";
    bt.create();
    bt.preOrderRecursive();
    std::cout << "\n";
    bt.preOrderLoop();
    std::cout << "\n";
    bt.preOrderLoopTwo();
    std::cout << "\n";

    bt.midOrderLoop();
    std::cout << "\n";
    bt.afterOrderLoop();
    std::cout << "\n";
    bt.levelOrderLoop();
    std::cout << "\n";

    std::cout << "count: " << bt.countRecursive() << " " << bt.countLoop() << "\n";
    std::cout << "height: " << bt.height() << "\n";
    return 0;
}