

http://en.cppreference.com/w/cpp/algorithm/rotate

std::rotate

定义于头文件 <algorithm>

(1)	(C++11 前)
    template< class ForwardIt >
    void rotate( ForwardIt first, ForwardIt n_first, ForwardIt last );
    (C++11 起)
    template< class ForwardIt >
    ForwardIt rotate( ForwardIt first, ForwardIt n_first, ForwardIt last );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt >
    ForwardIt rotate( ExecutionPolicy&& policy, ForwardIt first, ForwardIt n_first, ForwardIt last );

1) 进行元素范围上的左旋转。
 具体而言， std::rotate 交换范围 [first, last) 中的元素，
    方式满足元素 n_first 成为新范围的首个元素，而 n_first - 1 成为最后元素。
 此函数的前提条件是 [first, n_first) 和 [n_first, last) 为合法范围。
2) 同 (1) ，但按照 policy 执行。
    这些重载不参与重载决议，除非 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 。

参数
    first	-	原范围的起始
    n_first	-	应出现在旋转后范围起始的元素
    last	-	原范围的结尾
    policy	-	所用的执行策略。细节见执行策略。
    
类型要求
    -ForwardIt 必须满足 ValueSwappable 和 ForwardIterator 的要求。
    -解引用 ForwardIt 结果的类型必须满足 MoveAssignable 和 MoveConstructible 的要求。

返回值
    （无）(C++11 前)
    等于 first + (last - n_first) 的迭代器。(C++11 起)

复杂度
    与 first 和 last 间的距离成线性。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template <class ForwardIt>
    ForwardIt rotate(ForwardIt first, ForwardIt n_first, ForwardIt last)
    {
        if(first == n_first) return last;
        if(n_first == last) return first;
    
        ForwardIt next = n_first;
    
        do {
            std::iter_swap(first++, next++);
            if (first == n_first) n_first = next;
        }
        while (next != last);
    
        ForwardIt ret = first;
    
        for(next = n_first; next != last; ) {
            std::iter_swap(first++, next++);
            if(first == n_first) n_first = next;
            else if(next == last) next = n_first;
        }
    
        return ret;
    }

示例
std::rotate 在许多算法中是常用的构建块。此示例演示插入排序：

#include <vector>
#include <iostream>
#include <algorithm>
 
int main()
{
    std::vector<int> v{2, 4, 2, 0, 5, 10, 7, 3, 7, 1}; 
 
    std::cout << "before sort:      ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    // 插入排序
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);
    }
 
    std::cout << "after sort:       ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    // 简单地旋转到左侧
    std::rotate(v.begin(), v.begin() + 1, v.end());
 
    std::cout << "simple rotate left  : ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    // 简单地旋转到右侧
    std::rotate(v.rbegin(), v.rbegin() + 1, v.rend());
 
    std::cout << "simple rotate right : ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
}
输出：

before sort:      2 4 2 0 5 10 7 3 7 1 
after sort:       0 1 2 2 3 4 5 7 7 10 
simple rotate left : 1 2 2 3 4 5 7 7 10 0
simple rotate right: 0 1 2 2 3 4 5 7 7 10