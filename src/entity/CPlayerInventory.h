/*
 * CPlayerInventory.h
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_CPLAYERINVENTORY_H_
#define SRC_ENTITY_CPLAYERINVENTORY_H_

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

#endif /* SRC_ENTITY_CPLAYERINVENTORY_H_ */
