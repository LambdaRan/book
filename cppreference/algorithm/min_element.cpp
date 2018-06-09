

http://en.cppreference.com/w/cpp/algorithm/min_element

std::min_element

定义于头文件 <algorithm>
(1)	(C++17 前)
    template< class ForwardIt > 
    ForwardIt min_element( ForwardIt first, ForwardIt last );
    (C++17 起)
    template< class ForwardIt > 
    constexpr ForwardIt min_element( ForwardIt first, ForwardIt last );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt > 
    ForwardIt min_element( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last );

(3)	(C++17 前)
    template< class ForwardIt, class Compare >
    ForwardIt min_element( ForwardIt first, ForwardIt last, Compare comp );
    (C++17 起)
    template< class ForwardIt, class Compare >
    constexpr ForwardIt min_element( ForwardIt first, ForwardIt last, Compare comp );
(4)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt, class Compare >
    ForwardIt min_element( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, Compare comp );

寻找范围 [first, last) 中的最小元素。

1) 用 operator< 比较元素。
3) 用给定的二元比较函数 comp 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	定义要检验范围的向前迭代器
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 要求的对象），若a 小于 b ，则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不需要拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 ForwardIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    rdIt 必须满足 ForwardIterator 的要求。

返回值
指向范围 [first, last) 中最小元素的迭代器。若范围中有多个元素等价于最小元素，则返回指向首个这种元素的迭代器。
若范围为空则返回 last 。

复杂度
准确比较 max(N-1,0) 次，其中 N = std::distance(first, last) 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class ForwardIt>
    ForwardIt min_element(ForwardIt first, ForwardIt last)
    {
        if (first == last) return last;
    
        ForwardIt smallest = first;
        ++first;
        for (; first != last; ++first) {
            if (*first < *smallest) {
                smallest = first;
            }
        }
        return smallest;
    }
版本二
    template<class ForwardIt, class Compare>
    ForwardIt min_element(ForwardIt first, ForwardIt last, 
                                Compare comp)
    {
        if (first == last) return last;
    
        ForwardIt smallest = first;
        ++first;
        for (; first != last; ++first) {
            if (comp(*first, *smallest)) {
                smallest = first;
            }
        }
        return smallest;
    }

示例

#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v{3, 1, 4, 1, 5, 9};
 
    std::vector<int>::iterator result = std::min_element(std::begin(v), std::end(v));
    std::cout << "min element at: " << std::distance(std::begin(v), result);
}

输出：

min element at: 1