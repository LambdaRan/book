
http://en.cppreference.com/w/cpp/algorithm/generate_n

std::generate_n

定义于头文件 <algorithm>
(1)	
    template< class OutputIt, class Size, class Generator >
    void generate_n( OutputIt first, Size count, Generator g );

    template< class OutputIt, class Size, class Generator >
    OutputIt generate_n( OutputIt first, Size count, Generator g );

    template< class OutputIt, class Size, class Generator >
    constexpr OutputIt generate_n( OutputIt first, Size count, Generator g );

(2)
    template< class ExecutionPolicy, class ForwardIt , class Size, class Generator >
    ForwardIt generate_n( ExecutionPolicy&& policy, ForwardIt first, Size count, Generator g );

1) 若 count>0 ，则赋值给定函数对象 g 所生成的值给始于 first 的范围的首 count 个元素。否则不做任何事。
2) 同 (1) ，但按照 policy 执行。
    此重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first	-	要生成的元素范围起始
    count	-	要生成的元素数
    policy	-	所用的执行策略。细节见执行策略。
    g	-	将要调用的生成器函数。
    签名应等价于如下：
    Ret fun();
    类型 Ret 必须使得 OutputIt 类型对象能被解引用并能被赋 Ret 类型值。 ​

类型要求
    -OutputIt 必须满足 OutputIterator 的要求。
    -ForwardIt 必须满足 ForwardIterator 的要求。

返回值
（无）	(C++11 前)
    若 count>0 则为最后被赋值元素后一位置的迭代器。否则为 first 。	(C++11 起)

复杂度
    对于 count>0 ，准确 count 次调用 g() 和赋值。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
    template< class OutputIt, class Size, class Generator >
    OutputIt generate_n( OutputIt first, Size count, Generator g )
    {
        for( Size i = 0; i < count; i++ ) {
            *first++ = g();
        }
        return first;
    }

示例
下列代码以随机数填充 int 的数组。

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <algorithm>
 
int main()
{
    const std::size_t N = 5;
    int ar[N];
    std::generate_n(ar, N, std::rand); // 使用 C 函数 rand()
 
    std::cout << "ar: ";
    std::copy(ar, ar+N, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}

可能的输出：

ar: 52894 15984720 41513563 41346135 51451456