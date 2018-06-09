

http://en.cppreference.com/w/cpp/algorithm/prev_permutation


std::prev_permutation
  C++ 算法库 
定义于头文件 <algorithm>
template< class BidirIt >
bool prev_permutation( BidirIt first, BidirIt last);
(1)	
template< class BidirIt, class Compare >
bool prev_permutation( BidirIt first, BidirIt last, Compare comp);
(2)	
变换范围 [first, last) 为来自于相对于 operator< 或 comp 的字典序的所有排列集合的上个排列。若这种排列存在则返回 true ，否则变换范围为末排列（如同用 std::sort(first, last); std::reverse(first, last); ）并返回 false 。

参数
first, last	-	要重排的元素范围
comp	-	比较函数对象（即满足比较 (Compare) 要求的对象），若首个参数小于第二个，则返回 ​true 。
比较函数的签名应等价于如下者：

 bool cmp(const Type1 &a, const Type2 &b);

签名不需要拥有 const & ，但函数对象必须不修改传递给它的对象。
类型 Type1 与 Type2 必须使得 BidirIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
-BidirIt 必须满足 ValueSwappable 和 BidirectionalIterator 的要求。
返回值
若新排列按字典序前趋旧排列则为 true 。若抵达首个排列并重置范围为最末排列则为 false 。

异常
任何从迭代器操作或元素交换抛出的异常。

复杂度
至多 (last-first)/2 次交换。

典型实现在排列的整个序列上，平均每次调用使用约 3 次比较和 1.5 次交换。

可能的实现
template<class BidirIt>
bool prev_permutation(BidirIt first, BidirIt last)
{
    if (first == last) return false;
    BidirIt i = last;
    if (first == --i) return false;
 
    while (1) {
        BidirIt i1, i2;
 
        i1 = i;
        if (*i1 < *--i) {
            i2 = last;
            while (!(*--i2 < *i))
                ;
            std::iter_swap(i, i2);
            std::reverse(i1, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}
示例
下列代码以逆序打印字符串 "abc" 的所有六个排列

运行此代码
#include <algorithm>
#include <string>
#include <iostream>
#include <functional>
int main()
{
    std::string s="abc";
    std::sort(s.begin(), s.end(), std::greater<char>());
    do {
        std::cout << s << ' ';
    } while(std::prev_permutation(s.begin(), s.end()));
    std::cout << '\n';
}
输出：

cba cab bca bac acb abc