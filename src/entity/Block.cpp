/*
 * Block.cpp
 *
 *  Created on: 02.07.2015
 *      Author: Kevin
 */

#include "Block.h"
#include "renderer/BlockRenderer.h"

CBlock::CBlock() {

	m_entityRenderer = new BlockRenderer(this);
}


CBlock::CBlock( Vector3f position, float size ) : Entity(position), m_size(size)
{
	m_entityRenderer = new BlockRenderer(this);

}

CBlock::~CBlock() {

}

float CBlock::getSize()
{
	return m_size;
}

