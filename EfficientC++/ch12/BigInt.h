

#ifndef BIGINT_H
#define BIGINT_H

#include "RCObject.h"

class BigInt : public RCObject
{
    friend BigInt operator+(const BigInt&, const BigInt&);
public: 
    BigInt(const char *);
    BigInt(unsigned = 0);
    BigInt(const BigInt&);
    BigInt& operator=(const BigInt&);
    BigInt& operator+=(const BigInt&);
    ~BigInt();

    char *getDigits() const 
    {
        return digits;
    }

    unsigned getNdigits() const
    {
        return ndigits;
    }
private: 
    char *digits;
    unsigned ndigits;
    unsigned size; // 分配的字符串大小
    BigInt(const BigInt&, const BigInt&); // 主要用于操作的ctor
    char fetch(unsigned i) const;
};


inline
char BigInt::fetch(unsigned i) const
{
    return i < ndigits ? digits[i] : 0;
}

inline
BigInt operator+(const BigInt &left, const BigInt &right)
{
    return BigInt(left, right);
}
#endif // !BIGINT_H
