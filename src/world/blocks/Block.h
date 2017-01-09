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

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../../textures/Texture.h"

class Block {
public:
    Block();
    Block( float size, const Texture* pTexture );
    virtual ~Block();
	float GetSize() const;
	const Texture* GetTexture() const;

protected:
	float m_size; // the size from the middle point to each axis
	const Texture* m_pTexture;

};

#endif /* _BLOCK_H_ */
