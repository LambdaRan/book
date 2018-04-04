
#ifndef SIMPLEmUTEX_H
#define SIMPLEmUTEX_H

#include <pthread.h>

class SimpleMutex 
{
public:
    SimpleMutex(pthread_mutex_t& lock)
        : mutex_(lock)
    {
        acquire();
    }

    ~SimpleMutex()
    {
        release();
    }
private:
    int  acquire()
    {
        return pthread_mutex_lock(&mutex_);
    }

    int release()
    {
        return pthread_mutex_unlock(&mutex_);
    }
    pthread_mutex_t &mutex_;
};

#endif // !SIMPLEmUTEX_H
