
http://en.cppreference.com/w/cpp/algorithm/reverse_copy

std::reverse_copy

定义于头文件 <algorithm>

    (1)	(C++20 前)
    template< class BidirIt, class OutputIt >
    OutputIt reverse_copy( BidirIt first, BidirIt last, OutputIt d_first );

    (C++20 起)
    template< class BidirIt, class OutputIt >
    constexpr OutputIt reverse_copy( BidirIt first, BidirIt last, OutputIt d_first );
(2)	(C++17 起)
    template< class ExecutionPolicy, class BidirIt, class ForwardIt >
    ForwardIt reverse_copy( ExecutionPolicy&& policy, BidirIt first, BidirIt last, ForwardIt d_first );

1) 复制来自范围 [first, last) 的元素到始于 d_first 的新范围，使得新范围中元素以逆序排列。
 表现如同通过对于每个非负的 i < (last - first) 执行一次赋值 *(d_first + (last - first) - 1 - i) = *(first + i) 。
 若源与目标范围（分别为 [first, last) 和 [d_first, d_first+(last-first)) ）重叠，则行为未定义。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要复制的元素范围
    d_first	-	新范围的起始

类型要求
    -BidirIt 必须满足 BidirectionalIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt 必须满足 ForwardIterator 的要求。

返回值
    指向最后被复制元素后一元素的迭代器。

复杂度
与 first 和 last 间的距离成线性。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template<class BidirIt, class OutputIt>
    OutputIt reverse_copy(BidirIt first, BidirIt last, OutputIt d_first)
    {
        while (first != last) {
            *(d_first++) = *(--last);
        }
        return d_first;
    }

示例

#include <vector>
#include <iostream>
#include <algorithm>
 
int main()
{
    std::vector<int> v({1,2,3});
    for (const auto& value : v) {
        std::cout << value << " ";
    }
    std::cout << '\n';
 
    std::vector<int> destination(3);
    std::reverse_copy(std::begin(v), std::end(v), std::begin(destination));
    for (const auto& value : destination) {
        std::cout << value << " ";
    }
    std::cout << '\n';
}

输出：
1 2 3 
3 2 1
