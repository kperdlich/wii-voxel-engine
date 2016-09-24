/*
 * IEquipable.h
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#ifndef _IEQUIPABLE_H_
#define _IEQUIPABLE_H_

#include "../components/UITextureElement.h"
#include "Entity.h"

class IEquipable {
public:
	IEquipable();
	virtual ~IEquipable();

	virtual UITextureElement& GetUITextureElement() = 0;
	virtual Entity& GetEntity() = 0;

};

#endif /* _IEQUIPABLE_H_ */
