

#include "BinarySortTree.h"

#include <iostream>

int main(void)
{
    int a[] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
    BinarySortTree<int> bst;
    for (std::size_t i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
    {
        bst.insertBST(a[i]);
    }
    std::cout << "\n";
    bst.midOrderLoop();
    std::cout << "\n";

    std::cout << "find 35 : " << (bst.searchRecursiveBST(35) ? "true" : "false") << std::endl; 
    bst.deleteBST(35);
    std::cout << "find 35 : " << (bst.searchLoopBST(35) ? "true" : "false") << std::endl; 
    return 0;
}