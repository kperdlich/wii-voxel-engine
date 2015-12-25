/*
 * Basic2DScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_SCENES_BASIC2DSCENE_H_
#define SRC_GUI_SCENES_BASIC2DSCENE_H_

#include <vector>
#include "../components/UIElement.h"
#include "BasicScene.h"
#include "../renderer/Renderer2D.h"

class Basic2DScene: public BasicScene {
public:
	Basic2DScene();
	virtual ~Basic2DScene();
	virtual void draw();
	virtual void load();
	virtual void unload();
	virtual void update();


protected:
	Renderer2D* getRenderer();
	std::vector<UIElement*> m_elements;

};

#endif /* SRC_GUI_SCENES_BASIC2DSCENE_H_ */
