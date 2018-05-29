

http://en.cppreference.com/w/cpp/algorithm/search

std::search

定义于头文件 <algorithm>
(1)	
    template< class ForwardIt1, class ForwardIt2 >
    ForwardIt1 search( ForwardIt1 first, ForwardIt1 last,
                    ForwardIt2 s_first, ForwardIt2 s_last );

    template< class ForwardIt1, class ForwardIt2 >
    constexpr ForwardIt1 search( ForwardIt1 first, ForwardIt1 last,
                                ForwardIt2 s_first, ForwardIt2 s_last );
(2)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    ForwardIt1 search( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                    ForwardIt2 s_first, ForwardIt2 s_last );

(3)	
    template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    ForwardIt1 search( ForwardIt1 first, ForwardIt1 last,
                    ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );

    template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    constexpr ForwardIt1 search( ForwardIt1 first, ForwardIt1 last,
                             ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );
(4)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class BinaryPredicate >
    ForwardIt1 search( ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last,
                    ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p );

(5)	
    template<class ForwardIterator, class Searcher>
    ForwardIterator search( ForwardIterator first, ForwardIterator last,
                            const Searcher& searcher );

    template<class ForwardIterator, class Searcher>
    constexpr ForwardIterator search( ForwardIterator first, ForwardIterator last,
                                    const Searcher& searcher );
                                    
1-4) 搜索范围 [first, last - (s_last - s_first)) 中元素子序列 [s_first, s_last) 的首次出现。
1) 元素用 operator== 比较。
3) 元素用给定的二元谓词 p 比较。
2,4) 同 (1,3) ，但按 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。
5) 在序列 [first, last) 中搜索 searcher 构造函数中指定的模式。
    等效地执行 return searcher(first, last).first; 。搜索器 (Searcher) 不必为可复制构造 (CopyConstructible) 。

标准库提供下列搜索器：
    default_searcher  (C++17) 
    标准 C++ 库搜索算法实现 
    (类模板)
    boyer_moore_searcher  (C++17) 
    Boyer-Moore 搜索算法实现 
    (类模板)
    boyer_moore_horspool_searcher  (C++17) 
    Boyer-Moore-Horspool 搜索算法实现 
    (类模板)
    (C++17 起)

参数
    first, last	-	要检验的元素范围
    s_first, s_last	-	要搜索的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    searcher	-	封装搜索算法和搜索模式的搜索器
    p	-	若元素应被当做相等则返回 ​true 的二元谓词。
    谓词函数的签名应等价于如下者：
    bool pred(const Type1 &a, const Type2 &b);
    签名不必有 const & ，但函数必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 ForwardIt1 与 ForwardIt2 类型的对象在解引用后分别能隐式转换到 Type1 与 Type2 。 ​

类型要求
    -ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。
    -Searcher 必须满足 Searcher 的要求。
返回值
    1-4) 指向范围中 [first, last - (s_last - s_first)) ，首个子序列 [s_first, s_last) 起始的迭代器。
        若找不到这种子序列，则返回 last 。
    若 [s_first, s_last) 为空，则返回 first 。(C++11 起)
    5) 返回 searcher.operator() 的结果，即指向找到的子串位置的迭代器，或若找不到则为 last 。
复杂度
    1-4) 至多 S*N 次搜索，其中 S = std::distance(s_first, s_last) 而 N = std::distance(first, last) 。
    5) 依赖于搜索器
异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class ForwardIt1, class ForwardIt2>
    ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 s_first, ForwardIt2 s_last)
    {
        for (; ; ++first) {
            ForwardIt1 it = first;
            for (ForwardIt2 s_it = s_first; ; ++it, ++s_it) {
                if (s_it == s_last) {
                    return first;
                }
                if (it == last) {
                    return last;
                }
                if (!(*it == *s_it)) {
                    break;
                }
            }
        }
    }
版本二
    template<class ForwardIt1, class ForwardIt2, class BinaryPredicate>
    ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                            ForwardIt2 s_first, ForwardIt2 s_last, 
                            BinaryPredicate p)
    {
        for (; ; ++first) {
            ForwardIt1 it = first;
            for (ForwardIt2 s_it = s_first; ; ++it, ++s_it) {
                if (s_it == s_last) {
                    return first;
                }
                if (it == last) {
                    return last;
                }
                if (!p(*it, *s_it)) {
                    break;
                }
            }
        }
    }

示例

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
 
template<typename Container>
bool in_quote(const Container& cont, const std::string& s)
{
    return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}
 
int main()
{
    std::string str = "why waste time learning, when ignorance is instantaneous?";
    // str.find() 也能使用
    std::cout << std::boolalpha << in_quote(str, "learning") << '\n'
                                << in_quote(str, "lemming")  << '\n';
 
    std::vector<char> vec(str.begin(), str.end());
    std::cout << std::boolalpha << in_quote(vec, "learning") << '\n'
                                << in_quote(vec, "lemming")  << '\n';
 
    // C++17 重载演示：
    std::string in = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
                     " sed do eiusmod tempor incididunt ut labore et dolore magna aliqua";
    std::string needle = "pisci";
    auto it = std::search(in.begin(), in.end(),
                   std::boyer_moore_searcher(
                       needle.begin(), needle.end()));
    if(it != in.end())
        std::cout << "The string " << needle << " found at offset "
                  << it - in.begin() << '\n';
    else
        std::cout << "The string " << needle << " not found\n";
}

输出：
    true
    false
    true
    false
    The string pisci found at offset 43