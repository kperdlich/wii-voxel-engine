/*
 * Block.cpp
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#include "Block.h"

CBlock::CBlock() {

}


CBlock::CBlock( float size, const Texture* pTexture ) : m_size(size), m_pTexture(pTexture)
{

}

CBlock::~CBlock() {

}


const Texture* CBlock::GetTexture() const
{
	return m_pTexture;
}

float CBlock::GetSize() const
{
	return m_size;
}

