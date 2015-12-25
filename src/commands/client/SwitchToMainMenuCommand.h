/*
 * SwitchToMainMenuCommand.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_COMMANDS_CLIENT_SWITCHTOMAINMENUCOMMAND_H_
#define SRC_COMMANDS_CLIENT_SWITCHTOMAINMENUCOMMAND_H_

#include "../BasicCommand.h"
#include "../../handler/Controller.h"

class SwitchToMainMenuCommand: public BasicCommand {
public:
	SwitchToMainMenuCommand();
	virtual ~SwitchToMainMenuCommand();
	void executeCommand() override;
	static const char* Name() { return "SwitchToMainMenuCommand"; };
};

#endif /* SRC_COMMANDS_CLIENT_SWITCHTOMAINMENUCOMMAND_H_ */
