#include "ECS/spriteDefinitions.h"
#include "Globals/globals.h"

namespace
{
    UVRect GetUV(int col, int row, int spriteW, int spriteH, int texW, int texH)
    {
        float u0 = (col * spriteW) / (float)texW;
        float v0 = (row * spriteH) / (float)texH;
        float u1 = ((col + 1) * spriteW) / (float)texW;
        float v1 = ((row + 1) * spriteH) / (float)texH;

        return { u0, v0, u1, v1 };
    }

    void RegisterOne(
        SpriteDatabase& spriteDB,
        Renderer2D& renderer,
        SpriteID id,
        int col,
        int row)
    {
        const int spriteW = static_cast<int>(WIDTH_OF_ENTITY_IN_SPRITESHEET);
        const int spriteH = static_cast<int>(HEIGHT_OF_ENTITY_IN_SPRITESHEET);
        const int texW = static_cast<int>(WIDTH_OF_WHOLE_SPRITESHEET);
        const int texH = static_cast<int>(HEIGHT_OF_WHOLE_SPRITESHEET);

        UVRect uv = GetUV(col, row, spriteW, spriteH, texW, texH);

        spriteDB.RegisterSprite(id, uv);
        renderer.RegisterSprite(id, uv, 1.0f, 1.0f);
    }
}

namespace SpriteDefinitions
{
    void RegisterAllPlayerSprites(SpriteDatabase& spriteDB, Renderer2D& renderer)
    {
        RegisterOne(spriteDB, renderer, PLAYER_0, 0, 0);
        RegisterOne(spriteDB, renderer, PLAYER_1, 1, 0);
        RegisterOne(spriteDB, renderer, PLAYER_2, 2, 0);
        RegisterOne(spriteDB, renderer, PLAYER_3, 0, 1);
        RegisterOne(spriteDB, renderer, PLAYER_4, 1, 1);
        RegisterOne(spriteDB, renderer, PLAYER_5, 2, 1);
    }
}