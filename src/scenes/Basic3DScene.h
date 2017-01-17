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

#ifndef _BASIC3DSCENE_H_
#define _BASIC3DSCENE_H_

#include "Scene.h"
#include "../renderer/Renderer3D.h"
#include "../components/UiElement.h"
#include "../entity/EntityHandler.h"
#include "../world/Camera.h"
#include "../world/GameWorld.h"
#include "../world/SkyBox.h"

class Basic3DScene: public Scene {
public:
    Basic3DScene();
    virtual ~Basic3DScene();
    virtual void Load() override;
    virtual void Unload() override;

    virtual void Draw() override;
    virtual void Update(float deltaSeconds) override;

	class EntityHandler& GetEntityHandler();



protected:
	class Renderer3D& Get3DRenderer();
	class EntityHandler* m_entityHandler;
	std::vector<UiElement*> m_uiElements;
	class Camera* m_mainCamera;
    class GameWorld* m_pGameWorld;
	class SkyBox* m_pSkyBox;
};

#endif /* _BASIC3DSCENE_H_ */
