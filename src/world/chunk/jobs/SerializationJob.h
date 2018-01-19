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

#ifndef SERIALIZATIONJOB_H
#define SERIALIZATIONJOB_H


#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "../chunkdata.h"
#include "../../../utils/Thread.h"
#include "../../../utils/SafeQueue.h"

void* QueueJob(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    SafeQueue<BlockChangeData>* queue = static_cast<SafeQueue<BlockChangeData>*>(thread->Data());

    while(true)
    {
       if (queue->IsEmpty())
       {
           if(thread->Stop())
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

          const std::string& filename = blockData.Filepath;

          std::ifstream file;
          file.open(filename);
          bool serialized = false;

          if (file.is_open())
          {
              std::ostringstream search;
              search << "X";
              search << blockData.BlockPosition.X;
              search << "Y";
              search << blockData.BlockPosition.Y;
              search << "Z";
              search << blockData.BlockPosition.Z;
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
                      //LOG("Replace File %s -> Line: %s : SearchLine %s", filename.c_str(), line.c_str(), search.str().c_str());
                      serialized = true;
                      break;
                  }
              }

              file.close();

              if(!serialized)
              {
                  std::ofstream stream(filename, std::ios_base::app | std::ios_base::out);
                  stream << "X" << blockData.BlockPosition.X << "Y" << blockData.BlockPosition.Y << "Z" << blockData.BlockPosition.Z << ":" << static_cast<unsigned short>(blockData.Type) << '\n';
                  stream.flush();
                  stream.close();
                  //LOG("Add Line into file %s", filename.c_str());
              }
          }
          else
          {
              std::ofstream stream(filename);

              stream << blockData.ChunkPosition.GetX() << ';' << blockData.ChunkPosition.GetY() << ';' << blockData.ChunkPosition.GetZ() << '\n';
              stream << "X" << blockData.BlockPosition.X << "Y" << blockData.BlockPosition.Y << "Z" << blockData.BlockPosition.Z << ":" << static_cast<unsigned short>(blockData.Type) << '\n';

              stream.flush();
              stream.close();
              //LOG("Create File %s", filename.c_str());
          }
        }
    }

    return nullptr;
}

#endif // SERIALIZATIONJOB_H
