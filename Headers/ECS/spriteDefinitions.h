#pragma once
#include "ECS/spriteDatabase.h"
#include "Render/render.h"

namespace SpriteDefinitions
{
    void RegisterAllPlayerSprites(SpriteDatabase& spriteDB, Renderer2D& renderer);
}