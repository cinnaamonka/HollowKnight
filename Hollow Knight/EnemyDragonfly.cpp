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

	ChangeTexture(1, 6, 8);

	Rectf myShape = GetShape();
	Rectf bounds = GetBoundaries();

	if (myShape.left + myShape.width >= bounds.left + bounds.width || myShape.left < bounds.left)
	{
		m_Velocity.x *= -1;
	}
	if (myShape.bottom + myShape.height >= bounds.bottom + bounds.height || myShape.bottom < bounds.bottom)
	{
		m_Velocity.y *= -1;
	}
	if (!IsKilled())
	{
		myShape.left += m_Velocity.x * elapsedSec;
		myShape.bottom += m_Velocity.y * elapsedSec;
	}

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