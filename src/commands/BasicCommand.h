/*
 * BasicCommand.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef _BASICCOMMAND_H_
#define _BASICCOMMAND_H_

class BasicCommand {
public:
	BasicCommand();
	virtual ~BasicCommand();
	virtual void ExecuteCommand();
};

#endif /* _BASICCOMMAND_H_ */
