

http://en.cppreference.com/w/cpp/algorithm/partition_point

std::partition_point

定义于头文件 <algorithm>
(1)	(C++11 起) (C++20 前)
    template< class ForwardIt, class UnaryPredicate >
    ForwardIt partition_point( ForwardIt first, ForwardIt last, UnaryPredicate p );
(C++20 起)
    template< class ForwardIt, class UnaryPredicate >
    constexpr ForwardIt partition_point( ForwardIt first, ForwardIt last, UnaryPredicate p );

检验（如同用 std::partition 的）划分范围 [first, last) ，并定位第一划分的结尾，即首个不满足 p 的元素，
    或若所有元素满足 p 则为 last 。

参数
    first, last	-	要检验的元素被划分范围
    p	-	对于在范围起始找到的元素则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 ForwardIt 类型对象能在解引用后隐式转换到 Type 。 ​

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。
    -UnaryPredicate 必须满足 Predicate 的要求。

返回值
    [first, last) 内第一划分结尾后的迭代器，或若所有元素满足 p 则为 last 。

复杂度
    给定 N = std::distance(first, last) ，进行 O(log N) 次谓词 p 的应用。

    然而，对于非随机访问迭代器 (RandomAccessIterator) ，迭代器自增次数为 O(N) 。

示例

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
 
int main()
{
    std::array<int, 9> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
 
    auto is_even = [](int i){ return i % 2 == 0; };
    std::partition(v.begin(), v.end(), is_even);
 
    auto p = std::partition_point(v.begin(), v.end(), is_even);
 
    std::cout << "Before partition:\n    ";
    std::copy(v.begin(), p, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nAfter partition:\n    ";
    std::copy(p, v.end(), std::ostream_iterator<int>(std::cout, " "));
}
输出：

Before partition:
    8 2 6 4 
After partition:
    5 3 7 1 9
