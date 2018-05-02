

#include <iostream>

#include <algorithm>
#include <iterator>
//#include <string>
#include <vector>

using namespace std;
//using std::string;

int main(void)
{
    //string str = "";
    vector<int> icv;
    int nums;
    std::cin >> nums;    
    for (int i = 0; i != nums; ++i)
    {
        int num;
        std::cin >> num;
        icv.push_back(num);
    }
    cout << endl;
    for (auto v : icv)
        cout << v << " ";
    cout << endl;

    for (size_t i = icv.size(); i != 0; --i)
    {
        vector<int>::iterator imax = max_element(icv.begin(), next(icv.begin(), i));
        reverse(icv.begin(), next(imax));
        reverse(icv.begin(), next(icv.begin(), i));
    }

    for (auto v : icv)
        cout << v << " ";
    cout << endl;    
    return 0;
}