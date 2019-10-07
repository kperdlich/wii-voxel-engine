/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#pragma once

#include <map>
#include "utils/GameHelper.h"
#include "commands/BasicCommand.h"
#include "commands/client/SwitchToInGameCommand.h"
#include "commands/client/SwitchToIntroCommand.h"
#include "commands/client/SwitchToMainMenuCommand.h"


class BasicCommandHandler {
	std::map< const char*, BasicCommand* > m_commandMap;
public:
	BasicCommandHandler();
	virtual ~BasicCommandHandler();
	void ExecuteCommand( const char* commandName );
	void Init();
};
