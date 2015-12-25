/*
 * ClassicBackground.h
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_COMPONENTS_CLASSICBACKGROUND_H_
#define SRC_GUI_COMPONENTS_CLASSICBACKGROUND_H_

#include "UITextureElement.h"
#include "../BasicTexture.h"
#include "../../handler/TextureHandler.h"

class ClassicBackground: public UITextureElement {
public:
	ClassicBackground(const char* name, BasicTexture* tex);
	virtual ~ClassicBackground();
	void load();
	void unload();

	void setColor(u32 color);
	u32 getColor();

};

#endif /* SRC_GUI_COMPONENTS_CLASSICBACKGROUND_H_ */
