

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
    std::cout << "list pop(): 1 --> " << l1.pop() << "\n";
    int ret;
    l1.deletel(1, ret);
    std::cout << "list deletel(1): 6 --> " << ret << "\n";
    l1.append(9);
    std::cout << "list append(9): 9 --> " << l1.get(l1.size()) << "\n";

    int *iter;
    int count = 0;
    l1.iterator_init(1);
    //for (l1.iterator_init(1); l1.iterator_end(); )

    if (l1.iterator_end())
    {
        std::cout << "list iterator_end NULL" << "\n";
    } 
    else  
    {
        std::cout << "list iterator_end Not NULL" << "\n";
        iter = l1.iterator_next();
        std::cout << "list next " << *iter << "\n";
        for (int i = 0; i < 2; ++i)
        {
            iter = l1.iterator_next();
            if (iter != NULL)
             std::cout << "list next " << *iter << "\n";
            else 
                break;
        }
    }
    // while (l1.iterator_end())
    // {
    //     ++count;
    //     std::cout << " count:" << count << " ";
    //     iter = l1.iterator_next();
    //     std::cout << *iter;
    // }
    // std::cout << "\n";

    // l1.reverse();
    // for (l1.iterator_init(1); l1.iterator_end(); )
    // {
    //     iter = l1.iterator_next();
    //     std::cout << *iter;
    // }
    // std::cout << "\n";    

    //std::cout << "list find(6): true -->  " << (l1.find(6) == 0 ? "false" : "true") << "\n";

    //int ret = l1.deletel(0);
    //std::cout << "list deletel(0) value: 0 -->  " << ret << "\n";

    l1.clear();
    std::cout << "list clear size: 0 --> " << l1.size() << "\n";

    return 0;
}