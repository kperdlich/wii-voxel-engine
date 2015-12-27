/*
 * TextureHandler.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_TEXTUREHANDLER_H_
#define SRC_GUI_TEXTUREHANDLER_H_

#include <grrlib.h>
#include <vector>
#include "../gui/Texture.h"
#include "../gui/SpriteSheet.h"
#include "../gui/LabelTexture.h"

class TextureHandler {

private:
	std::vector<BasicTexture*> m_Textures;

public:
	TextureHandler();
	~TextureHandler();
	Texture* createTexture( const u8* textureName);
	SpriteSheet* createTilemap( const u8* textureName );
	Tile* createTile(int x, int y, int index, SpriteSheet* spriteSheet);
	LabelTexture* createLabel( int x, int y, const char* text, GRRLIB_ttfFont* font, uint fontSize, u32 color );
	LabelTexture* createLabel( const char* text, GRRLIB_ttfFont* font );
	BasicTexture* getTextureByID( u16 index );
	void destroyTextureByID( u16 index );
	void destroyAllTextures();
	std::vector<BasicTexture*>* getTextures();
protected:
	u16 getNewIndex();

};



#endif /* SRC_GUI_TEXTUREHANDLER_H_ */
