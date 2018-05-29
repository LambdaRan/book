

http://en.cppreference.com/w/cpp/algorithm/find_end

std::find_end

定义于头文件 <algorithm>
(1)	
    template< class ForwardIt1, class ForwardIt2 >
    ForwardIt1 find_end( ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last );
    template< class ForwardIt1, class ForwardIt2 >
    constexpr ForwardIt1 find_end( ForwardIt1 first, ForwardIt1 last,
                                ForwardIt2 s_first, ForwardIt2 s_last );
(2)	
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    ForwardIt1 find_end( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last );

(3)	
    template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    ForwardIt1 find_end( ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );

    template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    constexpr ForwardIt1 find_end( ForwardIt1 first, ForwardIt1 last,
                                ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );
(4) 
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    ForwardIt1 find_end( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );

在范围 [first, last) 中搜索最后的元素子列 [s_first, s_last) 。

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
    -ForwardIt1 必须满足 ForwardIterator 的要求。
    -ForwardIt2 必须满足 ForwardIterator 的要求。

返回值
    指向范围 [first, last) 中最后的子列 [s_first, s_last) 起始的迭代器。

    若找不到这种子列，则返回 last 。(C++11 前)
    若 [s_first, s_last) 为空或若找不到这种子列，则返回 last 。(C++11 起)

复杂度
    至多比较 S*(N-S+1) 次，其中 S = distance(s_first, s_last) 而 N = distance(first, last) 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class ForwardIt1, class ForwardIt2>
    ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last)
    {
        if (s_first == s_last)
            return last;
        ForwardIt1 result = last;
        while (true) {
            ForwardIt1 new_result = std::search(first, last, s_first, s_last);
            if (new_result == last) {
                break;
            } else {
                result = new_result;
                first = result;
                ++first;
            }
        }
        return result;
    }
版本二
    template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
                        ForwardIt2 s_first, ForwardIt2 s_last,
                        BinaryPredicate p)
    {
        if (s_first == s_last)
            return last;
        ForwardIt1 result = last;
        while (true) {
            ForwardIt1 new_result = std::search(first, last, s_first, s_last, p);
            if (new_result == last) {
                break;
            } else {
                result = new_result;
                first = result;
                ++first;
            }
        }
        return result;
    }

示例
下列代码用 find_end() 搜索二个不同的数列。

#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    std::vector<int>::iterator result;
 
    std::vector<int> t1{1, 2, 3};
 
    result = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
    if (result == v.end()) {
        std::cout << "subsequence not found\n";
    } else {
        std::cout << "last subsequence is at: "
                  << std::distance(v.begin(), result) << "\n";
    }
 
    std::vector<int> t2{4, 5, 6};
    result = std::find_end(v.begin(), v.end(), t2.begin(), t2.end());
    if (result == v.end()) {
        std::cout << "subsequence not found\n";
    } else {
        std::cout << "last subsequence is at: " 
                  << std::distance(v.begin(), result) << "\n";
    }
}
输出：
    last subsequence is at: 8
    subsequence not found