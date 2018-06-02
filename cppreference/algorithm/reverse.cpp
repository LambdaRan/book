
http://en.cppreference.com/w/cpp/algorithm/reverse

std::reverse

定义于头文件 <algorithm>
(1)	
    template< class BidirIt >
    void reverse( BidirIt first, BidirIt last );
(2)	(C++17 起)
    template< class ExecutionPolicy, class BidirIt >
    void reverse( ExecutionPolicy&& policy, BidirIt first, BidirIt last );

1) 反转 [first, last) 范围中的元素顺序
 表现如同应用 std::iter_swap 到对于非负 i < (last-first)/2 的每对迭代器 first+i, (last-i) - 1
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要反转的元素的范围
    policy	-	所用的执行策略。细节见执行策略。

类型要求
    -BidirIt 必须满足 ValueSwappable 和 BidirectionalIterator 的要求。

返回值
（无）

复杂度
和 first 与 last 间的距离成线性

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template<class BidirIt>
    void reverse(BidirIt first, BidirIt last)
    {
        while ((first != last) && (first != --last)) {
            std::iter_swap(first++, last);
        }
    }

示例

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
 
int main()
{
    std::vector<int> v{1,2,3};
    std::reverse(std::begin(v), std::end(v));
    for(auto e : v) std::cout << e;
    std::cout << '\n';
 
    int a[] = {4, 5, 6, 7};
    std::reverse(std::begin(a), std::end(a));
    for(auto e : a) std::cout << e;
}

输出：
321
7654
