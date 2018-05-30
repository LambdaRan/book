
http://en.cppreference.com/w/cpp/algorithm/generate

std::generate

定义于头文件 <algorithm>
(1)	
    template< class ForwardIt, class Generator >
    void generate( ForwardIt first, ForwardIt last, Generator g );

    template< class ForwardIt, class Generator >
    constexpr void generate( ForwardIt first, ForwardIt last, Generator g );
(2)	
    template< class ExecutionPolicy, class ForwardIt, class Generator >
    void generate( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, Generator g );

1) 以给定函数对象 g 所生成的值赋值范围 [first, last) 中的每个元素。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要生成的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    g	-	将要调用的生成器函数。
    签名应等价于如下：
    Ret fun();
    类型 Ret 必须使得 ForwardIt 类型对象能被解引用并能被赋 Ret 类型值。 ​

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。

返回值
（无）

复杂度
    准确 std::distance(first, last) 次调用 g() 及赋值。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template<class ForwardIt, class Generator>
    void generate(ForwardIt first, ForwardIt last, Generator g)
    {
        while (first != last) {
            *first++ = g();
        }
    }

示例
下列代码以随机数填充 vector ：

#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
 
int main()
{
    std::vector<int> v(5);
    std::srand(0); // 仅为示例
    std::generate(v.begin(), v.end(), std::rand); // 使用 C 函数 std::rand()
 
    std::cout << "v: ";
    for (auto iv: v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
 
    // 以来自 lambda 函数的默认值 0,1,2,3,4 初始化
    // 等价于 std::iota(v.begin(), v.end(), 0);
    std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });
 
    std::cout << "v: ";
    for (auto iv: v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
}

可能的输出：

v: 1804289383 846930886 1681692777 1714636915 1957747793 
v: 0 1 2 3 4