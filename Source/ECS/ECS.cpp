#include "ECS/ecs.h"

Entity ECS::CreateEntity()
{
    Entity e = nextEntity++;
    entities.push_back(e);
    return e;
}

void ECS::DestroyEntity(Entity e)
{
    transforms.erase(e);
    sprites.erase(e);

    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        if (*it == e)
        {
            entities.erase(it);
            break;
        }
    }
}

void ECS::AddTransform(Entity e, float x, float y)
{
    transforms[e] = { x, y };
}

void ECS::AddSprite(Entity e, int spriteID, float size)
{
    sprites[e] = { spriteID, size };
}

TransformComponent* ECS::GetTransform(Entity e)
{
    auto it = transforms.find(e);
    if (it != transforms.end())
        return &it->second;
    return nullptr;
}

SpriteComponent* ECS::GetSprite(Entity e)
{
    auto it = sprites.find(e);
    if (it != sprites.end())
        return &it->second;
    return nullptr;
}

const std::vector<Entity>& ECS::GetEntities() const
{
    return entities;
}