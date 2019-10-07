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

#include "components/List.h"
#include "components/UiElement.h"
#include "utils/Debug.h"

List::List(uint32_t x, uint32_t y, uint32_t sizeBetweenElements )
    : UiElement(x, y, 0.f, 0.f, nullptr), m_sizeBetweenElements(sizeBetweenElements) {}

List::List(uint32_t sizeBetweenElements) : List(0, 0, sizeBetweenElements) {}

List::~List()
{
	for ( uint32_t i = 0; i < m_elements.size(); i++)
	{
		delete m_elements[i];
	}

	m_elements.clear();
}


void List::AddComponent(UiElement* element)
{
	uint32_t entryX, entryY;
	if ( m_elements.size() == 0 )
	{
		entryX = m_x;
		entryY = m_y;
	}
	else
	{
		UiElement* lastEntry = m_elements.back();
		entryX= lastEntry->GetX();
		entryY = lastEntry->GetY() + m_sizeBetweenElements;
	}

	element->SetX(entryX);
	element->SetY(entryY);

	m_elements.push_back( element );
}

void List::Update()
{
	UiElement::Update();

	for ( uint32_t i = 0; i < m_elements.size(); i++)
	{
		m_elements[i]->Update();
	}

}

