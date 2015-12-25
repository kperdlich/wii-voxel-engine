/*
 * CHotbar.h
 *
 *  Created on: 09.07.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_WORLD_HUD_CHOTBAR_H_
#define SRC_GUI_WORLD_HUD_CHOTBAR_H_

#include "../../components/UITextureElement.h"
#include "../../BasicTexture.h"

class CHotbar: public UITextureElement {
public:
	CHotbar( const char* name, BasicTexture* tex );
	virtual ~CHotbar();

	void setColor(u32 color);
	u32 getColor();
};

#endif /* SRC_GUI_WORLD_HUD_CHOTBAR_H_ */
