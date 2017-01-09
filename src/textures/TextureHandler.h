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
    Texture* CreateTexture( const uint8_t* textureName, const char* searchName, bool visible );
    Texture* CreateTexture( const uint8_t* textureName, const char* searchName );
    LabelTexture* CreateLabel( int x, int y, const char* text, GRRLIB_ttfFont* font, uint32_t fontSize, uint32_t color, const char* searchName );
	LabelTexture* CreateLabel( const char* text, GRRLIB_ttfFont* font, const char* searchName );
    BasicTexture* GetTextureByID( uint16_t index );
	void DestroyTextureByName( const char* searchName );
	void DestroyAllTextures();
	const std::vector<BasicTexture*>* GetTextures() const;
	bool FindTexture(std::string key) const;
	const BasicTexture* GetTexture(std::string key) const;
	uint32_t TextureCount() const;
protected:
	u16 GetNewIndex() const;

};



#endif /* _TEXTUREHANDLER_H_ */
