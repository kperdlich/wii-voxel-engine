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

#include "BasicScene.h"
#include "../renderer/Renderer3D.h"
#include "../components/UIElement.h"
#include "../entity/EntityHandler.h"
#include "../world/Camera.h"
#include "../world/GameWorld.h"
#include "../world/CSkyBox.h"

class Basic3DScene: public BasicScene {
public:
	Basic3DScene();
	virtual ~Basic3DScene();
	virtual void Load();
	virtual void Unload();

	virtual void Draw();
	virtual void Update();

	class EntityHandler& GetEntityHandler();

	void SetGraphicsMode(bool textureMode, bool normalMode);

protected:
	class Renderer3D& Get3DRenderer();
	class EntityHandler* m_entityHandler;
	std::vector<UIElement*> m_uiElements;
	class Camera* m_mainCamera;
	class CGameWorld* m_pGameWorld;
	class CSkyBox* m_pSkyBox;
};

#endif /* _BASIC3DSCENE_H_ */
