#include "Application/application.h"
#include "Scene/GameScene/mainMenu.h"
#include "Render/render.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <chrono>
#include <thread>

void MainMenu::Load()
{
	std::cout << "MainMenu Load\n";
}

void MainMenu::Init()
{
	std::cout << "TestScene Init\n";

	quad = renderer.CreateSpriteQuadMesh();

	if (!renderer.LoadTexture(spriteTexture, "Assets/cat.png"))
	{
		std::cout << "Texture load failed.\n";
	}
}

void MainMenu::Update(float dt)
{
	glfwPollEvents();
	std::cout << "\rFPS: " << 1.0 / dt << std::flush;
	(void)dt;
	double mousex, mousey;
	glfwGetCursorPos(window, &mousex, &mousey);
	std::cout << " Mouse X: " << mousex << " Mouse Y: " << mousey << std::flush;

}

void MainMenu::Render()
{
	renderer.DrawSprite(
		quad,
		spriteTexture,
		0.0f, 0.0f,   // pos
		100.0f, 100.0f    // size
	);

}

void MainMenu::Shutdown()
{
	renderer.DestroyMesh(quad);
	renderer.DestroyTexture(spriteTexture);
	std::cout << "TestScene Shutdown\n";
}
