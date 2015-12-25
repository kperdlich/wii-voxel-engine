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

class Player: public Entity {
public:
	Player(Camera* playerCamera);
	virtual ~Player();
	void update();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();

	//void moveTo( Vector3f movement );
	void rotate( Vector3f rotation );

	Vector3f getWorldPosition();
	Vector3f getWorldAngle();

private:
	Camera* m_pCamera;



};

#endif /* SRC_ENTITY_PLAYER_H_ */
