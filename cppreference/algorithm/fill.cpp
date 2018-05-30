

http://en.cppreference.com/w/cpp/algorithm/fill

std::fill

定义于头文件 <algorithm>
(1)	
    template< class ForwardIt, class T >
    void fill( ForwardIt first, ForwardIt last, const T& value );

    template< class ForwardIt, class T >
    constexpr void fill( ForwardIt first, ForwardIt last, const T& value );
(2)
    template< class ExecutionPolicy, class ForwardIt, class T >
    void fill( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, const T& value );

1) 赋值给定的 value 给 [first, last) 中的元素。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要修改的元素范围
    value	-	要赋的值
    policy	-	所用的执行策略。细节见执行策略。

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。

返回值
（无）

复杂度
    准确赋值 last - first 次。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template< class ForwardIt, class T >
    void fill(ForwardIt first, ForwardIt last, const T& value)
    {
        for (; first != last; ++first) {
            *first = value;
        }
    }

示例
    下列代码用 fill() 设置 int 的 vectort 的所有元素为 -1 ：

#include <algorithm>
#include <vector>
#include <iostream>
 
int main()
{
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
 
    std::fill(v.begin(), v.end(), -1);
 
    for (auto elem : v) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

输出：

-1 -1 -1 -1 -1 -1 -1 -1 -1 -1