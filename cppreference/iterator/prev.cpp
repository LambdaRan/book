
http://en.cppreference.com/w/cpp/iterator/prev

std::prev

定义于头文件 <iterator>
    template< class BidirIt >
    BidirIt prev(
    BidirIt it, 
    typename std::iterator_traits<BidirIt>::difference_type n = 1 );

    template< class BidirIt >
    constexpr BidirIt prev(
    BidirIt it, 
    typename std::iterator_traits<BidirIt>::difference_type n = 1 );

返回迭代器 it 的第 n 个前驱。

参数
    it	-	迭代器
    n	-	it 要被减少的元素数

类型要求
    -BidirIt 必须满足 BidirectionalIterator 的要求。

返回值
    迭代器 it 的第 n 个前驱。

可能的实现
    template<class BidirIt>
    BidirIt prev(BidirIt it, typename std::iterator_traits<BidirIt>::difference_type n = 1)
    {
        std::advance(it, -n);
        return it;
    }

注意
    尽管表达式 --c.end() 通常能编译，然而不保证会这么做： 
    c.end() 是右值表达式，而且无迭代器要求指定右值的自减保证进行。
    尤其是当迭代器以指针实现时， --c.end() 不能编译，而 std::prev(c.end()) 可以。

示例

#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
 
    auto it = v.end();
 
    auto pv = std::prev(it, 2);
 
    std::cout << *pv << '\n';
}

输出：
    1