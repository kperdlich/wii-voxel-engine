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

#ifndef _UIELEMENT_H_
#define _UIELEMENT_H_

class UIElement
{

protected:
	UIElement(int x, int y, float width, float height, const char* name );
	int m_x, m_y;
	float m_width, m_height;
	const char* m_Name; // note: the name has to be unique per scene!!!
	bool m_visible;

public:
	virtual ~UIElement();
	virtual void Load();
	virtual void Update();

	float GetHeight() const;
	void SetHeight(float height);
	const char* GetName() const;
	bool IsVisible() const;
	void SetVisible(bool visible);
	float GetWidth() const;
	void SetWidth(float width);

	virtual int GetX() const;
	virtual void SetX(int x);
	virtual int GetY() const;
	virtual void SetY(int y);
};



#endif /* _UIELEMENT_H_ */
