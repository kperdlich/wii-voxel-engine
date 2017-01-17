#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "../textures/Texture.h"
#include <cinttypes>
#include <cstddef>

class MasterRenderer
{
public:
    MasterRenderer();

    static size_t GetDisplayListSizeForFaces(uint32_t faces);
    static void SetGraphicsMode(bool bTexturemode, bool bNormalMode);
    static void LoadTexture(const Texture& texture, uint8_t textureMapSlot = GX_TEXMAP0);
    static void DrawImage(const Texture& texture, float xpos, float ypos, float degrees, float scaleX, float scaleY, uint32_t color);
};

#endif // MASTERRENDERER_H
