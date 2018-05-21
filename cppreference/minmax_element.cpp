

http://en.cppreference.com/w/cpp/algorithm/minmax_element

std::minmax_element

定义于头文件 <algorithm>

<1>
    template< class ForwardIt > 
    std::pair<ForwardIt,ForwardIt> 
        minmax_element( ForwardIt first, ForwardIt last );
    template< class ForwardIt > 
    constexpr std::pair<ForwardIt,ForwardIt> 
        minmax_element( ForwardIt first, ForwardIt last );

<3>
    template< class ForwardIt, class Compare >
    std::pair<ForwardIt,ForwardIt> 
        minmax_element( ForwardIt first, ForwardIt last, Compare comp );


寻找范围 [first, last) 中最小和最大的元素。
1) 用 operator< 比较元素。
3) 用给定的二元比较函数 comp 比较元素。

参数：
    first, last	-	定义要检验的元素范围的迭代器
    policy	-	所用的执行策略。细节见执行策略。
    cmp	-	比较函数对象（即满足比较 (Compare) 要求的对象），若若 *a 小于 *b ，则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不需要拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 ForwardIt 类型的对象能在解引用后隐式转换到这两个类型。

类型要求
    ForwardIt 必须满足 ForwardIterator 的要求。

返回值
    以指向最小元素的迭代器为第一元素，以指向最大元素的迭代器为第二元素的 pair 。
    若范围为空则返回 std::make_pair(first, first) 。若多个元素等价于最小元素，则返回指向首个这种元素的迭代器。
    若多个元素等价于最大元素，则返回指向最后一个这种元素的迭代器。

复杂度
    至多应用谓词 max(floor(3/2(N−1)), 0) 次，其中 N = std::distance(first, last) 。

可能的实现
版本一
    template<class ForwardIt>
    std::pair<ForwardIt, ForwardIt> 
        minmax_element(ForwardIt first, ForwardIt last)
    {
        return std::minmax_element(first, last, std::less<>());
    }
版本二
    template<class ForwardIt, class Compare>
    std::pair<ForwardIt, ForwardIt> 
        minmax_element(ForwardIt first, ForwardIt last, Compare comp)
    {
        std::pair<ForwardIt, ForwardIt> result(first, first);
    
        if (first == last) return result;
        if (++first == last) return result;
    
        if (comp(*first, *result.first)) {
            result.first = first;
        } else {
            result.second = first;
        }
        while (++first != last) {
            ForwardIt i = first;
            if (++first == last) {
                if (comp(*i, *result.first)) result.first = i;
                else if (!(comp(*i, *result.second))) result.second = i;
                break;
            } else {
                if (comp(*first, *i)) {
                    if (comp(*first, *result.first)) result.first = first;
                    if (!(comp(*i, *result.second))) result.second = i;
                } else {
                    if (comp(*i, *result.first)) result.first = i;
                    if (!(comp(*first, *result.second))) result.second = first;
                }
            }
        }
        return result;
    }

示例
运行此代码

#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> v = { 3, 9, 1, 4, 2, 5, 9 };
 
    auto result = std::minmax_element(v.begin(), v.end());
    std::cout << "min element at: " << (result.first - v.begin()) << '\n';
    std::cout << "max element at: " << (result.second - v.begin()) << '\n';
}

输出：

min element at: 2
max element at: 6