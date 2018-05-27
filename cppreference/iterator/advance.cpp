

http://en.cppreference.com/w/cpp/iterator/advance

std::advance
定义于头文件 <iterator>

    template< class InputIt, class Distance >
    void advance( InputIt& it, Distance n );

    template< class InputIt, class Distance >
    constexpr void advance( InputIt& it, Distance n );

增加给定的迭代器 it 以 n 个元素的步长。

若 n 为负，则迭代器自减。该情况下， InputIt 必须满足双向迭代器 (BidirectionalIterator) 的要求，否则行为未定义。

参数
    it	-	要前进的迭代器
    n	-	it 要前进的元素数

类型要求
    -InputIt 必须满足 InputIterator 的要求。

返回值
（无）

复杂度
    线性。
    然而，若 InputIt 额外满足随机访问迭代器 (RandomAccessIterator) 的要求，则复杂度是常数。

注意
    若指定的自增或自减序列要求一个不可自增迭代器（例如尾后迭代器）自增，
        或不可自减迭代器（例如首迭代器或孤立迭代器）自减，则行为未定义。

示例

#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
 
    auto vi = v.begin();
 
    std::advance(vi, 2);
 
    std::cout << *vi << '\n';
}

输出：
    4