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

#ifndef MUTEX_H
#define MUTEX_H

#include <ogcsys.h>
#include <gccore.h>

class Mutex
{
public:
    Mutex()
    {
        LWP_MutexInit(&m_mutex, false);
    }

    ~Mutex()
    {
        LWP_MutexDestroy(m_mutex);
    }

    void Lock()
    {
        LWP_MutexLock(m_mutex);
    }

    void Unlock()
    {
        LWP_MutexUnlock(m_mutex);
    }

private:
    mutex_t m_mutex;
};

#endif // MUTEX_H
