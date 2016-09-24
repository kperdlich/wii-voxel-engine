/*
 * CHud.cpp
 *
 *  Created on: 09.07.2015
 *      Author: Kevin
 */

#include "CHud.h"

// define all component names here!

CHud::CHud() {



}

CHud::~CHud() {
	// TODO Auto-generated destructor stub
}

void CHud::addComponent(UITextureElement* component) {
	m_hudComponents.push_back( component );
}

void CHud::Init()
{
	m_playerInventoryHud = new CPlayerInventoryHud();
}
