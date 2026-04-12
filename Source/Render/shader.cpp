#include "Render/shader.h"
#include <iostream>

Shader::~Shader()
{
    if (programID != 0)
    {
        glDeleteProgram(programID);
    }
}

GLuint Shader::Compile(GLenum type, const char* source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Shader compilation failed:\n" << infoLog << '\n';
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

bool Shader::LoadFromSource(const char* vertexSrc, const char* fragmentSrc)
{
    GLuint vertexShader = Compile(GL_VERTEX_SHADER, vertexSrc);
    if (!vertexShader) return false;

    GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSrc);
    if (!fragmentShader)
    {
        glDeleteShader(vertexShader);
        return false;
    }

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    GLint success = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cout << "Shader linking failed:\n" << infoLog << '\n';

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(programID);
        programID = 0;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

void Shader::Use() const
{
    glUseProgram(programID);
}