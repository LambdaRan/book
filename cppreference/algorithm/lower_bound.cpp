

http://en.cppreference.com/w/cpp/algorithm/lower_bound

std::lower_bound

定义于头文件 <algorithm>
(1)	(C++20 前)
    template< class ForwardIt, class T >
    ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value );
    (C++20 起)
    template< class ForwardIt, class T >
    constexpr ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value );

(2)	(C++20 前)
    template< class ForwardIt, class T, class Compare >
    ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );
    (C++20 起)
    template< class ForwardIt, class T, class Compare >
    constexpr ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value, Compare comp );

返回指向范围 [first, last) 中首个不小于（即大于或等于） value 的元素的迭代器，或若找不到这种元素则返回 last 。

范围 [first, last) 必须已相对于表达式 element < value 或 comp(element, value) 划分。完全排序的范围满足此判别标准。
第一版本用 operator< 比较元素，第二版本用给定的比较函数 comp 。

参数
    first, last	-	定义要检验的已部分排序范围的迭代器
    value	-	要与元素比较的值
    comp	-	若第一参数小于（即先序于）第二个则返回 ​true 的二元谓词。
    谓词函数的签名应等价于如下者：
    bool pred(const Type1 &a, const Type2 &b);
    签名不必有 const & ，但函数必须不修改传递给它的对象。
    类型 Type1 必须使得 ForwardIt 类型的对象能在解引用后隐式转换到 Type1 。类型 Type2 必须使得 T 类型的对象能隐式转换到 Type2 。 ​

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。
    -Compare 必须满足 BinaryPredicate 的要求。不要求满足 Compare 。

返回值
    指向首个不小于 value 的元素的迭代器，或若找不到这种元素则为 last 。

复杂度
    进行的比较次数与 first 和 last 间的距离成对数（至多 log2(last - first) + O(1) 次比较）。
        然而，对于非随机访问迭代器 (RandomAccessIterator) ，迭代次自增次数为线性。

可能的实现
版本一
    template<class ForwardIt, class T>
    ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value)
    {
        ForwardIt it;
        typename std::iterator_traits<ForwardIt>::difference_type count, step;
        count = std::distance(first, last);
    
        while (count > 0) {
            it = first; 
            step = count / 2; 
            std::advance(it, step);
            if (*it < value) {
                first = ++it; 
                count -= step + 1; 
            }
            else
                count = step;
        }
        return first;
    }
版本二
    template<class ForwardIt, class T, class Compare>
    ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
    {
        ForwardIt it;
        typename std::iterator_traits<ForwardIt>::difference_type count, step;
        count = std::distance(first,last);
    
        while (count > 0) {
            it = first;
            step = count / 2;
            std::advance(it, step);
            if (comp(*it, value)) {
                first = ++it;
                count -= step + 1;
            }
            else
                count = step;
        }
        return first;
    }
示例

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
template<class ForwardIt, class T, class Compare=std::less<>>
ForwardIt binary_find(ForwardIt first, ForwardIt last, const T& value, Compare comp={})
{
    // 注意：类型 T 和 Forward 解引用后的类型都必须可隐式转换为
    // 用于 Compare 的 Type1 和 Type2 。
    // 这严格于 lower_bound 要求（见上述）
 
    first = std::lower_bound(first, last, value, comp);
    return first != last && !comp(value, *first) ? first : last;
}
 
int main()
{
    std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
 
    auto lower = std::lower_bound(data.begin(), data.end(), 4);
    auto upper = std::upper_bound(data.begin(), data.end(), 4);
 
    std::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
 
    std::cout << '\n';
 
    // 经典二分搜索，仅若存在才返回值
 
    data = { 1, 2, 4, 6, 9, 10 }; 
 
    auto it = binary_find(data.cbegin(), data.cend(), 4); // 选择 '5' 的 < 将返回 end()
 
    if(it != data.cend())
      std::cout << *it << " found at index "<< std::distance(data.cbegin(), it);
 
    return 0;
}

输出：
4 4 4 
4 found at index 2