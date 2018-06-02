

http://en.cppreference.com/w/cpp/algorithm/iter_swap

std::iter_swap

定义于头文件 <algorithm>

    template< class ForwardIt1, class ForwardIt2 >
    void iter_swap( ForwardIt1 a, ForwardIt2 b );

交换给定的迭代器所指向的元素的值。

参数
    a, b	-	指向要交换的元素的迭代器

类型要求
    -ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。
    -*a, *b 必须满足 Swappable 的要求。

返回值
（无）

复杂度
    常数

可能的实现
    template<class ForwardIt1, class ForwardIt2>
    void iter_swap(ForwardIt1 a, ForwardIt2 b)
    {
    using std::swap;
    swap(*a, *b);
    }

示例
下面是选择排序在 C++ 中的实现

#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
 
template<class ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end)
{
    for (ForwardIt i = begin; i != end; ++i)
        std::iter_swap(i, std::min_element(i, end));
}
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-10, 10);
    std::vector<int> v;
    generate_n(back_inserter(v), 20, bind(dist, gen));
 
    std::cout << "Before sort: ";
    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
 
    selection_sort(v.begin(), v.end());
 
    std::cout << "\nAfter sort: ";
    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

输出：

Before sort: -7 6 2 4 -1 6 -9 -1 2 -5 10 -9 -5 -3 -5 -3 6 6 1 8
After sort: -9 -9 -7 -5 -5 -5 -3 -3 -1 -1 1 2 2 4 6 6 6 6 8 10