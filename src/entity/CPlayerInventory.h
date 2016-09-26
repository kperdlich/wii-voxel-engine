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

#ifndef _CPLAYERINVENTORY_H_
#define _CPLAYERINVENTORY_H_

#include "IEquipable.h"

#define INVENTORY_MAX_SIZE 10

class CPlayerInventory {
public:
	CPlayerInventory();
	virtual ~CPlayerInventory();

	bool AddToInventory(IEquipable& item);

private:
	std::vector<IEquipable*> m_pInventory;
	uint m_inventoryIndex = 0;
};

#endif /* _CPLAYERINVENTORY_H_ */
