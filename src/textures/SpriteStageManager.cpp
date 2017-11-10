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
#include "SpriteStageManager.h"
#include "../utils/Debug.h"


bool SpriteStageManager::DestroySpriteByName(const char *searchName)
{
    auto spriteAtlasIt = m_spriteAtlas.find( searchName );
    if ( spriteAtlasIt != m_spriteAtlas.end() )
    {
        spriteAtlasIt->second->Unload();
        delete spriteAtlasIt->second;
        m_spriteAtlas.erase(searchName);
        return true;
    }
    return false;
}


void SpriteStageManager::DestroyAllSprites()
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

void SpriteStageManager::DestroyAll()
{
    DestroyAllSprites();
}


Sprite* SpriteStageManager::CreateSprite(const uint8_t *pSpriteData, uint32_t spriteSize, const char *pSearchName, uint16_t sortingLayer)
{
    TextureLoadingData textureData = { pSpriteData, spriteSize };
    auto sprite = new Sprite( 0, 0, textureData );
    sprite->SetSortingLayerIndex(sortingLayer);
    sprite->Load();
    m_spriteAtlas.insert(std::make_pair(pSearchName, sprite));
    return sprite;
}


Label* SpriteStageManager::CreateLabel(int x, int y, const char* text,
        GRRLIB_ttfFont* font, uint32_t fontSize, u32 color, const char* searchName, uint16_t sortingLayer)
{


    Label* label = new Label( text, x, y, {nullptr, 0}, font, fontSize, color );
    label->Load();
    label->SetSortingLayerIndex(sortingLayer);
    m_spriteAtlas.insert(std::make_pair(searchName, label));
	return label;
}

Label* SpriteStageManager::CreateLabel( const char* text, GRRLIB_ttfFont* font, const char* searchName, uint16_t sortingLayer )
{
    return CreateLabel(0, 0, text, font, DEFAULT_FONT_SIZE, GRRLIB_WHITE, searchName, sortingLayer);
}


bool SpriteStageManager::FindSprite(std::string key) const
{
    auto spriteAtlasIt = m_spriteAtlas.find(key);
    return spriteAtlasIt != m_spriteAtlas.end();
}

const Sprite *SpriteStageManager::GetSprite(std::string key) const
{
    auto spriteAtlasIt = m_spriteAtlas.find(key);
    if (spriteAtlasIt != m_spriteAtlas.end())
    {
       return (spriteAtlasIt->second);
    }

    return nullptr;
}

std::vector<const Sprite*> SpriteStageManager::GetSpriteRenderList()
{
    if ( m_spriteCashDirty )
    {
        m_spriteRenderCash.clear();
        for ( auto it = m_spriteAtlas.begin(); it != m_spriteAtlas.end(); it++)
        {
            Sprite* pSprite = it->second;
            if (pSprite->IsVisible())
            {
                m_spriteRenderCash.push_back(pSprite);
            }
        }

        std::sort(m_spriteRenderCash.begin(), m_spriteRenderCash.end(), [](const Sprite* a, const Sprite* b) { return a->GetSortingLayerIndex() < b->GetSortingLayerIndex(); });
        m_spriteCashDirty = false;
    }

    return m_spriteRenderCash;
}
