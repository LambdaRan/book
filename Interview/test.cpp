

#include <iostream>

#include <iterator>
#include <algorithm>
#include <list>

int main(void)
{
    std::list<int> lst = {1, 2, 3, 4};
    std::list<int> lst2;

    std::copy(lst.begin(), lst.end(), std::inserter(lst2, lst2.begin()));

    for (auto &v:lst2)
        std::cout << v << " ";
    

    return 0;
}