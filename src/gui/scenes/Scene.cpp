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

void Scene::load() {
}

void Scene::unload() {
}

void Scene::draw() {
}

void Scene::update() {
}

TextureHandler* Scene::getTextureHandler() {
	return m_TextureHandler;
}

Renderer* Scene::getRenderer() {
	return m_Renderer;
}
