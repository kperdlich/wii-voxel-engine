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


void SpriteStageManager::Clear()
{
    m_spriteAtlas.clear();
    m_spriteRenderCash.clear();
    m_spriteCashDirty = true;
}


bool SpriteStageManager::FindSprite(const std::string& name ) const
{
    auto spriteAtlasIt = m_spriteAtlas.find(name);
    return spriteAtlasIt != m_spriteAtlas.end();
}


ISprite* SpriteStageManager::Add(ISprite *sprite)
{
    m_spriteAtlas.insert(std::make_pair(sprite->GetName(), sprite));
    return sprite;
}

bool SpriteStageManager::Remove(const ISprite& sprite)
{
    auto spriteAtlasIt = m_spriteAtlas.find(sprite.GetName());
    if (spriteAtlasIt != m_spriteAtlas.end())
    {
        m_spriteAtlas.erase(sprite.GetName());
        m_spriteCashDirty = true;
        return true;
    }

    return false;
}

const ISprite* SpriteStageManager::GetSprite(const std::string& key) const
{
    auto spriteAtlasIt = m_spriteAtlas.find(key);
    if (spriteAtlasIt != m_spriteAtlas.end())
    {
       return (spriteAtlasIt->second);
    }

    return nullptr;
}

std::vector<const ISprite*>& SpriteStageManager::GetSpriteRenderList()
{
    if ( m_spriteCashDirty )
    {
        m_spriteRenderCash.clear();
        for ( auto it = m_spriteAtlas.begin(); it != m_spriteAtlas.end(); it++)
        {
            ISprite* sprite = it->second;
            if (sprite->IsVisible())
            {
                m_spriteRenderCash.push_back(sprite);
            }
        }

        std::sort(m_spriteRenderCash.begin(), m_spriteRenderCash.end(), [](const ISprite* a, const ISprite* b) { return a->GetSortingLayerIndex() < b->GetSortingLayerIndex(); });
        m_spriteCashDirty = false;
    }

    return m_spriteRenderCash;
}
