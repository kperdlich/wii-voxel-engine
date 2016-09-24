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
	Clear();

}

Entity* EntityHandler::GetEntity(unsigned int id)
{
	std::map<unsigned int, Entity*>::iterator it = m_entityMap.find(id);
	if ( it != m_entityMap.end() )
		return it->second;

	return NULL;
}

void EntityHandler::AddEntity(Entity* entity)
{
	unsigned int newId = GetNewID();
	entity->SetId( newId );
	m_entityMap.insert( std::pair<unsigned int, Entity*>(newId, entity) );
}

void EntityHandler::Update() {

}

const std::map<unsigned int, Entity*>* EntityHandler::GetEntities() const
{
	return &m_entityMap;
}

void EntityHandler::Clear() {
	for (auto it = m_entityMap.begin(); it != m_entityMap.end(); ++it)
	{
		delete it->second;
	}

	m_entityMap.clear();
}

Entity* EntityHandler::GetPlayer() const {
	for (auto it = m_entityMap.begin(); it != m_entityMap.end(); ++it)
	{
		if ( it->second->IsPlayer() )
		{
			return it->second;
		}
	}

	return NULL;
}

unsigned int EntityHandler::GetNewID()
{
	if ( m_entityMap.size() < 1)
		return 0;
	return m_entityMap.end()->first + 1;
}
