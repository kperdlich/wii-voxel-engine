/*
 * SpriteSheet.h
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_SPRITESHEET_H_
#define SRC_GUI_SPRITESHEET_H_

#include "Texture.h"
#include "Tile.h"
#include <vector>

class Tile;

class SpriteSheet: public Texture {

public:
	SpriteSheet( const unsigned char* texture, const u16 id );
	virtual ~SpriteSheet();
	void loadTexture();
	void unloadTexture();
	Tile* createTile( float x, float y, int index, const u16 id);
	txTypes getTextureType();
};

#endif /* SRC_GUI_SPRITESHEET_H_ */
