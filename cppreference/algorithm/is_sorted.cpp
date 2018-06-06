

http://en.cppreference.com/w/cpp/algorithm/is_sorted

std::is_sorted
 
定义于头文件 <algorithm>
(1)	(C++11 起) (C++20 前)
    template< class ForwardIt >
    bool is_sorted( ForwardIt first, ForwardIt last );
    (C++20 起)
    template< class ForwardIt >
    constexpr bool is_sorted( ForwardIt first, ForwardIt last );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt >
    bool is_sorted( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last );

(3)	(C++11 起) (C++20 前)
    template< class ForwardIt, class Compare >
    bool is_sorted( ForwardIt first, ForwardIt last, Compare comp );
    (C++20 起)
    template< class ForwardIt, class Compare >
    constexpr bool is_sorted( ForwardIt first, ForwardIt last, Compare comp );
(4)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt, class Compare >
    bool is_sorted( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, Compare comp );

检查 [first, last) 中的元素是否以不降序排序。

1) 用 operator< 比较元素。
3) 用给定的二元比较函数 comp 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要检验的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 概念的对象），若第一参数小于（即先序于）第二参数则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不必拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 ForwardIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。

返回值
    若范围中的元素已以升序排序则为 true 。

复杂度
    与 first 和 last 间的距离成线性。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class ForwardIt>
    bool is_sorted(ForwardIt first, ForwardIt last)
    {
        return std::is_sorted_until(first, last) == last;
    }
版本二
    template<class ForwardIt, class Compare>
    bool is_sorted(ForwardIt first, ForwardIt last, Compare comp)
    {
        return std::is_sorted_until(first, last, comp) == last;
    }
示例

#include <iostream>
#include <algorithm>
#include <iterator>
int main() 
{
    int digits[] = {3, 1, 4, 1, 5};
 
    for (auto i : digits) std::cout << i << ' ';
    std::cout << ": is_sorted: " << std::boolalpha
              << std::is_sorted(std::begin(digits), std::end(digits)) << '\n';
 
    std::sort(std::begin(digits), std::end(digits));
 
    for (auto i : digits) std::cout << i << ' ';
    std::cout << ": is_sorted: "
              << std::is_sorted(std::begin(digits), std::end(digits)) << '\n';
}

输出：
3 1 4 1 5 : is_sorted: false
1 1 3 4 5 : is_sorted: true