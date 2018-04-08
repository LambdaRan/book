

#include "RCPtr.h"

template<typename T>
void RCPtr<T>::init()
{
    if (0 == pointee)
        return;
    if (false == pointee->isShareable())
    {
        pointee = new T(*pointee);
    }

    pointee->addReference();
}

template<typename T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr &rhs)
{
    if (pointee != rhs.pointee)
    {
        if (pointee)
            pointee->removeReference();
        pointee = rhs.pointee;
        init();
    }

    return *this;
}