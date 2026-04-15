#include "Application/application.h"
#include "Scene/GameScene/mainMenu.h"
#include "Render/render.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <chrono>
#include <thread>

UVRect GetUV(int col, int row, int spriteW, int spriteH, int texW, int texH)
{
	float u0 = (col * spriteW) / (float)texW;
	float v0 = (row * spriteH) / (float)texH;
	float u1 = ((col + 1) * spriteW) / (float)texW;
	float v1 = ((row + 1) * spriteH) / (float)texH;

	return { u0, v0, u1, v1 };
}

UVRect playerFrames[6];
int currentFrame = 0;
float animTimer = 0.0f;
float frameDuration = 10.0f;

void MainMenu::Load()
{
	std::cout << "MainMenu Load\n";
}

void MainMenu::Init()
{
	std::cout << "TestScene Init\n";

	quad = renderer.CreateSpriteQuadMesh();

	renderer.LoadTexture(spriteTexture, "Assets/player.png");

	playerFrames[0] = GetUV(0, 0, 204, 204, 612, 408);
	playerFrames[1] = GetUV(1, 0, 204, 204, 612, 408);
	playerFrames[2] = GetUV(2, 0, 204, 204, 612, 408);

	playerFrames[3] = GetUV(0, 1, 204, 204, 612, 408);
	playerFrames[4] = GetUV(1, 1, 204, 204, 612, 408);
	playerFrames[5] = GetUV(2, 1, 204, 204, 612, 408);

}

void MainMenu::Update(float dt)
{
	std::cout << "\rFPS: " << 1.0 / dt << std::flush;

	animTimer += dt;

	if (animTimer >= frameDuration)
	{
		animTimer -= frameDuration;
		currentFrame = (currentFrame + 1) % 6;
	}
}

void MainMenu::Render()
{

	renderer.DrawSprite(quad, spriteTexture, 0, 0, 100, 100, playerFrames[currentFrame]);

}

void MainMenu::Shutdown()
{
	renderer.DestroyMesh(quad);
	renderer.DestroyTexture(spriteTexture);
	std::cout << "TestScene Shutdown\n";
}
