/*
 * Debug.h
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

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
