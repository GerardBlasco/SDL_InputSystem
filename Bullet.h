#pragma once
#include "Sprite.h"
#include <iostream>

class Bullet : public Sprite
{
private:
	class Vector2 direction;

public:
	Bullet(Scene* myScene, std::string imgName, float sideSize, class Vector2 target, class Vector2 origin);

	virtual void Update();

	virtual void Move();
};

