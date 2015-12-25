/*
 * Entity.h
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_ENTITY_H_
#define SRC_ENTITY_ENTITY_H_

#include <grrlib.h>
#include "renderer/EntityRenderer.h"

class EntityRenderer;

class Entity {
public:
	Entity();
	virtual ~Entity();

	uint getId();
	void setId( unsigned int id );

	double getX();
	void setX(double x);
	double getY();
	void setY(double y);
	double getZ();
	void setZ(double z);
	void setVisible(bool value);
	bool isVisible();

	bool isPlayer();
	bool setPlayer( bool value );

	EntityRenderer* getRenderer();


protected:
	bool m_visible, m_isPlayer;
	double m_x, m_y, m_z;
	uint m_id;
	EntityRenderer* m_entityRenderer;

};

#endif /* SRC_ENTITY_ENTITY_H_ */
