/*
 * TextureHandler.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_TEXTUREHANDLER_H_
#define SRC_GUI_TEXTUREHANDLER_H_

#include "../core/grrlib.h"
#include <map>
#include <vector>
#include <string>
#include "../gui/Texture.h"
#include "../gui/SpriteSheet.h"
#include "../gui/LabelTexture.h"

class TextureHandler {

private:
	std::vector<BasicTexture*> m_textures;
	std::map<std::string, std::vector<BasicTexture*>::iterator> m_textureMap;

public:
	TextureHandler();
	~TextureHandler();
	Texture* createTexture( const u8* textureName, const char* searchName );
	/*SpriteSheet* createTilemap( const u8* textureName );
	Tile* createTile(int x, int y, int index, SpriteSheet* spriteSheet);*/
	LabelTexture* createLabel( int x, int y, const char* text, GRRLIB_ttfFont* font, uint fontSize, u32 color, const char* searchName );
	LabelTexture* createLabel( const char* text, GRRLIB_ttfFont* font, const char* searchName );
	BasicTexture* getTextureByID( u16 index );
	//void destroyTextureByID( u16 index );
	void destroyTextureByName( const char* searchName );
	void destroyAllTextures();
	std::vector<BasicTexture*>* getTextures();
	bool FindTexture(std::string key);
	BasicTexture* GetTexture(std::string key);
	unsigned int TextureCount();
protected:
	u16 getNewIndex();

};



#endif /* SRC_GUI_TEXTUREHANDLER_H_ */
