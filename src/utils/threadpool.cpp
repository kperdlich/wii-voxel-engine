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

#include "Threadpool.h"

lwpq_t ThreadPool::s_thread_queue;
Thread ThreadPool::s_threads[THREAD_POOL_SIZE];

void ThreadPool::Init()
{
    LWP_InitQueue(&s_thread_queue);
}

Thread* ThreadPool::GetThread()
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

void ThreadPool::Destroy()
{
    for ( unsigned int i = 0; i < THREAD_POOL_SIZE; i++ )
    {
        s_threads[i].Destroy();
    }

    LWP_CloseQueue(s_thread_queue);
}

const lwpq_t &ThreadPool::GetThreadQueue()
{
     return s_thread_queue;
}
