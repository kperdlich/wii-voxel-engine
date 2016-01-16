/*
 * UIElement.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_COMPONENTS_UIELEMENT_H_
#define SRC_GUI_COMPONENTS_UIELEMENT_H_

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
	virtual void load();
	virtual void update();

	float getHeight();
	void setHeight(float height);
	const char* getName();
	bool isVisible();
	void setVisible(bool visible);
	float getWidth();
	void setWidth(float width);

	virtual int getX();
	virtual void setX(int x);
	virtual int getY();
	virtual void setY(int y);
};



#endif /* SRC_GUI_COMPONENTS_UIELEMENT_H_ */
