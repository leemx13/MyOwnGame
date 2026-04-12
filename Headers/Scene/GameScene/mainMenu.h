#pragma once
#include <memory>
#include <iostream>
#include "Scene/scene.h"
#include "Render/render.h"

class MainMenu : public Scene
{
public:
    explicit MainMenu(Renderer2D& inRenderer) : renderer(inRenderer) {}            // ctor for Test scene

    void Load() override;
    void Init() override;
    void Update(float dt) override;
    void Render() override;
    void Shutdown() override;

private:
    Renderer2D& renderer;
    Mesh quad;
    Texture2D spriteTexture;
};