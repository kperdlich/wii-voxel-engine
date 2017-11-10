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

#ifndef _SCENE_H_
#define _SCENE_H_

#include "../renderer/SpriteStageManager.h"
#include "../renderer/Renderer.h"

class Scene {

public:
    Scene();
    virtual ~Scene();
	virtual void Load();
	virtual void Unload();
	virtual void Draw();
    virtual void Update(float deltaSeconds);
	virtual SpriteStageManager& GetSpriteStageManager() const;
	virtual Renderer& GetRenderer() const;

protected:
    SpriteStageManager *m_spriteStageManager;
    Renderer *m_renderer;
};



#endif /* _SCENE_H_ */
