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

#ifndef _INGAMESCENE_H_
#define _INGAMESCENE_H_

#include "Basic3DScene.h"

class InGameScene: public Basic3DScene {
public:
    InGameScene();
    virtual ~InGameScene();
    void Update(float deltaSeconds) override;
	void Load() override;
    void Unload() override;
	void Draw() override;

    inline class GameWorld* GetWorld() const
    {
        return m_pGameWorld;
    }

protected:
	void InitEntities();

};

#endif /* _INGAMESCENE_H_ */
