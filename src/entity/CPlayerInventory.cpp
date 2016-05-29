/*
 * CPlayerInventory.cpp
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#include "CPlayerInventory.h"

CPlayerInventory::CPlayerInventory() {
	// TODO Auto-generated constructor stub

}

CPlayerInventory::~CPlayerInventory() {
	// TODO Auto-generated destructor stub
}

bool CPlayerInventory::AddToInventory(IEquipable& item)
{
	if ( m_pInventory.size() < INVENTORY_MAX_SIZE )
	{
		m_pInventory.push_back(&item);
		return true;
	}

	return false;
}

