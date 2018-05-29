

http://en.cppreference.com/w/cpp/algorithm/count

std::count, std::count_if
定义于头文件 <algorithm>
(1)	
    template< class InputIt, class T >
    typename iterator_traits<InputIt>::difference_type
        count( InputIt first, InputIt last, const T &value );

    template< class InputIt, class T >
    constexpr typename iterator_traits<InputIt>::difference_type
                count( InputIt first, InputIt last, const T &value );
(2)	
    template< class ExecutionPolicy, class ForwardIt, class T >
    typename iterator_traits<ForwardIt>::difference_type
        count( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, const T &value );

(3)	
    template< class InputIt, class UnaryPredicate >
    typename iterator_traits<InputIt>::difference_type
        count_if( InputIt first, InputIt last, UnaryPredicate p );

    template< class InputIt, class UnaryPredicate >
    constexpr typename iterator_traits<InputIt>::difference_type
                count_if( InputIt first, InputIt last, UnaryPredicate p );
(4)
    template< class ExecutionPolicy, class ForwardIt, class UnaryPredicate >
    typename iterator_traits<ForwardIt>::difference_type
        count_if( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p );

返回范围 [first, last) 中满足特定判别标准的元素数。

1) 计数等于 value 的元素。
3) 计数谓词 p 对其返回 true 的元素。
2,4) 同 (1,3) ，但按照 policy 执行。这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

参数
    first, last	-	要检验的元素范围
    value	-	要搜索的值
    policy	-	所用的执行策略。细节见执行策略。
    p	-	对要求的元素则返回 true 的一元谓词。
    谓词函数签名应等价于如下者：
    bool pred(const Type &a);
    签名不必拥有 const & ，但函数必须不修改传递给它的对象。
    类型 Type 必须使得 InputIt 类型对象能在解引用后隐式转换到 Type 。 ​

类型要求
    -InputIt 必须满足 InputIterator 的要求。
    -ForwardIt 必须满足 ForwardIterator 的要求。

返回值
    满足条件的元素数。

复杂度
    准确 last - first 次比较/应用谓词。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

注意
    对于无任何额外判别标准的 [first, last) 中的元素数，见 std::distance 。

可能的实现
版本一
    template<class InputIt, class T>
    typename iterator_traits<InputIt>::difference_type
        count(InputIt first, InputIt last, const T& value)
    {
        typename iterator_traits<InputIt>::difference_type ret = 0;
        for (; first != last; ++first) {
            if (*first == value) {
                ret++;
            }
        }
        return ret;
    }
版本二
    template<class InputIt, class UnaryPredicate>
    typename iterator_traits<InputIt>::difference_type
        count_if(InputIt first, InputIt last, UnaryPredicate p)
    {
        typename iterator_traits<InputIt>::difference_type ret = 0;
        for (; first != last; ++first) {
            if (p(*first)) {
                ret++;
            }
        }
        return ret;
    }

示例

#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
 
    // 确定 std::vector 中有多少个整数匹配目标值。
    int target1 = 3;
    int target2 = 5;
    int num_items1 = std::count(v.begin(), v.end(), target1);
    int num_items2 = std::count(v.begin(), v.end(), target2);
    std::cout << "number: " << target1 << " count: " << num_items1 << '\n';
    std::cout << "number: " << target2 << " count: " << num_items2 << '\n';
 
    // 用 lambda 表达式计量能被 3 整除的元素数。
    int num_items3 = std::count_if(v.begin(), v.end(), [](int i){return i % 3 == 0;});
    std::cout << "number divisible by three: " << num_items3 << '\n';
}

输出：
    number: 3 count: 2
    number: 5 count: 0
    number divisible by three: 3