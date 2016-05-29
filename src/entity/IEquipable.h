/*
 * IEquipable.h
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_IEQUIPABLE_H_
#define SRC_ENTITY_IEQUIPABLE_H_

#include "../gui/components/UITextureElement.h"
#include "Entity.h"

class IEquipable {
public:
	IEquipable();
	virtual ~IEquipable();

	virtual UITextureElement& GetUITextureElement() = 0;
	virtual Entity& GetEntity() = 0;

};

#endif /* SRC_ENTITY_IEQUIPABLE_H_ */
