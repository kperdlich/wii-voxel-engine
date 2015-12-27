/*
 * MainMenuScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_SCENES_MAINMENUSCENE_H_
#define SRC_GUI_SCENES_MAINMENUSCENE_H_



#include "Basic2DScene.h"
#include "../components/BasicButton.h"


class MainMenuScene: public Basic2DScene {
public:
	MainMenuScene();
	virtual ~MainMenuScene();
	void load() override;
	void draw() override;
	void update() override;
private:
	void createButtons();
	BasicButton* createDefaultMainMenuButton( const char* buttonName, const char* buttontext, void (*clickCallback) (BasicButton*) );

};

#endif /* SRC_GUI_SCENES_MAINMENUSCENE_H_ */
