#pragma once
#include <glad/glad.h>
#include "Render/shader.h"

class Renderer2D
{
public:
    bool Init();
    void Shutdown();

    void BeginFrame(float r, float g, float b, float a);
    void DrawQuad();
    void EndFrame();

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    Shader shader;
};