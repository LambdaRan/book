

http://en.cppreference.com/w/cpp/algorithm/accumulate

std::accumulate
  C++ 算法库 
定义于头文件 <numeric>
template< class InputIt, class T >
T accumulate( InputIt first, InputIt last, T init );
(1)	
template< class InputIt, class T, class BinaryOperation >
T accumulate( InputIt first, InputIt last, T init,
              BinaryOperation op );
(2)	
计算给定值 init 与给定范围 [first, last) 中元素的和。第一版本用 operator+ ，第二版本用二元函数 op 求和元素，均将 std::move 应用到其左侧运算数 (C++20 起)。

op 必须无副效应。

(C++11 前)
op 必须不非法化涉及范围的任何迭代器，含尾迭代器，或修改该范围的任何元素。

(C++11 起)
参数
first, last	-	要求和的元素范围
init	-	和的初值
op	-	被使用的二元函数对象。接收当前积累值 a （初始化为 init ）和当前元素 b 的二元运算符。
该函数的签名应当等价于：

 Ret fun(const Type1 &a, const Type2 &b);

签名中并不需要有 const &。
类型 Type1 必须使得 T 类型的对象能隐式转换到 Type1 。类型 Type2 必须使得 InputIt 类型的对象能在解引用后隐式转换到 Type2 。 类型 Ret 必须使得 T 类型对象能被赋 Ret 类型值。 ​

类型要求
-InputIt 必须满足 InputIterator 的要求。
-T 必须满足 CopyAssignable 和 CopyConstructible 的要求。
返回值
1) 给定值与给定范围中的元素的和。
2) 给定范围在 op 上左折叠的结果
注意
std::accumulate 进行左折叠。为进行右折叠，必须逆转二元运算符的参数顺序，并使用逆序迭代器。

可能的实现
版本一
template<class InputIt, class T>
T accumulate(InputIt first, InputIt last, T init)
{
    for (; first != last; ++first) {
        init = std::move(init) + *first; // C++20 起有 std::move
    }
    return init;
}
版本二
template<class InputIt, class T, class BinaryOperation>
T accumulate(InputIt first, InputIt last, T init, 
             BinaryOperation op)
{
    for (; first != last; ++first) {
        init = op(std::move(init), *first); // C++20 起有 std::move
    }
    return init;
}
示例
运行此代码
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
 
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 
    int sum = std::accumulate(v.begin(), v.end(), 0);
 
    int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
 
    std::string s = std::accumulate(std::next(v.begin()), v.end(),
                                    std::to_string(v[0]), // 以首元素开始
                                    [](std::string a, int b) {
                                        return a + '-' + std::to_string(b);
                                    });
 
    std::cout << "sum: " << sum << '\n'
              << "product: " << product << '\n'
              << "dash-separated string: " << s << '\n';
}
输出：

sum: 55
product: 3628800
dash-separated string: 1-2-3-4-5-6-7-8-9-10