#pragma once
#include <glad/glad.h>
#include <unordered_map>
#include "Render/shader.h"
#include "Render/mesh.h"
#include "Render/texture2D.h"

struct UVRect
{
    float u0, v0;
    float u1, v1;
};

struct SpriteDefinition
{
    UVRect uv;
    float width;
    float height;
};

class Renderer2D
{
public:
    bool Init();
    void Shutdown();

    void BeginFrame(float r, float g, float b, float a);
    void EndFrame();

    bool LoadTexture(Texture2D& texture, const char* filePath);
    void DestroyTexture(Texture2D& texture);

    void SetAtlasTexture(const Texture2D& atlas);
    void RegisterSprite(int id, const UVRect& uv, float width, float height);

    void DrawSpriteByID(
        int id,
        float posX,
        float posY,
        float scaleX = 1.0f,
        float scaleY = 1.0f
    );

private:
    Mesh CreateSpriteQuadMesh();
    void DestroyMesh(Mesh& mesh);

    void DrawSpriteInternal(
        const Mesh& mesh,
        const Texture2D& texture,
        float posX,
        float posY,
        float scaleX,
        float scaleY,
        const UVRect& uv
    );

private:
    Shader shader;

    Mesh sharedQuad;

    Texture2D atlasTexture;
    bool hasAtlas = false;

    std::unordered_map<int, SpriteDefinition> spriteDefs;
};