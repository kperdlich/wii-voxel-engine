/*
 * BasicTexture.h
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#ifndef _BASICTEXTURE_H_
#define _BASICTEXTURE_H_

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
	BasicTexture(float x, float y, u16 id);
	virtual ~BasicTexture();
	virtual txTypes GetTextureType() const;

	virtual void LoadTexture();
	virtual void UnloadTexture();

	float GetX() const;
	void SetX(float x);
	float GetY() const;
	void SetY(float y);

	void SetColor(u32 color);
	u32 GetColor() const;

	virtual uint GetWidth() const;
	virtual uint GetHeight() const;

	u16 GetId() const;

	virtual bool IsVisible() const;
	virtual void SetVisible(bool value);

protected:
	float m_x, m_y;
	const u16 m_id;
	bool m_visible;
	u32 m_color;
};

#endif /* _BASICTEXTURE_H_ */
