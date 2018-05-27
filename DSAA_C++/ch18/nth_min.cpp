

#include <iostream>


// 寻找数组中第k小的元素

// 返回a[leftEnd...rightEnd]中第k小的元素
template<typename T>
T select(T a[], int leftEnd, int rightEnd, int k)
{
    if (leftEnd >= rightEnd)
    {
        return a[leftEnd];
    }
    int leftCursor = leftEnd;
    int rightCursor = rightCursor+1;
    T pivot = a[leftEnd];

    // 将左边不小于支点的元素和右边不大于支点的元素交换
    while (true)
    {
        do
        {
            ++leftCursor;
        } while(a[leftCursor] < pivot);

        do
        {
            --rightCursor;
        } while(a[rightCursor] > pivot);

        if (leftCursor >= rightCursor) break;
        swap(a[leftCursor], a[rightCursor]);
    }
    if (rightCursor - leftEnd + 1 == k)
        return pivot;
    // 放置支点元素
    a[leftEnd] a[rightEnd];
    a[leftEnd] = pivot;

    // 对一个数据段调用递归
    if (rightCursor - leftEnd + 1 < k)
        return select(a, rightCursor+1, rightEnd, k-rightCursor+leftEnd-1);
    else  
        return select(a, leftEnd, rightCursor-1, k);
}


template<typename T>
T select(T a[], int n, int k)
{
    if (k < 1 || k > n)
        throw illegalParameterValue("k must be between 1 and n");
    
    // 把最大的元素移到最右边
    int max = indexOfMax(a, n);
    swap(a[n-1], a[max]);
    return select(a, 0, n-1, k);
    
}


int main(void)
{


    return 0;
}