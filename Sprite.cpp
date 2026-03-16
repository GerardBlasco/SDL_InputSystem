#include "Sprite.h"
#include "Scene.h"
#include "Bullet.h"
#include "Vector2.h"
#include "InputSystem.h"

Sprite::Sprite(Scene* myScene, std::string imgName, float sideSize):Actor(myScene)
{
	imageName = imgName;
	this->sideSize = sideSize;

	InputSystem::Map("Boost")->AddListener(this, &Sprite::Sprint);
}

Sprite::Sprite(Scene* myScene, std::string imgName, Transform transform, float sideSize):Actor(myScene)
{
	imageName = imgName;
	this->transform = transform;
	this->sideSize = sideSize;
}

void Sprite::Update()
{
	if (!InputSystem::Map("Boost")->performed) {
		bulletSize = 30;
	}

	// Ejecuta una accion cuando se hace trigger
	if (InputSystem::Map("Shoot")->triggered) {
		Bullet* bullet = new Bullet(myScene, "bullet.png", bulletSize, Vector2(InputSystem::DeltaX(), InputSystem::DeltaY()), transform.position + (sideSize / 2));
		myScene->LoadActor(bullet);
	}

	// Mueve la position del actor
	transform.position.x += InputSystem::Map("MoveX")->ReadFloat() * 0.05f;
	transform.position.y += InputSystem::Map("MoveY")->ReadFloat() * 0.05f;
}

void Sprite::Render()
{
	myScene->GI->DrawSprite(imageName, transform, sideSize, sideSize);
}

void Sprite::Move()
{
	transform.position.x += 0.2f;
}

void Sprite::Sprint()
{
	bulletSize = 60;
}
