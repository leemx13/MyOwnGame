#include "ECS/renderSystem.h"

void RenderSystem::Render(ECS& ecs, SpriteDatabase& spriteDB, Renderer2D& renderer)
{
    for (Entity e : ecs.GetEntities())
    {
        auto* transform = ecs.GetTransform(e);
        auto* sprite = ecs.GetSprite(e);

        if (!transform || !sprite)
            continue;

        const SpriteData* spriteData = spriteDB.GetSprite(static_cast<SpriteID>(sprite->spriteID));
        if (!spriteData)
            continue;

        renderer.DrawSpriteByID(
            sprite->spriteID,
            transform->x,
            transform->y,
            sprite->size,
            sprite->size
        );
    }
}