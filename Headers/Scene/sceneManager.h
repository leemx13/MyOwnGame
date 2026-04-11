#pragma once
#include <memory>
#include "Scene/scene.h"

class SceneManager
{
public:
    void ChangeScene(std::unique_ptr<Scene> newScene);

    void Update(float dt);
    void Render();

private:
    std::unique_ptr<Scene> currentScene;
};