
http://en.cppreference.com/w/cpp/algorithm/pop_heap

std::pop_heap

定义于头文件 <algorithm>
(1)	
template< class RandomIt >
void pop_heap( RandomIt first, RandomIt last );
(2)	
template< class RandomIt, class Compare >
void pop_heap( RandomIt first, RandomIt last, Compare comp );

交换在位置 first 的值和在位置 last-1 的值，并令子范围 [first, last-1) 变为最大堆。
这拥有从范围 [first, last) 所定义的堆移除首个（最大）元素的效应。

函数的首个版本使用 operator< 比较元素，第二版本使用给定的比较函数 comp 。

参数
    first, last	-	定义要修改的合法非空堆的元素范围
    comp	-	比较函数对象（即满足比较 (Compare) 要求的对象），若首个参数小于第二个，则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不需要拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 RandomIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -RandomIt 必须满足 ValueSwappable 和 RandomAccessIterator 的要求。
    -解引用 RandomIt 结果的类型必须满足 MoveAssignable 和 MoveConstructible 的要求。

返回值
（无）

复杂度
至多 2×log(N) 次比较，其中 N=std::distance(first, last).

注意
    最大堆是拥有下列属性的元素范围 [f,l) ：

    设 N = l - f ，对于所有 0 < i < N ， f[floor((i-1)/2)] 不小于 f[i] 。
    可用 std::push_heap() 添加新元素
    可用 std::pop_heap() 移除首元素

示例

#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };
 
    std::make_heap(v.begin(), v.end());
 
    std::cout << "v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
    
    // 移动最大元素到结尾 将最大元素移到最后位置
    std::pop_heap(v.begin(), v.end()); 
 
    std::cout << "after pop_heap: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
 
    int largest = v.back();
    v.pop_back();  // 实际移出最大元素
    std::cout << "largest element: " << largest << '\n';
 
    std::cout << "heap without largest: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
}

输出：

v: 9 5 4 1 1 3 
after pop_heap: 5 3 4 1 1 9 
largest element: 9
heap without largest: 5 3 4 1 1