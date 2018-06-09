
http://en.cppreference.com/w/cpp/algorithm/sort_heap

std::sort_heap

定义于头文件 <algorithm>
(1)	
    template< class RandomIt >
    void sort_heap( RandomIt first, RandomIt last );
(2)	
    template< class RandomIt, class Compare >
    void sort_heap( RandomIt first, RandomIt last, Compare comp );

转换最大堆 [first, last) 为以升序排序的范围。产生的范围不再拥有堆属性。

函数的第一版本用 operator< 比较元素，第二版本用给定的比较函数 comp 比较。

参数
    first, last	-	要排序的元素范围
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

返回值
    至多 2×N×log(N) 次比较，其中 N=std::distance(first, last) 。

注意
    有下列属性的元素范围 [f,l) ：

    设 N = l - f ，对于所有 0 < i < N ， f[floor((i-1)/2)] 不小于 f[i] 。
    可用 std::push_heap() 添加新元素
    可用 std::pop_heap() 移除首元素

可能的实现
版本一
    template< class RandomIt >
    void sort_heap( RandomIt first, RandomIt last )
    {
        while (first != last)
            std::pop_heap(first, last--);
    }
版本二
    template< class RandomIt, class Compare >
    void sort_heap( RandomIt first, RandomIt last, Compare comp )
    {
        while (first != last)
            std::pop_heap(first, last--, comp);
    }

示例

#include <algorithm>
#include <vector>
#include <iostream>
 
int main()
{
    std::vector<int> v = {3, 1, 4, 1, 5, 9}; 
 
    std::make_heap(v.begin(), v.end());
 
    std::cout << "heap:\t";
    for (const auto &i : v) {
        std::cout << i << ' ';
    }   
 
    std::sort_heap(v.begin(), v.end());
 
    std::cout << "\nsorted:\t";
    for (const auto &i : v) {                                                   
        std::cout << i << ' ';
    }   
    std::cout << '\n';
}

输出：

heap:   9 4 5 1 1 3 
sorted: 1 1 3 4 5 9