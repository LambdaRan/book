
#include <iostream>

#include <utility>
#include <vector>

#include <random> // 随机数
// 寻找数组中的最大值与最小值


// 解法一： 两次循环
// 2N 次比较

// 解法二：
// 较小数 放在偶数位
// 较大数 放在奇数位
// 1.5N 次比较
std::pair<int, int> minmax_element(std::vector<int> &vec)
{
    for (std::size_t i = 1; i < vec.size(); i += 2)
    {
        if (vec[i-1] > vec[i])
            std::swap(vec[i-1], vec[i]);
    }

    int min = 0;
    for (std::size_t i = 0; i < vec.size(); i += 2)
    {
        min = min < vec[i] ? min : vec[i];
    }
    int max = 0;
    for (std::size_t i = 1; i < vec.size(); i += 2)
    {
        max = max > vec[i] ? max : vec[i];
    }

    return std::make_pair(min, max);
}
// 不破坏原数组
std::pair<int, int> minmax_elementconst(const std::vector<int> &vec)
{
    int max = vec[0];
    int min = vec[0];

    for(auto v : vec)
    {
        min = min < v ? min : v;
        max = max > v ? max : v;
    }
    return std::make_pair(min, max);
}
// 解法四：分治思想
// 1.5N - 2 次比较
std::pair<int, int> search(const std::vector<int> &vec, std::size_t b, std::size_t e)
{
    if (e - b <= 1)
    {
        if (vec[e] < vec[b])
            return std::make_pair(vec[e], vec[b]);
        else  
            return std::make_pair(vec[b], vec[e]);
    }

    std::pair<int, int> lpair = search(vec, b, b+(e-b)/2);
    std::pair<int, int> rpair = search(vec, b+(e-b)/2, e);
    
    int min = lpair.first < rpair.first ? lpair.first : rpair.first;
    int max = lpair.second > rpair.second ? lpair.second : rpair.second;

    return std::make_pair(min, max);
}

std::vector<int> random_vector(int n)
{
    static std::default_random_engine e;
    static std::uniform_int_distribution<int> u(0, 100);

    std::vector<int> ret(n);
    for (int i = 0; i < n; ++i)
        ret[i] = u(e);
    return ret;
} 
int main(void)
{

    std::cout << " search min and max elements in array" << "\n";

    for (int i = 0; i < 6; ++i)
    {
        std::vector<int> vectst(random_vector(100));
        std::pair<int, int> retpair = minmax_elementconst(vectst);
        std::cout << "min: " << retpair.first << " max: " << retpair.second << "\n";

        retpair = search(vectst, 0, vectst.size());
        std::cout << "min: " << retpair.first << " max: " << retpair.second << "\n";

        retpair = minmax_element(vectst);
        std::cout << "min: " << retpair.first << " max: " << retpair.second << "\n";
    }
    return 0;
}