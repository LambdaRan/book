
http://en.cppreference.com/w/cpp/algorithm/set_symmetric_difference

计算两组之间的对称差异 
std::set_symmetric_difference

定义于头文件 <algorithm>
(1)	(C++20 前)
    template< class InputIt1, class InputIt2, class OutputIt >
    OutputIt set_symmetric_difference( InputIt1 first1, InputIt1 last1,
                                    InputIt2 first2, InputIt2 last2,
                                    OutputIt d_first );
    (C++20 起)
    template< class InputIt1, class InputIt2, class OutputIt >
    constexpr OutputIt set_symmetric_difference( InputIt1 first1, InputIt1 last1,
                                                InputIt2 first2, InputIt2 last2,
                                                OutputIt d_first );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class ForwardIt3 >
    ForwardIt3 set_symmetric_difference( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1,
                                    ForwardIt2 first2, ForwardIt2 last2,
                                    ForwardIt3 d_first );

(3)	(C++20 前)
    template< class InputIt1, class InputIt2,
            class OutputIt, class Compare >
    OutputIt set_symmetric_difference( InputIt1 first1, InputIt1 last1,
                                    InputIt2 first2, InputIt2 last2,
                                    OutputIt d_first, Compare comp );
    (C++20 起)
    template< class InputIt1, class InputIt2,
            class OutputIt, class Compare >
    constexpr OutputIt set_symmetric_difference( InputIt1 first1, InputIt1 last1,
                                                InputIt2 first2, InputIt2 last2,
                                                OutputIt d_first, Compare comp );
(4)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2,
            class ForwardIt3, class Compare >
    ForwardIt3 set_symmetric_difference( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1,
                                    ForwardIt2 first2, ForwardIt2 last2,
                                    ForwardIt3 d_first, Compare comp );

计算二个已排序范围的对称差：复制在任一范围中，但不在两个范围中找到的元素，到始于 d_first 的范围。结果范围亦为已排序。

若某元素在 [first1, last1) 中找到 m 次而在 [first2, last2) 中找到 n 次，则将准确复制它 std::abs(m-n) 次到 d_first 。
    若 m>n ，则从[first1,last1) 复制末 m-n 个元素，否则从 [first2,last2) 复制末 n-m 个元素。结果范围不能与任一输入范围重叠。

1) 用 operator< 比较元素，而范围必须相对于相同标准已排序。
3) 用给定的二元比较函数 comp 比较元素，而范围必须相对相同标准已排序。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first1, last1	-	第一个输入的已排序范围
    first2, last2	-	第二个输入的已排序范围
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 概念的对象），若第一参数小于（即先序于）第二参数则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不必拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 InputIt1 与 InputIt2 类型的对象在解引用后能隐式转换到 Type1 与 Type2 两者。 ​

类型要求
    -InputIt1, InputIt2 必须满足 InputIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt1, ForwardIt2, ForwardIt3 必须满足 ForwardIterator 的要求。

返回值
构造范围的尾后迭代器。

复杂度
至多 2·(N1+N2-1) 次比较，其中 N1 = std::distance(first1, last1) 而 N2 = std::distance(first2, last2) 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class InputIt1, class InputIt2, class OutputIt>
    OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
                                    InputIt2 first2, InputIt2 last2,
                                    OutputIt d_first)
    {
        while (first1 != last1) {
            if (first2 == last2) return std::copy(first1, last1, d_first);
    
            if (*first1 < *first2) {
                *d_first++ = *first1++;
            } else {
                if (*first2 < *first1) {
                    *d_first++ = *first2;
                } else {
                    ++first1;
                }
                ++first2;
            }
        }
        return std::copy(first2, last2, d_first);
    }
版本二
    template<class InputIt1, class InputIt2,
            class OutputIt, class Compare>
    OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
                                    InputIt2 first2, InputIt2 last2,
                                    OutputIt d_first, Compare comp)
    {
        while (first1 != last1) {
            if (first2 == last2) return std::copy(first1, last1, d_first);
    
            if (comp(*first1, *first2)) {
                *d_first++ = *first1++;
            } else {
                if (comp(*first2, *first1)) {
                    *d_first++ = *first2;
                } else {
                    ++first1;
                }
                ++first2;
            }
        }
        return std::copy(first2, last2, d_first);
    }

示例

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
int main()
{
    std::vector<int> v1{1,2,3,4,5,6,7,8     };
    std::vector<int> v2{        5,  7,  9,10};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
 
    std::vector<int> v_symDifference;
 
    std::set_symmetric_difference(
        v1.begin(), v1.end(),
        v2.begin(), v2.end(),
        std::back_inserter(v_symDifference));
 
    for(int n : v_symDifference)
        std::cout << n << ' ';
}

输出：

1 2 3 4 6 8 9 10