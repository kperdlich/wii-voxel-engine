/*
 * Player.h
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"
#include "../world/Camera.h"
#include "../utils/Vector3f.h"
#include "CPlayerInventory.h"
#include "IEquipable.h"

class Player: public Entity {
public:
	Player();
	virtual ~Player();
	void Update();

	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();

	void AddToInventory(IEquipable& item);

	void Rotate( Vector3f rotation );

private:
	CPlayerInventory* m_inventory;
};

#endif /* _PLAYER_H_ */
