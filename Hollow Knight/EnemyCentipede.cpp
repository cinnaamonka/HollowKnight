#include "pch.h"
#include "EnemyCentipede.h"

#include <Texture.h>

// EnemyCentipede

EnemyCentipede::EnemyCentipede(const Point2f& position) :
	BaseEnemy(position, "EnemyCentipede.png",5)
{
	SetVelocity(Vector2f(30.f, 0.0f));
	SetBoundaries(600.0f, GetShape().height); // default
}
EnemyCentipede::~EnemyCentipede()
{
	std::cout << "clear" << std::endl;
}
void EnemyCentipede::Update(float elapsedSec)
{
	UpdateFrame(elapsedSec,GetFramesNumber());

	ChangeTexture(1,4);

	Rectf myShape = GetShape();
	Rectf bounds = GetBoundaries();

	if (myShape.left + myShape.width >= bounds.left + bounds.width || myShape.left < bounds.left)
	{
		SetVelocity(GetVelocity() * (-1));
	}
	if (!IsKilled())
	{
		myShape.left += GetVelocity().x * elapsedSec;
	}
	
	SetShape(myShape);
}

