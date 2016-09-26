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

#ifndef _CHUD_H_
#define _CHUD_H_

#include <vector>
#include "../../components/UITextureElement.h"
#include "CHotbar.h"
#include "CPlayerInventoryHud.h"

class CHud {
public:
	CHud();
	virtual ~CHud();
	void addComponent( UITextureElement* component );
	void Init();

protected:
	CPlayerInventoryHud* m_playerInventoryHud;


	std::vector<UITextureElement*> m_hudComponents;

};

#endif /* _CHUD_H_ */
