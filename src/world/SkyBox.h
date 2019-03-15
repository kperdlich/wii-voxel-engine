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

#ifndef SRC_WORLD_CSKYBOX_H_
#define SRC_WORLD_CSKYBOX_H_

#include "../renderer/displaylist.h"
#include "../textures/Texture.h"
#include "../Engine.h"

class SkyBox {
public:
    SkyBox();
    ~SkyBox();
	void Render();
	void Init();
    void Clear();

private:
	void CreateSkyBox();    
    Texture* m_pSkyBoxTextures[6];	
    DisplayList m_displayList;
};

#endif /* SRC_WORLD_CSKYBOX_H_ */
