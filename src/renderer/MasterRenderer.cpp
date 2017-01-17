#include "MasterRenderer.h"
#include <gccore.h>
#include <math.h>

MasterRenderer::MasterRenderer()
{

}

size_t MasterRenderer::GetDisplayListSizeForFaces(uint32_t faces)
{
    return (size_t) ((32 * 6) * faces); // 32 * 6 magic numbers, seems to work fine
}

void MasterRenderer::SetGraphicsMode(bool bTexturemode, bool bNormalMode)
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

void MasterRenderer::LoadTexture(const Texture& texture, uint8_t textureMapSlot /*= GX_TEXMAP0*/)
{
   GX_LoadTexObj(texture.GetTextureObject(), textureMapSlot);
}


// GRRLIB stuff ..
extern  GRRLIB_drawSettings  GRRLIB_Settings;
extern  Mtx                  GXmodelView2D;
extern guVector axis;

void MasterRenderer::DrawImage(const Texture& texture, float xpos, float ypos, float degrees, float scaleX, float scaleY, uint32_t color)
 {
     u16       width, height;
     Mtx       m, m1, m2, mv;

     GXTexObj* texObj = texture.GetTextureObject();
     GRRLIB_texImg* tex = texture.GetGrrlibTexture();

     GX_LoadTexObj(texObj,      GX_TEXMAP0);
     GX_SetTevOp  (GX_TEVSTAGE0, GX_MODULATE);
     GX_SetVtxDesc(GX_VA_TEX0,   GX_DIRECT);

     guMtxIdentity  (m1);
     guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0);
     guMtxRotAxisDeg(m2, &axis, degrees);
     guMtxConcat    (m2, m1, m);

     width  = tex->w * 0.5;
     height = tex->h * 0.5;

     guMtxTransApply(m, m,
         xpos +width  +tex->handlex
             -tex->offsetx +( scaleX *(-tex->handley *sin(-DegToRad(degrees))
                                       -tex->handlex *cos(-DegToRad(degrees))) ),
         ypos +height +tex->handley
             -tex->offsety +( scaleY *(-tex->handley *cos(-DegToRad(degrees))
                                       +tex->handlex *sin(-DegToRad(degrees))) ),
         0);
     guMtxConcat(GXmodelView2D, m, mv);

     GX_LoadPosMtxImm(mv, GX_PNMTX0);
     GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
         GX_Position3f32(-width, -height, 0);
         GX_Color1u32   (color);
         GX_TexCoord2f32(0, 0);

         GX_Position3f32(width, -height, 0);
         GX_Color1u32   (color);
         GX_TexCoord2f32(1, 0);

         GX_Position3f32(width, height, 0);
         GX_Color1u32   (color);
         GX_TexCoord2f32(1, 1);

         GX_Position3f32(-width, height, 0);
         GX_Color1u32   (color);
         GX_TexCoord2f32(0, 1);
     GX_End();
     GX_LoadPosMtxImm(GXmodelView2D, GX_PNMTX0);

     GX_SetTevOp  (GX_TEVSTAGE0, GX_PASSCLR);
     GX_SetVtxDesc(GX_VA_TEX0,   GX_NONE);
 }
