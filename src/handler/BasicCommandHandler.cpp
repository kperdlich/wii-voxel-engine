/*
 * BasicCommandHandler.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "BasicCommandHandler.h"

CBasicCommandHandler::CBasicCommandHandler() {

}

CBasicCommandHandler::~CBasicCommandHandler() {
	for( std::map<const char*, BasicCommand*>::iterator cMapIt = m_commandMap.begin(); cMapIt != m_commandMap.end(); ++cMapIt )
	{
		delete cMapIt->second;
	}

	m_commandMap.clear();
}

void CBasicCommandHandler::executeCommand(const char* commandName) {
	if( m_commandMap.find( commandName ) != m_commandMap.end())
	{
		static_cast<BasicCommand*>(m_commandMap.at( commandName ))->executeCommand();
	}
}

void CBasicCommandHandler::init() {
	// register all client side commands
	m_commandMap.clear();

	m_commandMap[ SwitchToIntroCommand::Name() ] = new SwitchToIntroCommand();
	m_commandMap[ SwitchToMainMenuCommand::Name() ] = new SwitchToMainMenuCommand();
	m_commandMap[ SwitchToInGameCommand::Name() ] = new SwitchToInGameCommand();
}
