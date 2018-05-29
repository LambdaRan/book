

http://en.cppreference.com/w/cpp/algorithm/for_each

std::for_each
定义于头文件 <algorithm>
(1)	
    template< class InputIt, class UnaryFunction >
    UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );

    template< class InputIt, class UnaryFunction >
    constexpr UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );
(2)
    template< class ExecutionPolicy, class ForwardIt, class UnaryFunction2 >
    void for_each( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryFunction2 f );

1) 按顺序应用给定的函数对象 f 到解引用范围 [first, last) 中每个迭代器的结果。
2) 应用给定的函数对象 f 到解引用范围 [first, last) 中每个迭代器的结果（不必按顺序）。
    按照 policy 执行算法。此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

对于两个重载，若迭代器类型为可变，则 f 可以通过解引用后的迭代器修改范围的元素。若 f 返回结果，则忽略结果。

不同于其余算法，不允许 for_each 复制序列中的元素，即使它们为可平凡复制。

参数
    first, last	-	要应用函数到的范围
    policy	-	所用的执行策略。细节见执行策略。
    f	-	函数对象，要应用于解引用范围 [first, last) 中每个迭代器结果的函数
    函数签名应当等价于如下者：
    void fun(const Type &a);
    签名不必拥有 const & 。
    类型 Type 必须使得 InputIt 类型对象能在解引用后隐式转换到 Type 。

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -ForwardIt 必须满足 ForwardIterator 的要求。
    -UnaryFunction 必须满足 MoveConstructible 的要求。不必为 CopyConstructible 。
    -UnaryFunction2 必须满足 CopyConstructible 的要求。

返回值
    1) f (C++11 前) std::move(f) (C++11 起)
    2) （无）

复杂度
    准确应用 last - first 次 f 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template<class InputIt, class UnaryFunction>
    UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
    {
        for (; first != last; ++first) {
            f(*first);
        }
        return f;
    }

示例
下列代码用 lambda 函数自增 vector 的所有元素，然后用函数对象中的重载 operator() 计算其和。
    注意推荐用更适合的算法 std::accumulate 计算和。

#include <vector>
#include <algorithm>
#include <iostream>
 
struct Sum
{
    Sum(): sum{0} { }
    void operator()(int n) { sum += n; }
    int sum;
};
 
int main()
{
    std::vector<int> nums{3, 4, 2, 8, 15, 267};
 
    auto print = [](const int& n) { std::cout << " " << n; };
 
    std::cout << "before:";
    std::for_each(nums.begin(), nums.end(), print);
    std::cout << '\n';
 
    std::for_each(nums.begin(), nums.end(), [](int &n){ n++; });
 
    // 对每个数调用 Sum::operator()
    Sum s = std::for_each(nums.begin(), nums.end(), Sum());
 
    std::cout << "after: ";
    std::for_each(nums.begin(), nums.end(), print);
    std::cout << '\n';
    std::cout << "sum: " << s.sum << '\n';
}

输出：
    before: 3 4 2 8 15 267
    after:  4 5 3 9 16 268
    sum: 305