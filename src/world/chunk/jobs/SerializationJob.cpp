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

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "SerializationJob.h"

void SerializationJob::Execute()
{
    const BlockChangeData& blockData = m_queue.Pop();
    const std::string& filename = blockData.Filepath;

    std::ifstream file;
    file.open(filename);
    bool bReplaced = false;

    if (file.is_open())
    {
        std::vector<std::string> fileContent;
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
                line.replace(pos, search.str().length(), search.str());
                //LOG("Replace File %s -> Line: %s : SearchLine %s", filename.c_str(), line.c_str(), search.str().c_str());
                bReplaced = true;
            }
            fileContent.push_back(line);
        }

        file.close();

        if(bReplaced)
        {
            std::ofstream stream(filename, std::ofstream::out | std::ofstream::trunc);
            for (auto& s : fileContent)
                stream << s << '\n';
            stream.flush();
            stream.close();
        }
        else
        {
            std::ofstream stream(filename, std::ios_base::app | std::ios_base::out);
            stream << "X" << blockData.BlockPosition.X << "Y" << blockData.BlockPosition.Y << "Z" << blockData.BlockPosition.Z << ":" << static_cast<unsigned short>(blockData.Type) << '\n';
            stream.flush();
            stream.close();
            //LOG("Add Line into file %s", filename.c_str());
        }
        fileContent.clear();
    }
    else
    {
        std::ofstream stream(filename);
        stream << blockData.ChunkPosition.X << ';' << blockData.ChunkPosition.Y << '\n';
        stream << "X" << blockData.BlockPosition.X << "Y" << blockData.BlockPosition.Y << "Z" << blockData.BlockPosition.Z << ":" << static_cast<unsigned short>(blockData.Type) << '\n';
        stream.flush();
        stream.close();
        //LOG("Create File %s", filename.c_str());
    }
}
