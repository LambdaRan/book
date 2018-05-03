

#include <stdint.h>

#include <iostream>


uint32_t sum1(uint32_t n)
{
    uint32_t iCount = 0;
    uint32_t iFactor = 1;
    uint32_t iLowerNum = 0;
    uint32_t iCurrNum = 0;
    uint32_t iHigherNum = 0;

    while (n / iFactor != 0)
    {
        iLowerNum = n - (n / iFactor) * iFactor;
        iCurrNum = (n / iFactor) % 10;
        iHigherNum = n / (iFactor * 10);

        switch (iCurrNum)
        {
            case 0: 
                iCount += iHigherNum * iFactor;
                break;
            case 1: 
                iCount += iHigherNum * iFactor + iLowerNum + 1;
                break;
            default: 
                iCount += (iHigherNum + 1) * iFactor;
                break;
        }
        iFactor *= 10;
    }
    return iCount;
}

int main(void)
{

    std::cout << " 100000000 -> " << sum1(100000000) << "\n";

    return 0;
}