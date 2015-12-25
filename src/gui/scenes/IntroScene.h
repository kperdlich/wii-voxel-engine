/*
 * IntroScene.h
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_SCENES_INTROSCENE_H_
#define SRC_GUI_SCENES_INTROSCENE_H_

#include <grrlib.h>
#include "../../handler/Controller.h"
#include "../../handler/TextureHandler.h"
#include "Basic2DScene.h"
#include "../../commands/client/SwitchToMainMenuCommand.h"
#include "../../commands/client/SwitchToInGameCommand.h"

class Controller;

class IntroScene : public Basic2DScene
{
public:
	IntroScene();
	~IntroScene();
	void load() override;
	void update() override;
	void draw() override;

private:
	u32 m_BackgroundAlpha;
};


#endif /* SRC_GUI_SCENES_INTROSCENE_H_ */
