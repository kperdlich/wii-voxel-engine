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

#include "renderer/SpriteStageManager.h"

class Scene {

public:
    Scene();
    virtual ~Scene();
    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;
    void operator=(const Scene&) = delete;
    void operator=(Scene&&) = delete;
	virtual void Load();
	virtual void Unload();
	virtual void Draw();
    virtual void Update(float deltaSeconds);
	virtual SpriteStageManager& GetSpriteStageManager() const;	

    bool IsLoaded() const
    {
        return m_bLoaded;
    }

protected:
    bool m_bLoaded = false;

protected:
    SpriteStageManager *m_spriteStageManager;

};
