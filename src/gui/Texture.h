/*
 * Texture.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_TEXTURE_H_
#define SRC_GUI_TEXTURE_H_

#include "grrlib.h"
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

	virtual txTypes getTextureType();

	GRRLIB_texImg* getNativeTexture();

	virtual void loadTexture() override;
	virtual void unloadTexture() override;

	uint getWidth();
	uint getHeight();

	bool isLoaded();
	bool isVisible() override;
};


#endif /* SRC_GUI_TEXTURE_H_ */
