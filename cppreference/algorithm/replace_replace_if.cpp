
http://en.cppreference.com/w/cpp/algorithm/replace

std::replace, std::replace_if

定义于头文件 <algorithm>
(1)	
    template< class ForwardIt, class T >
    void replace( ForwardIt first, ForwardIt last,
                const T& old_value, const T& new_value );

    template< class ForwardIt, class T >
    constexpr void replace( ForwardIt first, ForwardIt last,
                            const T& old_value, const T& new_value );
(2)
    template< class ExecutionPolicy, class ForwardIt, class T >
    void replace( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last,
                const T& old_value, const T& new_value );

(3)	
    template< class ForwardIt, class UnaryPredicate, class T >
    void replace_if( ForwardIt first, ForwardIt last,
                    UnaryPredicate p, const T& new_value );

    template< class ForwardIt, class UnaryPredicate, class T >
    constexpr void replace_if( ForwardIt first, ForwardIt last,
                           UnaryPredicate p, const T& new_value );
(4)
    template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate, class T >
    void replace_if( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last,
                    UnaryPredicate p, const T& new_value );

以 new_value 替换范围 [first, last) 中所有满足特定判别标准的元素。

1) 替换所有等于 old_value 的元素。
3) 替换所有谓词 p 对其返回 true 的元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要处理的元素范围
    old_value	-	要被替换的元素值
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若应该替换元素则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 ForwardIt 类型对象能在解引用后隐式转换到 Type 。 ​

    new_value	-	用作替换者的值

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。
    -UnaryPredicate 必须满足 Predicate 的要求。
返回值
（无）

复杂度
    准确应用 last - first 次谓词。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

注意
    算法以引用接收 old_value 和 new_value ，故若任一者是到范围 [first, last) 中元素的引用，则算法能有不期待的行为。

可能的实现
版本一
    template<class ForwardIt, class T>
    void replace(ForwardIt first, ForwardIt last,
                const T& old_value, const T& new_value)
    {
        for (; first != last; ++first) {
            if (*first == old_value) {
                *first = new_value;
            }
        }
    }
版本二
    template<class ForwardIt, class UnaryPredicate, class T>
    void replace_if(ForwardIt first, ForwardIt last,
                    UnaryPredicate p, const T& new_value)
    {
        for (; first != last; ++first) {
            if(p(*first)) {
                *first = new_value;
            }
        }
    }
示例
下列代码首先在 int 的 vector 中以 88 替换 8 的所有出现，然后以 55 替换所有小于 5 的值。

#include <algorithm>
#include <array>
#include <iostream>
#include <functional>
 
int main()
{
    std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
 
    std::replace(s.begin(), s.end(), 8, 88);
 
    for (int a : s) {
        std::cout << a << " ";
    }
    std::cout << '\n';
 
    std::replace_if(s.begin(), s.end(), 
                    std::bind(std::less<int>(), std::placeholders::_1, 5), 55);
    for (int a : s) {
        std::cout << a << " ";
    }
    std::cout << '\n';
}

输出：
5 7 4 2 88 6 1 9 0 3
5 7 55 55 88 6 55 9 55 55