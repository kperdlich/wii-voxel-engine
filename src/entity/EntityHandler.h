/*
 * EntityHandler.h
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

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
