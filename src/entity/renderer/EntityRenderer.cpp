/*
 * EntityRenderer.cpp
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#include "EntityRenderer.h"
#include "../../handler/Controller.h"

EntityRenderer::EntityRenderer( Entity* entity ) : m_Entity(entity) {

}

EntityRenderer::~EntityRenderer() {

}

void EntityRenderer::setTexture(Texture* texture) {
	m_entityTexture = texture;
	m_entityTexture->setVisible(false); // invisible else it would be rendered by the 2d renderer as a normal texture
}

Texture* EntityRenderer::getTexture() {
	return m_entityTexture;
}

void EntityRenderer::render() {
}

TextureHandler* EntityRenderer::getTextureHandler() {
	return Controller::getInstance().getSceneHandler()->getCurrentScene()->getTextureHandler();
}
