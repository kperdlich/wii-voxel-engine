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
