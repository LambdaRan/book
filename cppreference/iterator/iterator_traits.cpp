
https://en.cppreference.com/w/cpp/iterator/iterator_traits

std::iterator_traits
定义于头文件 <iterator>
    template< class Iterator >
    struct iterator_traits;
    template< class T >
    struct iterator_traits<T*>;
    template< class T >
    struct iterator_traits<const T*>;

std::iterator_traits 是类型特性类，为迭代器类型的属性提供统一的接口，使得能够仅针对迭代器实现算法。

该类定义了如下类型，与 std::iterator 中的类型定义相对应：

difference_type - 可用来标示迭代器间距的类型
value_type - 迭代器解除引用后所得到的值的类型。对于输出迭代器，该类型为 void 。
pointer - 指向被迭代类型（ value_type ）的指针
reference - 被迭代类型（ value_type ）的引用类型
iterator_category - 迭代器类别。必须是迭代器类别标签之一。
可以针对用户自定义迭代器特化该模版，这样，即便该类型没有提供一般的类型定义，也能获取关于该迭代器的信息。

模版参数
    Iterator	-	需要取得与之相关属性的迭代器类型

成员类型
    成员类型	定义
    difference_type	Iterator::difference_type
    value_type	Iterator::value_type
    pointer	Iterator::pointer
    reference	Iterator::reference
    iterator_category	Iterator::iterator_category
    若 Iterator 没有全部五个成员类型 difference_type 、 value_type 、 pointer 、 reference 及 iterator_category ，
        则此模板无任何拥有那些名称的成员（ std::iterator_traits 对 SFINAE 友好）

特化
    如果要把用户提供的类型作为迭代器使用，该类型特征可以针对这一类型进行特化。
        标准库中提供了针对指针类型 T * 的两种偏特化，使得可以在任何需要迭代器的算法里使用裸指针。

    针对 T * 特化的成员类型
        成员类型	定义
        difference_type	std::ptrdiff_t
        value_type	T (C++20 前)std::remove_cv_t<T> (C++20 起)
        pointer	T*
        reference	T&
        iterator_category	std::random_access_iterator_tag
    针对 const T * 特化的成员类型    
        成员类型	定义
        difference_type	std::ptrdiff_t
        value_type	T
        pointer	const T*
        reference	const T&
        iterator_category	std::random_access_iterator_tag

示例

下列使用展示对双向迭代器的通用 reverse() 实现
#include <iostream>
#include <iterator>
#include <vector>
#include <list>
 
template<class BidirIt>
void my_reverse(BidirIt first, BidirIt last)
{
    typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    --n;
    while(n > 0) {
        typename std::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
        n -= 2;
    }
}
 
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    my_reverse(v.begin(), v.end());
    for (int n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
 
    std::list<int> l{1, 2, 3, 4, 5};
    my_reverse(l.begin(), l.end());
    for (auto n : l) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
 
    int a[] = {1, 2, 3, 4, 5};
    my_reverse(a, a+5);
    for (int i=0; i<5; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
 
//    std::istreambuf_iterator<char> i1(std::cin), i2;
//    my_reverse(i1, i2); // 编译错误
 
}

输出：
    5 4 3 2 1
    5 4 3 2 1
    5 4 3 2 1