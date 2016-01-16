/*
 * List.cpp
 *
 *  Created on: 27.12.2015
 *      Author: Kevin
 */

#include "List.h"
#include "UIElement.h"
#include "../../utils/Debug.h"

List::List(int x, int y, int sizeBetweenElements ) : UIElement(x, y, 0.f, 0.f, ""), m_sizeBetweenElements(sizeBetweenElements)
{

}

List::List( int sizeBetweenElements ) : List(0, 0, sizeBetweenElements)
{

}

List::~List()
{
	for ( unsigned int i = 0; i < m_elements.size(); i++)
	{
		delete m_elements[i];
	}

	m_elements.clear();
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

void List::update()
{
	UIElement::update();

	for ( unsigned int i = 0; i < m_elements.size(); i++)
	{

		m_elements[i]->update();
	}

}

