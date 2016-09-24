/*
 * InGameScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef _INGAMESCENE_H_
#define _INGAMESCENE_H_

#include "Basic3DScene.h"


class InGameScene: public Basic3DScene {
public:
	InGameScene();
	virtual ~InGameScene();
	void Update() override;
	void Load() override;
	void Draw() override;
protected:
	void initEntities();

};

#endif /* _INGAMESCENE_H_ */
