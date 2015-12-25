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
	virtual ~CBlock();

protected:
	unsigned int m_blockType; // set the render texture by the type
};

#endif /* SRC_ENTITY_BLOCK_H_ */
