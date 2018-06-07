
http://en.cppreference.com/w/cpp/algorithm/equal_range

std::equal_range

定义于头文件 <algorithm>
(1)	(C++20 前)
    template< class ForwardIt, class T >
    std::pair<ForwardIt,ForwardIt> 
        equal_range( ForwardIt first, ForwardIt last, const T& value );
    (C++20 起)
    template< class ForwardIt, class T >
    constexpr std::pair<ForwardIt,ForwardIt> 
                equal_range( ForwardIt first, ForwardIt last, const T& value );

(2) (C++20 前)	
    template< class ForwardIt, class T, class Compare >
    std::pair<ForwardIt,ForwardIt> 
        equal_range( ForwardIt first, ForwardIt last, const T& value, Compare comp );
    (C++20 起)
    template< class ForwardIt, class T, class Compare >
    constexpr std::pair<ForwardIt,ForwardIt> 
                equal_range( ForwardIt first, ForwardIt last, const T& value, Compare comp );

返回范围 [first, last) 中含有所有等价于 value 的元素的范围。

范围 [first, last) 必须相对于与 value 的比较已排序，即它必须满足下列所有要求：

已相对 element < value 或 comp(element, value) 划分
已相对 !(value < element) 或 !comp(value, element) 划分
对于所有元素，若 element < value 或 comp(element, value) 为 true ，
    则 !(value < element) 或 !comp(value, element) 亦为 true
完全排序的范围满足这些判别标准。

以二个迭代器定义返回的范围，一个指向首个不小于 value 的元素，而另一个指向首个大于 value 的元素。
    可替而用 std::lower_bound() 获得第一迭代器，用 std::upper_bound() 获得第二迭代器。

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
    含有定义所需范围的一对迭代器的 std::pair ，第一迭代器指向首个不小于 value 的元素，而第二迭代器指向首个大于 value 的元素。

    若无元素小于 value ，则 last 作为第一元素返回。类似地，若无元素大于 value ，则 last 作为第二元素返回。

复杂度
进行的比较次数与 first 和 last 间的距离成对数（至多 log2(last - first) + O(1) 次比较）。
    然而，对于非随机访问迭代器 (RandomAccessIterator) ，迭代次自增次数为线性。

可能的实现
版本一
    template<class ForwardIt, class T>
    std::pair<ForwardIt,ForwardIt> 
        equal_range(ForwardIt first, ForwardIt last,
                    const T& value)
    {
        return std::make_pair(std::lower_bound(first, last, value),
                            std::upper_bound(first, last, value));
    }
版本二
    template<class ForwardIt, class T, class Compare>
    std::pair<ForwardIt,ForwardIt> 
        equal_range(ForwardIt first, ForwardIt last,
                    const T& value, Compare comp);
    {
        return std::make_pair(std::lower_bound(first, last, value, comp),
                            std::upper_bound(first, last, value, comp));
    }

示例

#include <algorithm>
#include <vector>
#include <iostream>
 
struct S
{
    int number;
    char name;
    // 注意：此比较运算符忽略 name
    bool operator< ( const S& s ) const { return number < s.number; }
};
 
int main()
{
    // 注意：非有序，仅相对于定义于下的 S 划分
    std::vector<S> vec = { {1,'A'}, {2,'B'}, {2,'C'}, {2,'D'}, {4,'G'}, {3,'F'} };
 
    S value = {2, '?'};
 
    auto p = std::equal_range(vec.begin(), vec.end(), value);
 
    for ( auto i = p.first; i != p.second; ++i )
        std::cout << i->name << ' ';
 
 
    // 异相比较:
    struct Comp
    {
        bool operator() ( const S& s, int i ) const { return s.number < i; }
        bool operator() ( int i, const S& s ) const { return i < s.number; }
    };
 
    auto p2 = std::equal_range(vec.begin(),vec.end(), 2, Comp{});
 
    for ( auto i = p2.first; i != p2.second; ++i )
        std::cout << i->name << ' ';
}

输出：

B C D B C D