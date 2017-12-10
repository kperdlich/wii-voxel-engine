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

#ifndef _BLOCKRENDERER_H_
#define _BLOCKRENDERER_H_

#include <vector>
#include "BlockRenderHelper.h"
#include "../world/blocks/Block.h"
#include "../textures/Texture.h"


class BlockRenderer {
public:
	BlockRenderer();
	virtual ~BlockRenderer();
    void Prepare(std::vector<BlockRenderVO> *positionList, const Block& block);
    void Draw();
	void Finish();
    static void DrawFocusOnSelectedCube(const Vector3& blockWorldPosition, float blockSizeToCenter);

private:
    const Block* m_pBlock;
	float m_renderBlockSize = 0.0f;
    std::vector<BlockRenderVO>* m_positions;


};

#endif /* _BLOCKRENDERER_H_ */
