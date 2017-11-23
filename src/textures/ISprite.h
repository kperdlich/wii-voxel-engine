/***
 *
 * Copyright (C) 2017 DaeFennek
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

#ifndef ISPRITE_H
#define ISPRITE_H

#include "IDrawable.h"
#include <string>


enum class ESpriteType {
    SPRITE  = 0,
    LABEL   = 1
};

class ISprite
{
public:

    virtual bool IsVisible() const = 0;
    virtual void SetVisible(bool value) = 0;

    virtual void Render() const = 0;

    virtual void SetSortingLayerIndex(uint16_t index) = 0;
    virtual uint16_t GetSortingLayerIndex() const = 0;

    virtual const std::string& GetName() const = 0;
    virtual void SetName(const std::string& name) = 0;

    virtual ESpriteType GetType() const = 0;
};

#endif // ISPRITE_H
