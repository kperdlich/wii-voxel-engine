/*
 * Logo.h
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_COMPONENTS_LOGO_H_
#define SRC_GUI_COMPONENTS_LOGO_H_

#include "UITextureElement.h"


class Logo: public UITextureElement {
public:
	Logo(const char* name, BasicTexture* tex);
	virtual ~Logo();
	void load();
	void unload();

	void setColor(u32 color);
	u32 getColor();

};

#endif /* SRC_GUI_COMPONENTS_LOGO_H_ */
