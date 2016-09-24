/*
 * Logo.h
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#ifndef _LOGO_H_
#define _LOGO_H_

#include "UITextureElement.h"


class Logo: public UITextureElement {
public:
	Logo(const char* name, BasicTexture* tex);
	virtual ~Logo();
	void Load();
	void Unload();
};

#endif /* _LOGO_H_ */
