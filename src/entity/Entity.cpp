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


Entity::~Entity() {
	delete m_entityRenderer;
}

uint Entity::getId() {
	return m_id;
}

void Entity::setId(unsigned int id) {
	m_id = id;
}

void Entity::setVisible(bool value) {
	m_visible = true;
}

bool Entity::isVisible() {
	return m_visible;
}

bool Entity::isPlayer() {
	return m_isPlayer;
}

bool Entity::setPlayer(bool value) {
	m_isPlayer = value;
}

EntityRenderer* Entity::getRenderer() {
	return m_entityRenderer;
}

void Entity::setPosition( Vector3f position )
{
	m_position = position;
}

Vector3f Entity::getPosition()
{
	return m_position;
}

void Entity::setRotation( Vector3f rotation )
{
	m_rotation = rotation;
}

Vector3f Entity::getRotation()
{
	return m_rotation;
}
