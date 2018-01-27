/***
 *
 * Copyright (C) 2016 DaeFennek
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

#include "Debug.h"
#include "Mutex.h"

std::ofstream Debug::s_file;
Mutex Debug::s_mutex;

void Debug::Init()
{
    s_file.open(LOG_FILE);
}

void Debug::Log(const ELogType &logType, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[200];
    vsprintf(buffer, format, args);

    va_end(args);

    s_mutex.Lock();
    switch (logType)
    {
    case ELogType::INFO:
        s_file << "[INFO] ";
        break;
    case ELogType::WARNING:
        s_file << "[WARNING] ";
        break;
    case ELogType::ERROR:
        s_file << "[ERROR] ";
        break;
    }
    s_file << buffer << std::endl;
    s_mutex.Unlock();
}

void Debug::Release()
{
    s_file.close();
}
