/*
 * MainMenuScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_SCENES_MAINMENUSCENE_H_
#define SRC_GUI_SCENES_MAINMENUSCENE_H_

#include "../components/Logo.h"
#include "../components/Cursor.h"
#include "../components/ClassicBackground.h"
#include "../components/BasicButton.h"
#include "Basic2DScene.h"
#include "../../commands/client/SwitchToIntroCommand.h"

class MainMenuScene: public Basic2DScene {
public:
	MainMenuScene();
	virtual ~MainMenuScene();
	void load() override;
	void draw() override;
	void update() override;
private:
	void createButtons();

};

#endif /* SRC_GUI_SCENES_MAINMENUSCENE_H_ */
