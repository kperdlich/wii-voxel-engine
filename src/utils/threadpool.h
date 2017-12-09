/***
 *
 * Copyright (C) 2017 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <ogcsys.h>
#include <gccore.h>

#define THREAD_POOL_SIZE 5

class Thread
{
public:
    Thread()
    {
        LWP_MutexInit(&m_mutex, false);
    }

    int Create(void* (*entry)(void *),void *stackbase,u32 stack_size,u8 prio)
    {
        return LWP_CreateThread(&m_threadID, entry, this, stackbase, stack_size, prio);
    }

    bool Stop()
    {
        Lock();
        bool val = m_bStop;
        Unlock();
        return val;
    }

    void Lock()
    {
        LWP_MutexLock(m_mutex);
    }

    void Unlock()
    {
        LWP_MutexUnlock(m_mutex);
    }

    bool TryReserve()
    {
        bool bfound = false;
        Lock();
        if (m_bAvailable)
        {
            bfound = true;
            m_bAvailable = false;
        }
        Unlock();
        return bfound;
    }

    void Release()
    {        
        Lock();
        bool available = m_bAvailable;
        Unlock();

        if (!available)
        {
            Lock();
            m_bStop = true;
            Unlock();

            if ( IsSuspended() )
            {
                Resume();
            }
            LWP_JoinThread(m_threadID, nullptr);

            Lock();
            m_bAvailable = true;
            m_bStop = false;
            Unlock();
        }
    }

    void Destroy()
    {
        Release();
        LWP_MutexDestroy(m_mutex);
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
    mutex_t m_mutex;
};

static lwpq_t s_thread_queue;
static Thread s_threads[THREAD_POOL_SIZE];

class ThreadPool
{

public:

    static void Init()
    {         
         LWP_InitQueue(&s_thread_queue);
    }

    static Thread* GetThread()
    {
        for ( unsigned int i = 0; i < THREAD_POOL_SIZE; i++ )
        {
            Thread& thread = s_threads[i];
            if(thread.TryReserve())
            {
                return &thread;
            }
        }
        return nullptr;
    }

    static void Destroy()
    {
        for ( unsigned int i = 0; i < THREAD_POOL_SIZE; i++ )
        {
            s_threads[i].Destroy();
        }

        LWP_CloseQueue(s_thread_queue);
    }

    static const lwpq_t& GetThreadQueue()
    {
        return s_thread_queue;
    }

};

#endif // THREADPOOL_H
