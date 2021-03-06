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

#include "scenes/Scene.h"
#include "components/UiElement.h"
#include "entity/EntityHandler.h"
#include "world/Camera.h"
#include "world/GameWorld.h"
#include "world/SkyBox.h"

class Basic3DScene : public Scene {
public:
	Basic3DScene();
	Basic3DScene(const Basic3DScene&) = delete;
	Basic3DScene(Basic3DScene&&) = delete;
	void operator=(const Basic3DScene&) = delete;
	void operator=(Basic3DScene&&) = delete;
	virtual ~Basic3DScene();
	virtual void Load() override;
	virtual void Unload() override;

	virtual void Draw() override;
	virtual void Update(float deltaSeconds) override;

	inline const class Camera* GetCamera() const
	{
		return m_mainCamera;
	}

	inline class GameWorld* GetWorld() const
	{
		return m_pGameWorld;
	}

	class EntityHandler& GetEntityHandler();

protected:
	void Render2D() const;
	void ClearUiElements();

	std::vector<UiElement*> m_uiElements;
	class EntityHandler* m_entityHandler = nullptr;
	class Camera* m_mainCamera = nullptr;
	class GameWorld* m_pGameWorld = nullptr;
	class SkyBox* m_skyBox = nullptr;
};
