/*
 * InGameScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_SCENES_INGAMESCENE_H_
#define SRC_GUI_SCENES_INGAMESCENE_H_

#include "Basic3DScene.h"

class InGameScene: public Basic3DScene {
public:
	InGameScene();
	virtual ~InGameScene();
	void update() override;
	void load() override;
	void draw() override;
protected:
	void initEntities();
	void drawMap(); // todo: let's handle this by the world class
};

#endif /* SRC_GUI_SCENES_INGAMESCENE_H_ */
