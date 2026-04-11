#include <windows.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include "Application/application.h"
#include "Scene/scene.h"

class TestScene : public Scene
{
public:
    explicit TestScene(Renderer2D& inRenderer)
        : renderer(inRenderer)
    {
    }

    void Load() override
    {
        std::cout << "TestScene Load\n";
    }

    void Init() override
    {
        std::cout << "TestScene Init\n";
    }

    void Update(float dt) override
    {
        (void)dt;
    }

    void Render() override
    {
        renderer.DrawQuad();
    }

    void Shutdown() override
    {
        std::cout << "TestScene Shutdown\n";
    }

private:
    Renderer2D& renderer;
};

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd = 1)
{
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;

    AllocConsole();

    FILE* dummyFile = nullptr;
    freopen_s(&dummyFile, "CONOUT$", "w", stdout);
    freopen_s(&dummyFile, "CONOUT$", "w", stderr);

    Application app;

    if (!app.Init())
    {
        return -1;
    }

    app.GetSceneManager().ChangeScene(
        std::make_unique<TestScene>(app.GetRenderer())
    );

    app.Run();
    app.Shutdown();

    return 0;
}