/*
 * EntityHandler.h
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_ENTITYHANDLER_H_
#define SRC_ENTITY_ENTITYHANDLER_H_

#include <map>
#include "Entity.h"

class EntityHandler {
public:
	EntityHandler();
	virtual ~EntityHandler();

	Entity* getEntity(unsigned int id);
	void addEntity(Entity* entity);

	void update();
	void clear();

	std::map<unsigned int, Entity*>* getEntities();

	Entity* getPlayer();

private:
	std::map<unsigned int, Entity*> m_entityMap;
	unsigned int getNewID();
};

#endif /* SRC_ENTITY_ENTITYHANDLER_H_ */
