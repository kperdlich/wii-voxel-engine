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

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"
#include "../world/Camera.h"
#include "../utils/Vector3.h"
#include "PlayerInventory.h"
#include "IEquipable.h"

class CPlayer: public Entity {
public:
    CPlayer();
    virtual ~CPlayer();
    void Update(float deltaSeconds);
	void AddToInventory(IEquipable& item);
    void Move(float x, float y, float deltaTime);
	void Rotate( const Vector3& rotation );

private:
	void UpdateInventory();

private:
    PlayerInventory* m_pInventory;


};

#endif /* _PLAYER_H_ */
