

#include <iostream>
#include <algorithm>

#define ASIZE(x) (sizeof(x)/sizeof(x[0]))

// 冒泡排序
// 时间复杂度： 最好O(1) 
// 最坏：逆序 O(pow(N))
void bubbleSort(int* a, int size)
{
    bool flag = true;
    for (int i = 0; i < size && flag; ++i)
    {
        flag = false;
        for (int j = size - 2; j >= i; --j)
        {
            if (a[j] > a[j+1])
            {
                std::swap(a[j], a[j+1]);
                flag = true;
            }
        }
    }
}

// 简单选择排序
// 时间复杂度： O(pow(N))
void selectSort(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        int minindex = i;
        for (int j = i+1; j < size; ++j)
        {
            if (arr[minindex] < arr[j])
                minindex = j;
        }
        if (i != minindex)
            std::swap(arr[i], arr[minindex]);
    }
}

// 插入排序
// 时间复杂度： 最好（O(n） 最坏(O(pow(N)))
void insertSort(int *arr, int size)
{
    for (int i = 1; i < size; ++i)
    {
        int tmp = arr[i];
        if (arr[i] < arr[i-1])
        {
            int j;
            for (j = i-1; j >= 0 && arr[j] > tmp; --j)
            {
                arr[j+1] = arr[j];
            }
            arr[j+1] = tmp;
        }
    }
}

// 希尔排序
// 不稳定
// 时间复杂度： O(pow(n, 3/2))
void shellSort(int* arr, int size)
{
    int increment = size;
    do
    {
        increment = increment / 3 + 1;
        for (int i = increment; i < size; ++i)
        {
            if (arr[i] < arr[i-increment])
            {
                int tmp = arr[i];
                int j;
                for (j = i-increment; j>=0 && arr[j] > tmp; j-= increment)
                {
                    arr[j+increment] = arr[j];
                }
                arr[j+increment] = tmp;
            }
        }
    } while(increment > 1);
}


void heapAdjust(int* arr, int s, int size)
{
    int tmp = arr[s];
    for (int i = 2 * s; i < size-1; i *= 2)
    {
        if (i < size && arr[i] < arr[i+1])
            ++i;
        if (tmp >= arr[i])
            break;
        arr[s] = arr[i];
        s = i;
    }
    arr[s] = tmp;
}

// 堆排序 --> 基于完全二叉树
// 不稳定
// 时间复杂度： 建堆：O(n)
// 重建堆：O(nlog2(n))
void heapSort(int* arr, int size)
{
    for (int i = size / 2; i >= 0; --i)
    {
        heapAdjust(arr, i, size);
    }

    for (int i = size-1; i > 0; --i)
    {
        std::swap(arr[0], arr[i]);
        heapAdjust(arr, 0, i-1);
    }
}


// 归并排序

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
        for (int l = 0; l <= m; ++l)
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
//
void mergeSort(int* arr, int size)
{
    int* tr = (int *)malloc(size*sizeof(int));
    int k = 1; // 
    while (k < size)
    {
        mergePass(arr, tr, k, size-1);
        k = k*2;
        mergePass(tr, arr, k, size-1);
        k = k*2;
    }
    free(tr);
}

// 快速排序
// 时间复杂度: 最好 O(nlog2(n))
// 最坏：O(n2)
int partition(int* arr, int low, int high)
{
    int pivotkey;
    pivotkey = arr[low];
    while (low < high)
    {
        while (low < high && arr[high] >= pivotkey)
            --high;
        std::swap(arr[low], arr[high]);
        while (low < high && arr[low] <= pivotkey)
            ++low;
        std::swap(arr[low], arr[high]);
    }
    return low;
}
void qsort(int* arr, int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = partition(arr, low, high);
        qsort(arr, low, pivot-1);
        qsort(arr, pivot+1, high);
    }
}
// 尾递归优化，减少递归次数
void qsort1(int* arr, int low, int high)
{
    int pivot;
    if ((high-low) > MAX_LENGTH_INSERT_SORT)
    {
        while (low < high)
        {
            pivot = partition(arr, low, high);
            qsort1(arr, low, pivot-1);
            low = pivot + 1;
        }
    } 
    else 
    {
        insertSort(arr, high+1);
    }
}
void quickSort(int* arr, int size)
{
    qsort(arr, 1, size);
}

void print_elements(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
int main(void)
{
    int arr[] = {9,1,5,8,3,7,4,6,2};
    //bubbleSort(arr, ASIZE(arr));
    //insertSort(arr, ASIZE(arr));
    //shellSort(arr, ASIZE(arr));
    //heapSort(arr, ASIZE(arr));
    
    mergeSort(arr, ASIZE(arr));
    print_elements(arr, ASIZE(arr));

    return 0;
}