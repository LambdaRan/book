

#include <iostream>
#include <string.h>


// 将有序序列 C[startOfFirst ... endOfFirst] 和 C[endOfFirst+1 ... endOfSecond]
// 归并为有序的 D[startOfFirst ... endOfSecond]
// 下标操作
template<typename T>
void merge(T c[], T d[], int startOfFirst, int endOfFirst, int endOfSecond)
{
    int first =  startOfFirst; // 第一个数据段的索引
    int second = endOfFirst + 1; // 第二个数据段的索引
    int result = endOfSecond; // 归并数据的索引

    // 直到有一半先结束
    while ((first <= endOfFirst) && (second <= endOfSecond))
    {
        if (c[first] <= c[second])
            d[result++] = c[first++];
        else  
            d[result++] = c[second++];
    }

    // 归并剩余的元素
    if (first > endOfFirst)
        for (int q = second; q <= endOfSecond; ++q)
            d[result++] = c[q];
    else  
        for (int q = first; q <= endOfFirst; ++q)
            d[result++] = c[q];
}

// 把相邻的两个数据段从X到Y归并
template<typename T>
void mergePass(T x[], T y[], int n, int segmentSize)
{
    // 将x中相邻长度为n的子序列两两归并到y
    int i = 0;
    while (i <= n - 2 * segmentSize)
    {
        merge(x, y, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
        i = i + 2 * segmentSize;
    }

    // 少于两个满数据段
    if (i + segmentSize < n)
    {
        // 剩有两个数据段
        merge(x, y, i, i + segmentSize - 1, n - 1);
    }
    else   
    {
        // 只剩下一个数据段,复制到y
        for (int j = i; j <= n; ++j)
            y[j] = x[j];
    }
}


template<typename T>
void mergeSort(T a[], int n)
{
    //T *b = new T [n];
    T *b = static_cast<T*>(malloc(n * sizeof(T)));
    if (!b)
    {
        std::cout << "error" << std::endl;
        return;
    }
    std::cout << "before:" << b << std::endl;
    int segmentSize = 1;
    while (segmentSize < n)
    {
        mergePass(a, b, n-1, segmentSize); // 从 a 到 b 的归并
        segmentSize += segmentSize;
        mergePass(b, a, n-1, segmentSize);
        segmentSize += segmentSize;
    }

    std::cout << "after:" << b << std::endl;

    //delete[] b;
    free(b);
    return ;
}


// 归并排序

// 将有序序列SR[i...m] 和 SR[m+1...n]归并为有序的TR[i...n]
// 下标操作
// void merge(int* sr, int* tr, int i, int m, int n)
// {
//     int j, k;
//     for (j = m+1, k = i; i <= m && j <= n; ++k)
//     {
//         if (sr[i] < sr[j])
//             tr[k] = sr[i++];
//         else  
//             tr[k] = sr[j++];
//     }

//     if (i <= m) // 将剩余的SR[i...m]复制到TR
//     {
//         for (int l = 0; l <= m; ++l)
//         {
//             tr[k+l] = sr[i+l];
//         }
//     }

//     if (j <= n) // 将剩余的SR[j...n]复制到TR
//     {
//         for (int l = 0; i <= n-j; ++l)
//         {
//             tr[k+l] = sr[j+l];
//         }
//     }
// }
// // 将SR[]中相邻长度为s的子序列两两归并到TR[]
// void mergePass(int* sr, int* tr, int s, int n) // 下标
// {
//     int i = 1;
//     while (i <= n-2*s+1)
//     {
//         merge(sr, tr, i, i+s-1, i+2*s-1); // 两两归并
//         i += 2*s;
//     }

//     if (i < n-s+1) //归并最后两个序列
//     {
//         merge(sr, tr, i, i+s-1, n);
//     }
//     else // 若最后只剩下单个子序列
//     {
//         for (int j = i; j <= n; ++j)
//         {
//             tr[j] = sr[j];
//         }
//     }
// }
// //
// void mergeSort(int* arr, int size)
// {
//     int* tr = (int *)malloc(size*sizeof(int));
//     int k = 1; // 
//     while (k < size)
//     {
//         mergePass(arr, tr, k, size-1);
//         k = k*2;
//         mergePass(tr, arr, k, size-1);
//         k = k*2;
//     }
//     free(tr);
// }

int main(void)
{

    //int arr[] = {49,80,2,12,55,31,84,38,59,71,8,43,34,94,64,13,15};
    int arr[] = {9,1,5,8,3,7,4,6,2};
    std::cout << "before: \n";
    for (auto v : arr)
        std::cout << v << " ";
    std::cout << "\n";

    mergeSort(arr, sizeof(arr)/sizeof(arr[0]));

    std::cout << "after: \n";
    for (auto v : arr)
        std::cout << v << " ";
    std::cout << "\n";

    return 0;
}