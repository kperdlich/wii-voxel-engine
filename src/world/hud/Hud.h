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

#pragma once

#include <vector>
#include "../../components/UiTextureElement.h"
#include "Hotbar.h"
#include "PlayerInventoryHud.h"

class Hud {
public:
    Hud();
    Hud(const Hud&) = delete;
    Hud(Hud&&) = delete;
    void operator=(const Hud&) = delete;
    void operator=(Hud&&) = delete;
    virtual ~Hud();
	void addComponent( UiTextureElement* component );
	void Init();

protected:
	PlayerInventoryHud* m_playerInventoryHud;
	std::vector<UiTextureElement*> m_hudComponents;
};
