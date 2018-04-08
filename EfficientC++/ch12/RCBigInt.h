

#ifndef RCBIGINT_H
#define RCBIGINT_H

#include "RCPtr.h"
#include "BigInt.h"

class RCBigInt
{
    friend RCBigInt operator+(const RCBigInt&, const RCBigInt&);
public: 
    RCBigInt(const char *p)
        : value(new BigInt(p))
    {}
    RCBigInt(unsigned u = 0)
        : value(new BigInt(u))
    {}

    RCBigInt(const BigInt &bi)
        : value(new BigInt(bi))
    {}

    void print() const 
    {
        //value->print();
    }
private: 
    RCPtr<BigInt> value;
};

inline
RCBigInt operator+(const RCBigInt &lhs, const RCBigInt &rhs)
{
    return RCBigInt(*(lhs.value) + *(rhs.value));
}

#endif