
http://en.cppreference.com/w/cpp/algorithm/partial_sort_copy

std::partial_sort_copy

定义于头文件 <algorithm>
(1)	
template< class InputIt, class RandomIt >
RandomIt partial_sort_copy( InputIt first, InputIt last,
                            RandomIt d_first, RandomIt d_last );
(2)	(C++17 起)
template< class ExecutionPolicy, class ForwardIt, class RandomIt >
RandomIt partial_sort_copy( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last,
                            RandomIt d_first, RandomIt d_last );
(3)	
template< class InputIt, class RandomIt, class Compare >
RandomIt partial_sort_copy( InputIt first, InputIt last,
                            RandomIt d_first, RandomIt d_last,
                            Compare comp );
(4)	(C++17 起)
template< class ExecutionPolicy, class ForwardIt, class RandomIt, class Compare >
RandomIt partial_sort_copy( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last,
                            RandomIt d_first, RandomIt d_last,
                            Compare comp );

以升序排序范围 [first, last) 中的某些元素，存储结果于范围 [d_first, d_last) 。

至多将 d_last - d_first 个元素放置并排序到范围 [d_first, d_first + n) 中。
    其中 n 是要排序的元素数（ n = min(last - first, d_last - d_first) ）。不保证保持相等元素的顺序。

1) 用 operator< 比较元素。
3) 用给定的二元比较函数 comp 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要排序的元素范围
    d_first, d_last	-	定义目标范围的随机访问迭代器
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 概念的对象），若第一参数小于（即先序于）第二参数则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不必拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 RandomIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -ForwardIt 必须满足 ForwardIterator 的要求。
    -RandomIt 必须满足 ValueSwappable 和 RandomAccessIterator 的要求。
    -解引用 RandomIt 结果的类型必须满足 MoveAssignable 和 MoveConstructible 的要求。

返回值
    指向定义已排序范围上界的元素的迭代器，即 d_first + min(last - first, d_last - d_first) 。

复杂度
    O(N·log(min(D,N)) 次应用 cmp ，其中 N = std::distance(first, last) ， D = std::distance(d_first, d_last) 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

示例
下列代码排序 int 的 vector 并将它们复制到较小和较大的 vector 中。

#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
 
int main()
{
    std::vector<int> v0{4, 2, 5, 1, 3};
    std::vector<int> v1{10, 11, 12};
    std::vector<int> v2{10, 11, 12, 13, 14, 15, 16};
    std::vector<int>::iterator it;
 
    it = std::partial_sort_copy(v0.begin(), v0.end(), v1.begin(), v1.end());
 
    std::cout << "Writing to the smaller vector in ascending order gives: ";
    for (int a : v1) {
        std::cout << a << " ";
    }
    std::cout << '\n';
    if(it == v1.end())
        std::cout << "The return value is the end iterator\n";
 
    it = std::partial_sort_copy(v0.begin(), v0.end(), v2.begin(), v2.end(), 
                                std::greater<int>());
 
    std::cout << "Writing to the larger vector in descending order gives: ";
    for (int a : v2) {
        std::cout << a << " ";
    }
    std::cout << '\n' << "The return value is the iterator to " << *it << '\n';
}

输出：

Writing to the smaller vector in ascending order gives: 1 2 3
The return value is the end iterator
Writing to the larger vector in descending order gives: 5 4 3 2 1 15 16
The return value is the iterator to 15