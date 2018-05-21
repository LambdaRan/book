

#include <iostream>

#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

// 分而治之思想： 查找最大值最小值
// low high 为下标
// 比较次数 f(n) = 2 * f(n/2) + 2
pair<int, int> find_minmax(vector<int>& vec, int low, int high)
{
    pair<int, int> ret;
    int dif = high - low;
    if (dif > 1)
    {
        pair<int, int> lp = find_minmax(vec, low, low+dif/2);
        pair<int, int> hp = find_minmax(vec, low+dif/2+1, high);

        ret.first = lp.first < hp.first ? lp.first : hp.first;
        ret.second = lp.second > hp.second ? lp.second : hp.second;
    }
    else  
    {
        if (vec[low] < vec[high])
        {
            ret.first = vec[low];
            ret.second = vec[high];
        }
        else  
        {
            ret.first = vec[high];
            ret.second = vec[low];
        }
    }
    return ret;
}
// 非递归实现
// 总的比较次数： floor(3/2(N−1))
template<typename T>
bool find_minmaxLoop(T a[], int n, int& indexOfMin, int& indexOfMax)
{
    if (n < 1) return false;
    if (n == 1)
    {
        indexOfMin  = indexOfMax = 0;
        return true;
    }

    int s = 1; // 循环的起点
    if (n % 2 == 1) // n 为奇数
    {
        indexOfMin = indexOfMax = 0;
    }
    else  
    {
        if (a[0] > a[1])
        {
            indexOfMin = 1;
            indexOfMax = 0;
        }
        else   
        {
            indexOfMin = 0;
            indexOfMax = 1;
        }
        s = 2; 
    }

    for (int i = s; i < n; i += 2)
    {
        if (a[i] > a[i + 1])
        {
            if (a[i] > a[indexOfMax])
                indexOfMax = i;
            if (a[i + 1] < a[indexOfMin])
                indexOfMin = i + 1;
        }
        else  
        {
            if (a[i+1] > a[indexOfMax])
                indexOfMax = i = 1;
            if (a[i] < a[indexOfMin])
                indexOfMin = i;
        }
    }
    return true;
}
int main(void)
{

    vector<int> tv = {10, 21, 22, 79, 14, 44, 45, 76, 2, 93, 27, 8, 38, 64, 95, 13, 72, 20, 66};

    auto result = std::minmax_element(tv.begin(), tv.end());
    std::cout << "min element at: " << (result.first - tv.begin()) << " is " << *result.first << '\n';
    std::cout << "max element at: " << (result.second - tv.begin()) << " is " << *result.second << '\n';


    pair<int, int> ret = find_minmax(tv, 0, tv.size()-1);
    std::cout << "min element is: " << ret.first << '\n';
    std::cout << "max element is: " << ret.second << '\n';    
    return 0;
}