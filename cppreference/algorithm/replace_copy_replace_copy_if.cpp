
http://en.cppreference.com/w/cpp/algorithm/replace_copy

std::replace_copy, std::replace_copy_if

定义于头文件 <algorithm>
(1)	
    template< class InputIt, class OutputIt, class T >
    OutputIt replace_copy( InputIt first, InputIt last, OutputIt d_first,
                            const T& old_value, const T& new_value );

    template< class InputIt, class OutputIt, class T >
    constexpr OutputIt replace_copy( InputIt first, InputIt last, OutputIt d_first,
                                    const T& old_value, const T& new_value );
(2)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class T >
    ForwardIt2 replace_copy( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 d_first, const T& old_value, const T& new_value );

(3)	
    template< class InputIt, class OutputIt, class UnaryPredicate, class T >
    OutputIt replace_copy_if( InputIt first, InputIt last, OutputIt d_first,
                            UnaryPredicate p, const T& new_value );

    template< class InputIt, class OutputIt, class UnaryPredicate, class T >
    constexpr OutputIt replace_copy_if( InputIt first, InputIt last, OutputIt d_first,
                                        UnaryPredicate p, const T& new_value );
(4)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class UnaryPredicate, class T >
    ForwardIt2 replace_copy_if( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                                ForwardIt2 d_first, UnaryPredicate p, const T& new_value );

复制来自范围 [first, last) 的所有元素到始于 d_first 的范围，并以 new_value 替换所有满足特定判别标准的元素。源与目标范围不能重叠。

1) 替换所有等于 old_value 的元素。
3) 替换所有谓词 p 对其满足 true 的元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要复制的元素范围
    d_first	-	目标范围的起始
    old_value	-	要被替换的元素值
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若应该替换元素则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 InputIt 类型对象能在解引用后隐式转换到 Type 。 ​

    new_value	-	用作替换者的元素值

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。

返回值
    指向最后复制元素后一元素的迭代器。

复杂度
    准确应用 last - first 次谓词。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class InputIt, class OutputIt, class T>
    OutputIt replace_copy(InputIt first, InputIt last, OutputIt d_first,
                        const T& old_value, const T& new_value)
    {
        for (; first != last; ++first) {
            *d_first++ = (*first == old_value) ? new_value : *first;
        }
        return d_first;
    }
版本二
    template<class InputIt, class OutputIt, 
            class UnaryPredicate, class T>
    OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt d_first,
                            UnaryPredicate p, const T& new_value)
    {
        for (; first != last; ++first) {
            *d_first++ = p( *first ) ? new_value : *first;
        }
        return d_first;
    }
示例
下列代码打印 vector ，同时临时替换所有超过 5 的值为 99 。


#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
 
int main()
{
    std::vector<int> v{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    std::replace_copy_if(v.begin(), v.end(),
                         std::ostream_iterator<int>(std::cout, " "),
                         [](int n){return n > 5;}, 99);
    std::cout << '\n';
}

输出：
5 99 4 2 99 99 1 99 0 3