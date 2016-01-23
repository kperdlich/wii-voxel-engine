/*
 * Block.h
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_BLOCK_H_
#define SRC_ENTITY_BLOCK_H_

#include "../../Texture.h"

class CBlock {
public:
	CBlock();
	CBlock( float size, Texture* pTexture );
	virtual ~CBlock();
	float getSize();
	Texture* GetTexture();

protected:
	float m_size; // the size from the middle point to each axis
	Texture* m_pTexture;

};

#endif /* SRC_ENTITY_BLOCK_H_ */
