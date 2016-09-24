/*
 * Entity.cpp
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#include "Entity.h"

Entity::Entity() {}

Entity::Entity( Vector3f position )
{
	m_position = position;
}


Entity::~Entity()
{
	delete m_entityRenderer;
}


uint Entity::GetId() const
{
	return m_id;
}

void Entity::SetId(unsigned int id)
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

void Entity::SetPosition( Vector3f position )
{
	m_position = position;
}

const Vector3f& Entity::GetPosition() const
{
	return m_position;
}

void Entity::SetRotation( Vector3f rotation )
{
	m_rotation = rotation;
}

const Vector3f& Entity::GetRotation() const
{
	return m_rotation;
}

void Entity::SetWorld(class CGameWorld* pWorld)
{
	m_pWorld = pWorld;
}
