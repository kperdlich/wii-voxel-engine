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

#include "PlayerInventory.h"

PlayerInventory::PlayerInventory() {
	// TODO Auto-generated constructor stub

}

PlayerInventory::~PlayerInventory() {
	// TODO Auto-generated destructor stub
}

bool PlayerInventory::AddToInventory(IEquipable& item)
{
	if ( m_pInventory.size() < INVENTORY_MAX_SIZE )
	{
		m_pInventory.push_back(&item);
		return true;
	}

	return false;
}
