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

#ifndef _LABEL_H_
#define _LABEL_H_

#include "../core/grrlib.h"
#include "IDrawable.h"
#include "ISprite.h"
#include <string>

class Label : public IDrawable, public ISprite {
private:
    Label( const std::string& text, float x, float y, GRRLIB_ttfFont* font, uint32_t fontSize, uint32_t color);

public:
    ~Label();
    static Label* Create(std::string text, GRRLIB_ttfFont* font, std::string searchName, uint16_t sortingLayer = 0);

    void Render() const override;

    float GetX() const override
    {
        return m_x;
    }

    void SetX(float x) override
    {
        m_x = x;
    }

    float GetY() const override
    {
        return m_y;
    }

    void SetY(float y) override
    {
        m_y = y;
    }

    GRRLIB_ttfFont& GetFont() const
    {
        return *m_font;
    }

    const std::string& GetText() const
    {
        return m_text;
    }

    uint32_t GetFontSize() const
    {
        return m_fontSize;
    }

    uint32_t GetTextColor() const
    {
        return m_textColor;
    }

    void SetFontSize(uint32_t fontSize)
    {
        m_fontSize = fontSize;
    }

    void SetTextColor(u32 textColor)
    {
        m_textColor = textColor;
    }

    void SetSortingLayerIndex(uint16_t index) override
    {
        m_sortingLayerIndex = index;
    }

    uint16_t GetSortingLayerIndex() const override
    {
        return m_sortingLayerIndex;
    }

    const std::string& GetName() const override
    {
        return m_name;
    }

    void SetName(const std::string& name) override
    {
        m_name = name;
    }

    bool IsVisible() const override
    {
        return true;
    }

    void SetVisible(bool value) override
    {

    }

    ESpriteType GetType() const override
    {
        return ESpriteType::LABEL;
    }

protected:
    std::string m_text;
    std::string m_name;
    uint16_t m_sortingLayerIndex = 0;
	GRRLIB_ttfFont* m_font;
    uint32_t m_fontSize = 0;
    uint32_t m_textColor = 0;
    float m_x, m_y;
};

#endif /* _LABEL_H_ */
