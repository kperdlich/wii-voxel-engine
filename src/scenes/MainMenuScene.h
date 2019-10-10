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
#include <functional>
#include "scenes/Basic2DScene.h"
#include "components/BasicButton.h"

class MainMenuScene : public Basic2DScene {
public:
	void Load() override;
	void Draw() override;
	void Update(float deltaSeconds) override;
private:
	void CreateMainMenuButtonList();
	BasicButton* CreateDefaultMainMenuButton(const char* buttonName, const char* buttontext, std::function<void(BasicButton*)> clickCallback);

};
