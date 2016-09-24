/*
 * Scene.h
 *
 *  Created on: 23.05.2015
 *      Author: Kevin
 */

#ifndef _SCENE_H_
#define _SCENE_H_

#include "../textures/TextureHandler.h"
#include "../renderer/Renderer.h"

class Scene {

public:
	Scene();
	virtual ~Scene();
	virtual void Load();
	virtual void Unload();
	virtual void Draw();
	virtual void Update();
	virtual TextureHandler& GetTextureHandler() const;
	virtual Renderer& GetRenderer() const;

protected:
	TextureHandler *m_TextureHandler;
	Renderer *m_Renderer;


};



#endif /* _SCENE_H_ */
