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

#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include <queue>
#include <ogcsys.h>
#include <gccore.h>
#include "Mutex.h"


template<class T>
class SafeQueue
{
public:  
    T Pop()
    {
        m_mutex.Lock();
        T val = m_queue.front();
        m_queue.pop();
        m_mutex.Unlock();
        return val;
    }

    void Push(const T& value)
    {
        m_mutex.Lock();
        m_queue.push(value);
        m_mutex.Unlock();
    }

    bool IsEmpty()
    {
        m_mutex.Lock();
        bool bIsEmpty = m_queue.empty();
        m_mutex.Unlock();
        return bIsEmpty;
    }

private:
    std::queue<T> m_queue;
    Mutex m_mutex;
};

#endif // SAFEQUEUE_H
