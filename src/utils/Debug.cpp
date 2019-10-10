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

#include "utils/Debug.h"
#include "utils/Mutex.h"
#include "utils/lockguard.h"

std::ofstream Debug::s_file;
Mutex Debug::s_fileMutex;
Socket Debug::s_socket;
bool Debug::s_bLogAlwaysToServer = false;

void Debug::Init()
{
	s_file.open(LOG_FILE);
}

void Debug::InitServer(const std::string& host, uint16_t port, bool bLogAlwaysToServer = false)
{
	s_socket.Connect(host, port);
	s_bLogAlwaysToServer = bLogAlwaysToServer;
}

void Debug::Log(const ELogType& logType, const char* format, ...)
{
	va_list args;
	va_start(args, format);

	char buffer[200];
	vsprintf(buffer, format, args);

	va_end(args);

	std::string msg;
	switch (logType)
	{
	case ELogType::INFO:
		msg += "[INFO] ";
		break;
	case ELogType::WARNING:
		msg += "[WARNING] ";
		break;
	case ELogType::ERROR:
		msg += "[ERROR] ";
		break;
	}
	msg += buffer;

	if (s_bLogAlwaysToServer)
	{
		s_socket.SendString(msg);
		char terminator = '\n';
		s_socket.Send(&terminator, 1);
	}

	lock_guard guard(s_fileMutex);
	s_file << msg << std::endl;
}

void Debug::LogServer(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	char buffer[200];
	vsprintf(buffer, format, args);

	va_end(args);

	s_socket.SendString(buffer);
}

void Debug::Release()
{
	s_file.close();
	if (s_socket.IsConnected())
		s_socket.Disconnect();
}
