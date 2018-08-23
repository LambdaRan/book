
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;


// 插入排序
// insertion sort
// for (auto i = v.begin(); i != v.end(); ++i) 
// {
//     std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);
// }

// 插入排序
// 平均复杂度： O（pow(n,2)）
// 最好情况：   O（n）  有序
// 最坏情况：   O（pow(n,2)）   逆序
// 空间复杂度：  O（1）
// 稳定性：     稳定
// 思想： 将一个记录插入到已经排序的有序列表中，从而得到一个新的，记录数增1的有序表。
void insertSort(int *arr, int n)
{
    if (n <= 1) return;
    for (int i = 1; i < n; ++i)    
    {
        if (arr[i] < arr[i-1])
        {
            int dump = arr[i];
            int j;
            for (j = i-1; j >= 0 && arr[j] > dump; --j)
                std::swap(arr[j], arr[j+1]);
            arr[j+1] = dump;
        }
    }
}
int main()
{
    cout << "Insert Sort" << endl;
    int arr[] = {4,2,7,9,5,4,6,2};
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

    insertSort(arr, sizeof(arr)/sizeof(arr[0]));

    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;
    return 0;
}