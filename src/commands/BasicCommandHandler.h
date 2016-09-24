/*
 * BasicCommandHandler.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef _BASICCOMMANDHANDLER_H_
#define _BASICCOMMANDHANDLER_H_

#include <map>
#include "../utils/GameHelper.h"
#include "../commands/BasicCommand.h"
#include "../commands/client/SwitchToInGameCommand.h"
#include "../commands/client/SwitchToIntroCommand.h"
#include "../commands/client/SwitchToMainMenuCommand.h"


class CBasicCommandHandler {
	std::map< const char*, BasicCommand* > m_commandMap;
public:
	CBasicCommandHandler();
	virtual ~CBasicCommandHandler();
	void ExecuteCommand( const char* commandName );
	void Init();
};

#endif /* _BASICCOMMANDHANDLER_H_ */
