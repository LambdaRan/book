

#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdlib.h>

using namespace std;


// 归并排序
template<class Iter>
void merge_sort(Iter first, Iter last)
{
    if (last - first > 1) 
    {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }
}


// 将有序序列SR[i...m] 和 SR[m+1...n]归并为有序的TR[i...n]
// 下标操作
void merge(int* sr, int* tr, int i, int m, int n)
{
    int j, k;
    for (j = m+1, k = i; i <= m && j <= n; ++k)
    {
        if (sr[i] < sr[j])
            tr[k] = sr[i++];
        else  
            tr[k] = sr[j++];
    }

    if (i <= m) // 将剩余的SR[i...m]复制到TR
    {
        for (int l = 0; l <= m-i; ++l)
        {
            tr[k+l] = sr[i+l];
        }
    }

    if (j <= n) // 将剩余的SR[j...n]复制到TR
    {
        for (int l = 0; i <= n-j; ++l)
        {
            tr[k+l] = sr[j+l];
        }
    }
}
// 将SR[]中相邻长度为s的子序列两两归并到TR[]
void mergePass(int* sr, int* tr, int s, int n) // 下标
{
    int i = 1;
    while (i <= n-2*s+1)
    {
        merge(sr, tr, i, i+s-1, i+2*s-1); // 两两归并
        i += 2*s;
    }

    if (i < n-s+1) //归并最后两个序列
    {
        merge(sr, tr, i, i+s-1, n);
    }
    else // 若最后只剩下单个子序列
    {
        for (int j = i; j <= n; ++j)
        {
            tr[j] = sr[j];
        }
    }
}
// 归并排序
// 平均复杂度： O（nlogn）
// 最好情况：   O（nlogn）
// 最坏情况：   O（nlogn）
// 空间复杂度：  O（n）
// 稳定性：     稳定
// 思想： 就是利用归并的思想实现排序。假设初始序列含有n个记录，则可以看成是n个有序的子序列，
// 每个子序列的长度为1，然后两两归并，得到ceil(n/2)个长度为2或1的有序子序列；再两两归并，。。
// 如此重复，直到得到一个长度为n的有序序列为止。

void mergeSort(int* arr, int size)
{
    int* tr = (int *)std::malloc(size * sizeof(int));
    int k = 1; // 
    while (k < size)
    {
        mergePass(arr, tr, k, size-1);
        k = k*2;
        mergePass(tr, arr, k, size-1);
        k = k*2;
    }
    std::free(tr);
}                                                     
int main()
{
    cout << "Merge Sort" << endl;
    int arr[] = {4,2,7,9,5,4,6,2};
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

    mergeSort(arr, sizeof(arr)/sizeof(arr[0]));

    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;
    return 0;
}
