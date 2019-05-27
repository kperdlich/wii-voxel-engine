#pragma once

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
