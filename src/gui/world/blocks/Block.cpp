/*
 * Block.cpp
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#include "Block.h"

CBlock::CBlock() {

}


CBlock::CBlock( float size, Texture* pTexture ) : /*Entity(position), */ m_size(size), m_pTexture(pTexture)
{

}

CBlock::~CBlock() {

}


Texture* CBlock::GetTexture()
{
	return m_pTexture;
}

float CBlock::getSize()
{
	return m_size;
}

