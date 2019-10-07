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

#pragma once

#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include "core/grrlib.h"
#include "textures/ISprite.h"

class SpriteStageManager {

private:

    std::vector<const ISprite*> m_spriteRenderCash;
    bool m_spriteCashDirty = true;
    std::unordered_map<std::string, ISprite*> m_spriteAtlas;

public:
    SpriteStageManager() {}
    ~SpriteStageManager() {}
    SpriteStageManager(const SpriteStageManager&) = delete;
    SpriteStageManager(SpriteStageManager&&) = delete;
    void operator=(const SpriteStageManager&) = delete;
    void operator=(SpriteStageManager&&) = delete;

    void Clear();    
    bool FindSprite(const std::string& name) const;

    ISprite* Add(ISprite* sprite);
    bool Remove(const ISprite& sprite);

    const ISprite* GetSprite(const std::string& key) const;

    std::vector<const ISprite*>& GetSpriteRenderList();

    uint32_t SpriteCount() const
    {
        return m_spriteAtlas.size();
    }

    void SetSpriteCashDirty(bool value)
    {
        m_spriteCashDirty = value;
    }   
};
