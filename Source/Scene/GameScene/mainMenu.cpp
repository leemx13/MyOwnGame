#include "Scene/GameScene/mainMenu.h"
#include "ECS/spriteDefinitions.h"
#include "ECS/spriteIDs.h"
#include <iostream>

void MainMenu::Load()
{
    std::cout << "MainMenu Load\n";
}

void MainMenu::Init()
{
    std::cout << "MainMenu Init\n";

    renderer.LoadTexture(atlas, "Assets/player.png");
    renderer.SetAtlasTexture(atlas);

    SpriteDefinitions::RegisterAllPlayerSprites(spriteDB, renderer);

    Entity e1 = ecs.CreateEntity();
    ecs.AddTransform(e1, -300.0f, 0.0f);
    ecs.AddSprite(e1, PLAYER_0, 100.0f);

    Entity e2 = ecs.CreateEntity();
    ecs.AddTransform(e2, 0.0f, 0.0f);
    ecs.AddSprite(e2, PLAYER_1, 100.0f);

    Entity e3 = ecs.CreateEntity();
    ecs.AddTransform(e3, 300.0f, 0.0f);
    ecs.AddSprite(e3, PLAYER_3, 100.0f);
}

void MainMenu::Update(float dt)
{
    (void)dt;
}

void MainMenu::Render()
{
    renderSystem.Render(ecs, spriteDB, renderer);
}

void MainMenu::Shutdown()
{
    renderer.DestroyTexture(atlas);
}