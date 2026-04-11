#pragma once
#include <glad/glad.h>
#include <string>

class Shader
{
public:
    Shader() = default;
    ~Shader();

    bool LoadFromSource(const char* vertexSrc, const char* fragmentSrc);
    void Use() const;

    GLuint GetProgram() const { return programID; }

private:
    GLuint programID = 0;

    GLuint Compile(GLenum type, const char* source);
};