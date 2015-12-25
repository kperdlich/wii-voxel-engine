/*
 * SwitchToInGameCommand.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_COMMANDS_CLIENT_SWITCHTOINGAMECOMMAND_H_
#define SRC_COMMANDS_CLIENT_SWITCHTOINGAMECOMMAND_H_

#include "../BasicCommand.h"
#include "../../handler/Controller.h"

class SwitchToInGameCommand: public BasicCommand {
public:
	SwitchToInGameCommand();
	virtual ~SwitchToInGameCommand();
	void executeCommand() override;
	static const char* Name() { return "SwitchToInGameCommand"; };
};

#endif /* SRC_COMMANDS_CLIENT_SWITCHTOINGAMECOMMAND_H_ */
