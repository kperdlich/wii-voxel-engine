/*
 * ClassicBackground.h
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#ifndef _CLASSICBACKGROUND_H_
#define _CLASSICBACKGROUND_H_

#include "UITextureElement.h"
#include "../textures/BasicTexture.h"
#include "../textures/TextureHandler.h"

class ClassicBackground: public UITextureElement {
public:
	ClassicBackground(const char* name, BasicTexture* tex);
	virtual ~ClassicBackground();
	void Load();
	void Unload();
};

#endif /* _CLASSICBACKGROUND_H_ */
