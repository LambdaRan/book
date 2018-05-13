

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
    bubbleSort(arr, ASIZE(arr));
    print_elements(arr, ASIZE(arr));

    return 0;
}