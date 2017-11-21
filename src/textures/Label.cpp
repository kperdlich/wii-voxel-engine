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

#include "Label.h"
#include "../Engine.h"

Label::Label(const std::string& text, float x, float y, GRRLIB_ttfFont* font, uint32_t fontSize, uint32_t color )
    : m_x(x), m_y(y), m_text( text ), m_font( font ), m_fontSize( fontSize ), m_textColor( color )
{
}

Label::~Label() { }

Label *Label::Create(std::string text, GRRLIB_ttfFont *font, std::string searchName, uint16_t sortingLayer)
{
    Label* label = new Label( text, 0, 0, font, DEFAULT_FONT_SIZE, GRRLIB_WHITE );
    label->SetName(searchName);
    label->SetSortingLayerIndex(sortingLayer);    
    Engine::Get().GetSpriteStageManager().Add(label);
    return label;
}


