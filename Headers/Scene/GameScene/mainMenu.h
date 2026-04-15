#pragma once
#include "Scene/scene.h"
#include "Render/render.h"
#include "ECS/ecs.h"
#include "ECS/spriteDatabase.h"
#include "ECS/renderSystem.h"
#include <GLFW/glfw3.h>

class MainMenu : public Scene
{
public:
    MainMenu(Renderer2D& r, GLFWwindow* w)
        : renderer(r), window(w) {
    }

    void Load() override;
    void Init() override;
    void Update(float dt) override;
    void Render() override;
    void Shutdown() override;

private:
    Renderer2D& renderer;
    GLFWwindow* window = nullptr;

    Texture2D atlas;

    ECS ecs;
    SpriteDatabase spriteDB;
    RenderSystem renderSystem;
};