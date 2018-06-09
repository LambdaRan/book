
http://en.cppreference.com/w/cpp/algorithm/is_heap

std::is_heap

定义于头文件 <algorithm>
(1)	(C++11 起) (C++20 前)
    template< class RandomIt >
    bool is_heap( RandomIt first, RandomIt last );
    (C++20 起)
    template< class RandomIt >
    constexpr bool is_heap( RandomIt first, RandomIt last );
(2)	(C++17 起)
    template< class ExecutionPolicy, class RandomIt >
    bool is_heap( ExecutionPolicy&& policy, RandomIt first, RandomIt last );

(3)	(C++11 起) (C++20 前)
    template< class RandomIt, class Compare >
    bool is_heap( RandomIt first, RandomIt last, Compare comp );
    (C++20 起)
    template< class RandomIt, class Compare >
    constexpr bool is_heap( RandomIt first, RandomIt last, Compare comp );
(4)	(C++17 起)
    template< class ExecutionPolicy, class RandomIt, class Compare >
    bool is_heap( ExecutionPolicy&& policy, RandomIt first, RandomIt last, Compare comp );

检查范围 [first, last) 中的元素是否为最大堆。

1) 用 operator< 比较元素。
3) 用给定的二元比较函数 comp 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要检验的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 要求的对象），若首个参数小于第二个，则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不需要拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 RandomIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -RandomIt 必须满足 RandomAccessIterator 的要求。

返回值
若范围为最大堆则为 true ，否则为 false 。

复杂度
与 first 和 last 间的距离成线性

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

注意
    最大堆是拥有下列属性的元素范围 [f,l) ：

    设 N = l - f ，对于所有 0 < i < N ， f[floor((i-1)/2)] 不小于 f[i] 。
    可用 std::push_heap() 添加新元素
    可用 std::pop_heap() 移除首元素

示例

#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
 
    std::cout << "initially, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
 
    if (!std::is_heap(v.begin(), v.end())) {
        std::cout << "making heap...\n";
        std::make_heap(v.begin(), v.end());
    }
 
    std::cout << "after make_heap, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
}

输出：

initially, v: 3 1 4 1 5 9 
making heap...
after make_heap, v: 9 5 4 1 1 3
