
http://en.cppreference.com/w/cpp/algorithm/nth_element

std::nth_element
  C++ 算法库 
定义于头文件 <algorithm>
(1)	
    template< class RandomIt >
    void nth_element( RandomIt first, RandomIt nth, RandomIt last );

(2)	(C++17 起)
    template< class ExecutionPolicy, class RandomIt >
    void nth_element( ExecutionPolicy&& policy, RandomIt first, RandomIt nth, RandomIt last );
(3)	
    template< class RandomIt, class Compare >
    void nth_element( RandomIt first, RandomIt nth, RandomIt last, Compare comp );
(4)	(C++17 起)
    template< class ExecutionPolicy, class RandomIt, class Compare >
    void nth_element( ExecutionPolicy&& policy, RandomIt first, RandomIt nth, RandomIt last, Compare comp );

nth_element 是部分排序算法，它重排 [first, last) 中元素，使得：

nth 所指向的元素被更改为假如 [first, last) 已排序则该位置会出现的元素。
这个新的 nth 元素前的所有元素小于或等于新的 nth 元素后的所有元素。
更正式而言， nth_element 以升序部分排序范围 [first, last) ，
    使得对于任何范围 [first, nth) 中的 i 和任何范围 [nth, last) 中的 j ，
    都满足条件 !(*j < *i) （对于 (1-2) ，对 (3-4) 则为 comp(*j, *i) == false ）。
    置于 nth 位置的元素则准确地是假如完全排序范围则应出现于此位置的元素。

nth 可以是尾迭代器，此情况下函数无效果。

1) 用 operator< 比较元素。
3) 用给定的二元比较函数 comp 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。这些重载不参与重载决议，除非 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 。

参数
    first, last	-	定义待排序范围的随机访问迭代器
    nth	-	定义排序划分点的随机访问迭代器
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
    1,3) 平均与 std::distance(first, last) 成线性。
    2,4) O(N) 次应用谓词和 O(N log N) 次交换，其中 N = last - first 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

注意
典型地使用内省选择算法，尽管允许其他拥有适合平均情况复杂度的选择算法。

示例

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
 
int main()
{
    std::vector<int> v{5, 6, 4, 3, 2, 6, 7, 9, 3};
 
    std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
    std::cout << "The median is " << v[v.size()/2] << '\n';
 
    std::nth_element(v.begin(), v.begin()+1, v.end(), std::greater<int>());
    std::cout << "The second largest element is " << v[1] << '\n';
}

输出：

The median is 5
The second largest element is 7
