

#include "TimeRecord.h"

#include <iostream>

#include <algorithm>
//#include <random>
#include <iterator>
#include <vector>


#define MAXSIZE 65536


int count = 0;

int binary_search(int *arr, int size, int value)
{
    count = 0;
    int low = 0;
    int hight = size - 1;
    while (low <= hight)
    {
        int mid = (low + hight) / 2;
        if (arr[mid] == value)
        {
            return mid;
        }
        else if (arr[mid] < value)
        {
            low = mid + 1;
        }
        else  
        {
            hight = mid - 1;
        }
        ++count;
    }
    return -1;
}

int interpolation_search(int *arr, int size, int value)
{
    count = 0;
    int low = 0;
    int hight = size - 1;
    while (low <= hight && low >= 0)
    {
        int mid = low + (hight-low) * (value-arr[low]) / (arr[hight]-arr[low]);
        if (arr[mid] == value)
        {
            return mid;
        }
        else if (arr[mid] < value)
        {
            low = mid + 1;
        }
        else  
        {
            hight = mid - 1;
        }
        ++count;
    }
    return -1;    
}

std::vector<int>& fibonacciLoop(int n = 30)
{
    std::vector<int> oldValue(n+1);

    oldValue[0] = 0;
    oldValue[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        oldValue[i] = oldValue[i-1] + oldValue[i-2];
    }

    return oldValue;
}

int fibonacci_search(int *arr, int size, int value)
{
    std::vector<int> fvector= fibonacciLoop();
    int k = 0;
    while (size > fvector[k] - 1)
        ++k;
    
    for (int i = size; i < fvector[k]-1; ++i)
        arr[i] = arr[n];

    int low = 0;
    int high = size - 1;
    while (low <= high)
    {
        int mid = low + fvector[k-1] - 1;
        if (value < arr[mid])
        {
            high = mid - 1;
            k = k - 1;
        }
        else if (value > arr[mid])
        {
            low = mid + 1;
            k = k - 2;
        }
        else  
        {
            if (mid <= size)
                return mid;
            else  
                return size;
        }
    }
    return -1;
}

int main(void)
{

    int test[MAXSIZE];
    for (std::size_t i = 0; i < sizeof(test)/sizeof(int); ++i)
        test[i] = i*2;
    
    //std::random_device rd;
    //std::mt19937 g(rd());
    //std::shuffle(std::begin(test), std::end(test), g);

    int input;
    std::cin >> input;

    TimeRecord tm;
    tm.start();
    int ret = binary_search(test, sizeof(test)/sizeof(int), input);
    tm.stop();
    std::cout << "binary search find " << input << " at " << ret << " count " << count << "\n";
    
    tm.start();
    ret = interpolation_search(test, sizeof(test)/sizeof(int), input);
    tm.stop();
    std::cout << "interpolation search find " << input << " at " << ret << " count " << count << "\n";

    return 0;
}