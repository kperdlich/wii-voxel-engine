/*
 * BasicCommand.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_COMMANDS_BASICCOMMAND_H_
#define SRC_COMMANDS_BASICCOMMAND_H_

class BasicCommand {
public:
	BasicCommand();
	virtual ~BasicCommand();
	virtual void executeCommand();
};

#endif /* SRC_COMMANDS_BASICCOMMAND_H_ */
