/*
 * EntityHandler.cpp
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#include "EntityHandler.h"

EntityHandler::EntityHandler() {

}

EntityHandler::~EntityHandler()
{
	clear();

}

Entity* EntityHandler::getEntity(unsigned int id)
{
	std::map<unsigned int, Entity*>::iterator it = m_entityMap.find(id);
	if ( it != m_entityMap.end() )
		return it->second;

	return NULL;
}

void EntityHandler::addEntity(Entity* entity)
{
	unsigned int newId = getNewID();
	entity->setId( newId );
	m_entityMap.insert( std::pair<unsigned int, Entity*>(newId, entity) );
}

void EntityHandler::update() {

}

std::map<unsigned int, Entity*>* EntityHandler::getEntities() {
	return &m_entityMap;
}

void EntityHandler::clear() {
	for (std::map<unsigned int, Entity*>::iterator it = m_entityMap.begin(); it != m_entityMap.end(); ++it)
	{
		delete it->second;
	}

	m_entityMap.clear();
}

Entity* EntityHandler::getPlayer() {
	for (std::map<unsigned int, Entity*>::iterator it = m_entityMap.begin(); it != m_entityMap.end(); ++it)
	{
		if ( it->second->isPlayer() )
		{
			return it->second;
		}
	}

	return NULL;
}

unsigned int EntityHandler::getNewID()
{
	if ( m_entityMap.size() < 1)
		return 0;
	return m_entityMap.end()->first + 1;
}
