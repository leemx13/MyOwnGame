#pragma once
#include <glad/glad.h>

struct Texture2D
{
    GLuint id = 0;
    int width = 0;
    int height = 0;
    int channels = 0;
};