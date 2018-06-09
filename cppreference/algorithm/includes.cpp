
http://en.cppreference.com/w/cpp/algorithm/includes

std::includes
如果一个集合是另一个集合的子集（函数模板），则返回true 

定义于头文件 <algorithm>
(1)	(C++20 前)
    template< class InputIt1, class InputIt2 >
    bool includes( InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2 );
    (C++20 起)
    template< class InputIt1, class InputIt2 >
    constexpr bool includes( InputIt1 first1, InputIt1 last1,
                            InputIt2 first2, InputIt2 last2 );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2 >
    bool includes( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1,
                ForwardIt2 first2, ForwardIt2 last2 );

(3)	(C++20 前)
    template< class InputIt1, class InputIt2, class Compare >
    bool includes( InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2, Compare comp );
    (C++20 起)
    template< class InputIt1, class InputIt2, class Compare >
    constexpr bool includes( InputIt1 first1, InputIt1 last1,
                            InputIt2 first2, InputIt2 last2, Compare comp );
(4)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class Compare >
    bool includes( ExecutionPolicy&& policy, ForwardIt1 first1, ForwardIt1 last1,
                ForwardIt2 first2, ForwardIt2 last2, Compare comp );

若已排序范围 [first2, last2) 是已排序范围 [first1, last1) 的子序列则返回 true 。

1) 两个范围都必须以 operator< 排序。
3) 两个范围都必须以给定的比较函数 comp 排序。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first1, last1	-	要检验的已排序元素范围
    first2, last2	-	要搜索的已排序元素范围
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 概念的对象），若第一参数小于（即先序于）第二参数则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不必拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 InputIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -InputIt1, InputIt2 必须满足 InputIterator 的要求。
    -ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。

返回值
    若 [first2, last2) 是 [first1, last1) 的子序列则为 true ；否则为 false 。

复杂度
    至多 2·(N1+N2-1) 次比较，其中 N1 = std::distance(first1, last1) 而 N2 = std::distance(first2, last2) 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class InputIt1, class InputIt2>
    bool includes(InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2)
    {
        for (; first2 != last2; ++first1)
        {
            if (first1 == last1 || *first2 < *first1)
                return false;
            if ( !(*first1 < *first2) )
                ++first2;
        }
        return true;
    }
版本二
    template<class InputIt1, class InputIt2>
    bool includes(InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2, Compare comp)
    {
        for (; first2 != last2; ++first1)
        {
            if (first1 == last1 || comp(*first2, *first1))
                return false;
            if (!comp(*first1, *first2))
                ++first2;
        }
        return true;
    }
示例

#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
 
int main()
{
  std::vector<char> v1 {'a', 'b', 'c', 'f', 'h', 'x'};
  std::vector<char> v2 {'a', 'b', 'c'};
  std::vector<char> v3 {'a', 'c'};
  std::vector<char> v4 {'g'};
  std::vector<char> v5 {'a', 'c', 'g'};
 
  for (auto i : v1) std::cout << i << ' ';
  std::cout << "\nincludes:\n" << std::boolalpha;
 
  for (auto i : v2) std::cout << i << ' ';
  std::cout << ": " << std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << '\n';
  for (auto i : v3) std::cout << i << ' ';
  std::cout << ": " << std::includes(v1.begin(), v1.end(), v3.begin(), v3.end()) << '\n';
  for (auto i : v4) std::cout << i << ' ';
  std::cout << ": " << std::includes(v1.begin(), v1.end(), v4.begin(), v4.end()) << '\n';
  for (auto i : v5) std::cout << i << ' ';
  std::cout << ": " << std::includes(v1.begin(), v1.end(), v5.begin(), v5.end()) << '\n';
 
  auto cmp_nocase = [](char a, char b) {
    return std::tolower(a) < std::tolower(b);
  };
 
  std::vector<char> v6 {'A', 'B', 'C'};
  for (auto i : v6) std::cout << i << ' ';
  std::cout << ": (case-insensitive) "
            << std::includes(v1.begin(), v1.end(), v6.begin(), v6.end(), cmp_nocase)
            << '\n';
}

输出：

a b c f h x
includes:
a b c : true
a c : true
g : false
a c g : false
A B C : (case-insensitive) true