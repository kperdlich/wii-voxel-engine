/*
 * CPlayerInventoryHud.h
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#ifndef SRC_GUI_WORLD_HUD_CPLAYERINVENTORYHUD_H_
#define SRC_GUI_WORLD_HUD_CPLAYERINVENTORYHUD_H_

#include "IHudComponent.h"

class CPlayerInventoryHud: public IHudComponent {
public:
	CPlayerInventoryHud();
	virtual ~CPlayerInventoryHud();

	void Update();


};

#endif /* SRC_GUI_WORLD_HUD_CPLAYERINVENTORYHUD_H_ */
