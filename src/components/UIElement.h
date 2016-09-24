/*
 * UIElement.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

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
