/*
 * UITextureElement.h
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_COMPONENTS_UITEXTUREELEMENT_H_
#define SRC_GUI_COMPONENTS_UITEXTUREELEMENT_H_

#include "UIElement.h"
#include "../BasicTexture.h"

class UITextureElement: public UIElement {
public:
	UITextureElement(int x, int y, float width, float height, const char* name, BasicTexture* tex);
	virtual ~UITextureElement();
	void load();
	void unload();

	virtual void setColor(u32 color) = 0;
	virtual u32 getColor() = 0;

	void setX(int x);
	void setY(int y);

protected:
	BasicTexture* m_texture;
};

#endif /* SRC_GUI_COMPONENTS_UITEXTUREELEMENT_H_ */
