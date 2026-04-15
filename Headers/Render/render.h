#pragma once
#include <glad/glad.h>
#include "Render/shader.h"
#include "Render/mesh.h"
#include "Render/texture2D.h"

struct UVRect
{
    float u0, v0;
    float u1, v1;
};

class Renderer2D
{
public:
    bool Init();
    void Shutdown();

    void BeginFrame(float r, float g, float b, float a);
    void EndFrame();

    Mesh CreateSpriteQuadMesh();
    void DestroyMesh(Mesh& mesh);
    void DrawMesh(const Mesh& mesh);

    bool LoadTexture(Texture2D& texture, const char* filePath);
    void DestroyTexture(Texture2D& texture);

    void DrawSprite(
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
};