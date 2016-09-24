/*
 * Basic2DScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef _BASIC2DSCENE_H_
#define _BASIC2DSCENE_H_

#include <vector>
#include "../components/UIElement.h"
#include "BasicScene.h"
#include "../renderer/Renderer2D.h"

class Basic2DScene: public BasicScene {
public:
	Basic2DScene();
	virtual ~Basic2DScene();
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Unload() override;
	virtual void Update() override;

protected:
	Renderer2D& Get2DRenderer();

	std::vector<UIElement*> m_elements;

};

#endif /* _BASIC2DSCENE_H_ */
