/*
 * SwitchToIntroCommand.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_COMMANDS_CLIENT_SWITCHTOINTROCOMMAND_H_
#define SRC_COMMANDS_CLIENT_SWITCHTOINTROCOMMAND_H_

#include "../BasicCommand.h"
#include "../../handler/Controller.h"

class SwitchToIntroCommand: public BasicCommand {
public:
	SwitchToIntroCommand();
	virtual ~SwitchToIntroCommand();
	void executeCommand() override;
	static const char* Name() { return "SwitchToIntroCommand"; };
};

#endif /* SRC_COMMANDS_CLIENT_SWITCHTOINTROCOMMAND_H_ */
