/*
 * SwitchToIntroCommand.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef _SWITCHTOINTROCOMMAND_H_
#define _SWITCHTOINTROCOMMAND_H_

#include "../BasicCommand.h"
#include "../../Controller.h"

class SwitchToIntroCommand: public BasicCommand {
public:
	SwitchToIntroCommand();
	virtual ~SwitchToIntroCommand();
	void ExecuteCommand() override;
	static const char* Name() { return "SwitchToIntroCommand"; };
};

#endif /* _SWITCHTOINTROCOMMAND_H_ */
