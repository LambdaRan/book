

http://en.cppreference.com/w/cpp/algorithm/swap

std::swap

定义于头文件 <algorithm> (C++11 前)
定义于头文件 <utility> (C++11 起)
(1)	
    template< class T >
    void swap( T& a, T& b );
(2)	(C++11 起)
    template< class T2, std::size_t N >
    void swap( T2 (&a)[N], T2 (&b)[N]);

交换给定值

1) 交换 a 与 b 。
    此重载仅若 std::is_move_constructible_v<T> && std::is_move_assignable_v<T> 为 true 才参与重载决议。 (C++17 起)
2) 交换 a 与 b 数组。
    等效于调用 std::swap_ranges(a, a+N, b) 。此重载仅若 std::is_swappable_v<T2> 为 true 才参与重载决议。 (C++17 起)

参数
    a, b	-	要交换的值

类型要求
    -T 必须满足 MoveAssignable 和 MoveConstructible 的要求。
    -T2 必须满足 Swappable 的要求。
返回值
（无）

异常
1)
    （无）	(C++11 前)
    noexcept 规定：  
    noexcept(
        std::is_nothrow_move_constructible<T>::value &&
        std::is_nothrow_move_assignable<T>::value
    )
    (C++11 起)
2)
    noexcept 规定：  
    noexcept(noexcept(swap(*a, *b)))
    异常规定中标识符 swap 的查找在通常查找规则的所找到的任何内容外，还会找到此函数模板，
        这使得异常规定等价于 C++17 std::is_nothrow_swappable 。	(C++17 前)
    noexcept 规定：  
    noexcept(std::is_nothrow_swappable_v<T2>)
    (C++17 起)

复杂度
    1) 常量
    2) 与 N 呈线性

特化
    std::swap 可以对用户定义类型在命名空间 std 中特化，
        但这些特化不会为 ADL所寻找（命名空间 std 并非对用户定义类型的关联空间）。
        令用户定义类型可交换的期待方式是在与该类型相同的命名空间中提供非成员函数 swap ：细节见可交换 (Swappable) 。

标准库已提供下列重载：

示例

#include <algorithm>
#include <iostream>
 
int main()
{
   int a = 5, b = 3;
 
   // 前
   std::cout << a << ' ' << b << '\n';
 
   std::swap(a,b);
 
   // 后
   std::cout << a << ' ' << b << '\n';
}

输出：
5 3
3 5