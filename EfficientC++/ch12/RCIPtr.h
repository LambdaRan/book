

#ifndef RCIPTR_H
#define RCIPTR_H

#include "RCObject.h"

template<typename T>
class RCIPtr 
{

public:
    RCIPtr(T *realPtr = 0);

    RCIPtr(const RCIPtr &rhs);
    ~RCIPtr();

    RCIPtr& operator=(const RCIPtr &rhs);

    T* operator->() const 
    {
        return counter->pointee;
    }

    T& operator*() const 
    {
        return *(counter->pointee);
    }
    
private: 
    struct CountHolder : public RCObject
    {
        ~CountHolder()
        {
            delete pointee;
        }
        T *pointee;
    };
    RCIPtr<T>::CountHolder *counter;
    void init();
};

#endif