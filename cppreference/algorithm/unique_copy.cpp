
http://en.cppreference.com/w/cpp/algorithm/unique_copy

std::unique_copy
  C++ 算法库 
定义于头文件 <algorithm>
(1)	(C++20 前)
    template< class InputIt, class OutputIt >
    OutputIt unique_copy( InputIt first, InputIt last,
                        OutputIt d_first );
    (C++20 起)
    template< class InputIt, class OutputIt >
    constexpr OutputIt unique_copy( InputIt first, InputIt last,
                                    OutputIt d_first );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    ForwardIt2 unique_copy( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 d_first );

(3)	(C++20 前)
    template< class InputIt, class OutputIt, class BinaryPredicate >
    OutputIt unique_copy( InputIt first, InputIt last,
                        OutputIt d_first, BinaryPredicate p );
    C++20 起)
    template< class InputIt, class OutputIt, class BinaryPredicate >
    constexpr OutputIt unique_copy( InputIt first, InputIt last,
                                    OutputIt d_first, BinaryPredicate p );
(4)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    ForwardIt2 unique_copy( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 d_first, BinaryPredicate p );

从范围 [first, last) 复制元素到始于 d_first 的另一范围，使得无连续的相等元素。只复制每组等价元素的首元素。

1) 用 operator== 比较元素。
3) 用给定的二元谓词 p 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要处理的元素范围
    d_first	-	目标范围的起始
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若元素应被当做相等则返回 ​true 的二元谓词。
    谓词函数的签名应等价于如下者：
    bool pred(const Type1 &a, const Type2 &b);
    签名不必有 const & ，但函数必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 InputIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。
    -解引用 InputIt 结果的类型必须满足 CopyAssignable 的要求。若 InputIt 不满足向前迭代器 (ForwardIterator) 。
    -解引用 InputIt 结果的类型必须满足 CopyConstructible 的要求。
        若 InputIt 或 OutputIt 均不满足向前迭代器 (ForwardIterator) ，
        或若 InputIt 不满足向前迭代器 (ForwardIterator) 且 InputIt 的 value_type 异于 OutputIt 。

返回值
    指向最后被写入元素后一元素的输出迭代器。

复杂度
    对于非空范围，准确应用 std::distance(first, last) - 1 次对应的比较器。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

注意
    若 InputIt 满足向前迭代器 (ForwardIterator) ，则此函数重读取输入，以检测重复。
    否则，若 OutputIt 满足向前迭代器 (ForwardIterator) ，且 InputIt 的 value_type 与 OutputIt 的相同，
        则此函数比较 *d_first 与 *first 。
    否则，此函数比较 *first 和局部元素副本。

    对有 ExecutionPolicy 的重载，若 ForwardIterator1 的值类型非可复制构造 (CopyConstructible) 
        且可复制赋值 (CopyAssignable) 则有性能开销。

示例

#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
 
int main()
{
    std::string s1 = "The      string    with many       spaces!";
    std::cout << "before: " << s1 << '\n';
 
    std::string s2;
    std::unique_copy(s1.begin(), s1.end(), std::back_inserter(s2),
                     [](char c1, char c2){ return c1 == ' ' && c2 == ' '; });
 
    std::cout << "after:  " << s2 << '\n';
}
输出：

before: The      string    with many       spaces!
after:  The string with many spaces!