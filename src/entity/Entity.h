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
	Entity( Vector3 position );
	virtual ~Entity();

	uint GetId() const;
	void SetId( unsigned int id );

	void SetPosition( Vector3 position );
	const Vector3& GetPosition() const;

	void SetRotation( Vector3 position );
	const Vector3& GetRotation() const;

	void SetVisible(bool value);
	bool IsVisible() const;

	bool IsPlayer() const;
	void SetPlayer( bool value );

	void SetWorld(class CGameWorld* pWorld);

	const EntityRenderer* GetRenderer() const;


protected:
	bool m_visible = true, m_isPlayer = false;
	Vector3 m_position, m_rotation;
	uint m_id;
	EntityRenderer* m_entityRenderer;
	class CGameWorld* m_pWorld;

};

#endif /* _ENTITY_H_ */
