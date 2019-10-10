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

#pragma once

#include <map>
#include "entity/Entity.h"

class EntityHandler {
public:
	EntityHandler();
	virtual ~EntityHandler();
	EntityHandler(const EntityHandler&) = delete;
	EntityHandler(EntityHandler&&) = delete;
	void operator=(const EntityHandler&) = delete;
	void operator=(EntityHandler&&) = delete;

	class Entity* GetEntity(uint32_t id);
	void AddEntity(class Entity* entity);

	void Update();
	void Clear();

	const std::map<uint32_t, class Entity*>* GetEntities() const;

	class Entity* GetPlayer() const;

private:
	std::map<uint32_t, class Entity*> m_entityMap;
	uint32_t GetNewID();
};
