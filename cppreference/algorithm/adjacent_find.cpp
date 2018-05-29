

http://en.cppreference.com/w/cpp/algorithm/adjacent_find


std::adjacent_find

定义于头文件 <algorithm>
(1)	
    template< class ForwardIt >
    ForwardIt adjacent_find( ForwardIt first, ForwardIt last );

    template< class ForwardIt >
    constexpr ForwardIt adjacent_find( ForwardIt first, ForwardIt last );
(2)	
    template< class ExecutionPolicy, class ForwardIt >
    ForwardIt adjacent_find( ExecutionPolicy&& policy,
                            ForwardIt first, ForwardIt last );

(3)	
    template< class ForwardIt, class BinaryPredicate>
    ForwardIt adjacent_find( ForwardIt first, ForwardIt last, BinaryPredicate p );

    template< class ForwardIt, class BinaryPredicate>
    constexpr ForwardIt adjacent_find( ForwardIt first, ForwardIt last, BinaryPredicate p );
(4)
    template< class ExecutionPolicy, class ForwardIt, class BinaryPredicate>
    ForwardIt adjacent_find( ExecutionPolicy&& policy,
                            ForwardIt first, ForwardIt last, BinaryPredicate p );

在范围 [first, last) 中搜索二个相继的等同元素。

1) 用 operator== 比较元素。
3) 用给定的二元谓词 p 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要检验的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若元素应被当做相等则返回 ​true 的二元谓词。
    谓词函数的签名应等价于如下者：
    bool pred(const Type1 &a, const Type2 &b);
    签名不必有 const & ，但函数必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 ForwardIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。

返回值
    指向首对等同元素的首个元素的迭代器，
        即首个满足 *it == *(it+1) （第一版本）或 p(*it, *(it + 1)) != false（第二版本）的迭代器 it 。
    若找不到这种元素，则返回 last 。

复杂度
    1,3) 准确应用 min((result-first)+1, (last-first)-1) 次谓词，其中 result 是返回值。
    2,4) 应用 O(last-first) 次对应的谓词。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class ForwardIt>
    ForwardIt adjacent_find(ForwardIt first, ForwardIt last)
    {
        if (first == last) {
            return last;
        }
        ForwardIt next = first;
        ++next;
        for (; next != last; ++next, ++first) {
            if (*first == *next) {
                return first;
            }
        }
        return last;
    }
版本二
    template<class ForwardIt, class BinaryPredicate>
    ForwardIt adjacent_find(ForwardIt first, ForwardIt last, 
                            BinaryPredicate p)
    {
        if (first == last) {
            return last;
        }
        ForwardIt next = first;
        ++next;
        for (; next != last; ++next, ++first) {
            if (p(*first, *next)) {
                return first;
            }
        }
        return last;
    }

示例

#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v1{0, 1, 2, 3, 40, 40, 41, 41, 5};
 
    auto i1 = std::adjacent_find(v1.begin(), v1.end());
 
    if (i1 == v1.end()) {
        std::cout << "no matching adjacent elements\n";
    } else {
        std::cout << "the first adjacent pair of equal elements at: "
                  << std::distance(v1.begin(), i1) << '\n';
    }
 
    auto i2 = std::adjacent_find(v1.begin(), v1.end(), std::greater<int>());
    if (i2 == v1.end()) {
        std::cout << "The entire vector is sorted in ascending order\n";
    } else {
        std::cout << "The last element in the non-decreasing subsequence is at: "
                  << std::distance(v1.begin(), i2) << '\n';
    }
}

输出：
The first adjacent pair of equal elements at: 4
The last element in the non-decreasing subsequence is at: 7