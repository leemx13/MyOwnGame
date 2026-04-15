#pragma once
#include <unordered_map>
#include <vector>

using Entity = int;

struct TransformComponent
{
    float x = 0.0f;
    float y = 0.0f;
};

struct SpriteComponent
{
    int spriteID = -1;
    float size = 100.0f;
};

class ECS
{
public:
    Entity CreateEntity();
    void DestroyEntity(Entity e);

    void AddTransform(Entity e, float x, float y);
    void AddSprite(Entity e, int spriteID, float size);

    TransformComponent* GetTransform(Entity e);
    SpriteComponent* GetSprite(Entity e);

    const std::vector<Entity>& GetEntities() const;

private:
    Entity nextEntity = 0;
    std::vector<Entity> entities;

    std::unordered_map<Entity, TransformComponent> transforms;
    std::unordered_map<Entity, SpriteComponent> sprites;
};