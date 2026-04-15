#pragma once
#include <unordered_map>
#include "Render/render.h"
#include "ECS/spriteIDs.h"

struct SpriteData
{
    UVRect uv;
};

class SpriteDatabase
{
public:
    void RegisterSprite(SpriteID id, const UVRect& uv);
    const SpriteData* GetSprite(SpriteID id) const;

private:
    std::unordered_map<int, SpriteData> sprites;
};