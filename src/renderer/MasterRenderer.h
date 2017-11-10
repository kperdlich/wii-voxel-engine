#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "../textures/Texture.h"
#include "../textures/Sprite.h"
#include <cinttypes>
#include <cstddef>

class MasterRenderer
{
public:
    MasterRenderer();

    static size_t GetDisplayListSizeForFaces(uint32_t faces);
    static void SetGraphicsMode(bool bTexturemode, bool bNormalMode);
    static void LoadTexture(const Texture& texture, uint8_t textureMapSlot = GX_TEXMAP0);
    static void DrawSprite(const Sprite& sprite);
};

#endif // MASTERRENDERER_H
