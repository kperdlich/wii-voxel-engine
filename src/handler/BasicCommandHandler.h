/*
 * BasicCommandHandler.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_HANDLER_BASICCOMMANDHANDLER_H_
#define SRC_HANDLER_BASICCOMMANDHANDLER_H_

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
	void executeCommand( const char* commandName );
	void init();
};

#endif /* SRC_HANDLER_BASICCOMMANDHANDLER_H_ */
