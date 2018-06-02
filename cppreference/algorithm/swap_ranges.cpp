
http://en.cppreference.com/w/cpp/algorithm/swap_ranges

std::swap_ranges

定义于头文件 <algorithm>
(1)	
    template< class ForwardIt1, class ForwardIt2 >
    ForwardIt2 swap_ranges( ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2 );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    ForwardIt2 swap_ranges( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2 );

1) 在范围 [first1, last1) 和始于 first2 的另一范围间交换元素。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first1, last1	-	要交换的第一个元素范围
    first2	-	要交换的第二个元素范围的起始
    policy	-	所用的执行策略。细节见执行策略。

类型要求
    -ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。
    -ForwardIt1 与 ForwardIt2 解引用的类型必须满足 Swappable 的要求

返回值
    指向始于 first2 的范围中被交换的最末元素后一元素的迭代器。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template<class ForwardIt1, class ForwardIt2>
    ForwardIt2 swap_ranges(ForwardIt1 first1, 
                                ForwardIt1 last1, 
                                ForwardIt2 first2)
    {
        while (first1 != last1) {
            std::iter_swap(first1++, first2++);
        }
        return first2;
    }

示例
演示来自不同容器的子范围交换

#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::list<int> l = {-1, -2, -3, -4, -5};
 
    std::swap_ranges(v.begin(), v.begin()+3, l.begin());
 
    for(int n : v)
       std::cout << n << ' ';
    std::cout << '\n';
    for(int n : l)
       std::cout << n << ' ';
    std::cout << '\n';
}

输出：
-1 -2 -3 4 5
1 2 3 -4 -5

复杂度
与 first1 和 last1 的距离成线性