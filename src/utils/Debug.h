/*
 * Debug.h
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#ifndef SRC_UTILS_DEBUG_H_
#define SRC_UTILS_DEBUG_H_

#include <grrlib.h>
#include <vector>
#include "../handler/Controller.h"

#define DEBUG_LINE 200

class Debug {

private:
	std::vector<char*> m_logs;

public:
	Debug();
	virtual ~Debug();
	void log(char* msg);
	void print();
	void clear();

	static Debug& getInstance()
	{
		static Debug instance;
		return instance;
	}

	Debug(Debug const&)	  = delete;
	void operator=(Debug const&) = delete;

};

#endif /* SRC_UTILS_DEBUG_H_ */
