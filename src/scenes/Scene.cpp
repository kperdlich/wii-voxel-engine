/*
 * Scene.cpp
 *
 *  Created on: 23.05.2015
 *      Author: Kevin
 */

#include "Scene.h"


Scene::Scene() {
}


Scene::~Scene()
{
	delete m_TextureHandler;
	delete m_Renderer;
}

void Scene::Load() {
}

void Scene::Unload() {
}

void Scene::Draw() {
}

void Scene::Update() {
}

TextureHandler& Scene::GetTextureHandler() const
{
	return *m_TextureHandler;
}

Renderer& Scene::GetRenderer() const
{
	return *m_Renderer;
}
