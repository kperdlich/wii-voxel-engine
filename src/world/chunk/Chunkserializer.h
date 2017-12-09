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

#ifndef CHUNKSERIALIZER_H
#define CHUNKSERIALIZER_H

#include <vector>
#include <string>
#include <gccore.h>
#include "chunkdata.h"
#include "SerializationJob.h"


class ChunkSerializer
{
public:
    ChunkSerializer();
    ~ChunkSerializer();

    void Serialize(const struct BlockChangeData& data);
    void Deserialize(class ChunkLoadingData* data);
    static std::string GetFilePath(const Vector3& chunkPosition);


private:    
    SerializationJob m_serializationJob;

};

#endif // CHUNKSERIALIZER_H
