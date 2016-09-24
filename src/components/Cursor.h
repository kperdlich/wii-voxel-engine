/*
 * Cursor.h
 *
 *  Created on: 28.06.2015
 *      Author: Kevin
 */

#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "UITextureElement.h"

class Cursor: public UITextureElement {
public:
	Cursor( const char* name, BasicTexture* tex );
	virtual ~Cursor();
	void Update();
};

#endif /* _CURSOR_H_ */
