

#ifndef RCOBJECT_H
#define RCOBJECT_H

class RCObject
{
public: 
    void addReference()
    {
        ++refCount;
    }

    void removeRefernece()
    {
        if (--refCount == 0)
            delete this;
    }

    void markUnshareable()
    {
        shareable = false;
    }

    bool isShareable() const
    {
        return shareable;
    }

    bool isShared() const 
    {
        return refCount > 1;
    }
protected: 
    RCObject() 
        : refCount(0), shareable(true)
    {}

    RCObject(const RCObject &rhs)
        : refCount(0), shareable(true)
    {}

    RCObject& operator=(const RCObject &rhs)
    {
        return *this;
    }
    virtual ~RCObject() {}
private: 
    int refCount;
    bool shareable;
};

#endif // !RCOBJECT_H
