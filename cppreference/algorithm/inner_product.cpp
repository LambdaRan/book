
http://en.cppreference.com/w/cpp/algorithm/inner_product

std::inner_product
  C++ 算法库 
定义于头文件 <numeric>
template< class InputIt1, class InputIt2, class T >
T inner_product( InputIt1 first1, InputIt1 last1,
                 InputIt2 first2, T value );
(1)	
template<class InputIt1, class InputIt2, class T,
         class BinaryOperation1, class BinaryOperation2> 
T inner_product( InputIt1 first1, InputIt1 last1,
                 InputIt2 first2, T value,
                 BinaryOperation1 op1,
                 BinaryOperation2 op2 );
(2)	
计算内积（即积之和）或在范围 [first1, last1) 和始于 first2 的范围上进行有序映射/规约操作。

1) 以初值 init 初始化积累器 acc ，然后
以表达式 acc = acc + *first1 * *first2 修改它，再以表达式 acc = acc + *(first1+1) * *(first2+1) 修改它，以此类推

(C++20 前)
以表达式 acc = std::move(acc) + *first1 * *first2 修改它，再以表达式 acc = std::move(acc) + *(first1+1) * *(first2+1) 修改它，以此类推

(C++20 起)
直至抵达 last1 。对于 + 与 * 的内建含义，此算法计算二个范围的内积。
2) 以初值 init 初始化积累器 acc ，然后
以表达式 acc = op1(acc, op2(*first1, *first2)) 修改它，再以表达式 acc = op1(acc, op2(*(first1+1), *(first2+1))) 修改它，以此类推

(C++20 前)
以表达式 acc = op1(std::move(acc), op2(*first1, *first2)) 修改它，再以表达式 acc = op1(std::move(acc), op2(*(first1+1), *(first2+1))) 修改它，以此类推

(C++20 起)
直至抵达 last1 。
op1 或 op2 必须无副效应。

(C++11 前)
op1 或 op2 必须不非法化所涉及范围的任何迭代器，含尾迭代器或修改该范围的任何元素。

(C++11 起)
参数
first1, last1	-	元素范围
first2	-	第二个元素范围的起始
value	-	积的和的初值
op1	-	被使用的二元函数对象。此“和”函数接收 op2 所返回的值和当前积累器的值，并产生存储于积累器的新值。
该函数的签名应当等价于：

 Ret fun(const Type1 &a, const Type2 &b);

签名中并不需要有 const &。
类型 Type1 与 Type2 必须使得 T 与 Type3 类型的对象各能隐式转换成 Type1 与 Type2 。 类型 Ret 必须使得 T 类型对象能被赋 Ret 类型值。 ​

op2	-	被使用的二元函数对象。此“积”函数从每个范围接收一个值并产生新值。
该函数的签名应当等价于：

 Ret fun(const Type1 &a, const Type2 &b);

签名中并不需要有 const &。
类型 Type1 与 Type2 必须使得 InputIt1 与 InputIt2 类型的对象在解引用后分别能隐式转换到 Type1 与 Type2 。 类型 Ret 必须使得 Type3 类型对象能被赋 Ret 类型值。 ​

类型要求
-InputIt1, InputIt2 必须满足 InputIterator 的要求。
-ForwardIt1, ForwardIt2 必须满足 ForwardIterator 的要求。
-T 必须满足 CopyAssignable 和 CopyConstructible 的要求。
返回值
上述 acc 的最终值。

可能的实现
版本一
template<class InputIt1, class InputIt2, class T>
T inner_product(InputIt1 first1, InputIt1 last1,
                InputIt2 first2, T value)
{
    while (first1 != last1) {
         value = std::move(value) + *first1 * *first2; // C++20 起有 std::move
         ++first1;
         ++first2;
    }
    return value;
}
版本二
template<class InputIt1, class InputIt2,
         class T,
         class BinaryOperation1, class BinaryOperation2>
T inner_product(InputIt1 first1, InputIt1 last1,
                InputIt2 first2, T value,
                BinaryOperation1 op1
                BinaryOperation2 op2)
{
    while (first1 != last1) {
         value = op1(std::move(value), op2(*first1, *first2)); // C++20 起有 std::move
         ++first1;
         ++first2;
    }
    return value;
}
注意
此算法的可并行版本 std::transform_reduce 要求 op1 与 op2 可交换并可结合，但 std::inner_product 不作这种要求，且始终以给定顺序进行操作。

示例
运行此代码
#include <numeric>
#include <iostream>
#include <vector>
#include <functional>
int main()
{
    std::vector<int> a{0, 1, 2, 3, 4};
    std::vector<int> b{5, 4, 2, 3, 1};
 
    int r1 = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    std::cout << "Inner product of a and b: " << r1 << '\n';
 
    int r2 = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                std::plus<>(), std::equal_to<>());
    std::cout << "Number of pairwise matches between a and b: " <<  r2 << '\n';
}
输出：

Inner product of a and b: 21
Number of pairwise matches between a and b: 2