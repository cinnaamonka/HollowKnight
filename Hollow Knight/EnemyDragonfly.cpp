#include "pch.h"
#include "EnemyDragonfly.h"

#include <Texture.h>

EnemyDragonfly::EnemyDragonfly(const Point2f& position) :
	BaseEnemy(position, "EnemyDragonfly.png", 15)
{
	SetVelocity(Vector2f(100.0f, 100.0f));
	SetBoundaries(600.0f, GetShape().height * 10);
}
EnemyDragonfly::~EnemyDragonfly()
{

}
void EnemyDragonfly::Update(float elapsedSec)
{
	UpdateFrame(elapsedSec, GetFramesNumber());

	const int killingTexturesAmount = 1;
	const int movingTexturesAmount = 6;
	const int atackingTexturesAmount = 8;

	ChangeTexture(killingTexturesAmount, movingTexturesAmount, atackingTexturesAmount);

	const float groundPos = 3200.f;
	Rectf myShape = GetShape();
	Rectf bounds = GetBoundaries();
	const float fallingAfterDyingSpeed = 65.0f;

	if (IsKilled())
	{
		if (myShape.bottom >= groundPos)
		{
			myShape.bottom -= fallingAfterDyingSpeed * elapsedSec;
		}
		SetShape(myShape);
		return;
	}

	if (myShape.left + myShape.width >= bounds.left + bounds.width || myShape.left < bounds.left)
	{
		SetVelocity(Vector2f(GetVelocity().x * (-1), GetVelocity().y));

	}
	if (myShape.bottom + myShape.height >= bounds.bottom + bounds.height || myShape.bottom <= bounds.bottom)
	{
		SetVelocity(Vector2f(GetVelocity().x, GetVelocity().y * (-1)));
	}

	if (GetCanSeeAvatar())
	{
		Vector2f directionVector = Vector2f(GetAvatarShape().left, GetAvatarShape().bottom) - Vector2f(myShape.left, myShape.bottom);

		directionVector.Normalized();
		Vector2f velocity = directionVector;

		SetVelocity(velocity);
	}

	myShape.left += GetVelocity().x * elapsedSec;
	myShape.bottom += GetVelocity().y * elapsedSec;


	SetShape(myShape);
}

