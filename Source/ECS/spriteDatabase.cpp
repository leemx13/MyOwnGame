#include "ECS/spriteDatabase.h"

void SpriteDatabase::RegisterSprite(SpriteID id, const UVRect& uv)
{
    sprites[id] = { uv };
}

const SpriteData* SpriteDatabase::GetSprite(SpriteID id) const
{
    auto it = sprites.find(id);
    if (it != sprites.end())
        return &it->second;

    return nullptr;
}