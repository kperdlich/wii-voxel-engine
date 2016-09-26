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

#ifndef _ENTITYHANDLER_H_
#define _ENTITYHANDLER_H_

#include <map>
#include "Entity.h"

class EntityHandler {
public:
	EntityHandler();
	virtual ~EntityHandler();

	class Entity* GetEntity(unsigned int id);
	void AddEntity(class Entity* entity);

	void Update();
	void Clear();

	const std::map<unsigned int, class Entity*>* GetEntities() const;

	class Entity* GetPlayer() const;

private:
	std::map<unsigned int, class Entity*> m_entityMap;
	unsigned int GetNewID();
};

#endif /* _ENTITYHANDLER_H_ */
