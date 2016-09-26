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

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../core/grrlib.h"
#include "BasicTexture.h"


class Texture : public BasicTexture
{

protected:
	const unsigned char* m_TextureBytes = NULL;
	GRRLIB_texImg* m_Texture = NULL;
	bool m_TextureLoaded;

public:
	Texture( float x, float y, const unsigned char* texture, const u16 id );
	virtual ~Texture();

	virtual txTypes GetTextureType() const override;

	GRRLIB_texImg* GetNativeTexture() const;

	virtual void LoadTexture() override;
	virtual void UnloadTexture() override;

	virtual uint GetWidth() const override;
	virtual uint GetHeight() const override;

	bool isLoaded() const;
	virtual bool IsVisible() const override;
};


#endif /* _TEXTURE_H_ */
