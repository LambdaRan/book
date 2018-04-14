

#include "List_v0.h"
#include <iostream>


int main(void)
{
    std::cout << "Test list" << std::endl;

    List_v0<int, 32> l1;
    std::cout << "list size: " << l1.size() << " capcity: " << l1.capcity() << std::endl;

    l1.push(2);
    l1.push(6);
    l1.push(1);
    std::cout << "list size: 3 --> " << l1.size() << "\n";

    l1.insert(0, 0);
    std::cout << "list get(0): 0 --> " << l1.get(0) << "\n";

    std::cout << "list find(6): true -->  " << (l1.find(6) == 0 ? "false" : "true") << "\n";

    int ret;
    l1.deletel(0, ret);
    std::cout << "list deletel(0) value: 0 -->  " << ret << "\n";

    l1.clear();
    std::cout << "list clear size: 0 --> " << l1.size() << "\n";
    return 0;
}