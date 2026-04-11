#include "Scene/sceneManager.h"

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
    if (currentScene)
    {
        currentScene->Shutdown();
    }

    currentScene = std::move(newScene);

    if (currentScene)
    {
        currentScene->Load();
        currentScene->Init();
    }
}

void SceneManager::Update(float dt)
{
    if (currentScene)
    {
        currentScene->Update(dt);
    }
}

void SceneManager::Render()
{
    if (currentScene)
    {
        currentScene->Render();
    }
}