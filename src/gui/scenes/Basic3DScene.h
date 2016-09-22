/*
 * Basic3DScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_SCENES_BASIC3DSCENE_H_
#define SRC_GUI_SCENES_BASIC3DSCENE_H_

#include "BasicScene.h"
#include "../renderer/Renderer3D.h"
#include "../components/UIElement.h"
#include "../../entity/EntityHandler.h"
#include "../world/Camera.h"
#include "../world/GameWorld.h"

class Basic3DScene: public BasicScene {
public:
	Basic3DScene();
	virtual ~Basic3DScene();
	virtual void load();
	virtual void unload();

	virtual void draw();
	virtual void update();

	class EntityHandler& GetEntityHandler();

	void SetGraphicsMode(bool textureMode, bool normalMode);

protected:
	class Renderer3D* getRenderer();
	class EntityHandler* m_entityHandler;
	std::vector<UIElement*> m_uiElements;
	class Camera* m_mainCamera;
	class CGameWorld* m_pGameWorld;
};

#endif /* SRC_GUI_SCENES_BASIC3DSCENE_H_ */
