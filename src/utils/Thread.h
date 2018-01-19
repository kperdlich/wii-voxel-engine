#ifndef THREAD_H
#define THREAD_H

#include "Mutex.h"
#include <ogcsys.h>
#include <gccore.h>

class Thread
{
public:

    int Create(void* (*entry)(void *),void *stackbase,u32 stack_size,u8 prio)
    {
        return LWP_CreateThread(&m_threadID, entry, this, stackbase, stack_size, prio);
    }

    bool Stop()
    {
        m_mutex.Lock();
        bool val = m_bStop;
        m_mutex.Unlock();
        return val;
    }

    bool TryReserve()
    {
        bool bfound = false;
        m_mutex.Lock();
        if (m_bAvailable)
        {
            bfound = true;
            m_bAvailable = false;
        }
        m_mutex.Unlock();
        return bfound;
    }

    void Release()
    {
        m_mutex.Lock();
        bool available = m_bAvailable;
        m_mutex.Unlock();

        if (!available)
        {
            m_mutex.Lock();
            m_bStop = true;
            m_mutex.Unlock();

            if ( IsSuspended() )
            {
                Resume();
            }
            LWP_JoinThread(m_threadID, nullptr);

            m_mutex.Lock();
            m_bAvailable = true;
            m_bStop = false;
            m_mutex.Unlock();
        }
    }

    void Destroy()
    {
        Release();
    }

    bool IsSuspended()
    {
        return LWP_ThreadIsSuspended(m_threadID);
    }

    void Resume()
    {
        LWP_ResumeThread(m_threadID);
    }

    void Suspend()
    {
        LWP_SuspendThread(m_threadID);
    }

    void* Data()
    {
        return m_data;
    }

    void SetData(void* data)
    {
        m_data = data;
    }

private:
    lwp_t m_threadID;
    bool m_bAvailable = true;
    bool m_bStop = false;
    void* m_data = nullptr;
    Mutex m_mutex;
};


#endif // THREAD_H
