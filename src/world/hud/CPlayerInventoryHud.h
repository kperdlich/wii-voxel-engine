/*
 * CPlayerInventoryHud.h
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#ifndef _CPLAYERINVENTORYHUD_H_
#define _CPLAYERINVENTORYHUD_H_

#include "IHudComponent.h"

class CPlayerInventoryHud: public IHudComponent {
public:
	CPlayerInventoryHud();
	virtual ~CPlayerInventoryHud();

	void Update();


};

#endif /* _CPLAYERINVENTORYHUD_H_ */
