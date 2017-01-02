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
#include <stdio.h>

#define DEBUG_STRINGS 25
#define CHARS_PER_DEBUG_STRING 50 // should always be enough for debug logs

Debug::Debug()
{
    AllocateDebugBuffer();
}

Debug::~Debug()
{
    DestroyDebugBuffer();
}

void Debug::AllocateDebugBuffer()
{
    for ( uint i = 0; i < DEBUG_STRINGS; i++)
    {
        m_logs.push_back(new char[CHARS_PER_DEBUG_STRING]);
    }
}

void Debug::DestroyDebugBuffer()
{
    for ( uint i = 0; i < DEBUG_STRINGS; i++)
    {
        delete[] m_logs[i];
    }
}

char* Debug::GetNextLogBuffer()
{
    if ( m_logIndex == DEBUG_STRINGS - 1)
    {
        m_logIndex = DEFAULT_DEBUG_INDEX;
        m_logOverflow = true;
    }
    return m_logs[++m_logIndex];
}

void Debug::Log(char* format, ...)
{    
    va_list args;
    va_start(args, format);

    char* pBuffer = GetNextLogBuffer();
    vsprintf(pBuffer, format, args);

    va_end(args);
}

void Debug::Print()
{
    uint y = DEBUG_LINE;
    for (char i = 0; i <= m_logIndex; i++)
	{
        GRRLIB_PrintfTTF( 0, y, Controller::GetInstance().GetFontHandler().GetNativFontByID( DEFAULT_FONT_ID ), m_logs[i], DEFAULT_FONT_SIZE, m_logOverflow ? GRRLIB_RED : GRRLIB_WHITE );

        if ( m_logIndex > DEBUG_STRINGS )
		{
			y = DEBUG_LINE;
		}
		else
		{
			y += 10;
        }
    }
}

void Debug::Reset()
{
    m_logIndex = DEFAULT_DEBUG_INDEX;
}

void Debug::Destroy()
{
    DestroyDebugBuffer();
}



