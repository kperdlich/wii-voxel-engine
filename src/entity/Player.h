/*
 * Player.h
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_PLAYER_H_
#define SRC_ENTITY_PLAYER_H_

#include "Entity.h"
#include "../gui/world/Camera.h"
#include "../utils/Vector3f.h"
#include "CPlayerInventory.h"
#include "IEquipable.h"

class Player: public Entity {
public:
	Player();
	virtual ~Player();
	void update();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();

	void AddToInventory(IEquipable& item);

	void rotate( Vector3f rotation );

private:
	CPlayerInventory* m_inventory;
};

#endif /* SRC_ENTITY_PLAYER_H_ */
