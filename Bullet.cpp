#include "Bullet.h"
#include "Vector2.h"

Bullet::Bullet(Scene* myScene, std::string imgName, float sideSize, Vector2 target, Vector2 origin):Sprite(myScene, imgName, sideSize)
{
	transform.position = origin;

	direction = target - origin;

	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	direction.x /= length;
	direction.y /= length;
}

void Bullet::Update()
{
	Move();
}

void Bullet::Move()
{
	transform.position = transform.position + direction * 0.2f;
}
