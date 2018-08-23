

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;


// 希尔排序
// 平均复杂度： O(nlogn) ~ O（pow(n,2)）
// 最好情况：   O（pow(n,3/2)）  
// 最坏情况：   O（pow(n,2)）   
// 空间复杂度：  O（1）
// 稳定性：     不稳定
// 思想： 将相聚某个增量的记录组成一个子序列，这样才能保证在子序列内分别进行直接插入排序后得到的结果是基本有序而不是局部有序。
void shellSort(int *arr, int n)
{
    if (n <= 1) return;
    int increment = n;
    do {
        increment = increment/3 + 1;
        for (int i = increment; i < n; ++i)
        {
            if (arr[i] < arr[i-increment])
            {
                int cur = arr[i];
                int j = 0;
                // 每隔increment个元素找到要插入的位置
                for (j = i-increment; j >= 0 && arr[j] > cur; j -= increment)
                    arr[j+increment] = arr[j];
                arr[j+increment] = cur; 
            }
        }
    } while (increment > 1);
}                                                      
int main()
{
    cout << "Shell Sort" << endl;
    int arr[] = {4,2,7,9,5,4,6,2};
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

    shellSort(arr, sizeof(arr)/sizeof(arr[0]));

    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;
    return 0;
}