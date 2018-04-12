

#include "LinkList.h"

#include <iostream>


int main(void)
{

    LinkList<int> l1;

    std::cout << "list size: " << l1.size() << std::endl;

    l1.push(2);
    l1.push(6);
    l1.push(1);
    std::cout << "list size: 3 --> " << l1.size() << "\n";
    l1.insert(8,8);
    std::cout << "list insert(8,8) get(size): 8 --> " << l1.get(l1.size()) << "\n";

    std::cout << "list get(2): 6 --> " << l1.get(2) << "\n";

    //std::cout << "list find(6): true -->  " << (l1.find(6) == 0 ? "false" : "true") << "\n";

    //int ret = l1.deletel(0);
    //std::cout << "list deletel(0) value: 0 -->  " << ret << "\n";

    l1.clear();
    std::cout << "list clear size: 0 --> " << l1.size() << "\n";

    return 0;
}