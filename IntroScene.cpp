#include "IntroScene.h"
#include "Sprite.h"
#include "SDL3/SDL.h"
#include "InputSystem.h"

IntroScene::IntroScene(GraphicsInterface* GI):Scene(GI)
{
	InputSystem::CreateMap("MoveX");
	InputSystem::CreateMap("MoveY");
	InputSystem::CreateMap("Shoot");
	InputSystem::CreateMap("Boost", SDLK_LSHIFT);

	InputSystem::Map("MoveX")->AddBinding(SDLK_D);
	InputSystem::Map("MoveX")->AddBinding(SDLK_A, true);

	InputSystem::Map("MoveY")->AddBinding(SDLK_W, true);
	InputSystem::Map("MoveY")->AddBinding(SDLK_S);

	InputSystem::Map("Shoot")->AddBinding(SDL_BUTTON_LEFT);

	GI->LoadImage("UFO.png");
	GI->LoadImage("bullet.png");

	Sprite* sprite = new Sprite(this, "UFO.png", 100);
	actors.push_back(sprite);
}
