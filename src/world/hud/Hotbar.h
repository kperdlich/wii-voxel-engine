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

#ifndef _CHOTBAR_H_
#define _CHOTBAR_H_

#include "../../components/UiTextureElement.h"
#include "../../textures/BasicTexture.h"

class Hotbar: public UiTextureElement {
public:
    Hotbar( const char* name, BasicTexture* tex );
    virtual ~Hotbar();
};

#endif /* _CHOTBAR_H_ */
