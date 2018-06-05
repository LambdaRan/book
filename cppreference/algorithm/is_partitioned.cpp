
http://en.cppreference.com/w/cpp/algorithm/is_partitioned


  C++ 算法库 
定义于头文件 <algorithm>
(1)	(C++11 起) (C++20 前)
    template< class InputIt, class UnaryPredicate >
    bool is_partitioned( InputIt first, InputIt last, UnaryPredicate p );

    (C++20 起)
    template< class InputIt, class UnaryPredicate >
    constexpr bool is_partitioned( InputIt first, InputIt last, UnaryPredicate p );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
    bool is_partitioned( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p );

1) 若范围 p 中的所有满足的元素都出现在所有不满足的元素前则返回 true 。若 [first, last) 为空亦返回 true 。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要检查的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若期待在范围开始找到该元素则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 InputIt 类型对象能在解引用后隐式转换到 Type 。 ​

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -ForwardIt 必须满足 ForwardIterator 的要求。而其值类型必须可转换为 UnaryPredicate 的参数类型
    -UnaryPredicate 必须满足 Predicate 的要求。

返回值
若范围 [first, last) 为空或以 p 划分则为 true 。否则为 false 。

复杂度
至多应用 std::distance(first, last) 次 p 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template< class InputIt, class UnaryPredicate >
    bool is_partitioned(InputIt first, InputIt last, UnaryPredicate p)
    {
        // 找到第一个不满足的情况
        for (; first != last; ++first)
            if (!p(*first))
                break;
        // 如果在不满足的序列中存在满足的情况，则没有排序
        for (; first != last; ++first)
            if (p(*first))
                return false;
        return true;
    }

示例

#include <algorithm>
#include <array>
#include <iostream>
 
int main()
{
    std::array<int, 9> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
 
    auto is_even = [](int i){ return i % 2 == 0; };
    std::cout.setf(std::ios_base::boolalpha);
    std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << ' ';
 
    std::partition(v.begin(), v.end(), is_even);
    std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << ' ';
 
    std::reverse(v.begin(), v.end());
    std::cout << std::is_partitioned(v.begin(), v.end(), is_even);
}

输出：
false true false