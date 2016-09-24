/*
 * CHotbar.h
 *
 *  Created on: 09.07.2015
 *      Author: Kevin
 */

#ifndef _CHOTBAR_H_
#define _CHOTBAR_H_

#include "../../components/UITextureElement.h"
#include "../../textures/BasicTexture.h"

class CHotbar: public UITextureElement {
public:
	CHotbar( const char* name, BasicTexture* tex );
	virtual ~CHotbar();
};

#endif /* _CHOTBAR_H_ */
