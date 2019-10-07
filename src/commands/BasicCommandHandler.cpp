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

#include "commands/BasicCommandHandler.h"

BasicCommandHandler::BasicCommandHandler() {

}

BasicCommandHandler::~BasicCommandHandler() {
	for( auto cMapIt = m_commandMap.begin(); cMapIt != m_commandMap.end(); ++cMapIt )
	{
		delete cMapIt->second;
	}

	m_commandMap.clear();
}

void BasicCommandHandler::ExecuteCommand(const char* commandName) {
	if( m_commandMap.find( commandName ) != m_commandMap.end())
	{
		m_commandMap.at( commandName )->ExecuteCommand();
	}
}

void BasicCommandHandler::Init() {
	// register all client side commands
	m_commandMap.clear();

	m_commandMap[ SwitchToIntroCommand::Name() ] = new SwitchToIntroCommand();
	m_commandMap[ SwitchToMainMenuCommand::Name() ] = new SwitchToMainMenuCommand();
	m_commandMap[ SwitchToInGameCommand::Name() ] = new SwitchToInGameCommand();
}
