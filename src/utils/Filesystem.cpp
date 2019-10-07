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
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "utils/Filesystem.h"
#include "utils/Debug.h"


void FileSystem::Init()
{
    assert(fatInitDefault());

    if (!DirectoryExist(WORLD_PATH))
        CreateDirectory(WORLD_PATH);
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
    struct stat sb;
    return stat(directoryPath.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode);
}

bool FileSystem::FileExist(const std::string &filePath)
{
    std::ifstream fstream;
    fstream.open(filePath);
    return fstream.is_open();
}

void FileSystem::Write(const std::string &file, const char* data, size_t size)
{
    std::ofstream stream(file);
    stream.write(data, size);
    stream.close();
}

int FileSystem::RemoveDirectory(const std::string& directoryPath)
{
    return RemoveDirectory(directoryPath.c_str());
}

int FileSystem::RemoveDirectory(const char *directoryPath)
{
    DIR* pdir = opendir(directoryPath);
    if (pdir != nullptr)
    {
        while(true)
        {
            struct dirent* pent = readdir(pdir);
            if(pent == nullptr)
                break;

            if(strcmp(".", pent->d_name) != 0 && strcmp("..", pent->d_name) != 0)
            {
                char dnbuf[260];
                sprintf(dnbuf, "%s/%s", directoryPath, pent->d_name);

                struct stat statbuf;
                stat(dnbuf, &statbuf);

                if(S_ISDIR(statbuf.st_mode))
                {
                    LOG("%s <DIR>\n", dnbuf);
                    RemoveDirectory(dnbuf);
                }
                else
                {
                    LOG("Deleting %s (%d)\n", dnbuf, (int)statbuf.st_size);
                    RemoveFile(dnbuf);
                }
            }
        }
        closedir(pdir);
    }
    return rmdir(directoryPath);
}

int FileSystem::RemoveFile(const std::string &filePath)
{
    return RemoveFile(filePath.c_str());
}

int FileSystem::RemoveFile(const char *filePath)
{
    return unlink(filePath);
}
