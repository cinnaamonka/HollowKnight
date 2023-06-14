#include "pch.h"
#include "EnemyDragonfly.h"

#include <Texture.h>

EnemyDragonfly::EnemyDragonfly(const Point2f& position) :
	BaseEnemy(position, "EnemyDragonfly.png", 15), m_CanSeeAvatar(false)
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

	Rectf myShape = GetShape();
	Rectf bounds = GetBoundaries();

	if (IsKilled())
	{
		return;
	}

	bool isCollide
	{
		myShape.left < bounds.left + bounds.width && 
		myShape.left + myShape.width > bounds.left &&
	    myShape.bottom < bounds.bottom && 
		myShape.bottom > bounds.bottom
	};

	if ((myShape.left + myShape.width >= bounds.left + bounds.width || myShape.left <= bounds.left) && isCollide)
	{
		SetVelocity(Vector2f(GetVelocity().x * (-1), GetVelocity().y));
	
	}
	if ((myShape.bottom + myShape.height >= bounds.bottom + bounds.height || myShape.bottom <= bounds.bottom) && isCollide)
	{
		SetVelocity(Vector2f(GetVelocity().x, GetVelocity().y * (-1)));	
	}

	if (GetCanSeeAvatar())
	{
		Vector2f directionVector = Vector2f(GetAvatarShape().left, GetAvatarShape().bottom) - Vector2f(myShape.left, myShape.bottom);
		m_CanSeeAvatar = true;
		directionVector.Normalized();
		Vector2f velocity = directionVector;
		SetVelocity(velocity);
	}
	else
	{
		m_CanSeeAvatar = false;
	}

	if (m_CanSeeAvatar)
	{
		myShape.left += GetVelocity().x * elapsedSec;
		myShape.bottom += GetVelocity().y * elapsedSec;
	}

	SetShape(myShape);
}

