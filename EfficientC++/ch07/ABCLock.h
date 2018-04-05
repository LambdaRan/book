


#ifndef ABCLOCK_H
#define ABCLOCK_H

class ABCLock 
{
public: 
    virtual ~ABCLock() {}
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

#endif // !ABCLOCK_H
