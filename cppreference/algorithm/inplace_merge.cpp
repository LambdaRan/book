

http://en.cppreference.com/w/cpp/algorithm/inplace_merge

std::inplace_merge
 
定义于头文件 <algorithm>
(1)
    template< class BidirIt >
    void inplace_merge( BidirIt first, BidirIt middle, BidirIt last );

(2)	
    template< class ExecutionPolicy, class BidirIt >
    void inplace_merge( ExecutionPolicy&& policy, BidirIt first, BidirIt middle, BidirIt last );

(3)	
    template< class BidirIt, class Compare>
    void inplace_merge( BidirIt first, BidirIt middle, BidirIt last, Compare comp );

(4)
    template< class ExecutionPolicy, class BidirIt, class Compare>
    void inplace_merge( ExecutionPolicy&& policy, BidirIt first, BidirIt middle, BidirIt last, Compare comp );

归并二个相继的已排序范围 [first, middle) 及 [middle, last) 为一个已排序范围 [first, last) 。
对于原先二个范围中的等价元素。来自第一范围的元素（保持其原顺序）先于来自第二范围的元素（保持其原顺序）。

1) 用 operator< 比较元素，且范围必须对于同关系已排序。
3) 用给定的二元比较函数 comp 比较元素，且范围必须对于同关系已排序。
2,4) 同 (1,3) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first	-	第一个已排序范围的起始
    middle	-	第一个已排序范围的结尾及第二个已排序范围的起始
    last	-	第二个已排序范围的结尾
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 概念的对象），若第一参数小于（即先序于）第二参数则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不必拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 BidirIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -BidirIt 必须满足 ValueSwappable 和 BidirectionalIterator 的要求。
    -解引用 BidirIt 结果的类型必须满足 MoveAssignable 和 MoveConstructible 的要求。

返回值
（无）

复杂度
    给定 N = std::distance(first, last)} ，
    1,3) 若附加内存可用则准确为 N-1 次比较。若内存不足，则为 O(N log N) 次比较。
    2,4) O(N log N) 次比较。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

注意
    此函数试图分配临时缓冲区。若分配失败，则选择较低效的算法。

示例
#include <vector>
#include <iostream>
#include <algorithm>
 
template<class Iter>
void merge_sort(Iter first, Iter last)
{
    if (last - first > 1) {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }
}
 
int main()
{
    std::vector<int> v{8, 2, -2, 0, 11, 11, 1, 7, 3};
    merge_sort(v.begin(), v.end());
    for(auto n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
    
    std::vector<int> v2{1,3,5,2,4,6};
    
    std::cout << "before:\n";
    for(auto n : v2) {
        std::cout << n << ' ';
    }
    std::cout << '\n';  
    
    auto mid = std::next(v2.begin(), std::distance(v2.begin(), v2.end()) / 2);
    std::inplace_merge(v2.begin(), mid, v2.end());
    
    std::cout << "after:\n";
    for(auto n : v2) {
        std::cout << n << ' ';
    }
    std::cout << '\n';  
}

输出:
    -2 0 1 2 3 7 8 11 11 
    before:
    1 3 5 2 4 6 
    after:
    1 2 3 4 5 6