/*
 * TextureHandler.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

#ifndef _TEXTUREHANDLER_H_
#define _TEXTUREHANDLER_H_

#include "../core/grrlib.h"
#include <map>
#include <vector>
#include <string>
#include "../textures/Texture.h"
#include "../textures/SpriteSheet.h"
#include "../textures/LabelTexture.h"

class TextureHandler {

private:
	std::vector<BasicTexture*> m_textures;
	std::map<std::string, std::vector<BasicTexture*>::iterator> m_textureMap;

public:
	TextureHandler();
	~TextureHandler();
	Texture* CreateTexture( const u8* textureName, const char* searchName );
	LabelTexture* CreateLabel( int x, int y, const char* text, GRRLIB_ttfFont* font, uint fontSize, u32 color, const char* searchName );
	LabelTexture* CreateLabel( const char* text, GRRLIB_ttfFont* font, const char* searchName );
	BasicTexture* GetTextureByID( u16 index );
	void DestroyTextureByName( const char* searchName );
	void DestroyAllTextures();
	const std::vector<BasicTexture*>* GetTextures() const;
	bool FindTexture(std::string key) const;
	const BasicTexture* GetTexture(std::string key) const;
	unsigned int TextureCount() const;
protected:
	u16 GetNewIndex() const;

};



#endif /* _TEXTUREHANDLER_H_ */
