
#include <iostream>

#include <algorithm>

// 解法一：辗转相除法
// f(x, y) = f(y, x%y) (x >= y > 0)
long gcd_mod(long x, long y)
{
    if (x < y)
        std::swap(x, y);
    
    return (!y) ? x : gcd_mod(y, x%y);
}
long gcd_loop(long a, long b)
{
	unsigned long r;

	if (a < b)
		std::swap(a, b);

	if (!b)
		return a;
	while ((r = a % b) != 0) {
		a = b;
		b = r;
	}
	return b;
}

// 解法二：相减法
// f(x, y) = f(x-y, y)
// 辗转相除法, 对于大整数而言，取模运算（其中用到除法）是非常昂贵的开销，将成为整个算法的瓶颈
// 相减法 把大整数取模运算转换成大整数减法运算

long gcd_sub(long x, long y)
{
    if (x < y)
        std::swap(x, y);
    if (y == 0)
        return x;
    else
        return gcd_sub(x-y, y);
} 

// 解法三： 
// 相减法 缺点：迭代次数太多
// 结合 解法一与解法二
// 最坏时间复杂度 O(log2(max(x, y)))
inline
bool isEven(long num)
{
    return ((num & 0x01) == 0);
}
long gcd_other(long x, long y)
{
    if (x < y)
        std::swap(x, y);
    if (y == 0)
        return x;
    else  
    {
        if (isEven(x))
        {
            if (isEven(y))
                return (gcd_other(x >> 1, y >> 1) << 1);
            else  
                return gcd_other(x >> 1, y);
        }
        else  
        {
            if (isEven(y))
                return gcd_other(x, y >> 1);
            else  
                return gcd_other(y, x-y);            
        }
    }
}

int main(void)
{

    std::cout << "最大公约数：" << "\n";

    
    long n = 42;
    long m = 30;

    std::cout << "辗转相除法：递归　" << gcd_mod(m, n) << "\n";
    std::cout << "辗转相除法：迭代　" << gcd_loop(m, n) << "\n";
    
    std::cout << "相减法：　" << gcd_sub(m, n) << "\n";
    std::cout << "其他：　" << gcd_other(m, n) << "\n";
    


    return 0;
}