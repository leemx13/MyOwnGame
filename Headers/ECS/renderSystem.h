#pragma once
#include "ECS/ecs.h"
#include "ECS/spriteDatabase.h"
#include "Render/render.h"

class RenderSystem
{
public:
    void Render(ECS& ecs, SpriteDatabase& spriteDB, Renderer2D& renderer);
};