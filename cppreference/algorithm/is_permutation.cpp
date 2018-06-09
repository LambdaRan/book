

http://en.cppreference.com/w/cpp/algorithm/is_permutation

std::is_permutation
  C++ 算法库 
定义于头文件 <algorithm>
(1)	
template< class ForwardIt1, class ForwardIt2 >
bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                     ForwardIt2 first2 );
(C++11 起) 
(C++20 前)
template< class ForwardIt1, class ForwardIt2 >
constexpr bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                               ForwardIt2 first2 );
(C++20 起)
(2)	
template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                     ForwardIt2 first2, BinaryPredicate p );
(C++11 起) 
(C++20 前)
template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
constexpr bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                               ForwardIt2 first2, BinaryPredicate p );
(C++20 起)
(3)	
template< class ForwardIt1, class ForwardIt2 >
bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                     ForwardIt2 first2, ForwardIt2 last2 );
(C++14 起) 
(C++20 前)
template< class ForwardIt1, class ForwardIt2 >
constexpr bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                               ForwardIt2 first2, ForwardIt2 last2 );
(C++20 起)
(4)	
template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                     ForwardIt2 first2, ForwardIt2 last2,
                     BinaryPredicate p );
(C++14 起) 
(C++20 前)
template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
constexpr bool is_permutation( ForwardIt1 first1, ForwardIt1 last1,
                               ForwardIt2 first2, ForwardIt2 last2,
                               BinaryPredicate p );
(C++20 起)
若存在范围 [first1, last1) 中元素的排列，使得该范围等于 [first2,last2) ，则返回 true ，若不给出，则其中 last2 代表 first2 + (last1 - first1) 。

1,3) 用 operator== 比较元素。若它不是等价关系则行为未定义。
2,4) 用给定的二元谓词 p 比较元素。若它不是等价关系则行为未定义。
参数
first1, last1	-	要比较的元素范围
first2, last2	-	要比较的第二范围
p	-	若元素应被当做相等则返回 ​true 的二元谓词。
谓词函数的签名应等价于如下：

 bool pred(const Type &a, const Type &b);

Type 应是 ForwardIt1 和 ForwardIt2 共同的值类型。签名不必有 const & ，但函数必须不修改传递给它的对象。 ​

类型要求
-ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。
-ForwardIt1, ForwardIt2 必须拥有相同的 value_type 。
返回值
若范围 [first1, last1) 是 [first2, last2) 的排列则为 true 。

复杂度
至多应用 O(N2) 次谓词，或若序列已经相等，则准确应用 N 次，其中 N=std::distance(first1, last1) 。

然而，若 ForwardIt1 和 ForwardIt2 满足随机访问迭代器 (RandomAccessIterator) 的要求且 std::distance(first1, last1) != std::distance(first2, last2) ，则不应用谓词。

可能的实现
template<class ForwardIt1, class ForwardIt2>
bool is_permutation(ForwardIt1 first, ForwardIt1 last,
                    ForwardIt2 d_first)
{
   // 跳过公共前缀
   std::tie(first, d_first) = std::mismatch(first, last, d_first);
   // 在 rest 上迭代，计数 [d_first, d_last) 中出现多少次
   // 每个来自 [first, last) 的元素
   if (first != last) {
       ForwardIt2 d_last = d_first;
       std::advance(d_last, std::distance(first, last));
       for (ForwardIt1 i = first; i != last; ++i) {
            if (i != std::find(first, i, *i)) continue; // 已经遇到此 *i
 
            auto m = std::count(d_first, d_last, *i);
            if (m==0 || std::count(i, last, *i) != m) {
                return false;
            }
        }
    }
    return true;
}
示例
运行此代码
#include <algorithm>
#include <vector>
#include <iostream>
int main()
{
    std::vector<int> v1{1,2,3,4,5};
    std::vector<int> v2{3,5,4,1,2};
    std::cout << "3,5,4,1,2 is a permutation of 1,2,3,4,5? "
              << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v2.begin()) << '\n';
 
    std::vector<int> v3{3,5,4,1,1};
    std::cout << "3,5,4,1,1 is a permutation of 1,2,3,4,5? "
              << std::boolalpha
              << std::is_permutation(v1.begin(), v1.end(), v3.begin()) << '\n';
}
输出：

3,5,4,1,2 is a permutation of 1,2,3,4,5? true
3,5,4,1,1 is a permutation of 1,2,3,4,5? false