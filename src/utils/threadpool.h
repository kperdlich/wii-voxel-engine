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

static mutex_t s_mutex;


struct Thread
{
    lwp_t ThreadID;
    bool Available = true;
    void* Data;

    int Create(void* (*entry)(void *),void *stackbase,u32 stack_size,u8 prio)
    {
        return LWP_CreateThread(&ThreadID, entry, this, stackbase, stack_size, prio);
    }


    template<class T>
    void CleanUp()
    {
        delete (T*)Data;
    }

    void Release()
    {
        LWP_MutexLock(s_mutex);
        Available = true;
        LWP_MutexUnlock(s_mutex);
    }

};

static Thread s_threads[THREAD_POOL_SIZE];

class ThreadPool
{

public:

    static void Init()
    {
         LWP_MutexInit(&s_mutex, false);
    }

    static Thread* GetThread()
    {        
        LWP_MutexLock(s_mutex);

        for ( unsigned int i = 0; i < THREAD_POOL_SIZE; i++ )
        {
            if (s_threads[i].Available)
            {
                s_threads[i].Available = false;
                LWP_MutexUnlock(s_mutex);
                return &s_threads[i];
            }
        }

        LWP_MutexUnlock(s_mutex);
        return nullptr;
    }

    static void CleanUp()
    {
        LWP_MutexDestroy(s_mutex);
    }

    static void Join()
    {
        for ( unsigned int i = 0; i < THREAD_POOL_SIZE; i++ )
        {
            if(!s_threads[i].Available)
                LWP_JoinThread(s_threads[i].ThreadID, nullptr);
        }
    }

};

#endif // THREADPOOL_H
