
http://en.cppreference.com/w/cpp/algorithm/unique

std::unique

定义于头文件 <algorithm>

(1)	(C++20 前)
    template< class ForwardIt >
    ForwardIt unique( ForwardIt first, ForwardIt last );
    (C++20 起)
    template< class ForwardIt >
    constexpr ForwardIt unique( ForwardIt first, ForwardIt last );
(2)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt >
    ForwardIt unique( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last );

(3)	(C++20 前)
    template< class ForwardIt, class BinaryPredicate >
    ForwardIt unique( ForwardIt first, ForwardIt last, BinaryPredicate p );
    (C++20 起)
    template< class ForwardIt, class BinaryPredicate >
    constexpr ForwardIt unique( ForwardIt first, ForwardIt last, BinaryPredicate p );
(4)	(C++17 起)
    template< class ExecutionPolicy, class ForwardIt, class BinaryPredicate >
    ForwardIt unique( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, BinaryPredicate p );

从来自范围 [first, last) 的相继等价元素组消除首元素外的元素，并返回范围的新逻辑结尾的尾后迭代器。

通过用覆写要被擦除的元素的方式迁移范围中的元素进行移除。保持剩余元素的相对顺序，且不更改容器的物理大小。
指向范围的新逻辑结尾和物理结尾之间元素的迭代器仍然可解引用，但元素自身拥有未指定值。
调用 unique 典型地随后调用容器的 erase 方法，它擦除未指定值并减小容器的物理大小，以匹配其新的逻辑大小。

1) 用 operator== 比较元素。若它不是等价关系则行为未定义。
3) 用给定的谓词 p 比较元素。若它不是等价关系则行为未定义。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要处理的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若元素应被当做相等则返回 ​true 的二元谓词。
    谓词函数的签名应等价于如下者：
    bool pred(const Type1 &a, const Type2 &b);
    签名不必有 const & ，但函数必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 ForwardIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。
    -解引用 ForwardIt 结果的类型必须满足 MoveAssignable 的要求。

返回值
    指向范围新结尾的向前迭代器。

复杂度
    对于非空范围，准确应用 std::distance(first,last) -1 次对应的谓词。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class ForwardIt>
    ForwardIt unique(ForwardIt first, ForwardIt last)
    {
        if (first == last)
            return last;
    
        ForwardIt result = first;
        while (++first != last) {
            if (!(*result == *first) && ++result != first) {
                *result = std::move(*first);
            }
        }
        return ++result;
    }
版本二
    template<class ForwardIt, class BinaryPredicate>
    ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
    {
        if (first == last)
            return last;
    
        ForwardIt result = first;
        while (++first != last) {
            if (!p(*result, *first) && ++result != first) {
                *result = std::move(*first);
            }
        }
        return ++result;
    }

示例

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
 
int main() 
{
    // 移除重复元素（正常使用）
    std::vector<int> v{1,2,3,1,2,3,3,4,5,4,5,6,7};
    std::sort(v.begin(), v.end()); // 1 1 2 2 3 3 3 4 4 5 5 6 7 
    auto last = std::unique(v.begin(), v.end());
    // v 现在保有 {1 2 3 4 5 6 7 x x x x x x} ，其中 'x' 为不确定
    v.erase(last, v.end()); 
    for (int i : v)
      std::cout << i << " ";
    std::cout << "\n";
 
    // 移除连续空格
    std::string s = "wanna go    to      space?";
    auto end = std::unique(s.begin(), s.end(), [](char l, char r){
        return std::isspace(l) && std::isspace(r) && l == r;
    });
    // s 现在保有 "wanna go to space?xxxxxxxx" ，其中 'x' 为不确定
    std::cout << std::string(s.begin(), end) << '\n';
}

输出：
1 2 3 4 5 6 7
wanna go to space?