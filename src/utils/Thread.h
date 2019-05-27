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

#pragma once

#include <ogcsys.h>
#include <gccore.h>
#include "Mutex.h"
#include "Debug.h"

class Thread        
{
public:
    virtual ~Thread() {}
    int Start();
    bool IsStopped();
    void Stop();
    bool IsSuspended();
    void Resume();
    void Suspend();

private:
    int Create(void* (*entry)(void *), void *stackbase, u32 stack_size, u8 prio);
    static void* ThreadEntry(void* args);

protected:
    virtual void PreExecute() = 0;
    virtual void Execute() = 0;

private:
    lwp_t m_threadID;   
    bool m_bStop = false;    
    Mutex m_mutex;
};
