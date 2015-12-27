/*
 * BasicButton.h
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_COMPONENTS_BASICBUTTON_H_
#define SRC_GUI_COMPONENTS_BASICBUTTON_H_

#include "UITextureElement.h"
#include "../Texture.h"
#include "../LabelTexture.h"

#define BUTTON_LABEL_DISTANCE 3

class BasicButton: public UITextureElement {

public:
	typedef void (*OnClickCallback)(BasicButton*);

	BasicButton( float x, float y, const char* name, Texture* defaultTexture, Texture* highlightTexture, LabelTexture* label, OnClickCallback clickCallback );
	virtual ~BasicButton();
	void update();
	bool handleMoveOver();
	void handleOnClick();
	void updateLabel();

	void setColor(u32 color);
	void setButtonCallback(OnClickCallback callback);

	virtual void setX(int x) override;
	virtual void setY(int y) override;


private:
	Texture* m_highlightTexture;
	LabelTexture* m_label;
	OnClickCallback m_clickCallback;


};

#endif /* SRC_GUI_COMPONENTS_BASICBUTTON_H_ */
