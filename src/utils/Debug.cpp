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

void Debug::Init()
{
    m_file.open(LOG_FILE);
}

void Debug::Log(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[200];
    vsprintf(buffer, format, args);

    va_end(args);

    m_file << buffer << std::endl;
}

void Debug::Release()
{
    m_file.close();
}
