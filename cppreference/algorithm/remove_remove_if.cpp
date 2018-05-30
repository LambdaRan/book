
http://en.cppreference.com/w/cpp/algorithm/remove


std::remove, std::remove_if

定义于头文件 <algorithm>
(1)	
    template< class ForwardIt, class T >
    ForwardIt remove( ForwardIt first, ForwardIt last, const T& value );

    template< class ForwardIt, class T >
    constexpr ForwardIt remove( ForwardIt first, ForwardIt last, const T& value );
(2)	
    template< class ExecutionPolicy, class ForwardIt, class T >
    ForwardIt remove( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, const T& value );

(3)	
    template< class ForwardIt, class UnaryPredicate >
    ForwardIt remove_if( ForwardIt first, ForwardIt last, UnaryPredicate p );

    template< class ForwardIt, class UnaryPredicate >
    constexpr ForwardIt remove_if( ForwardIt first, ForwardIt last, UnaryPredicate p );
(4)
    template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
    ForwardIt remove_if( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p );

从范围 [first, last) 移除所有满足特定判别标准的元素，并返回范围新结尾的尾后迭代器。

1) 移除所有等于 value 的元素。
3) 移除所有 p 对于它返回 true 的元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

通过以满足不移除的元素出现在范围起始的方式，迁移（以移动赋值的方式）范围中的元素进行移除。
    保持剩余元素的相对顺序，且不更改容器的物理大小。指向范围的新逻辑结尾和物理结尾之间元素的迭代器仍然可解引用，
    但元素自身拥有未指定值（因为可移动赋值 (MoveAssignable) 的后置条件）。
    调用 remove 典型地后随调用容器的 erase 方法，它擦除未指定值并减小容器的物理大小，以匹配其新的逻辑大小。

参数
    first, last	-	要处理的元素范围
    value	-	要移除的元素值
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若应该移除元素则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 ForwardIt 类型对象能在解引用后隐式转换到 Type 。 ​

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。
    -解引用 ForwardIt 结果的类型必须满足 MoveAssignable 的要求。
    -UnaryPredicate 必须满足 Predicate 的要求。

返回值
    新值范围的尾后迭代器（若它不是 end ，则它指向未指定值，而此迭代器与 end 之间的迭代器所指向的任何值亦然）。

复杂度
    准确应用 std::distance(first, last) 次谓词。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

注意
    同名的容器成员函数 list::remove 、 list::remove_if 、 forward_list::remove 及 forward_list::remove_if 
        擦除被移除的元素。

    这些算法不可用于关联容器，如 std::set 和 std::map ，
        因为 ForwardIt 不能解引用为可移动赋值 (MoveAssignable) 类型（这些容器中的关键不可修改）。

    标准库亦定义 std::remove 接收 const char* 的重载，用于删除文件： std::remove 。

    因为 std::remove 以引用接收 value ，若引用到范围 [first, last) 中的元素，则它能有不期待的行为。

可能的实现
版本一
    template< class ForwardIt, class T >
    ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
    {
        first = std::find(first, last, value);
        if (first != last)
            for(ForwardIt i = first; ++i != last; )
                if (!(*i == value))
                    *first++ = std::move(*i);
        return first;
    }
版本二
    template<class ForwardIt, class UnaryPredicate>
    ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
    {
        first = std::find_if(first, last, p);
        if (first != last)
            for(ForwardIt i = first; ++i != last; )
                if (!p(*i))
                    *first++ = std::move(*i);
        return first;
    }
示例
下列代码从 string 移除所有空格，通过迁移所有非空格字符到左侧，再擦除其他内容。这是擦除移除手法的样例。
// https://en.wikipedia.org/wiki/Erase-remove_idiom
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
 
int main()
{
    std::string str1 = "Text with some   spaces";
    auto ret = std::remove(str1.begin(), str1.end(), ' ');
    std::cout << *ret << " " << *(ret+1) << std::endl;
    str1.erase(ret,str1.end());
    std::cout << str1 << '\n';
 
    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(std::remove_if(str2.begin(), 
                              str2.end(),
                              [](unsigned char x){return std::isspace(x);}),
               str2.end());
    std::cout << str2 << '\n';
}

输出：
p a
Textwithsomespaces
Textwithsomewhitespaces