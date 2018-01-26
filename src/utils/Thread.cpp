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

#include "Thread.h"
#include "Debug.h"

int Thread::Create(void *(*entry)(void *), void *stackbase, u32 stack_size, u8 prio)
{
    int32_t ret = LWP_CreateThread(&m_threadID, entry, this, stackbase, stack_size, prio);
    if (ret < 0)
    {
        LOG("Thread: Couldn't create Thread!");
    }

    return ret;
}

void* Thread::ThreadEntry(void *args)
{
    static_cast<Thread*>(args)->PreExecute();
    return nullptr;
}


int Thread::Start()
{
    return Create(Thread::ThreadEntry, nullptr, 0, 128);
}

bool Thread::IsStopped()
{
    m_mutex.Lock();
    bool val = m_bStop;
    m_mutex.Unlock();
    return val;
}

void Thread::Stop()
{
    m_mutex.Lock();
    m_bStop = true;
    m_mutex.Unlock();

    if (IsSuspended())
    {
        Resume();
    }
    LWP_JoinThread(m_threadID, nullptr);

    m_mutex.Lock();

    m_bStop = false;
    m_mutex.Unlock();
}

bool Thread::IsSuspended()
{
    return LWP_ThreadIsSuspended(m_threadID);
}

void Thread::Resume()
{
    LWP_ResumeThread(m_threadID);
}

void Thread::Suspend()
{
    LWP_SuspendThread(m_threadID);
}
