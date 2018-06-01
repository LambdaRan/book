

http://en.cppreference.com/w/cpp/algorithm/remove_copy

std::remove_copy, std::remove_copy_if

定义于头文件 <algorithm>
(1)	
    template< class InputIt, class OutputIt, class T >
    OutputIt remove_copy( InputIt first, InputIt last, OutputIt d_first,
                        const T& value );

    template< class InputIt, class OutputIt, class T >
    constexpr OutputIt remove_copy( InputIt first, InputIt last, OutputIt d_first,
                                    const T& value );
(2) 
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class T >
    ForwardIt2 remove_copy( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 d_first, const T& value );

(3)	
    template< class InputIt, class OutputIt, class UnaryPredicate >
    OutputIt remove_copy_if( InputIt first, InputIt last, OutputIt d_first,
                            UnaryPredicate p );

    template< class InputIt, class OutputIt, class UnaryPredicate >
    constexpr OutputIt remove_copy_if( InputIt first, InputIt last, OutputIt d_first,
                                    UnaryPredicate p );
(4)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class UnaryPredicate >
    ForwardIt2 remove_copy_if( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 d_first, UnaryPredicate p );

复制来自范围 [first, last) 的元素到始于 d_first 的另一范围，省略满足特定判别标准的元素。源与目标范围不能重叠。

1) 忽略所有等于 value 的元素。
3) 忽略所有谓词 p 对其返回 true 的元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要复制的元素范围
    d_first	-	目标范围的起始。
    value	-	不复制的元素的值
    policy	-	所用的执行策略。细节见执行策略。
类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。
    -UnaryPredicate 必须满足 Predicate 的要求。
返回值
    指向最后被复制元素的迭代器。

复杂度
    准确应用 last - first 次谓词。

    对拥有 ExecutionPolicy 的重载，若 ForwardIt1 的 value_type 非可移动构造 (MoveConstructible) 则有性能开销。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class InputIt, class OutputIt, class T>
    OutputIt remove_copy(InputIt first, InputIt last,
                        OutputIt d_first, const T& value)
    {
        for (; first != last; ++first) {
            if (!(*first == value)) {
                *d_first++ = *first;
            }
        }
        return d_first;
    }
版本二
    template<class InputIt, class OutputIt, class UnaryPredicate>
    OutputIt remove_copy_if(InputIt first, InputIt last,
                            OutputIt d_first, UnaryPredicate p)
    {
        for (; first != last; ++first) {
            if (!p(*first)) {
                *d_first++ = *first;
            }
        }
        return d_first;
    }

示例
下列代码输出字符串并临时擦除空格。

#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>
int main()
{
    std::string str = "Text with some   spaces";
    std::cout << "before: " << str << "\n";
 
    std::cout << "after:  ";
    std::remove_copy(str.begin(), str.end(),
                     std::ostream_iterator<char>(std::cout), ' ');
    std::cout << '\n';
}
输出：

before: Text with some   spaces
after:  Textwithsomespaces