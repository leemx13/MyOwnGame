#include "Application/application.h"
#include <glad/glad.h>       
#include <GLFW/glfw3.h>      
#include <iostream>

bool Application::Init()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW.\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "GAM200 Engine", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window.\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // 1 is to match fps to monitor refresh rate 

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to initialize GLAD.\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }

    glViewport(0, 0, 1280, 720);

    if (!renderer.Init())
    {
        std::cerr << "Failed to initialize renderer.\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }

    return true;
}

void Application::Run()
{
    float lastTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        glfwPollEvents();

        sceneManager.Update(dt);

        renderer.BeginFrame(0.0f, 0.0f, 0.0f, 1.0f);
        sceneManager.Render();
        renderer.EndFrame();

        glfwSwapBuffers(window);
    }
}

void Application::Shutdown()
{
    renderer.Shutdown();

    if (window)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    glfwTerminate();
}