#include "pch.h"
#include "EnemyDragonfly.h"

#include <Texture.h>

EnemyDragonfly::EnemyDragonfly(const Point2f& position) :
	BaseEnemy(position, "EnemyDragonfly.png", 15), m_Velocity{ 100.0f,100.0f }
{
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
		m_Velocity.x *= -1;

	}
	if (myShape.bottom + myShape.height >= bounds.bottom + bounds.height || myShape.bottom <= bounds.bottom)
	{
		m_Velocity.y *= -1;
	}

	if (GetCanSeeAvatar())
	{
		Vector2f directionVector = Vector2f(GetAvatarShape().left, GetAvatarShape().bottom) - Vector2f(myShape.left, myShape.bottom);

		directionVector.Normalized();
		Vector2f velocity = directionVector;

		m_Velocity = velocity;
	}
	
	myShape.left += m_Velocity.x * elapsedSec;
	myShape.bottom += m_Velocity.y * elapsedSec;


	SetShape(myShape);
}

void EnemyDragonfly::Draw() const
{
	if (m_Velocity.x < 0)
	{
		glPushMatrix();

		glTranslatef(GetShape().left, GetShape().bottom, 0);
		glRotatef(0, 0, 0, 1);
		glScalef(-1, 1, 1);
		glTranslatef(-GetShape().width, 0, 0);

		GetTexture()->Draw(Point2f(0, 0), GetSourceRect());

		glPopMatrix();
	}
	else
	{
		GetTexture()->Draw(GetShape(), GetSourceRect());
	}

}
