/*
 * BasicScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_SCENES_BASICSCENE_H_
#define SRC_GUI_SCENES_BASICSCENE_H_

#include "Scene.h"

class BasicScene: public Scene {
public:
	BasicScene();
	virtual ~BasicScene();
	virtual void unload() override;

};

#endif /* SRC_GUI_SCENES_BASICSCENE_H_ */
