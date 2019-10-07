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

#pragma once

#include <functional>

#include "UiTextureElement.h"
#include "../textures/Texture.h"
#include "../textures/Label.h"

class BasicButton: public UiTextureElement
{
public:
    using ButtonCallback = std::function<void(BasicButton*)>;

    BasicButton(float x, float y, const char* name, Sprite* defaultTexture,
                 Sprite* highlightTexture, Label* label, ButtonCallback clickCallback);
    BasicButton(const BasicButton&) = delete;
    BasicButton(BasicButton&&) = delete;
    void operator=(const BasicButton&) = delete;
    void operator=(BasicButton&&) = delete;
    virtual ~BasicButton();

	void Update();
    bool MouseOver();
    void CheckForClick();
	void UpdateLabel();

	void SetColor(u32 color);
    void SetButtonCallback(ButtonCallback callback);

    virtual void SetX(uint32_t x) override;
    virtual void SetY(uint32_t y) override;


private:
    Sprite* m_highlightTexture = nullptr;
    Label* m_label = nullptr;
    ButtonCallback m_clickCallback;
    bool m_mouseOver = false;
};
