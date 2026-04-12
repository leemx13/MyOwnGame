#include <windows.h>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <memory>
#include "Application/application.h"
#include "Scene/scene.h"
#include "Scene/GameScene/mainMenu.h"

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;

    AllocConsole();                                  //allocate stuff to console to print std::cout
    FILE* console = nullptr;
    freopen_s(&console, "CONOUT$", "w", stdout);

    Application app;

    if (!app.Init())                                    //if can't initialize app end program
        return -1;

    app.GetSceneManager().ChangeScene(
        std::make_unique<MainMenu>(app.GetRenderer(), app.GetWindow())
    );

    app.Run(60.0f);             //set fps
    app.Shutdown();

    return 0;
}