/*
 * BasicButton.h
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#ifndef _BASICBUTTON_H_
#define _BASICBUTTON_H_

#include "UITextureElement.h"
#include "../textures/Texture.h"
#include "../textures/LabelTexture.h"

#define BUTTON_LABEL_DISTANCE 3

class BasicButton: public UITextureElement {

public:
	typedef void (*OnClickCallback)(BasicButton*);

	BasicButton( float x, float y, const char* name, Texture* defaultTexture, Texture* highlightTexture, LabelTexture* label, OnClickCallback clickCallback );
	virtual ~BasicButton();
	void Update();
	bool HandleMoveOver();
	void HandleOnClick();
	void UpdateLabel();

	void SetColor(u32 color);
	void SetButtonCallback(OnClickCallback callback);

	virtual void SetX(int x) override;
	virtual void SetY(int y) override;


private:
	Texture* m_highlightTexture;
	LabelTexture* m_label;
	OnClickCallback m_clickCallback;
};

#endif /* _BASICBUTTON_H_ */
