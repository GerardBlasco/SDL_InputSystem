#include "Actor.h"
#include "Scene.h"

Actor::Actor(Scene* myScene)
{
	this->myScene = myScene;
}

void Actor::Update()
{
	
}

void Actor::Move(float x, float y) 
{
	transform.position.x += x;
	transform.position.y += y;
}

void Actor::Render()
{

}
