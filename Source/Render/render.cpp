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

        void main()
        {
            vec2 scaled = aPos * uScale;
            vec2 finalPos = scaled + uPosition;
            gl_Position = vec4(finalPos, 0.0, 1.0);
            vUV = aUV;
        }
    )";

    const char* fragmentSrc = R"(
        #version 330 core
        in vec2 vUV;
        out vec4 FragColor;

        uniform sampler2D uTexture;
        uniform vec4 uColor;

        void main()
        {
            FragColor = texture(uTexture, vUV) * uColor;
        }
    )";

    if (!shader.LoadFromSource(vertexSrc, fragmentSrc))
    {
        return false;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Renderer2D::Shutdown()
{
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
        // x      y      u     v
        -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  1.0f, 1.0f,

        -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.0f, 1.0f
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return mesh;
}

void Renderer2D::DestroyMesh(Mesh& mesh)
{
    if (mesh.vbo != 0)
    {
        glDeleteBuffers(1, &mesh.vbo);
        mesh.vbo = 0;
    }

    if (mesh.vao != 0)
    {
        glDeleteVertexArrays(1, &mesh.vao);
        mesh.vao = 0;
    }

    mesh.vertexCount = 0;
}

void Renderer2D::DrawMesh(const Mesh& mesh)
{
    shader.Use();

    glBindVertexArray(mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    glBindVertexArray(0);
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

    if (!data)
    {
        std::cout << "Failed to load texture: " << filePath << '\n';
        return false;
    }

    GLenum format = GL_RGB;
    if (texture.channels == 1)
        format = GL_RED;
    else if (texture.channels == 3)
        format = GL_RGB;
    else if (texture.channels == 4)
        format = GL_RGBA;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        texture.width,
        texture.height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    return true;
}

void Renderer2D::DestroyTexture(Texture2D& texture)
{
    if (texture.id != 0)
    {
        glDeleteTextures(1, &texture.id);
        texture.id = 0;
    }

    texture.width = 0;
    texture.height = 0;
    texture.channels = 0;
}

void Renderer2D::DrawSprite(
    const Mesh& mesh,
    const Texture2D& texture,
    float posX,
    float posY,
    float scaleX,
    float scaleY
)
{
    shader.Use();

    GLint posLoc = glGetUniformLocation(shader.GetProgram(), "uPosition");
    GLint scaleLoc = glGetUniformLocation(shader.GetProgram(), "uScale");
    GLint colorLoc = glGetUniformLocation(shader.GetProgram(), "uColor");
    GLint texLoc = glGetUniformLocation(shader.GetProgram(), "uTexture");

    glUniform2f(posLoc, Globals::WorldToNormalized::ConvertX(posX, WINWIDTH), Globals::WorldToNormalized::ConvertY(posY, WINHEIGHT));
    glUniform2f(scaleLoc, Globals::WorldToNormalized::ConvertScaleX(scaleX, WINWIDTH), Globals::WorldToNormalized::ConvertScaleX(scaleY, WINHEIGHT));
    glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glUniform1i(texLoc, 0);

    glBindVertexArray(mesh.vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}