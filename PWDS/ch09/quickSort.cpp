
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;



//快速排序
template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last)
{
    if(first == last) return;
    auto pivot = *std::next(first, std::distance(first,last)/2);
    ForwardIt middle1 = std::partition(first, last, 
                            [pivot](const auto& em){ return em < pivot; });
    ForwardIt middle2 = std::partition(middle1, last, 
                            [pivot](const auto& em){ return !(pivot < em); });
    quicksort(first, middle1);
    quicksort(middle2, last);
}

int median(int a, int b, int c)
{
    if (a < b)
        if (b < c)
            return b;
        else if (a < c) // a < b, b >= c, a < c
            return c;
        else  
            return a;
    else if(a < c) // c > a >= b
        return a;
    else if (b < c) // a >= b, a >= c, b < c
        return c;
    else  
        return b;
}
int partition_v2(int *arr, int first, int last)
{
    int pivot = median(arr[first], arr[first+(last-first)/2], arr[last-1]);
    while (true)
    {
        // 找到 >= pivot的元素就停下来
        while (arr[first] < pivot) ++first;
        --last;
        // 找到<= pivot的元素就停下来
        while (pivot < arr[last]) --last;
        if (!(first < last)) return first;
        std::swap(arr[first], arr[last]);
        ++first;
    }
}
void qsort_v2(int* arr, int low, int high)
{
    if (low == high) return;

    int middle1 = partition_v2(arr, low, high);
    int middle2 = partition_v2(arr, middle1, high);
    qsort_v2(arr, low, middle1-1);
    qsort_v2(arr, middle2+1, high);
}

int partition(int* arr, int low, int high)
{
    int pivotkey = arr[low];
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
    if (low < high)
    {
        int middle1 = partition(arr, low, high);
        qsort(arr, low, middle1-1);
        qsort(arr, middle1+1, high);
    }
}
// 尾递归优化，减少递归次数
// void qsort1(int* arr, int low, int high)
// {
//     int pivot;
//     if ((high-low) > MAX_LENGTH_INSERT_SORT)
//     {
//         while (low < high)
//         {
//             pivot = partition(arr, low, high);
//             qsort1(arr, low, pivot-1);
//             low = pivot + 1;
//         }
//     } 
//     else 
//     {
//         insertSort(arr, high+1);
//     }
// }

// 快速排序
// 平均复杂度： O（nlogn）
// 最好情况：   O（nlogn）  
// 最坏情况：   O（pow(n,2)）   正序或逆序
// 空间复杂度：  O（logn） ~ O(n)
// 稳定性：     稳定
// 思想： 通过一趟排序将待排记录分割成独立的两部分，其中一部分记录的关键字均比另一部分记录的关键字小，
// 则可分别对这两部分记录继续进行排序，已达到整个序列有序的目的。
// 快速排序
// 时间复杂度: 最好 O(nlog2(n))
// 最坏：O(n2)
void quickSort(int* arr, int size)
{
    qsort(arr, 0, size);
}        

// 快速排序的优化：
// 1. 优化选取枢轴 --》三数取中median-of-three
// 2. 优化不必要的交换 采用赋值
// 3. 优化小数组时的排序方案
// 4. 优化递归操作 --》尾递归
int main()
{
    cout << "Quick Sort" << endl;
    int arr[] = {4,2,7,9,5,4,6,2};
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

    quickSort(arr, sizeof(arr)/sizeof(arr[0]));

    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;
    return 0;
}