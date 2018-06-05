

http://en.cppreference.com/w/cpp/algorithm/stable_partition

std::stable_partition

定义于头文件 <algorithm>
(1)	
    template< class BidirIt, class UnaryPredicate >
    BidirIt stable_partition( BidirIt first, BidirIt last, UnaryPredicate p );
(2)	(C++17 起)
    template< class ExecutionPolicy, class BidirIt, class UnaryPredicate >
    BidirIt stable_partition( ExecutionPolicy&& policy, BidirIt first, BidirIt last, UnaryPredicate p );

1) 重排序范围 [first, last) 中的元素，使得所有谓词 p 对其返回 true 的元素先于谓词 p 对其返回 false 的元素。保持元素的相对顺序。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要重排序的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若元素应先序于其他元素则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 BidirIt 类型对象能在解引用后隐式转换到 Type 。 ​

类型要求
    -BidirIt 必须满足 ValueSwappable 和 BidirectionalIterator 的要求。
    -解引用 BidirIt 结果的类型必须满足 MoveAssignable 和 MoveConstructible 的要求。
    -UnaryPredicate 必须满足 Predicate 的要求。

返回值
指向第二范围首元素的迭代器

复杂度
    给定 N = last - first

    1) 若有充足内存，则准确应用 N 次谓词及交换 O(N) 次。若内存不充足，则至多交换 N log N 次。
    2) O(N log N) 次交换及应用 O(N) 次谓词。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。
注意
此函数试图分配临时缓冲区。若分配失败，则选择较低效的算法。

示例

#include <iostream>
#include <algorithm>
#include <vector>
 
int main()
{
    std::vector<int> v{0, 0, 3, 0, 2, 4, 5, 0, 7};
    std::stable_partition(v.begin(), v.end(), [](int n){return n>0;});
    for (int n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}

输出：
3 2 4 5 7 0 0 0 0