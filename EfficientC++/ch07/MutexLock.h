

#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H

#include "ABCLock.h"
#include <pthread.h>

class MutexLock : public ABCLock 
{
public: 
    MutexLock()
    {
        pthread_mutex_init(&lock_, NULL);
    }

    ~MutexLock()
    {
        pthread_mutex_destroy(&lock_);
    }

    void lock()
    {
        pthread_mutex_lock(&lock_);
    }

    void unlock()
    {
        pthread_mutex_unlock(&lock_);
    }
private: 
    pthread_mutex_t lock_;
};

#endif // !MUTEXLOCK_H
