#pragma once
#include "Transform.h"
#include <vector>

class Actor
{
public:
	class Scene* myScene;

	Actor(class Scene* myScene);
	Transform transform {};
	virtual void Update();
	virtual void Render();

	void Move(float x, float y);
};

