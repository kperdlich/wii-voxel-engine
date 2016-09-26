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
#include "../Controller.h"

#define DEBUG_LINE 200

class Debug {

private:
	std::vector<char*> m_logs;

public:
	Debug();
	virtual ~Debug();
	void Log(char* msg);
	void Print();
	void Clear();

	static Debug& GetInstance()
	{
		static Debug instance;
		return instance;
	}

	Debug(Debug const&)	  = delete;
	void operator=(Debug const&) = delete;

};

#endif /* _DEBUG_H_ */
