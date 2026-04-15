#include "Render/render.h"
#include "Globals/globals.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/stb_image.h"

bool Renderer2D::Init()
{
    const char* vertexSrc = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec2 aUV;

    out vec2 vUV;

    uniform vec2 uPosition;
    uniform vec2 uScale;
    uniform vec2 uScreenSize;

    uniform vec2 uUVMin;
    uniform vec2 uUVMax;

    void main()
    {
        vec2 scaled = aPos * uScale;
        vec2 worldPos = scaled + uPosition;

        float ndcX = worldPos.x / (uScreenSize.x * 0.5);
        float ndcY = worldPos.y / (uScreenSize.y * 0.5);

        gl_Position = vec4(ndcX, ndcY, 0.0, 1.0);

        vUV = mix(uUVMin, uUVMax, aUV);
    }
)";

    const char* fragmentSrc = R"(
    #version 330 core
    in vec2 vUV;
    out vec4 FragColor;

    uniform sampler2D uTexture;

    void main()
    {
        FragColor = texture(uTexture, vUV);
    }
)";

    if (!shader.LoadFromSource(vertexSrc, fragmentSrc))
        return false;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sharedQuad = CreateSpriteQuadMesh();

    return true;
}

void Renderer2D::Shutdown()
{
    DestroyMesh(sharedQuad);
}

void Renderer2D::BeginFrame(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer2D::EndFrame()
{
}

Mesh Renderer2D::CreateSpriteQuadMesh()
{
    Mesh mesh;

    float vertices[] =
    {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,

        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };

    mesh.vertexCount = 6;

    glGenVertexArrays(1, &mesh.vao);
    glGenBuffers(1, &mesh.vbo);

    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    return mesh;
}

void Renderer2D::DestroyMesh(Mesh& mesh)
{
    if (mesh.vbo) glDeleteBuffers(1, &mesh.vbo);
    if (mesh.vao) glDeleteVertexArrays(1, &mesh.vao);
}

bool Renderer2D::LoadTexture(Texture2D& texture, const char* filePath)
{
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(
        filePath,
        &texture.width,
        &texture.height,
        &texture.channels,
        0
    );

    if (!data) return false;

    GLenum format = (texture.channels == 4) ? GL_RGBA : GL_RGB;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexImage2D(GL_TEXTURE_2D, 0, format,
        texture.width, texture.height,
        0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return true;
}

void Renderer2D::DestroyTexture(Texture2D& texture)
{
    if (texture.id)
        glDeleteTextures(1, &texture.id);
}

void Renderer2D::SetAtlasTexture(const Texture2D& atlas)
{
    atlasTexture = atlas;
    hasAtlas = true;
}

void Renderer2D::RegisterSprite(int id, const UVRect& uv, float width, float height)
{
    spriteDefs[id] = { uv, width, height };
}

void Renderer2D::DrawSpriteByID(
    int id,
    float posX,
    float posY,
    float scaleX,
    float scaleY
)
{
    if (!hasAtlas) return;

    auto it = spriteDefs.find(id);
    if (it == spriteDefs.end()) return;

    const SpriteDefinition& def = it->second;

    DrawSpriteInternal(
        sharedQuad,
        atlasTexture,
        posX,
        posY,
        def.width * scaleX,
        def.height * scaleY,
        def.uv
    );
}

void Renderer2D::DrawSpriteInternal(
    const Mesh& mesh,
    const Texture2D& texture,
    float posX,
    float posY,
    float scaleX,
    float scaleY,
    const UVRect& uv
)
{
    shader.Use();

    glUniform2f(glGetUniformLocation(shader.GetProgram(), "uPosition"), posX, posY);
    glUniform2f(glGetUniformLocation(shader.GetProgram(), "uScale"), scaleX, scaleY);
    glUniform2f(glGetUniformLocation(shader.GetProgram(), "uScreenSize"), WINWIDTH, WINHEIGHT);

    glUniform2f(glGetUniformLocation(shader.GetProgram(), "uUVMin"), uv.u0, uv.v0);
    glUniform2f(glGetUniformLocation(shader.GetProgram(), "uUVMax"), uv.u1, uv.v1);

    glBindTexture(GL_TEXTURE_2D, texture.id);

    glBindVertexArray(mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
}