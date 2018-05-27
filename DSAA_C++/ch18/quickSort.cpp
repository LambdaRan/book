

#include <iostream>


template<typename T>
void quickSort(T a[], int leftEnd, int rightEnd)
{
    if (leftEnd <= rightEnd) return;

    int leftCursor = leftEnd;
    int rightCursor = rightEnd + 1;

    T pivot = a[leftEnd];

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

    a[leftEnd] = a[rightCursor];
    a[rightEnd] = pivot;

    quickSort(a, leftEnd, rightCursor-1);
    quickSort(a, rightCursor+1, rightEnd);

}
template<typename T>
void quickSort(T a[], int n)
{
    if (n <= 1) return ;
    int max = indexOfMax(a, n);
    swap(a[n-1], a[max]);;
    quickSort(a, 0, n-2);
}


int main(void)
{



    return 0;
}