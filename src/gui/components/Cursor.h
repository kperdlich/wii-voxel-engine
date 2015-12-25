/*
 * Cursor.h
 *
 *  Created on: 28.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_COMPONENTS_CURSOR_H_
#define SRC_GUI_COMPONENTS_CURSOR_H_

#include "UITextureElement.h"

class Cursor: public UITextureElement {
public:
	Cursor( const char* name, BasicTexture* tex );
	virtual ~Cursor();
	void update();

	void setColor(u32 color);
	u32 getColor();
};

#endif /* SRC_GUI_COMPONENTS_CURSOR_H_ */
