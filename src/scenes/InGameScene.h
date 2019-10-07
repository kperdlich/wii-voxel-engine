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

#include "Basic3DScene.h"
#include "../event/eventlistener.h"
#include "../components/worldloader.h"


class InGameScene: public Basic3DScene, public IEventListener {
public:
    InGameScene();   
    virtual ~InGameScene();
    void Update(float deltaSeconds) override;
	void Load() override;
    void Unload() override;
	void Draw() override;
    virtual void OnEvent(Event event) override;    

protected:
	void InitEntities();
    WorldLoader* m_pWorldLoader;
};
