/***
 *
 * Copyright (C) 2018 DaeFennek
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

#ifndef JOB_H
#define JOB_H

#include "Thread.h"
#include "Threadpool.h"
#include "SafeQueue.h"
#include "Debug.h"

template<class T>
class Job
{
public:
    void Add(const T& data)
    {
        m_queue.Push(data);
        if (m_pThread->IsSuspended())
        {
            m_pThread->Resume();
        }
    }

    void Start(void* (*entry)(void *))
    {
        m_pThread = ThreadPool::GetThread();
        if ( m_pThread )
        {
            m_pThread->SetData((void*)&m_queue);
            m_pThread->Create(entry, nullptr, 0, 128);
        }
        else
        {
            // todo handle
            LOG("Job: No free thread in pool!");
        }
    }

    void Stop()
    {
        if (m_pThread)
        {
            m_pThread->Release();
        }
    }

private:
    SafeQueue<T> m_queue;
    Thread* m_pThread = nullptr;
};

#endif // JOB_H
