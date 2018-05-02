#include <iostream>

#include <vector>
int main() 
{
    int nums;
    std::vector<int> vec;
    std::cin >> nums;

    for (int i = 0; i != nums; ++i)
    {
        int num;
        std::cin >> num;
        vec.push_back(num);
    }
    for (auto v : vec)
        std::cout << v << " ";
    std::cout << std::endl;
}