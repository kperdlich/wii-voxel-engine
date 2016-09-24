/*
 * Entity.h
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "../renderer/EntityRenderer.h"
#include "../core/grrlib.h"
#include "../utils/MathHelper.h"
#include "../world/GameWorld.h"

class EntityRenderer;

class Entity {
public:
	Entity();
	Entity( Vector3f position );
	virtual ~Entity();

	uint GetId() const;
	void SetId( unsigned int id );

	void SetPosition( Vector3f position );
	const Vector3f& GetPosition() const;

	void SetRotation( Vector3f position );
	const Vector3f& GetRotation() const;

	void SetVisible(bool value);
	bool IsVisible() const;

	bool IsPlayer() const;
	void SetPlayer( bool value );

	void SetWorld(class CGameWorld* pWorld);

	const EntityRenderer* GetRenderer() const;


protected:
	bool m_visible = true, m_isPlayer = false;
	Vector3f m_position, m_rotation;
	uint m_id;
	EntityRenderer* m_entityRenderer;
	class CGameWorld* m_pWorld;

};

#endif /* _ENTITY_H_ */
