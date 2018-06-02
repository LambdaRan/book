
http://en.cppreference.com/w/cpp/algorithm/rotate_copy

std::rotate_copy

定义于头文件 <algorithm>

(1)	(C++20 前)
    template< class ForwardIt, class OutputIt >
    OutputIt rotate_copy( ForwardIt first, ForwardIt n_first,
                        ForwardIt last, OutputIt d_first );
    (C++20 起)
    template< class ForwardIt, class OutputIt >
    constexpr OutputIt rotate_copy( ForwardIt first, ForwardIt n_first,
                                    ForwardIt last, OutputIt d_first );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    ForwardIt2 rotate_copy( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 n_first,
                        ForwardIt1 last, ForwardIt2 d_first );

1) 从范围 [first, last) 复制元素到始于 d_first 的另一范围，
    使得 n_first 成为新范围的首元素，而 n_first - 1 成为末元素。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要复制的元素范围
    n_first	-	指向 [first, last) 中应出现在新范围起始的元素的迭代器
    d_first	-	目标范围的起始
    policy	-	所用的执行策略。细节见执行策略。

类型要求
    -ForwardIt, ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。

复杂度
与 first 和 last 间的距离成线性

返回值
    指向最后被复制元素后一元素的输出迭代器。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template<class ForwardIt, class OutputIt>
    OutputIt rotate_copy(ForwardIt first, ForwardIt n_first,
                            ForwardIt last, OutputIt d_first)
    {
        d_first = std::copy(n_first, last, d_first);
        return std::copy(first, n_first, d_first);
    }

示例

#include <algorithm>
#include <vector>
#include <iostream>
 
int main()
{
    std::vector<int> src = {1, 2, 3, 4, 5}; 
    auto pivot = std::find(src.begin(), src.end(), 3); 
    std::vector<int> dest(src.size());                                          
 
    std::rotate_copy(src.begin(), pivot, src.end(), dest.begin());
 
    for (const auto &i : dest) {
        std::cout << i << ' ';
    }   
    std::cout << '\n';
}

输出：
3 4 5 1 2
