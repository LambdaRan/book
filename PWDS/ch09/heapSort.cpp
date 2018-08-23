
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

// 标准库中函数：
// is_heap();
// is_heap_until();
// make_heap();
// push_heap();
// pop_heap();
// sort_heap();

void heapSort_v1(int *arr, int n)
{
    std::make_heap(arr, arr+n);
    for (int i = n; i > 0; --i)
        std::pop_heap(arr, arr+i);
    // while (n > 1)
    // {
    //     std::pop_heap(arr, arr+n);
    //     --n;
    // }
}

// 将待排序的序列构建成为一个大顶堆，其实就是从上往下，从右到左，
// 将每个非终端节点当做根节点，将其和其子树调整成大顶堆。
// adn 要调整的关键字arr[adn]
// end 使arr[adn ... end]成为一个大顶堆
void heapAdjust(int *arr, int adn, int end)
{
    int cur = arr[adn];
    for (int j = 2*adn; j < end-1; j*= 2)
    {
        // 判断左右孩子那个值大
        if (j < end && arr[j] < arr[j+1])   ++j;
        // 当前的值比左右孩子节点中的值都大，退出
        if (cur >= arr[j])   break;
        arr[adn] = arr[j];
        adn = j;
    }
    arr[adn] = cur;
}
// 堆排序
// 平均复杂度： O(nlogn)
// 最好情况：   O(nlogn)
// 最坏情况：   O(nlogn)
// 空间复杂度：  O（1）
// 稳定性：     不稳定
// 思想： 将待排序的序列构造成一个大顶堆，此时最大值就是堆顶的根节点，
// 将它跟尾元素交换，然后将剩下的n-1个元素重新构造成一个大顶堆。
void heapSort(int *arr, int n)
{
    if (n <= 1) return;
    for (int i = n/2; i >= 0; --i)
        heapAdjust(arr, i, n);
    for (int i = n; i > 0; --i)
    {
        std::swap(arr[0], arr[i-1]);
        heapAdjust(arr, 0, i-1);
    }
}                                                   
int main()
{
    cout << "Heap Sort" << endl;
    int arr[] = {4,2,7,9,5,4,6,2};
    cout << "init:\n";
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

    heapSort(arr, sizeof(arr)/sizeof(arr[0]));
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

    // cout << "init:\n";
    // std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    // cout << endl;
    // int n = sizeof(arr)/sizeof(arr[0]);

    // std::make_heap(arr, arr+n);
    // cout << "make heap:\n";
    // std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    // cout << endl;

    // std::pop_heap(arr, arr+n);
    // cout << "pop heap:\n";
    // std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    // cout << endl;

    // std::sort_heap(arr, arr+n-1);

    // //heapSort_v1(arr, sizeof(arr)/sizeof(arr[0]));
    // cout << "sort heap:\n";
    // std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    // cout << endl;
    return 0;
}
