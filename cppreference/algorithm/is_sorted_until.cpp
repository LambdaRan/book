
http://en.cppreference.com/w/cpp/algorithm/is_sorted_until

std::is_sorted_until

定义于头文件 <algorithm>
(1)	(C++11 起) (C++20 前)
    template< class ForwardIt >
    ForwardIt is_sorted_until( ForwardIt first, ForwardIt last );

    (C++20 起)
    template< class ForwardIt >
    constexpr ForwardIt is_sorted_until( ForwardIt first, ForwardIt last );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt >
    ForwardIt is_sorted_until( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last );
(3)	(C++11 起) (C++20 前)
    template< class ForwardIt, class Compare >
    ForwardIt is_sorted_until( ForwardIt first, ForwardIt last, 
                            Compare comp );
    (C++20 起)
    template< class ForwardIt, class Compare >
    constexpr ForwardIt is_sorted_until( ForwardIt first, ForwardIt last, 
                                        Compare comp );
(4)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt, class Compare >
    ForwardIt is_sorted_until( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, 
                            Compare comp );
                            
检验范围 [first, last) ，并寻找始于 first 且其中元素已以升序排序的最大范围。

1) 用 operator< 比较元素。
3) 用给定的二元比较函数 comp 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要检验的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 概念的对象），若第一参数小于（即先序于）第二参数则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不必拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 ForwardIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。

返回值
    始于 first 且其中元素已以升序排序的最大范围。即满足范围 [first, it) 已排序的最后迭代器 it 。

复杂度
    与 first 和 last 间的距离成线性。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class ForwardIt>
    ForwardIt is_sorted_until(ForwardIt first, ForwardIt last)
    {
        if (first != last) {
            ForwardIt next = first;
            while (++next != last) {
                if (*next < *first)
                    return next;
                first = next;
            }
        }
        return last;
    }
版本二
    template <class ForwardIt, class Compare>
    ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp) 
    {
        using namespace std::placeholders;
        ForwardIt it = std::adjacent_find(first, last, std::bind(comp, _2, _1));
        return it == last ? last : std::next(it);
    }
示例

#include <iostream>
#include <algorithm>
#include <iterator>
#include <random>
 
int main()
{
    std::random_device rd;
    std::mt19937 g(rd());
    const int N = 6;
    int nums[N] = {3, 1, 4, 1, 5, 9};
 
    const int min_sorted_size = 4;
    int sorted_size = 0;
    do {
        std::shuffle(nums, nums + N, g);
        int *sorted_end = std::is_sorted_until(nums, nums + N);
        sorted_size = std::distance(nums, sorted_end);
 
        for (auto i : nums) std::cout << i << ' ';
        std::cout << " : " << sorted_size << " initial sorted elements\n";
    } while (sorted_size < min_sorted_size);
}

可能的输出：
4 1 9 5 1 3  : 1 initial sorted elements
4 5 9 3 1 1  : 3 initial sorted elements
9 3 1 4 5 1  : 1 initial sorted elements
1 3 5 4 1 9  : 3 initial sorted elements
5 9 1 1 3 4  : 2 initial sorted elements
4 9 1 5 1 3  : 2 initial sorted elements
1 1 4 9 5 3  : 4 initial sorted elements
