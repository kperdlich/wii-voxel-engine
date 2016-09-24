/*
 * EntityRenderer.cpp
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#include "EntityRenderer.h"
#include "../Controller.h"

EntityRenderer::EntityRenderer( Entity* entity ) : m_Entity(entity) {

}

EntityRenderer::~EntityRenderer() {

}

void EntityRenderer::SetTexture(Texture* texture) {
	m_entityTexture = texture;
	m_entityTexture->SetVisible(false); // invisible else it would be rendered by the 2d renderer as a normal texture
}

Texture* EntityRenderer::GetTexture() const
{
	return m_entityTexture;
}

void EntityRenderer::Render() const {}

TextureHandler& EntityRenderer::GetTextureHandler()
{
	return Controller::GetInstance().GetSceneHandler().GetCurrentScene().GetTextureHandler();
}
