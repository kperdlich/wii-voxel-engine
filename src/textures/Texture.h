/*
 * Texture.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../core/grrlib.h"
#include "BasicTexture.h"


class Texture : public BasicTexture
{

protected:
	const unsigned char* m_TextureBytes;
	GRRLIB_texImg* m_Texture;
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
