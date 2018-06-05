
http://en.cppreference.com/w/cpp/algorithm/partition_copy

std::partition_copy
  C++ 算法库 
定义于头文件 <algorithm>
(1)	(C++11 起) (C++20 前)
    template< class InputIt, class OutputIt1,
            class OutputIt2, class UnaryPredicate >
    std::pair<OutputIt1, OutputIt2>
        partition_copy( InputIt first, InputIt last,
                        OutputIt1 d_first_true, OutputIt2 d_first_false,
                        UnaryPredicate p );
    (C++20 起)
    template< class InputIt, class OutputIt1,
            class OutputIt2, class UnaryPredicate >
    constexpr std::pair<OutputIt1, OutputIt2>
                partition_copy( InputIt first, InputIt last,
                                OutputIt1 d_first_true, OutputIt2 d_first_false,
                                UnaryPredicate p );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2,
            class ForwardIt3, class UnaryPredicate >
    std::pair<ForwardIt2, ForwardIt3>
        partition_copy( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 d_first_true, ForwardIt3 d_first_false,
                        UnaryPredicate p );

1) 从范围 [first, last) 复制元素到二个不同范围，取决于谓词 p 的返回值。复制满足谓词 p 的元素到始于 d_first_true 的范围。
    复制剩余元素到始于 d_first_false 的范围。若输入范围与任一输出范围重叠，则行为未定义。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要排序的元素范围
    d_first_true	-	满足 p 的元素的输出范围起始
    d_first_false	-	不满足 p 的元素的输出范围起始
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若元素应置于 d_first_true 中则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 InputIt 类型对象能在解引用后隐式转换到 Type 。 ​

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -解引用 InputIt 结果的类型必须满足 CopyAssignable 的要求。
    -OutputIt1, OutputIt2 必须满足 OutputIterator 的要求。
    -ForwardIt1, ForwardIt2, ForwardIt3 必须满足 ForwardIterator 的要求。
        ForwardIt1 的值类型必须为可复制赋值 (CopyAssignable) ，可写入到 ForwardIt2 和 ForwardIt3 ，
        并且可转换为 UnaryPredicate 的参数类型
    -UnaryPredicate 必须满足 Predicate 的要求。

返回值
    从指向 d_first_true 范围结尾的迭代器和指向 d_first_false 范围结尾的迭代器构造的 std::pair 。

复杂度
准确应用 distance(first, last) 次 p 。

对于带 ExecutionPolicy 的重载，若 ForwardIt 的值类型非可复制构造 (CopyConstructible) ，则可能有性能开销。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template<class InputIt, class OutputIt1,
            class OutputIt2, class UnaryPredicate>
    std::pair<OutputIt1, OutputIt2>
        partition_copy(InputIt first, InputIt last,
                    OutputIt1 d_first_true, OutputIt2 d_first_false,
                    UnaryPredicate p)
    {
        while (first != last) {
            if (p(*first)) {
                *d_first_true = *first;
                ++d_first_true;
            } else {
                *d_first_false = *first;
                ++d_first_false;
            }
            ++first;
        }
        return std::pair<OutputIt1, OutputIt2>(d_first_true, d_first_false);
    }

示例

#include <iostream>
#include <algorithm>
#include <utility>
 
int main()
{
    int arr [10] = {1,2,3,4,5,6,7,8,9,10};
    int true_arr [5] = {0};
    int false_arr [5] = {0};
 
    std::partition_copy(std::begin(arr), std::end(arr), std::begin(true_arr), std::begin(false_arr),
                        [] (int i) {return i > 5;});
 
    std::cout << "true_arr: ";
    for (auto x : true_arr) {
        std::cout << x << ' ';
    }
    std::cout << '\n'; 
 
    std::cout << "false_arr: ";
    for (auto x : false_arr) {
        std::cout << x << ' ';
    }
    std::cout << '\n'; 
 
    return 0;
 
}

输出：
true_arr: 6 7 8 9 10
false_arr: 1 2 3 4 5