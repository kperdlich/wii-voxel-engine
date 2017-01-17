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

#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include "Texture.h"
#include <vector>

class SpriteSheet: public Texture {

public:
	SpriteSheet( const unsigned char* texture, const u16 id );
	virtual ~SpriteSheet();
	virtual void LoadTexture() override;
	virtual void UnloadTexture() override;
	virtual ETextureType GetTextureType() const override;
};

#endif /* _SPRITESHEET_H_ */
