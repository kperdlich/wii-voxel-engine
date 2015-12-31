/*
 * Block.h
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_BLOCK_H_
#define SRC_ENTITY_BLOCK_H_

#include "Entity.h"



class CBlock: public Entity {
public:
	CBlock();
	CBlock( Vector3f position, float size );
	virtual ~CBlock();
	float getSize();

protected:
	unsigned int m_blockType; // set the render texture by the type
	float m_size; // the size from the middle point to each axis
};

#endif /* SRC_ENTITY_BLOCK_H_ */
