

#include <iostream>

#include <assert.h>

class test 
{
public: 
    int val1;
    static const int val2 = 0;
};
const int test::val2;

#include <stdio.h>
#include <limits.h>

int main(void)
{
    static_assert(sizeof(test) == sizeof(int), "sizeof(test) == sizeof(int)");
    return 0;
}