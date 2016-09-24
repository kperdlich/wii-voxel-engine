/*
 * SwitchToMainMenuCommand.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef _SWITCHTOMAINMENUCOMMAND_H_
#define _SWITCHTOMAINMENUCOMMAND_H_

#include "../BasicCommand.h"
#include "../../Controller.h"

class SwitchToMainMenuCommand: public BasicCommand {
public:
	SwitchToMainMenuCommand();
	virtual ~SwitchToMainMenuCommand();
	void ExecuteCommand() override;
	static const char* Name() { return "SwitchToMainMenuCommand"; };
};

#endif /* _SWITCHTOMAINMENUCOMMAND_H_ */
