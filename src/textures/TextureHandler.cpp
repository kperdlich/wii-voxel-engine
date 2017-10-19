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


#include <functional>
#include <algorithm>
#include "TextureHandler.h"
#include "../utils/Debug.h"


void TextureHandler::DestroySpriteByName(const char *searchName)
{
    auto spriteAtlasIt = m_spriteAtlas.find( searchName );
    if ( spriteAtlasIt != m_spriteAtlas.end() )
    {
        spriteAtlasIt->second->Unload();
        delete spriteAtlasIt->second;
        m_spriteAtlas.erase(searchName);
    }
}

void TextureHandler::DestroyTextureByName( const char* searchName )
{
    auto textureAtlasIt = m_textureAtlas.find( searchName );
    if ( textureAtlasIt != m_textureAtlas.end() )
	{
        textureAtlasIt->second->Unload();
        delete textureAtlasIt->second;
        m_textureAtlas.erase(searchName);
	}
}


void TextureHandler::DestroyAllTextures()
{
    if ( m_textureAtlas.empty())
        return;

    for ( auto it = m_textureAtlas.begin(); it != m_textureAtlas.end(); it++)
    {
        it->second->Unload();
        delete it->second;
    }

    m_textureAtlas.clear();   
}

void TextureHandler::DestroyAllSprites()
{
    if ( m_spriteAtlas.empty())
        return;

    for ( auto it = m_spriteAtlas.begin(); it != m_spriteAtlas.end(); it++)
    {
        it->second->Unload();
        delete it->second;
    }

    m_spriteAtlas.clear();
}

void TextureHandler::DestroyAll()
{
    DestroyAllTextures();
    DestroyAllSprites();
}


Texture* TextureHandler::CreateTexture(const uint8_t* pTextureData, uint32_t textureSize, const char* pSearchName)
{    
    if ( FindTexture(pSearchName))
	{
        return nullptr;
	}

    TextureLoadingData textureData = { pTextureData, textureSize };
    Texture* tex = new Texture( 0, 0, textureData, GetNewTextureIndex() );
    tex->Load();
    m_textureAtlas.insert(std::make_pair(pSearchName, tex));
    return tex;
}

Sprite* TextureHandler::CreateSprite(const uint8_t *pSpriteData, uint32_t spriteSize, const char *pSearchName, uint16_t sortingLayer)
{
    if ( FindSprite(pSearchName))
    {
        return nullptr;
    }

    TextureLoadingData textureData = { pSpriteData, spriteSize };
    auto sprite = new Sprite( 0, 0, textureData, GetNewSpriteIndex() );
    sprite->SetSortingLayerIndex(sortingLayer);
    sprite->Load();
    m_spriteAtlas.emplace(pSearchName, sprite);
    return sprite;
}


u16 TextureHandler::GetNewTextureIndex()
{
    return ++m_textureIndex;
}

u16 TextureHandler::GetNewSpriteIndex()
{
     return ++m_spriteIndex;
}

Label* TextureHandler::CreateLabel(int x, int y, const char* text,
        GRRLIB_ttfFont* font, uint32_t fontSize, u32 color, const char* searchName)
{
    if ( FindSprite(searchName))
	{
        return nullptr;
	}

    Label* label = new Label( text, x, y, {nullptr, 0}, GetNewSpriteIndex(), font, fontSize, color );
    label->Load();
    m_spriteAtlas.insert(std::make_pair(searchName, label));
	return label;
}

Label* TextureHandler::CreateLabel( const char* text, GRRLIB_ttfFont* font, const char* searchName )
{
    return CreateLabel(0, 0, text, font, DEFAULT_FONT_SIZE, GRRLIB_WHITE, searchName);
}

bool TextureHandler::FindTexture(std::string key) const
{
    auto textureAtlasIt = m_textureAtlas.find(key);
    return textureAtlasIt != m_textureAtlas.end();
}

bool TextureHandler::FindSprite(std::string key) const
{
    auto spriteAtlasIt = m_spriteAtlas.find(key);
    return spriteAtlasIt != m_spriteAtlas.end();
}

const Sprite *TextureHandler::GetSprite(std::string key) const
{
    auto spriteAtlasIt = m_spriteAtlas.find(key);
    if (spriteAtlasIt != m_spriteAtlas.end())
    {
       return (spriteAtlasIt->second);
    }

    return nullptr;
}

std::vector<const Sprite*> TextureHandler::GetSpriteRenderList()
{
    std::vector<const Sprite*> sprites;
    for ( auto it = m_spriteAtlas.begin(); it != m_spriteAtlas.end(); it++)
    {
        Sprite* pSprite = it->second;
        if (pSprite->IsVisible())
        {
            sprites.push_back(pSprite);
        }
    }

    // todo fix z-sorting
    std::sort(sprites.begin(), sprites.end());
    return sprites;
}

const Texture* TextureHandler::GetTexture(std::string key) const
{
     auto textureAtlasIt = m_textureAtlas.find(key);
     if (textureAtlasIt != m_textureAtlas.end())
     {
        return (textureAtlasIt->second);
     }

     return nullptr;    
}
