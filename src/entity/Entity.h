/*
 * Entity.h
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_ENTITY_H_
#define SRC_ENTITY_ENTITY_H_

#include <grrlib.h>
#include "renderer/EntityRenderer.h"
#include "../utils/MathHelper.h"

class EntityRenderer;

class Entity {
public:
	Entity();
	Entity( Vector3f position );
	virtual ~Entity();

	uint getId();
	void setId( unsigned int id );

	void setPosition( Vector3f position );
	Vector3f getPosition();

	void setRotation( Vector3f position );
	Vector3f getRotation();

	void setVisible(bool value);
	bool isVisible();

	bool isPlayer();
	bool setPlayer( bool value );

	EntityRenderer* getRenderer();


protected:
	bool m_visible = true, m_isPlayer = false;
	Vector3f m_position, m_rotation;
	uint m_id;
	EntityRenderer* m_entityRenderer;

};

#endif /* SRC_ENTITY_ENTITY_H_ */
