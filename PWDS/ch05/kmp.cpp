
#include <stddef.h>
#include <assert.h>

#include <iostream>
#include <vector>
#include <string>

std::vector<int> get_next(const std::string &str)
{
    assert(str.size() > 0);

    int j = -1;
    std::vector<int> next(str.size());
    next[0] = -1;
    size_t i = 0;
    while (i < str.size() - 1)
    {
        if (j == -1 || str[i] == str[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else  
        {
            j = next[j];
        }
    }
    return next;
}

std::vector<int> get_nextval(const std::string &str)
{
    assert(str.size() > 0);

    int j = -1;
    std::vector<int> next(str.size());
    next[0] = -1;
    size_t i = 0;
    while (i < str.size() - 1)
    {
        if (j == -1 || str[i] == str[j])
        {
            ++i;
            ++j;
            //next[i] = j;

            if (str[i] != str[j])
                next[i] = j;
            else  
                next[i] = next[j];
        }
        else  
        {
            j = next[j];
        }
    }
    return next;
}
int index_kmp(const std::string &mstr, const std::string &tstr, int position)
{
    int size_mstr = mstr.size();
    int size_tstr = tstr.size();

    if (size_mstr == 0 || size_tstr == 0 || position > size_mstr)
        return -1;
    
    std::vector<int> next = get_next(tstr);

    int j = 0;
    int i = position;
    while (i < size_mstr && j < size_tstr)
    {
        if (j == -1 || mstr[i] == tstr[j])
        {
            ++i;
            ++j;
        }
        else  
        {
            j = next[j];
        }
    }

    if (j >= size_tstr)
        return i - size_tstr;
    else  
        return -1;
}

void printf_next(const std::vector<int> &next)
{
    std::cout << "next:" << "\n";
    for (auto v : next)
        std::cout << " " << v;
    std::cout << std::endl;
}
int main(void)
{
    std::string pstr1 = "abcdex";
    std::string pstr2 = "abcabx";
    std::string pstr3 = "ababaaaba";

    std::string pstr4 = "ababaaaba"; 
    std::string pstr5 = "aaaaaaaab";   

    std::vector<int> next = get_next(pstr1);
    printf_next(next);

    next = get_next(pstr2);
    printf_next(next);

    next = get_next(pstr3);
    printf_next(next);

    next = get_nextval(pstr4);
    printf_next(next);

    next = get_nextval(pstr5);
    printf_next(next);

    std::string main_str = "bacbababadababacambabacaddababacasdsd";
    std::string pattern_str = "ababaca";
    
    int index = index_kmp(main_str, pattern_str, 0);
    std::cout << "find index: 10 -- > " << index << std::endl;

    index = index_kmp(main_str, pattern_str, 11);
    std::cout << "find index: 26 -- > " << index << std::endl;
    return 0;
}