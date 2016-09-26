/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

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
	Texture* m_highlightTexture = NULL;
	LabelTexture* m_label = NULL;
	OnClickCallback m_clickCallback;
};

#endif /* _BASICBUTTON_H_ */
