/*
 * IntroScene.h
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#ifndef _INTROSCENE_H_
#define _INTROSCENE_H_


#include "Basic2DScene.h"

class Controller;

class IntroScene : public Basic2DScene
{
public:
	IntroScene();
	~IntroScene();
	void Load() override;
	void Update() override;
	void Draw() override;

private:
	u32 m_BackgroundAlpha;
};


#endif /* _INTROSCENE_H_ */
