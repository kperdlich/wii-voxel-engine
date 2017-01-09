/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#ifndef _UITEXTUREELEMENT_H_
#define _UITEXTUREELEMENT_H_

#include "UIElement.h"
#include "../textures/BasicTexture.h"

class UITextureElement: public UIElement {
public:
    UITextureElement(uint32_t x, uint32_t y, const char* name, BasicTexture* tex);
	UITextureElement(const char* name, BasicTexture* tex);
	virtual ~UITextureElement();
	void Load() override;

    virtual void SetColor(uint32_t color);
    virtual uint32_t GetColor() const;

    virtual void SetX(uint32_t x) override;
    virtual void SetY(uint32_t y) override;

protected:
	BasicTexture* m_texture;
};

#endif /* _UITEXTUREELEMENT_H_ */
