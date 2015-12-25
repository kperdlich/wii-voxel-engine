/*
 * Entity.cpp
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#include "Entity.h"

Entity::Entity() {
	m_visible = true;
}

Entity::~Entity() {
	delete m_entityRenderer;
}

uint Entity::getId() {
	return m_id;
}

double Entity::getX() {
	return m_x;
}

void Entity::setX(double x) {
	m_x = x;
}

double Entity::getY() {
	return m_y;
}

void Entity::setY(double y) {
	m_y = y;
}

double Entity::getZ() {
	return m_z;
}

void Entity::setZ(double z) {
	m_z = z;
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
