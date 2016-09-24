/*
 * SpriteSheet.h
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

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
	virtual txTypes GetTextureType() const override;
};

#endif /* _SPRITESHEET_H_ */
