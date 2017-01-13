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

#include "RenderHelper.h"

RenderHelper::RenderHelper() {}

RenderHelper::~RenderHelper() {}

size_t RenderHelper::GetDisplayListSizeForFaces(uint32_t faces)
{
    return (size_t) ((32 * 6) * faces); // 32 * 6 magic numbers, seems to work fine
}

void RenderHelper::SetGraphicsMode(bool bTexturemode, bool bNormalMode)
{
    GX_ClearVtxDesc();
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);

    if(bNormalMode)
        GX_SetVtxDesc(GX_VA_NRM, GX_DIRECT);

    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    if(bTexturemode)
        GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    if(bNormalMode)
        GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);

    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);

    if(bTexturemode)
        GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

    if(bTexturemode)
        GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    else
        GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
}
