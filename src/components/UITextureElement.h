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

#include "UiElement.h"
#include "../textures/Sprite.h"

class UiTextureElement: public UiElement {
public:
    UiTextureElement(uint32_t x, uint32_t y, const char* name, Sprite* tex);
    UiTextureElement(const char* name, Sprite* tex);
    virtual ~UiTextureElement();
	void Load() override;

    virtual void SetColor(uint32_t color);
    virtual uint32_t GetColor() const;

    virtual void SetX(uint32_t x) override;
    virtual void SetY(uint32_t y) override;

protected:
        Sprite* m_texture;
};

#endif /* _UITEXTUREELEMENT_H_ */
