/*
 * List.h
 *
 *  Created on: 27.12.2015
 *      Author: Kevin
 */

#ifndef _LIST_H_
#define _LIST_H_

#include "vector"
#include "UIElement.h"

class List : public UIElement {

public:
	List(int x, int y, int sizeBetweenElements );
	List( int sizeBetweenElements );
	virtual ~List();
	virtual void Update();

	void AddComponent(UIElement* element);

private:
	std::vector<UIElement*> m_elements;
	unsigned int m_sizeBetweenElements;
};

#endif /* _LIST_H_ */
