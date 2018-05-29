

http://en.cppreference.com/w/cpp/algorithm/search_n

std::search_n

定义于头文件 <algorithm>
(1)	
    template< class ForwardIt, class Size, class T >
    ForwardIt search_n( ForwardIt first, ForwardIt last, Size count, const T& value );

    template< class ForwardIt, class Size, class T >
    constexpr ForwardIt search_n( ForwardIt first, ForwardIt last, Size count, const T& value );
(2)
    template< class ExecutionPolicy, class ForwardIt, class Size, class T >
    ForwardIt search_n( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, Size count, const T& value );

(3)	
    template< class ForwardIt, class Size, class T, class BinaryPredicate >
    ForwardIt search_n( ForwardIt first, ForwardIt last, Size count, const T& value, 
                        BinaryPredicate p );

    template< class ForwardIt, class Size, class T, class BinaryPredicate >
    constexpr ForwardIt search_n( ForwardIt first, ForwardIt last, Size count, const T& value, 
                                BinaryPredicate p );
(4)
    template< class ExecutionPolicy, class ForwardIt, class Size, class T, class BinaryPredicate >
    ForwardIt search_n( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, Size count, const T& value, 
                        BinaryPredicate p );

在范围 [first, last) 中搜索 count 个等同元素的序列，每个都等于给定的值 value 。

1) 用 operator== 比较元素。
3) 用给定的二元谓词 p 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载仅若 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 才参与重载决议。

    参数
    first, last	-	要检验的元素范围
    count	-	要搜索的序列长度
    value	-	要搜索的元素值
    policy	-	所用的执行策略。细节见执行策略。
    p	-	若元素应被当做相等则返回 ​true 的二元谓词。
    谓词函数的签名应等价于如下者：
    bool pred(const Type1 &a, const Type2 &b);
    签名不必有 const & ，但函数必须不修改传递给它的对象。
    类型 Type1 必须使得 ForwardIt 类型的对象能在解引用后隐式转换到 Type1 。类型 Type2 必须使得 T 类型的对象能隐式转换到 Type2 。 ​

类型要求
    -ForwardIt 必须满足 ForwardIterator 的要求。

返回值
    指向范围 [first, last) 中找到的序列起始的迭代器。若找不到这种序列，则返回 last 。

复杂度
    至多应用 last - first 次谓词。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

可能的实现
版本一
    template<class ForwardIt, class Size, class T>
    ForwardIt search_n(ForwardIt first, ForwardIt last,
                        Size count, const T& value)
    {
        for(; first != last; ++first) {
            if (!(*first == value)) {
                continue;
            }
    
            ForwardIt candidate = first;
            Size cur_count = 0;
    
            while (true) {
                ++cur_count;
                if (cur_count == count) {
                    // 成功
                    return candidate;
                }
                ++first;
                if (first == last) {
                    // 穷尽列表
                    return last;
                }
                if (!(*first == value)) {
                    // 栏中过少
                    break;
                }
            }
        }
        return last;
    }
版本二
    template<class ForwardIt, class Size, class T, class BinaryPredicate>
    ForwardIt search_n(ForwardIt first, ForwardIt last,
                        Size count, const T& value, BinaryPredicate p)
    {
        for(; first != last; ++first) {
            if (!p(*first, value)) {
                continue;
            }
    
            ForwardIt candidate = first;
            Size cur_count = 0;
    
            while (true) {
                ++cur_count;
                if (cur_count == count) {
                    // 成功
                    return candidate;
                }
                ++first;
                if (first == last) {
                    // 穷尽列表
                    return last;
                }
                if (!p(*first, value)) {
                    // 栏中过少
                    break;
                }
            }
        }
        return last;
    }

示例

#include <iostream>
#include <algorithm>
#include <iterator>
 
template <class Container, class Size, class T>
bool consecutive_values(const Container& c, Size count, const T& v)
{
  return std::search_n(std::begin(c),std::end(c),count,v) != std::end(c);
}
 
int main()
{
   const char sequence[] = "1001010100010101001010101";
 
   std::cout << std::boolalpha;
   std::cout << "Has 4 consecutive zeros: "
             << consecutive_values(sequence,4,'0') << '\n';
   std::cout << "Has 3 consecutive zeros: "
             << consecutive_values(sequence,3,'0') << '\n';
}

输出：
Has 4 consecutive zeros: false
Has 3 consecutive zeros: true
