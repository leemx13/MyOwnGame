#pragma once

#include "Scene/sceneManager.h"
#include "Render/render.h"

struct GLFWwindow; // forward declaration

class Application
{
public:
    bool Init();
    void Run(float FPS);
    void Shutdown();

    GLFWwindow* GetWindow() const { return window; }
    SceneManager& GetSceneManager() { return sceneManager; }
    Renderer2D& GetRenderer() { return renderer; }

private:
    GLFWwindow* window = nullptr;
    SceneManager sceneManager;
    Renderer2D renderer;
};