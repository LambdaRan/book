

http://en.cppreference.com/w/cpp/algorithm/mismatch


std::mismatch
定义于头文件 <algorithm>
(1)	
    template< class InputIt1, class InputIt2 >
    std::pair<InputIt1,InputIt2>
        mismatch( InputIt1 first1, InputIt1 last1,
                InputIt2 first2 );
    template< class InputIt1, class InputIt2 >
    constexpr std::pair<InputIt1,InputIt2>
                mismatch( InputIt1 first1, InputIt1 last1,
                            InputIt2 first2 );
(2)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    std::pair<ForwardIt1,ForwardIt2>
        mismatch( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1,
                ForwardIt2 first2 );

(3)	
    template< class InputIt1, class InputIt2, class BinaryPredicate >
    std::pair<InputIt1,InputIt2>
        mismatch( InputIt1 first1, InputIt1 last1,
                InputIt2 first2,
                BinaryPredicate p );

    template< class InputIt1, class InputIt2, class BinaryPredicate >
    constexpr std::pair<InputIt1,InputIt2>
                mismatch( InputIt1 first1, InputIt1 last1,
                            InputIt2 first2,
                            BinaryPredicate p );
(4)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    std::pair<ForwardIt1,ForwardIt2>
        mismatch( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1,
                ForwardIt2 first2,
                BinaryPredicate p );

(5)	
    template< class InputIt1, class InputIt2 >
    std::pair<InputIt1,InputIt2>
        mismatch( InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2 );

    template< class InputIt1, class InputIt2 >
    constexpr std::pair<InputIt1,InputIt2>
                mismatch( InputIt1 first1, InputIt1 last1,
                            InputIt2 first2, InputIt2 last2 );
(6)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    std::pair<ForwardIt1,ForwardIt2>
        mismatch( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1,
                ForwardIt2 first2, ForwardIt2 last2 );

(7)	
    template< class InputIt1, class InputIt2, class BinaryPredicate >
    std::pair<InputIt1,InputIt2>
        mismatch( InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2,
                BinaryPredicate p );

    template< class InputIt1, class InputIt2, class BinaryPredicate >
    constexpr std::pair<InputIt1,InputIt2>
                mismatch( InputIt1 first1, InputIt1 last1,
                            InputIt2 first2, InputIt2 last2,
                        BinaryPredicate p );
(8)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    std::pair<ForwardIt1,ForwardIt2>
        mismatch( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1,
                ForwardIt2 first2, ForwardIt2 last2,
                BinaryPredicate p );

返回来自二个范围：一个以 [first1, last1) 定义而另一个以 [first2,last2) 定义，的首个不匹配对。
    若不提供 last2 （重载 (1-4) ），则它指代 first2 + (last1 - first1) 。

1,5) 用 operator== 比较元素。
3,7) 用给定的二元谓词 p 比较元素。
2,4,6,8) 同 (1,3,5,7) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first1, last1	-	第一元素范围
    first2, last2	-	第二元素范围
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若元素应被当做相等则返回 ​true 的二元谓词。
    谓词函数的签名应等价于如下者：
    bool pred(const Type1 &a, const Type2 &b);
    签名不必有 const & ，但函数必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 InputIt1 与 InputIt2 类型的对象在解引用后分别能隐式转换到 Type1 与 Type2 。 ​

类型要求
    -InputIt1 必须满足 InputIterator 的要求。
    -InputIt2 必须满足 InputIterator 的要求。
    -ForwardIt1 必须满足 ForwardIterator 的要求。
    -ForwardIt2 必须满足 ForwardIterator 的要求。
    -BinaryPredicate 必须满足 BinaryPredicate 的要求。

返回值
    带指向首二个不等价元素的迭代器的 std::pair 。

    若比较抵达 last1 时未找到不匹配，则该 pair 保有 last1 和来自第二范围的对应迭代器。
        若第二范围小于第一范围则行为未定义。	(C++14 前)
    若比较抵达 last1 或 last2 中首先发生者时未找到不匹配，则该 pair 保有尾迭代器和来自另一范围的对应迭代器。(C++14 起)

复杂度
    1-4) 至多 last1 - first1 次应用 operator== 或谓词 p 。
    5-8) 至多 min(last1 - first1, last2 - first2) 次应用 operator== 或谓词 p 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class InputIt1, class InputIt2>
    std::pair<InputIt1, InputIt2>
        mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        while (first1 != last1 && *first1 == *first2) {
            ++first1, ++first2;
        }
        return std::make_pair(first1, first2);
    }
版本二
    template<class InputIt1, class InputIt2, class BinaryPredicate>
    std::pair<InputIt1, InputIt2>
        mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
    {
        while (first1 != last1 && p(*first1, *first2)) {
            ++first1, ++first2;
        }
        return std::make_pair(first1, first2);
    }
版本三
    template<class InputIt1, class InputIt2>
    std::pair<InputIt1, InputIt2>
        mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        while (first1 != last1 && first2 != last2 && *first1 == *first2) {
            ++first1, ++first2;
        }
        return std::make_pair(first1, first2);
    }
版本四
    template<class InputIt1, class InputIt2, class BinaryPredicate>
    std::pair<InputIt1, InputIt2>
        mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate p)
    {
        while (first1 != last1 && first2 != last2 && p(*first1, *first2)) {
            ++first1, ++first2;
        }
        return std::make_pair(first1, first2);
    }

示例
此程序确定同时在给定字符串起始与在其结尾按逆序同时找到的最长子串（可能重叠）。

#include <iostream>
#include <string>
#include <algorithm>
 
std::string mirror_ends(const std::string& in)
{
    return std::string(in.begin(),
                       std::mismatch(in.begin(), in.end(), in.rbegin()).first);
}
 
int main()
{
    std::cout << mirror_ends("abXYZba") << '\n'
              << mirror_ends("abca") << '\n'
              << mirror_ends("aba") << '\n';
}

输出：
    ab
    a
    aba