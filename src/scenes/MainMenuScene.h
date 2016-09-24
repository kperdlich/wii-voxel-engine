/*
 * MainMenuScene.h
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#ifndef _MAINMENUSCENE_H_
#define _MAINMENUSCENE_H_



#include "Basic2DScene.h"
#include "../components/BasicButton.h"


class MainMenuScene: public Basic2DScene {
public:
	MainMenuScene();
	virtual ~MainMenuScene();
	void Load() override;
	void Draw() override;
	void Update() override;
private:
	void CreateMainMenuButtonList();
	BasicButton* CreateDefaultMainMenuButton( const char* buttonName, const char* buttontext, void (*clickCallback) (BasicButton*));

};

#endif /* _MAINMENUSCENE_H_ */
