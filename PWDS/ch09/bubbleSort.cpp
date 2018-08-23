
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

// 冒泡排序
// 平均复杂度： O（pow(n,2)）
// 最好情况：   O（n）   本身有序
// 最坏情况：   O(pow(n,2))
// 空间复杂度：  O（1）
// 稳定性：     稳定
// 思想： 两两比较相邻记录的关键字，如果反序则交换，知道没有反序的记录为止。
void bubbleSort(int *arr, int n)
{
    if (n <= 1) return;
    bool isSort = false;
    // 从头往前是因为：前面的已经排好序，不需要比较
    for (int i = 1; i < n && !isSort; ++i)
    {
        isSort = true;
        // 从尾端到前段两两比较，遇到逆序对就交换，将最后的移动到最前面
        for (int j = n-1; j >= i; --j)
        {
            if (arr[j] < arr[j-1])
            {
                std::swap(arr[j], arr[j-1]);
                isSort = false;
            }
        }
    }
}

int main()
{
    cout << "Bubble Sort" << endl;
    int arr[] = {4,2,7,9,5,4,6,2};
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

    bubbleSort(arr, sizeof(arr)/sizeof(arr[0]));

    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;
    return 0;
}