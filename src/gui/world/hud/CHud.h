/*
 * CHud.h
 *
 *  Created on: 09.07.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_WORLD_HUD_CHUD_H_
#define SRC_GUI_WORLD_HUD_CHUD_H_

#include <vector>
#include "../../components/UITextureElement.h"
#include "CHotbar.h"

class CHud {
public:
	CHud();
	virtual ~CHud();
	void addComponent( UITextureElement* component );

protected:
	std::vector<UITextureElement*> m_hudComponents;

};

#endif /* SRC_GUI_WORLD_HUD_CHUD_H_ */
