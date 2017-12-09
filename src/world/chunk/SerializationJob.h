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

#ifndef SERIALIZATIONJOB_H
#define SERIALIZATIONJOB_H

#include "chunkdata.h"
#include "../../utils/SafeQueue.h"
#include "../../utils/threadpool.h"

class SerializationJob
{
public:
    SerializationJob() {}

    void Add(const BlockChangeData &data);
    void Start();
    void Stop();

private:
    SafeQueue<BlockChangeData> m_queue;
    Thread* m_pThread = nullptr;
};

#endif // SERIALIZATIONJOB_H