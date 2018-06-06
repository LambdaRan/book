
http://en.cppreference.com/w/cpp/algorithm/partial_sort

std::partial_sort

定义于头文件 <algorithm>
(1)	
    template< class RandomIt >
    void partial_sort( RandomIt first, RandomIt middle, RandomIt last );
(2)	(C++17 起)
    template< class ExecutionPolicy, class RandomIt >
    void partial_sort( ExecutionPolicy&& policy, RandomIt first, RandomIt middle, RandomIt last );
(3)	
    template< class RandomIt, class Compare >
    void partial_sort( RandomIt first, RandomIt middle, RandomIt last, Compare comp );
(4)	(C++17 起)
    template< class ExecutionPolicy, class RandomIt, class Compare >
    void partial_sort( ExecutionPolicy&& policy, RandomIt first, RandomIt middle, RandomIt last, Compare comp );

重排元素，使得范围 [first, middle) 含有范围 [first, last) 中已排序的 middle - first 个最小元素。

不保证保持相等的元素顺序。范围 [middle, last) 中剩余的元素顺序未指定。

1) 用 operator< 比较元素。
3) 用给定的二元比较函数 comp 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要排序的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 概念的对象），若第一参数小于（即先序于）第二参数则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不必拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 RandomIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -RandomIt 必须满足 ValueSwappable 和 RandomAccessIterator 的要求。
    -解引用 RandomIt 结果的类型必须满足 MoveAssignable 和 MoveConstructible 的要求。

返回值
（无）

复杂度
    约 (last-first)log(middle-first) 次应用 cmp 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

示例
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
 
int main()
{
    std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
 
    std::partial_sort(s.begin(), s.begin() + 3, s.end());
    for (int a : s) {
        std::cout << a << " ";
    } 
}

可能的输出：
0 1 2 7 8 6 5 9 4 3

