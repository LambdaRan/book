

#include "BigInt.h"
#include <string.h>
#include <iostream>

BigInt::BigInt(const char *s)
{
    if (s[0] == '\0')
    {
        s = "0";
    }

    size = ndigits = strlen(s);
    digits = new char[size];
    for (unsigned i = 0; i < ndigits; ++i)
    {
        digits[i] = s[ndigits-1-i] - '0';
    }
}
BigInt::BigInt(unsigned u)
{
    unsigned v = u;
    for (ndigits = 1; (v/10) > 0; ++ndigits)
    {
        ;// 空
    }

    digits = new char[size = ndigits];

    for (unsigned i = 0; i < ndigits; ++i)
    {
        digits[i] = u % 10;
        u /= 10;
    }
}
BigInt::BigInt(const BigInt &copyFrom)
{
    size = ndigits = copyFrom.ndigits;
    digits = new char[size];
    for (unsigned i = 0; i < ndigits; ++i)
    {
        digits[i] = copyFrom.digits[i];
    }
}
BigInt::~BigInt()
{
    delete [] digits;
}

BigInt& BigInt::operator=(const BigInt &rhs)
{
    if (this == &rhs)
        return *this;
    ndigits = rhs.ndigits;
    if (ndigits > size)
    {
        delete [] digits;
        digits = new char[size = ndigits];
    }

    for (unsigned i = 0; i < ndigits; ++i)
    {
        digits[i] = rhs.digits[i];
    }

    return *this;
}
// 操作符构造函数 BigInt = left + right;
BigInt::BigInt(const BigInt &left, const BigInt &right)
{
    size = 1 + (left.ndigits > right.ndigits ? left.ndigits : right.ndigits);
    digits = new char[size];
    ndigits = left.ndigits;
    for (unsigned i = 0; i < ndigits; ++i)
    {
        digits[i] = left.digits[i];
    }
    *this += right;
}

BigInt& BigInt::operator+=(const BigInt &rhs)
{
    unsigned max = 1 + (rhs.ndigits > ndigits ? rhs.ndigits : ndigits);

    if (size < max)
    {
        char *d = new char[size = max];
        for (unsigned i = 0; i < ndigits; ++i)
        {
            d[i] = digits[i];
        }
        delete [] digits;
        digits = d;
    }
    while(ndigits < max)
    {
        digits[ndigits++] = 0;
    }

    for (unsigned i = 0; i < ndigits; ++i)
    {
        digits[i] += rhs.fetch(i);
        if (digits[i] >= 10)
        {
            digits[i] -= 10;
            digits[i+1] = 1;
        }
    }

    if (digits[ndigits-1] == 0)
    {
        --ndigits;
    }

    return *this;
}

std::ostream& operator<<(std::ostream &os, const BigInt &bi)
{
    char c;
    const char *d = bi.getDigits();
    for (int i = bi.getNdigits() - 1; i >= 0; --i)
    {
        c = d[i] + '0';
        os << c;
    }
    os << std::endl;
    return os;
}
