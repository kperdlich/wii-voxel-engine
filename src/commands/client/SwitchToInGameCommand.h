/*
 * SwitchToInGameCommand.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef _SWITCHTOINGAMECOMMAND_H_
#define _SWITCHTOINGAMECOMMAND_H_

#include "../BasicCommand.h"
#include "../../Controller.h"

class SwitchToInGameCommand: public BasicCommand {
public:
	SwitchToInGameCommand();
	virtual ~SwitchToInGameCommand();
	void ExecuteCommand() override;
	static const char* Name() { return "SwitchToInGameCommand"; };
};

#endif /* _SWITCHTOINGAMECOMMAND_H_ */
