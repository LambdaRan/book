

http://en.cppreference.com/w/cpp/algorithm/all_any_none_of


std::all_of, std::any_of, std::none_of

定义于头文件 <algorithm>
(1)	
    template< class InputIt, class UnaryPredicate >
    bool all_of( InputIt first, InputIt last, UnaryPredicate p );

    template< class InputIt, class UnaryPredicate >
    constexpr bool all_of( InputIt first, InputIt last, UnaryPredicate p );
(2)
    template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
    bool all_of( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p );

(3)	
    template< class InputIt, class UnaryPredicate >
    bool any_of( InputIt first, InputIt last, UnaryPredicate p );

    template< class InputIt, class UnaryPredicate >
    constexpr bool any_of( InputIt first, InputIt last, UnaryPredicate p );
(4)
    template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
    bool any_of( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p );

(5)	
    template< class InputIt, class UnaryPredicate >
    bool none_of( InputIt first, InputIt last, UnaryPredicate p );

    template< class InputIt, class UnaryPredicate >
    constexpr bool none_of( InputIt first, InputIt last, UnaryPredicate p );
(6)
    template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
    bool none_of( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p );

1) 检查一元谓词 p 是否对范围 [first, last) 中所有元素返回 true 。
3) 检查一元谓词 p 是否对范围 [first, last) 中至少一个元素返回 true 。
5) 检查一元谓词 p 是否不对范围 [first, last) 中任何元素返回 true 。
2,4,6) 同 (1,3,5) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要检验的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    p	-	一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 InputIt 类型对象能在解引用后隐式转换到 Type 。 ​

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -ForwardIt 必须满足 ForwardIterator 的要求。
    -UnaryPredicate 必须满足 Predicate 的要求。

返回值
    1-2) 若一元谓词对范围中所有元素返回 true 则为 true ，否则为 false 。若范围为空则返回 true 。
    3-4) 若一元谓词对范围中至少一个元素返回 true 则为 true ，否则为 false 。若范围为空则返回 false 。
    5-6) 若一元谓词不对范围中任何元素返回 true 则为 true ，否则为 false 。若范围为空则返回 true 。
    
复杂度
    1,3,5) 至多应用谓词 last - first 次
    2,4,6) 应用谓词 O(last-first) 次

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template< class InputIt, class UnaryPredicate >
    bool all_of(InputIt first, InputIt last, UnaryPredicate p)
    {
        return std::find_if_not(first, last, p) == last;
    }
版本二
    template< class InputIt, class UnaryPredicate >
    bool any_of(InputIt first, InputIt last, UnaryPredicate p)
    {
        return std::find_if(first, last, p) != last;
    }
版本三
    template< class InputIt, class UnaryPredicate >
    bool none_of(InputIt first, InputIt last, UnaryPredicate p)
    {
        return std::find_if(first, last, p) == last;
    }

示例

#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
 
int main()
{
    std::vector<int> v(10, 2);
    std::partial_sum(v.cbegin(), v.cend(), v.begin());
    std::cout << "Among the numbers: ";
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
 
    if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
        std::cout << "All numbers are even\n";
    }
    if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), 
                                                     std::placeholders::_1, 2))) {
        std::cout << "None of them are odd\n";
    }
    struct DivisibleBy
    {
        const int d;
        DivisibleBy(int n) : d(n) {}
        bool operator()(int n) const { return n % d == 0; }
    };
 
    if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
        std::cout << "At least one number is divisible by 7\n";
    }
}

输出：
    Among the numbers: 2 4 6 8 10 12 14 16 18 20 
    All numbers are even
    None of them are odd
    At least one number is divisible by 7