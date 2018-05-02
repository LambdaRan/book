

#include <iostream>

// 二进制最低位是1为奇数，否则为偶数。
// 小结：
// 任意一个长度为m的二进制数N可以表示为 N = b[1]+b[2]*2 + b[3]*exp2(2) +b[4]*exp2(3) + ... + b[m]*exp2(m-1)  
// 其中b[i]表示此二进制数第i位上的数字（1或0）所以，若低位b[i]为1，则说明N为奇数，反之为偶数，
// 将其除以2，即等于将整个二进制数向低位移一位


// 求N！末尾有几个0 -->因式分解中5的指数，然后求和
int factorialTailCout0_one(int N)
{
    int ret = 0;
    for (int i = 1; i <= N; ++i)
    {
        int j = i;
        while (j % 5 == 0)
        {
            ++ret;
            j /= 5;
        }
    }
    return ret;
}
int factorialTailCount0_two(int N)
{
    int ret = 0;
    while (N)
    {
        ret += N / 5;
        N /= 5;
    }
    return ret;
}
// 求N！二进制表示的最后1的位置 --》含有质因数2的个数加1
int lowestOne(int N)
{
    int ret = 0;
    while (N)
    {
        N >>= 1;
        ret += N;
    }
    return ret;
}



int main(void)
{

    std::cout << "10! : 2 --> " << factorialTailCout0_one(10) << std::endl;
    std::cout << "10! : 2 --> " << factorialTailCount0_two(10) << std::endl;

    std::cout << "10! : " << lowestOne(10) << std::endl;
    return 0;
}