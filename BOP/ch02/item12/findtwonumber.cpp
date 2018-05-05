

// 快速寻找满足条件的两个数

#include <iostream>

// 解法一： 穷举法
// 时间复杂度： O(pow(N, 2))

// 解法二：
// 先排序（O(Nlog2(N))）,在查找(O(log2(N))) ---> O(Nlog2(N))
// 使用hash表
// 时间复杂度 O(N) 空间复杂度O(N) --> 空间换取时间

// 解法三：
// 首先对数组进行排序，时间复杂度O(Nlog2(N))
// 然后令i=0， j=n-1, 看arr[i] + arr[j]是否等于sum，如果是则结束
// 如果小于sum，则 ++i，如果大于sum 则--j
// 只需遍历一次，就可得到最后结果，时间复杂度O(N)
// 总的时间复杂度 O(Nlog2(N))

int main(void)
{



    return 0;
}