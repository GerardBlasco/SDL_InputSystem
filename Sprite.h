#pragma once
#include "Actor.h"
#include <iostream>

class Sprite : public Actor
{
protected:
	std::string imageName;
	float sideSize;

public:
	Sprite(Scene* myScene, std::string imgName, float sideSize);
	Sprite(Scene* myScene, std::string imgName, Transform transform, float sideSize);
	virtual void Update();
	virtual void Render();

	virtual void Move();

	void Sprint();

	float bulletSize = 30;
};

