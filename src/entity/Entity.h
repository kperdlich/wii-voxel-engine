/*
 * Entity.h
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_ENTITY_H_
#define SRC_ENTITY_ENTITY_H_

#include "../core/grrlib.h"
#include "renderer/EntityRenderer.h"
#include "../utils/MathHelper.h"
#include "../gui/world/GameWorld.h"

class EntityRenderer;

class Entity {
public:
	Entity();
	Entity( Vector3f position );
	virtual ~Entity();

	uint getId();
	void setId( unsigned int id );

	void SetPosition( Vector3f position );
	Vector3f GetPosition();

	void setRotation( Vector3f position );
	Vector3f getRotation();

	void SetVisible(bool value);
	bool IsVisible();

	bool IsPlayer();
	void SetPlayer( bool value );

	void SetWorld(class CGameWorld* pWorld);

	EntityRenderer* getRenderer();


protected:
	bool m_visible = true, m_isPlayer = false;
	Vector3f m_position, m_rotation;
	uint m_id;
	EntityRenderer* m_entityRenderer;
	class CGameWorld* m_pWorld;

};

#endif /* SRC_ENTITY_ENTITY_H_ */
