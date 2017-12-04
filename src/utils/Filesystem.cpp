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


#include <fat.h>
#include <dirent.h>
#include <sys/unistd.h>
#include <iostream>
#include <assert.h>

#include "Filesystem.h"
#include "Debug.h"


void FileSystem::Init()
{
    assert(fatInitDefault());
}

bool FileSystem::CreateDirectory(const std::string& directoryPath)
{
    if (!directoryPath.empty())
    {
        return (mkdir(directoryPath.c_str(), ACCESSPERMS) == 0);
    }

    return false;
}

bool FileSystem::DirectoryExist(const std::string& directoryPath)
{
    // todo implement
    return false;
}

bool FileSystem::FileExist(const std::string &filePath)
{
    std::ifstream fstream;
    fstream.open(filePath);
    return fstream.is_open();
}
