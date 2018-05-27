
http://en.cppreference.com/w/cpp/iterator/next

std::next

定义于头文件 <iterator>
    template< class ForwardIt >
    ForwardIt next(
    ForwardIt it, 
    typename std::iterator_traits<ForwardIt>::difference_type n = 1 );

    template< class InputIt >
    constexpr InputIt next(
    InputIt it, 
    typename std::iterator_traits<InputIt>::difference_type n = 1 );

返回迭代器 it 的第 n 个后继。

参数
    it	-	迭代器
    n	-	要前进的元素数
类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。
    -InputIt 必须满足 InputIterator 的要求。

返回值
    迭代器 it 的第 n 个后继。

可能的实现
    template<class ForwardIt>
    ForwardIt next(ForwardIt it,
                typename std::iterator_traits<ForwardIt>::difference_type n = 1)
    {
        std::advance(it, n);
        return it;
    }

注意
    尽管表达式 ++c.begin() 通常能编译，然而不保证会这么做： 
    c.begin() 是右值表达式，而无双向迭代器 (BidirectionalIterator) 要求指定右值的自增保证进行。
    尤其是迭代器以指针实现时， ++c.begin() 不能编译，而 std::next(c.begin()) 可以。

示例

#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
 
    auto it = v.begin();
 
    auto nx = std::next(it, 2);
 
    std::cout << *it << ' ' << *nx << '\n';
}

输出：
    3 4