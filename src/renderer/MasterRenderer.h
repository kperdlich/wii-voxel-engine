#pragma once

#include <cinttypes>
#include <cstddef>
#include "textures/Texture.h"
#include "textures/Sprite.h"

class MasterRenderer
{
public:
    MasterRenderer();
    MasterRenderer(const MasterRenderer&) = delete;
    MasterRenderer(MasterRenderer&&) = delete;
    void operator=(const MasterRenderer&) = delete;
    void operator=(MasterRenderer&&) = delete;
    static size_t GetDisplayListSizeForFaces(uint32_t faces);
    static void SetGraphicsMode(bool bTexturemode, bool bNormalMode);    
    static void DrawSprite(const Sprite& sprite);
    static void EnableFog();
    static void DisableFog();
};
