/*
 * InGameScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_SCENES_INGAMESCENE_H_
#define SRC_GUI_SCENES_INGAMESCENE_H_

#include "Basic3DScene.h"

#define MIN_DIST 1.0f
#define MAX_DIST 500.0f
#define FIELD_OF_VIEW 45.0f

class InGameScene: public Basic3DScene {
public:
	InGameScene();
	virtual ~InGameScene();
	void update() override;
	void load() override;
	void draw() override;
protected:
	void initEntities();
};

#endif /* SRC_GUI_SCENES_INGAMESCENE_H_ */
