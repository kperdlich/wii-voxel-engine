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

#include "Mutex.h"
#include <ogcsys.h>
#include <gccore.h>
#include "Thread.h"

#define THREAD_POOL_SIZE 5

class ThreadPool
{

private:
    static lwpq_t s_thread_queue;
    static Thread s_threads[THREAD_POOL_SIZE];

public:

    static void             Init();
    static Thread*          GetThread();
    static void             Destroy();
    static const lwpq_t&    GetThreadQueue();


};

#endif // THREADPOOL_H
