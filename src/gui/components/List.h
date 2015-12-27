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

class List : public UIElement{

public:
	List(int x, int y, const char* name, int sizeBetweenElements );
	List( int sizeBetweenElements );
	virtual ~List();

	virtual void load() override;
	virtual void update() override;


	void addComponent(UIElement* element);

private:
	std::vector<UIElement*> m_elements;
	unsigned int m_sizeBetweenElements;
};

#endif /* SRC_GUI_COMPONENTS_LIST_H_ */
