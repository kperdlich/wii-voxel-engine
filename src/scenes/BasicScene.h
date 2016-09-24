/*
 * BasicScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef _BASICSCENE_H_
#define _BASICSCENE_H_

#include "Scene.h"

class BasicScene: public Scene {
public:
	BasicScene();
	virtual ~BasicScene();
	virtual void Unload() override;

};

#endif /* _BASICSCENE_H_ */
