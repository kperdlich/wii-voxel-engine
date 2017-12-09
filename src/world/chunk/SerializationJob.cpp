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


#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "SerializationJob.h"
#include "Chunk.h"
#include "../../utils/Debug.h"


void* QueueJob(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    SafeQueue<BlockChangeData>* queue = static_cast<SafeQueue<BlockChangeData>*>(thread->Data());

    while(true)
    {
       if (queue->IsEmpty())
       {
           if( thread->Stop())
           {
               break;
           }
           else
           {
                LWP_SuspendThread(LWP_GetSelf());
           }
       }
       else
       {
          const BlockChangeData& blockData = queue->Pop();

          std::string filename = ChunkSerializer::GetFilePath(blockData.ChunkPosition);

          std::ifstream file;
          file.open(filename);
          bool serialized = false;

          if (file.is_open())
          {
              std::ostringstream search;
              search << "X";
              search << blockData.BlockPosition.m_x;
              search << "Y";
              search << blockData.BlockPosition.m_y;
              search << "Z";
              search << blockData.BlockPosition.m_z;
              search << ":";

              size_t pos;
              std::string line;
              while(std::getline(file,line))
              {
                  pos=line.find(search.str());
                  if(pos!=std::string::npos)
                  {
                      search << static_cast<unsigned short>(blockData.Type);
                      search << '\n';
                      line.replace(pos, search.str().length(), search.str());
                      LOG("Replace File %s -> Line: %s : SearchLine %s", filename.c_str(), line.c_str(), search.str().c_str());
                      serialized = true;
                      break;
                  }
              }

              file.close();

              if(!serialized)
              {
                  std::ofstream stream(filename, std::ios_base::app | std::ios_base::out);
                  stream << "X" << blockData.BlockPosition.m_x << "Y" << blockData.BlockPosition.m_y << "Z" << blockData.BlockPosition.m_z << ":" << static_cast<unsigned short>(blockData.Type) << '\n';
                  stream.flush();
                  stream.close();
                  LOG("Add Line into file %s", filename.c_str());
              }
          }
          else
          {
              std::ofstream stream(filename);

              stream << blockData.ChunkPosition.GetX() << ';' << blockData.ChunkPosition.GetY() << ';' << blockData.ChunkPosition.GetZ() << '\n';
              stream << "X" << blockData.BlockPosition.m_x << "Y" << blockData.BlockPosition.m_y << "Z" << blockData.BlockPosition.m_z << ":" << static_cast<unsigned short>(blockData.Type) << '\n';

              stream.flush();
              stream.close();
              LOG("Create File %s", filename.c_str());
          }
        }
    }

    return nullptr;
}

void SerializationJob::Add(const BlockChangeData& data)
{
    m_queue.Push(data);
    if (m_pThread->IsSuspended())
    {
        m_pThread->Resume();
    }
}

void SerializationJob::Start()
{
    m_pThread = ThreadPool::GetThread();
    if ( m_pThread )
    {
        m_pThread->SetData((void*)&m_queue);
        m_pThread->Create( QueueJob, nullptr, 0, 128);
    }
    else
    {
        // todo handle
        LOG("SerializationJob: No free thread in pool!");
    }
}

void SerializationJob::Stop()
{
    if (m_pThread)
    {
        m_pThread->Release();
    }
}
