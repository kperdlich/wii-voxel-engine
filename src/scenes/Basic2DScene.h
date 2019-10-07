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
#include "scenes/Scene.h"
#include "components/UiElement.h"


class Basic2DScene: public Scene {
public:
    Basic2DScene();
    Basic2DScene(const Basic2DScene&) = delete;
    Basic2DScene(Basic2DScene&&) = delete;
    void operator=(const Basic2DScene&) = delete;
    void operator=(Basic2DScene&&) = delete;
    virtual ~Basic2DScene();
	virtual void Draw() override;
	virtual void Load() override;
	virtual void Unload() override;
    virtual void Update(float deltaSeconds) override;

protected:
	std::vector<UiElement*> m_elements;

};
