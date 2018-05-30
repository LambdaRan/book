

http://en.cppreference.com/w/cpp/algorithm/move

std::move

定义于头文件 <algorithm>
(1)	
    template< class InputIt, class OutputIt >
    OutputIt move( InputIt first, InputIt last, OutputIt d_first );

    template< class InputIt, class OutputIt >
    constexpr OutputIt move( InputIt first, InputIt last, OutputIt d_first );
(2)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    ForwardIt2 move( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last, ForwardIt2 d_first );

1) 移动范围 [first, last) 中的元素到始于 d_first 的另一范围。
    此操作后被移动范围中的元素将仍然含有适合类型的合法值，但不必与移动前的值相同。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要移动的元素范围
    d_first	-	目标范围起始。若 d_first 在范围 [first, last) 中则行为未定义。
        此情况下可用 std::move_backward 代替 std::move 。
    policy	-	所用的执行策略。细节见执行策略。

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。

返回值
    指向最后移动元素后一位置的迭代器（ d_first + (last - first) ）。

复杂度
    准确移动赋值 last - first 次。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template<class InputIt, class OutputIt>
    OutputIt move(InputIt first, InputIt last, OutputIt d_first)
    {
        while (first != last) {
            *d_first++ = std::move(*first++);
        }
        return d_first;
    }

注意
    移动重叠的范围时， std::move 在移动到左侧（目标范围的起始在源范围外）时适合，
        而 std::move_backward 在移动到右侧（目标范围的结尾在源范围外）时适合。

示例
    下列代码从一个容器移动 thread 对象（自身不可复制）到另一个。

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <thread>
#include <chrono>
 
void f(int n)
{
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "thread " << n << " ended" << '\n';
}
 
int main() 
{
    std::vector<std::thread> v;
    v.emplace_back(f, 1);
    v.emplace_back(f, 2);
    v.emplace_back(f, 3);
    std::list<std::thread> l;
    // copy() 无法编译，因为 std::thread 不可复制
 
    std::move(v.begin(), v.end(), std::back_inserter(l)); 
    for (auto& t : l) t.join();
}

输出：
thread 1 ended
thread 2 ended
thread 3 ended