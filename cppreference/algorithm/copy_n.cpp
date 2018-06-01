

http://en.cppreference.com/w/cpp/algorithm/copy_n

std::copy_n

定义于头文件 <algorithm>
(1)	
    template< class InputIt, class Size, class OutputIt >
    OutputIt copy_n( InputIt first, Size count, OutputIt result );

    template< class InputIt, class Size, class OutputIt >
    constexpr OutputIt copy_n( InputIt first, Size count, OutputIt result );
(2)
    template< class ExecutionPolicy, class ForwardIt1, class Size, class ForwardIt2 >
    ForwardIt2 copy_n( ExecutionPolicy&& policy, ForwardIt1 first, Size count, ForwardIt2 result );

1) 若 count>0 ，则准确复制来自始于 first 的范围的 count 个值到始于 result 的范围。否则不做任何事。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first	-	复制来源的元素范围起始
    count	-	要复制的元素数
    result	-	目标范围起始
    policy	-	所用的执行策略。细节见执行策略。
类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。
复制
    若 count>0 则为指向目标范围中最后被复制元素后一元素的迭代器，否则为 result 。

复杂度
    若 count>0 ，则准确赋值 count 次。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。
可能的实现
    template< class InputIt, class Size, class OutputIt>
    OutputIt copy_n(InputIt first, Size count, OutputIt result)
    {
        if (count > 0) {
            *result++ = *first;
            for (Size i = 1; i < count; ++i) {
                *result++ = *++first;
            }
        }
        return result;
    }

示例

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
 
int main()
{
    std::string in = "1234567890";
    std::string out;
 
    std::copy_n(in.begin(), 4, std::back_inserter(out));
    std::cout << out << '\n';
}

输出：
1234