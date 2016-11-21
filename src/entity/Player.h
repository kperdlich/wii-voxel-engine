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
#include "CPlayerInventory.h"
#include "IEquipable.h"

class Player: public Entity {
public:
	Player();
	virtual ~Player();
	void Update();
	void AddToInventory(IEquipable& item);
	void Move(float x, float y);
	void Rotate( const Vector3& rotation );

private:
	CPlayerInventory* m_inventory;
};

#endif /* _PLAYER_H_ */
