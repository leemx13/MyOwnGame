#include "Application/application.h"
#include "Scene/GameScene/mainMenu.h"
#include "Render/render.h"
#include <iostream>

void MainMenu::Load()
{
	std::cout << "MainMenu Load\n";
}

void MainMenu::Init()
{
	std::cout << "MainMenu Init\n";
}

void MainMenu::Update(float dt)
{
	(void)dt;
	std::cout << "FPS: " << 1.0 / dt << "\n";
}

void MainMenu::Render()
{
	renderer.DrawQuad();
}

void MainMenu::Shutdown()
{
	std::cout << "MainMenu Shutdown\n";
}
