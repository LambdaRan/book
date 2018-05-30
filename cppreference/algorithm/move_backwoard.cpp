

http://en.cppreference.com/w/cpp/algorithm/move_backward

std::move_backward

定义于头文件 <algorithm>
    template< class BidirIt1, class BidirIt2 >
    BidirIt2 move_backward( BidirIt1 first, BidirIt1 last, BidirIt2 d_last );

    template< class BidirIt1, class BidirIt2 >
    constexpr BidirIt2 move_backward( BidirIt1 first, BidirIt1 last, BidirIt2 d_last );

移动来自范围 [first, last) 的元素到终于 d_last 的另一范围。以逆序移动元素（首先复制末元素），但保持其相对顺序。

若 d_last 在 (first, last] 内则行为未定义。该情况下必须用 std::move 代替 std::move_backward 。

参数
    first, last	-	要移动的元素范围
    d_last	-	目标范围结尾

类型要求
    -BidirIt1, BidirIt2 必须满足 BidirectionalIterator 的要求。

返回值
    目标范围中的迭代器，指向最后移动的元素。

复杂度
    准确移动赋值 last - first 次。

可能的实现
    template< class BidirIt1, class BidirIt2 >
    BidirIt2 move_backward(BidirIt1 first,
                                        BidirIt1 last,
                                        BidirIt2 d_last)
    {
        while (first != last) {
            *(--d_last) = std::move(*(--last));
        }
        return d_last;
    }

注意
    移动重叠的范围时， std::move 在移动到左侧（目标范围的起始在源范围外）时适合，
        而 std::move_backward 在移动到右侧（目标范围的结尾在源范围外）时适合。

示例

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
 
int main()
{
    std::vector<std::string> src{"foo", "bar", "baz"};
    std::vector<std::string> dest(src.size());
 
    std::cout << "src: ";
    for (const auto &s : src)
    {
        std::cout << s << ' ';
    }   
    std::cout << "\ndest: ";
    for (const auto &s : dest)
    {
        std::cout << s << ' ';
    }   
    std::cout << '\n';
 
    std::move_backward(src.begin(), src.end(), dest.end());
 
    std::cout << "src: ";                                                       
    for (const auto &s : src)
    {
        std::cout << s << ' ';
    }   
    std::cout << "\ndest: ";
    for (const auto &s : dest)
    {
        std::cout << s << ' ';
    }   
    std::cout << '\n';
}

输出：
src: foo bar baz 
dest:    
src:    
dest: foo bar baz