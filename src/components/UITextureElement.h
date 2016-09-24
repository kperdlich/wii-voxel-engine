/*
 * UITextureElement.h
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#ifndef _UITEXTUREELEMENT_H_
#define _UITEXTUREELEMENT_H_

#include "UIElement.h"
#include "../textures/BasicTexture.h"

class UITextureElement: public UIElement {
public:
	UITextureElement(int x, int y, const char* name, BasicTexture* tex);
	UITextureElement(const char* name, BasicTexture* tex);
	virtual ~UITextureElement();
	void Load() override;

	virtual void SetColor(u32 color);
	virtual u32 GetColor() const;

	virtual void SetX(int x) override;
	virtual void SetY(int y) override;

protected:
	BasicTexture* m_texture;
};

#endif /* _UITEXTUREELEMENT_H_ */
