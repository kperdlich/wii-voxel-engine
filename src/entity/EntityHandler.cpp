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

#include "entity/EntityHandler.h"

EntityHandler::EntityHandler() {

}

EntityHandler::~EntityHandler()
{
	Clear();

}

Entity* EntityHandler::GetEntity(uint32_t id)
{
    std::map<uint32_t, Entity*>::iterator it = m_entityMap.find(id);
	if ( it != m_entityMap.end() )
		return it->second;

    return nullptr;
}

void EntityHandler::AddEntity(Entity* entity)
{
    uint32_t newId = GetNewID();
	entity->SetId( newId );
    m_entityMap.insert( std::pair<uint32_t, Entity*>(newId, entity) );
}

void EntityHandler::Update() {

}

const std::map<uint32_t, Entity*>* EntityHandler::GetEntities() const
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

    return nullptr;
}

uint32_t EntityHandler::GetNewID()
{
	if ( m_entityMap.size() < 1)
		return 0;
	return m_entityMap.end()->first + 1;
}
