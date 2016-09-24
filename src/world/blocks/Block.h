/*
 * Block.h
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../../textures/Texture.h"

class CBlock {
public:
	CBlock();
	CBlock( float size, const Texture* pTexture );
	virtual ~CBlock();
	float GetSize() const;
	const Texture* GetTexture() const;

protected:
	float m_size; // the size from the middle point to each axis
	const Texture* m_pTexture;

};

#endif /* _BLOCK_H_ */
