

http://en.cppreference.com/w/cpp/algorithm/fill_n

std::fill_n

定义于头文件 <algorithm>
(1)	
    template< class OutputIt, class Size, class T >
    void fill_n( OutputIt first, Size count, const T& value );

    template< class OutputIt, class Size, class T >
    OutputIt fill_n( OutputIt first, Size count, const T& value );

    template< class OutputIt, class Size, class T >
    constexpr OutputIt fill_n( OutputIt first, Size count, const T& value );
(2)	
    template< class ExecutionPolicy, class ForwardIt, class Size, class T >
    ForwardIt fill_n( ExecutionPolicy&& policy, ForwardIt first, Size count, const T& value );

1) 若 count > 0 ，则赋值给定的 value 给始于 的范围的首 count 个元素。否则不做任何事。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first	-	要修改的元素范围起始
    count	-	要修改的元素数
    value	-	要赋的值
    policy	-	所用的执行策略。细节见执行策略。

类型要求
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt 必须满足 ForwardIterator 的要求。

返回值
（无）(C++11 前)
    若 count > 0 则为指向最后赋值元素后一位置的迭代器，否则为 first 。(C++11 起)

复杂度
    对于 count > 0 ，准确赋值 count 次。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template<class OutputIt, class Size, class T>
    OutputIt fill_n(OutputIt first, Size count, const T& value)
    {
        for (Size i = 0; i < count; ++i) {
            *first++ = value;
        }
        return first;
    }

示例
下列代码用 fill_n() 赋值 -1 给 int 的 vector 的前一半：

运行此代码
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
 
int main()
{
    std::vector<int> v1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
 
    std::fill_n(v1.begin(), 5, -1);
 
    std::copy(begin(v1), end(v1), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

输出：

-1 -1 -1 -1 -1 5 6 7 8 9