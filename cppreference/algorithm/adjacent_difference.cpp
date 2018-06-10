

http://en.cppreference.com/w/cpp/algorithm/adjacent_difference

std::adjacent_difference
  C++ 算法库 
定义于头文件 <numeric>
(1)	
template< class InputIt, class OutputIt >
OutputIt adjacent_difference( InputIt first, InputIt last, 
                              OutputIt d_first );
(C++20 前)
template< class InputIt, class OutputIt >
constexpr OutputIt adjacent_difference( InputIt first, InputIt last, 
                                        OutputIt d_first );
(C++20 起)
template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
ForwardIt2 adjacent_difference( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last, 
                                ForwardIt2 d_first );
(2)	(C++17 起)
(3)	
template< class InputIt, class OutputIt, class BinaryOperation >
OutputIt adjacent_difference( InputIt first, InputIt last, 
                              OutputIt d_first, BinaryOperation op );
(C++20 前)
template< class InputIt, class OutputIt, class BinaryOperation >
constexpr OutputIt adjacent_difference( InputIt first, InputIt last, 
                                        OutputIt d_first, BinaryOperation op );
(C++20 起)
template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class BinaryOperation >
ForwardIt2 adjacent_difference( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last, 
                                ForwardIt2 d_first, BinaryOperation op );
(4)	(C++17 起)
计算 [first, last) 范围中每对相邻元素的第二个和第一个的差，并写入它们到始于 d_first + 1 的范围。写入不修改的 *first 副本到 *d_first 。

1,3) 首先，创建类型为 InputIt 的 value_type 的积累器 acc ，以 *first 初始化，并赋值为 *d_first 的结果。然后，对于 [first + 1, last) 中按顺序的每个迭代器 i ，创建类型为 InputIt 的 value_type 的对象 val ，以 *i 初始化，计算 val - acc (C++20 前)val - std::move(acc) (C++20 起) （重载 (1) ）或 op(val, acc) (C++20 前)op(val, std::move(acc)) (C++20 起) （重载 (3) ），赋值结果到 *(d_first + (i - first)) ，并从 val 移动赋值到 acc 。
 first 可以等于 d_first 。
2,4) 首先，创建类型为 ForwardIt1 的 value_type 的对象，以 *first 初始化，并赋值为 *d_first 的结果。然后对 [1, last - first - 1] 中每个的 d ，创建类型为 ForwardIt1 的 value_type 的对象 val ，以 *(first + d) - *(first + d - 1) （重载 (2) ）或 op(*(first + d), *(first + d - 1)) （重载 (4) ）初始化，并赋值到 *(d_first + d) 。这根据 policy 执行。此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。
 若输入与输出范围以任何方式重叠则行为未定义。

等价操作：

*(d_first)   = *first;
*(d_first+1) = *(first+1) - *(first);
*(d_first+2) = *(first+2) - *(first+1);
*(d_first+3) = *(first+3) - *(first+2);
...
op 必须无副效应。

(C++11 前)
op 必须不非法化涉及范围的任何迭代器，含尾迭代器，或修改该范围的任何元素。

(C++11 起)
参数
first, last	-	元素范围
d_first	-	目标范围的起始
policy	-	所用的执行策略。细节见执行策略。
op	-	被使用的二元函数对象。
该函数的签名应当等价于：

 Ret fun(const Type1 &a, const Type2 &b);

签名中并不需要有 const &。
类型 Type1 与 Type2 必须使得 iterator_traits<InputIt>::value_type 类型的对象能隐式转换到这两个类型。 类型 Ret 必须使得 OutputIt 类型对象能被解引用并能被赋 Ret 类型值。 ​

类型要求
-InputIt 必须满足 InputIterator 的要求。InputIt 的 value_type 必须可移动赋值 (MoveAssignable) 且可从 *first 的类型构造
-OutputIt 必须满足 OutputIterator 的要求。acc （积累的值）和 val - acc 或 op(val, acc) (C++20 前)val - std::move(acc) 或 op(val, std::move(acc)) (C++20 起) 结果都必须可写入 OutputIt
-ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。ForwardIt1 的 value_type 必须可复制构造 (CopyConstructible) ，可从表达式 *first - *first 或 op(*first, *first) 构造，并且可赋值给 ForwardIt2 的 value_type
返回值
指向最后被写入元素正好后一位的迭代器。

注意
若 first == last ，则此函数无效果而将只不过返回 d_first 。

复杂度
恰好应用 (last - first) - 1 次二元操作

异常
拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。对于任何其他 ExecutionPolicy ，行为是实现定义的。
若算法无法分配内存，则抛出 std::bad_alloc 。
可能的实现
版本一
template<class InputIt, class OutputIt>
OutputIt adjacent_difference(InputIt first, InputIt last, 
                             OutputIt d_first)
{
    if (first == last) return d_first;
 
    typedef typename std::iterator_traits<InputIt>::value_type value_t;
    value_t acc = *first;
    *d_first = acc;
    while (++first != last) {
        value_t val = *first;
        *++d_first = val - std::move(acc); // C++20 起有 std::move
        acc = std::move(val);
    }
    return ++d_first;
}
版本二
template<class InputIt, class OutputIt, class BinaryOperation>
OutputIt adjacent_difference(InputIt first, InputIt last, 
                             OutputIt d_first, BinaryOperation op)
{
    if (first == last) return d_first;
 
    typedef typename std::iterator_traits<InputIt>::value_type value_t;
    value_t acc = *first;
    *d_first = acc;
    while (++first != last) {
        value_t val = *first;
        *++d_first = op(val, std::move(acc)); // C++20 起有 std::move
        acc = std::move(val);
    }
    return ++d_first;
}
示例
运行此代码
#include <numeric>
#include <vector>
#include <iostream>
#include <functional>
 
int main()
{
    // 默认实现——二个项之间的差
 
    std::vector<int> v{2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    std::adjacent_difference(v.begin(), v.end(), v.begin());
 
    for (auto n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
 
    // 斐波那契
    // 注意，列表中下一项是当前迭代的结果
 
    v = std::vector<int>(10);
    v[0] = 1;
 
    std::adjacent_difference(v.begin(), v.end() - 1, v.begin() + 1, std::plus<int>());
 
    for (auto n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}
输出：

2 2 2 2 2 2 2 2 2 2
1 1 2 3 5 8 13 21 34 55