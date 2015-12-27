/*
 * Scene.h
 *
 *  Created on: 23.05.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_SCENE_SCENE_H_
#define SRC_GUI_SCENE_SCENE_H_

#include "../../handler/TextureHandler.h"
#include "../renderer/Renderer.h"

class Scene {

public:
	Scene();
	virtual ~Scene();
	virtual void load();
	virtual void unload();
	virtual void draw();
	virtual void update();
	TextureHandler* getTextureHandler();
	Renderer* getRenderer();

protected:
	TextureHandler *m_TextureHandler;
	Renderer *m_Renderer;


};



#endif /* SRC_GUI_SCENE_SCENE_H_ */
