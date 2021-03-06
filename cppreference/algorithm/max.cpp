
http://en.cppreference.com/w/cpp/algorithm/max

std::max

定义于头文件 <algorithm>
(1)	(C++14 前)
    template< class T > 
    const T& max( const T& a, const T& b );
    (C++14 起)
    template< class T > 
    constexpr const T& max( const T& a, const T& b );

(2)	(C++14 前)
    template< class T, class Compare >
    const T& max( const T& a, const T& b, Compare comp );
    (C++14 起)
    template< class T, class Compare >
    constexpr const T& max( const T& a, const T& b, Compare comp );

(3)	(C++11 起) (C++14 前)
    template< class T >
    T max( std::initializer_list<T> ilist );
    (C++14 起)
    template< class T >
    constexpr T max( std::initializer_list<T> ilist );

(4)	(C++11 起) (C++14 前)
    template< class T, class Compare >
    T max( std::initializer_list<T> ilist, Compare comp );
    (C++14 起)
    template< class T, class Compare >
    constexpr T max( std::initializer_list<T> ilist, Compare comp );

返回给定值中的较大者。

1-2) 返回 a 与 b 的较大者。
3-4) 返回 initializer_list ilist 中值的最大者。
(1,3) 版本用 operator< 比较元素， (2,4) 版本用给定的比较函数 comp 。

参数
    a, b	-	要比较的值
    ilist	-	拥有要比较的值的 initializer_list
    cmp	-	比较函数对象（即满足比较 (Compare) 要求的对象），若若 a 小于 b ，则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不需要拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 T 类型的对象能隐式转换到这两个类型。 ​

类型要求
    - 为使用重载 (1,3) ， T 必须满足 LessThanComparable 的要求。
    - 为使用重载 (3,4) ， T 必须满足 CopyConstructible 的要求。

返回值
    1-2) a 与 b 的较大者。若它们等价，则返回 a 。
    3-4) ilist 中的最大值。若有数个等价于最大者的值，则返回最左侧的这种值。

复杂度
    1-2) 准确一次比较
    3-4) 准确 ilist.size() - 1 次比较

可能的实现
版本一
    template<class T> 
    const T& max(const T& a, const T& b)
    {
        return (a < b) ? b : a;
    }
版本二
    template<class T, class Compare> 
    const T& max(const T& a, const T& b, Compare comp)
    {
        return (comp(a, b)) ? b : a;
    }
版本三
    template< class T >
    T max( std::initializer_list<T> ilist)
    {
        return *std::max_element(ilist.begin(), ilist.end());
    }
版本四
    template< class T, class Compare >
    T max( std::initializer_list<T> ilist, Compare comp )
    {
        return *std::max_element(ilist.begin(), ilist.end(), comp);
    }

注意
若参数之一是右值，且返回该参数，则以引用捕获 std::max 的结果会产生一个悬垂引用：

int n = 1;
const int& r = std::max(n-1, n+1);
// r 为悬垂

示例
运行此代码
#include <algorithm>
#include <iostream>
#include <string>
 
int main()
{
    std::cout << "larger of 1 and 9999: " << std::max(1, 9999) << '\n'
              << "larger of 'a', and 'b': " << std::max('a', 'b') << '\n'
              << "longest of \"foo\", \"bar\", and \"hello\": " <<
                  std::max( { "foo", "bar", "hello" },
                            [](const std::string& s1, const std::string& s2) {
                                 return s1.size() < s2.size();
                             }) << '\n';
}

输出：

larger of 1 and 9999: 9999
larger of 'a', and 'b': b
longest of "foo", "bar", and "hello": hello