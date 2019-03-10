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


#include <sstream>
#include "SerializationJob.h"
#include "../../../utils/Filesystem.h"

void SerializationJob::Execute()
{
    const CompressedChunkData& chunkData = m_queue.Pop();
    /*std::ostringstream filename;
    filename << WORLD_PATH "/";
    filename << chunkData.X;
    filename << '_';
    filename << chunkData.Z;
    filename << ".data";
    FileSystem::Write(filename.str(),  reinterpret_cast<char*>(chunkData.Data), chunkData.Size);
    del (chunkData.Data);*/
}
