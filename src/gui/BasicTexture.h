/*
 * BasicTexture.h
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_BASICTEXTURE_H_
#define SRC_GUI_BASICTEXTURE_H_

#include "../core/grrlib.h"

enum txTypes {
	INVALID,
	SPRITE,
	SPRITE_SHEET,
	TILE,
	LABEL
};

class BasicTexture {
public:
	BasicTexture(float x, float y, const u16 id);
	virtual ~BasicTexture();
	virtual txTypes getTextureType();

	virtual void loadTexture();
	virtual void unloadTexture();

	float getX();
	void setX(float x);
	float getY();
	void setY(float y);

	void setColor(u32 color);
	u32 getColor();

	virtual uint getWidth();
	virtual uint getHeight();

	u16 getId();

	virtual bool isVisible();
	virtual void setVisible(bool value);

protected:
	float m_x, m_y;
	const u16 m_id;
	bool m_visible;
	u32 m_color;
};

#endif /* SRC_GUI_BASICTEXTURE_H_ */
