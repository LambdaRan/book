

http://en.cppreference.com/w/cpp/algorithm/partial_sum



std::partial_sum
  C++ 算法库 
定义于头文件 <numeric>
template< class InputIt, class OutputIt >
OutputIt partial_sum( InputIt first, InputIt last, OutputIt d_first );
(1)	
template< class InputIt, class OutputIt, class BinaryOperation >
OutputIt partial_sum( InputIt first, InputIt last, OutputIt d_first,
                      BinaryOperation op );
(2)	
计算范围 [first, last) 的子范围中元素的部分和，并写入到始于 d_first 的范围。第一版本用 operator+ ，第二版本用给定的二元函数 op 对元素求和，均将 std::move 应用到其左侧运算数 (C++20 起)。

等价运算：

*(d_first)   = *first;
*(d_first+1) = *first + *(first+1);
*(d_first+2) = *first + *(first+1) + *(first+2);
*(d_first+3) = *first + *(first+1) + *(first+2) + *(first+3);
...
op 必须无副效应。

(C++11 前)
op 必须不非法化涉及范围的任何迭代器，含尾迭代器，或修改该范围的任何元素。

(C++11 起)
参数
first, last	-	要求和的元素范围
d_first	-	目标范围起始；可以等于 first
op	-	被使用的二元函数对象。
该函数的签名应当等价于：

 Ret fun(const Type1 &a, const Type2 &b);

签名中并不需要有 const &。
类型 Type1 必须使得 iterator_traits<InputIt>::value_type 类型的对象能隐式转换到 Type1 。类型 Type2 必须使得 InputIt 类型的对象能在解引用后隐式转换到 Type2 。 类型 Ret 必须使得 iterator_traits<InputIt>::value_type 类型对象能被赋 Ret 类型值。 ​

类型要求
-InputIt 必须满足 InputIterator 的要求。
-OutputIt 必须满足 OutputIterator 的要求。
返回值
指向最后被写入元素后一元素的迭代器。

复杂度
恰好应用 (last - first) - 1 次二元运算

可能的实现
版本一
template<class InputIt, class OutputIt>
OutputIt partial_sum(InputIt first, InputIt last, 
                     OutputIt d_first)
{
    if (first == last) return d_first;
 
    typename std::iterator_traits<InputIt>::value_type sum = *first;
    *d_first = sum;
 
    while (++first != last) {
       sum = std::move(sum) + *first; // C++20 起有 std::move
       *++d_first = sum;
    }
    return ++d_first;
 
    // 或 C++14 起：
    // return std::partial_sum(first, last, d_first, std::plus<>());
}
版本二
template<class InputIt, class OutputIt, class BinaryOperation>
OutputIt partial_sum(InputIt first, InputIt last, 
                     OutputIt d_first, BinaryOperation op)
{
    if (first == last) return d_first;
 
    typename std::iterator_traits<InputIt>::value_type sum = *first;
    *d_first = sum;
 
    while (++first != last) {
       sum = op(std::move(sum), *first); // C++20 起有 std::move
       *++d_first = sum;
    }
    return ++d_first;
}
示例
运行此代码
#include <numeric>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
 
int main()
{
    std::vector<int> v = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; // 或 std::vector<int>v(10, 2);
 
    std::cout << "The first 10 even numbers are: ";
    std::partial_sum(v.begin(), v.end(), 
                     std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
 
    std::partial_sum(v.begin(), v.end(), v.begin(), std::multiplies<int>());
    std::cout << "The first 10 powers of 2 are: ";
    for (auto n : v) {
        std::cout << n << " ";
    }
    std::cout << '\n';
}
输出：

The first 10 even numbers are: 2 4 6 8 10 12 14 16 18 20 
The first 10 powers of 2 are: 2 4 8 16 32 64 128 256 512 1024