#pragma once

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
    static void DrawSprite(const Sprite& sprite);
    static void EnableFog();
    static void DisableFog();
};
