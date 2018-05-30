

http://en.cppreference.com/w/cpp/algorithm/copy_backward

std::copy_backward

定义于头文件 <algorithm>
    template< class BidirIt1, class BidirIt2 >
    BidirIt2 copy_backward( BidirIt1 first, BidirIt1 last, BidirIt2 d_last );
    (C++20 前)
    template< class BidirIt1, class BidirIt2 >
    constexpr BidirIt2 copy_backward( BidirIt1 first, BidirIt1 last, BidirIt2 d_last );
    (C++20 起)

复制来自 [first, last) 所定义范围的元素，到终于 d_last 的范围。以逆序复制元素（首先复制末元素），但保持其相对顺序。

若 d_last 在 (first, last] 中则行为未定义。该情况下必须用 std::copy 取代 std::copy_backward 。

参数
    first, last	-	要复制的元素范围
    d_last	-	目标范围的结尾。

类型要求
    -BidirIt 必须满足 BidirectionalIterator 的要求。

返回值
    指向最后复制元素的迭代器。

复杂度
    准确赋值 last - first 次。

注意
    复制重叠的范围时， std::copy 在复制到左侧（目标范围的起始在源范围外）时适合，而 std::copy_backward 在复制到右侧（目标范围的结尾在源范围外）时适合。

可能的实现
    template< class BidirIt1, class BidirIt2 >
    BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
    {
        while (first != last) {
            *(--d_last) = *(--last);
        }
        return d_last;
    }

示例

#include <algorithm>
#include <iostream>
#include <vector>
 
int main()
{
    std::vector<int> from_vector;
    for (int i = 0; i < 10; i++) {
        from_vector.push_back(i);
    }
 
    std::vector<int> to_vector(15);
 
    std::copy_backward(from_vector.begin(), from_vector.end(), to_vector.end());
 
    std::cout << "to_vector contains: ";
    for (auto i: to_vector) {
        std::cout << i << " ";
    }
 }

输出：
to_vector contains: 0 0 0 0 0 0 1 2 3 4 5 6 7 8 9