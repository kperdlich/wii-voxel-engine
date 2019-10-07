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

#include "entity/Entity.h"

Entity::Entity() {}

Entity::Entity( Vector3 position )
{
	m_position = position;
}


Entity::~Entity()
{
	delete m_entityRenderer;
}


uint32_t Entity::GetId() const
{
	return m_id;
}

void Entity::SetId(uint32_t id)
{
	m_id = id;
}

void Entity::SetVisible(bool value)
{
	m_visible = true;
}

bool Entity::IsVisible() const
{
	return m_visible;
}

bool Entity::IsPlayer() const
{
	return m_isPlayer;
}

void Entity::SetPlayer(bool value)
{
	m_isPlayer = value;
}

const EntityRenderer* Entity::GetRenderer() const
{
	return m_entityRenderer;
}

void Entity::SetPosition(const Vector3 &position )
{
	m_position = position;
}

const Vector3& Entity::GetPosition() const
{
	return m_position;
}

void Entity::SetRotation( const Vector3& rotation )
{
	m_rotation = rotation;
}

const Vector3& Entity::GetRotation() const
{
	return m_rotation;
}

void Entity::SetWorld(class GameWorld* pWorld)
{
	m_pWorld = pWorld;
}
