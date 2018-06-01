

http://en.cppreference.com/w/cpp/algorithm/copy

std::copy, std::copy_if

定义于头文件 <algorithm>
(1)	
    template< class InputIt, class OutputIt >
    OutputIt copy( InputIt first, InputIt last, OutputIt d_first );

    template< class InputIt, class OutputIt >
    constexpr OutputIt copy( InputIt first, InputIt last, OutputIt d_first );
(2)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    ForwardIt2 copy( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last, ForwardIt2 d_first );

(3)	
    template< class InputIt, class OutputIt, class UnaryPredicate >
    OutputIt copy_if( InputIt first, InputIt last,
                    OutputIt d_first,
                    UnaryPredicate pred );

    template< class InputIt, class OutputIt, class UnaryPredicate >
    constexpr OutputIt copy_if( InputIt first, InputIt last,
                                OutputIt d_first,
                                UnaryPredicate pred );
(4)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class UnaryPredicate >
    ForwardIt2 copy_if( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                    ForwardIt2 d_first,
                    UnaryPredicate pred );

复制 [first, last) 所定义的范围中的元素到始于 d_first 的另一范围。

1) 复制范围 [first, last) 中的所有元素。若 d_first 在范围 [first, last) 中则行为未定义。
    此情况下可用 std::copy_backward 代替。
3) 仅复制谓词 pred 对其返回 true 的元素。保持被复制元素的相对顺序。若源与目标范围重叠则行为未定义。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要复制的元素范围
    d_first	-	目标范围的起始。
    policy	-	所用的执行策略。细节见执行策略。
    pred	-	对所要求的元素则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 InputIt 类型对象能在解引用后隐式转换到 Type 。 ​

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。
    -UnaryPredicate 必须满足 Predicate 的要求。

返回值
    指向目标范围中最后复制元素的下个元素的输出迭代器。

复杂度
    1-2) 准确赋值 (last - first) 次
    3-4) 准确应用 (last - first) 次谓词， ​0​ 和 (last - first) 之间次赋值（对于每个谓词等于 true 的元素赋值，取决于谓词和输入数据）
    对于带 ExecutionPolicy 的重载，若 ForwardIt1 的 value_type 不可移动构造 (MoveConstructible) 则有性能开销。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

注意
    实践中，若 value_type 为可平凡复制 (TriviallyCopyable) ，
        则 std::copy 避免多次赋值并使用大批量复制函数，如 std::memmove 。

    复制重叠的范围时， std::copy 在复制到左侧（目标范围起始在源范围之外）时适合，
        而 std::copy_backward 在复制到右侧（目标范围结尾在源范围之外）时适合。

可能的实现
版本一
    template<class InputIt, class OutputIt>
    OutputIt copy(InputIt first, InputIt last, 
                OutputIt d_first)
    {
        while (first != last) {
            *d_first++ = *first++;
        }
        return d_first;
    }
版本二
    template<class InputIt, class OutputIt, class UnaryPredicate>
    OutputIt copy_if(InputIt first, InputIt last, 
                    OutputIt d_first, UnaryPredicate pred)
    {
        while (first != last) {
            if (pred(*first))
                *d_first++ = *first;
            ++first;
        }
        return d_first;
    }

示例
下列代码用 copy 复制一个 vector 的内容到另一个，并显示结果 vector ：

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
 
int main()
{
    std::vector<int> from_vector(10);
    std::iota(from_vector.begin(), from_vector.end(), 0);
 
    std::vector<int> to_vector;
    std::copy(from_vector.begin(), from_vector.end(),
              std::back_inserter(to_vector));
// 或可选地，
//  std::vector<int> to_vector(from_vector.size());
//  std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
// 任一方式都等价于
//  std::vector<int> to_vector = from_vector;
 
    std::cout << "to_vector contains: ";
 
    std::copy(to_vector.begin(), to_vector.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

输出：
to_vector contains: 0 1 2 3 4 5 6 7 8 9