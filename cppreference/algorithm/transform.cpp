

http://en.cppreference.com/w/cpp/algorithm/transform

std::transform

定义于头文件 <algorithm>
(1)	
    template< class InputIt, class OutputIt, class UnaryOperation >
    OutputIt transform( InputIt first1, InputIt last1, OutputIt d_first,
                        UnaryOperation unary_op );

    template< class InputIt, class OutputIt, class UnaryOperation >
    constexpr OutputIt transform( InputIt first1, InputIt last1, OutputIt d_first,
                                UnaryOperation unary_op );
(2)	
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class UnaryOperation >
    ForwardIt2 transform( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1,
                        ForwardIt2 d_first, UnaryOperation unary_op );
(3)	
    template< class InputIt1, class InputIt2, class OutputIt, class BinaryOperation >
    OutputIt transform( InputIt1 first1, InputIt1 last1, InputIt2 first2, 
                        OutputIt d_first, BinaryOperation binary_op );

    template< class InputIt1, class InputIt2, class OutputIt, class BinaryOperation >
    constexpr OutputIt transform( InputIt1 first1, InputIt1 last1, InputIt2 first2, 
                                OutputIt d_first, BinaryOperation binary_op );
(4)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class ForwardIt3, class BinaryOperation >
    ForwardIt3 transform( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1,
                        ForwardIt2 first2, ForwardIt3 d_first, BinaryOperation binary_op );

std::transform 应用给定的函数到范围并存储结果于始于 d_first 的另一范围。

1) 应用一元函数 unary_op 到 [first1, last1) 所定义的范围。
3) 应用二元函数 binary_op 到来自二个范围的元素对：一个以 [first1, last1) 定义，而另一个始于 first2 。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。
unary_op 和 binary_op 必须无副效应。(C++11 前)
unary_op 和 binary_op 必须不非法化所涉及范围的任何迭代器，包含尾迭代器，或修改该范围的任何元素。(C++11 起)

参数
    first1, last1	-	要变换的第一元素范围
    first2	-	要变换的第二元素范围的起始
    d_first	-	目标范围的起始，可以等于 first1 或 first2
    policy	-	所用的执行策略。细节见执行策略。
    unary_op	-	将要应用的一元算符函数。
    函数签名应等价于如下者：
    Ret fun(const Type &a);
    签名不必有 const & 。
    类型 Type 必须使得 InputIt 类型对象能在解引用后隐式转换到 Type 。 
        类型 Ret 必须使得 OutputIt 类型对象能被解引用并能被赋 Ret 类型值。 ​

    binary_op	-	被使用的二元函数对象。
    该函数的签名应当等价于：
    Ret fun(const Type1 &a, const Type2 &b);
    签名中并不需要有 const &。
    类型 Type1 与 Type2 必须使得 InputIt1 与 InputIt2 类型的对象在解引用后分别能隐式转换到 Type1 与 Type2 。
         类型 Ret 必须使得 OutputIt 类型对象能被解引用并能被赋 Ret 类型值。 ​

类型要求
    -InputIt, InputIt1, InputIt2 必须满足 InputIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt1, ForwardIt2, ForwardIt3 必须满足 ForwardIterator 的要求。

返回值
    指向最后一个变换的元素的输出迭代器。

复杂度
    1-2) 准确应用 std::distance(first1, last1) 次 unary_op 。
    3-4) 准确应用 std::distance(first1, last1) 次 binary_op 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class InputIt, class OutputIt, class UnaryOperation>
    OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, 
                    UnaryOperation unary_op)
    {
        while (first1 != last1) {
            *d_first++ = unary_op(*first1++);
        }
        return d_first;
    }
版本二
    template<class InputIt1, class InputIt2, 
            class OutputIt, class BinaryOperation>
    OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2, 
                    OutputIt d_first, BinaryOperation binary_op)
    {
        while (first1 != last1) {
            *d_first++ = binary_op(*first1++, *first2++);
        }
        return d_first;
    }

注意
    std::transform 不保证按顺序应用 unary_op 或 binary_op 。
        为按顺序应用函数到数列，或应用修改序列元素的函数，应使用 std::for_each 。

示例
下列代码用 transform ，以 toupper 函数原位转换字符串为大写，然后转换每个字符为其序数值：

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
 
int main()
{
    std::string s("hello");
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) -> unsigned char { return std::toupper(c); });
 
    std::vector<std::size_t> ordinals;
    std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
                   [](unsigned char c) -> std::size_t { return c; });
 
    std::cout << s << ':';
    for (auto ord : ordinals) {
       std::cout << ' ' << ord;
    }
}

输出：

HELLO: 72 69 76 76 79
