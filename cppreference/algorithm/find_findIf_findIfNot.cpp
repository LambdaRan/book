

http://en.cppreference.com/w/cpp/algorithm/find

std::find, std::find_if, std::find_if_not

定义于头文件 <algorithm>
(1)	
    template< class InputIt, class T >
    InputIt find( InputIt first, InputIt last, const T& value );

    template< class InputIt, class T >
    constexpr InputIt find( InputIt first, InputIt last, const T& value );
(2)
    template< class ExecutionPolicy, class ForwardIt, class T >
    ForwardIt find( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, const T& value );

(3)	
    template< class InputIt, class UnaryPredicate >
    InputIt find_if( InputIt first, InputIt last, 
                    UnaryPredicate p );

    template< class InputIt, class UnaryPredicate >
    constexpr InputIt find_if( InputIt first, InputIt last, 
                            UnaryPredicate p );
(4)
    template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
    ForwardIt find_if( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, 
                    UnaryPredicate p );

(5)	
    template< class InputIt, class UnaryPredicate >
    InputIt find_if_not( InputIt first, InputIt last, 
                        UnaryPredicate q );

    template< class InputIt, class UnaryPredicate >
    constexpr InputIt find_if_not( InputIt first, InputIt last, 
                                UnaryPredicate q );
(6)
    template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
    ForwardIt find_if_not( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, 
                        UnaryPredicate q );

返回范围 [first, last) 中满足特定判别标准的首个元素：

1) find 搜索等于 value 的元素。
3) find_if 搜索谓词 p 对其返回 true 的元素。
5) find_if_not 搜索谓词 q 对其返回 false 的元素。
2,4,6) 同 (1,3,5) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要检验的元素范围
    value	-	要与元素比较的值
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若为要求的元素则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 InputIt 类型对象能在解引用后隐式转换到 Type 。 ​

    q	-	若为要求的元素则返回 false 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 InputIt 类型对象能在解引用后隐式转换到 Type 。 ​

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -ForwardIt 必须满足 ForwardIterator 的要求。
    -UnaryPredicate 必须满足 Predicate 的要求。

返回值
    指向首个满足条件的迭代器，或若找不到这种元素则为 last 。

复杂度
    至多应用 last - first 次谓词。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class InputIt, class T>
    InputIt find(InputIt first, InputIt last, const T& value)
    {
        for (; first != last; ++first) {
            if (*first == value) {
                return first;
            }
        }
        return last;
    }
版本二
    template<class InputIt, class UnaryPredicate>
    InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        for (; first != last; ++first) {
            if (p(*first)) {
                return first;
            }
        }
        return last;
    }
版本三
    template<class InputIt, class UnaryPredicate>
    InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate q)
    {
        for (; first != last; ++first) {
            if (!q(*first)) {
                return first;
            }
        }
        return last;
    }

若你没有 C++11 ，则 std::find_if_not 的等价版本是以取反的谓词使用 std::find_if 。

    template<class InputIt, class UnaryPredicate>
    InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate q)
    {
        return std::find_if(first, last, std::not1(q));
    }

示例
下列示例在 int 的 vector 中寻找整数。

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
 
int main()
{
    int n1 = 3;
    int n2 = 5;
 
    std::vector<int> v{0, 1, 2, 3, 4};
 
    auto result1 = std::find(std::begin(v), std::end(v), n1);
    auto result2 = std::find(std::begin(v), std::end(v), n2);
 
    if (result1 != std::end(v)) {
        std::cout << "v contains: " << n1 << '\n';
    } else {
        std::cout << "v does not contain: " << n1 << '\n';
    }
 
    if (result2 != std::end(v)) {
        std::cout << "v contains: " << n2 << '\n';
    } else {
        std::cout << "v does not contain: " << n2 << '\n';
    }
}

输出：
    v contains: 3
    v does not contain: 5