

#include "RCIPtr.h"

template<typename T>
void RCIPtr<T>::init()
{
    if (0 == counter)
        return;
    if (false == counter->isShareable())
    {
        counter = new CountHolder;
        counter->pointee = new T(*counter->pointee);
    }

    counter->addReference();
}

template<typename T>
RCIPtr<T>::RCIPtr(T *realPtr)
    : counter(new CountHolder)
{
    counter->pointee = realPtr;
    init();
}

template<typename T>
RCIPtr<T>::RCIPtr(const RCIPtr &rhs)
    : counter(rhs.counter)
{
    init();
}

template<typename T>
RCIPtr<T>::~RCIPtr()
{
    if (counter)
        counter->removeRefernece();
}
template<typename T>
RCIPtr<T>& RCIPtr<T>::operator=(const RCIPtr &rhs)
{
    if (counter != rhs.counter)
    {
        if (counter)
            counter->removeReference();
        counter = rhs.counter;
        init();
    }

    return *this;
}