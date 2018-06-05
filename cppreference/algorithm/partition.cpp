
http://en.cppreference.com/w/cpp/algorithm/partition

std::partition

定义于头文件 <algorithm>

(1)	(C++11 前)
    template< class BidirIt, class UnaryPredicate >
    BidirIt partition( BidirIt first, BidirIt last, UnaryPredicate p );
    (C++11 起)
    template< class ForwardIt, class UnaryPredicate >
ForwardIt partition( ForwardIt first, ForwardIt last, UnaryPredicate p );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
    ForwardIt partition( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p );

1) 重排序范围 [first, last) 中的元素，使得谓词 p 对其返回 true 的元素前于谓词 p 对其返回 false 的元素。不保持相对顺序。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要重排序的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若元素应在顺序中先于其他元素则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 ForwardIt 类型对象能在解引用后隐式转换到 Type 。 ​

类型要求
    -BidirIt 必须满足 BidirectionalIterator 的要求。
    -ForwardIt 必须满足 ValueSwappable 和 ForwardIterator 的要求。然而，若 ForwardIt 亦满足 BidirectionalIterator 的要求则操作更高效
    -UnaryPredicate 必须满足 Predicate 的要求。

返回值
    指向第二组元素首元素的迭代器。

复杂度
    给定 N = std::distance(first,last) ，

    1) 准确 N 次应用谓词。若 ForwardIt 满足双向迭代器 (BidirectionalIterator) 的要求则至多交换 N/2 次，否则至多交换 N 次。
    2) O(N log N) 次交换， and O(N) 次应用谓词。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template<class ForwardIt, class UnaryPredicate>
    ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
    {
        first = std::find_if_not(first, last, p);
        if (first == last) return first;
    
        for (ForwardIt i = std::next(first); i != last; ++i) {
            if (p(*i)) {
                std::iter_swap(i, first);
                ++first;
            }
        }
        return first;
    }
示例

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <forward_list>
 
template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last)
{
    if(first == last) return;
    auto pivot = *std::next(first, std::distance(first,last)/2);
    ForwardIt middle1 = std::partition(first, last, 
                            [pivot](const auto& em){ return em < pivot; });
    ForwardIt middle2 = std::partition(middle1, last, 
                            [pivot](const auto& em){ return !(pivot < em); });
    quicksort(first, middle1);
    quicksort(middle2, last);
}
 
int main()
{
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    std::cout << "Original vector:\n    ";
    for (int elem : v)
        std::cout << elem << ' ';
 
    auto it = std::partition(v.begin(), v.end(), [](int i){return i % 2 == 0;});
 
    std::cout << "\nPartitioned vector:\n    ";
    std::copy(std::begin(v), it, std::ostream_iterator<int>(std::cout, " "));
    std::cout << " * ";
    std::copy(it, std::end(v), std::ostream_iterator<int>(std::cout, " "));
 
    std::forward_list<int> fl = {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
    std::cout << "\nUnsorted list:\n    ";
    for (int n : fl)
        std::cout << n << ' ';
    std::cout << '\n';  
 
    quicksort(std::begin(fl), std::end(fl));
    std::cout << "Sorted using quicksort:\n    ";
    for(int fi : fl) std::cout << fi << ' ';
    std::cout << '\n';
}

输出：

Original vector:
    0 1 2 3 4 5 6 7 8 9 
Partitioned vector:
    0 8 2 6 4  *  5 3 7 1 9 
Unsorted list:
    1 30 -4 3 5 -4 1 6 -8 2 -5 64 1 92 
Sorted using quicksort:
    -8 -5 -4 -4 1 1 1 2 3 5 6 30 64 92