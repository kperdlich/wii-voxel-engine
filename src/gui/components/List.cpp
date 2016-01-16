/*
 * List.cpp
 *
 *  Created on: 27.12.2015
 *      Author: Kevin
 */

#include "List.h"
#include "UIElement.h"
#include "../../utils/Debug.h"

List::List(int x, int y, int sizeBetweenElements ) : m_x(x), m_y(y) , m_sizeBetweenElements(sizeBetweenElements)
{

}

List::List( int sizeBetweenElements ) : List(0, 0, sizeBetweenElements)
{

}

List::~List()
{

}

void List::addComponent(UIElement* element)
{
	unsigned int entryX, entryY;
	if ( m_elements.size() == 0 )
	{
		entryX = m_x;
		entryY = m_y;
	}
	else
	{
		UIElement* lastEntry = m_elements.back();
		entryX= lastEntry->getX();
		entryY = lastEntry->getY() + m_sizeBetweenElements;
	}

	element->setX(entryX);
	element->setY(entryY);

	m_elements.push_back( element );

}

