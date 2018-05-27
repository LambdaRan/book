

http://en.cppreference.com/w/cpp/algorithm/minmax

std::minmax

定义于头文件 <algorithm>
(1)	
    template< class T > 
    std::pair<const T&,const T&> minmax( const T& a, const T& b );
    template< class T > 
    constexpr std::pair<const T&,const T&> minmax( const T& a, const T& b );

(2)	
    template< class T, class Compare >
    std::pair<const T&,const T&> minmax( const T& a, const T& b,
                                        Compare comp );
    template< class T, class Compare >
    constexpr std::pair<const T&,const T&> minmax( const T& a, const T& b,
                                               Compare comp );
(3)	
    template< class T >
    std::pair<T,T> minmax( std::initializer_list<T> ilist);
    template< class T >
    constexpr std::pair<T,T> minmax( std::initializer_list<T> ilist);
(4)	
    template< class T, class Compare >
    std::pair<T,T> minmax( std::initializer_list<T> ilist, Compare comp );
    template< class T, class Compare >
    constexpr std::pair<T,T> minmax( std::initializer_list<T> ilist, Compare comp );

返回给定值的最小和最大者。

1-2) 返回到 a 的 b 较小和较大者的引用。
3-4) 返回 initializer_list ilist 中值的最小和最大者。
(1,3) 版本用 operator< 比较值，而 (2,4) 版本用给定的比较函数 comp 。

参数
    a, b	-	要比较的值
    ilist	-	含要比较的值的 initializer_list
    comp	-	比较函数对象（即满足比较 (Compare) 要求的对象），若首个参数小于第二个，则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不需要拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 T 类型的对象能隐式转换到这两个类型。 ​

类型要求
    为使用重载 (1,3) ， T 必须满足 LessThanComparable 的要求。
    为使用重载 (3,4) ， T 必须满足 CopyConstructible 的要求。

返回值
    1-2) 若 a<b 或若 a 等价于 b 则返回 std::pair<const T&, const T&>(a, b) 的结果。
        若 b<a 则返回 std::pair<const T&, const T&>(b, a) 的结果。
    3-4) 以 ilist 中最小元素为第一元素，最大元素为第二元素的 pair 。若有数个元素等价于最小者，
        则返回最左的这种元素。若有数个元素等价于最大者，则返回最右的这种元素。

复杂度
    1-2) 准确一次比较
    3-4) 至多 ilist.size() * 3 / 2 次比较

可能的实现
版本一
    template<class T> 
    std::pair<const T&, const T&> minmax( const T& a, const T& b )
    {
        return (b < a) ? std::pair<const T&, const T&>(b, a)
                    : std::pair<const T&, const T&>(a, b);
    }
版本二
    template<class T, class Compare> 
    std::pair<const T&, const T&> minmax( const T& a, const T& b, Compare comp )
    {
        return comp(b, a) ? std::pair<const T&, const T&>(b, a)
                        : std::pair<const T&, const T&>(a, b);
    }
版本三
    template< class T >
    std::pair<T, T> minmax( std::initializer_list<T> ilist )
    {
        auto p = std::minmax_element(ilist.begin(), ilist.end());
        return std::make_pair(*p.first, *p.second);
    }
版本四
    template< class T, class Compare >
    std::pair<T, T> minmax( std::initializer_list<T> ilist, Compare comp )
    {
        auto p = std::minmax_element(ilist.begin(), ilist.end(), comp);
        return std::make_pair(*p.first, *p.second);
    }

示例

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
 
int main()
{
    std::vector<int> v {3, 1, 4, 1, 5, 9, 2, 6}; 
    std::srand(std::time(0));
    std::pair<int, int> bounds = std::minmax(std::rand() % v.size(),
                                             std::rand() % v.size());
 
    std::cout << "v[" << bounds.first << "," << bounds.second << "]: ";
    for (int i = bounds.first; i < bounds.second; ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

可能的输出：
v[2,7]: 4 1 5 9 2
