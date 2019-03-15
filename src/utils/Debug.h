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

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <fstream>
#include "Mutex.h"
#include "../net/Socket.h"
#include "../Engine.h"

#ifdef DEBUG
    #define LOG(format,...)     Debug::Log(ELogType::INFO, format, ##__VA_ARGS__)
    #define WARNING(format,...) Debug::Log(ELogType::WARNING, format, ##__VA_ARGS__)
    #define ERROR(format,...)   Debug::Log(ELogType::ERROR, format, ##__VA_ARGS__)
#else
    #define LOG(format, ...)
    #define WARNING(format,...)
    #define ERROR(format,...)
#endif

enum class ELogType : unsigned char
{
    INFO    = 0,
    WARNING = 1,
    ERROR   = 2
};

class Debug {

private:
    Debug() {}
    static Mutex s_fileMutex;
    static std::ofstream s_file;
    static Socket s_socket;
    static bool s_bLogAlwaysToServer;

public:
    static void Init();
    static void InitServer(bool bLogAlwaysToServer);
    static void Log(const ELogType& logType, const char* format, ...);
    static void LogServer(const char* format, ...);
    static void Release();   

    Debug(Debug const&)	  = delete;
    void operator=(Debug const&) = delete;
};

#endif /* _DEBUG_H_ */
