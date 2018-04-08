

#ifndef RCPTR_H
#define RCPTR_H

template<typename T>
class RCPtr 
{

public:
    RCPtr(T *realPtr = 0)
        : pointee(realPtr)
    {
        init();
    }

    RCPtr(const RCPtr &rhs)
        : pointee(rhs.pointee)
    {
        init();
    }

    ~RCPtr()
    {
        if (pointee)
            pointee->removeReference();
    }

    RCPtr& operator=(const RCPtr &rhs);

    T* operator->() const 
    {
        return pointee;
    }

    T& operator*() const 
    {
        return *pointee;
    }
    
private: 
    T *pointee;
    void init();
};

#endif