#ifndef LOCKGUARD_H
#define LOCKGUARD_H

#include "Mutex.h"

class lock_guard
{
public:
    lock_guard(Mutex& mutex);
    ~lock_guard();
    void Release();
    void Lock();
private:
    Mutex& m_mutex;
    bool m_bReleased;
};

#endif // LOCKGUARD_H
