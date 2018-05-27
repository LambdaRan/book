
http://en.cppreference.com/w/cpp/algorithm/merge

std::merge
定义于头文件 <algorithm>
(1)	
    template< class InputIt1, class InputIt2, class OutputIt >
    OutputIt merge( InputIt1 first1, InputIt1 last1,
                    InputIt2 first2, InputIt2 last2,
                    OutputIt d_first );

    template< class InputIt1, class InputIt2, class OutputIt >
    constexpr OutputIt merge( InputIt1 first1, InputIt1 last1,
                            InputIt2 first2, InputIt2 last2,
                            OutputIt d_first );

(2)	
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class ForwardIt3 >
    ForwardIt3 merge( ExecutionPolicy&& policy,
                    ForwardIt1 first1, ForwardIt1 last1,
                    ForwardIt2 first2, ForwardIt2 last2,
                    ForwardIt3 d_first );

(3)	
    template< class InputIt1, class InputIt2, class OutputIt, class Compare>
    OutputIt merge( InputIt1 first1, InputIt1 last1,
                    InputIt2 first2, InputIt2 last2,
                    OutputIt d_first, Compare comp );

    template< class InputIt1, class InputIt2, class OutputIt, class Compare>
    constexpr OutputIt merge( InputIt1 first1, InputIt1 last1,
                            InputIt2 first2, InputIt2 last2,
                            OutputIt d_first, Compare comp );

(4)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class ForwardIt3, class Compare>
    ForwardIt3 merge( ExecutionPolicy&& policy,
                    ForwardIt1 first1, ForwardIt1 last1,
                    ForwardIt2 first2, ForwardIt2 last2,
                    ForwardIt3 d_first, Compare comp );


归并二个已排序范围 [first1, last1) 和 [first2, last2) 到始于 d_first 的一个已排序范围中。

1) 用 operator< 比较元素。
3) 用给定的二元比较函数 comp 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>>
    为 true 才参与重载决议。
    
对于元范围中的等价元素，来自第一范围的元素（保持其原顺序）先于来自第二范围的元素（保持其原顺序）。
若目标范围与输入范围之一重叠，则行为未定义（输入范围可相互重叠）。

参数
    first1, last1	-	要归并的元素的第一范围
    first2, last2	-	要归并到元素的第二范围
    d_first	-	目标范围的起始
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 概念的对象），若第一参数小于（即先序于）第二参数则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不必拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 InputIt1 与 InputIt2 类型的对象在解引用后能隐式转换到 Type1 与 Type2 两者。 ​

类型要求
    -InputIt1, InputIt2 必须满足 InputIterator 的要求。
    -ForwardIt1, ForwardIt2, ForwardIt3 必须满足 ForwardIterator 的要求。
    -OutputIt 必须满足 OutputIterator 的要求。

返回值
    指向最后复制元素后一元素的迭代器。

复杂度
    1,3) 至多 std::distance(first1, last1) + std::distance(first2, last2) - 1 次比较。
    2,4) O(std::distance(first1, last1) + std::distance(first2, last2)) 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：
        若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
            对于任何其他 ExecutionPolicy ，行为是实现定义的。
        若算法无法分配内存，则抛出 std::bad_alloc 。

注意
    此算法进行类似 std::set_union 所做的任务。都消耗二个已排序输入范围，并产生拥有来自两个输入的元素的输出。
    刺二算法的区别在于处理来自二个输入的比较等价（见可比较小于 (LessThanComparable) 上的注意）的值。
    若任何等价的值在第一范围出现 n 次，在第二范围出现 m 此，则 std::merge 会输出所有 n+m 此出现，
    而 std::set_union 将只输出 std::max(n, m) 次。
    故 std::merge 准确输出 std::distance(first1, last1) + std::distance(first2, last2) 个值，
    而 std::set_union 可能产生得更少。

可能的实现
版本一
    template<class InputIt1, class InputIt2, class OutputIt>
    OutputIt merge(InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2,
                OutputIt d_first)
    {
        for (; first1 != last1; ++d_first) {
            if (first2 == last2) {
                return std::copy(first1, last1, d_first);
            }
            if (*first2 < *first1) {
                *d_first = *first2;
                ++first2;
            } else {
                *d_first = *first1;
                ++first1;
            }
        }
        return std::copy(first2, last2, d_first);
    }
版本二
    template<class InputIt1, class InputIt2,
            class OutputIt, class Compare>
    OutputIt merge(InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2,
                OutputIt d_first, Compare comp)
    {
        for (; first1 != last1; ++d_first) {
            if (first2 == last2) {
                return std::copy(first1, last1, d_first);
            }
            if (comp(*first2, *first1)) {
                *d_first = *first2;
                ++first2;
            } else {
                *d_first = *first1;
                ++first1;
            }
        }
        return std::copy(first2, last2, d_first);
    }

示例

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>
 
int main()
{
    // 以随机数填充 vector
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(0, 9);
 
    std::vector<int> v1(10), v2(10);
    std::generate(v1.begin(), v1.end(), std::bind(dis, std::ref(mt)));
    std::generate(v2.begin(), v2.end(), std::bind(dis, std::ref(mt)));
 
    // 排序
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
 
    // 输出 v1
    std::cout << "v1 : ";
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
 
    // 输出 v2
    std::cout << "v2 : ";
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
 
    // 归并
    std::vector<int> dst;
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));
 
    // 输出
    std::cout << "dst: ";
    std::copy(dst.begin(), dst.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
}

可能的输出：
v1 : 0 1 3 4 4 5 5 8 8 9 
v2 : 0 2 2 3 6 6 8 8 8 9 
dst: 0 0 1 2 2 3 3 4 4 5 5 6 6 8 8 8 8 8 9 9