
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;


// 选择排序
template<class ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end)
{
    for (ForwardIt i = begin; i != end; ++i)
        std::iter_swap(i, std::min_element(i, end));
}

// 选择排序
// 平均复杂度： O（pow(n,2)）
// 最好情况：   O（pow(n,2)）
// 最坏情况：   O（pow(n,2)）
// 空间复杂度：  O（1）
// 稳定性：     稳定
// 思想： 通过n-i次关键字间的比较，从n-i+1个记录中选出关键字最小的记录，并和第i个记录交换。
void selectSort(int *arr, int n)
{
    if (n <= 1) return;
    for (int i = 0; i < n; ++i)    
    {
        int minIndex = i;
        for (int j = i+1; j < n; ++j)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        if (i != minIndex)
            std::swap(arr[i], arr[minIndex]);
    }
}

int main()
{
    cout << "Select Sort" << endl;
    int arr[] = {4,2,7,9,5,4,6,2};
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

    selectSort(arr, sizeof(arr)/sizeof(arr[0]));

    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;
    return 0;
}