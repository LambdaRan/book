

http://en.cppreference.com/w/cpp/algorithm/binary_search

std::binary_search

定义于头文件 <algorithm>
(1)	(C++20 前)
    template< class ForwardIt, class T >
    bool binary_search( ForwardIt first, ForwardIt last, const T& value );
    (C++20 起)
    template< class ForwardIt, class T >
    constexpr bool binary_search( ForwardIt first, ForwardIt last, const T& value );

(2)	(C++20 前)
    template< class ForwardIt, class T, class Compare >
    bool binary_search( ForwardIt first, ForwardIt last, const T& value, Compare comp );
    (C++20 起)
    template< class ForwardIt, class T, class Compare >
    constexpr bool binary_search( ForwardIt first, ForwardIt last, const T& value, Compare comp );

检查等价于 value 的元素是否出现于范围 [first, last) 中。

对于要成功的 std::binary_search ，范围 [first, last) 必须至少部分排序，即它必须满足下列所有要求：

已相对 element < value 或 comp(element, value) 划分
已相对 !(value < element) 或 !comp(value, element) 划分
对于所有元素，若 element < value 或 comp(element, value) 为 true ，
    则 !(value < element) 或 !comp(value, element) 亦为 true
完全排序的范围满足这些判别标准。

第一版本用 operator< 比较元素，第二版本用给定的比较函数 comp 。

参数
    first, last	-	要检验的元素范围
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
    若找到等于 value 的元素则为 true ，否则为 false 。

复杂度
    进行的比较次数与 first 和 last 间的距离成对数（至多 log2(last - first) + O(1) 次比较）。
        然而，对于非随机访问迭代器 (RandomAccessIterator) ，迭代次自增次数为线性。

可能的实现
版本一
    template<class ForwardIt, class T>
    bool binary_search(ForwardIt first, ForwardIt last, const T& value)
    {
        first = std::lower_bound(first, last, value);
        return (!(first == last) && !(value < *first));
    }
版本二
    template<class ForwardIt, class T, class Compare>
    bool binary_search(ForwardIt first, ForwardIt last, const T& value, Compare comp)
    {
        first = std::lower_bound(first, last, value, comp);
        return (!(first == last) && !(comp(value, *first)));
    }
示例

#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    std::vector<int> haystack {1, 3, 4, 5, 9};
    std::vector<int> needles {1, 2, 3};
 
    for (auto needle : needles) {
        std::cout << "Searching for " << needle << '\n';
        if (std::binary_search(haystack.begin(), haystack.end(), needle)) {
            std::cout << "Found " << needle << '\n';
        } else {
            std::cout << "no dice!\n";
        }
    }
}

输出：

Searching for 1
Found 1
Searching for 2
no dice!
Searching for 3
Found 3