/*
 * SwitchToInGameCommand.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "SwitchToInGameCommand.h"

SwitchToInGameCommand::SwitchToInGameCommand() {
	// TODO Auto-generated constructor stub

}

SwitchToInGameCommand::~SwitchToInGameCommand() {
	// TODO Auto-generated destructor stub
}

void SwitchToInGameCommand::executeCommand() {
	Controller::getInstance().getSceneHandler()->loadScene( IN_GAME_ID );
}
