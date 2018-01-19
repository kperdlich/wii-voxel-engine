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

#ifndef CHUNKLOADERJOB_H
#define CHUNKLOADERJOB_H

#include <iostream>
#include <stdlib.h>
#include "../chunkdata.h"
#include "../../../utils/Thread.h"
#include "../../../utils/SafeQueue.h"

void* LoadChunkJob(void* data)
{
    Thread* thread = static_cast<Thread*>(data);
    SafeQueue<ChunkLoadingData>* queue = static_cast<SafeQueue<ChunkLoadingData>*>(thread->Data());

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
           const ChunkLoadingData& chunkData = queue->Pop();
           Chunk* chunk = chunkData.ChunkObj;
           const std::string& filepath = chunkData.Filepath;

           //chunk->Build();

           Vector3 chunkCenterPos;
           std::ifstream fstream;
           fstream.open(filepath);
           if (fstream.is_open())
           {
               std::string line;
               if (fstream.good())
               {
                   std::getline(fstream, line, ';');
                   chunkCenterPos.SetX(std::atof(line.c_str()));
                   std::getline(fstream, line, ';');
                   chunkCenterPos.SetY(std::atof(line.c_str()));
                   std::getline(fstream, line);
                   chunkCenterPos.SetZ(std::atof(line.c_str()));
               }

               auto blocks = chunk->GetBlocks();
               size_t posX, posY, posZ, posValue;
               while (std::getline(fstream, line))
               {
                   posX        = line.find("X");
                   posY        = line.find("Y");
                   posZ        = line.find("Z");
                   posValue    = line.find(":");

                   uint32_t x      = std::atoi(line.substr(posX+1, posY - posX).c_str());
                   uint32_t y      = std::atoi(line.substr(posY+1, posZ - posY).c_str());
                   uint32_t z      = std::atoi(line.substr(posZ+1, posValue - posZ).c_str());
                   uint8_t value   = std::atoi(line.substr(posValue+1).c_str());

                   blocks[x][y][z] = BlockType(value);
               }
           }

           chunk->SetLoaded(true);
           fstream.close();
       }
    }

    return nullptr;
}

#endif // CHUNKLOADERJOB_H
