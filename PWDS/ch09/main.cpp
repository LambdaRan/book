

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
    for (int i = 2 * s; i < size; i *= 2)
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

// 堆排序
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
    heapSort(arr, ASIZE(arr));
    
    print_elements(arr, ASIZE(arr));

    return 0;
}