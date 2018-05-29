

http://en.cppreference.com/w/cpp/algorithm/find_first_of

std::find_first_of

定义于头文件 <algorithm>
(1)	
    template< class ForwardIt1, class ForwardIt2 >
    ForwardIt1 find_first_of( ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 s_first, ForwardIt2 s_last );

    template< class InputIt, class ForwardIt >
    InputIt find_first_of( InputIt first, InputIt last,
                        ForwardIt s_first, ForwardIt s_last );

    template< class InputIt, class ForwardIt >
    constexpr InputIt find_first_of( InputIt first, InputIt last,
                                    ForwardIt s_first, ForwardIt s_last );
(2)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    ForwardIt1 find_first_of( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last );

(3)	
    template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    ForwardIt1 find_first_of( ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );

    template< class InputIt, class ForwardIt, class BinaryPredicate >
    InputIt find_first_of( InputIt first, InputIt last,
                        ForwardIt s_first, ForwardIt s_last, BinaryPredicate p );

    template< class InputIt, class ForwardIt, class BinaryPredicate >
    constexpr InputIt find_first_of( InputIt first, InputIt last,
                                    ForwardIt s_first, ForwardIt s_last, BinaryPredicate p );
(4)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    ForwardIt1 find_first_of( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt last,
                        ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );

在范围 [first, last) 中搜索范围 [s_first, s_last) 中的任何元素。

1) 用 operator== 比较元素。
3) 用给定的二元谓词 p 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要检验的元素范围
    s_first, s_last	-	要搜索的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若元素应被当做相等则返回 ​true 的二元谓词。
    谓词函数的签名应等价于如下者：
    bool pred(const Type1 &a, const Type2 &b);
    签名不必有 const & ，但函数必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 ForwardIt1 与 ForwardIt2 类型的对象在解引用后分别能隐式转换到 Type1 与 Type2 。 ​

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -ForwardIt1 必须满足 ForwardIterator 的要求。
    -ForwardIt2 必须满足 ForwardIterator 的要求。

返回值
    指向范围 [first, last) 中等于来自范围 [s_first; s_last) 中一个元素的首个元素。若找不到这种元素，则返回 last 。

复杂度
    至多做 (S*N) 次比较，其中 S = distance(s_first, s_last) 而 N = distance(first, last) 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class InputIt, class ForwardIt>
    InputIt find_first_of(InputIt first, InputIt last,
                        ForwardIt s_first, ForwardIt s_last)
    {
        for (; first != last; ++first) {
            for (ForwardIt it = s_first; it != s_last; ++it) {
                if (*first == *it) {
                    return first;
                }
            }
        }
        return last;
    }
版本二
    template<class InputIt, class ForwardIt, class BinaryPredicate>
    InputIt find_first_of(InputIt first, InputIt last,
                        ForwardIt s_first, ForwardIt s_last,
                        BinaryPredicate p)
    {
        for (; first != last; ++first) {
            for (ForwardIt it = s_first; it != s_last; ++it) {
                if (p(*first, *it)) {
                    return first;
                }
            }
        }
        return last;
    }
示例
下列代码在 int 的 vector 中搜索任何一个指定的整数：

#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v{0, 2, 3, 25, 5};
    std::vector<int> t{3, 19, 10, 2};
 
    auto result = std::find_first_of(v.begin(), v.end(), t.begin(), t.end());
 
    if (result == v.end()) {
        std::cout << "no elements of v were equal to 3, 19, 10 or 2\n";
    } else {
        std::cout << "found a match at "
                  << std::distance(v.begin(), result) << "\n";
    }
}

输出：
found a match at 1