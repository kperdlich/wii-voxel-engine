/*
 * List.h
 *
 *  Created on: 27.12.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_COMPONENTS_LIST_H_
#define SRC_GUI_COMPONENTS_LIST_H_

#include "vector"
#include "UIElement.h"

class List {

public:
	List(int x, int y, int sizeBetweenElements );
	List( int sizeBetweenElements );
	virtual ~List();

	void addComponent(UIElement* element);

private:
	std::vector<UIElement*> m_elements;
	unsigned int m_sizeBetweenElements;
	float m_x, m_y;
};

#endif /* SRC_GUI_COMPONENTS_LIST_H_ */
