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

#include "List.h"
#include "UIElement.h"
#include "../utils/Debug.h"

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


void List::AddComponent(UIElement* element)
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
		entryX= lastEntry->GetX();
		entryY = lastEntry->GetY() + m_sizeBetweenElements;
	}

	element->SetX(entryX);
	element->SetY(entryY);

	m_elements.push_back( element );
}

void List::Update()
{
	UIElement::Update();

	for ( unsigned int i = 0; i < m_elements.size(); i++)
	{
		m_elements[i]->Update();
	}

}

