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

#include <vector>
#include "../Engine.h"

#define DEBUG_LINE 200
#define DEFAULT_DEBUG_INDEX -1

#ifdef DEBUG
    #define LOG(format, ...) Debug::GetInstance().Log(format, __VA_ARGS__)
#else
    #define LOG(format, ...)
#endif

class Debug {

private:
    std::vector<char*> m_logs;
    signed char m_logIndex = DEFAULT_DEBUG_INDEX;
    bool m_logOverflow = false;

private:
    void AllocateDebugBuffer();
    void DestroyDebugBuffer();
    char* GetNextLogBuffer();

public:
	Debug();
	virtual ~Debug();
    void Log(const char* format, ...);
	void Print();
    void Reset();
    void Destroy();

	static Debug& GetInstance()
	{
        static Debug s_instance;
        return s_instance;
	}

	Debug(Debug const&)	  = delete;
	void operator=(Debug const&) = delete;

};

#endif /* _DEBUG_H_ */
