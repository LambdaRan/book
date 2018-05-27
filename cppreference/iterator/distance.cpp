
http://en.cppreference.com/w/cpp/iterator/distance

std::distance

定义于头文件 <iterator>

    template< class InputIt >
    typename std::iterator_traits<InputIt>::difference_type 
        distance( InputIt first, InputIt last );

    template< class InputIt >
    constexpr typename std::iterator_traits<InputIt>::difference_type 
        distance( InputIt first, InputIt last );

返回从 first 到 last 的路程。

若 last 不可从 first 通过（可以重复）自增 first 抵达，则行为未定义。(C++11 前)
若 InputIt 不是随机访问迭代器 (RandomAccessIterator) ，
    则若 last 不可从 first 通过（可以重复）自增 first 抵达，则行为未定义。 
若 InputIt 是 随机访问迭代器 (RandomAccessIterator) ，
    则若 last 不可从 first 抵达且 first 不可从 last 抵达，则行为未定义。(C++11 起)

参数
    first	-	指向首元素的迭代器
    last	-	指向范围尾的迭代器

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    若 InputIt 额外满足随机访问迭代器 (RandomAccessIterator) 的要求则操作更高效

返回值
    从 first 走到 last 所需的自增数。若使用随机访问迭代器且 first 可从 last 抵达，则值可能为负。 (C++11 起)

复杂度
    线性。
    然而，若 InputIt 额外满足随机访问迭代器 (RandomAccessIterator) 的要求，则复杂度是常数。

示例

#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
    std::cout << "distance(first, last) = "
              << std::distance(v.begin(), v.end()) << '\n'
              << "distance(last, first) = "
              << std::distance(v.end(), v.begin()) << '\n';
}

输出：
    distance(first, last) = 3
    distance(last, first) = -3