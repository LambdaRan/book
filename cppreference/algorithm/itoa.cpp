


http://en.cppreference.com/w/cpp/algorithm/iota


std::iota
  C++ 算法库 
定义于头文件 <numeric>
template< class ForwardIterator, class T >
void iota( ForwardIterator first, ForwardIterator last, T value );
(C++11 起)
以始于 value 并重复地求值 ++value 的顺序递增值填充范围 [first, last) 。

等价操作：

*(d_first)   = value;
*(d_first+1) = ++value;
*(d_first+2) = ++value;
*(d_first+3) = ++value;
...
参数
first, last	-	以 value 开始，按顺序递增填充的值的范围
value	-	要存储的初始值，表达式 ++value 必须为良式
返回值
（无）

复杂度
正好 last - first 次自增与赋值。

可能的实现
template<class ForwardIterator, class T>
void iota(ForwardIterator first, ForwardIterator last, T value)
{
    while(first != last) {
        *first++ = value;
        ++value;
    }
}
注意
此函数命名来源于编程语言 APL 中的整数函数 ⍳ 。它是 C++98 所不曾包含的 STL 组件之一，但最终于 C++11 进入了标准库。

示例
下列代码应用 std::shuffle 到 std::list 迭代器的 vector ，因为不能直接应用 std::shuffle 到 std::list 。用 std::iota 填充二个容器。

运行此代码
#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>
 
int main()
{
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);
 
    std::vector<std::list<int>::iterator> v(l.size());
    std::iota(v.begin(), v.end(), l.begin());
 
    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});
 
    std::cout << "Contents of the list: ";
    for(auto n: l) std::cout << n << ' ';
    std::cout << '\n';
 
    std::cout << "Contents of the list, shuffled: ";
    for(auto i: v) std::cout << *i << ' ';
    std::cout << '\n';
}
可能的输出：

Contents of the list: -4 -3 -2 -1 0 1 2 3 4 5
Contents of the list, shuffled: 0 -1 3 4 -4 1 -2 -3 2 5